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

#ifndef PLC_CHANNEL_H_
#define PLC_CHANNEL_H_

#include <math.h>
#include <complex>
#include <vector>
#include <set>

#include <ns3/assert.h>
#include <ns3/object.h>
#include <ns3/type-id.h>

#include <ns3/system-thread.h>
#include <ns3/packet.h>
#include <ns3/channel.h>
#include <ns3/nstime.h>
#include <ns3/packet.h>
#include <ns3/spectrum-value.h>
#include <ns3/net-device.h>
#include <ns3/bridge-net-device.h>
#include <ns3/traced-value.h>
#include <ns3/trace-source-accessor.h>

#include "plc-interface.h"

namespace ns3 {

class PLC_Graph;
class PLC_Phy;
class PLC_TxInterface;
class PLC_RxInterface;;

class PLC_TrxMetaInfo : public Object
{
public:
	static TypeId GetTypeId (void);

	PLC_TrxMetaInfo (void);

	void SetUncodedMessage (Ptr<const Packet> p) { m_uncoded_packet = p; }
	Ptr<const Packet> GetUncodedMessage (void) const { return m_uncoded_packet; }
	void SetHeaderMcs (ModulationAndCodingType mcs) { m_header_mcs = mcs; }
	ModulationAndCodingType GetHeaderMcs (void) const { return m_header_mcs; }
	void SetPayloadMcs (ModulationAndCodingType mcs) { m_payload_mcs = mcs; }
	ModulationAndCodingType GetPayloadMcs (void) const { return m_payload_mcs; }
	void SetHeaderDuration (Time duration) { m_header_duration = duration; }
	Time GetHeaderDuration (void) const { return m_header_duration; }
	void SetPayloadDuration (Time duration) { m_payload_duration = duration; }
	Time GetPayloadDuration (void) const { return m_payload_duration; }

private:
	Ptr<const Packet> m_uncoded_packet;
	ModulationAndCodingType m_header_mcs;
	ModulationAndCodingType m_payload_mcs;
	Time m_header_duration;
	Time m_payload_duration;
};

/**
 * PLC_EdgeTransferUnit holds the transfer function of a single edge of the PLC_Graph.
 * The channel transfer function for a (tx,rx) tupel is the product of the path's PLC_EdgeTransferData.
 * Each PLC_Edge references two PLC_EdgeTransferUnit instances (each for one direction).
 */
class PLC_EdgeTransferUnit : public Object
{
	friend class PLC_Outlet;

public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * @param edge Associated edge
	 * @param dst_node Node pointing to transfer direction
	 * @param sm Spectrum model
	 * @param time_variant If true channel transfer vector will be initialised as time variant value
	 */
	PLC_EdgeTransferUnit(PLC_Edge *edge, PLC_Node *dst_node, Ptr<const SpectrumModel> sm, bool time_variant = false);

	/**
	 *	Destructor
	 */
	~PLC_EdgeTransferUnit(void) {}

	/**
	 *
	 * @return Associated edge of the PLC graph
	 */
	PLC_Edge *GetEdge(void) const { return m_edge; }

	/**
	 *
	 * @return Destination node heading to transfer direction
	 */
	PLC_Node *GetDstNode(void) const { return m_dst_node; }

	/**
	 * Set channel transfer vector for this edge unit pointing to m_dst_node
	 * @param ctv Channel transfer vector
	 */
	void SetEdgeTransferVector(Ptr<PLC_TransferBase> ctv);

	/**
	 *
	 * @return Previously assigned channel transfer vector or NULL
	 */
	Ptr<PLC_TransferBase> GetEdgeTransferVector(void);

	/**
	 *
	 * @return Peek pointer of the channel transfer vector (for parallel processing)
	 */
	PLC_TransferBase *GetEdgeTransferVectorPtr(void) { return PeekPointer(m_edge_transfer_vector); }

	/**
	 *
	 * @return True if channel transfer vector is still up to date
	 */
	bool IsUp2Date(void) const { return m_is_up_2_date; }

	/**
	 * Sets the channel transfer vector out of date
	 */
	void SetOutOfDate(void) { m_is_up_2_date = false; }

	/**
	 *
	 * @return True if channel transfer vector is time variant
	 */
	bool IsTimeVariant(void);

	/**
	 * Mutex lock and unlock
	 */
	void Lock(void) const { m_edge_transfer_unit_mutex.Lock(); }
	void Unlock(void) const { m_edge_transfer_unit_mutex.Unlock(); }

private:
	void DoDispose(void);

