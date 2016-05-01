/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright  (c) 2012 University of British Columbia, Vancouver
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

#include <ns3/abort.h>
#include <ns3/log.h>
#include <ns3/simulator.h>
#include <ns3/random-variable-stream.h>
#include <ns3/llc-snap-header.h>
#include "plc-mac.h"

NS_LOG_COMPONENT_DEFINE ("PLC_Mac");

namespace ns3 {

#define PLC_MAC_FUNCTION(msg)\
	do {\
		if  (GetPhy() && GetPhy()->GetNode ()) {\
			NS_LOG_FUNCTION ("PLC_Mac[" << GetPhy()->GetNode ()->GetName () << "] : " << msg);\
		}\
		else {\
			NS_LOG_FUNCTION ("PLC_Mac: " << msg);\
		}\
	} while (0)

#define PLC_MAC_LOGIC(msg)\
	do {\
		if  (GetPhy() && GetPhy()->GetNode ()) {\
			NS_LOG_LOGIC ("PLC_Mac[" << GetPhy()->GetNode ()->GetName () << "]: " << msg);\
		}\
		else {\
			NS_LOG_LOGIC ("PLC_Mac: " << msg);\
		}\
	} while (0)

#define PLC_MAC_DEBUG(msg)\
	do {\
		if  (GetPhy() && GetPhy()->GetNode ()) {\
			NS_LOG_DEBUG ("PLC_Mac[" << GetPhy()->GetNode ()->GetName () << "]: " << msg);\
		}\
		else {\
			NS_LOG_DEBUG ("PLC_Mac: " << msg);\
		}\
	} while (0)

#define PLC_MAC_INFO(msg)\
	do {\
		if  (GetPhy() && GetPhy()->GetNode ()) {\
			NS_LOG_INFO ("PLC_Mac[" << GetPhy()->GetNode ()->GetName () << "]: " << msg);\
		}\
		else {\
			NS_LOG_INFO ("PLC_Mac: " << msg);\
		}\
	} while (0)

#ifndef MAX
#define MAX(x,y)        (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x,y)        (((x) < (y)) ? (x) : (y))
#endif

//////////////////////////////// PLC_Mac /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_Mac);

std::map<Mac48Address, Ptr<PLC_Mac> > PLC_Mac::mac_list = std::map<Mac48Address, Ptr<PLC_Mac> >  ();

TypeId
PLC_Mac::GetTypeId  (void)
{
  static TypeId tid = TypeId  ("ns3::PLC_Mac")
    .SetParent<Object>  ()
    ;
    return tid;
}

PLC_Mac::PLC_Mac ()
{
	m_broadcast_address = Mac48Address ("ff:ff:ff:ff:ff:ff");
	m_multicast_address = Mac48Address ("ff:ff:ff:ff:ff:ff");

	m_forward_up = true;

	m_csmaca_attempts = 0;
	m_csmaca_active = false;
	m_promiscuous_mode = false;
	m_macMinBE = 1;
	m_macMaxBE = 3;
	m_macMaxCSMABackoffs = 10;
	m_aUnitBackoffPeriod = 1; //20 symbols

	m_ackPacket = 0;
	m_rxPacket = 0;
	m_txQueue = CreateObject<DropTailQueue> ();
}

PLC_Mac::~PLC_Mac ()
{
}

void
PLC_Mac::DoInitialize (void)
{
	PLC_MAC_FUNCTION (this);
}

void
PLC_Mac::DoDispose (void)
{
	PLC_MAC_FUNCTION (this);
	m_data_callback = MakeNullCallback<void, Ptr<Packet>, Mac48Address, Mac48Address > ();
	m_promiscuous_data_callback = MakeNullCallback<void, Ptr<Packet>, Mac48Address, Mac48Address > ();
	m_acknowledgement_callback = MakeNullCallback<void> ();
	m_transmission_failed_callback = MakeNullCallback<void, Ptr<const Packet> > ();
	m_cca_request_callback = MakeNullCallback<void> ();

	m_ackPacket = 0;
	m_rxPacket = 0;
	m_txQueue = 0;
}

void
PLC_Mac::SetCcaRequestCallback (PLC_CcaRequestCallback c)
{
	PLC_MAC_FUNCTION (this);
	m_cca_request_callback = c;
}

void
PLC_Mac::RequestCca (void)
{
	PLC_MAC_FUNCTION(this);
	if (!m_cca_request_callback.IsNull ())
	{
		m_cca_request_callback ();
	}
}

void
PLC_Mac::InitializeCsmaCa (void)
{
	PLC_MAC_FUNCTION(this);

	// CSMA/CA algorithm according IEEE 802.15.4 (only unslotted implementation)
	m_NB = 0;
    m_BE = m_macMinBE;
    m_csmaca_active = true;
    Simulator::ScheduleNow (&PLC_Mac::RandomBackoffDelay, this);
}

void
PLC_Mac::RandomBackoffDelay ()
{
	NS_LOG_FUNCTION (this);

	Ptr<UniformRandomVariable> uniformVar = CreateObject<UniformRandomVariable>();
	uint64_t upperBound = (uint64_t) pow (2, m_BE) - 1;
	uint64_t backoffPeriod;
	Time randomBackoff;

	backoffPeriod = (uint64_t)uniformVar->GetValue (0,upperBound); //num backoff periods
	PLC_MAC_LOGIC ("CSMA/CA backoff periods: " << backoffPeriod);

	randomBackoff = MicroSeconds (backoffPeriod * m_aUnitBackoffPeriod * PLC_Phy::GetSymbolDuration().GetMicroSeconds());

	PLC_MAC_LOGIC ("Requesting CCA after backoff of " << randomBackoff.GetMicroSeconds () << " us");
	m_requestCCAEvent = Simulator::Schedule (randomBackoff, &PLC_Mac::RequestCca, this);
}

void
PLC_Mac::CcaConfirm(PLC_PhyCcaResult status)
{
	PLC_MAC_FUNCTION(this << status);

	if (m_csmaca_active)
	{
		if (status == CHANNEL_CLEAR)
		{
			Simulator::ScheduleNow(&PLC_Mac::CsmaCaConfirm, this, CHANNEL_IDLE);
		}
		else
		{
			m_BE = MIN (m_BE + 1, m_macMaxBE);
			m_NB++;
			if (m_NB > m_macMaxCSMABackoffs)
			{
				PLC_MAC_LOGIC ("CSMA/CA channel access failure");
				Simulator::ScheduleNow(&PLC_Mac::CsmaCaConfirm, this, CHANNEL_ACCESS_FAILURE);
			}
			else
			{
				PLC_MAC_LOGIC ("Perform another backoff; m_NB = " << static_cast<uint16_t> (m_NB));
				Simulator::ScheduleNow (&PLC_Mac::RandomBackoffDelay, this); //Perform another backoff
			}
		}
	}
	else
	{
		NotifyCcaConfirm(status);
	}
}

void
PLC_Mac::CsmaCaConfirm (PLC_CsmaCaState state)
{
	PLC_MAC_FUNCTION(this);
	m_csmaca_active = false;
	NotifyCsmaCaConfirm (state);
}

void
PLC_Mac::SetMacDataCallback (PLC_MacDataCallback c)
{
	PLC_MAC_FUNCTION (this);
	m_data_callback = c;
}


void
PLC_Mac::SetTransmissionFailedCallback (PLC_MacTransmissionFailedCallback c)
{
	PLC_MAC_FUNCTION (this);
	m_transmission_failed_callback = c;
}

void
PLC_Mac::SetPromiscuousMacDataCallback (PLC_MacDataCallback c)
{
	PLC_MAC_FUNCTION (this);
	m_promiscuous_data_callback = c;
}

void
PLC_Mac::SetMacAcknowledgementCallback (PLC_MacAcknowledgementCallback c)
{
	PLC_MAC_FUNCTION (this);
	m_acknowledgement_callback = c;
}

void
PLC_Mac::SetAddress (Mac48Address addr)
{
	NS_LOG_FUNCTION (this << addr);

	if  (mac_list.find (addr) != mac_list.end ())
	{
		NS_ABORT_MSG ("PLC_Mac::SetAddress: address " << addr << " has already been asigned to another device!");
	}
	m_address = addr;
	mac_list[addr] = Ptr<PLC_Mac>  (this);
}

Mac48Address
PLC_Mac::GetAddress (void)
{
	PLC_MAC_FUNCTION (this << m_address);
	return m_address;
}

void
PLC_Mac::SetBroadcastAddress (Mac48Address addr)
{
	m_broadcast_address = addr;
}

Mac48Address
PLC_Mac::GetBroadcastAddress (void)
{
	return m_broadcast_address;
}

void
PLC_Mac::SetMulticastAddress (Mac48Address addr)
{
	m_multicast_address = addr;
}

Mac48Address
PLC_Mac::GetMulticastAddress (void)
{
	return m_multicast_address;
}

void
PLC_Mac::SetPhy(Ptr<PLC_Phy> phy)
{
//	PLC_MAC_FUNCTION (this);
	DoSetPhy(phy);
}

Ptr<PLC_Phy>
PLC_Mac::GetPhy (void)
{
//	PLC_MAC_FUNCTION (this);
	return DoGetPhy();
}

bool
PLC_Mac::Send (Ptr<Packet> p, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this << p << dst);
	return SendFrom (p, GetAddress(), dst);
}

