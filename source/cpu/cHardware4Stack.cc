/*
 *  cHardware4Stack.cc
 *  Avida
 *
 *  Created by David on 11/17/05.
 *  Copyright 2005-2006 Michigan State University. All rights reserved.
 *  Copyright 1999-2003 California Institute of Technology.
 *
 */

#include "cHardware4Stack.h"

#include "cAvidaContext.h"
#include "cCPUTestInfo.h"
#include "functions.h"
#include "cGenomeUtil.h"
#include "cInstLibBase.h"
#include "cInstSet.h"
#include "cHardwareManager.h"
#include "cHardwareTracer.h"
#include "cMutation.h"
#include "cMutationLib.h"
#include "nMutation.h"
#include "cOrganism.h"
#include "cPhenotype.h"
#include "cRandom.h"
#include "cStringUtil.h"
#include "cTestCPU.h"
#include "cWorldDriver.h"
#include "cWorld.h"

#include <limits.h>

using namespace std;


class cInstLib4Stack : public cInstLibBase
{
  const size_t m_nopmods_array_size;
  const size_t m_function_array_size;
  cString *m_nopmod_names;
  cString *m_function_names;
  const int *m_nopmods;
  cHardware4Stack::tHardware4StackMethod *m_functions;
  static const cInstruction inst_error;
  static const cInstruction inst_default;
public:
    cInstLib4Stack(
                   size_t nopmod_array_size,
                   size_t function_array_size,
                   cString *nopmod_names,
                   cString *function_names,
                   const int *nopmods,
                   cHardware4Stack::tHardware4StackMethod *functions
                   ):m_nopmods_array_size(nopmod_array_size),
    m_function_array_size(function_array_size),
    m_nopmod_names(nopmod_names),
    m_function_names(function_names),
    m_nopmods(nopmods),
    m_functions(functions)
  {}
  cHardware4Stack::tHardware4StackMethod *GetFunctions(void){ return m_functions; } 
  const cString &GetName(const unsigned int id) {
    assert(id < m_function_array_size);
    return m_function_names[id];
  }
  const cString &GetNopName(const unsigned int id) {
    assert(id < m_nopmods_array_size);
    return m_nopmod_names[id];
  }
  int GetNopMod(const unsigned int id){
    assert(id < m_nopmods_array_size);
    return m_nopmods[id];
  }
  int GetNopMod(const cInstruction & inst){
    return GetNopMod(inst.GetOp());
  }
  int GetSize(){ return m_function_array_size; }
  int GetNumNops(){ return m_nopmods_array_size; }
  cInstruction GetInst(const cString & in_name){
    for (unsigned int i = 0; i < m_function_array_size; i++) {
      if (m_function_names[i] == in_name) return cInstruction(i);
    }
    return cInstLib4Stack::GetInstError();
  }
  const cInstruction & GetInstDefault(){ return inst_default; }
  const cInstruction & GetInstError(){ return inst_error; }
};

const cInstruction cInstLib4Stack::inst_error(255);
const cInstruction cInstLib4Stack::inst_default(0);

cInstLib4Stack* cHardware4Stack::s_inst_slib = cHardware4Stack::initInstLib();

cInstLibBase* cHardware4Stack::GetInstLib() { return s_inst_slib; }

cInstLib4Stack* cHardware4Stack::initInstLib(void)
{
  struct cNOPEntry4Stack {
    cNOPEntry4Stack(const cString &name, int nop_mod):name(name), nop_mod(nop_mod){}
    cString name;
    int nop_mod;
  };
  static const cNOPEntry4Stack s_n_array[] = {
    cNOPEntry4Stack("Nop-A", nHardware4Stack::STACK_AX),
    cNOPEntry4Stack("Nop-B", nHardware4Stack::STACK_BX),
    cNOPEntry4Stack("Nop-C", nHardware4Stack::STACK_CX),
    cNOPEntry4Stack("Nop-D", nHardware4Stack::STACK_DX),
    cNOPEntry4Stack("Nop-E", nHardware4Stack::STACK_EX),
    cNOPEntry4Stack("Nop-F", nHardware4Stack::STACK_FX)
  };
  
  struct cInstEntry4Stack {
    cInstEntry4Stack(const cString &name, tHardware4StackMethod function):name(name), function(function){}
    cString name;
    tHardware4StackMethod function;
  };
  static const cInstEntry4Stack s_f_array[] = {
    //1 
    cInstEntry4Stack("Nop-A",     &cHardware4Stack::Inst_Nop), 
    //2
    cInstEntry4Stack("Nop-B",     &cHardware4Stack::Inst_Nop), 
    //3
    cInstEntry4Stack("Nop-C",     &cHardware4Stack::Inst_Nop),   
    //4 
    cInstEntry4Stack("Nop-D",     &cHardware4Stack::Inst_Nop), 
    //38
    cInstEntry4Stack("Nop-E",     &cHardware4Stack::Inst_Nop),
    //39
    cInstEntry4Stack("Nop-F",     &cHardware4Stack::Inst_Nop),
    //5
    cInstEntry4Stack("Nop-X",     &cHardware4Stack::Inst_Nop),
    //6 
    cInstEntry4Stack("Val-Shift-R",   &cHardware4Stack::Inst_ShiftR),
    //7
    cInstEntry4Stack("Val-Shift-L",   &cHardware4Stack::Inst_ShiftL),
    //8
    cInstEntry4Stack("Val-Nand",      &cHardware4Stack::Inst_Val_Nand),
    //9
    cInstEntry4Stack("Val-Add",       &cHardware4Stack::Inst_Val_Add),
    //10
    cInstEntry4Stack("Val-Sub",       &cHardware4Stack::Inst_Val_Sub),
    //11
    cInstEntry4Stack("Val-Mult",      &cHardware4Stack::Inst_Val_Mult),
    //12
    cInstEntry4Stack("Val-Div",       &cHardware4Stack::Inst_Val_Div),
    //13
    cInstEntry4Stack("SetMemory",   &cHardware4Stack::Inst_SetMemory),
    //14
    cInstEntry4Stack("Divide",  &cHardware4Stack::Inst_Divide),
    //15
    cInstEntry4Stack("Inst-Read",    &cHardware4Stack::Inst_HeadRead),
    //16
    cInstEntry4Stack("Inst-Write",   &cHardware4Stack::Inst_HeadWrite),
    //keeping this one for the transition period
    //cInstEntry4Stack("Inst-Copy",    &cHardware4Stack::Inst_HeadCopy),
    //17
    cInstEntry4Stack("If-Equal",    &cHardware4Stack::Inst_IfEqual),
    //18
    cInstEntry4Stack("If-Not-Equal",  &cHardware4Stack::Inst_IfNotEqual),
    //19
    cInstEntry4Stack("If-Less",   &cHardware4Stack::Inst_IfLess),
    //20
    cInstEntry4Stack("If-Greater",    &cHardware4Stack::Inst_IfGreater),
    //21
    cInstEntry4Stack("Head-Push",    &cHardware4Stack::Inst_HeadPush),
    //22
    cInstEntry4Stack("Head-Pop",     &cHardware4Stack::Inst_HeadPop),
    //23
    cInstEntry4Stack("Head-Move",  &cHardware4Stack::Inst_HeadMove),
    //24
    cInstEntry4Stack("Search",  &cHardware4Stack::Inst_Search),
    //25
    cInstEntry4Stack("Push-Next",    &cHardware4Stack::Inst_PushNext),
    //26
    cInstEntry4Stack("Push-Prev",    &cHardware4Stack::Inst_PushPrevious),
    //27
    cInstEntry4Stack("Push-Comp",    &cHardware4Stack::Inst_PushComplement),
    //28
    cInstEntry4Stack("Val-Delete", &cHardware4Stack::Inst_ValDelete),
    //29
    cInstEntry4Stack("Val-Copy",  &cHardware4Stack::Inst_ValCopy),
    //30
    cInstEntry4Stack("ThreadFork",   &cHardware4Stack::Inst_ForkThread),
    //31
    //cInstEntry4Stack("if-label",  &cHardware4Stack::Inst_IfLabel),
    //32
    cInstEntry4Stack("Val-Inc",       &cHardware4Stack::Inst_Increment),
    //33
    cInstEntry4Stack("Val-Dec",       &cHardware4Stack::Inst_Decrement),
    //34
    cInstEntry4Stack("Val-Mod",       &cHardware4Stack::Inst_Mod),
    //35
    cInstEntry4Stack("ThreadKill",   &cHardware4Stack::Inst_KillThread),
    //36
    cInstEntry4Stack("IO", &cHardware4Stack::Inst_IO),
    //37
    cInstEntry4Stack("Inject", &cHardware4Stack::Inst_Inject),
    
    cInstEntry4Stack("NULL", &cHardware4Stack::Inst_Nop) // Last Instruction Always NULL
  };
  
  const int n_size = sizeof(s_n_array)/sizeof(cNOPEntry4Stack);
  
  static cString n_names[n_size];
  static int nop_mods[n_size];
  for (int i = 0; i < n_size; i++){
    n_names[i] = s_n_array[i].name;
    nop_mods[i] = s_n_array[i].nop_mod;
  }
  
  const int f_size = sizeof(s_f_array)/sizeof(cInstEntry4Stack);
  static cString f_names[f_size];
  static tHardware4StackMethod functions[f_size];
  for (int i = 0; i < f_size; i++){
    f_names[i] = s_f_array[i].name;
    functions[i] = s_f_array[i].function;
  }
  
  cInstLib4Stack *inst_lib = new cInstLib4Stack(
                                                n_size,
                                                f_size,
                                                n_names,
                                                f_names,
                                                nop_mods,
                                                functions
                                                );
  
  return inst_lib;
}

