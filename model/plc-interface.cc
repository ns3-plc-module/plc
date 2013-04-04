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

#include <boost/graph/copy.hpp>
#include <ns3/system-thread.h>
#include <ns3/plc-defs.h>
#include <ns3/log.h>
#include <ns3/simulator.h>
#include "plc-interface.h"
#include "plc-channel.h"
#include "plc-outlet.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PLC_Interface");
NS_OBJECT_ENSURE_REGISTERED  (PLC_Interface);
NS_OBJECT_ENSURE_REGISTERED  (PLC_TxInterface);
NS_OBJECT_ENSURE_REGISTERED  (PLC_RxInterface);

PLC_Interface::PLC_Interface (Ptr<PLC_Node> associated_plc_node, Ptr<const SpectrumModel> sm)
	: m_plc_node (associated_plc_node), m_spectrum_model (sm), m_phy (NULL)
{
}

PLC_Interface::~PLC_Interface ()
{
}

void
PLC_Interface::DoDispose (void)
{
	m_plc_node = 0;
	m_spectrum_model = 0;
	m_phy = 0;
}

TypeId
PLC_Interface::GetTypeId (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_Interface")
    		.SetParent<Object>  ()
    		;
	return tid;
}

Ptr<PLC_Graph>
PLC_Interface::GetGraph (void)
{
	PLC_LOG_FUNCTION (this);
	return this->m_plc_node->GetGraph ();
}

Ptr<PLC_Channel>
PLC_Interface::GetChannel (void)
{
	PLC_LOG_FUNCTION (this);
	return this->m_plc_node->GetGraph ()->GetChannel ();
}

void
PLC_Interface::SetPhy (Ptr<PLC_Phy> phy)
{
	PLC_LOG_FUNCTION (this << phy);
	this->m_phy = phy;
}

Ptr<PLC_Phy>
PLC_Interface::GetPhy (void)
{
	PLC_LOG_FUNCTION (this);
	return this->m_phy;
}

//////////////////////////////////////// PLC_TxInterface ////////////////////////////////////////////////

PLC_TxInterface::PLC_TxInterface (Ptr<PLC_Node> associated_plc_node, Ptr<const SpectrumModel> sm) : PLC_Interface (associated_plc_node, sm), m_all_bb_up2date (false)
{
//	PLC_LOG_INFO ("PLC_TxInterface installed on Node" << associated_plc_node->GetVertexId ());
}

void
PLC_TxInterface::DoStart (void)
{
}

void
PLC_TxInterface::DoDispose (void)
{
	m_txPsd = 0;

	std::map<PLC_RxInterface *, Ptr<PLC_ChannelTransferImpl> >::iterator cit;
	for (cit = m_channel_transfer_impls.begin(); cit != m_channel_transfer_impls.end(); cit++)
	{
		cit->second->Dispose();
	}

	m_channel_transfer_impls.clear ();
	PLC_Interface::DoDispose ();
}

TypeId
PLC_TxInterface::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_TxInterface")
    		.SetParent<PLC_Interface>  ()
    		;
	return tid;
}

uint32_t
PLC_TxInterface::GetTxIfIdx (void) const
{
	return this->m_txIfIdx;
}

void
PLC_TxInterface::InitializeChannelTransferImpls (void)
{
	PLC_LOG_INFO ("Initializing transmission channels from txInterface on Node" << this->m_plc_node->GetVertexId ());

	this->GetGraph ()->Lock ();
	std::vector<PLC_RxInterface *> rxInterfaces = this->GetGraph ()->GetConnectedRxInterfacePeekPtrs ();
	this->GetGraph ()->Unlock ();
	std::vector<PLC_RxInterface *>::iterator rx_it;

	for  (rx_it = rxInterfaces.begin (); rx_it != rxInterfaces.end (); rx_it++)
	{
		if  ( (*rx_it)->GetNode () != this->m_plc_node && IsWithinRange (*rx_it))
		{
			this->RegisterRxInterface (*rx_it);
		}
	}

	std::vector<PLC_ChannelTransferImpl *> ch_impls;
	std::map<PLC_RxInterface *, Ptr<PLC_ChannelTransferImpl> >::iterator channel_it;

	for  (channel_it = this->m_channel_transfer_impls.begin (); channel_it != this->m_channel_transfer_impls.end (); channel_it++)
	{
		ch_impls.push_back (PeekPointer (channel_it->second));
	}

	int i;
	unsigned int size;
	NS_ASSERT ( (size = ch_impls.size ()) < INT_MAX);

	for  (i = 0; i <  (int) size; i++)
	{
		ch_impls[i]->DiscoverBackboneBranches ();
	}
}

void PLC_TxInterface::CalculateChannels (void)
{
	std::vector<PLC_ChannelTransferImpl *> ch_impls;
	std::map<PLC_RxInterface *, Ptr<PLC_ChannelTransferImpl> >::iterator channel_it;

	for  (channel_it = this->m_channel_transfer_impls.begin (); channel_it != this->m_channel_transfer_impls.end (); channel_it++) {
		ch_impls.push_back (PeekPointer (channel_it->second));
	}

	int i;
	unsigned int size;
	NS_ASSERT ( (size = ch_impls.size ()) < INT_MAX);

	for  (i = 0; i <  (int) size; i++) {
		if (!ch_impls[i]->IsUp2Date())
		{
			ch_impls[i]->CalculateChannelTransferVector ();
		}
	}
}

/**
 * TODO mask interfaces for channel calculation which are not reachable due to long distance
 */
