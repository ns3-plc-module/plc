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

#include <ns3/simulator.h>
#include "plc-time.h"
#include "plc-phy.h"
#include "plc-simulator-impl.h"

namespace ns3 {

double PLC_Time::g_mainsFreq = 50;
double PLC_Time::g_period_s = 0.02;
double PLC_Time::g_resolution_s = 100e-6;
Time PLC_Time::g_period = MilliSeconds(20);
size_t PLC_Time::g_timeslots = 200;
Time PLC_Time::g_resolution = MicroSeconds(100);

void
PLC_Time::SetTimeModel(double mainsFreq, Time tSymbol)
{
	g_mainsFreq = mainsFreq;
	g_period_s = 1 / mainsFreq;
	g_timeslots = ceil(g_period_s / tSymbol.GetSeconds());

	g_period = Time::FromDouble(g_period_s, Time::S);
	NS_ASSERT(g_period > 0);

	g_resolution_s = tSymbol.GetDouble();

	Ptr<PLC_SimulatorImpl> simImpl = CreateObject<PLC_SimulatorImpl> ();
	Simulator::SetImplementation(simImpl);
	PLC_Phy::SetSymbolDuration(tSymbol);
}

void
PLC_Time::SetTimeModel(double mainsFreq, size_t timeslots, Time tSymbol)
{
	g_mainsFreq = mainsFreq;
	g_timeslots = timeslots;

	g_period_s = 1 / mainsFreq;
	g_period = Time::FromDouble(g_period_s, Time::S);
	NS_ASSERT(g_period > 0);

	g_resolution_s = g_period_s / timeslots;
	Time g_resolution = Time::FromDouble(g_resolution_s, Time::S);
	NS_ASSERT(tSymbol >= g_resolution);

	Ptr<PLC_SimulatorImpl> simImpl = CreateObject<PLC_SimulatorImpl> ();
	Simulator::SetImplementation(simImpl);
	PLC_Phy::SetSymbolDuration(tSymbol);
}

Timeslot
PLC_Time::GetTimeslot(Time t)
{
	Timeslot ret =  (Timeslot) floor(fmod(t.GetSeconds(), g_period_s) / g_resolution_s);
	NS_ASSERT(ret < g_timeslots);
	return ret;
}

}