cHardware4Stack::cHardware4Stack(cWorld* world, cOrganism* in_organism, cInstSet* in_m_inst_set)
: cHardwareBase(world, in_organism, in_m_inst_set)
, memory_array(nHardware4Stack::NUM_MEMORY_SPACES)
{
  /* FIXME:  reorganize storage of m_functions.  -- kgn */
  m_functions = s_inst_slib->GetFunctions();
  /**/
  inst_remainder = 0;
  
  for(int x=1; x <= m_world->GetConfig().MAX_CPU_THREADS.Get(); x++)
  {
    slice_array[x] = (x-1) * m_world->GetConfig().THREAD_SLICING_METHOD.Get() + 1;
  }
  
  memory_array[0] = in_organism->GetGenome();  // Initialize memory...
  memory_array[0].Resize(GetMemory(0).GetSize()+1);
  memory_array[0][memory_array[0].GetSize()-1] = cInstruction();
  Reset();                            // Setup the rest of the hardware...
}


cHardware4Stack::cHardware4Stack(const cHardware4Stack &hardware_4stack)
: cHardwareBase(hardware_4stack.m_world, hardware_4stack.organism, hardware_4stack.m_inst_set)
, m_functions(hardware_4stack.m_functions)
, memory_array(hardware_4stack.memory_array)
, threads(hardware_4stack.threads)
, thread_id_chart(hardware_4stack.thread_id_chart)
, cur_thread(hardware_4stack.cur_thread)
, inst_cost(hardware_4stack.inst_cost)
#if INSTRUCTION_COSTS
, inst_ft_cost(hardware_4stack.inst_ft_cost)
, inst_remainder(hardware_4stack.inst_remainder)
#endif
{
  for(int i = 0; i < nHardware4Stack::NUM_GLOBAL_STACKS; i++){
    global_stacks[i] = hardware_4stack.global_stacks[i];
  }
  for(unsigned int i = 0; i < sizeof(slice_array)/sizeof(float); i++){
    slice_array[i] = hardware_4stack.slice_array[i];
  }
}


void cHardware4Stack::Reset()
{
  //global_stack.Clear();
  //thread_time_used = 0;
  
  // Setup the memory...
  for (int i = 1; i < nHardware4Stack::NUM_MEMORY_SPACES; i++) {
    memory_array[i].Resize(1);
    //GetMemory(i).Replace(0, 1, cGenome(ConvertToInstruction(i)));
    GetMemory(i)=cGenome(ConvertToInstruction(i)); 
  }
  
  // We want to reset to have a single thread.
  threads.Resize(1);
  
  // Reset that single thread.
  threads[0].Reset(this, 0);
  thread_id_chart = 1; // Mark only the first thread as taken...
  cur_thread = 0;
  
  // Reset all stacks (local and global)
  for(int i = 0; i < nHardware4Stack::NUM_STACKS; i++) Stack(i).Clear();
  
#if INSTRUCTION_COSTS
  // instruction cost arrays
  const int num_inst_cost = m_inst_set->GetSize();
  inst_cost.Resize(num_inst_cost);
  inst_ft_cost.Resize(num_inst_cost);
  
  for (int i = 0; i < num_inst_cost; i++) {
    inst_cost[i] = m_inst_set->GetCost(cInstruction(i));
    inst_ft_cost[i] = m_inst_set->GetFTCost(cInstruction(i));
  }
#endif
  
}

// This function processes the very next command in the genome, and is made
// to be as optimized as possible.  This is the heart of avida.

void cHardware4Stack::SingleProcess(cAvidaContext& ctx)
{
  // Mark this organism as running...
  organism->SetRunning(true);
  
  cPhenotype & phenotype = organism->GetPhenotype();
  phenotype.IncTimeUsed();
  
  const int num_inst_exec = int(slice_array[GetNumThreads()]+ inst_remainder);
  inst_remainder = slice_array[GetNumThreads()] + inst_remainder - num_inst_exec;
  
  for (int i = 0; i < num_inst_exec; i++) {
    // Setup the hardware for the next instruction to be executed.
    ThreadNext();
    AdvanceIP() = true;
    IP().Adjust();
    
#if BREAKPOINTS
    if (IP().FlagBreakpoint()) {
      organism->DoBreakpoint();
    }
#endif
    
    // Print the status of this CPU at each step...
    if (m_tracer != NULL) m_tracer->TraceHardware(*this);
    
    // Find the instruction to be executed
    const cInstruction& cur_inst = IP().GetInst();
    
    // Test if costs have been paid and it is okay to execute this now...
    const bool exec = SingleProcess_PayCosts(ctx, cur_inst);
    
    // Now execute the instruction...
    if (exec == true) {
      SingleProcess_ExecuteInst(ctx, cur_inst);
      
      // Some instruction (such as jump) may turn advance_ip off.  Ususally
      // we now want to move to the next instruction in the memory.
      if (AdvanceIP() == true) IP().Advance();
    } // if exec
    
  } // Previous was executed once for each thread...
  
  // Kill creatures who have reached their max num of instructions executed
  const int max_executed = organism->GetMaxExecuted();
  if ((max_executed > 0 && phenotype.GetTimeUsed() >= max_executed)
      || phenotype.GetToDie()) {
    organism->Die();
  }
  
  organism->SetRunning(false);
}

