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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 * Modified by: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#ifndef PLC_SIMULATOR_IMPL_H_
#define PLC_SIMULATOR_IMPL_H_

#include "ns3/simulator-impl.h"
#include "ns3/scheduler.h"
#include "ns3/event-impl.h"

#include "ns3/ptr.h"

#include <list>

namespace ns3 {

class PLC_SimulatorImpl : public SimulatorImpl
{
public:
	static TypeId GetTypeId (void);

	PLC_SimulatorImpl ();
	~PLC_SimulatorImpl ();

	// Added to support simulation time granularity other than ns3::Time::Unit
	void SetGranularity(Time granularity);
	Time GetGranularity(void) { return m_granularity; }
	uint64_t GetQuantizedTicks(Time time);

	virtual void Destroy ();
	virtual bool IsFinished (void) const;
	virtual Time Next (void) const;
	virtual void Stop (void);
	virtual void Stop (Time const &time);
	virtual EventId Schedule (Time const &time, EventImpl *event);
	virtual void ScheduleWithContext (uint32_t context, Time const &time, EventImpl *event);
	virtual EventId ScheduleNow (EventImpl *event);
	virtual EventId ScheduleDestroy (EventImpl *event);
	virtual void Remove (const EventId &ev);
	virtual void Cancel (const EventId &ev);
	virtual bool IsExpired (const EventId &ev) const;
	virtual void Run (void);
	virtual void RunOneEvent (void);
	virtual Time Now (void) const;
	virtual Time GetDelayLeft (const EventId &id) const;
	virtual Time GetMaximumSimulationTime (void) const;
	virtual void SetScheduler (ObjectFactory schedulerFactory);
	virtual uint32_t GetSystemId (void) const;
	virtual uint32_t GetContext (void) const;

private:
	virtual void DoDispose (void);
	void ProcessOneEvent (void);
	uint64_t NextTs (void) const;
	typedef std::list<EventId> DestroyEvents;

	DestroyEvents m_destroyEvents;
	bool m_stop;
	Ptr<Scheduler> m_events;
	uint32_t m_uid;
	uint32_t m_currentUid;
	uint64_t m_currentTs;
	uint32_t m_currentContext;
	// number of events that have been inserted but not yet scheduled,
	// not counting the "destroy" events; this is used for validation
	int m_unscheduledEvents;

	Time 		m_granularity;
	int64_t 	m_tick_ts;
};

} // namespace ns3

#endif /* PLC_SIMULATOR_IMPL_H_ */