bool
PLC_Mac::SendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this << p << src << dst);
	return DoSendFrom (p, src, dst);
}

void
PLC_Mac::NotifyReceptionEndOk (Ptr<const Packet> p, uint16_t messageId)
{
	PLC_MAC_FUNCTION (this);
	PLC_MAC_INFO ("Received packet: " << *p);

	DoProcess (p);
}

void
PLC_Mac::SendAcknowledgement (Mac48Address src, uint16_t sequence_number)
{
	PLC_MAC_FUNCTION (this);

	// Send ACK
	PLC_MacHeader ackHeader;
	ackHeader.SetType(PLC_MacHeader::ACK);
	ackHeader.SetSrcAddress (m_address);
	ackHeader.SetDstAddress (src);
	ackHeader.SetSequenceNumber(sequence_number);
	ackHeader.SetMessageLength(0);

	m_ackPacket = Create<Packet> (0);
	m_ackPacket->AddHeader(ackHeader);

	RequestCca ();
}

void
PLC_Mac::SendNegativeAcknowledgement (Mac48Address src, uint16_t sequence_number)
{
	PLC_MAC_FUNCTION (this);

	// Send ACK
	PLC_MacHeader ackHeader;
	ackHeader.SetType(PLC_MacHeader::NACK);
	ackHeader.SetSrcAddress (m_address);
	ackHeader.SetDstAddress (src);
	ackHeader.SetSequenceNumber(sequence_number);
	ackHeader.SetMessageLength(0);

	m_ackPacket = Create<Packet> (0);
	m_ackPacket->AddHeader(ackHeader);

	RequestCca ();
}

