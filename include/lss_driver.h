/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
File created by Leonid Tochinski

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __lss_driver_h__
#define __lss_driver_h__

#include "can.h"

UNS8 baudrate_valid(UNS32 table_index);
void baudrate_set(UNS8 table_index);

#endif