// This method will test to see if all costs have been paid associated
// with executing an instruction and only return true when that instruction
// should proceed.
bool cHardware4Stack::SingleProcess_PayCosts(cAvidaContext& ctx, const cInstruction& cur_inst)
{
#if INSTRUCTION_COSTS
  assert(cur_inst.GetOp() < inst_cost.GetSize());
  
  // If first time cost hasn't been paid off...
  if ( inst_ft_cost[cur_inst.GetOp()] > 0 ) {
    inst_ft_cost[cur_inst.GetOp()]--;       // dec cost
    return false;
  }
  
  // Next, look at the per use cost
  if ( m_inst_set->GetCost(cur_inst) > 0 ) {
    if ( inst_cost[cur_inst.GetOp()] > 1 ){  // if isn't paid off (>1)
      inst_cost[cur_inst.GetOp()]--;         // dec cost
      return false;
    } else {                                 // else, reset cost array
      inst_cost[cur_inst.GetOp()] = m_inst_set->GetCost(cur_inst);
    }
  }
  
  // Prob of exec
  if ( m_inst_set->GetProbFail(cur_inst) > 0.0 ){
    return !( ctx.GetRandom().P(m_inst_set->GetProbFail(cur_inst)) );
  }
#endif
  return true;
}

// This method will handle the actuall execution of an instruction
// within single process, once that function has been finalized.
bool cHardware4Stack::SingleProcess_ExecuteInst(cAvidaContext& ctx, const cInstruction& cur_inst) 
{
  // Copy Instruction locally to handle stochastic effects
  cInstruction actual_inst = cur_inst;
  
#ifdef EXECUTION_ERRORS
  // If there is an execution error, execute a random instruction.
  if (organism->TestExeErr()) actual_inst = m_inst_set->GetRandomInst(ctx);
#endif /* EXECUTION_ERRORS */
  
  // Get a pointer to the corrisponding method...
  int inst_idx = m_inst_set->GetLibFunctionIndex(actual_inst);
  
  // Mark the instruction as executed
  IP().SetFlagExecuted();
	
  
#if INSTRUCTION_COUNT
  // instruction execution count incremeneted
  organism->GetPhenotype().IncCurInstCount(actual_inst.GetOp());
#endif
	
  // And execute it.
  const bool exec_success = (this->*(m_functions[inst_idx]))(ctx);
	
#if INSTRUCTION_COUNT
  // decremenet if the instruction was not executed successfully
  if (exec_success == false) {
    organism->GetPhenotype().DecCurInstCount(actual_inst.GetOp());
  }
#endif	
  
  return exec_success;
}


void cHardware4Stack::ProcessBonusInst(cAvidaContext& ctx, const cInstruction & inst)
{
  // Mark this organism as running...
  bool prev_run_state = organism->GetIsRunning();
  organism->SetRunning(true);
  
  if (m_tracer != NULL) m_tracer->TraceHardware(*this, true);
  
  SingleProcess_ExecuteInst(ctx, inst);
  
  organism->SetRunning(prev_run_state);
}

bool cHardware4Stack::OK()
{
  bool result = true;
  
  for(int i = 0 ; i < nHardware4Stack::NUM_MEMORY_SPACES; i++) {
    if (!memory_array[i].OK()) result = false;
  }
  
  for (int i = 0; i < GetNumThreads(); i++) {
    for(int j=0; j<nHardware4Stack::NUM_LOCAL_STACKS; j++)
      if (threads[i].local_stacks[j].OK() == false) result = false;
    if (threads[i].next_label.OK() == false) result = false;
  }
  
  return result;
}

void cHardware4Stack::PrintStatus(ostream& fp)
{
  fp << organism->GetPhenotype().GetTimeUsed() << " "
  << "IP:(" << IP().GetMemSpace() << ", " << IP().GetPosition() << ")    "
  
  << "AX:" << Stack(nHardware4Stack::STACK_AX).Top() << " "
  << setbase(16) << "[0x" << Stack(nHardware4Stack::STACK_AX).Top() << "]  " << setbase(10)
  
  << "BX:" << Stack(nHardware4Stack::STACK_BX).Top() << " "
  << setbase(16) << "[0x" << Stack(nHardware4Stack::STACK_BX).Top() << "]  " << setbase(10)
  
  << "CX:" << Stack(nHardware4Stack::STACK_CX).Top() << " "
  << setbase(16) << "[0x" << Stack(nHardware4Stack::STACK_CX).Top() << "]  " << setbase(10)
  
  << "DX:" << Stack(nHardware4Stack::STACK_DX).Top() << " "
  << setbase(16) << "[0x" << Stack(nHardware4Stack::STACK_DX).Top() << "]  " << setbase(10)
  
  << endl;
  
  fp << "  R-Head:(" << GetHead(nHardware::HEAD_READ).GetMemSpace() << ", " 
    << GetHead(nHardware::HEAD_READ).GetPosition() << ")  " 
    << "W-Head:(" << GetHead(nHardware::HEAD_WRITE).GetMemSpace()  << ", "
    << GetHead(nHardware::HEAD_WRITE).GetPosition() << ")  "
    << "F-Head:(" << GetHead(nHardware::HEAD_FLOW).GetMemSpace()   << ",  "
    << GetHead(nHardware::HEAD_FLOW).GetPosition() << ")  "
    << "RL:" << GetReadLabel().AsString() << "   "
    << endl;
  
  fp << "  Mem (" << GetMemory(0).GetSize() << "):"
		  << "  " << GetMemory(0).AsString()
		  << endl;
  fp << "       " << GetMemory(1).GetSize() << "):"
		  << "  " << GetMemory(1).AsString()
		  << endl;
  fp << "       " << GetMemory(2).GetSize() << "):"
		  << "  " << GetMemory(2).AsString()
		  << endl;
  fp << "       " << GetMemory(3).GetSize() << "):"
		  << "  " << GetMemory(3).AsString()
		  << endl;
  
  
  fp.flush();
}




/////////////////////////////////////////////////////////////////////////
// Method: cHardware4Stack::FindLabel(direction)
//
// Search in 'direction' (+ or - 1) from the instruction pointer for the
// compliment of the label in 'next_label' and return a pointer to the
// results.  If direction is 0, search from the beginning of the genome.
//
/////////////////////////////////////////////////////////////////////////

cHeadMultiMem cHardware4Stack::FindLabel(int direction)
{
  cHeadMultiMem & inst_ptr = IP();
  
  // Start up a search head at the position of the instruction pointer.
  cHeadMultiMem search_head(inst_ptr);
  cCodeLabel & search_label = GetLabel();
  
  // Make sure the label is of size  > 0.
  
  if (search_label.GetSize() == 0) {
    return inst_ptr;
  }
  
  // Call special functions depending on if jump is forwards or backwards.
  int found_pos = 0;
  if( direction < 0 ) {
    found_pos = FindLabel_Backward(search_label, inst_ptr.GetMemory(),
                                   inst_ptr.GetPosition() - search_label.GetSize());
  }
  
  // Jump forward.
  else if (direction > 0) {
    found_pos = FindLabel_Forward(search_label, inst_ptr.GetMemory(),
                                  inst_ptr.GetPosition());
  }
  
  // Jump forward from the very beginning.
  else {
    found_pos = FindLabel_Forward(search_label, inst_ptr.GetMemory(), 0);
  }
  
  // Return the last line of the found label, if it was found.
  if (found_pos > 0) search_head.Set(found_pos - 1, IP().GetMemSpace());
  //*** I THINK THIS MIGHT HAVE BEEN WRONG...CHANGED >= to >.  -law ***//
  
  // Return the found position (still at start point if not found).
  return search_head;
}


// Search forwards for search_label from _after_ position pos in the
// memory.  Return the first line _after_ the the found label.  It is okay
// to find search label's match inside another label.

