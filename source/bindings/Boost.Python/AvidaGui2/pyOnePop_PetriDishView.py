# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/Users/kaben/Projects/Software/Avida/svn/avida2/trunk/source/bindings/Boost.Python/AvidaGui2/pyOnePop_PetriDishView.ui'
#
# Created: Thu Feb 17 15:14:30 2005
#      by: The PyQt User Interface Compiler (pyuic) 3.13
#
# WARNING! All changes made in this file will be lost!


from qt import *
from pyPetriDishCtrl import pyPetriDishCtrl
from pyGradientScaleCtrl import pyGradientScaleCtrl
from pyLiveControlsCtrl import pyLiveControlsCtrl

image0_data = \
  "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d" \
  "\x49\x48\x44\x52\x00\x00\x00\x20\x00\x00\x00\x20" \
  "\x08\x06\x00\x00\x00\x73\x7a\x7a\xf4\x00\x00\x08" \
  "\x3d\x49\x44\x41\x54\x78\x9c\xed\x96\x5d\x6c\x1c" \
  "\xd5\x15\xc7\xff\xe7\xde\x99\xd9\xd9\x4f\x7b\xbd" \
  "\xfe\x88\xd7\x1b\x6c\x12\x3b\x35\x04\x92\xb4\xe1" \
  "\x33\x40\x53\x48\x44\x09\x22\x04\xa2\xd2\xd2\x87" \
  "\x36\x85\xf6\xa5\x55\x11\xa5\x2d\x50\x21\x68\xd5" \
  "\x02\x2a\x0d\x11\x05\xaa\x3e\x20\x50\x24\xd4\x40" \
  "\x11\x85\x16\xa9\xa0\x50\xa0\x8a\x83\x02\x09\x58" \
  "\x75\xe4\x38\x21\x90\x38\x8e\xed\xac\xed\x6c\xe2" \
  "\xd8\xbb\xeb\x9d\xd9\x99\xd9\xb9\xf7\xf4\x81\x35" \
  "\x4a\x28\x15\x08\xa9\xea\x0b\x7f\xe9\xe8\xce\x95" \
  "\x66\x74\x7e\xe7\x7f\x8f\xee\x19\xe0\x0b\xfd\x9f" \
  "\x45\x9f\xe7\xa3\xde\xde\x5e\x23\x91\x48\xc4\xb4" \
  "\xd6\x36\x00\xb2\x2c\xcb\xb3\x6d\xdb\xed\xeb\xeb" \
  "\xab\xfd\x4f\x00\xd6\xad\xbb\x36\xbd\x62\xc5\x85" \
  "\x97\x5e\xbe\xfa\xca\x65\xcb\x57\x2c\xef\x11\x24" \
  "\xb3\xc2\xb4\x6d\xcb\x22\x10\x11\x54\xa8\x51\xab" \
  "\x05\x81\x0a\xfd\xc2\xc1\xa1\xfd\xc3\x83\x43\x83" \
  "\x07\x5f\xf9\xfb\xdf\x76\xed\xd8\xb1\x63\xea\x73" \
  "\x03\x34\x36\x36\xe2\xba\xeb\x36\x7c\xf9\xd6\x5b" \
  "\x6f\xbb\x69\x71\xf7\x79\x17\x47\xac\x08\x31\x98" \
  "\x98\x18\x60\x0d\x82\x60\x80\x08\x00\x18\x1a\x52" \
  "\x0a\x86\x20\x12\xc4\x86\x65\x51\x5c\x85\x4a\x14" \
  "\xa6\xf2\xfd\x8f\x3d\xf6\xf0\x9f\xb7\x6d\x7b\xba" \
  "\xaf\x52\xa9\xe8\xcf\x0c\xb0\x6c\xd9\xf2\x96\x2d" \
  "\x5b\x9e\xb8\xa3\x67\xf1\xb2\x4b\x49\x08\x26\x22" \
  "\x82\x24\x08\x22\x5b\x9a\x46\x3c\x54\x7e\x42\xa9" \
  "\xc0\x54\x50\x82\x34\x41\x08\xc1\x64\x18\x35\x53" \
  "\xd8\x2e\x42\xed\x19\x86\x88\x4a\xc9\x92\x84\x50" \
  "\x5a\xb1\x2a\x4c\x8f\xf7\xff\xf8\x87\xb7\xdc\xdf" \
  "\xd7\xb7\xe3\xe8\xa7\x02\x6c\xdc\x78\xd3\xd2\xdf" \
  "\xfd\xf6\x89\xfb\x85\x61\xa7\x49\x48\x68\x70\xbc" \
  "\x16\x78\x6d\xfc\xfe\x60\xc6\x35\x64\xcc\x4f\x35" \
  "\x72\x2d\xd0\x2c\xa5\x41\x2c\x04\xc0\x82\x01\x66" \
  "\xa5\x43\x92\x06\x21\x1a\x89\x50\x3c\x11\x55\xf1" \
  "\x64\x83\x6b\x9b\x56\x51\x6b\xe5\x29\x85\x59\x61" \
  "\x73\xf1\xf1\x47\x1f\x78\xe8\xa1\x07\x1f\xdc\x79" \
  "\x7a\x3e\x79\xfa\x66\xfd\x86\x1b\x7b\x37\x6f\xde" \
  "\xba\x45\x85\x68\x50\x8c\x98\x3b\x37\xd3\x63\x3c" \
  "\xf7\x44\x4f\xe2\xd7\x3f\x6d\x8c\xbe\xf8\xac\x55" \
  "\xb8\x72\x03\x47\x8d\x26\x81\x53\x2c\xec\x50\x52" \
  "\x08\x62\xd3\x8e\xc1\x94\x36\x4c\xc3\x26\x43\x46" \
  "\x69\x2e\x12\x60\x94\x4e\xca\x59\x67\xc6\x0a\x1c" \
  "\xa7\x81\x14\x47\x41\x66\x45\xd5\x28\xbc\x62\xed" \
  "\x55\x5f\x65\xe5\x8d\xec\x7e\xfb\xed\xf1\xff\x00" \
  "\x68\x5d\xb0\x20\xf2\xe4\x9f\x5e\xfc\xbd\x50\x91" \
  "\x66\xa7\x52\xe9\x28\xce\x16\xce\xa9\x55\xdc\x78" \
  "\x70\x72\x86\xe6\xb2\x9d\x5c\xee\xea\x66\x71\xf9" \
  "\x3a\x54\xa7\x4b\xe4\x55\x7c\x04\x9e\x0f\xb3\x25" \
  "\xc9\x56\x24\x02\x61\x48\x21\xa4\xc1\x92\x0c\x7a" \
  "\x3d\xb6\x97\x36\xd3\x56\xda\x21\x07\x49\x06\x51" \
  "\xee\x0e\x72\xe6\xec\xec\xa9\x16\x21\x0d\x82\xb2" \
  "\xe6\xd6\x5c\x73\xe5\x45\xbb\x76\xee\x78\x2d\x7f" \
  "\xec\x98\x0b\x00\xc6\x3c\xc0\x5d\xf7\xdc\x73\x75" \
  "\x63\x6b\x36\x37\x3b\x79\x6a\xa1\x5b\x2d\x9d\x65" \
  "\x99\x71\x86\x25\x41\xab\xaf\xd3\x20\x08\x41\x82" \
  "\x2d\x09\x8e\xe5\x5a\x95\xd6\x4c\x81\xd6\x30\x6c" \
  "\x0b\x44\x12\x44\x20\x22\x49\x02\x82\x95\xef\x51" \
  "\x67\xb5\x99\xcb\xb2\x4a\x29\xcf\x22\x8e\x98\x6c" \
  "\x99\x29\x2a\x17\x67\x73\x7e\x50\x8d\xc1\x68\xf9" \
  "\xe0\x27\x77\xfd\xe2\x5b\xbb\x6f\xb8\xfe\x8f\x67" \
  "\xf4\xc0\xbe\xb1\xf1\x47\x98\x53\xeb\xcb\xf9\xe3" \
  "\x5d\xa6\x88\x12\x91\x01\x21\x08\x44\x02\x00\x91" \
  "\x60\xb0\x15\x86\xa2\x3a\xe1\x90\x61\x48\xf8\x96" \
  "\xe2\x44\x36\xc3\x62\xc6\x21\xcd\x04\x8a\x0a\xa8" \
  "\x64\x82\xdf\x8d\xbf\x4f\x5c\x03\xa7\xc3\x28\x3a" \
  "\xfc\x66\x48\x92\x5a\x2a\x12\xcc\x1a\xb5\x9a\x03" \
  "\x19\x11\xf9\x44\x4b\x6a\xf7\xb9\x5d\x99\x9b\xcf" \
  "\x70\x80\x28\xd6\x59\x9e\x2c\x74\x46\x64\x82\x20" \
  "\x04\x88\x05\x84\x29\x19\x1a\x42\x10\x69\x10\x53" \
  "\x30\x57\x65\x37\xf0\xc8\x54\x04\x1d\x8b\xb2\xa9" \
  "\x98\xbc\xb2\x22\x12\x12\x5e\xb5\x0a\x95\xb1\xf4" \
  "\x1f\x8c\xe7\xc5\x34\x1f\xa7\xb4\xd9\x88\x47\xdd" \
  "\x3b\xd4\xcb\x4d\xfd\xc6\x6e\x0c\xa0\x43\x2f\xe0" \
  "\xeb\xdd\x8b\xb8\xc7\x6d\xcd\x7a\x65\xaf\x13\x40" \
  "\x14\x40\x75\x1e\xc0\x9c\xce\x9f\xe8\x48\x99\x0d" \
  "\x42\x6b\x01\x41\x02\x99\xdd\xdb\xa9\xe9\xb9\xa7" \
  "\xa4\x6e\xcb\x62\x6e\xd5\x55\x28\x7d\xed\x7a\x4e" \
  "\x0f\x0f\xa0\xc9\x4e\x70\xad\xa5\x83\xfd\xb6\x16" \
  "\xf6\x95\xa6\x4a\x8c\x35\xc2\x1a\x0b\xdb\x20\x4f" \
  "\xf8\x94\x2d\x26\xa0\x55\x94\x49\xd7\x28\x6d\x36" \
  "\xe0\xb0\x39\x86\x82\x3f\x85\x8a\xe1\xd0\x4c\x75" \
  "\x09\x6c\xab\x9b\x2a\x4e\x29\x27\x84\x88\x68\xad" \
  "\x3f\x02\x88\xe9\x9a\x9f\x86\x25\x20\x09\x44\x06" \
  "\x51\xfa\xf5\x97\x60\x8e\x1c\x06\x8d\x8f\xa2\xd0" \
  "\xbb\x82\xd2\x83\x7b\xd0\xfa\xcb\xdb\x05\xb3\x82" \
  "\xd7\x9e\xa3\x89\x67\x77\x85\x71\xaf\x0a\x3b\x12" \
  "\x27\xa3\xc9\x10\x35\xdb\x56\xb1\x63\xa3\x62\xeb" \
  "\xe1\x65\xba\x96\x59\x83\x62\x7b\xbb\x16\x29\x13" \
  "\x9b\x0a\x6b\xf5\x51\x7f\x09\x4d\x73\x91\x17\x19" \
  "\x39\x22\x08\x40\x23\xa9\xb5\x8e\x02\x28\x1a\x00" \
  "\x04\x80\x48\xb9\xe4\x9a\x0d\x51\x90\x94\x16\x13" \
  "\x6b\xe4\x2f\xbf\x86\xd0\xd9\x0b\xbb\x78\x8a\xbd" \
  "\x4b\xd7\x72\x6a\xcf\xeb\xe4\x58\x06\x4c\x2d\x51" \
  "\x5e\x7c\x0e\x9b\x86\x41\xe1\x5c\x48\x81\x13\x42" \
  "\xb9\x0a\x5e\x86\xa9\xe3\xf9\x27\x11\x79\xf1\x19" \
  "\x41\xa6\x01\xeb\xea\x1b\xd8\xb9\xe5\x36\x5e\xff" \
  "\xab\x3b\x29\x94\x16\xfc\x45\x4b\x28\xff\xfd\x35" \
  "\xac\x88\xc0\xb6\x6d\x0a\x21\x6c\xad\xb5\x31\xef" \
  "\x80\x71\xf8\x83\x23\xa1\x49\x31\x5e\x98\xeb\x42" \
  "\x7a\xe8\x1d\xa4\x0e\x0c\x40\xb5\xb6\xeb\xe0\x8a" \
  "\x35\xf0\x96\x9c\xc7\xc3\x4b\x73\xb0\xbe\xbd\x49" \
  "\xc7\xa7\xcb\x64\xb0\x05\xa1\x41\x45\xed\xb3\x96" \
  "\x0a\x61\xd5\x43\x26\xd1\xc5\xaa\x30\x29\x82\x58" \
  "\x14\x86\x34\x50\xcd\xb4\xc1\xca\x8f\xc1\x18\xfe" \
  "\x80\x64\xa8\x40\x23\x87\x80\x1f\xdc\xad\xdc\xa0" \
  "\x4a\x32\x93\x54\x5a\x6b\x02\x40\x1f\x35\xe1\xb1" \
  "\xc9\xd1\xc3\xd9\x05\x67\x77\x9b\x91\x49\x5e\xf4" \
  "\xd2\x36\xb2\x77\xfe\x83\xc8\x88\xd0\xf1\xaf\x6f" \
  "\xe0\xe9\xb5\xab\x71\x7b\xec\x11\xe1\x44\x1d\x64" \
  "\xdb\xb2\xb8\x6f\xf6\xbb\x6a\xe5\x5b\x2f\x53\x76" \
  "\x60\x0f\x6a\x6d\x39\x78\xe7\xaf\x44\x59\x2e\xe2" \
  "\x89\x07\x9e\xd2\xba\x5c\x04\x4f\x8e\x01\xa9\x34" \
  "\xa2\xa1\x8f\xb1\x1b\xbf\xa7\x8d\xc9\x71\x62\xa7" \
  "\x88\x92\xef\x09\x47\x0b\x71\xa4\xff\xdd\x31\x00" \
  "\xb5\x79\x00\x06\x10\xee\xec\x7b\xe5\xd5\x4b\x56" \
  "\xad\x5b\x97\x3f\x3a\x41\x03\xc9\x26\xea\x5e\x90" \
  "\x43\xcc\x73\x30\xb7\x62\x15\x1f\xb2\xa7\xc8\xa1" \
  "\x39\x28\x62\xb8\xce\x2c\x3a\xd0\x4a\x89\xe7\xb6" \
  "\x92\x18\xd8\x43\x51\xd3\x80\xbb\xfe\x66\x46\xef" \
  "\x4a\x12\xc2\x60\x34\x66\x98\x1a\x32\x04\x30\x0f" \
  "\x26\xc7\xe5\x81\xa5\x97\x71\xb3\x5e\x8f\xec\xa8" \
  "\x0d\x77\xa2\x40\x76\xb2\x81\x5f\x7d\xe1\x99\x57" \
  "\x01\x84\x00\xc2\x79\x80\xea\xbe\xbd\xef\xf4\xed" \
  "\x1b\xda\xf3\xaf\xee\x6c\xcf\xca\x63\x97\x5c\xcd" \
  "\xde\x37\x37\x21\x6e\xc6\xd0\xd0\x9c\xe5\xae\xd9" \
  "\x22\x7e\xe4\xde\xc0\xd3\xb2\x48\x92\x0d\x6d\x9a" \
  "\x3e\xe6\xc2\x40\xc8\x54\x0a\xa6\x52\xa8\xf4\x2c" \
  "\x65\xa5\x42\x30\x33\x40\x02\xcc\x35\x80\x85\x78" \
  "\x59\xbe\x8d\xf7\x66\xf6\x8a\x6b\xdd\x55\x30\xfc" \
  "\x76\xc4\xb4\xc5\x23\x23\x07\xc6\xdf\xd8\xfe\x97" \
  "\xbf\x02\xf0\x00\xe8\xf9\x8b\xc8\x00\xd0\x9a\x6e" \
  "\x6a\xbe\xe0\xde\x4d\x3f\x7f\xb2\x1d\x68\x6d\x5d" \
  "\x74\x16\x38\x91\x64\xce\x75\x21\x7b\x78\x08\x8d" \
  "\x63\x47\x61\xc7\xe3\x5c\xb9\x6c\x1d\x54\xba\x95" \
  "\x45\xa5\x44\x55\xcb\x62\x5d\x29\x13\x27\x1a\x20" \
  "\xe2\x09\x30\x48\xb1\x0e\x85\xef\x7b\x54\xf5\x5d" \
  "\x1e\x8d\x4d\x88\xb6\x48\x23\x69\x66\x9c\xc8\x17" \
  "\x51\x3e\x72\xaa\xfc\xf0\x96\x3b\xef\x18\x1b\x1d" \
  "\xfe\x27\x80\xe3\x00\xfc\xf9\x59\xa0\x01\x28\xaf" \
  "\xea\x7a\x7b\x87\x87\xf6\x9d\x7f\xee\xf2\x4b\xda" \
  "\xdb\xda\x52\x61\xa2\x81\xa0\x14\xb9\x4e\x85\x66" \
  "\x5b\xda\x68\xca\x0f\xe8\x88\xaf\xa9\x36\x72\x80" \
  "\xe8\xe9\xc7\x05\xbd\xb9\x5d\xe8\xfc\x11\x9a\x5c" \
  "\x74\x0e\xdc\x23\xef\xd3\x89\x91\x61\x39\x91\x1f" \
  "\xa3\xd9\x8a\x43\xb1\xa4\x2d\xce\x4e\xb4\x51\x52" \
  "\x46\x41\x55\x85\xf1\x43\xa3\x85\x2d\x9b\xef\xbe" \
  "\x6f\x74\x74\xf8\x4d\x00\xd3\x00\x9c\x8f\x4f\xc3" \
  "\x10\x40\xe8\xba\x4e\xf9\xad\xfd\xfd\x6f\x25\x32" \
  "\x99\xf6\xce\xf3\x57\xe6\x0c\x82\xe0\xaa\x4b\xa1" \
  "\x1f\xa0\xe4\x78\x98\x92\x49\x76\x4f\x16\xe8\x64" \
  "\xac\x09\x85\x4c\x0e\xf9\x64\x1b\xcf\x58\x71\xaa" \
  "\x0e\x0e\x90\x37\x3e\x8e\xda\xd4\x24\xe9\x5a\x8d" \
  "\x62\x6d\xcd\xb0\xa3\x12\x4e\xd9\x51\x6f\xbc\xb6" \
  "\xbd\xff\xc1\xdf\xfc\xec\xde\xe3\xc7\x27\xfb\xeb" \
  "\x95\x97\x3f\xba\x81\x71\xa6\x08\x40\x1c\x40\x06" \
  "\x40\x4b\xd7\xd9\xdd\x17\x6f\xfc\xc6\x77\x36\x7e" \
  "\x75\xf5\xb5\x17\x47\x22\x76\xd4\x29\x39\xe2\x44" \
  "\xc9\x07\x0a\x79\xa8\x52\x11\x22\x08\xa0\x2c\x0b" \
  "\x68\x5d\x80\xc8\xa1\xfd\x90\xcc\x20\x02\xf4\xc2" \
  "\x2e\x9d\xea\xe9\x0a\x0e\x1e\xec\xdf\xf7\xfc\x0b" \
  "\xdb\x5e\x78\x6f\xff\xe0\x2e\x00\x05\x00\xa7\x00" \
  "\xcc\xd5\x1d\xff\x44\x80\x79\x45\x00\x34\xd4\x23" \
  "\x1d\x8f\x27\xba\x56\x5e\x78\xd9\x05\x5f\x3a\xf7" \
  "\x2b\xcb\x52\x4d\x1d\x67\xb5\x2f\x5c\xbc\x20\x62" \
  "\x46\x2d\x30\x04\xb3\x26\x68\xa5\x7c\xa7\x54\x9b" \
  "\x1a\x39\x78\xe2\x64\x7e\x64\x72\x64\xf2\xe8\xd0" \
  "\xd0\xc1\xbd\x7b\xca\xe5\xd2\x08\x80\x12\x80\x62" \
  "\x7d\xad\xd6\x9b\xfe\x8c\x8a\xff\x9b\x04\x3e\x1c" \
  "\x18\x09\x00\xb1\xba\x33\x71\x00\xb6\x10\x22\x1e" \
  "\x8d\xc6\x92\x96\x15\xb1\x89\x04\x82\x5a\xe0\x57" \
  "\xdd\x8a\xa3\x94\x9a\xab\x27\xa9\x02\xa8\x00\x70" \
  "\xeb\x67\xed\x02\x50\x9f\x94\xe4\xb3\xfc\x15\x13" \
  "\x00\x13\x80\x55\x77\xc6\xac\xaf\xa2\x1e\x5c\x7f" \
  "\xa7\x86\x0f\xfb\xc8\xaf\x3f\xfb\x00\x82\x8f\x57" \
  "\xfc\x79\x00\x3e\x2e\x71\x5a\xe0\x34\x00\x5d\x0f" \
  "\xfe\xb4\xa4\x5f\xe8\x0b\x9d\xae\x7f\x03\x0c\xdb" \
  "\xe8\xdf\x8f\xa4\x44\x04\x00\x00\x00\x00\x49\x45" \
  "\x4e\x44\xae\x42\x60\x82"