void
PLC_Mac::TriggerTransmission (void)
{
	PLC_MAC_FUNCTION (this);

	Ptr<const Packet> p;

	if (m_ackPacket)
	{
		// Acknowledgement packet has higher priority
		p = m_ackPacket;

		// debug
		NS_LOG_DEBUG ("Sending ack: " << *p);
	}
	else if (m_txQueue->IsEmpty() == false)
	{
		p = m_txQueue->Peek()->GetPacket();

		// debug
		NS_LOG_DEBUG ("Sending data: " << *p);
	}
	else
	{
		PLC_MAC_LOGIC("No packet to send");
		return;
	}

	PLC_MAC_LOGIC ("Triggering transmission of packet " << *p);

	if (GetPhy ()->InitializeTx (p) == false)
	{
		PLC_MAC_LOGIC ("PHY rejected transmission");
	}
}

void
PLC_Mac::ForwardUp(Ptr<Packet> p, Mac48Address src, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this);

	if (m_forward_up)
	{
		PLC_MAC_LOGIC ("Forwarding up: " << *p);

		if (!m_data_callback.IsNull())
		{
			PLC_LOG_LOGIC("Forwarding up: " << *p);
			m_data_callback(p, src, dst);
		}
	}
	else
	{
		PLC_MAC_LOGIC ("Forwarding up is deactivated");
	}
}

//////////////////////////////// PLC_ArqMac /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_ArqMac);

TypeId
PLC_ArqMac::GetTypeId  (void)
{
  static TypeId tid = TypeId  ("ns3::PLC_ArqMac")
    .SetParent<PLC_Mac>  ()
    .AddConstructor<PLC_ArqMac> ()
    ;
    return tid;
}

PLC_ArqMac::PLC_ArqMac (void)
{
	Ptr<UniformRandomVariable> u = CreateObject<UniformRandomVariable>();
	m_sequence_number = u->GetInteger(0, 65535);
	m_timeout = Seconds(1);
	m_max_replays = 1000;
	m_replays = 0;
}