int cHardware4Stack::FindLabel_Forward(const cCodeLabel & search_label,
                                       const cGenome & search_genome, int pos)
{
  assert (pos < search_genome.GetSize() && pos >= 0);
  
  int search_start = pos;
  int label_size = search_label.GetSize();
  bool found_label = false;
  
  // Move off the template we are on.
  pos += label_size;
  
  // Search until we find the complement or exit the memory.
  while (pos < search_genome.GetSize()) {
    
    // If we are within a label, rewind to the beginning of it and see if
    // it has the proper sub-label that we're looking for.
    
    if (m_inst_set->IsNop(search_genome[pos])) {
      // Find the start and end of the label we're in the middle of.
      
      int start_pos = pos;
      int end_pos = pos + 1;
      while (start_pos > search_start &&
             m_inst_set->IsNop( search_genome[start_pos - 1] )) {
        start_pos--;
      }
      while (end_pos < search_genome.GetSize() &&
             m_inst_set->IsNop( search_genome[end_pos] )) {
        end_pos++;
      }
      int test_size = end_pos - start_pos;
      
      // See if this label has the proper sub-label within it.
      int max_offset = test_size - label_size + 1;
      int offset = start_pos;
      for (offset = start_pos; offset < start_pos + max_offset; offset++) {
        
        // Test the number of matches for this offset.
        int matches;
        for (matches = 0; matches < label_size; matches++) {
          if (search_label[matches] !=
              m_inst_set->GetNopMod( search_genome[offset + matches] )) {
            break;
          }
        }
        
        // If we have found it, break out of this loop!
        if (matches == label_size) {
          found_label = true;
          break;
        }
      }
      
      // If we've found the complement label, set the position to the end of
      // the label we found it in, and break out.
      
      if (found_label == true) {
        // pos = end_pos;
        pos = label_size + offset;
        break;
      }
      
      // We haven't found it; jump pos to just after the current label being
      // checked.
      pos = end_pos;
    }
    
    // Jump up a block to the next possible point to find a label,
    pos += label_size;
  }
  
  // If the label was not found return a -1.
  if (found_label == false) pos = -1;
  
  return pos;
}

// Search backwards for search_label from _before_ position pos in the
// memory.  Return the first line _after_ the the found label.  It is okay
// to find search label's match inside another label.

int cHardware4Stack::FindLabel_Backward(const cCodeLabel & search_label,
                                        const cGenome & search_genome, int pos)
{
  assert (pos < search_genome.GetSize());
  
  int search_start = pos;
  int label_size = search_label.GetSize();
  bool found_label = false;
  
  // Move off the template we are on.
  pos -= label_size;
  
  // Search until we find the complement or exit the memory.
  while (pos >= 0) {
    // If we are within a label, rewind to the beginning of it and see if
    // it has the proper sub-label that we're looking for.
    
    if (m_inst_set->IsNop( search_genome[pos] )) {
      // Find the start and end of the label we're in the middle of.
      
      int start_pos = pos;
      int end_pos = pos + 1;
      while (start_pos > 0 && m_inst_set->IsNop(search_genome[start_pos - 1])) {
        start_pos--;
      }
      while (end_pos < search_start &&
             m_inst_set->IsNop(search_genome[end_pos])) {
        end_pos++;
      }
      int test_size = end_pos - start_pos;
      
      // See if this label has the proper sub-label within it.
      int max_offset = test_size - label_size + 1;
      for (int offset = start_pos; offset < start_pos + max_offset; offset++) {
        
        // Test the number of matches for this offset.
        int matches;
        for (matches = 0; matches < label_size; matches++) {
          if (search_label[matches] !=
              m_inst_set->GetNopMod(search_genome[offset + matches])) {
            break;
          }
        }
        
        // If we have found it, break out of this loop!
        if (matches == label_size) {
          found_label = true;
          break;
        }
      }
      
      // If we've found the complement label, set the position to the end of
      // the label we found it in, and break out.
      
      if (found_label == true) {
        pos = end_pos;
        break;
      }
      
      // We haven't found it; jump pos to just before the current label
      // being checked.
      pos = start_pos - 1;
    }
    
    // Jump up a block to the next possible point to find a label,
    pos -= label_size;
  }
  
  // If the label was not found return a -1.
  if (found_label == false) pos = -1;
  
  return pos;
}

// Search for 'in_label' anywhere in the hardware.
cHeadMultiMem cHardware4Stack::FindLabel(const cCodeLabel & in_label, int direction)
{
  assert (in_label.GetSize() > 0);
  
  // IDEALY:
  // Keep making jumps (in the proper direction) equal to the label
  // length.  If we are inside of a label, check its size, and see if
  // any of the sub-labels match properly.
  // FOR NOW:
  // Get something which works, no matter how inefficient!!!
  
  cHeadMultiMem temp_head(this);
  
  while (temp_head.InMemory()) {
    // IDEALY: Analyze the label we are in; see if the one we are looking
    // for could be a sub-label of it.  Skip past it if not.
    
    int i;
    for (i = 0; i < in_label.GetSize(); i++) {
      if (!m_inst_set->IsNop(temp_head.GetInst()) ||
          in_label[i] != m_inst_set->GetNopMod(temp_head.GetInst())) {
        break;
      }
    }
    if (i == GetLabel().GetSize()) {
      temp_head.AbsJump(i - 1);
      return temp_head;
    }
    
    temp_head.AbsJump(direction);     // IDEALY: MAKE LARGER JUMPS
  }
  
  temp_head.AbsSet(-1);
  return temp_head;
}

// @CAO: direction is not currently used; should be used to indicate the
// direction which the heads[nHardware::HEAD_IP] should progress through a creature.
cHeadMultiMem cHardware4Stack::FindFullLabel(const cCodeLabel & in_label)
{
  assert(in_label.GetSize() > 0); // Trying to find label of 0 size!
  
  cHeadMultiMem temp_head(this);
  
  while (temp_head.InMemory()) {
    // If we are not in a label, jump to the next checkpoint...
    if (m_inst_set->IsNop(temp_head.GetInst())) {
      temp_head.AbsJump(in_label.GetSize());
      continue;
    }
    
    // Otherwise, rewind to the begining of this label...
    
    while (!(temp_head.AtFront()) && m_inst_set->IsNop(temp_head.GetInst(-1)))
      temp_head.AbsJump(-1);
    
    // Calculate the size of the label being checked, and make sure they
    // are equal.
    
    int checked_size = 0;
    while (m_inst_set->IsNop(temp_head.GetInst(checked_size))) {
      checked_size++;
    }
    if (checked_size != in_label.GetSize()) {
      temp_head.AbsJump(checked_size + 1);
      continue;
    }
    
    // ...and do the comparison...
    
    int j;
    bool label_match = true;
    for (j = 0; j < in_label.GetSize(); j++) {
      if (!m_inst_set->IsNop(temp_head.GetInst(j)) ||
          in_label[j] != m_inst_set->GetNopMod(temp_head.GetInst(j))) {
        temp_head.AbsJump(in_label.GetSize() + 1);
        label_match = false;
        break;
      }
    }
    
    if (label_match) {
      // If we have found the label, return the position after it.
      temp_head.AbsJump(j - 1);
      return temp_head;
    }
    
    // We have not found the label... increment i.
    
    temp_head.AbsJump(in_label.GetSize() + 1);
  }
  
  // The label does not exist in this creature.
  
  temp_head.AbsSet(-1);
  return temp_head;
}

