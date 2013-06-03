/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012
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

#ifndef PLC_ThreadDispatcher_H_
#define PLC_ThreadDispatcher_H_

#include <vector>
#include <ns3/system-thread.h>

namespace ns3 {

class PLC_ThreadDispatcher
{
	PLC_ThreadDispatcher ();

	void EnableMultithreadind (void) { m_multithreading_enabled = true; }
	void DisableMultithreading (void) { m_multithreading_enabled = false; }
	bool MultithreadingEnabled (void) { return m_multithreading_enabled; }

	void SetMaxThreads (size_t max) { m_max_threads = max; }
	size_t GetMaxThreads (void) { return m_max_threads; }

	void Run (std::vector<Callback<void> > callbacks);

private:
	bool m_multithreading_enabled;
	size_t m_max_threads;
	std::vector<Ptr<SystemThread> > m_threads;
};

}

#endif /* PLC_ThreadDispatcher_H_ */