void
PLC_ArqMac::DoInitialize (void)
{
	PLC_MAC_FUNCTION (this);
	PLC_Mac::DoInitialize ();
}

void
PLC_ArqMac::DoDispose (void)
{
	PLC_MAC_FUNCTION (this);
	m_timeoutEvent.Cancel ();
	PLC_Mac::DoDispose ();
}

bool
PLC_ArqMac::DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this << p << src << dst);
	NS_ASSERT_MSG (m_phy, "Phy not set!");
	PLC_MAC_INFO ("Packet to send: " << *p);

	Ptr<Packet> txPacket = p->Copy ();
	m_txHeader.SetType(PLC_MacHeader::DATA);
	m_txHeader.SetSrcAddress(src);
	m_txHeader.SetDstAddress(dst);
	m_txHeader.SetMessageLength(p->GetSize());
	m_txHeader.SetSequenceNumber(m_sequence_number++);
	txPacket->AddHeader(m_txHeader);

	if (!m_txQueue->Enqueue (Ptr<QueueItem>(new QueueItem(txPacket))))
	{
		PLC_MAC_LOGIC ("TX queue full, packet dropped");
		return false;
	}

	PLC_MAC_LOGIC ("Triggering CSMA/CA...");
	InitializeCsmaCa();

	return true;
}

void
PLC_ArqMac::DoProcess (Ptr<const Packet> p)
{
	PLC_MAC_FUNCTION (this << p);

	PLC_MAC_LOGIC ("Received packet: " << *p);

	m_rxPacket = p->Copy ();
	m_rxPacket->RemoveHeader (m_rxHeader);

	if (m_rxHeader.GetHasRelayHeader ())
	{
		PLC_RelayMacHeader relayHeader;
		m_rxPacket->RemoveHeader (relayHeader);
	}

	Mac48Address src_addr = m_rxHeader.GetSrcAddress ();
	Mac48Address dst_addr = m_rxHeader.GetDstAddress ();

	if (dst_addr == m_address)
	{
		PLC_MAC_INFO ("Packet is for me");

		if (m_rxHeader.GetType() == PLC_MacHeader::DATA)
		{
			PLC_MAC_INFO ("Received data frame, forwarding up...");
			ForwardUp(m_rxPacket, src_addr, dst_addr);

			PLC_MAC_INFO ("Sending ACK...");
			SendAcknowledgement (src_addr, m_rxHeader.GetSequenceNumber());
		}
		else if (
					m_rxHeader.GetType () == PLC_MacHeader::ACK &&
					m_txQueue->IsEmpty () == false
				 )
		{
			Ptr<const Packet> lastTxPacket = m_txQueue->Peek ()->GetPacket();
			PLC_MacHeader txMacHdr;
			lastTxPacket->PeekHeader(txMacHdr);

			if (m_rxHeader.GetSequenceNumber() == txMacHdr.GetSequenceNumber())
			{
				PLC_MAC_INFO ("Received ACK");
				NotifyAcknowledgement ();
			}
		}
	}
	else if (dst_addr == GetBroadcastAddress ())
	{
		PLC_MAC_INFO ("Broadcast MAC address, forwarding up...");
		ForwardUp (m_rxPacket, src_addr, dst_addr);
	}
	else if (dst_addr == GetMulticastAddress ())
	{
		PLC_MAC_INFO ("Multicast MAC address, forwarding up...");
		ForwardUp (m_rxPacket, src_addr, dst_addr);
	}
	else if (m_promiscuous_mode && m_rxHeader.GetType() == PLC_MacHeader::DATA)
	{
		PLC_MAC_INFO ("Promiscuous mode, forwarding up...");
		ForwardUp (m_rxPacket, src_addr, dst_addr);
	}
	else
	{
		PLC_MAC_INFO ("Packet not for me, discarding...");
		m_rxPacket = 0;
	}
}

void
PLC_ArqMac::DoSetPhy (Ptr<PLC_Phy> phy)
{
	NS_ASSERT_MSG(phy->GetInstanceTypeId().IsChildOf(PLC_HalfDuplexOfdmPhy::GetTypeId()), "Phy instance has to be a subclass of type PLC_HalfDuplexOfdmPhy!");
	m_phy = StaticCast<PLC_HalfDuplexOfdmPhy, PLC_Phy> (phy);

	m_phy->SetReceiveSuccessCallback(MakeCallback(&PLC_Mac::NotifyReceptionEndOk, this));
	m_phy->SetFrameSentCallback(MakeCallback(&PLC_Mac::NotifyTransmissionEnd, this));
	m_phy->SetCcaConfirmCallback(MakeCallback(&PLC_Mac::CcaConfirm, this));

	SetCcaRequestCallback(MakeCallback(&PLC_HalfDuplexOfdmPhy::CcaRequest, m_phy));
}

