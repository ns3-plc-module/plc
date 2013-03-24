/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) YEAR COPYRIGHTHOLDER
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

#ifndef PLC_EDGE_H
#define PLC_EDGE_H

#include <map>

#include "plc-defs.h"
#include "plc-cable.h"
#include "plc-channel.h"

namespace ns3 {

class PLC_Node;
class PLC_Cable;

/**
 * \brief Edge of the PLC graph
 *
 * This class represents an edge of the undirected graph defined by the PLC network topology.
 * An edge instance can either be a transmission line connecting two nodes or an abstract two port network,
 * that is used to characterize network transformers
 */

class PLC_Edge : public Object
{
	friend class PLC_Graph;
	friend class PLC_Outlet;

public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 * No default constructor, because an edge can't exists without connected nodes
	 *
	 * @param sm The spectrum model to be used
	 * @param from First node linked by this edge
	 * @param to Second node linked by this edge
	 */
	PLC_Edge(Ptr<const SpectrumModel> sm, Ptr<PLC_Node> from, Ptr<PLC_Node> to);

	/**
	 * Destructor
	 * Pure virtual due to abstract base class
	 */
	virtual ~PLC_Edge() = 0;

	/**
	 * The length of this edge
	 * @return Distance between the linked nodes
	 */
	double GetLength(void) { return m_length; }

	/**
	 * Lock edge mutex for multiprocessing
	 */
	void Lock() const { m_line_mutex.Lock(); }

	/**
	 * Unlock edge mutex
	 */
	void Unlock() const { m_line_mutex.Unlock(); }

	/**
	 * Get the second node linked by this edge
	 * @param src_node First node
	 * @return Second node (opposite of src_node)
	 */
	PLC_Node *GetConnectedNode(PLC_Node *src_node);

	/**
	 * Triggers calculation of the input impedance of this node
	 * This function is recursive
	 * @param dst_node Output destination node
	 */
	virtual void CalculateInputImpedance(PLC_Node *dst_node) = 0;

	/**
	 * Triggers the calculation of the so called edge transfer factor which is
	 * the transfer function representation of a two port network
	 * @param dst_node Output destination node
	 */
	virtual void CalculateEdgeTransferFactor(PLC_Node *dst_node) = 0;

	/**
	 * Approximation of the damping through this edge.
	 * This function is not used yet, but meant to reduce the computational effort
	 * in order to mask non reachable nodes
	 * @return Approximation of the node attenuation
	 */
	virtual double GetAttenuationApproxdB(void) = 0;

	/**
	 * Propagation delay for signals running through this node
	 * Ideal because the calculated delay is non dispersive
	 * @return
	 */
	virtual double GetIdealPropagationDelay(void) = 0;

	/**
	 * Indicates whether the cached input impedance of this edge is up to date
	 * @param dst_node Destination node
	 * @return True if impedance is up to date, false otherwise
	 */
	bool IsInputImpedanceUp2Date(PLC_Node *dst_node);

	/**
	 * Indicates whether the calculated edge transfer factor is still up to date
	 * @param dst_node Destination node
	 * @return true if no reachable impedance has changed, false otherwise
	 */
	bool IsEdgeTransferFactorUp2Date(PLC_Node *dst_node);

	/**
	 * Set the input impedance heading to dst_node out of date
	 * @param dst_node Destination node
	 */
	void SetInputImpedanceOutOfDate(PLC_Node *dst_node);

	/**
	 * Set the edge transfer function in direction to dst_node out of date
	 * @param dst_node Destination node
	 */
	void SetEdgeTransferFactorOutOfDate(PLC_Node *dst_node);

	/**
	 * Get the input impedance looking to dst_node
	 * @param dst_node Destination node
	 * @return Input impedance
	 */
	PLC_Impedance *GetInputImpedance(PLC_Node *dst_node);

	/**
	 * Caches the input and node impedances respectively in direction to dst_node
	 * @param dst_node Destination node
	 * @param input_impedance Input impedance
	 * @param load_impedance Load impedance
	 */
	void CacheImpedances(PLC_Node *dst_node, Ptr<PLC_Impedance> input_impedance, Ptr<PLC_Impedance> load_impedance);

