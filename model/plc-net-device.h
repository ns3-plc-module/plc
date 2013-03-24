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

#ifndef PLC_NET_DEVICE_H_
#define PLC_NET_DEVICE_H_

#include <string>
#include <stdint.h>
#include "ns3/net-device.h"
#include "ns3/traced-callback.h"
#include "ns3/spectrum-model.h"
#include "ns3/plc-channel.h"
#include "ns3/spectrum-value.h"
#include "ns3/plc-phy.h"
#include "ns3/plc-mac.h"

namespace ns3 {

/**
 * @class PLC_NetDevice
 *
 * @brief Abstract base class for PLC net devices
 *
 * This class together with its subclasses are responsible for configuring PLC net devices.
 * Thus, when all parameters have been set, the interconnection
 * between PHY and MAC layer is performed by CompleteConfig()
 *
 * Because the implementations of PLC_NetDevice use different PHY and MAC
 * instances (simple vs. harq/ir) the respective configuration is done in the subclasses
 */
class PLC_NetDevice : public NetDevice
{
public:
	static TypeId GetTypeId (void);

	PLC_NetDevice ();
	virtual ~PLC_NetDevice ();

	void SetPlcNode(Ptr<PLC_Node> plc_node);
	Ptr<PLC_Node> GetPlcNode(void) { return m_plc_node; }
	void SetSpectrumModel(Ptr<const SpectrumModel> sm);
	void SetNoiseFloor(Ptr<const SpectrumValue> psd);
	void SetTxPowerSpectralDensity(Ptr<SpectrumValue> txPsd);

	void SetShuntImpedance(Ptr<PLC_Impedance> shuntImpedance);
	void SetRxImpedance(Ptr<PLC_Impedance> rxImpedance);
	void SetTxImpedance(Ptr<PLC_Impedance> txImpedance);
	Ptr<PLC_Impedance> GetShuntImpedance(void) { return m_shuntImpedance; }
	Ptr<PLC_Impedance> GetRxImpedance(void) { return m_rxImpedance; }
	Ptr<PLC_Impedance> GetTxImpedance(void) { return m_txImpedance; }

	Ptr<PLC_Outlet> GetOutlet(void) { return m_outlet; }
	Ptr<const SpectrumModel> GetSpectrumModel(void);

	void Receive (Ptr<Packet> p, Mac48Address from, Mac48Address to);

	// From class NetDevice
	virtual void SetIfIndex (const uint32_t index);
	virtual uint32_t GetIfIndex (void) const;
	virtual Ptr<Channel> GetChannel (void) const;
	virtual void SetAddress (Address address);
	virtual Address GetAddress (void) const;
	virtual bool SetMtu (const uint16_t mtu);
	virtual uint16_t GetMtu (void) const;
	virtual bool IsLinkUp (void) const;
	virtual void AddLinkChangeCallback (Callback<void> callback);
	virtual bool IsBroadcast (void) const;
	virtual Address GetBroadcast (void) const;
	virtual bool IsMulticast (void) const;
	virtual Address GetMulticast (Ipv4Address multicastGroup) const;
	virtual Address GetMulticast (Ipv6Address addr) const;
	virtual bool IsBridge (void) const;
	virtual bool IsPointToPoint (void) const;
	virtual bool Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);
	virtual bool SendFrom (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);
	virtual Ptr<Node> GetNode (void) const;
	virtual void SetNode (Ptr<Node> node);
	virtual bool NeedsArp (void) const;

	virtual void SetReceiveCallback (ReceiveCallback cb);
	virtual void SetPromiscReceiveCallback (PromiscReceiveCallback cb);
	virtual bool SupportsSendFrom (void) const;

	virtual bool ConfigComplete(void);

	virtual void SetPhy (Ptr<PLC_Phy> phy);
	virtual void SetMac (Ptr<PLC_Mac> mac);
	virtual Ptr<PLC_Phy> GetPhy (void);
	virtual Ptr<PLC_Mac> GetMac (void);

	PLC_ChannelTransferImpl *GetChannelTransferImpl(Ptr<PLC_NetDevice> dev);

	void LinkUp (void);
	void LinkDown (void);

protected:
	virtual void DoDispose (void);
	virtual void DoStart (void);
	Ptr<Channel> DoGetChannel (void) const;
	virtual void CompleteConfig (void);

	Ptr<const SpectrumModel> m_spectrum_model;
	Ptr<const SpectrumValue> m_noiseFloor;
	Ptr<SpectrumValue> m_txPsd;
	Ptr<Node> m_node;
	Ptr<PLC_Node> m_plc_node;
	Ptr<PLC_Outlet> m_outlet;

	Ptr<PLC_Phy> m_phy;
	Ptr<PLC_Mac> m_mac;

	bool m_linkUp;

	uint32_t m_ifIndex;
	uint32_t m_txIfIndex;
	uint32_t m_rxIfIndex;
	Ptr<PLC_Impedance> m_shuntImpedance;
	Ptr<PLC_Impedance> m_txImpedance;
	Ptr<PLC_Impedance> m_rxImpedance;

	ModulationAndCodingType m_mcs;

	bool m_configComplete;

	ReceiveCallback m_receive_cb;
	PromiscReceiveCallback m_promiscuous_receive_cb;

	TracedCallback<> m_linkChanges;
};

}

#endif /* PLC_NET_DEVICE_H_ */