Ptr<PLC_Phy>
PLC_ArqMac::DoGetPhy (void)
{
	NS_LOG_FUNCTION (this);
	NS_ASSERT_MSG(m_phy, "Phy not set");
	return m_phy;
}

void
PLC_ArqMac::NotifyAcknowledgement (void)
{
	PLC_MAC_FUNCTION (this);

	m_timeoutEvent.Cancel ();
	m_requestCCAEvent.Cancel ();
	m_backoffEndEvent.Cancel ();

	m_txQueue->Dequeue ();

	if (!m_acknowledgement_callback.IsNull())
	{
		m_acknowledgement_callback();
	}

	if (m_txQueue->IsEmpty() == false)
	{
		PLC_MAC_LOGIC ("Initializeing CSMA/CA for next packet to send...");
		InitializeCsmaCa ();
	}
}

void
PLC_ArqMac::NotifyCcaConfirm (PLC_PhyCcaResult status)
{
	PLC_MAC_FUNCTION (this << status);

	if (!m_csmaca_active)
	{
		if (status == CHANNEL_CLEAR)
		{
			NS_LOG_LOGIC ("Channel clear, start sending packet...");
			TriggerTransmission ();
		}
		else
		{
			NS_LOG_LOGIC ("Channel occupied, starting CSMA/CA...");
			InitializeCsmaCa ();
		}
	}
}

void
PLC_ArqMac::NotifyCsmaCaConfirm (PLC_CsmaCaState state)
{
	PLC_MAC_FUNCTION (this);
	PLC_MAC_LOGIC ("CsmaCaConfirm, status: " << state);

	if (state == CHANNEL_IDLE)
	{
		TriggerTransmission ();
		m_csmaca_attempts = 0;
	}
	else
	{
		PLC_MAC_LOGIC ("Channel access failure");
		if  (m_phy != NULL)
		{
			// reschedule CSMA/CA
			if (m_csmaca_attempts++ < MAX_CSMACA_ATTEMPTS)
			{
				PLC_MAC_LOGIC("Entering CSMA/CA round " << m_csmaca_attempts);
				Simulator::ScheduleNow (&PLC_Mac::InitializeCsmaCa, this);
			}
			else
			{
				// TODO CsmaCa failure callback
				PLC_MAC_LOGIC("Max CsmaCa attempts reached");
				m_csmaca_attempts = 0;
			}
		}
	}
}

void
PLC_ArqMac::NotifyTransmissionEnd (void)
{
	PLC_MAC_FUNCTION (this);

	if (m_ackPacket)
	{
		PLC_MAC_LOGIC ("Acknowledgement frame sent");
		m_ackPacket = 0;

		if (m_txQueue->IsEmpty () == false)
		{
			PLC_MAC_LOGIC ("Initializeing CSMA/CA for next frame to be sent...");
			InitializeCsmaCa ();
		}
	}
	else
	{
		// Data frame sent
		Ptr<const Packet> p = m_txQueue->Peek ()->GetPacket();
		NS_ASSERT_MSG (p, "No packet in send queue, something went wrong!");

		PLC_MacHeader macHdr;
		p->PeekHeader(macHdr);

		if 	(
			macHdr.GetDstAddress () == GetBroadcastAddress () ||
			macHdr.GetDstAddress () == GetMulticastAddress ()
			)
		{
			// Don't wait for broadcast/multicast acknowledgements
			m_txQueue->Dequeue ();
		}
		else
		{
			PLC_MAC_LOGIC ("Winding up acknowledgement timeout clock...");

                        if (m_timeoutEvent.IsRunning ())
			{
				m_timeoutEvent.Cancel ();
			}

			m_timeoutEvent = Simulator::Schedule (m_timeout, &PLC_ArqMac::AcknowledgementTimeout, this);
		}
	}
}