	/**
	 * Inits the data structures used to cache the edge data
	 * @param dst_node Destination node
	 * @param time_variant Can be set true if already known that the input impedance of dst_node is time variant
	 */
	void InitEdgeTransferFactor(PLC_Node *dst_node, bool time_variant = false);

	/**
	 * Get the edge transfer unit for computation of the transfer function
	 * @param dst_node Destination node
	 * @return Pointer to the edge transfer unit instance
	 */
	PLC_EdgeTransferUnit *GetEdgeTransferUnit(PLC_Node *dst_node);

	/**
	 * Get the edge transfer unit but trigger an update cycle before
	 * @param dst_node Destination node
	 * @return Pointer to the edge transfer unit instance
	 */
	PLC_EdgeTransferUnit *GetUpdatedEdgeTransferUnit(PLC_Node *dst_node);

	std::vector<PLC_Node *> GetNodes(void);

protected:
	virtual void DoDispose(void);

	mutable PLC_Mutex			m_line_mutex;
	Ptr<const SpectrumModel> 	m_spectrum_model;
 	double 						m_propagation_delay;
	bool						added2graph;
 	double 						m_length;

	PLC_EdgeTransferDataMap		m_edge_transfer_data;
};

/**
 * \brief Line connecting to nodes
 */
class PLC_Line : public PLC_Edge
{
	friend class PLC_Node;

public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor of an edge of type line from node \from to node \to
	 * @param cable_type Instance of cable model
	 * @param from First node
	 * @param to Second node
	 */
	PLC_Line(Ptr<PLC_Cable> cable_type, Ptr<PLC_Node> from, Ptr<PLC_Node> to);
	~PLC_Line() {}

	/*
	 * definition of the inherited pure virtual functions
	 */
	double GetIdealPropagationDelay(void) { return m_propagation_delay; }

	Ptr<const PLC_Cable> GetCable(void) const { return m_cable; }
	Ptr<const PLC_FreqSelectiveImpedance> GetCharLineImp(void) const;
	Ptr<const PLC_FreqSelectiveImpedance> GetTransLineConst(void) const;

	void CalculateEdgeTransferFactor(PLC_Node *dst_node);
	double GetAttenuationApproxdB(void);

	void CalculateInputImpedance(PLC_Node *dst_node);

	/**
	 * Template function for the calculation of input impedance of line heading to the
	 * load impedance \z_l of type LoadImpedanceType
	 * If LoadImpedanceType if time variant ImpedanceReturnType has to be PLC_TimeVariantFrequencySelectiveValue
	 *
	 * @param z_l load impedance
	 * @return Input impedance
	 */
	template<typename ImpedanceReturnType, typename LoadImpedanceType>
	ImpedanceReturnType CalcLineInputImpedance(const LoadImpedanceType& z_l);

private:
	virtual void DoDispose(void);

	Ptr<PLC_Cable> 		m_cable;
};

/**
 * \brief Characterization of a two port network
 *
 *
 * Characterization of a two port network by its A,B,C,D parameters
 */
class PLC_TwoPort : public PLC_Edge
{
public:
	static TypeId GetTypeId(void);

	/**
	 * Constructor
	 *
	 * A,B,C,D parameters have to be an instance of PLC_ValueBase subclasses
	 *
	 * @param sm Used spectrum model
	 * @param from First node
	 * @param to Second node
	 * @param A
	 * @param B
	 * @param C
	 * @param D
	 */
	PLC_TwoPort(
				Ptr<const SpectrumModel> sm,
				Ptr<PLC_Node> from, Ptr<PLC_Node> to,
				Ptr<PLC_ValueBase> A, Ptr<PLC_ValueBase> B, Ptr<PLC_ValueBase> C, Ptr<PLC_ValueBase> D
				);

private:
	ushort timeVarianceIndicator;

	void CalculateInputImpedance(PLC_Node *dst_node);
	void CalculateEdgeTransferFactor(PLC_Node *dst_node);
	double GetAttenuationApproxdB(void);
	double GetIdealPropagationDelay(void);

	Ptr<PLC_ValueBase> m_A, m_B, m_C, m_D;
};

/**
 * A transformer can be seen as a two port network
 */
typedef PLC_TwoPort	PLC_Transformer;

}

#endif /* PLC_EDGE_H */
