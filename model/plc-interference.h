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

#ifndef PLC_INTERFERENCE_H_
#define PLC_INTERFERENCE_H_

#include <ns3/nstime.h>
#include <ns3/spectrum-value.h>
#include <ns3/traced-value.h>
#include <ns3/trace-source-accessor.h>

namespace ns3 {

/**
 * This class implements a gaussian interference model, i.e., all
 * incoming signals are added to the total interference.
 */
class PLC_Interference : public Object
{
public:
	static TypeId GetTypeId(void);

	PLC_Interference();

	void SetNoiseFloor(Ptr<const SpectrumValue> noiseFloor);
	Ptr<const SpectrumValue> GetNoiseFloor(void) { return m_noiseFloor; }

	void StartRx (Ptr<const SpectrumValue> rxPsd);
	void AlterRxSignal (Ptr<const SpectrumValue> rxSignal);
	void EndRx(void);

	void AddInterferenceSignal (Ptr<const SpectrumValue> spd);
	void RemoveInterferenceSignal (Ptr<const SpectrumValue> spd);

	Ptr<SpectrumValue> GetSinr(void);
	double GetTotalRxPower(void);
	double GetTotalNoisePower(void);

	void SetSinrBase(Ptr<const SpectrumValue> baseSinr);
	Ptr<const SpectrumValue> GetSinrBase(void);

private:
	void DoDispose ();

	void CalcSinr(void);

	bool m_receiving;

	Ptr<SpectrumValue>			m_allSignals;
	Ptr<const SpectrumValue> 	m_rxSignal;
	Ptr<SpectrumValue> 			m_noiseSignals;
	Ptr<const SpectrumValue> 	m_noiseFloor;
	Ptr<SpectrumValue>			m_sinr;
	Ptr<const SpectrumValue>	m_sinr_base;

	TracedCallback<Time, Ptr<const SpectrumValue> > m_sumSignalTracer;
	TracedCallback<Time, Ptr<const SpectrumValue> > m_rxSignalTracer;
	TracedCallback<Time, Ptr<const SpectrumValue> > m_noiseSignalTracer;
	TracedCallback<Time, Ptr<const SpectrumValue> > m_SinrTracer;
};

}

#endif /* PLC_INTERFERENCE_H_ */