void
PLC_ArqMac::AcknowledgementTimeout(void)
{
	PLC_MAC_FUNCTION (this);
	if (m_txQueue->IsEmpty () == false)
	{
		PLC_MAC_LOGIC ("Acknowledgement timeout");

		if (m_replays++ <= m_max_replays)
		{
			PLC_MAC_LOGIC ("Triggering CSMA/CA for frame replay...");
			InitializeCsmaCa ();
		}
		else
		{
			PLC_MAC_INFO ("Maximum replays reached, transmission failed!");
			Ptr<const Packet> p = m_txQueue->Dequeue()->GetPacket();
			m_replays = 0;

			if (!m_transmission_failed_callback.IsNull())
			{
				m_transmission_failed_callback (p);
			}

			if (m_txQueue->IsEmpty () == false)
			{
				InitializeCsmaCa ();
			}
		}
	}
}

//////////////////////////////// PLC_HarqMac /////////////////////////////////////////////

NS_OBJECT_ENSURE_REGISTERED (PLC_HarqMac);

TypeId
PLC_HarqMac::GetTypeId  (void)
{
  static TypeId tid = TypeId  ("ns3::PLC_HarqMac")
    .SetParent<PLC_Mac>  ()
    .AddConstructor<PLC_HarqMac> ()
    ;
    return tid;
}

PLC_HarqMac::PLC_HarqMac (void)
{
	m_send_redundancy = false;
	Ptr<UniformRandomVariable> u = CreateObject<UniformRandomVariable>();
	m_sequence_number = u->GetInteger(0, 65535);
	m_acknowledgement_timeout = MicroSeconds(100);
	m_max_redundancy_frames = 1000;
	m_sent_redundancy_frames = 0;
}

void
PLC_HarqMac::DoInitialize (void)
{
	PLC_MAC_FUNCTION (this);
	PLC_Mac::DoInitialize ();
}

void
PLC_HarqMac::DoDispose (void)
{
	PLC_MAC_FUNCTION (this);
	m_acknowledgementTimeoutEvent.Cancel ();
	PLC_Mac::DoDispose ();
}

bool
PLC_HarqMac::DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this << p << src << dst);
	NS_ASSERT_MSG (m_phy, "Phy not set!");
	PLC_MAC_INFO ("Packet to send: " << *p);

	Ptr<Packet> txPacket = p->Copy ();
	m_txHeader.SetType(PLC_MacHeader::DATA);
	m_txHeader.SetSrcAddress(src);
	m_txHeader.SetDstAddress(dst);
	m_txHeader.SetMessageLength(p->GetSize());
	m_txHeader.SetSequenceNumber(m_sequence_number++);
	txPacket->AddHeader(m_txHeader);

	if (!m_txQueue->Enqueue(Ptr<QueueItem>(new QueueItem(txPacket))))
	{
		PLC_MAC_LOGIC ("TX queue full, packet dropped");
		return false;
	}

	m_send_redundancy = false;
	PLC_MAC_LOGIC ("Triggering CSMA/CA...");
	InitializeCsmaCa();

	return true;
}

