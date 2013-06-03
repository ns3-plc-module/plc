/*
 * plc-header.cc
 *
 *  Created on: 2012-05-25
 *      Author: deadlock
 */

#include <ns3/address-utils.h>
#include "plc-header.h"

namespace ns3 {

//////////////////////// PLC_Preamble //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_Preamble);

Time PLC_Preamble::preamble_duration = MicroSeconds(10);

TypeId
PLC_Preamble::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_Preamble")
    .SetParent<Header> ()
    .AddConstructor<PLC_Preamble> ();
  return tid;
}

PLC_Preamble::PLC_Preamble (void)
{
}

PLC_Preamble::~PLC_Preamble (void)
{
}

void
PLC_Preamble::SetDuration (Time duration)
{
	preamble_duration = duration;
}

Time
PLC_Preamble::GetDuration (void)
{
	return preamble_duration;
}

uint32_t
PLC_Preamble::GetSerializedSize (void) const
{
	return 0;
}

TypeId
PLC_Preamble::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_Preamble::Serialize (Buffer::Iterator start) const
{
}

uint32_t
PLC_Preamble::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	return i.GetDistanceFrom(start);
}

void
PLC_Preamble::Print (std::ostream &os) const
{
	os << "duration = " << GetDuration();
}

//////////////////////// PLC_PhyFrameControlHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_PhyFrameControlHeader);

TypeId
PLC_PhyFrameControlHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_PhyFrameControlHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_PhyFrameControlHeader> ();
  return tid;
}

PLC_PhyFrameControlHeader::PLC_PhyFrameControlHeader(void)
{
}

PLC_PhyFrameControlHeader::~PLC_PhyFrameControlHeader(void)
{
}

uint32_t
PLC_PhyFrameControlHeader::GetSerializedSize (void) const
{
	return 10;
}

TypeId
PLC_PhyFrameControlHeader::GetInstanceTypeId (void) const
{
	return GetTypeId ();
}

void
PLC_PhyFrameControlHeader::Serialize (Buffer::Iterator start) const
{
	Buffer::Iterator i = start;
	i.WriteU16(m_message_id);
	i.WriteU16(m_payload_symbols);
	i.WriteU8(m_payload_mct);
	i.WriteU16(m_prng_seed);
	i.WriteU16(m_num_blocks);
	i.WriteU8(m_fccs);
}

uint32_t
PLC_PhyFrameControlHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	m_message_id		= i.ReadU16();
	m_payload_symbols 	= i.ReadU16();
	m_payload_mct 		= i.ReadU8();
	m_prng_seed 		= i.ReadU16();
	m_num_blocks 		= i.ReadU16();
	m_fccs 				= i.ReadU8();
	return i.GetDistanceFrom(start);
}

void
PLC_PhyFrameControlHeader::Print (std::ostream &os) const
{
	os << "Message id = " << (int) m_message_id;
	os << ", payload symbols = " << (int) m_payload_symbols;
	os << ", payload mcs = " << (ModulationAndCodingType) m_payload_mct;
	os << ", Prng seed = " << (int) m_prng_seed;
	os << ", Blocks = " << (int) m_num_blocks;
	os << ", fccs = " << (int) m_fccs;
}

//////////////////////// PLC_MacHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_MacHeader);

TypeId
PLC_MacHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_MacHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_MacHeader> ();
  return tid;
}

PLC_MacHeader::PLC_MacHeader(void)
{
	m_flags = 0;
}

PLC_MacHeader::~PLC_MacHeader(void)
{
}

uint32_t
PLC_MacHeader::GetSerializedSize (void) const
{
	return 19;
}

TypeId
PLC_MacHeader::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_MacHeader::Serialize (Buffer::Iterator start) const
{
    Buffer::Iterator i = start;
    WriteTo (i, m_dst_address);
    WriteTo (i, m_src_address);
    i.WriteU8(m_flags);
    i.WriteHtonU16(m_msg_sqn);
	i.WriteHtonU32(m_msg_length);
}

uint32_t
PLC_MacHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	ReadFrom (i, m_dst_address);
	ReadFrom (i, m_src_address);
	m_flags = i.ReadU8();
	m_msg_sqn = i.ReadNtohU16();
	m_msg_length = i.ReadNtohU32();
	return i.GetDistanceFrom(start);
}

void
PLC_MacHeader::Print (std::ostream &os) const
{
	os << "destination address = " << m_dst_address;
	os << ", source address = " << m_src_address;
	os << ", type = " << GetType();
	os << ", sequence number = " << (int) m_msg_sqn;
	os << ", message length = " << (int) m_msg_length;
	os << ", has relay mac header = " << GetHasRelayHeader();
}

