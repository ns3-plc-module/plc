/*
 * plc-header.cc
 *
 *  Created on: 2012-05-25
 *      Author: deadlock
 */

#include <ns3/address-utils.h>
#include "plc-header.h"

namespace ns3 {

//////////////////////// PLC_PhyPacketTag //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_PhyPacketTag);

TypeId
PLC_PhyPacketTag::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_PhyPacketTag")
    .SetParent<Tag> ();
  return tid;
}

uint32_t
PLC_PhyPacketTag::GetSerializedSize (void) const
{
	return sizeof(ModulationAndCodingType) + sizeof(uint64_t) + sizeof(size_t);
}

void
PLC_PhyPacketTag::Serialize (TagBuffer i) const
{
	i.WriteU8((uint8_t) m_payload_mcs);
	i.WriteU64(m_duration.ToInteger(Time::GetResolution()));
	i.WriteU32(m_uncoded_bits);
}

void
PLC_PhyPacketTag::Deserialize (TagBuffer i)
{
	m_payload_mcs = (ModulationAndCodingType) i.ReadU8();
	m_duration = Time::FromInteger((int64_t) i.ReadU64(), Time::GetResolution());
	m_uncoded_bits = (uint32_t) i.ReadU32();
}

void
PLC_PhyPacketTag::Print (std::ostream &os) const
{
	os << ", Header Modulation and Coding Type = " << m_payload_mcs;
	os << ", Duration = " << m_duration;
	os << ", Uncoded bits = " << m_uncoded_bits;
}

TypeId
PLC_PhyPacketTag::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

//////////////////////// PLC_PhyHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_PhyHeader);

TypeId
PLC_PhyHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_PhyHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_PhyHeader> ();
  return tid;
}

PLC_PhyHeader::PLC_PhyHeader(void)
{
	// PHY preamble: 10101010
	m_preamble = 0xaa;
}

PLC_PhyHeader::~PLC_PhyHeader(void)
{
}

uint32_t
PLC_PhyHeader::GetSerializedSize (void) const
{
	return sizeof(m_preamble);
}

TypeId
PLC_PhyHeader::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_PhyHeader::Serialize (Buffer::Iterator start) const
{
	Buffer::Iterator i = start;
	i.WriteU8(m_preamble);
}

uint32_t
PLC_PhyHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	m_preamble = i.ReadU8();
	return i.GetDistanceFrom(start);
}

void
PLC_PhyHeader::Print (std::ostream &os) const
{
	os << "preamble = " << m_preamble;
}

//////////////////////// PLC_RatelessPhyHeader //////////////////////////

NS_OBJECT_ENSURE_REGISTERED(PLC_RatelessPhyHeader);

TypeId
PLC_RatelessPhyHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_RatelessPhyHeader")
    .SetParent<Header> ()
    .AddConstructor<PLC_RatelessPhyHeader> ();
  return tid;
}

PLC_RatelessPhyHeader::PLC_RatelessPhyHeader(void)
{

}

PLC_RatelessPhyHeader::~PLC_RatelessPhyHeader(void)
{

}

uint32_t
PLC_RatelessPhyHeader::GetSerializedSize (void) const
{
	return 11;
}

TypeId
PLC_RatelessPhyHeader::GetInstanceTypeId (void) const
{
	return GetTypeId();
}

void
PLC_RatelessPhyHeader::Serialize (Buffer::Iterator start) const
{
	Buffer::Iterator i = start;
	i.WriteU8(m_flags);
	i.WriteHtonU16(m_prng_seed);
	i.WriteHtonU16(m_datagram_id);
	i.WriteU8(GetFirstChunkSqn());
	i.WriteHtonU32(m_num_blocks);
	i.WriteU8(m_crc);
}

uint32_t
PLC_RatelessPhyHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	m_flags = i.ReadU8();
	m_prng_seed = i.ReadNtohU16();
	m_datagram_id = i.ReadNtohU16();
	m_first_chunk_sqn = i.ReadU8();
	m_num_blocks = i.ReadNtohU32();
	m_crc = i.ReadU8();
	return i.GetDistanceFrom(start);
}

void
PLC_RatelessPhyHeader::Print (std::ostream &os) const
{
	os << "control frame flag = " << (m_flags & 0x1);
	os << ", prng seed = " << (int) m_prng_seed;
	os << ", datagram id = " << (int) m_datagram_id;
	os << ", first chunk sqn = " << (int) m_first_chunk_sqn;
	os << ", message blocks = " << (int) m_num_blocks;
}

void PLC_RatelessPhyHeader::SetPrngSeed(uint16_t seed)
{
	m_prng_seed = seed;
}

void
PLC_RatelessPhyHeader::SetFirstChunkSqn(uint8_t sqn)
{
	m_first_chunk_sqn = sqn;
}

void PLC_RatelessPhyHeader::SetDatagramId(uint16_t id)
{
	m_datagram_id = id;
}

void PLC_RatelessPhyHeader::SetNumBlocks(uint32_t blocks)
{
	m_num_blocks = blocks;
}

void PLC_RatelessPhyHeader::SetControlFrame(bool a)
{
	if (a)
		m_flags |= 0x1;
	else
		m_flags &= ~0x1;
}

bool PLC_RatelessPhyHeader::IsControlFrame(void) const
{
	return (m_flags & 0x1);
}

uint16_t PLC_RatelessPhyHeader::GetDatagramId(void) const
{
	return m_datagram_id;
}

uint16_t PLC_RatelessPhyHeader::GetPrngSeed(void) const
{
	return m_prng_seed;
}

uint32_t PLC_RatelessPhyHeader::GetNumBlocks(void) const
{
	return m_num_blocks;
}

uint8_t PLC_RatelessPhyHeader::GetFirstChunkSqn(void) const
{
	return m_first_chunk_sqn;
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
}

void PLC_MacHeader::SetDstAddress(Mac48Address addr)
{
	m_dst_address = addr;
}

void PLC_MacHeader::SetSrcAddress(Mac48Address addr)
{
	m_src_address = addr;
}

void PLC_MacHeader::SetType(PLC_MacHeader::MacHdrType type)
{
	m_flags = (m_flags & 0xf0) | (0x0f & type);
}

void PLC_MacHeader::SetSequenceNumber(uint16_t sqn)
{
	m_msg_sqn = sqn;
}

void PLC_MacHeader::SetMessageLength(uint32_t length)
{
	m_msg_length = length;
}

Mac48Address PLC_MacHeader::GetDstAddress(void) const
{
	return m_dst_address;
}

Mac48Address PLC_MacHeader::GetSrcAddress(void) const
{
	return m_src_address;
}

PLC_MacHeader::MacHdrType PLC_MacHeader::GetType(void) const
{
	return (PLC_MacHeader::MacHdrType)(m_flags & 0x0f);
}

uint16_t PLC_MacHeader::GetSequenceNumber(void) const
{
	return m_msg_sqn;
}

uint32_t PLC_MacHeader::GetMessageLength(void) const
{
	return m_msg_length;
}

}
