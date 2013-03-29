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

#include <ns3/log.h>
#include <ns3/llc-snap-header.h>
#include <ns3/simulator.h>
#include "plc-net-device.h"
#include "ns3/abort.h"
#include "ns3/node.h"
#include "ns3/plc-mac.h"
#include "ns3/plc-phy.h"
#include "ns3/spectrum-channel.h"
#include "ns3/pointer.h"
#include "plc-interface.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_NetDevice");

////////////////////////////////////// PLC_Netdevice ////////////////////////////////////////////////

TypeId
PLC_NetDevice::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::PLC_NetDevice")
	.SetParent<NetDevice> ()
	.AddConstructor<PLC_NetDevice> ()
	.AddAttribute ("Channel", "The channel attached to this device",
				   PointerValue (),
				   MakePointerAccessor (&PLC_NetDevice::DoGetChannel),
				   MakePointerChecker<SpectrumChannel> ())
	;
	return tid;
}

PLC_NetDevice::PLC_NetDevice ()
{
	NS_LOG_FUNCTION (this);
	// Default Modulation and Coding Scheme
	m_mcs = BPSK_1_2;
	m_linkUp = true;
	m_configComplete = false;
}

PLC_NetDevice::~PLC_NetDevice ()
{
	NS_LOG_FUNCTION (this);
}

void
PLC_NetDevice::DoDispose (void)
{
	NS_LOG_FUNCTION (this);

	m_node = 0;
	m_noiseFloor = 0;
	m_txPsd = 0;
	m_plc_node = 0;
	m_rxImpedance = 0;
	m_txImpedance = 0;
	// chain up.
	NetDevice::DoDispose ();
}

void
PLC_NetDevice::DoStart (void)
{
	NS_LOG_FUNCTION (this);
	NetDevice::DoStart ();
}

void
PLC_NetDevice::SetPlcNode(Ptr<PLC_Node> plc_node)
{
	NS_LOG_FUNCTION(this);
	m_plc_node = plc_node;
	m_plc_node->AggregateObject(this);
	CompleteConfig ();
}

void
PLC_NetDevice::SetSpectrumModel(Ptr<const SpectrumModel> sm)
{
	NS_LOG_FUNCTION(this);
	this->m_spectrum_model = sm;
	CompleteConfig ();
}

void
PLC_NetDevice::SetNoiseFloor(Ptr<const SpectrumValue> psd)
{
	NS_LOG_FUNCTION(this << psd);
	m_noiseFloor = psd;
	CompleteConfig();
}

void
PLC_NetDevice::SetTxPowerSpectralDensity(Ptr<SpectrumValue> txPsd)
{
	NS_LOG_FUNCTION(this << txPsd);
	m_txPsd = txPsd;
	CompleteConfig();
}

void
PLC_NetDevice::SetShuntImpedance(Ptr<PLC_Impedance> shuntImpedance)
{
	NS_LOG_FUNCTION(this << shuntImpedance);
	m_shuntImpedance = shuntImpedance;

}

void
PLC_NetDevice::SetRxImpedance(Ptr<PLC_Impedance> rxImpedance)
{
	NS_LOG_FUNCTION(this << rxImpedance);
	m_rxImpedance = rxImpedance;

	if (GetPhy())
	{
		if (GetPhy()->GetInstanceTypeId().IsChildOf(PLC_HalfDuplexOfdmPhy::GetTypeId()))
		{
			Ptr<PLC_HalfDuplexOfdmPhy> phy = StaticCast<PLC_HalfDuplexOfdmPhy, PLC_Phy> (GetPhy());
			phy->SetRxImpedance(rxImpedance);
		}
	}
}

void
PLC_NetDevice::SetTxImpedance(Ptr<PLC_Impedance> txImpedance)
{

}

Ptr<const SpectrumModel>
PLC_NetDevice::GetSpectrumModel(void)
{
	NS_LOG_FUNCTION (this);
	return m_spectrum_model;
}

void
PLC_NetDevice::Receive (Ptr<Packet> packet, Mac48Address from, Mac48Address to)
{
	NS_LOG_FUNCTION (this);
	NS_LOG_LOGIC(*packet);

	LlcSnapHeader llc;
	packet->RemoveHeader (llc);

	if (!m_receive_cb.IsNull())
	{
		m_receive_cb(this, packet, llc.GetType (), from);
	}
}

Ptr<Channel> PLC_NetDevice::GetChannel (void) const
{
	return DoGetChannel();
}

Ptr<Channel>
PLC_NetDevice::DoGetChannel (void) const
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT_MSG(m_plc_node, "The device is not bound to a PLC_Node which defines the Channel");
	return m_plc_node->GetChannel();
}

void
PLC_NetDevice::SetIfIndex (const uint32_t index)
{
	NS_LOG_FUNCTION (this << index);
	m_ifIndex = index;
}

uint32_t
PLC_NetDevice::GetIfIndex (void) const
{
	NS_LOG_FUNCTION (this);
	return m_ifIndex;
}

void
PLC_NetDevice::LinkUp (void)
{
	NS_LOG_FUNCTION (this);
	m_linkUp = true;

	if (GetPhy() != NULL)
	{
		GetPhy()->Start();
	}

	m_linkChanges ();
}
void
PLC_NetDevice::LinkDown (void)
{
	NS_LOG_FUNCTION (this);
	m_linkUp = false;
	m_linkChanges ();
}

bool
PLC_NetDevice::SetMtu (const uint16_t mtu)
{
  NS_ABORT_MSG ("Unsupported");
  return false;
}

uint16_t
PLC_NetDevice::GetMtu (void) const
{
  NS_ABORT_MSG ("Unsupported");
  return 0;
}

