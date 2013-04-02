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
#include <ns3/random-variable.h>
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

	m_csmaca_active = false;
	m_promiscuous_mode = false;
	m_macMinBE = 3;
	m_macMaxBE = 5;
	m_macMaxCSMABackoffs = 4;
	m_aUnitBackoffPeriod = 20; //20 symbols
}

PLC_Mac::~PLC_Mac ()
{
}

void
PLC_Mac::DoStart (void)
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
	m_transmission_failed_callback = MakeNullCallback<void> ();
	m_cca_request_callback = MakeNullCallback<void> ();
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
	if (!m_cca_request_callback.IsNull())
	{
		m_cca_request_callback();
	}
}

void
PLC_Mac::StartCsmaCa (void)
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

	UniformVariable uniformVar;
	uint64_t upperBound = (uint64_t) pow (2, m_BE) - 1;
	uint64_t backoffPeriod;
	Time randomBackoff;

	uniformVar = UniformVariable (0, upperBound);
	backoffPeriod = (uint64_t)uniformVar.GetValue (); //num backoff periods
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
	DoSetPhy(phy);
}

Ptr<PLC_Phy>
PLC_Mac::GetPhy (void)
{
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
PLC_Mac::NotifyReceptionEndOk (Ptr<const Packet> p)
{
	PLC_MAC_FUNCTION (this);
	PLC_MAC_INFO ("Received packet");
	PLC_MAC_DEBUG ("Frame: " << *p);

	DoProcess (p);
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
	m_awaiting_ack = false;
	m_txPacket = 0;
	m_rxPacket = 0;
	UniformVariable u;
	m_sequence_number = u.GetInteger(0, 65535);
	m_timeout = MilliSeconds(100);
	m_max_replays = 10;
	m_replays = 0;
}

void
PLC_ArqMac::DoStart (void)
{
	PLC_MAC_FUNCTION (this);
	PLC_Mac::DoStart ();
}

void
PLC_ArqMac::DoDispose (void)
{
	PLC_MAC_FUNCTION (this);
	m_txPacket = 0;
	m_rxPacket = 0;
	m_timeoutEvent.Cancel ();
	PLC_Mac::DoDispose ();
}

bool
PLC_ArqMac::DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this << p << src << dst);
	NS_ASSERT_MSG (m_phy, "Phy not set!");
	PLC_MAC_INFO ("Packet to send: " << *p);

	if (m_awaiting_ack)
	{
		// TODO: implement send queue
		PLC_MAC_INFO ("Last sent frame has not been acknowledged yet, cannot send new frame...");
		return false;
	}

	m_txPacket = p;
	m_txHeader.SetType(PLC_MacHeader::DATA);
	m_txHeader.SetSrcAddress(src);
	m_txHeader.SetDstAddress(dst);
	m_txHeader.SetMessageLength(p->GetSize());
	m_txHeader.SetSequenceNumber(m_sequence_number++);
	m_txPacket->AddHeader(m_txHeader);

	m_awaiting_ack = true;
	m_replays = 0;

	PLC_MAC_INFO ("Triggering CSMA/CA...");
	StartCsmaCa();

	return true;
}