void
PLC_HarqMac::DoProcess (Ptr<const Packet> p)
{
	PLC_MAC_FUNCTION (this << p);

	// debug
	NS_LOG_DEBUG ("Received frame: " << *p);

	m_rxPacket = p->Copy();
	m_rxPacket->RemoveHeader(m_rxHeader);

	if (m_rxHeader.GetHasRelayHeader())
	{
		PLC_RelayMacHeader relayHeader;
		m_rxPacket->RemoveHeader (relayHeader);
	}

	Mac48Address src_addr = m_rxHeader.GetSrcAddress ();
	Mac48Address dst_addr = m_rxHeader.GetDstAddress ();

	if (dst_addr == m_address)
	{
		PLC_MAC_INFO ("Packet is for me");

		if (m_rxHeader.GetType() == PLC_MacHeader::DATA)
		{
			PLC_MAC_INFO ("Received data frame, forwarding up...");
			ForwardUp(m_rxPacket, src_addr, dst_addr);

			PLC_MAC_INFO ("Sending acknowledgement...");
			SendAcknowledgement (src_addr, m_rxHeader.GetSequenceNumber());
		}
		else if (
					m_rxHeader.GetType () == PLC_MacHeader::ACK &&
					m_txQueue->IsEmpty () == false
				 )
		{
			Ptr<const Packet> lastTxPacket = m_txQueue->Peek ()->GetPacket();
			PLC_MacHeader txMacHdr;
			lastTxPacket->PeekHeader(txMacHdr);

			if (m_rxHeader.GetSequenceNumber() == txMacHdr.GetSequenceNumber())
			{
				PLC_MAC_INFO ("Received ACK");
				NotifyAcknowledgement ();
			}
		}
		else if (
					m_rxHeader.GetType () == PLC_MacHeader::NACK &&
					m_txQueue->IsEmpty () == false
				 )
		{
			Ptr<const Packet> lastTxPacket = m_txQueue->Peek ()->GetPacket();
			PLC_MacHeader txMacHdr;
			lastTxPacket->PeekHeader(txMacHdr);

			if (m_rxHeader.GetSequenceNumber() == txMacHdr.GetSequenceNumber())
			{
				PLC_MAC_INFO ("Received NACK");
				NotifyNegativeAcknowledgement ();
			}
		}
	}
	else if (dst_addr == GetBroadcastAddress ())
	{
		PLC_MAC_INFO ("Broadcast MAC address, forwarding up...");
		ForwardUp (m_rxPacket, src_addr, dst_addr);
	}
	else if (dst_addr == GetMulticastAddress ())
	{
		PLC_MAC_INFO ("Multicast MAC address, forwarding up...");
		ForwardUp (m_rxPacket, src_addr, dst_addr);
	}
	else if (m_promiscuous_mode && m_rxHeader.GetType() == PLC_MacHeader::DATA)
	{
		PLC_MAC_INFO ("Promiscuous mode, forwarding up...");
		ForwardUp (m_rxPacket, src_addr, dst_addr);
	}
	else
	{
		PLC_MAC_INFO ("Packet not for me, discarding...");
		m_rxPacket = 0;
	}
}

void
PLC_HarqMac::DoSetPhy (Ptr<PLC_Phy> phy)
{
	NS_ASSERT_MSG(phy->GetInstanceTypeId().IsChildOf(PLC_InformationRatePhy::GetTypeId()), "PHY instance has to be a subclass of PLC_InformationRatePhy!");
	m_phy = StaticCast<PLC_InformationRatePhy, PLC_Phy> (phy);

	m_phy->SetReceiveSuccessCallback(MakeCallback(&PLC_Mac::NotifyReceptionEndOk, this));
	m_phy->SetFrameSentCallback(MakeCallback(&PLC_Mac::NotifyTransmissionEnd, this));
	m_phy->SetCcaConfirmCallback(MakeCallback(&PLC_Mac::CcaConfirm, this));

	SetCcaRequestCallback(MakeCallback(&PLC_HalfDuplexOfdmPhy::CcaRequest, m_phy));
}

Ptr<PLC_Phy>
PLC_HarqMac::DoGetPhy (void)
{
//	PLC_MAC_FUNCTION (this);
	NS_ASSERT_MSG(m_phy, "Phy not set");
	return m_phy;
}

void
PLC_HarqMac::NotifyCcaConfirm (PLC_PhyCcaResult status)
{
	PLC_MAC_FUNCTION (this << status);

	if (!m_csmaca_active)
	{
		if (status == CHANNEL_CLEAR)
		{
			NS_LOG_LOGIC ("Channel clear, start sending packet...");
			TriggerTransmission ();
		}
		else
		{
			NS_LOG_LOGIC ("Channel occupied, starting CSMA/CA...");
			InitializeCsmaCa ();
		}
	}
}

void
PLC_HarqMac::NotifyCsmaCaConfirm (PLC_CsmaCaState state)
{
	PLC_MAC_FUNCTION (this);

	PLC_MAC_LOGIC ("CsmaCaConfirm, status: " << state);

	if (state == CHANNEL_IDLE)
	{
		TriggerTransmission ();
		m_csmaca_attempts = 0;
	}
	else
	{
		PLC_MAC_LOGIC ("Channel access failure");
		if  (m_phy != NULL)
		{
			// reschedule CSMA/CA
			if (m_csmaca_attempts++ < MAX_CSMACA_ATTEMPTS)
			{
				PLC_MAC_LOGIC("Entering CSMA/CA round " << m_csmaca_attempts);
				Simulator::ScheduleNow (&PLC_Mac::InitializeCsmaCa, this);
			}
			else
			{
				// TODO CsmaCa failure callback
				PLC_MAC_LOGIC("Max CsmaCa attempts reached");
				m_csmaca_attempts = 0;
			}
		}
	}
}