image1_data = \
  "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d" \
  "\x49\x48\x44\x52\x00\x00\x00\x0f\x00\x00\x00\x0e" \
  "\x08\x06\x00\x00\x00\xf0\x8a\x46\xef\x00\x00\x01" \
  "\xd7\x49\x44\x41\x54\x78\x9c\x85\x92\xcd\x6a\x53" \
  "\x51\x14\x85\xbf\x9b\x5c\x09\x89\x69\xa3\xad\xb6" \
  "\x45\xc1\xe2\x4f\x1a\x9d\x28\x8a\x13\x91\x80\xc1" \
  "\xd0\xa9\xe0\x44\xa1\x82\x38\xa8\x93\x4e\xd4\xe2" \
  "\xd4\x17\x70\x20\x8a\x51\x21\xfa\x04\xfa\x06\x05" \
  "\x87\x22\xc4\x61\x41\x09\x0d\x04\x35\x85\x04\x93" \
  "\xe6\xaf\xf6\x26\xb9\xe7\x2c\x07\x6d\xd3\x34\x11" \
  "\xba\x60\x71\xe0\xec\xb3\xce\x62\xef\xbd\x90\xc4" \
  "\x20\x5b\xad\x96\x96\x9f\x3c\x55\xa5\x52\xd1\x70" \
  "\x6d\x98\x01\x06\xd0\x6e\xb7\x95\x79\x91\xe5\x88" \
  "\x3b\x85\x31\x96\x83\xe0\x48\x02\xa0\xd3\xe9\x28" \
  "\xf3\x32\xcb\x4c\x60\x8e\xdf\xb5\x3c\x53\x73\x51" \
  "\x42\xa1\xd0\xbe\xc7\xb1\x58\x8c\x54\x2a\x45\x38" \
  "\x1c\x76\xfa\x62\xdf\xf7\xf5\xe6\x55\x96\xe3\x9c" \
  "\xa3\x56\xde\xe2\xd8\xd4\x18\x96\x3d\x67\x21\xac" \
  "\x0c\x5e\x6f\x8b\x52\x23\xcf\xdd\x07\xb7\x48\x24" \
  "\x12\x8e\x23\x89\x77\xaf\xdf\x2b\xd6\x3d\xc5\x46" \
  "\xb9\x83\xac\xc0\xd9\x15\x81\x24\x8c\x84\x95\xc5" \
  "\xf3\x7d\xa6\xa7\xc7\x21\x5a\x63\xe1\xe1\x6d\x82" \
  "\x97\x2f\x5e\x55\x77\xfd\x30\xed\x3f\x86\xdd\x16" \
  "\xf6\x3b\x82\x95\xc5\x58\x8b\x91\xa5\xd6\xdc\xe4" \
  "\x68\x64\x92\x46\x6f\x9d\xc0\xcd\xf9\x1b\x14\x36" \
  "\x7e\xe0\x19\x7f\x48\xb8\x0d\xbb\xf3\xa1\x91\x30" \
  "\xb2\x08\x68\x79\x3d\xca\xbf\xea\x04\xa2\xd1\xa8" \
  "\xb3\xf4\x68\x81\x92\xf7\x9d\xae\x35\xfb\x5c\xa5" \
  "\xed\xd3\x58\xdb\x77\xb7\xb2\xf4\x7a\x06\x6f\xab" \
  "\xbb\x37\xed\xc2\x5a\x41\x99\xe7\x9f\x38\x3d\x76" \
  "\x9e\x4d\xbf\xc3\xdf\x6e\x13\x83\xb0\x56\x08\x70" \
  "\x02\x2e\xae\x13\xc2\xc8\x30\x39\x31\xce\x89\xb3" \
  "\x03\xab\x02\xc8\xe5\xbe\xe9\xe3\x87\x2f\x6c\x7a" \
  "\x75\xae\xa5\xcf\x10\x0c\x06\xfb\xb5\x66\xa3\x4d" \
  "\xee\xeb\x1a\x13\xe1\x0b\xb8\xee\x21\xae\xcf\x4f" \
  "\x32\x92\x9a\x95\x95\xcf\xba\x77\x67\x49\xd5\x6a" \
  "\x75\x24\x61\xf9\x7c\x5e\x8b\xf7\x9f\xe9\xf1\xe2" \
  "\x5b\x15\x8b\x45\xb9\xc3\xa9\x49\xa7\x53\x4e\x28" \
  "\xe4\x2a\x12\x89\x8c\x24\x2a\x1e\x8f\x3b\x33\x27" \
  "\xa3\xaa\x55\xea\xcc\xce\xce\x3a\x23\x62\x80\x64" \
  "\x32\xe9\xfc\xef\x1e\xe0\xd2\x95\x04\xeb\x3f\x6b" \
  "\x3b\x53\x3d\x20\xfc\xc3\x5c\x5d\x5d\x55\xa9\x54" \
  "\x92\x24\xfe\x01\x03\x3d\x5a\xfa\x32\x50\xe5\x56" \
  "\x00\x00\x00\x00\x49\x45\x4e\x44\xae\x42\x60\x82"

