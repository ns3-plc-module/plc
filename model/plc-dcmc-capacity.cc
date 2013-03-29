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

#include <ns3/fatal-error.h>
#include <math.h>
#include "plc-dcmc-capacity.h"

namespace ns3 {

SpectrumValue GetCapacity(const SpectrumValue& SINR, Modulation mod, short cardinality)
{
	SpectrumValue capacityPerHertz(SINR.GetSpectrumModel());

	const double *cap;
	if (mod == QAM)
	{
		switch (cardinality)
		{
			case 2:
			{
				cap = qamCap[0];
				break;
			}
			case 4:
			{
				cap = qamCap[1];
				break;
			}
			case 8:
			{
				cap = qamCap[2];
				break;
			}
			case 16:
			{
				cap = qamCap[3];
				break;
			}
			case 32:
			{
				cap = qamCap[4];
				break;
			}
			case 64:
			{
				cap = qamCap[5];
				break;
			}
			default:
			{
				NS_FATAL_ERROR("QAM" << cardinality << " not supported");
				break;
			}
		}
	}
	else if (mod == PSK)
	{
		switch (cardinality)
		{
			case 16:
			{
				cap = pskCap[0];
				break;
			}
			case 32:
			{
				cap = pskCap[1];
				break;
			}
			case 64:
			{
				cap = pskCap[2];
				break;
			}
			default:
			{
				NS_FATAL_ERROR("PSK" << cardinality << " not supported");
				break;
			}
		}
	}
	else
	{
		NS_FATAL_ERROR("Unsupported modulation type");
	}

	Values::const_iterator sinr_it = SINR.ConstValuesBegin();
	Values::iterator cit = capacityPerHertz.ValuesBegin();
	while (sinr_it != SINR.ConstValuesEnd() && cit != capacityPerHertz.ValuesEnd())
	{
		// subchannel sinr
		double sc_sinr = *sinr_it;
		if (sc_sinr < -10)
		{
			*cit = log2(1+pow(10, sc_sinr/10));
		}
		else if (sc_sinr >= 40)
		{
			*cit = log2(cardinality);
		}
		else
		{
			short x1 = floor(sc_sinr+10);
			short x2 = ceil(sc_sinr+10);

			if (x1 == x2)
			{
				*cit = cap[x1];
			}
			else
			{
				double y1 = cap[x1];
				double y2 = cap[x2];

				// linear interpolation
				*cit = y1 + (sc_sinr-x1+10)*((y2-y1)/(x2-x1));
			}
		}
		++sinr_it;
		++cit;
	}

	return capacityPerHertz;
}

} // namespace ns3