void
PLC_HarqMac::TriggerTransmission (void)
{
	PLC_MAC_FUNCTION (this);

	Ptr<const Packet> p;

	if (m_ackPacket)
	{
		// Acknowledgement packet has highest priority
		p = m_ackPacket;
	}
	else if (m_send_redundancy)
	{
		PLC_MAC_LOGIC ("Channel idle, start sending redundancy frame");
		if (!m_phy->SendRedundancy())
		{
			PLC_MAC_LOGIC ("PHY rejected to start transmitting");
		}

		return;
	}
	else if (m_txQueue->IsEmpty() == false)
	{
		p = m_txQueue->Peek ()->GetPacket();
		m_sent_redundancy_frames = 0;
	}
	else
	{
		PLC_MAC_LOGIC("No packet to send");
		return;
	}

	PLC_MAC_LOGIC ("Triggering transmission of packet " << *p);

	if (GetPhy ()->InitializeTx (p) == false)
	{
		// debug
		NS_LOG_DEBUG ("PHY rejected transmission");

		PLC_MAC_LOGIC ("PHY rejected transmission");
	}
}

void
PLC_HarqMac::NotifyTransmissionEnd (void)
{
	PLC_MAC_FUNCTION (this);

	if (m_ackPacket)
	{
		PLC_MAC_LOGIC ("Acknowledgement frame sent");
		m_ackPacket = 0;

		if (m_txQueue->IsEmpty () == false)
		{
			PLC_MAC_LOGIC ("Initializeing CSMA/CA for next frame to be sent...");
			InitializeCsmaCa ();
		}
	}
	else
	{
		// Data frame sent
		Ptr<const Packet> p = m_txQueue->Peek ()->GetPacket();
		NS_ASSERT_MSG (p, "No packet in send queue, something went wrong!");

		PLC_MacHeader macHdr;
		p->PeekHeader(macHdr);

		if 	(
			macHdr.GetDstAddress () == GetBroadcastAddress () ||
			macHdr.GetDstAddress () == GetMulticastAddress ()
			)
		{
			// Don't wait for broadcast/multicast acknowledgements
			m_txQueue->Dequeue();
		}
		else
		{
			PLC_MAC_LOGIC ("Winding up acknowledgement timeout clock...");

			if (m_acknowledgementTimeoutEvent.IsRunning ())
			{
				m_acknowledgementTimeoutEvent.Cancel ();
			}

			m_acknowledgementTimeoutEvent = Simulator::Schedule (m_acknowledgement_timeout, &PLC_HarqMac::AcknowledgementTimeout, this);
		}
	}
}

void
PLC_HarqMac::AcknowledgementTimeout(void)
{
	PLC_MAC_FUNCTION (this);
	if (m_txQueue->IsEmpty () == false)
	{
		PLC_MAC_LOGIC ("Acknowledgement timeout");

		if (m_sent_redundancy_frames++ <= m_max_redundancy_frames)
		{
			PLC_MAC_LOGIC ("Triggering CSMA/CA for redundancy transmission...");

			// debug
			NS_LOG_DEBUG ("send redundancy: true");

			m_send_redundancy = true;
			InitializeCsmaCa ();
		}
		else
		{
			PLC_MAC_INFO ("Maximum replays reached, transmission failed!");

			Ptr<const Packet> p = m_txQueue->Dequeue ()->GetPacket();
			m_sent_redundancy_frames = 0;
			m_send_redundancy = false;

			if (!m_transmission_failed_callback.IsNull())
			{
				m_transmission_failed_callback (p);
			}

			if (m_txQueue->IsEmpty () == false)
			{
				InitializeCsmaCa ();
			}
		}
	}
}

void
PLC_HarqMac::NotifyAcknowledgement (void)
{
	PLC_MAC_FUNCTION (this);

	m_acknowledgementTimeoutEvent.Cancel ();
	m_requestCCAEvent.Cancel ();
	m_backoffEndEvent.Cancel ();

	m_txQueue->Dequeue();
	m_send_redundancy = false;

	if (!m_acknowledgement_callback.IsNull())
	{
		m_acknowledgement_callback();
	}

	if (m_txQueue->IsEmpty() == false)
	{
		PLC_MAC_LOGIC ("Initializeing CSMA/CA for next packet to send...");
		InitializeCsmaCa ();
	}
}

void
PLC_HarqMac::NotifyNegativeAcknowledgement (void)
{
	PLC_MAC_FUNCTION (this);
}

}