void
PLC_ArqMac::DoProcess (Ptr<const Packet> p)
{
	PLC_MAC_FUNCTION (this << p);
	PLC_MAC_INFO ("Received packet: " << *p);

	m_rxPacket = p->Copy();
	m_rxPacket->RemoveHeader(m_rxHeader);

	Mac48Address src_addr = m_rxHeader.GetSrcAddress ();
	Mac48Address dst_addr = m_rxHeader.GetDstAddress ();

	if (dst_addr == m_address)
	{
		PLC_MAC_INFO ("Packet is for me");

		if (m_rxHeader.GetType() == PLC_MacHeader::DATA)
		{
			PLC_MAC_INFO ("Received data frame, forwarding up and sending ACK...");

			if (!m_data_callback.IsNull())
			{
				PLC_LOG_LOGIC("Forwarding up: " << *m_rxPacket);
				m_data_callback(m_rxPacket, src_addr, dst_addr);
			}

			// Send ACK
			m_txHeader.SetType(PLC_MacHeader::ACK);
			m_txHeader.SetSrcAddress (m_address);
			m_txHeader.SetDstAddress (src_addr);
			m_txHeader.SetSequenceNumber(m_rxHeader.GetSequenceNumber());
			m_txHeader.SetMessageLength(0);

			m_txPacket = Create<Packet> (0);
			m_txPacket->AddHeader(m_txHeader);

			m_awaiting_ack = false;

			RequestCca ();
		}
		else if (
				m_awaiting_ack &&
				m_rxHeader.GetType() == PLC_MacHeader::ACK &&
				m_rxHeader.GetSequenceNumber() == m_txHeader.GetSequenceNumber()
				)
		{
			PLC_MAC_INFO ("Received ACK");

			m_awaiting_ack = false;
			m_timeoutEvent.Cancel();

			if (!m_acknowledgement_callback.IsNull())
			{
				m_acknowledgement_callback();
			}
		}
	}
	else if (m_promiscuous_mode && m_rxHeader.GetType() == PLC_MacHeader::DATA)
	{
		PLC_MAC_INFO ("Promiscuous mode, forwarding up...");
		if (!m_data_callback.IsNull())
		{
			m_data_callback(m_rxPacket, src_addr, dst_addr);
		}
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
	NS_ASSERT_MSG(m_phy, "Phy not set");
	return m_phy;
}

void
PLC_ArqMac::NotifyCcaConfirm (PLC_PhyCcaResult status)
{
	PLC_MAC_FUNCTION (this << status);

	if (!m_csmaca_active && status == CHANNEL_CLEAR)
	{
		if (m_phy != NULL)
		{
			if (m_txPacket)
			{
				PLC_MAC_INFO ("Channel Idle, start sending packet " << m_txPacket);
				if (!m_phy->StartTx(m_txPacket))
				{
					PLC_MAC_LOGIC ("PHY rejected to start transmitting");
				}
			}
			else
			{
				PLC_MAC_LOGIC("No packet to send");
			}
		}
		else
		{
			NS_LOG_UNCOND ("PHY not set, cannot send datagram");
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
		if (m_phy != NULL)
		{
			if (m_txPacket)
			{
				PLC_MAC_INFO ("Channel Idle, start sending packet " << m_txPacket);
				if (!m_phy->StartTx(m_txPacket))
				{
					PLC_MAC_LOGIC ("PHY rejected to start transmitting");
				}
			}
			else
			{
				PLC_MAC_LOGIC("No packet to send");
			}
		}
		else
		{
			NS_LOG_UNCOND ("PHY not set, cannot send datagram");
		}
	}
	else
	{
		PLC_MAC_LOGIC ("Channel access failure");
		if  (m_phy != NULL)
		{
			// reschedule CSMA/CA
			if (m_csmaca_attempts++ < MAX_CSMACA_ATTEMPTS)
			{
				PLC_MAC_LOGIC("CSMA/CA attempt " << m_csmaca_attempts);
				Simulator::ScheduleNow (&PLC_Mac::StartCsmaCa, this);
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

	if (m_awaiting_ack)
	{
		PLC_MAC_INFO ("Winding up timeout clock...");
		m_timeoutEvent = Simulator::Schedule (m_timeout, &PLC_ArqMac::AcknowledgementTimeout, this);
	}
}

void
PLC_ArqMac::AcknowledgementTimeout(void)
{
	PLC_MAC_FUNCTION (this);
	if (m_awaiting_ack)
	{
		PLC_MAC_INFO ("Acknowledgement timeout");

		if (m_replays++ <= m_max_replays)
		{
			PLC_MAC_INFO ("Triggering CSMA/CA for frame replay...");
			StartCsmaCa ();
		}
		else
		{
			PLC_MAC_INFO ("Maximum replays reached, transmission failed!");
			m_awaiting_ack = false;
			m_replays = 0;

			if (!m_transmission_failed_callback.IsNull())
			{
				m_transmission_failed_callback ();
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
	m_awaiting_ack = false;
	m_txPacket = 0;
	m_rxPacket = 0;
	UniformVariable u;
	m_sequence_number = u.GetInteger(0, 65535);
	m_acknowledgement_timeout = MicroSeconds(100);
	m_max_redundancy_frames = 10;
	m_sent_redundancy_frames = 0;
}

void
PLC_HarqMac::DoStart (void)
{
	PLC_MAC_FUNCTION (this);
	PLC_Mac::DoStart ();
}

void
PLC_HarqMac::DoDispose (void)
{
	PLC_MAC_FUNCTION (this);
	m_txPacket = 0;
	m_rxPacket = 0;
	m_acknowledgementTimeoutEvent.Cancel ();
	PLC_Mac::DoDispose ();
}

bool
PLC_HarqMac::DoSendFrom (Ptr<Packet> p, Mac48Address src, Mac48Address dst)
{
	PLC_MAC_FUNCTION (this << p << src << dst);
	NS_ASSERT_MSG (m_phy, "Phy not set!");
	PLC_MAC_INFO ("Packet to send: " << *p);

	if (m_awaiting_ack)
	{
		// TODO: implement send queue
		PLC_MAC_INFO ("Last sent frame has not been acknowledged yet, cannot send new frame...");
		return false;
	}

	m_txPacket = p;
	m_txHeader.SetType(PLC_MacHeader::DATA);
	m_txHeader.SetSrcAddress(src);
	m_txHeader.SetDstAddress(dst);
	m_txHeader.SetMessageLength(p->GetSize());
	m_txHeader.SetSequenceNumber(m_sequence_number++);
	m_txPacket->AddHeader(m_txHeader);

	m_awaiting_ack = true;
	m_sent_redundancy_frames = 0;

	PLC_MAC_INFO ("Triggering CSMA/CA...");
	StartCsmaCa();

	return true;
}

void
PLC_HarqMac::DoProcess (Ptr<const Packet> p)
{
	PLC_MAC_FUNCTION (this << p);
	PLC_MAC_INFO ("Received packet: " << *p);

	m_rxPacket = p->Copy();
	m_rxPacket->RemoveHeader(m_rxHeader);

	Mac48Address src_addr = m_rxHeader.GetSrcAddress ();
	Mac48Address dst_addr = m_rxHeader.GetDstAddress ();

	if (dst_addr == m_address)
	{
		PLC_MAC_INFO ("Packet is for me");

		if (m_rxHeader.GetType() == PLC_MacHeader::DATA)
		{
			PLC_MAC_INFO ("Received data frame, forwarding up and sending ACK...");

			if (!m_data_callback.IsNull())
			{
				PLC_LOG_LOGIC("Forwarding up: " << *m_rxPacket);
				m_data_callback(m_rxPacket, src_addr, dst_addr);
			}

			// Send ACK
			m_txHeader.SetType(PLC_MacHeader::ACK);
			m_txHeader.SetSrcAddress (m_address);
			m_txHeader.SetDstAddress (src_addr);
			m_txHeader.SetSequenceNumber(m_rxHeader.GetSequenceNumber());
			m_txHeader.SetMessageLength(0);

			m_txPacket = Create<Packet> (0);
			m_txPacket->AddHeader(m_txHeader);

			m_awaiting_ack = false;

			RequestCca ();
		}
		else if (
				m_awaiting_ack &&
				m_rxHeader.GetType() == PLC_MacHeader::ACK &&
				m_rxHeader.GetSequenceNumber() == m_txHeader.GetSequenceNumber()
				)
		{
			PLC_MAC_INFO ("Received ACK");

			m_awaiting_ack = false;
			m_acknowledgementTimeoutEvent.Cancel ();

			if (!m_acknowledgement_callback.IsNull())
			{
				m_acknowledgement_callback();
			}
		}
	}
	else if (m_promiscuous_mode && m_rxHeader.GetType() == PLC_MacHeader::DATA)
	{
		PLC_MAC_INFO ("Promiscuous mode, forwarding up...");
		if (!m_data_callback.IsNull())
		{
			m_data_callback(m_rxPacket, src_addr, dst_addr);
		}
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
	NS_ASSERT_MSG(m_phy, "Phy not set");
	return m_phy;
}

void
PLC_HarqMac::NotifyCcaConfirm (PLC_PhyCcaResult status)
{
	PLC_MAC_FUNCTION (this << status);

	if (!m_csmaca_active && status == CHANNEL_CLEAR)
	{
		if (m_phy != NULL)
		{
			if (m_awaiting_ack)
			{
				PLC_MAC_LOGIC ("Channel idle, start sending redundancy frame ");
				if (!m_phy->SendRedundancy())
				{
					PLC_MAC_LOGIC ("PHY rejected to start transmitting");
				}
			}
			else if (m_txPacket)
			{
				PLC_MAC_LOGIC ("Channel idle, start sending frame " << *m_txPacket);
				if (!m_phy->StartTx(m_txPacket))
				{
					PLC_MAC_LOGIC ("PHY rejected to start transmitting");
				}
			}
			else
			{
				PLC_MAC_LOGIC("No packet to send");
			}
		}
		else
		{
			NS_LOG_UNCOND ("PHY not set, cannot send datagram");
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
		if (m_phy != NULL)
		{
			if (m_txPacket)
			{
				PLC_MAC_INFO ("Channel Idle, start sending packet " << m_txPacket);
				if (!m_phy->StartTx(m_txPacket))
				{
					PLC_MAC_LOGIC ("PHY rejected to start transmitting");
				}
			}
			else
			{
				PLC_MAC_LOGIC("No packet to send");
			}
		}
		else
		{
			NS_LOG_UNCOND ("PHY not set, cannot send datagram");
		}
	}
	else
	{
		PLC_MAC_LOGIC ("Channel access failure");
		if  (m_phy != NULL)
		{
			// reschedule CSMA/CA
			if (m_csmaca_attempts++ < MAX_CSMACA_ATTEMPTS)
			{
				PLC_MAC_LOGIC("CSMA/CA attempt " << m_csmaca_attempts);
				Simulator::ScheduleNow (&PLC_Mac::StartCsmaCa, this);
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
PLC_HarqMac::NotifyTransmissionEnd (void)
{
	PLC_MAC_FUNCTION (this);

	if (m_awaiting_ack)
	{
		PLC_MAC_INFO ("Winding up acknowledgement timeout clock...");
		m_acknowledgementTimeoutEvent = Simulator::Schedule (m_acknowledgement_timeout, &PLC_HarqMac::AcknowledgementTimeout, this);
	}
}

void
PLC_HarqMac::AcknowledgementTimeout(void)
{
	PLC_MAC_FUNCTION (this);
	if (m_awaiting_ack)
	{
		PLC_MAC_INFO ("Acknowledgement timeout");

		if (m_sent_redundancy_frames++ <= m_max_redundancy_frames)
		{
			PLC_MAC_INFO ("Requesting CCA to send redundancy frame...");
			RequestCca ();
		}
		else
		{
			PLC_MAC_INFO ("Maximum replays reached, transmission failed!");
			m_awaiting_ack = false;
			m_sent_redundancy_frames = 0;

			if (!m_transmission_failed_callback.IsNull())
			{
				m_transmission_failed_callback ();
			}
		}
	}
}

}