// This is the code run by the INFECTED organism.  Its function is to SPREAD infection.
bool cHardware4Stack::InjectParasite(cAvidaContext& ctx, double mut_multiplier)
{
  const int end_pos = GetHead(nHardware::HEAD_WRITE).GetPosition();
  const int mem_space_used = GetHead(nHardware::HEAD_WRITE).GetMemSpace();
  
  // Make sure the creature will still be above the minimum size,
  // TEMPORARY!  INJECTED CODE CAN 
  if (end_pos <= 0) {
    organism->Fault(FAULT_LOC_INJECT, FAULT_TYPE_ERROR, "inject: no code to inject");
    return false; // (inject fails)
  }
  
  if (end_pos < MIN_INJECT_SIZE) {
    GetMemory(mem_space_used)=cGenome(ConvertToInstruction(mem_space_used)); 
    organism->Fault(FAULT_LOC_INJECT, FAULT_TYPE_ERROR, "inject: new size too small");
    return false; // (inject fails)
  }
  
  GetMemory(mem_space_used).Resize(end_pos);
  
  cCPUMemory injected_code = GetMemory(mem_space_used);
  
  Inject_DoMutations(ctx, mut_multiplier, injected_code);
  
  int inject_signal = false;
  
  if (injected_code.GetSize() > 0) inject_signal = organism->InjectParasite(injected_code);
  
  //************* CALL GOES HERE ******************//
  // spin around randomly (caution: possible organism dizziness)
  //const int num_neighbors = organism->GetNeighborhoodSize();
  //for(unsigned int i=0; i<ctx.GetRandom().GetUInt(num_neighbors); i++)
  //  organism->Rotate(1);
  
  // If we don't have a host, stop here.
  //cOrganism * host_organism = organism->GetNeighbor();
  
  
  //if(host_organism!=NULL)
  //  {
  //    
  //  }
  
  //************** CALL ENDS HERE ******************//
  
  //reset the memory space which was injected
  GetMemory(mem_space_used)=cGenome(ConvertToInstruction(mem_space_used)); 
  
  for(int x=0; x<nHardware::NUM_HEADS; x++)
  {
    GetHead(x).Reset(IP().GetMemSpace(), this);
  }
  
  for(int x=0; x<nHardware4Stack::NUM_LOCAL_STACKS; x++)
  {
    Stack(x).Clear();
  }
  
  AdvanceIP() = false;
  
  return inject_signal;
}

//This is the code run by the TARGET of an injection.  This RECIEVES the infection.
bool cHardware4Stack::InjectHost(const cCodeLabel & in_label, const cGenome & inject_code)
{
  // Make sure the genome will be below max size after injection.
  
  // xxxTEMPORARYxxx - we should have this match injection templates.  For now it simply 
  
  // FIND THE FIRST EMPTY MEMORY SPACE
  int target_mem_space;
  for (target_mem_space = 0; target_mem_space < nHardware4Stack::NUM_MEMORY_SPACES; target_mem_space++)
  {
    if(isEmpty(target_mem_space))
    {
      break;
    }
  }
  
  if (target_mem_space == nHardware4Stack::NUM_MEMORY_SPACES)
  {
    return false;
  }
  
  assert(target_mem_space >=0 && target_mem_space < nHardware4Stack::NUM_MEMORY_SPACES);
  
  if(ForkThread()) {
    // Inject the new code
    cCPUMemory oldcode = GetMemory(target_mem_space);
    GetMemory(target_mem_space) = inject_code;
    GetMemory(target_mem_space).Resize(inject_code.GetSize() + oldcode.GetSize());
    
    // Copies previous instructions to the end of the injected code.
    // Is there a faster way to do this?? -law
    for(int x=0; x<oldcode.GetSize(); x++)
      GetMemory(target_mem_space)[inject_code.GetSize()+x] = oldcode[x];
    
    // Set instruction flags on the injected code
    for (int i = 0; i < inject_code.GetSize(); i++) {
      memory_array[target_mem_space].SetFlagInjected(i);
    }
    organism->GetPhenotype().IsModified() = true;
    
    // Adjust all of the heads to take into account the new mem size.
    
    cur_thread=GetNumThreads()-1;
    
    for(int i=0; i<cur_thread; i++) {
      for(int j=0; j<nHardware::NUM_HEADS; j++) {
        if(threads[i].heads[j].GetMemSpace()==target_mem_space)
          threads[i].heads[j].Jump(inject_code.GetSize());
      }
    }
    
    for (int i=0; i < nHardware::NUM_HEADS; i++) {    
      GetHead(i).Reset(target_mem_space, this);
    }
    for (int i=0; i < nHardware4Stack::NUM_LOCAL_STACKS; i++) {
      Stack(i).Clear();
    }
  }
  
  return true; // (inject succeeds!)
}


void cHardware4Stack::ReadInst(const int in_inst)
{
  if (m_inst_set->IsNop( cInstruction(in_inst) )) {
    GetReadLabel().AddNop(in_inst);
  } else {
    GetReadLabel().Clear();
  }
}

// This function looks at the current position in the info of a creature,
// and sets the next_label to be the sequence of nops which follows.  The
// instruction pointer is left on the last line of the label found.

void cHardware4Stack::ReadLabel(int max_size)
{
  int count = 0;
  cHeadMultiMem * inst_ptr = &( IP() );
  
  GetLabel().Clear();
  
  while (m_inst_set->IsNop(inst_ptr->GetNextInst()) &&
         (count < max_size)) {
    count++;
    inst_ptr->Advance();
    GetLabel().AddNop(m_inst_set->GetNopMod(inst_ptr->GetInst()));
    
    // If this is the first line of the template, mark it executed.
    if (GetLabel().GetSize() <=	m_world->GetConfig().MAX_LABEL_EXE_SIZE.Get()) {
      inst_ptr->SetFlagExecuted();
    }
  }
}


bool cHardware4Stack::ForkThread()
{
  const int num_threads = GetNumThreads();
  if (num_threads == m_world->GetConfig().MAX_CPU_THREADS.Get()) return false;
  
  // Make room for the new thread.
  threads.Resize(num_threads + 1);
  
  //IP().Advance();
  
  // Initialize the new thread to the same values as the current one.
  threads[num_threads] = threads[cur_thread]; 
  
  // Find the first free bit in thread_id_chart to determine the new
  // thread id.
  int new_id = 0;
  while ( (thread_id_chart >> new_id) & 1 == 1) new_id++;
  threads[num_threads].SetID(new_id);
  thread_id_chart |= (1 << new_id);
  
  return true;
}


int cHardware4Stack::TestParasite() const
{
  return IP().TestParasite();
}


bool cHardware4Stack::KillThread()
{
  // Make sure that there is always at least one thread...
  if (GetNumThreads() == 1) return false;
  
  // Note the current thread and set the current back one.
  const int kill_thread = cur_thread;
  ThreadPrev();
  
  // Turn off this bit in the thread_id_chart...
  thread_id_chart ^= 1 << threads[kill_thread].GetID();
  
  // Copy the last thread into the kill position
  const int last_thread = GetNumThreads() - 1;
  if (last_thread != kill_thread) {
    threads[kill_thread] = threads[last_thread];
  }
  
  // Kill the thread!
  threads.Resize(GetNumThreads() - 1);
  
  if (cur_thread > kill_thread) cur_thread--;
  
  return true;
}



////////////////////////////
//  Instruction Helpers...
////////////////////////////

inline int cHardware4Stack::FindModifiedStack(int default_stack)
{
  assert(default_stack < nHardware4Stack::NUM_STACKS);  // Stack ID too high.
  
  if (m_inst_set->IsNop(IP().GetNextInst())) {
    IP().Advance();
    default_stack = m_inst_set->GetNopMod(IP().GetInst());
    IP().SetFlagExecuted();
  }
  return default_stack;
}

inline int cHardware4Stack::FindModifiedHead(int default_head)
{
  assert(default_head < nHardware::NUM_HEADS); // Head ID too high.
  
  if (m_inst_set->IsNop(IP().GetNextInst())) {
    IP().Advance();    
    int nop_head = m_inst_set->GetNopMod(IP().GetInst());
    if (nop_head < nHardware::NUM_HEADS) default_head = nop_head;
    IP().SetFlagExecuted();
  }
  return default_head;
}

inline int cHardware4Stack::FindComplementStack(int base_stack)
{
  const int comp_stack = base_stack + 2;
  return comp_stack%nHardware4Stack::NUM_STACKS;
}

int cHardware4Stack::GetCopiedSize(const int parent_size, const int child_size)
{
  int copied_size = 0;
  const cCPUMemory& memory = GetMemory(m_cur_child);
  for (int i = 0; i < memory.GetSize(); i++) {
    if (memory.FlagCopied(i)) copied_size++;
	}
  return copied_size;
}


