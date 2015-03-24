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

#ifndef PLC_MAC_H_
#define PLC_MAC_H_

#include <set>
#include <map>
#include <ns3/object.h>
#include <ns3/callback.h>
#include <ns3/packet.h>
#include <ns3/event-id.h>
#include <ns3/drop-tail-queue.h>
#include "plc-phy.h"
#include "plc-header.h"

namespace ns3 {

class PLC_Relay;

typedef enum
{
	CHANNEL_IDLE,
	CHANNEL_ACCESS_FAILURE
} PLC_CsmaCaState;

typedef Callback<void, Ptr<Packet> , Mac48Address, Mac48Address > PLC_MacDataCallback;
typedef Callback<void> PLC_MacAcknowledgementCallback;
typedef Callback<void, Ptr<const Packet> > PLC_MacTransmissionFailedCallback;
typedef Callback<void> PLC_CcaRequestCallback; // This method informs MAC whether the channel is idle or busy

/**
 * \class PLC_Mac
 *
 * Abstract base class for PLC MAC layers implementing
 * 48 bit addressing, channel access via CSMA/CA algorithm
 * and Stop-And-Wait transmission
 */
class PLC_Mac : public Object
{
public:
	static TypeId GetTypeId (void);

	PLC_Mac (void);
	~PLC_Mac (void) = 0;

	void SetCcaRequestCallback (PLC_CcaRequestCallback c);
	void RequestCca ();
	void InitializeCsmaCa (void);
	void RandomBackoffDelay ();
	void CcaConfirm (PLC_PhyCcaResult status);
	void CsmaCaConfirm (PLC_CsmaCaState state);
	virtual void NotifyCcaConfirm (PLC_PhyCcaResult status) = 0;
	virtual void NotifyCsmaCaConfirm (PLC_CsmaCaState state) = 0;

	void SetMinBE (uint8_t minBE) { m_macMinBE = minBE; }
	uint8_t GetMinBE (void) { return m_macMinBE; }
	void SetMaxBE (uint8_t maxBE) { m_macMaxBE = maxBE; }
	uint8_t GetMaxBE (void) { return m_macMaxBE; }
	void SetUnitBackoffPeriod (uint32_t nsymbols) { m_aUnitBackoffPeriod = nsymbols; }
	uint32_t GetUnitBackoffPeriod (void) { return m_aUnitBackoffPeriod; }

	/**
	 * Callback for data delivery to higher layer
	 */
	void SetMacDataCallback (PLC_MacDataCallback c);

	/**
	 * Callback for failed data transmission
	 */
	void SetTransmissionFailedCallback (PLC_MacTransmissionFailedCallback c);

	/**
	 * Callback for promiscuous data delivery to higher layer
	 */
	void SetPromiscuousMacDataCallback (PLC_MacDataCallback c);

	/**
	 * Callback indicating that acknowledgement for previously sent data
	 * has been received
	 */
	void SetMacAcknowledgementCallback (PLC_MacAcknowledgementCallback c);

	/**
	 * Set MAC address
	 *
	 * @param addr 16 bit MAC address
	 */
	void SetAddress (Mac48Address addr);

	/**
	 * @return 16bit MAC address
	 */
	Mac48Address GetAddress (void);

	/**
	 * Set broadcast address
	 *
	 * @param addr 16 bit broadcast address
	 */
	void SetBroadcastAddress (Mac48Address addr);

	/**
	 * @return 16 bit broadcast address
	 */
	Mac48Address GetBroadcastAddress (void);

	/**
	 * Set multicast address
	 *
	 * @param addr 16 bit multicast address
	 */
	void SetMulticastAddress (Mac48Address addr);

	/**
	 * @return 16 bit multicast address
	 */
	Mac48Address GetMulticastAddress (void);

	/**
	 * Send packet p to dst
	 * @param p
	 * @param dst
	 * @return
	 */
	bool Send (Ptr<Packet> p, Mac48Address dst);

	/**
	 *
	 * @param p
	 * @param src
	 * @param dst
	 * @return
	 */
	bool SendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst);

	void SetPhy (Ptr<PLC_Phy> phy);
	Ptr<PLC_Phy> GetPhy (void);

	/**
	* Notify the MAC that the PHY has finished a previously started transmission
	*/
	virtual void NotifyTransmissionEnd (void) = 0;

	/**
	* Notify MAC that PHY successfully finished reception of packet p
	*
	* @param p the received packet
	*/
	void NotifyReceptionEndOk (Ptr<const Packet> p, uint16_t messageId);

	void SendAcknowledgement(Mac48Address src, uint16_t sequence_number);
	void SendNegativeAcknowledgement(Mac48Address src, uint16_t sequence_number);

protected:
	// static MAC list needed for opportunistic relaying
	static std::map<Mac48Address, Ptr<PLC_Mac> > mac_list;