class pyOnePop_PetriDishView(QWidget):
  def __init__(self,parent = None,name = None,fl = 0):
    QWidget.__init__(self,parent,name,fl)

    self.image0 = QPixmap()
    self.image0.loadFromData(image0_data,"PNG")
    self.image1 = QPixmap()
    self.image1.loadFromData(image1_data,"PNG")
    if not name:
      self.setName("pyOnePop_PetriDishView")

    self.setEnabled(1)

    pyOnePop_PetriDishViewLayout = QVBoxLayout(self,0,6,"pyOnePop_PetriDishViewLayout")
    pyOnePop_PetriDishViewLayout.setResizeMode(QLayout.Minimum)

    layout179 = QHBoxLayout(None,0,6,"layout179")

    self.pixmapLabel1 = QLabel(self,"pixmapLabel1")
    self.pixmapLabel1.setSizePolicy(QSizePolicy(0,0,0,0,self.pixmapLabel1.sizePolicy().hasHeightForWidth()))
    self.pixmapLabel1.setPixmap(self.image0)
    self.pixmapLabel1.setScaledContents(1)
    layout179.addWidget(self.pixmapLabel1)

    self.textLabel3 = QLabel(self,"textLabel3")
    self.textLabel3.setSizePolicy(QSizePolicy(3,5,0,0,self.textLabel3.sizePolicy().hasHeightForWidth()))
    textLabel3_font = QFont(self.textLabel3.font())
    textLabel3_font.setPointSize(11)
    self.textLabel3.setFont(textLabel3_font)
    layout179.addWidget(self.textLabel3)

    layout178 = QVBoxLayout(None,0,6,"layout178")
    spacer126 = QSpacerItem(1,1,QSizePolicy.Minimum,QSizePolicy.Minimum)
    layout178.addItem(spacer126)

    self.toolButton31_2 = QToolButton(self,"toolButton31_2")
    toolButton31_2_font = QFont(self.toolButton31_2.font())
    toolButton31_2_font.setPointSize(10)
    self.toolButton31_2.setFont(toolButton31_2_font)
    self.toolButton31_2.setIconSet(QIconSet(self.image1))
    layout178.addWidget(self.toolButton31_2)
    spacer126_2 = QSpacerItem(1,1,QSizePolicy.Minimum,QSizePolicy.Minimum)
    layout178.addItem(spacer126_2)
    layout179.addLayout(layout178)
    pyOnePop_PetriDishViewLayout.addLayout(layout179)

    layout91 = QHBoxLayout(None,0,6,"layout91")

    self.m_petri_dish_ctrl = pyPetriDishCtrl(self,"m_petri_dish_ctrl")
    self.m_petri_dish_ctrl.setSizePolicy(QSizePolicy(3,3,5,0,self.m_petri_dish_ctrl.sizePolicy().hasHeightForWidth()))
    layout91.addWidget(self.m_petri_dish_ctrl)

    self.m_gradient_scale_ctrl = pyGradientScaleCtrl(self,"m_gradient_scale_ctrl")
    self.m_gradient_scale_ctrl.setSizePolicy(QSizePolicy(0,1,1,0,self.m_gradient_scale_ctrl.sizePolicy().hasHeightForWidth()))
    self.m_gradient_scale_ctrl.setMinimumSize(QSize(50,50))
    self.m_gradient_scale_ctrl.setBackgroundMode(pyGradientScaleCtrl.PaletteDark)
    layout91.addWidget(self.m_gradient_scale_ctrl)
    pyOnePop_PetriDishViewLayout.addLayout(layout91)

    layout1 = QHBoxLayout(None,0,6,"layout1")

    self.textLabel11 = QLabel(self,"textLabel11")
    self.textLabel11.setSizePolicy(QSizePolicy(0,1,0,0,self.textLabel11.sizePolicy().hasHeightForWidth()))
    layout1.addWidget(self.textLabel11)

    self.m_update_label = QLabel(self,"m_update_label")
    self.m_update_label.setSizePolicy(QSizePolicy(0,1,0,0,self.m_update_label.sizePolicy().hasHeightForWidth()))
    layout1.addWidget(self.m_update_label)

    self.m_mode_combobox = QComboBox(0,self,"m_mode_combobox")
    self.m_mode_combobox.setSizePolicy(QSizePolicy(3,0,0,0,self.m_mode_combobox.sizePolicy().hasHeightForWidth()))
    m_mode_combobox_font = QFont(self.m_mode_combobox.font())
    m_mode_combobox_font.setPointSize(11)
    self.m_mode_combobox.setFont(m_mode_combobox_font)
    layout1.addWidget(self.m_mode_combobox)

    self.textLabel10 = QLabel(self,"textLabel10")
    self.textLabel10.setSizePolicy(QSizePolicy(0,1,0,0,self.textLabel10.sizePolicy().hasHeightForWidth()))
    layout1.addWidget(self.textLabel10)

    self.m_zoom_spinbox = QSpinBox(self,"m_zoom_spinbox")
    self.m_zoom_spinbox.setSizePolicy(QSizePolicy(0,0,0,0,self.m_zoom_spinbox.sizePolicy().hasHeightForWidth()))
    layout1.addWidget(self.m_zoom_spinbox)
    pyOnePop_PetriDishViewLayout.addLayout(layout1)

    layout229 = QHBoxLayout(None,0,6,"layout229")
    spacer169_2 = QSpacerItem(10,10,QSizePolicy.MinimumExpanding,QSizePolicy.Minimum)
    layout229.addItem(spacer169_2)

    self.m_live_controls_ctrl = pyLiveControlsCtrl(self,"m_live_controls_ctrl")
    self.m_live_controls_ctrl.setSizePolicy(QSizePolicy(0,0,0,0,self.m_live_controls_ctrl.sizePolicy().hasHeightForWidth()))
    self.m_live_controls_ctrl.setMinimumSize(QSize(0,50))
    layout229.addWidget(self.m_live_controls_ctrl)
    spacer169 = QSpacerItem(10,10,QSizePolicy.MinimumExpanding,QSizePolicy.Minimum)
    layout229.addItem(spacer169)
    pyOnePop_PetriDishViewLayout.addLayout(layout229)

    self.languageChange()

    self.resize(QSize(265,191).expandedTo(self.minimumSizeHint()))
    self.clearWState(Qt.WState_Polished)


  def languageChange(self):
    self.setCaption(self.__tr("pyOnePop_PetriDishView"))
    self.textLabel3.setText(self.__tr("[population]"))
    self.toolButton31_2.setText(QString.null)
    self.textLabel11.setText(self.__tr("<font size=\"-1\"><p align=\"right\">Update:</p></font>"))
    self.m_update_label.setText(self.__tr("<font size=\"-1\">10000</font>"))
    self.m_mode_combobox.clear()
    self.m_mode_combobox.insertItem(self.__tr("Merit"))
    self.textLabel10.setText(self.__tr("<font size=\"-1\"><p align=\"right\">Zoom:</p></font>"))


  def __tr(self,s,c = None):
    return qApp.translate("pyOnePop_PetriDishView",s,c)