void cHardware4Stack::Inject_DoMutations(cAvidaContext& ctx, double mut_multiplier, cCPUMemory & injected_code)
{
  //sCPUStats & cpu_stats = organism->CPUStats();
  //cCPUMemory & child_genome = organism->ChildGenome();
  
  organism->GetPhenotype().SetDivType(mut_multiplier);
  
  // Divide Mutations
  if (organism->TestDivideMut(ctx)) {
    const unsigned int mut_line = ctx.GetRandom().GetUInt(injected_code.GetSize());
    injected_code[mut_line] = m_inst_set->GetRandomInst(ctx);
    //cpu_stats.mut_stats.divide_mut_count++;
  }
  
  // Divide Insertions
  if (organism->TestDivideIns(ctx) && injected_code.GetSize() < MAX_CREATURE_SIZE){
    const unsigned int mut_line = ctx.GetRandom().GetUInt(injected_code.GetSize() + 1);
    injected_code.Insert(mut_line, m_inst_set->GetRandomInst(ctx));
    //cpu_stats.mut_stats.divide_insert_mut_count++;
  }
  
  // Divide Deletions
  if (organism->TestDivideDel(ctx) && injected_code.GetSize() > MIN_CREATURE_SIZE){
    const unsigned int mut_line = ctx.GetRandom().GetUInt(injected_code.GetSize());
    injected_code.Remove(mut_line);
    //cpu_stats.mut_stats.divide_delete_mut_count++;
  }
  
  // Divide Mutations (per site)
  if(organism->GetDivMutProb() > 0){
    int num_mut = ctx.GetRandom().GetRandBinomial(injected_code.GetSize(), 
                                                       organism->GetDivMutProb() / mut_multiplier);
    // If we have lines to mutate...
    if( num_mut > 0 ){
      for (int i = 0; i < num_mut; i++) {
        int site = ctx.GetRandom().GetUInt(injected_code.GetSize());
        injected_code[site] = m_inst_set->GetRandomInst(ctx);
        //cpu_stats.mut_stats.div_mut_count++;
      }
    }
  }
  
  
  // Insert Mutations (per site)
  if(organism->GetInsMutProb() > 0){
    int num_mut = ctx.GetRandom().GetRandBinomial(injected_code.GetSize(),
                                                       organism->GetInsMutProb());
    // If would make creature to big, insert up to MAX_CREATURE_SIZE
    if( num_mut + injected_code.GetSize() > MAX_CREATURE_SIZE ){
      num_mut = MAX_CREATURE_SIZE - injected_code.GetSize();
    }
    // If we have lines to insert...
    if( num_mut > 0 ){
      // Build a list of the sites where mutations occured
      static int mut_sites[MAX_CREATURE_SIZE];
      for (int i = 0; i < num_mut; i++) {
        mut_sites[i] = ctx.GetRandom().GetUInt(injected_code.GetSize() + 1);
      }
      // Sort the list
      qsort( (void*)mut_sites, num_mut, sizeof(int), &IntCompareFunction );
      // Actually do the mutations (in reverse sort order)
      for(int i = num_mut-1; i >= 0; i--) {
        injected_code.Insert(mut_sites[i], m_inst_set->GetRandomInst(ctx));
        //cpu_stats.mut_stats.insert_mut_count++;
      }
    }
  }
  
  
  // Delete Mutations (per site)
  if( organism->GetDelMutProb() > 0 ){
    int num_mut = ctx.GetRandom().GetRandBinomial(injected_code.GetSize(),
                                                       organism->GetDelMutProb());
    // If would make creature too small, delete down to MIN_CREATURE_SIZE
    if (injected_code.GetSize() - num_mut < MIN_CREATURE_SIZE) {
      num_mut = injected_code.GetSize() - MIN_CREATURE_SIZE;
    }
    
    // If we have lines to delete...
    for (int i = 0; i < num_mut; i++) {
      int site = ctx.GetRandom().GetUInt(injected_code.GetSize());
      injected_code.Remove(site);
      //cpu_stats.mut_stats.delete_mut_count++;
    }
  }
  
  // Mutations in the parent's genome
  if (organism->GetParentMutProb() > 0) {
    for (int i = 0; i < GetMemory(0).GetSize(); i++) {
      if (organism->TestParentMut(ctx)) {
        GetMemory(0)[i] = m_inst_set->GetRandomInst(ctx);
        //cpu_stats.mut_stats.parent_mut_line_count++;
      }
    }
  }
  
}


bool cHardware4Stack::Divide_Main(cAvidaContext& ctx, int mem_space_used, double mut_multiplier)
{
  int write_head_pos = GetHead(nHardware::HEAD_WRITE).GetPosition();
  
  // We're going to disallow division calls from memory spaces other than zero 
  // for right now -law
  if(IP().GetMemSpace()!=0)
    return false;
  
  // Make sure this divide will produce a viable offspring.
  m_cur_child = mem_space_used;
  if(!Divide_CheckViable(ctx, GetMemory(IP().GetMemSpace()).GetSize(), write_head_pos)) 
    return false;
  
  // Since the divide will now succeed, set up the information to be sent
  // to the new organism
  cGenome & child_genome = organism->ChildGenome();
  GetMemory(mem_space_used).Resize(write_head_pos);
  child_genome = GetMemory(mem_space_used);
  
  // Handle Divide Mutations...
  Divide_DoMutations(ctx, mut_multiplier);
  
  // Many tests will require us to run the offspring through a test CPU;
  // this is, for example, to see if mutations need to be reverted or if
  // lineages need to be updated.
  Divide_TestFitnessMeasures(ctx);
  
#if INSTRUCTION_COSTS
  // reset first time instruction costs
  for (int i = 0; i < inst_ft_cost.GetSize(); i++) {
    inst_ft_cost[i] = m_inst_set->GetFTCost(cInstruction(i));
  }
#endif
  
  bool parent_alive = organism->ActivateDivide(ctx);
  
  //reset the memory of the memory space that has been divided off
  GetMemory(mem_space_used)=cGenome(ConvertToInstruction(mem_space_used)); 
  
  // 3 Division Methods:
  // 1) DIVIDE_METHOD_OFFSPRING - Create a child, leave parent state untouched.
  // 2) DIVIDE_METHOD_SPLIT - Create a child, completely reset state of parent.
  // 3) DIVIDE_METHOD_BIRTH - Create a child, reset state of parent's current thread.
  if(parent_alive && !(m_world->GetConfig().DIVIDE_METHOD.Get() == DIVIDE_METHOD_OFFSPRING))
  {
    
    if(m_world->GetConfig().DIVIDE_METHOD.Get() == DIVIDE_METHOD_SPLIT)
    {
      //this will wipe out all parasites on a divide.
      Reset();
      
    }
    else if(m_world->GetConfig().DIVIDE_METHOD.Get() == DIVIDE_METHOD_BIRTH)
    {
      //if this isn't the only thread, get rid of it!
      // ***this can cause a concurrency problem if we have 
      // multiprocessor support for single organisms...don't 
      // think that's happening anytime soon though -law ***
      if(!organism->GetPhenotype().IsModified() && GetNumThreads()>1 || 
         GetNumThreads()>2)
	    {
	      KillThread();
	    }
      
      //this will reset the current thread's heads and stacks.  It will 
      //not touch any other threads or memory spaces (ie: parasites)
      else
	    {
	      for(int x=0; x<nHardware::NUM_HEADS; x++)
        {
          GetHead(x).Reset(0, this);
        }
	      for(int x=0; x<nHardware4Stack::NUM_LOCAL_STACKS; x++)
        {
          Stack(x).Clear();
        }	  
	    }
    }
    AdvanceIP()=false;
  }
  
  return true;
}