void
PLC_MacHeader::SetDstAddress (Mac48Address addr)
{
	m_dst_address = addr;
}

void
PLC_MacHeader::SetSrcAddress (Mac48Address addr)
{
	m_src_address = addr;
}

void
PLC_MacHeader::SetType (PLC_MacHeader::MacHdrType type)
{
	m_flags = (m_flags & 0xf0) | (0x0f & type);
}

void
PLC_MacHeader::SetSequenceNumber (uint16_t sqn)
{
	m_msg_sqn = sqn;
}

void
PLC_MacHeader::SetMessageLength (uint32_t length)
{
	m_msg_length = length;
}

void
PLC_MacHeader::SetHasRelayHeader (bool hasRelayHeader)
{
	uint8_t mask = ((0x1 & hasRelayHeader)<<4) | 0xef;
	m_flags |= mask;
}

Mac48Address
PLC_MacHeader::GetDstAddress (void) const
{
	return m_dst_address;
}

Mac48Address
PLC_MacHeader::GetSrcAddress (void) const
{
	return m_src_address;
}

PLC_MacHeader::MacHdrType
PLC_MacHeader::GetType (void) const
{
	return (PLC_MacHeader::MacHdrType)(m_flags & 0x0f);
}

uint16_t
PLC_MacHeader::GetSequenceNumber (void) const
{
	return m_msg_sqn;
}

uint32_t
PLC_MacHeader::GetMessageLength (void) const
{
	return m_msg_length;
}

bool
PLC_MacHeader::GetHasRelayHeader (void) const
{
	return (m_flags & 0x10);
}

//////////////////////// PLC_RelayMacHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_RelayMacHeader);

TypeId
PLC_RelayMacHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_RelayMacHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_RelayMacHeader> ();
  return tid;
}

PLC_RelayMacHeader::PLC_RelayMacHeader(void)
{
	m_relay_hops = 0;
	m_flags = 0;
}

PLC_RelayMacHeader::~PLC_RelayMacHeader(void)
{
}

uint32_t
PLC_RelayMacHeader::GetSerializedSize (void) const
{
	return 16;
}

TypeId
PLC_RelayMacHeader::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_RelayMacHeader::Serialize (Buffer::Iterator start) const
{
    Buffer::Iterator i = start;
    WriteTo (i, m_dst_address);
    WriteTo (i, m_src_address);
    i.WriteU16(m_msg_sqn);
    i.WriteU8(m_relay_hops);
    i.WriteU8(m_flags);
}

uint32_t
PLC_RelayMacHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	ReadFrom (i, m_dst_address);
	ReadFrom (i, m_src_address);
	m_msg_sqn = i.ReadU16 ();
	m_relay_hops = i.ReadU8 ();
	m_flags = i.ReadU8 ();
	return i.GetDistanceFrom (start);
}

void
PLC_RelayMacHeader::Print (std::ostream &os) const
{
	os << "destination address = " << m_dst_address;
	os << ", source address = " << m_src_address;
	os << ", sequence number = " << (int) m_msg_sqn;
	os << ", relay hops = " << (int) m_relay_hops;
	os << ", relay type = " << (int) m_flags;
}

void
PLC_RelayMacHeader::SetDstAddress (Mac48Address addr)
{
	m_dst_address = addr;
}

void
PLC_RelayMacHeader::SetSrcAddress (Mac48Address addr)
{
	m_src_address = addr;
}

void
PLC_RelayMacHeader::IncrementRelayHops (void)
{
	m_relay_hops++;
}

Mac48Address
PLC_RelayMacHeader::GetDstAddress (void) const
{
	return m_dst_address;
}

Mac48Address
PLC_RelayMacHeader::GetSrcAddress (void) const
{
	return m_src_address;
}

uint8_t
PLC_RelayMacHeader::GetRelayHops (void) const
{
	return m_relay_hops;
}

void
PLC_RelayMacHeader::SetRelayType (RelayMacHdrType type)
{
	m_flags |= (0x1 & type);
}

PLC_RelayMacHeader::RelayMacHdrType
PLC_RelayMacHeader::GetRelayType (void)
{
	return (RelayMacHdrType)(m_flags & 0x1);
}

void
PLC_RelayMacHeader::SetSequenceNumber (uint16_t sqn)
{
	m_msg_sqn = sqn;
}


uint16_t
PLC_RelayMacHeader::GetSequenceNumber (void) const
{
	return m_msg_sqn;
}

}