	virtual void DoInitialize (void);
	virtual void DoDispose (void);
	virtual bool DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst) = 0;
	virtual void DoProcess (Ptr<const Packet> p) = 0;
	virtual void DoSetPhy (Ptr<PLC_Phy> phy) = 0;
	virtual Ptr<PLC_Phy> DoGetPhy (void) = 0;
	virtual void DoNotifyReceptionEndOk (void) {}

	virtual void TriggerTransmission (void);
	void ForwardUp (Ptr<Packet> p, Mac48Address src, Mac48Address dst);

	Mac48Address m_address;
	Mac48Address m_broadcast_address;
	Mac48Address m_multicast_address;

	Ptr<DropTailQueue> 	m_txQueue;
	Ptr<Packet>			m_ackPacket;
	Ptr<Packet> 		m_rxPacket;

	bool m_forward_up;

	// unslotted CSMA/CA according to IEEE 802.15.4
	bool m_csmaca_active;
	bool m_promiscuous_mode;
	uint32_t m_csmaca_attempts;
	uint8_t m_NB;                         // number of backoffs for the current transmission
	uint8_t m_BE;                         // backoff exponent
	uint8_t m_macMinBE;                   // 0-macMaxBE default 3
	uint8_t m_macMaxBE;                   // 3-8 default 5
	uint8_t m_macMaxCSMABackoffs;         // 0-5 default 4
	uint32_t m_aUnitBackoffPeriod;        // 20 symbols in each backoff periods
	EventId m_requestCCAEvent;
	EventId m_backoffEndEvent;

	PLC_MacDataCallback m_data_callback;
	PLC_MacTransmissionFailedCallback m_transmission_failed_callback;
	PLC_MacDataCallback m_promiscuous_data_callback;
	PLC_MacAcknowledgementCallback m_acknowledgement_callback;
	PLC_CcaRequestCallback m_cca_request_callback;
};

class PLC_ArqMac : public PLC_Mac
{
public:
	static TypeId GetTypeId (void);

	PLC_ArqMac (void);

	void SetAcknowledgementTimeout (Time timeout) { m_timeout = timeout; }
	Time GetAcknowledgementTimeout (void) { return m_timeout; }

	void SetMaxReplays (size_t max_replays) { m_max_replays = max_replays; }
	size_t GetMaxReplays (void) { return m_max_replays; }

	virtual void NotifyCcaConfirm (PLC_PhyCcaResult status);
	virtual void NotifyCsmaCaConfirm (PLC_CsmaCaState state);
	virtual void NotifyTransmissionEnd (void);

	virtual void AcknowledgementTimeout (void);

protected:
	virtual void DoInitialize (void);
	virtual void DoDispose (void);
	virtual bool DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst);
	virtual void DoProcess (Ptr<const Packet> p);
	virtual void DoSetPhy (Ptr<PLC_Phy> phy);
	virtual Ptr<PLC_Phy> DoGetPhy (void);

	virtual void NotifyAcknowledgement (void);

	Ptr<PLC_HalfDuplexOfdmPhy> m_phy;

	PLC_MacHeader m_txHeader;
	PLC_MacHeader m_rxHeader;
	uint16_t m_sequence_number;

	Time m_timeout;
	EventId m_timeoutEvent;
	size_t m_max_replays;
	size_t m_replays;
};

/**
 * HARQ Type I MAC layer implementation
 */
class PLC_HarqMac : public PLC_Mac
{
public:
	static TypeId GetTypeId (void);

	PLC_HarqMac (void);

	void SetAcknowledgementTimeout (Time timeout) { m_acknowledgement_timeout = timeout; }
	Time GetAcknowledgementTimeout (void) { return m_acknowledgement_timeout; }

	void SetMaxRedundancyFrames (size_t max_frames) { m_max_redundancy_frames = max_frames; }
	size_t GetMaxRedundancyFrames (void) { return m_max_redundancy_frames; }

	virtual void NotifyCcaConfirm (PLC_PhyCcaResult status);
	virtual void NotifyCsmaCaConfirm (PLC_CsmaCaState state);
	virtual void NotifyTransmissionEnd (void);

	virtual void AcknowledgementTimeout (void);

protected:
	virtual void DoInitialize (void);
	virtual void DoDispose (void);
	virtual bool DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst);
	virtual void DoProcess (Ptr<const Packet> p);
	virtual void DoSetPhy (Ptr<PLC_Phy> phy);
	virtual Ptr<PLC_Phy> DoGetPhy (void);

	virtual void NotifyAcknowledgement (void);
	virtual void NotifyNegativeAcknowledgement (void);

	virtual void TriggerTransmission (void);

	Ptr<PLC_InformationRatePhy> m_phy;

	PLC_MacHeader m_txHeader;
	PLC_MacHeader m_rxHeader;
	uint16_t m_sequence_number;

	bool m_send_redundancy;

	Time m_acknowledgement_timeout;
	EventId m_acknowledgementTimeoutEvent;
	size_t m_max_redundancy_frames;
	size_t m_sent_redundancy_frames;
};

}

#endif /* PLC_MAC_H_ */
