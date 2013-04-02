/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 University of British Columbia, Vancouver
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

#include <ns3/abort.h>
#include "plc-defs.h"

namespace ns3 {

PLC_Mutex g_log_mutex;
PLC_Mutex g_smartpointer_mutex;

std::ostream&
operator<<(std::ostream& os, ModulationAndCodingType type)
{
	switch (type)
	{
	case (BPSK_1_4):
		{
			os << "BPSK_1_4";
			break;
		}
	case (BPSK_1_2):
		{
			os << "BPSK_1_2";
			break;
		}
	case (QPSK_1_2):
		{
			os << "QPSK_1_2";
			break;
		}
	case (QAM16_1_2):
		{
			os << "QAM16_1_2";
			break;
		}
	case (QAM64_16_21):
		{
			os << "QAM64_16_21";
			break;
		}
	case (BPSK_RATELESS):
		{
			os << "BPSK_RATELESS";
			break;
		}
	case (QAM4_RATELESS):
		{
			os << "QAM4_RATELESS";
			break;
		}
	case (QAM16_RATELESS):
		{
			os << "QAM16_RATELESS";
			break;
		}
	case (QAM32_RATELESS):
		{
			os << "QAM32_RATELESS";
			break;
		}
	case (QAM64_RATELESS):
		{
			os << "QAM64_RATELESS";
			break;
		}
	default:
		{
			os << "INVALID";
			break;
		}
	}
	return os;
}

double
GetCodeRate (ModulationAndCodingType mcs)
{
	NS_ASSERT_MSG (mcs < BPSK_RATELESS, "Rateless codes do not have fixed code rate");

	double code_rate;
	switch (mcs)
	{
		case BPSK_1_4:
		{
			code_rate = 0.25;
			break;
		}
		case BPSK_1_2:
		{
			code_rate = 0.5;
			break;
		}
		case QPSK_1_2:
		{
			code_rate = 0.5;
			break;
		}

		case QAM16_1_2:
		{
			code_rate = 0.5;
			break;
		}

		case QAM64_16_21:
		{
			code_rate = (double) 16/21;
			break;
		}

		default:
		{
			NS_ABORT_MSG("Modulation and Coding Scheme " << mcs << " not supported");
			break;
		}
	}

	return code_rate;
}

size_t
GetBitsPerSymbol (ModulationAndCodingType mcs)
{
	size_t bits;
	switch(mcs)
	{
		case BPSK_1_4:
		case BPSK_1_2:
		case BPSK_RATELESS:
		{
			bits = 1;
			break;
		}
		case QPSK_1_2:
		case QAM4_RATELESS:
		{
			bits = 2;
			break;
		}
		case QAM16_1_2:
		case QAM16_RATELESS:
		{
			bits = 4;
			break;
		}
		case QAM32_RATELESS:
		{
			bits = 5;
			break;
		}
		case QAM64_16_21:
		case QAM64_RATELESS:
		{
			bits = 6;
			break;
		}
		default:
		{
			NS_ABORT_MSG("Unsupported Modulation and Coding Type");
			bits = 0;
			break;
		}
	}
	return bits;
}

}