cString cHardware4Stack::ConvertToInstruction(int mem_space_used)
{
  char c = mem_space_used + 97;  // 97 - ASCII for 'a'
  cString ret;
  ret += c;
  return ret;
}


//6
bool cHardware4Stack::Inst_ShiftR(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  int value = Stack(stack_used).Pop();
  value >>= 1;
  Stack(stack_used).Push(value);
  return true;
}

//7
bool cHardware4Stack::Inst_ShiftL(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  int value = Stack(stack_used).Pop();
  value <<= 1;
  Stack(stack_used).Push(value);
  return true;
}

//8
bool cHardware4Stack::Inst_Val_Nand(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  Stack(stack_used).Push(~(Stack(nHardware4Stack::STACK_BX).Top() & Stack(nHardware4Stack::STACK_CX).Top()));
  return true;
}

//9
bool cHardware4Stack::Inst_Val_Add(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  Stack(stack_used).Push(Stack(nHardware4Stack::STACK_BX).Top() + Stack(nHardware4Stack::STACK_CX).Top());
  return true;
}

//10
bool cHardware4Stack::Inst_Val_Sub(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  Stack(stack_used).Push(Stack(nHardware4Stack::STACK_BX).Top() - Stack(nHardware4Stack::STACK_CX).Top());
  return true;
}

//11
bool cHardware4Stack::Inst_Val_Mult(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  Stack(stack_used).Push(Stack(nHardware4Stack::STACK_BX).Top() * Stack(nHardware4Stack::STACK_CX).Top());
  return true;
}

//12
bool cHardware4Stack::Inst_Val_Div(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  if (Stack(nHardware4Stack::STACK_CX).Top() != 0) {
    if (0-INT_MAX > Stack(nHardware4Stack::STACK_BX).Top() && Stack(nHardware4Stack::STACK_CX).Top() == -1)
      organism->Fault(FAULT_LOC_MATH, FAULT_TYPE_ERROR, "div: Float exception");
    else
      Stack(stack_used).Push(Stack(nHardware4Stack::STACK_BX).Top() / Stack(nHardware4Stack::STACK_CX).Top());
  } else {
    organism->Fault(FAULT_LOC_MATH, FAULT_TYPE_ERROR, "div: dividing by 0");
    return false;
  }
  return true;
}

//13 
bool cHardware4Stack::Inst_SetMemory(cAvidaContext& ctx)
{
  int mem_space_used = FindModifiedStack(-1);
  
  if(mem_space_used==-1) {
    mem_space_used = FindFirstEmpty();
    if(mem_space_used==-1)
      return false;
  }
  
  GetHead(nHardware::HEAD_FLOW).Set(0, mem_space_used);
  return true;
}

//14
bool cHardware4Stack::Inst_Divide(cAvidaContext& ctx)
{
  int mem_space_used = GetHead(nHardware::HEAD_WRITE).GetMemSpace();
  int mut_multiplier = 1;
  
  return Divide_Main(ctx, mem_space_used, mut_multiplier);
}

//15
bool cHardware4Stack::Inst_HeadRead(cAvidaContext& ctx)
{
  const int head_id = FindModifiedHead(nHardware::HEAD_READ);
  GetHead(head_id).Adjust();
  sCPUStats & cpu_stats = organism->CPUStats();
  
  // Mutations only occur on the read, for the moment.
  int read_inst = 0;
  if (organism->TestCopyMut(ctx)) {
    read_inst = m_inst_set->GetRandomInst(ctx).GetOp();
    cpu_stats.mut_stats.copy_mut_count++;  // @CAO, hope this is good!
  } else {
    read_inst = GetHead(head_id).GetInst().GetOp();
  }
  Stack(nHardware4Stack::STACK_AX).Push(read_inst);
  ReadInst(read_inst);
  
  cpu_stats.mut_stats.copies_exec++;  // @CAO, this too..
  GetHead(head_id).Advance();
  return true;
}

//16
bool cHardware4Stack::Inst_HeadWrite(cAvidaContext& ctx)
{
  const int head_id = FindModifiedHead(nHardware::HEAD_WRITE);
  cHeadMultiMem & active_head = GetHead(head_id);
  int mem_space_used = active_head.GetMemSpace();
  
  //commented out for right now...
  if(active_head.GetPosition()>=GetMemory(mem_space_used).GetSize()-1)
  {
    GetMemory(mem_space_used).Resize(GetMemory(mem_space_used).GetSize()+1);
    GetMemory(mem_space_used).Copy(GetMemory(mem_space_used).GetSize()-1, GetMemory(mem_space_used).GetSize()-2);
  }
  
  active_head.Adjust();
  
  int value = Stack(nHardware4Stack::STACK_AX).Pop();
  if (value < 0 || value >= m_inst_set->GetSize()) value = 0;
  
  active_head.SetInst(cInstruction(value));
  active_head.SetFlagCopied();
  
  // Advance the head after write...
  active_head++;
  return true;
}

//??
bool cHardware4Stack::Inst_HeadCopy(cAvidaContext& ctx)
{
  // For the moment, this cannot be nop-modified.
  cHeadMultiMem & read_head = GetHead(nHardware::HEAD_READ);
  cHeadMultiMem & write_head = GetHead(nHardware::HEAD_WRITE);
  sCPUStats & cpu_stats = organism->CPUStats();
  
  read_head.Adjust();
  write_head.Adjust();
  
  // TriggerMutations(nMutation::TRIGGER_READ, read_head);
  
  // Do mutations.
  cInstruction read_inst = read_head.GetInst();
  if (organism->TestCopyMut(ctx)) {
    read_inst = m_inst_set->GetRandomInst(ctx);
    cpu_stats.mut_stats.copy_mut_count++; 
    write_head.SetFlagMutated();
    write_head.SetFlagCopyMut();
    //organism->GetPhenotype().IsMutated() = true;
  }
  ReadInst(read_inst.GetOp());
  
  cpu_stats.mut_stats.copies_exec++;
  
  write_head.SetInst(read_inst);
  write_head.SetFlagCopied();  // Set the copied flag...
  
  // TriggerMutations(nMutation::TRIGGER_WRITE, write_head);
  
  read_head.Advance();
  write_head.Advance();
  return true;
}

//17
bool cHardware4Stack::Inst_IfEqual(cAvidaContext& ctx)      // Execute next if bx == ?cx?
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_AX);
  const int stack_used2 = (stack_used+1)%nHardware4Stack::NUM_STACKS;
  if (Stack(stack_used).Top() != Stack(stack_used2).Top())  IP().Advance();
  return true;
}

//18
bool cHardware4Stack::Inst_IfNotEqual(cAvidaContext& ctx)     // Execute next if bx != ?cx?
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_AX);
  const int stack_used2 = (stack_used+1)%nHardware4Stack::NUM_STACKS;
  if (Stack(stack_used).Top() == Stack(stack_used2).Top())  IP().Advance();
  return true;
}

//19
bool cHardware4Stack::Inst_IfLess(cAvidaContext& ctx)       // Execute next if ?bx? < ?cx?
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_AX);
  const int stack_used2 = (stack_used+1)%nHardware4Stack::NUM_STACKS;
  if (Stack(stack_used).Top() >=  Stack(stack_used2).Top())  IP().Advance();
  return true;
}

//20
bool cHardware4Stack::Inst_IfGreater(cAvidaContext& ctx)       // Execute next if bx > ?cx?
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_AX);
  const int stack_used2 = (stack_used+1)%nHardware4Stack::NUM_STACKS;
  if (Stack(stack_used).Top() <= Stack(stack_used2).Top())  IP().Advance();
  return true;
}

