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

#include "plc-device-helper.h"
#include <ns3/node.h>
#include <ns3/object-factory.h>
#include <ns3/log.h>
#include <ns3/abort.h>

namespace ns3 {

void
IncrementMacAddress(Mac48Address *addr)
{
	uint8_t buf[6];
	addr->CopyTo(buf);

	uint64_t address = 	(((uint64_t) buf[0] << 40) & 0xff0000000000) |
						(((uint64_t) buf[1] << 32) & 0x00ff00000000) |
						(((uint64_t) buf[2] << 24) & 0x0000ff000000) |
						(((uint64_t) buf[3] << 16) & 0x000000ff0000) |
						(((uint64_t) buf[4] << 8)  & 0x00000000ff00) |
						(((uint64_t) buf[5] << 0)  & 0x0000000000ff);

	++address;

	buf[0] = (address >> 40) & 0xff;
	buf[1] = (address >> 32) & 0xff;
	buf[2] = (address >> 24) & 0xff;
	buf[3] = (address >> 16) & 0xff;
	buf[4] = (address >> 8) & 0xff;
	buf[5] = (address >> 0) & 0xff;

	addr->CopyFrom(buf);
}

////////////////////////// PLC_NetDeviceHelper ////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_NetDeviceHelper);

TypeId
PLC_NetDeviceHelper::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId("ns3::PLC_NetDeviceHelper")
    		.SetParent<Object> ()
    		;
	return tid;
}

PLC_NetDeviceHelper::PLC_NetDeviceHelper(Ptr<const SpectrumModel> sm, Ptr<SpectrumValue> txPsd, PLC_NodeList& deviceNodes)
	: m_spectrum_model(sm), m_txPsd(txPsd), m_netdevice_nodes(deviceNodes)
{
	// Modulation and Coding Schemes
	m_header_mcs = BPSK_1_2;
	m_payload_mcs = BPSK_1_2;

	// Default phy model to be used
	m_phyTid = PLC_InformationRatePhy::GetTypeId();
	// Default mac model to be used
	m_macTid = PLC_ArqMac::GetTypeId();

	// Create ns3::Node for this NetDevice by default
	m_create_nodes = true;
}

void
PLC_NetDeviceHelper::DefinePhyType(TypeId tid)
{
	m_phyTid = tid;
}

void
PLC_NetDeviceHelper::DefineMacType(TypeId tid)
{
	m_macTid = tid;
}

void
PLC_NetDeviceHelper::SetRxImpedance(Ptr<PLC_Impedance> rxImpedance)
{
	m_rxImpedance = rxImpedance->Copy();

	if (m_netdeviceMap.size() > 0)
	{
		PLC_NetdeviceMap::iterator nit;
		for (nit = m_netdeviceMap.begin(); nit != m_netdeviceMap.end(); nit++)
		{
			nit->second->SetRxImpedance(m_rxImpedance);
		}
	}
}

void
PLC_NetDeviceHelper::SetTxImpedance(Ptr<PLC_Impedance> txImpedance)
{
	m_txImpedance = txImpedance->Copy();

	if (m_netdeviceMap.size() > 0)
	{
		PLC_NetdeviceMap::iterator nit;
		for (nit = m_netdeviceMap.begin(); nit != m_netdeviceMap.end(); nit++)
		{
			nit->second->SetTxImpedance(m_txImpedance);
		}
	}
}

void
PLC_NetDeviceHelper::Setup(void)
{
	NS_ASSERT_MSG(m_txPsd, "TX psd not set!");

	// Test if payload mcs is compatible
	if (m_phyTid == PLC_IncrementalRedundancyPhy::GetTypeId())
	{
		NS_ASSERT_MSG (m_payload_mcs >= BPSK_RATELESS, "Payload modulation and coding type (" << m_payload_mcs << ") not compatible with PLC_IncrementalRedundancyPhy");
	}

	if (m_noiseFloor == NULL)
	{
		m_noiseFloor = CreateBestCaseBgNoise(m_spectrum_model)->GetNoisePsd();
	}

	ObjectFactory netdeviceFactory;
	netdeviceFactory.SetTypeId(PLC_NetDevice::GetTypeId());

	ObjectFactory phyFactory;
	phyFactory.SetTypeId(m_phyTid);

	ObjectFactory macFactory;
	macFactory.SetTypeId(m_macTid);

	Mac48Address addr("00:00:00:00:00:00");

	PLC_NodeList::iterator nit;
	for (nit = m_netdevice_nodes.begin(); nit != m_netdevice_nodes.end(); nit++)
	{
		// Create net device
		Ptr<PLC_NetDevice> dev = netdeviceFactory.Create<PLC_NetDevice> ();

		dev->SetPlcNode(*nit);
		dev->SetSpectrumModel(m_spectrum_model);
		dev->SetNoiseFloor(m_noiseFloor);
		dev->SetTxPowerSpectralDensity(m_txPsd);

		// Create PHY
		Ptr<PLC_Phy> phy = phyFactory.Create<PLC_Phy> ();

		if (phy->GetInstanceTypeId() == PLC_ErrorRatePhy::GetTypeId())
		{
			NS_ASSERT_MSG (m_header_mcs == m_payload_mcs, "Header and payload modulation and coding schemes have to be identical for PLC_ErrorRatePhy");
			NS_ASSERT_MSG (m_header_mcs < BPSK_RATELESS, "Rateless encoding not supported by PLC_ErrorRatePhy");
			(StaticCast<PLC_ErrorRatePhy, PLC_Phy> (phy))->SetModulationAndCodingScheme(m_header_mcs);
		}
		else if (
				phy->GetInstanceTypeId() == PLC_InformationRatePhy::GetTypeId () ||
				phy->GetInstanceTypeId().IsChildOf(PLC_InformationRatePhy::GetTypeId ())
				 )
		{
			(StaticCast<PLC_InformationRatePhy, PLC_Phy> (phy))->SetHeaderModulationAndCodingScheme(m_header_mcs);
			(StaticCast<PLC_InformationRatePhy, PLC_Phy> (phy))->SetPayloadModulationAndCodingScheme(m_payload_mcs);
		}
		else
		{
			NS_ABORT_MSG("Incompatible PHY type!");
		}

		// Create MAC
		Ptr<PLC_Mac> mac = macFactory.Create<PLC_Mac> ();

		dev->SetPhy(phy);
		dev->SetMac(mac);

		if (m_rxImpedance)
			dev->SetRxImpedance(m_rxImpedance);

		if (m_txImpedance)
			dev->SetTxImpedance(m_txImpedance);

		IncrementMacAddress(&addr);
		dev->SetAddress(addr);

		if (m_create_nodes)
		{
			// Create ns-3 node
			Ptr<Node> node = CreateObject<Node> ();

			// Bind device to ns-3 node
			node->AddDevice(dev);
		}

		NS_ASSERT(dev->ConfigComplete());

		std::string name = (*nit)->GetName();
		NS_ASSERT_MSG(m_netdeviceMap.find(name) == m_netdeviceMap.end(), "Duplicate netdevice name");
		m_netdeviceMap[name] = dev;
	}
}

Ptr<PLC_NetDevice>
PLC_NetDeviceHelper::GetDevice(std::string name)
{
	NS_ASSERT_MSG(m_netdeviceMap.find(name) != m_netdeviceMap.end(), "Unknown net device");
	return m_netdeviceMap[name];
}


} // namespace ns3