	Ptr<const SpectrumModel> 	m_spectrum_model;
	mutable PLC_Mutex 			m_edge_transfer_unit_mutex;
	PLC_Edge 					*m_edge;	 // non ns3::Ptr<>, because object system
	PLC_Node 					*m_dst_node; // gets screwed up with parallel processing
	Ptr<PLC_TransferBase> 		m_edge_transfer_vector; // Channel Transfer Function data for the m_edge heading to m_dst_node

	bool m_is_up_2_date;
};

/**
 * \class PLC_ChannelTransferImpl
 *
 * PLC_ChannelTransferImpl is owner of the channel transfer function of a (tx,rx)-tupel.
 * Besides it caches the square values of the absolute channel transfer function.
 */
class PLC_ChannelTransferImpl : public Object
{
	friend class PLC_TxInterface;

public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * @param txInterface Transmission source interface
	 * @param rxInterface Transmission sink interface
	 * @param sm Spectrum model
	 * @param create_backbone_path If true the backbone path from txInterface to rxInterface will be calculated
	 */
	PLC_ChannelTransferImpl(PLC_TxInterface *txInterface, PLC_RxInterface *rxInterface, Ptr<const SpectrumModel> sm, bool create_backbone_path = true);
	~PLC_ChannelTransferImpl() {}

	/**
	 *
	 * @return PLC graph of the interfaces
	 */
	Ptr<PLC_Graph> GetGraph(void);

	/**
	 *
	 * @return True if channel transfer function is time variant, false otherwise
	 */
	bool IsTimeVariant(void);

	/**
	 * If channel transfer vector is not time variant it will be converted to a time variant value.
	 * Called if an PLC_EdgeTransferUnit of the backbone path becomes time variant.
	 */
	void SetTimeVariant(void);

	/**
	 * Set to true if the channel transfer function should be recalculated immediately after a change in
	 * the network, e.g. for the time correct tracing of the channel transfer function's evolution.
	 * If false the channel transfer function will only be updated at the next point in time when needed
	 * @param value
	 */
	void UpdateImmediately(bool value) { m_update_immediately = value; }

	/**
	 *
	 * @return True if the channel transfer function is up to date
	 */
	bool IsUp2Date(void) { return m_is_up_2_date; }

	/**
	 * @return An estimation for the signal's propagation delay on the direct path
	 */
	Time GetDirectPathPropagationDelay(void);

	/**
	 * Get backbone path
	 * @return 	List of backbone nodes lying between txInterface and rxInterface;
	 * 			In case of a direct connection the function returns an empty list
	 */
	std::list<PLC_BackboneBranch *> GetBackbonePath(void);

	/**
	 *
	 * @return Iterator to the head of the backbone path list
	 */
	PLC_BackbonePath::iterator BackbonePathBegin(void);

	/**
	 *
	 * @return Iterator to the tail of the backbone path list
	 */
	PLC_BackbonePath::iterator BackbonePathEnd(void);

	/**
	 * Creates the backbone path
	 */
	void CreateBackbonePath(void);

	/**
	 * @brief Triggers a parallel depth first search onto the PLC graph originating
	 * from each node of the backbone path.
	 * If an outlet is found while traversing the graph a registration with the backbone node is done in order
	 * to get informed when the outlet impedance changes during the simulation and the channel transfer function
	 * needs to be recalculated.
	 *
	 * @warning Should be called after CreateBackbonePath() and before InitializeChannelTransferVector()
	 */
	void DiscoverBackboneBranches(void);

	/**
	 * Initialize the channel transfer vector data structure
	 * @param set_time_variant
	 */
	void InitializeChannelTransferVector(bool set_time_variant = false);

	/**
	 * Triggers the channel calculation
	 */
	void CalculateChannelTransferVector(void);

	/**
	 * @return Updated channel transfer vector
	 */
	Ptr<PLC_TransferBase> GetChannelTransferVector(void);

	/**
	 * Get magnitude square of the channel transfer function.
	 * Triggers GetAbsSqrCtf() if not up to date
	 * @param timeslot Timeslot for timevariant CTF
	 * @return |H(f)|²
	 */
	Ptr<SpectrumValue> GetAbsSqrCtf(unsigned int timeslot = 0);

	/**
	 * Create square of the absolute channel transfer function
	 */
	void GenerateAbsSqrCtf(void);