//21
bool cHardware4Stack::Inst_HeadPush(cAvidaContext& ctx)
{
  const int head_used = FindModifiedHead(nHardware::HEAD_IP);
  Stack(nHardware4Stack::STACK_BX).Push(GetHead(head_used).GetPosition());
  //if (head_used == nHardware::HEAD_IP) {
  //  GetHead(head_used).Set(GetHead(nHardware::HEAD_FLOW));
  //  AdvanceIP() = false;
  //}
  return true;
}

//22
bool cHardware4Stack::Inst_HeadPop(cAvidaContext& ctx)
{
  const int head_used = FindModifiedHead(nHardware::HEAD_IP);
  GetHead(head_used).Set(Stack(nHardware4Stack::STACK_BX).Pop(), 
                         GetHead(head_used).GetMemSpace(), this);
  return true;
}

//23 
bool cHardware4Stack::Inst_HeadMove(cAvidaContext& ctx)
{
  const int head_used = FindModifiedHead(nHardware::HEAD_IP);
  if(head_used != nHardware::HEAD_FLOW)
  {
    GetHead(head_used).Set(GetHead(nHardware::HEAD_FLOW));
    if (head_used == nHardware::HEAD_IP) AdvanceIP() = false;
  }
  else
  {
    threads[cur_thread].heads[nHardware::HEAD_FLOW]++;
  }
  return true;
}

//24
bool cHardware4Stack::Inst_Search(cAvidaContext& ctx)
{
  ReadLabel();
  GetLabel().Rotate(2, nHardware4Stack::NUM_NOPS);
  cHeadMultiMem found_pos = FindLabel(0);
  if(found_pos.GetPosition()-IP().GetPosition()==0)
  {
    GetHead(nHardware::HEAD_FLOW).Set(IP().GetPosition()+1, IP().GetMemSpace(), this);
    // pushing zero into nHardware4Stack::STACK_AX on a missed search makes it difficult to create
    // a self-replicating organism.  -law
    //Stack(nHardware4Stack::STACK_AX).Push(0);
    Stack(nHardware4Stack::STACK_BX).Push(0);
  }
  else
  {
    int search_size = found_pos.GetPosition() - IP().GetPosition() + GetLabel().GetSize() + 1;
    Stack(nHardware4Stack::STACK_BX).Push(search_size);
    Stack(nHardware4Stack::STACK_AX).Push(GetLabel().GetSize());
    GetHead(nHardware::HEAD_FLOW).Set(found_pos);
  }  
  
  return true; 
}

//25
bool cHardware4Stack::Inst_PushNext(cAvidaContext& ctx) 
{
  int stack_used = FindModifiedStack(nHardware4Stack::STACK_AX);
  int successor = (stack_used+1)%nHardware4Stack::NUM_STACKS;
  Stack(successor).Push(Stack(stack_used).Pop());
  return true;
}

//26
bool cHardware4Stack::Inst_PushPrevious(cAvidaContext& ctx) 
{
  int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  int predecessor = (stack_used+nHardware4Stack::NUM_STACKS-1)%nHardware4Stack::NUM_STACKS;
  Stack(predecessor).Push(Stack(stack_used).Pop());
  return true;
}

//27
bool cHardware4Stack::Inst_PushComplement(cAvidaContext& ctx) 
{
  int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  int complement = FindComplementStack(stack_used);
  Stack(complement).Push(Stack(stack_used).Pop());
  return true;
}

//28
bool cHardware4Stack::Inst_ValDelete(cAvidaContext& ctx)
{
  int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  Stack(stack_used).Pop();
  return true;
}

//29
bool cHardware4Stack::Inst_ValCopy(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  Stack(stack_used).Push(Stack(stack_used).Top());
  return true;
}

//30
bool cHardware4Stack::Inst_ForkThread(cAvidaContext& ctx)
{
  if (!ForkThread()) 
    organism->Fault(FAULT_LOC_THREAD_FORK, FAULT_TYPE_FORK_TH);
  else
    IP().Advance();
  return true;
}

//31
bool cHardware4Stack::Inst_IfLabel(cAvidaContext& ctx)
{
  ReadLabel();
  GetLabel().Rotate(2, nHardware4Stack::NUM_NOPS);
  if (GetLabel() != GetReadLabel())  IP().Advance();
  return true;
}

//32
bool cHardware4Stack::Inst_Increment(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  int value = Stack(stack_used).Pop();
  Stack(stack_used).Push(++value);
  return true;
}

//33
bool cHardware4Stack::Inst_Decrement(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  int value = Stack(stack_used).Pop();
  Stack(stack_used).Push(--value);
  return true;
}

//34
bool cHardware4Stack::Inst_Mod(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  if (Stack(nHardware4Stack::STACK_CX).Top() != 0) {
    if(Stack(nHardware4Stack::STACK_CX).Top() == -1)
      Stack(stack_used).Push(0);
    else
      Stack(stack_used).Push(Stack(nHardware4Stack::STACK_BX).Top() % Stack(nHardware4Stack::STACK_CX).Top());
  } else {
    organism->Fault(FAULT_LOC_MATH, FAULT_TYPE_ERROR, "mod: modding by 0");
    return false;
  }
  return true;
}

//35
bool cHardware4Stack::Inst_KillThread(cAvidaContext& ctx)
{
  if (!KillThread()) organism->Fault(FAULT_LOC_THREAD_KILL, FAULT_TYPE_KILL_TH);
  else AdvanceIP() = false;
  return true;
}

//36
bool cHardware4Stack::Inst_IO(cAvidaContext& ctx)
{
  const int stack_used = FindModifiedStack(nHardware4Stack::STACK_BX);
  
  // Do the "put" component
  const int value_out = Stack(stack_used).Top();
  organism->DoOutput(ctx, value_out);  // Check for tasks compleated.
  
  // Do the "get" component
  const int value_in = organism->GetNextInput();
  Stack(stack_used).Push(value_in);
  organism->DoInput(value_in);
  return true;
}

int cHardware4Stack::FindFirstEmpty()
{
  bool OK=true;
  const int current_mem_space = IP().GetMemSpace();
  
  for(int x=1; x<nHardware4Stack::NUM_MEMORY_SPACES; x++)
  {
    OK=true;
    
    int index = (current_mem_space+x) % nHardware4Stack::NUM_MEMORY_SPACES;
    
    for(int y=0; y<GetMemory(index).GetSize() && OK; y++)
    {
      if(GetMemory(index)[y].GetOp() >= nHardware4Stack::NUM_NOPS)
        OK=false; 
    }
    for(int y=0; y<GetNumThreads() && OK; y++)
    {
      for(int z=0; z<nHardware::NUM_HEADS; z++)
	    {
	      if(threads[y].heads[z].GetMemSpace() == index)
          OK=false;
	    }
    }
    if(OK)
      return index;
  }
  return -1;
}

bool cHardware4Stack::isEmpty(int mem_space_used)
{
  for(int x=0; x<GetMemory(mem_space_used).GetSize(); x++)
  {
    if(GetMemory(mem_space_used)[x].GetOp() >= nHardware4Stack::NUM_NOPS)
      return false;
  }
  return true;
}

// The inject instruction can be used instead of a divide command, paired
// with an allocate.  Note that for an inject to work, one needs to have a
// broad range for sizes allowed to be allocated.
//
// This command will cut out from read-head to write-head.
// It will then look at the template that follows the command and inject it
// into the complement template found in a neighboring organism.

bool cHardware4Stack::Inst_Inject(cAvidaContext& ctx)
{
  double mut_multiplier = 1;
  
  return InjectParasite(ctx, mut_multiplier);
}



/*
 bool cHardware4Stack::Inst_InjectRand()
 {
   // Rotate to a random facing and then run the normal inject instruction
   const int num_neighbors = organism->GetNeighborhoodSize();
   organism->Rotate(ctx.GetRandom().GetUInt(num_neighbors));
   Inst_Inject();
   return true;
 }
 
 */
