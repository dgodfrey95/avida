/*
 *  viewer-core/cMap.h
 *  Avida
 *
 *  Created by Charles on 7-9-07
 *  Copyright 1999-2011 Michigan State University. All rights reserved.
 *  http://avida.devosoft.org/
 *
 *
 *  This file is part of Avida.
 *
 *  Avida is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 *  Avida is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License along with Avida.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors: David M. Bryson <david@programerror.com>, Charles Ofria <ofria@msu.edu>
 */

#ifndef AvidaCoreViewMap_h
#define AvidaCoreViewMap_h

#include "cRWLock.h"
#include "cString.h"
#include "tArray.h"

class cPopulation;
class cWorld;


namespace Avida {
  namespace CoreView {
    
    // Map Mode/Type Enumerations
    // --------------------------------------------------------------------------------------------------------------  
    
    enum eMapGridViewType { MAP_GRID_VIEW_COLOR = 0x1, MAP_GRID_VIEW_SYMBOLS = 0x2, MAP_GRID_VIEW_TAGS = 0x4 };

    
    // DiscreteScale Base Clase Definition
    // --------------------------------------------------------------------------------------------------------------  
    
    class DiscreteScale
    {
    public:
      struct Entry {
        int index;
        cString label;
      };
      
    public:
      virtual ~DiscreteScale() = 0;
      
      virtual int GetScaleRange() const = 0;
      virtual int GetNumLabeledEntries() const = 0;
      virtual Entry GetEntry(int index) const = 0;
    };
    
    
    // MapMode Base Class Definition
    // --------------------------------------------------------------------------------------------------------------  
    
    class MapMode
    {
    public:
      virtual ~MapMode() = 0;
      
      virtual const cString& GetName() const = 0;
      virtual const tArray<int>& GetGridValues() const = 0;
      virtual const tArray<int>& GetValueCounts() const = 0;
      
      virtual const DiscreteScale& GetScale() const = 0;
      
      virtual int GetSupportedTypes() const = 0;
      
      virtual void Update(cPopulation& pop) = 0;
    };
    
    
    // Map Definition
    // --------------------------------------------------------------------------------------------------------------  
    
    class cMap
    {
    protected:
      int m_width;
      int m_height;
      int m_num_viewer_colors;
      
      tArray<MapMode*> m_view_modes;  // List of view modes...
      int m_color_mode;      // Current map color mode (index into m_view_modes, -1 = off)
      int m_symbol_mode;     // Current map symbol mode (index into m_view_modes, -1 = off)
      int m_tag_mode;        // Current map tag mode (index into m_view_modes, -1 = off)
      
      cRWLock m_rw_lock;
      
      
    public:
      cMap(cWorld* world);
      ~cMap();
      
      
      inline int GetWidth() const { return m_width; }
      inline int GetHeight() const { return m_height; }
      
      
      inline int GetColorMode() const { return m_color_mode; }
      inline int GetSymbolMode() const { return m_symbol_mode; }
      inline int GetTagMode() const { return m_tag_mode; }
      
      
      inline const tArray<int>& GetColors() const { return m_view_modes[m_color_mode]->GetGridValues(); }
      inline const tArray<int>& GetSymbols() const { return m_view_modes[m_symbol_mode]->GetGridValues(); }
      inline const tArray<int>& GetTags() const { return m_view_modes[m_tag_mode]->GetGridValues(); }
      
      inline const tArray<int>& GetColorCounts() const { return m_view_modes[m_color_mode]->GetValueCounts(); }
      inline const tArray<int>& GetSymbolCounts() const { return m_view_modes[m_symbol_mode]->GetValueCounts(); }
      inline const tArray<int>& GetTagCounts() const { return m_view_modes[m_tag_mode]->GetValueCounts(); }
      
      inline const DiscreteScale& GetColorScale() const { return m_view_modes[m_color_mode]->GetScale(); }
      inline const DiscreteScale& GetSymbolScale() const { return m_view_modes[m_symbol_mode]->GetScale(); }
      inline const DiscreteScale& GetTagScale() const { return m_view_modes[m_tag_mode]->GetScale(); }
      
      
      inline int GetNumModes() const { return m_view_modes.GetSize(); }
      inline const cString& GetModeName(int idx) const { return m_view_modes[idx]->GetName(); }
      inline int GetModeSupportedTypes(int idx) const { return m_view_modes[idx]->GetSupportedTypes(); }
      
      void SetMode(int mode);
      inline void SetNumViewerColors(int num_colors) { m_num_viewer_colors = num_colors; }
      
      
      inline void Retain() { m_rw_lock.ReadLock(); }
      inline void Release() { m_rw_lock.ReadUnlock(); }
      
      
      // Core Viewer Internal Methods
      void UpdateMaps(cPopulation& pop);
      
      
    protected:
      void updateMap(cPopulation& pop, int map_id);
    };
    
  };
};




#endif
