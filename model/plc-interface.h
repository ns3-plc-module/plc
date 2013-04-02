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

#ifndef PLC_INTERFACE_H_
#define PLC_INTERFACE_H_

#include <map>

#include <ns3/node.h>
#include <ns3/spectrum-model.h>
#include <ns3/plc-graph.h>
#include <ns3/plc-backbone.h>
#include <ns3/plc-defs.h>
#include <ns3/packet-burst.h>
#include <ns3/spectrum-value.h>
#include <ns3/traced-callback.h>
#include <ns3/data-rate.h>
#include <ns3/event-id.h>

#include "plc-phy.h"

namespace ns3 {

class PLC_Node;
class PLC_Outlet;
class PLC_Graph;
class PLC_BackboneBranch;
class PLC_ChannelTransferImpl;
class PLC_Channel;
class PLC_Phy;
class PLC_TrxMetaInfo;

/**
 * \class PLC_Interface
 *
 * \brief Abstract base class for transmitter and receiver interfaces
 *
 * Transmission channels will be calculated for each transmitter-receiver
 * pair. Because not every device has to be duplex the computational costs can be
 * reduced by distinction between transmitting and receiving interfaces
 */
class PLC_Interface : public Object
{
public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * @param associated_plc_node PLC_Node the interface is located on
	 * @param sm Spectrum model
	 */
	PLC_Interface(Ptr<PLC_Node> associated_plc_node, Ptr<const SpectrumModel> sm);
	virtual ~PLC_Interface() = 0;

	/**
	 * @return PLC_Graph of associated_plc_node
	 */
	Ptr<PLC_Graph> GetGraph(void);

	/**
	 * @return PLC_Channel the interface is connected to
	 */
	Ptr<PLC_Channel> GetChannel(void);

	/**
	 * Define PLC_Phy instance that uses this interface
	 * @param phy
	 */
	void SetPhy(Ptr<PLC_Phy> phy);

	/**
	 * @return PLC_Phy instance using this interface
	 */
	Ptr<PLC_Phy> GetPhy(void);

	/**
	 * Bind interface to node
	 * @param node
	 */
	void SetNode(Ptr<PLC_Node> node) { this->m_plc_node = node; }

	/**
	 * @return PLC_Node the interface is located on
	 */
	Ptr<PLC_Node> GetNode(void) const { return m_plc_node; }
	PLC_Node *GetNodePeekPointer(void) const { return PeekPointer(m_plc_node); }

	/**
	 * Mutex lock and unlock
	 */
	void Lock(void) { m_mutex.Lock(); }
	void Unlock(void) { m_mutex.Unlock(); }

protected:
    // pure virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) = 0;
	virtual void DoDispose(void);

	mutable PLC_Mutex			m_mutex;
	Ptr<PLC_Node> 				m_plc_node;
	Ptr<const SpectrumModel>	m_spectrum_model;
	Ptr<PLC_Phy>				m_phy;
};

/**
 * \class PLC_TxInterface
 *
 * \brief Interface with transmitting ability
 */
class PLC_TxInterface : public PLC_Interface
{
	friend class PLC_Outlet;

public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * @param associated_plc_node PLC_Node the interface is located on
	 * @param sm Spectrum model
	 */
	PLC_TxInterface(Ptr<PLC_Node> associated_plc_node, Ptr<const SpectrumModel> sm);
	~PLC_TxInterface() {}

	/**
	 * Assign the index returned by PLC_Channel::AddTxInterface to this interface
	 * @param idx
	 */
	void SetIdx(uint32_t idx) { m_txIfIdx = idx; }

	/**
	 * @return Index the interface is registered with the channel
	 */
	uint32_t GetTxIfIdx(void) const;

	/**
	 * @return The most recent used transmission power spectral density
	 */
	Ptr<const SpectrumValue> GetTxPsd(void) { return m_txPsd; }

	/**
	 * Initialize channel implementations from this transmission interface to each known receiver interface.
	 *
	 * Only call after all interfaces have been added to PLC_Channel
	 */
	void InitializeChannelTransferImpls(void);

	/**
	 * Calculate the channel transfer function to each receiver interface
	 *
	 * Only call after InitializeChannelTransferImpls()
	 */
	void CalculateChannels(void);