	/**
	 * \brief Calculate the power spectral density seen at the receiver's interface
	 *
	 * rxPsd = txPsd*|H|^2
	 *
	 * @param txPsd Power spectral density of the transmitted waveform
	 * @param timeslot Timeslot of propagation
	 * @return Received power spectral density
	 */
	Ptr<SpectrumValue> CalculateRxPowerSpectralDensity(Ptr<const SpectrumValue> txPsd, Timeslot timeslot = 0);

	/**
	 * Mutex lock and unlock
	 */
	void Lock(void) const { m_mutex.Lock(); }
	void Unlock(void) const { m_mutex.Unlock(); }

private:
	void DoDispose(void);

	void AddBackboneBranch(Ptr<PLC_Node> branch, Ptr<PLC_Node> node_before, Ptr<PLC_Node> node_next);
	Ptr<PLC_TransferBase> MultiplyChannelTransferVector(Ptr<PLC_TransferBase> result, PLC_TransferBase *ctv);
	void SetOutOfDate(void);
	void CalculateDirectPathPropagationDelay(void);

	Ptr<const SpectrumModel> 			m_spectrum_model;
	mutable PLC_Mutex 					m_mutex;
	PLC_TxInterface 					*m_txInterface;
	PLC_RxInterface						*m_rxInterface;
	PLC_BackbonePath 					m_backbone_path;
	Ptr<PLC_TransferBase> 				m_channel_transfer_vector;
	std::vector<Ptr<SpectrumValue> >	m_abs_sqr_ctf;

	uint64_t m_impedance_hash_sum;

	Time m_delay;
	bool m_is_time_variant;
	bool m_ctv_is_up_2_date;
	bool m_is_up_2_date;

	bool m_update_immediately;
	bool m_update_scheduled;
	TracedCallback<Time, Ptr<PLC_TransferBase> > m_channelDataTracer;
};

/**
 *	\class PLC_Channel
 *
 *	Joins all PLC channel transfer functions
 *	By extending ns3::Channel this class provides an interface for attaching
 *	ns3::NetDevice instances to a PLC channel
 */
class PLC_Channel : public Channel
{
	friend class PLC_Outlet;

public:
	static TypeId GetTypeId(void);

	/**
	 * Default constructor
	 */
	PLC_Channel();

	/**
	 * Constructor
	 * @param graph PLC_Graph instance to use
	 */
	PLC_Channel(Ptr<PLC_Graph> graph);
	~PLC_Channel(void);

	/**
	 * Set PLC_Graph
	 * Has to be done before calling InitTransmissionChannels
	 * @param graph PLC_Graph
	 */
	void SetGraph(Ptr<PLC_Graph> graph);

	/**
	 * @return The used PLC_Graph instance
	 */
	Ptr<PLC_Graph> GetGraph(void) { return this->m_graph; }

	/**
	 * Connect a TxInterface to this channel
	 */
	uint32_t AddTxInterface(Ptr<PLC_TxInterface> txInterface);

	/**
	* \returns the number of TxInterfaces connected to this Channel.
	*/
	uint32_t GetNTxInterfaces(void) const;

	/**
	* \param i index of TxInterface to retrieve
	* \returns one of the TxInterfaces connected to this channel.
	*/
	Ptr<PLC_TxInterface> GetTxInterface(uint32_t i) const;

	/**
	 * Connect a RxInterface to this channel
	 */
	uint32_t AddRxInterface(Ptr<PLC_RxInterface> rxInterface);

	/**
	* \returns the number of RxInterface connected to this Channel.
	*/
	uint32_t GetNRxInterfaces(void) const;

	/**
	* \param i index of RxInterface to retrieve
	* \returns one of the RxInterface connected to this channel.
	*
	* This method must be implemented by subclasses.
	*/
	Ptr<PLC_RxInterface> GetRxInterface(uint32_t i) const;

	/**
	 * Connect a NetDevice to this channel.
	 * This method must be implemented by subclasses.
	 * However, this implementation uses PLC_TxInterface and PLC_RxInterface to
	 * identify attached communication devices rather than ns3::NetDevice.
	 * Hence it is possible to distinguish between simple Tx devices (e.g. noise sources)
	 * and simplex Rx devices, which decreases the effort of channel computation
	 */
	uint32_t AddDevice(Ptr<NetDevice>);

	/**
	* \returns the number of NetDevices connected to this Channel.
	*
	* This method must be implemented by subclasses.
	*/
	uint32_t GetNDevices (void) const;

	/**
	 * \param i index of NetDevice to retrieve
	 * \returns one of the NetDevices connected to this channel.
	 */
	Ptr<NetDevice> GetDevice (uint32_t i) const;

	/**
	 * Create PLC_Graph and init transmission channel data structures
	 */
	void InitTransmissionChannels(void);

