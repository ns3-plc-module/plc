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

#ifndef PLC_DEVICE_HELPER_H_
#define PLC_DEVICE_HELPER_H_

#include <string>
#include <ns3/object.h>
#include <ns3/random-variable.h>
#include "ns3/plc-node.h"
#include "ns3/plc-outlet.h"
#include "ns3/plc-noise.h"
#include "ns3/plc-edge.h"
#include "ns3/plc-net-device.h"
#include "ns3/plc-channel.h"
#include "ns3/plc-link-performance-model.h"
#include "ns3/plc-phy.h"
#include "ns3/plc-mac.h"

namespace ns3 {

class PLC_NetDeviceHelper : public Object
{
public:
	static TypeId GetTypeId(void);

	PLC_NetDeviceHelper(Ptr<const SpectrumModel> sm, Ptr<SpectrumValue> txPsd, PLC_NodeList& netdevices);

	void DefinePhyType(TypeId tid);
	void DefineMacType(TypeId tid);

	void SetNoiseFloor(Ptr<const SpectrumValue> psd) { m_noiseFloor = psd; }
	void SetTxPowerSpectralDensity(Ptr<SpectrumValue> txPsd) { m_txPsd = txPsd; }
	void SetRxImpedance(Ptr<PLC_Impedance> rxImpedance);
	void SetTxImpedance(Ptr<PLC_Impedance> txImpedance);
	Ptr<PLC_Impedance> GetRxImpedance(void) { return m_rxImpedance; }
	Ptr<PLC_Impedance> GetTxImpedance(void) { return m_txImpedance; }
	void SetHeaderModulationAndCodingScheme(ModulationAndCodingType mcs) { m_header_mcs = mcs; }
	void SetPayloadModulationAndCodingScheme(ModulationAndCodingType mcs) { m_payload_mcs = mcs; }

	void Setup(void);

	void CreateNodes(bool create) { m_create_nodes = create; }

	Ptr<PLC_NetDevice> GetDevice(std::string name);

	PLC_NetdeviceMap GetNetdeviceMap(void) { return m_netdeviceMap; }

private:
	Ptr<const SpectrumModel> m_spectrum_model;
	Ptr<PLC_Channel> m_channel;
	Ptr<SpectrumValue> m_txPsd;
	PLC_NodeList m_netdevice_nodes;
	Ptr<const SpectrumValue> m_noiseFloor;
	Ptr<PLC_Impedance> m_rxImpedance;
	Ptr<PLC_Impedance> m_txImpedance;
	ModulationAndCodingType m_header_mcs;
	ModulationAndCodingType m_payload_mcs;
	TypeId m_phyTid;
	TypeId m_macTid;
	bool m_create_nodes;

	PLC_NetdeviceMap m_netdeviceMap;
};

}

#endif /* PLC_DEVICE_HELPER_H_ */