	/**
	 * Get the channel transfer implementation that has the channel transfer data to rxInterface
	 * @param rxInterface
	 * @return Channel transfer implementation to rxInterface
	 */
	PLC_ChannelTransferImpl *GetChannelTransferImpl(PLC_RxInterface *rxInterface);

	/**
	 * Get the backbone path between this tx interface and the sink rx interface
	 * An empty list indicates a direct connection
	 * @param sink RX Interface of the backbone path
	 * @return Backbone path
	 */
	std::list<PLC_BackboneBranch *> GetBackbonePath(PLC_RxInterface *sink);

	/**
	 * @param sink RX Interface of the backbone path
	 * @return Iterator to start of the backbone path to sink
	 */
	PLC_BackbonePath::iterator BackbonePathBegin(PLC_RxInterface *sink);

	/**
	 * @param sink RX Interface of the backbone path
	 * @return Iterator to end of the backbone path to sink
	 */
	PLC_BackbonePath::iterator BackbonePathEnd(PLC_RxInterface *sink);

	/**
	 * Start transmission from this tx interface
	 *
	 * @param p Packet to be transmitted or NULL for noise signal
	 * @param metaInfo Meta information for link performance emulation
	 */
	void StartTx(Ptr<const Packet> p, Ptr<const SpectrumValue> txPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);

private:
    // virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}
	virtual void DoStart(void);
	virtual void DoDispose(void);

	// currently all rx interfaces are taken into account
	// even if they are too far away
	bool IsWithinRange(PLC_RxInterface *rxInterface);
	bool IsCenterFreqWithinRange(PLC_RxInterface *rxInterface);

	void RegisterRxInterface(PLC_RxInterface *rxInterface);

	// called by PLC_Outlet
	void SetChannelTransferImplsOutOfDate(void);
	void SetTimeVariantChannel(PLC_RxInterface *rx);

	bool m_all_bb_up2date;
	uint32_t m_txIfIdx;
	Ptr<const SpectrumValue> m_txPsd;
	std::map<PLC_RxInterface *, Ptr<PLC_ChannelTransferImpl> >  m_channel_transfer_impls;
};

/**
 * \class PLC_TxInterface
 *
 * \brief Interface with receiving ability
 */
class PLC_RxInterface : public PLC_Interface
{
public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * @param associated_plc_node PLC_Node the interface is located on
	 * @param sm Spectrum model
	 */
	PLC_RxInterface(Ptr<PLC_Node> associated_node, Ptr<const SpectrumModel> sm);
	~PLC_RxInterface() {}

	/**
	 * Assign the index returned by PLC_Channel::AddTxInterface to this interface
	 * @param idx
	 */
	void SetIdx(uint32_t idx) { m_rxIfIdx = idx; }

	/**
	 * @return Index the interface is registered with the channel
	 */
	uint32_t GetRxIfIdx(void) const;

	/**
	 * Connect this interface to an outlet
	 * @param outlet
	 */
	void SetOutlet(Ptr<PLC_Outlet> outlet);

	/**
	 * @return Outlet the interface is connected with
	 */
	Ptr<PLC_Outlet> GetOutlet(void) { return m_outlet; }

	/**
	 * Start receiving. Called by PLC_Channel::TransmissionStart()
	 *
	 * @param p Packet associated with the incoming waveform or NULL for noise
	 * @param rxPsd received power spectral density
	 * @param metaInfo meta information for link performance emulation
	 **/
	void StartRx(Ptr<const Packet> p, uint32_t txId, Ptr<SpectrumValue>& rxPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);

	/**
	 * Called when rxPsd changes due to channel evolution
	 * @param txId Transmitter index
	 * @param rxSignal New rxPsd
	 */
	void RxPsdChanged(uint32_t txId, Ptr<SpectrumValue> rxSignal);

private:
    // virtual dummy function to keep pybindgen happy
    virtual void pureVirtualDummy(void) {}
	virtual void DoStart(void);
	virtual void DoDispose(void);

	Ptr<PLC_Outlet> m_outlet;

	bool m_is_up_2_date;
	uint32_t m_rxIfIdx;
};

} // namespace ns3

#endif /* PLC_INTERFACE_H_ */
