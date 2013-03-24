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

#ifndef PLC_TIME_H_
#define PLC_TIME_H_

#include <ns3/nstime.h>
#include "plc-defs.h"

namespace ns3 {

class PLC_Time
{
public:

	static void SetTimeModel(double mainsFreq, Time tSymbol);
	static void SetTimeModel(double mainsFreq, size_t timeslots, Time tSymbol);
	static Time GetMainsPeriod(void) { return g_period; }
	static size_t GetNumTimeslots(void) { return g_timeslots; }
	static Timeslot GetTimeslot(Time t);
	static double GetResolutionS(void) { return g_resolution_s; }
	static double GetPeriodS(void) { return g_period_s; }

private:
	static double g_mainsFreq;
	static size_t g_timeslots;
	static Time g_period;
	static Time g_resolution;
	static double g_resolution_s;
	static double g_period_s;
};

}

#endif /* PLC_TIME_H_ */