bool
PLC_TxInterface::IsWithinRange (PLC_RxInterface *rxInterface)
{
	return true;
}

bool
PLC_TxInterface::IsCenterFreqWithinRange (PLC_RxInterface *rxInterface)
{
	return true;
}

void
PLC_TxInterface::RegisterRxInterface (PLC_RxInterface *rxInterface)
{
	PLC_LOG_FUNCTION (this << "rxInterface " << rxInterface << "registered");

	g_smartpointer_mutex.Lock ();
	this->m_channel_transfer_impls[rxInterface] = CreateObject<PLC_ChannelTransferImpl>  (this, rxInterface, this->m_spectrum_model, false);
	g_smartpointer_mutex.Unlock ();

	this->m_channel_transfer_impls[rxInterface]->CreateBackbonePath ();
}

std::list<PLC_BackboneBranch *>
PLC_TxInterface::GetBackbonePath (PLC_RxInterface *sink)
{
	PLC_LOG_FUNCTION (this << sink);
	std::list<PLC_BackboneBranch *> ret;

	this->m_channel_transfer_impls[sink]->Lock ();
	ret = this->m_channel_transfer_impls[sink]->GetBackbonePath ();
	this->m_channel_transfer_impls[sink]->Unlock ();

	return ret;
}

PLC_BackbonePath::iterator PLC_TxInterface::BackbonePathBegin (PLC_RxInterface *sink)
{
	PLC_LOG_FUNCTION (this << sink);
	PLC_BackbonePath::iterator ret;

	NS_ASSERT(m_channel_transfer_impls.find(sink) != m_channel_transfer_impls.end());

	this->m_channel_transfer_impls[sink]->Lock ();
	ret = this->m_channel_transfer_impls[sink]->BackbonePathBegin ();
	this->m_channel_transfer_impls[sink]->Unlock ();

	return ret;
}

PLC_BackbonePath::iterator PLC_TxInterface::BackbonePathEnd (PLC_RxInterface *sink)
{
	PLC_BackbonePath::iterator ret;

	this->m_channel_transfer_impls[sink]->Lock ();
	ret = this->m_channel_transfer_impls[sink]->BackbonePathEnd ();
	this->m_channel_transfer_impls[sink]->Unlock ();

	return ret;
}

PLC_ChannelTransferImpl *
PLC_TxInterface::GetChannelTransferImpl (PLC_RxInterface *rxInterface)
{
	if  (this->m_channel_transfer_impls.find (rxInterface) == this->m_channel_transfer_impls.end ())
		return NULL;
	else
		return PeekPointer (m_channel_transfer_impls[rxInterface]);
}

void
PLC_TxInterface::StartTx (Ptr<const Packet> p, Ptr<const SpectrumValue> txPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_LOG_FUNCTION (this << p << metaInfo);
	if (p != NULL)
	{
		PLC_LOG_LOGIC("Outgoing frame: " << *p);
	}
	this->m_txPsd = txPsd;

	this->GetChannel()->TransmissionStart(p, GetTxIfIdx(), txPsd, duration, metaInfo);
}

void
PLC_TxInterface::SetChannelTransferImplsOutOfDate (void)
{
	PLC_LOG_FUNCTION (this);
	std::map<PLC_RxInterface *, Ptr<PLC_ChannelTransferImpl> >::iterator it;

	for  (it = m_channel_transfer_impls.begin (); it != m_channel_transfer_impls.end (); it++)
	{
		it->second->Lock ();
		it->second->SetOutOfDate ();
		it->second->Unlock ();
	}
}

void
PLC_TxInterface::SetTimeVariantChannel (PLC_RxInterface *rx)
{
	PLC_LOG_FUNCTION (this);
	Ptr<PLC_ChannelTransferImpl> ch_impl = this->m_channel_transfer_impls[rx];
	ch_impl->Lock ();
	ch_impl->SetTimeVariant ();
	ch_impl->Unlock ();
}

//////////////////////////////////////// PLC_RxInterface ////////////////////////////////////////////////

PLC_RxInterface::PLC_RxInterface (Ptr<PLC_Node> associated_node, Ptr<const SpectrumModel> sm)
	: PLC_Interface (associated_node, sm)
{
}

void PLC_RxInterface::DoStart (void)
{
}

void PLC_RxInterface::DoDispose (void)
{
	PLC_Interface::DoDispose ();
}

uint32_t
PLC_RxInterface::GetRxIfIdx (void) const
{
	return this->m_rxIfIdx;
}

TypeId
PLC_RxInterface::GetTypeId  (void)
{
	static TypeId tid = ns3::TypeId ("ns3::PLC_RxInterface")
    		.SetParent<PLC_Interface> ()
    		;
	return tid;
}

void
PLC_RxInterface::SetOutlet(Ptr<PLC_Outlet> outlet)
{
	m_outlet = outlet;
	m_outlet->SetRxInterface(this);
}

void
PLC_RxInterface::StartRx (Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo)
{
	PLC_LOG_FUNCTION (this << p << rxPsd << metaInfo);
	if  (this->m_phy != NULL)
	{
		m_phy->StartRx (p, txId, rxPsd, duration, metaInfo);
	}
}

void
PLC_RxInterface::RxPsdChanged (uint32_t txId, Ptr<SpectrumValue> rxSignal)
{
	PLC_LOG_FUNCTION (this << rxSignal);
	if  (this->m_phy != NULL)
		this->m_phy->RxPsdChanged (txId, rxSignal);
}

} // namespace ns3
