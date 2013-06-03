/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 University of British Columbia, Vancouver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#ifndef PLC_OUTPUT_HELPER_H_
#define PLC_OUTPUT_HELPER_H_

#include <ns3/random-variable.h>
#include <ns3/spectrum-value.h>
#include <ns3/spectrum-model.h>
#include <ns3/plc-value.h>

namespace ns3 {

class PLC_OutputHelper
{
public:
	void PrintComplex(std::string name, Ptr<const PLC_ValueBase> value);
	void PrintAbsolute(std::string name, Ptr<const PLC_ValueBase> value);
	void PrintBode(std::string name, Ptr<const PLC_ValueBase> value);
	void PrintSeparatedBode(std::string name, Ptr<const PLC_ValueBase> value);
};

}

#endif /* PLC_OUTPUT_HELPER_H_ */