bool
PLC_NetDevice::IsLinkUp (void) const
{
	NS_LOG_FUNCTION (this);
	return m_linkUp;
}

void
PLC_NetDevice::AddLinkChangeCallback (Callback<void> callback)
{
	NS_LOG_FUNCTION (this);
	m_linkChanges.ConnectWithoutContext (callback);
}

bool
PLC_NetDevice::IsBroadcast (void) const
{
	NS_LOG_FUNCTION (this);
	return false;
}

Address
PLC_NetDevice::GetBroadcast (void) const
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_mac, "MAC not set!");
	return m_mac->GetBroadcastAddress();
}

bool
PLC_NetDevice::IsMulticast (void) const
{
	NS_LOG_FUNCTION (this);
	return false;
}

Address
PLC_NetDevice::GetMulticast (Ipv4Address multicastGroup) const
{
	NS_LOG_FUNCTION (this);
	return m_mac->GetMulticastAddress ();
}

Address
PLC_NetDevice::GetMulticast (Ipv6Address addr) const
{
	NS_LOG_FUNCTION (this);
	return m_mac->GetMulticastAddress ();
}

bool
PLC_NetDevice::IsBridge (void) const
{
	NS_LOG_FUNCTION (this);
	return false;
}

bool
PLC_NetDevice::IsPointToPoint (void) const
{
	NS_LOG_FUNCTION (this);
	return false;
}

Ptr<Node>
PLC_NetDevice::GetNode (void) const
{
	NS_LOG_FUNCTION (this);
	return m_node;
}

void
PLC_NetDevice::SetNode (Ptr<Node> node)
{
	NS_LOG_FUNCTION (this);
	m_node = node;
	CompleteConfig ();
}

void
PLC_NetDevice::SetPhy (Ptr<PLC_Phy> phy)
{
	NS_LOG_FUNCTION (this << phy);
	m_phy = phy;
}

Ptr<PLC_Phy>
PLC_NetDevice::GetPhy (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_phy, "PHY not set!");
	return m_phy;
}

void
PLC_NetDevice::SetMac (Ptr<PLC_Mac> mac)
{
	NS_LOG_FUNCTION (this << mac);
	m_mac = mac;
}

Ptr<PLC_Mac>
PLC_NetDevice::GetMac (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_mac, "MAC not set!");
	return m_mac;
}

bool
PLC_NetDevice::NeedsArp (void) const
{
	NS_LOG_FUNCTION (this);
	return false;
}

void
PLC_NetDevice::SetReceiveCallback (ReceiveCallback cb)
{
	NS_LOG_FUNCTION (this);
	m_receive_cb = cb;
}

void
PLC_NetDevice::SetPromiscReceiveCallback (PromiscReceiveCallback cb)
{
	NS_LOG_FUNCTION (this);
	m_promiscuous_receive_cb = cb;
}

bool
PLC_NetDevice::SupportsSendFrom (void) const
{
	NS_LOG_FUNCTION_NOARGS ();
	return true;
}

PLC_ChannelTransferImpl *
PLC_NetDevice::GetChannelTransferImpl(Ptr<PLC_NetDevice> dev)
{
	NS_ASSERT(ConfigComplete() && dev->ConfigComplete());
	return m_phy->GetChannelTransferImpl(PeekPointer(dev->GetPhy()));
}

void
PLC_NetDevice::SetAddress (Address address)
{
	NS_LOG_FUNCTION (this);
	m_mac->SetAddress (Mac48Address::ConvertFrom (address));
}

Address
PLC_NetDevice::GetAddress (void) const
{
	NS_LOG_FUNCTION (this);
	return m_mac->GetAddress ();
}

bool
PLC_NetDevice::ConfigComplete(void)
{
	NS_LOG_FUNCTION (this);
	return m_configComplete;
}

void
PLC_NetDevice::CompleteConfig (void)
{
	NS_LOG_FUNCTION (this);
	if (m_spectrum_model == 0
	  || m_noiseFloor == 0
	  || m_txPsd == 0
	  || m_node == 0
	  || m_plc_node == 0
	  || ConfigComplete())
	{
	  return;
	}

	if (m_phy == 0)
	{
		m_phy = CreateObject<PLC_InformationRatePhy> ();
	}

	if (m_mac == 0)
	{
		m_mac = CreateObject<PLC_ArqMac> ();
	}

	NS_ASSERT_MSG(m_phy->GetInstanceTypeId().IsChildOf(PLC_HalfDuplexOfdmPhy::GetTypeId()), "PHY has to be of type PLC_HalfDuplexOfdmPhy!");
	Ptr<PLC_HalfDuplexOfdmPhy> phy = StaticCast<PLC_HalfDuplexOfdmPhy, PLC_Phy> (m_phy);

	m_outlet = CreateObject<PLC_Outlet> (m_plc_node, m_shuntImpedance);
	phy->CreateInterfaces(m_outlet, m_txPsd, m_rxImpedance, m_txImpedance);
	phy->GetTxInterface()->AggregateObject(m_node);
	phy->GetRxInterface()->AggregateObject(m_node);
	phy->SetNoiseFloor(m_noiseFloor);
	m_mac->SetPhy(m_phy);
	m_mac->SetMacDataCallback(MakeCallback(&PLC_NetDevice::Receive, this));

	m_configComplete = true;
}

bool
PLC_NetDevice::Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT(m_configComplete);

	LlcSnapHeader llc;
	llc.SetType (protocolNumber);
	packet->AddHeader (llc);

	return m_mac->Send(packet, Mac48Address::ConvertFrom (dest));
}

bool
PLC_NetDevice::SendFrom (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT(m_configComplete);

	return m_mac->SendFrom(packet, Mac48Address::ConvertFrom (source), Mac48Address::ConvertFrom (dest));
}

}