	/**
	 * Calculate transmission channels from every txInterface
	 * to every rxInterface
	 */
	void CalcTransmissionChannels(void);

	/**
	 * Get the channel transfer data between TX-Interface with txId and RX-Interface with rxId
	 */
	Ptr<PLC_TransferBase> GetChannelTransferData(uint32_t txId, uint32_t rxId);

	/**
	* \brief Start transmitting a packet over the channel
	*
	* If the srcId belongs to a txInterface that is connected to the
	* channel, packet transmission begins, and the channel becomes busy
	* until the packet has completely reached all destinations.
	*
	* \param p A reference to the packet that will be transmitted over
	* the channel or NULL if txInterface is a noise source
	* \param srcId The device Id of the txInterface that wants to
	* transmit on the channel.
	* \param st Spectrum Type of txPsd to emulate different modulations
	*/
	void TransmissionStart(Ptr<const Packet> p, uint32_t txId, Ptr<const SpectrumValue> txPsd, Time duration, Ptr<const PLC_TrxMetaInfo> metaInfo);

	/**
	* \brief Indicates that the txInterface has finished transmitting over the channel
	*
	* The channel will stay busy until the packet has completely
	* propagated to all net devices attached to the channel. The
	* TransmitEnd function schedules the PropagationCompleteEvent which
	* will free the channel for further transmissions. Stores the
	* packet p as the m_currentPkt, the packet being currently
	* transmitting.
	*
	* \return Returns true unless the source was detached before it
	* completed its transmission.
	*/
	bool TransmissionEnd(uint32_t txId, Time propagation_delay);

	/**
	* \brief Indicates that the channel has finished propagating the
	* current packet. The channel is released and becomes free.
	*
	* Calls the receive function of every active rx Interface that is
	* attached to the channel.
	*/
	void PropagationCompleteEvent(uint32_t txId);

	/**
	 * Get the current timeslot
	 */
	Timeslot GetCurrentTimeslot(void);

	/**
	 * Calculate remaining time from t to next slot after t
	 */
	Time GetRemainingSlotTime(Time t);

	/**
	 * Process periodic tasks,
	 * i.e. update receive power spectral densities of all active
	 * transmission when a new timeslot starts
	 */
	void ProcessTimeslotTasks(Timeslot timeslot);

	/**
	 * While a transmission is active ProcessTimeslotTasks() has to be rescheduled
	 * for the next timeslot
	 */
	void ScheduleNextTimeslotTasks(void);

	/**
	 * Changes the receive PSDs of the rxInterfaces
	 * @param timeslot Current timeslot (as parameter to avoid recalculation)
	 */
	void UpdateReceivePSDs(Timeslot timeslot, bool channel_changed = false);

	/**
	 * Deletes the cached (time variant) power spectral density from tx to rx.
	 * When they are needed the next time they have to be recalculated.
	 * Called by PLC_Outlet after impedance change
	 */
	void DeleteOutOfDatePSDs(Ptr<PLC_TxInterface> tx, Ptr<PLC_RxInterface> rx);

	/**
	 * Mutex lock and unlock
	 */
	void Lock(void) const { m_mutex.Lock(); }
	void Unlock(void) const { m_mutex.Unlock(); }

private:
	void DoStart(void);
	void DoDispose(void);

	/**
	 * Helper function for computation and caching of receive PSDs
	 */
	void MakeRxPsdMapEntries(Timeslot cur_timeslot, Timeslot end_timeslot, PLC_RxPsdMap& rxPsdMap, PLC_ChannelTransferImpl *ch_impl, Ptr<const SpectrumValue> txPsd);

	mutable PLC_Mutex					m_mutex;
	mutable PLC_Mutex					m_schedule_mutex;
	Ptr<PLC_Graph>						m_graph;

	std::set<Ptr<PLC_Phy> >				m_phys;
	std::vector<Ptr<PLC_TxInterface> >	m_txInterfaces;
	std::vector<Ptr<PLC_RxInterface> >	m_rxInterfaces;
	std::vector<Ptr<NetDevice> >		m_devices;

	std::set<uint32_t>				m_transmitting;
	std::set<uint32_t>				m_propagating;
	PLC_TransmissionDescriptorMap	m_transmission_descriptors;

	bool m_timeslot_tasks_scheduled;

	TracedCallback<Time, uint32_t, bool> m_occupancyLogger;
	TracedCallback<Time, std::set<uint32_t> > m_activeTxIfLogger;
};

}

#endif /* PLC_CHANNEL_H_ */
