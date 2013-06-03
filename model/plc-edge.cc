/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012
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

#include <ns3/log.h>

#include "plc-value.h"
#include "plc-edge.h"
#include "plc-node.h"
#include "plc-graph.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("PLC_Edge");
NS_OBJECT_ENSURE_REGISTERED (PLC_Edge);
NS_OBJECT_ENSURE_REGISTERED (PLC_Line);
NS_OBJECT_ENSURE_REGISTERED (PLC_TwoPort);


TypeId
PLC_Edge::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::PLC_Edge")
				  .SetParent<Object> ()
				  ;
	return tid;
}

PLC_Edge::PLC_Edge (Ptr<const SpectrumModel> sm, Ptr<PLC_Node> from, Ptr<PLC_Node> to)
{
	PLC_LOG_FUNCTION(this);
	m_spectrum_model = sm;
	m_length = CalculateDistance(from->GetPosition(), to->GetPosition());

	PLC_EdgeTransferData dataInit;
	dataInit.impedance_mutex = new PLC_Mutex ();
	dataInit.input_impedance.first = NULL;
	dataInit.input_impedance.second.IsUp2Date 		= false;
	dataInit.input_impedance.second.IsTimeVariant 	= false;
	dataInit.etf_initialized						= false;

	m_edge_transfer_data[PeekPointer(from)] 	= dataInit;

	dataInit.impedance_mutex = new PLC_Mutex ();
	m_edge_transfer_data[PeekPointer(to)] 	= dataInit;

	from->AddEdge(to, Ptr<PLC_Edge> (this));
	to->AddEdge(from, Ptr<PLC_Edge> (this));

	added2graph = false;
	m_propagation_delay = 0;
}

PLC_Edge::~PLC_Edge(void)
{
}

void
PLC_Edge::DoDispose (void)
{
	PLC_LOG_FUNCTION(this);
	m_spectrum_model = 0;
	PLC_EdgeTransferDataMap::iterator eit;

	for (eit = m_edge_transfer_data.begin (); eit != m_edge_transfer_data.end (); eit++)
	{
		eit->second.load_impedance = 0;
		eit->second.edge_transfer_unit = 0;
		delete eit->second.impedance_mutex;
	}
}

void
PLC_Edge::CacheImpedances (PLC_Node *dst_node, Ptr<PLC_Impedance> input_impedance, Ptr<PLC_Impedance> load_impedance)
{
	PLC_LOG_FUNCTION(this);
	PLC_InputImpedance eq_imp;
	PLC_ImpedanceIndicator indicator;

	indicator.IsUp2Date = true;
	indicator.IsTimeVariant = input_impedance->IsTimeVariant();

	eq_imp.first 	= input_impedance;
	eq_imp.second 	= indicator;

	NS_ASSERT (m_edge_transfer_data.find (dst_node) != m_edge_transfer_data.end ());

	m_edge_transfer_data[dst_node].input_impedance = eq_imp;
	m_edge_transfer_data[dst_node].load_impedance = load_impedance;
}

PLC_Node *
PLC_Edge::GetConnectedNode (PLC_Node *src_node)
{
	PLC_LOG_FUNCTION(this << src_node);
	PLC_Node *ret;

	PLC_EdgeTransferDataMap::iterator it = m_edge_transfer_data.begin();

	NS_ASSERT((m_edge_transfer_data.size() == 2) && ((it->first == src_node) || ((++it)->first == src_node)));

	for (it = m_edge_transfer_data.begin(); it != m_edge_transfer_data.end(); it++)
	{
		if (it->first == src_node) continue;

		ret = it->first;
	}

	return ret;
}

bool
PLC_Edge::IsInputImpedanceUp2Date (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);

	LockImpedanceCache (dst_node);
	bool ret = m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date;
	UnlockImpedanceCache (dst_node);

	return ret;
}

void
PLC_Edge::SetInputImpedanceOutOfDate (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);

	LockImpedanceCache (dst_node);
	m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date = false;
	UnlockImpedanceCache (dst_node);
}

bool
PLC_Edge::IsEdgeTransferFactorUp2Date (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);

	LockEdgeTransferUnit (dst_node);
	bool ret = m_edge_transfer_data[dst_node].edge_transfer_unit->IsUp2Date();
	UnlockEdgeTransferUnit (dst_node);

	return ret;
}

void
PLC_Edge::SetEdgeTransferFactorOutOfDate (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);

	LockEdgeTransferUnit (dst_node);
	m_edge_transfer_data[dst_node].edge_transfer_unit->SetOutOfDate();
	UnlockEdgeTransferUnit (dst_node);
}

PLC_Impedance *
PLC_Edge::GetInputImpedance (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);

	if (IsInputImpedanceUp2Date (dst_node) == false)
	{
		CalculateInputImpedance(dst_node);
	}


	NS_ASSERT (IsInputImpedanceUp2Date (dst_node));

	LockImpedanceCache (dst_node);
	PLC_Impedance *ret = PeekPointer(m_edge_transfer_data[dst_node].input_impedance.first);
	UnlockImpedanceCache (dst_node);

	return ret;
}

void
PLC_Edge::InitEdgeTransferFactor (PLC_Node *dst_node, bool time_variant)
{
	PLC_LOG_FUNCTION(this << dst_node << time_variant);

	NS_ASSERT(m_edge_transfer_data.find (dst_node) != m_edge_transfer_data.end());
	NS_ASSERT_MSG(m_spectrum_model, "Spectrum model of edge " << this << " not set");

	if (!m_edge_transfer_data[dst_node].etf_initialized) {
		m_edge_transfer_data[dst_node].edge_transfer_unit = CreateObject<PLC_EdgeTransferUnit> (this, dst_node, m_spectrum_model, time_variant);
		m_edge_transfer_data[dst_node].etf_initialized = true;
	}

	else if (time_variant && !m_edge_transfer_data[dst_node].edge_transfer_unit->IsTimeVariant()) {
		m_edge_transfer_data[dst_node].edge_transfer_unit = CreateObject<PLC_EdgeTransferUnit> (this, dst_node, m_spectrum_model, true);
	}
}

PLC_EdgeTransferUnit *
PLC_Edge::GetEdgeTransferUnit(PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);


	NS_ASSERT(m_edge_transfer_data.find(dst_node) != m_edge_transfer_data.end());
	NS_ASSERT(m_edge_transfer_data[dst_node].edge_transfer_unit != NULL);

	PLC_EdgeTransferUnit *ret = PeekPointer(m_edge_transfer_data[dst_node].edge_transfer_unit);

	return ret;
}

PLC_EdgeTransferUnit *
PLC_Edge::GetUpdatedEdgeTransferUnit(PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);

	NS_ASSERT(m_edge_transfer_data.find(dst_node) != m_edge_transfer_data.end());
	NS_ASSERT(m_edge_transfer_data[dst_node].edge_transfer_unit != NULL);

	if (IsEdgeTransferFactorUp2Date (dst_node) == false)
	{
		CalculateEdgeTransferFactor(dst_node);
	}

	LockEdgeTransferUnit (dst_node);

	PLC_EdgeTransferUnit *ret = PeekPointer(m_edge_transfer_data[dst_node].edge_transfer_unit);

	UnlockEdgeTransferUnit (dst_node);

	return ret;
}

std::vector<PLC_Node *>
PLC_Edge::GetNodes(void)
{
	PLC_LOG_FUNCTION(this);
	std::vector<PLC_Node *> ret;

	ret.push_back(m_edge_transfer_data.begin()->first);
	ret.push_back((++m_edge_transfer_data.begin())->first);

	return ret;
}

void
PLC_Edge::LockImpedanceCache (PLC_Node *dst)
{
	PLC_LOG_FUNCTION (this << dst);
	NS_ASSERT (m_edge_transfer_data.find (dst) != m_edge_transfer_data.end ());
	m_edge_transfer_data[dst].impedance_mutex->Lock ();
}

void
PLC_Edge::UnlockImpedanceCache (PLC_Node *dst)
{
	PLC_LOG_FUNCTION (this << dst);
	NS_ASSERT (m_edge_transfer_data.find (dst) != m_edge_transfer_data.end ());
	m_edge_transfer_data[dst].impedance_mutex->Unlock ();
}

void
PLC_Edge::LockEdgeTransferUnit (PLC_Node *dst)
{
	PLC_LOG_FUNCTION (this << dst);
	NS_ASSERT (m_edge_transfer_data.find (dst) != m_edge_transfer_data.end ());
	NS_ASSERT (m_edge_transfer_data[dst].etf_initialized);
	m_edge_transfer_data[dst].edge_transfer_unit->Lock ();
}

void
PLC_Edge::UnlockEdgeTransferUnit (PLC_Node *dst)
{
	PLC_LOG_FUNCTION (this << dst);
	NS_ASSERT (m_edge_transfer_data.find (dst) != m_edge_transfer_data.end ());
	NS_ASSERT (m_edge_transfer_data[dst].etf_initialized);
	m_edge_transfer_data[dst].edge_transfer_unit->Unlock ();
}

////////////////////////////////////////// PLC_Line ///////////////////////////////////////////////////////////////////////

TypeId PLC_Line::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PLC_Line")
    				  .SetParent<PLC_Edge> ()
    				  ;
  return tid;
}

PLC_Line::PLC_Line(Ptr<PLC_Cable> cable_type, Ptr<PLC_Node> from, Ptr<PLC_Node> to)
	: PLC_Edge(cable_type->GetSpectrumModel(), from, to), m_cable(cable_type)
{
	PLC_LOG_FUNCTION(this);
	m_spectrum_model = cable_type->GetSpectrumModel();

	m_propagation_delay = m_length / cable_type->GetPropSpeedApprox();
}

void PLC_Line::DoDispose(void)
{
	PLC_LOG_FUNCTION(this);
	m_cable = 0;
	PLC_Edge::DoDispose();
}

void
PLC_Line::CalculateInputImpedance(PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);
	NS_LOG_INFO("Destination Node Id: " << dst_node->GetVertexId());

	PLC_Impedance *z_l_ptr;

	PLC_NodeOutEdgesMap outEdges;
	PLC_NodeOutEdgesMap::iterator outEdges_it;

	if (IsInputImpedanceUp2Date (dst_node))
	{
		// Input impedance was calculated by another thread in the meantime
		return;
	}

    LockImpedanceCache (dst_node);

	// get transmission line characteristics
	PLC_FreqSelectiveImpedance z_c 		= m_cable->GetCharImp();
	PLC_FreqSelectiveImpedance gamma 	= m_cable->GetTransConst();

	NS_LOG_LOGIC("Characteristic impedance of the cable segment: " << z_c);
	NS_LOG_LOGIC("Transmission constant of the cable segment: " << gamma);

	// get connected lines of destination node
	outEdges = dst_node->GetEdges();

	// destination node is leaf
	if (outEdges.size() == 1) {
		NS_LOG_INFO("Destination node is leaf");

		TypeId tid;
		bool IsOpenCircuit;

		NS_ASSERT(PeekPointer(outEdges.begin()->second) == this);

		IsOpenCircuit = dst_node->IsOpenCircuit();

		// use characteristic impedance for input impedance as approximation for long lines
		if (m_length > PL_CHAR_IMPEDANCE_APPROX_THRESHOLD) {
			if (IsOpenCircuit)
			{
				CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance>(z_c), NULL);
			}
			else
			{
				CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance>(z_c), dst_node->GetImpedancePtr());
			}

			UnlockImpedanceCache (dst_node);
			return;
		}

		if (IsOpenCircuit) {
			NS_LOG_INFO("Destination node is open circuit");

			// access impedance: z_a = A/C
			PLC_FreqSelectiveImpedance tmp = exp(-2 * gamma * m_length);
			Ptr<PLC_FreqSelectiveImpedance> res = CreateObject<PLC_FreqSelectiveImpedance> (z_c * (1 + tmp) / (1 - tmp));

			NS_LOG_LOGIC("Line access impedance: " << *res);

			CacheImpedances(dst_node, res, NULL);

			UnlockImpedanceCache (dst_node);
			return;
		}

		z_l_ptr = dst_node->GetImpedancePeekPtr();

		Ptr<PLC_Impedance> res;

		switch (z_l_ptr->GetValueType()) {

			case PLC_ValueBase::CONSTANT:
			{
				res = CreateObject<PLC_FreqSelectiveImpedance>
						(
								CalcLineInputImpedance<PLC_FreqSelectiveImpedance, PLC_ConstImpedance>
								(
								*static_cast<PLC_ConstImpedance *> (z_l_ptr)
								)
						);

				NS_LOG_INFO("Destination node has constant shunt impedance");
				break;
			}

			case PLC_ValueBase::FREQ_SELECTIVE:
			{
				res = CreateObject<PLC_FreqSelectiveImpedance>
						(
								CalcLineInputImpedance<PLC_FreqSelectiveImpedance, PLC_FreqSelectiveImpedance>
								(
								*static_cast<PLC_FreqSelectiveImpedance *> (z_l_ptr)
								)
						);

				NS_LOG_INFO("Destination node has frequency selective shunt impedance");
				break;
			}

			case PLC_ValueBase::TIMEVARIANT_CONSTANT:
			{
				res = CreateObject<PLC_TimeVariantFreqSelectiveImpedance>
						(
								CalcLineInputImpedance<PLC_TimeVariantFreqSelectiveImpedance, PLC_TimeVariantConstImpedance>
								(
								*static_cast<PLC_TimeVariantConstImpedance *> (z_l_ptr)
								)
						);

				NS_LOG_INFO("Destination node has time variant shunt impedance");

				break;
			}

			case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
			{
				res = CreateObject<PLC_TimeVariantFreqSelectiveImpedance>
						(
								CalcLineInputImpedance<PLC_TimeVariantFreqSelectiveImpedance, PLC_TimeVariantFreqSelectiveImpedance>
								(
								*static_cast<PLC_TimeVariantFreqSelectiveImpedance *> (z_l_ptr)
								)
						);

				NS_LOG_INFO("Destination node has time variant and frequency selective shunt impedance");

				break;
			}

			default:
			{
				NS_FATAL_ERROR("PLC_Line::CalculateInputImpedance(): incompatible load impedance type");
				break;
			}
		}

		PLC_LOG_LOGIC("Line load impedance:" << *(dst_node->GetImpedancePtr()));
		NS_LOG_LOGIC("Line access impedance: " << *res);
		CacheImpedances(dst_node, res, dst_node->GetImpedancePtr());
	}

	// destination node is not leaf
	else
	{
		NS_LOG_INFO("Destination is not leaf");

		Ptr<PLC_Impedance> res;
		std::vector<PLC_Impedance *> parallel_impedances;
		bool EqImpIsTimeVariant = false;

		if (!dst_node->IsOpenCircuit())
		{
			NS_LOG_INFO("Destination node has parallel shunt impedance");
			PLC_Impedance *node_impedance = dst_node->GetImpedancePeekPtr();
			NS_ASSERT(node_impedance != NULL);

			if (node_impedance->IsTimeVariant())
				EqImpIsTimeVariant = true;

			parallel_impedances.push_back(node_impedance);
		}

		std::vector<PLC_Edge *> edges;
		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++)
		{
			if (PeekPointer(outEdges_it->second) != this)
			{
				edges.push_back(PeekPointer(outEdges_it->second));
			}
		}

		int i;
		size_t num_edges = edges.size();
		NS_ASSERT(num_edges <= INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
		for (i = 0; i < (int) num_edges; i++) {
			PLC_Node *new_dst = edges[i]->GetConnectedNode(dst_node);
			if (edges[i]->IsInputImpedanceUp2Date(new_dst) == false)
			{
				edges[i]->CalculateInputImpedance(new_dst);
			}
		}

		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++) {
			PLC_Edge *cur_edge;
			PLC_Impedance *cur_eq_imp;

			if ((cur_edge = PeekPointer(outEdges_it->second)) == this) continue;

			PLC_Node *new_dst = cur_edge->GetConnectedNode(dst_node);
			cur_eq_imp = cur_edge->GetInputImpedance(new_dst);

			if (cur_eq_imp->IsTimeVariant())
			{
				EqImpIsTimeVariant = true;
			}

			parallel_impedances.push_back(cur_eq_imp);
		}

		Ptr<PLC_Impedance> z_l_tmp;
		PLC_FreqSelectiveImpedance tmp = tanh(gamma * m_length);

		if (!EqImpIsTimeVariant) {

			Ptr<PLC_FreqSelectiveImpedance> z_l = CalcEquivalentImpedance<PLC_FreqSelectiveImpedance> (m_spectrum_model, parallel_impedances);

			if (m_length > PL_CHAR_IMPEDANCE_APPROX_THRESHOLD) {
				CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance> (z_c), z_l);
				return;
			}

			z_l_tmp = z_l;
			res = CreateObject<PLC_FreqSelectiveImpedance> (z_c * ((*z_l) + (z_c * tmp)) / (z_c + ((*z_l) * tmp)));
		}

		else {

			Ptr<PLC_TimeVariantFreqSelectiveImpedance> z_l = CalcEquivalentImpedance<PLC_TimeVariantFreqSelectiveImpedance> (m_spectrum_model, parallel_impedances);

			if (m_length > PL_CHAR_IMPEDANCE_APPROX_THRESHOLD) {
				CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance> (z_c), z_l);

				UnlockImpedanceCache (dst_node);
				return;
			}

			z_l_tmp = z_l;
			res = CreateObject<PLC_TimeVariantFreqSelectiveImpedance> (z_c * ((*z_l) + (z_c * tmp)) / (z_c + ((*z_l) * tmp)));
		}

		PLC_LOG_LOGIC("Line load impedance:" << *z_l_tmp);
		NS_LOG_LOGIC("Line access impedance: " << *res);

		CacheImpedances(dst_node, res, z_l_tmp);
	}

	UnlockImpedanceCache (dst_node);
}

PLC_FreqSelectiveImpedance
PLC_Line::GetCharLineImp (void) const
{
	PLC_LOG_FUNCTION(this);
	PLC_FreqSelectiveImpedance ret = m_cable->GetCharImp ();

	return ret;
}

PLC_FreqSelectiveImpedance
PLC_Line::GetTransLineConst (void) const
{
	PLC_LOG_FUNCTION(this);
	PLC_FreqSelectiveImpedance ret = m_cable->GetTransConst ();

	return ret;
}

void
PLC_Line::CalculateEdgeTransferFactor (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);

	if (IsEdgeTransferFactorUp2Date (dst_node))
	{
		// Edge transfer factor was calculated by another thread in the meantime
		return;
	}

	LockEdgeTransferUnit (dst_node);

	PLC_FreqSelectiveImpedance gamma 	= GetTransLineConst ();
	PLC_FreqSelectiveImpedance z_c 		= GetCharLineImp ();

	NS_ASSERT(m_length > 0);
	PLC_FreqSelectiveImpedance tmp = gamma * m_length;
	PLC_FreqSelectiveImpedance e_valp = exp(tmp);
	PLC_FreqSelectiveImpedance e_valm = exp(-tmp);

	if (IsInputImpedanceUp2Date (dst_node) == false)
	{
		CalculateInputImpedance(dst_node);
	}

	NS_ASSERT(IsInputImpedanceUp2Date (dst_node));

	LockImpedanceCache (dst_node);
	Ptr<PLC_ValueBase> load_impedance = m_edge_transfer_data[dst_node].load_impedance;
	UnlockImpedanceCache (dst_node);


	// indicates destination node is leaf and open circuit
	if (load_impedance == NULL) {

		PLC_LOG_LOGIC("Destination node is leaf and open circuit");

		NS_ASSERT(dst_node->IsOpenCircuit());
		NS_ASSERT(dst_node->GetNumEdges() == 1);

		Ptr<PLC_FreqSelectiveValue> etv = CreateObject<PLC_FreqSelectiveValue> (2 / (e_valp + e_valm));
		m_edge_transfer_data[dst_node].edge_transfer_unit->SetEdgeTransferVector(etv);

		PLC_LOG_LOGIC("Calculated edge transfer vector: " << *etv);
	}

	else
	{
		PLC_ValueBase::PLC_ValueType imp_type = load_impedance->GetValueType();

		Ptr<PLC_TransferBase> etf;

		switch (imp_type) {

			case PLC_ValueBase::CONSTANT:
			{
				PLC_ConstImpedance z_l = *static_cast<PLC_ConstImpedance *> (PeekPointer(load_impedance));
				PLC_FreqSelectiveValue reflection_factor = (z_l - z_c) / (z_l + z_c);
				NS_LOG_LOGIC("Reflection factor: " << reflection_factor);
				etf = CreateObject<PLC_FreqSelectiveValue> ((1 + reflection_factor) / (e_valp + (reflection_factor * e_valm)));
				break;
			}

			case PLC_ValueBase::FREQ_SELECTIVE:
			{
				PLC_FreqSelectiveImpedance z_l = *static_cast<PLC_FreqSelectiveImpedance *> (PeekPointer(load_impedance));
				PLC_FreqSelectiveValue reflection_factor = (z_l - z_c) / (z_l + z_c);
				NS_LOG_LOGIC("Reflection factor: " << reflection_factor);
				etf = CreateObject<PLC_FreqSelectiveValue> ((1 + reflection_factor) / (e_valp + (reflection_factor * e_valm)));
				break;
			}

			case PLC_ValueBase::TIMEVARIANT_CONSTANT:
			{
				PLC_TimeVariantConstImpedance z_l = *static_cast<PLC_TimeVariantConstImpedance *> (PeekPointer(load_impedance));
				PLC_TimeVariantFreqSelectiveValue reflection_factor = (z_l - z_c) / (z_l + z_c);
				NS_LOG_LOGIC("Reflection factor: " << reflection_factor);
				etf = CreateObject<PLC_TimeVariantFreqSelectiveValue> ((1 + reflection_factor) / (e_valp + (reflection_factor * e_valm)));
				break;
			}

			case PLC_ValueBase::TIMEVARIANT_FREQ_SELECTIVE:
			{
				PLC_TimeVariantFreqSelectiveImpedance z_l = *static_cast<PLC_TimeVariantFreqSelectiveImpedance *> (PeekPointer(load_impedance));
				PLC_TimeVariantFreqSelectiveValue reflection_factor = (z_l - z_c) / (z_l + z_c);
				NS_LOG_LOGIC("Reflection factor: " << reflection_factor);
				etf = CreateObject<PLC_TimeVariantFreqSelectiveValue> ((1 + reflection_factor) / (e_valp + (reflection_factor * e_valm)));
				break;
			}

			default:
			{
				NS_FATAL_ERROR("PLC_Line::CalculateEdgeTransferFactor(): incompatible load impedance type");
				break;
			}
		}

		PLC_LOG_LOGIC("Calculated edge transfer vector: " << *etf);

		m_edge_transfer_data[dst_node].edge_transfer_unit->SetEdgeTransferVector(etf);
	}

	// Unlock edge transfer unit for multithread processing
	UnlockEdgeTransferUnit (dst_node);
}

double
PLC_Line::GetAttenuationApproxdB (void)
{
	PLC_LOG_FUNCTION(this);
	PLC_FreqSelectiveImpedance gamma = GetTransLineConst();
	NS_ASSERT(m_spectrum_model == gamma.GetSpectrumModel());

	PLC_Value fc_g = gamma[gamma.GetSpectrumModel()->GetNumBands()/2];

	return (-20*log(abs(exp(-m_length * fc_g))));
}

template<typename ImpedanceReturnType, typename LoadImpedanceType>
ImpedanceReturnType
PLC_Line::CalcLineInputImpedance (const LoadImpedanceType& z_l)
{
	PLC_LOG_FUNCTION(this);
	ImpedanceReturnType ret(z_l.GetSpectrumModel());

	PLC_FreqSelectiveImpedance z_c 		= m_cable->GetCharImp();
	PLC_FreqSelectiveImpedance gamma 	= m_cable->GetTransConst();

	PLC_FreqSelectiveImpedance tmp = tanh(gamma * m_length);
	ret = z_c * (z_l + (z_c * tmp)) / (z_c + (z_l * tmp));

	return ret;
}

///////////////////////////////////////////////// PLC_TwoPort ////////////////////////////////////////////////////////////

PLC_TwoPort::PLC_TwoPort(Ptr<const SpectrumModel> sm,
			Ptr<PLC_Node> from, Ptr<PLC_Node> to,
			Ptr<PLC_ValueBase> A, Ptr<PLC_ValueBase> B, Ptr<PLC_ValueBase> C, Ptr<PLC_ValueBase> D)
	: PLC_Edge(sm, to, from), m_A(A), m_B(B), m_C(C), m_D(D)
{
}

TypeId PLC_TwoPort::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::PLC_TwoPort")
				  .SetParent<PLC_Edge> ()
				  ;
	return tid;
}

void
PLC_TwoPort::CalculateInputImpedance (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);
	Ptr<PLC_Impedance> load_impedance;

	PLC_NodeOutEdgesMap outEdges;
	PLC_NodeOutEdgesMap::iterator outEdges_it;

	if (IsInputImpedanceUp2Date (dst_node))
	{
		// Input impedance was calculated by another thread in the meantime
		return;
	}

    LockImpedanceCache (dst_node);

	// get connected edges of destination node
	outEdges = dst_node->GetEdges();

	// no connected nodes on transformer output side
	if (outEdges.size() == 1) {
		load_impedance = Ptr<PLC_Impedance> (Divide(m_A, m_C));
	}
	else {
		Ptr<PLC_Impedance> res;
		std::vector<PLC_Impedance *> parallel_impedances;
		bool EqImpIsTimeVariant = false;

		if (!dst_node->IsOpenCircuit()) {
			PLC_Impedance *node_impedance = dst_node->GetImpedancePeekPtr();
			NS_ASSERT(node_impedance != NULL);

			if (node_impedance->IsTimeVariant())
				EqImpIsTimeVariant = true;

			parallel_impedances.push_back(node_impedance);
		}

		std::vector<PLC_Edge *> edges;
		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++) {
			if (PeekPointer(outEdges_it->second) != this)
				edges.push_back(PeekPointer(outEdges_it->second));
		}

		int i;
		size_t num_edges = edges.size();
		NS_ASSERT(num_edges <= INT_MAX);

#ifdef PLC_MULTITHREADING
#pragma omp parallel for
#endif
		for (i = 0; i < (int) num_edges; i++) {
			PLC_Node *new_dst = edges[i]->GetConnectedNode(dst_node);
			if (edges[i]->IsInputImpedanceUp2Date(new_dst) == false)
			{
				edges[i]->CalculateInputImpedance(new_dst);
			}
		}

		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++) {
			PLC_Edge *cur_edge;
			PLC_Impedance *cur_eq_imp;

			if ((cur_edge = PeekPointer(outEdges_it->second)) == this) continue;

			PLC_Node *new_dst = cur_edge->GetConnectedNode(dst_node);
			cur_eq_imp = cur_edge->GetInputImpedance(new_dst);

			if (cur_eq_imp->IsTimeVariant())
				EqImpIsTimeVariant = true;

			parallel_impedances.push_back(cur_eq_imp);
		}

		if (!EqImpIsTimeVariant)
			load_impedance = CalcEquivalentImpedance<PLC_FreqSelectiveImpedance> (m_spectrum_model, parallel_impedances);
		else
			load_impedance = CalcEquivalentImpedance<PLC_TimeVariantFreqSelectiveImpedance> (m_spectrum_model, parallel_impedances);
	}

	// we have to save intermediate results in a smartpointer instance,
	// otherwise the value would be deleted by the smartpointer class
	Ptr<PLC_ValueBase> prod = Multiply(m_A, load_impedance);
	Ptr<PLC_ValueBase> sum1 = Add(prod, m_B);
	prod = Multiply(m_C, load_impedance);
	Ptr<PLC_ValueBase> sum2 = Add(prod, m_D);
	Ptr<PLC_Impedance> result = Divide(sum1, sum2);

	PLC_LOG_LOGIC("load_impedance: " << *load_impedance);
	PLC_LOG_LOGIC("input_impedance: " << *result);

	CacheImpedances(dst_node, result, load_impedance);

    UnlockImpedanceCache (dst_node);
}

void
PLC_TwoPort::CalculateEdgeTransferFactor (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);

	if (IsEdgeTransferFactorUp2Date (dst_node))
	{
		// Edge transfer factor was calculated by another thread in the meantime
		return;
	}

	LockEdgeTransferUnit (dst_node);

	if (IsInputImpedanceUp2Date (dst_node) == false)
	{
		CalculateInputImpedance(dst_node);
	}

	LockImpedanceCache (dst_node);
	Ptr<PLC_Impedance> input_impedance = m_edge_transfer_data[dst_node].input_impedance.first;
	UnlockImpedanceCache (dst_node);

	Ptr<PLC_ValueBase> prod = Multiply(m_A, input_impedance);
	Ptr<PLC_ValueBase> sum = Add(prod, m_B);
	Ptr<PLC_TransferBase> result = Divide(input_impedance, sum);

	m_edge_transfer_data[dst_node].edge_transfer_unit->SetEdgeTransferVector(result);
	m_edge_transfer_data[dst_node].etf_initialized = true;

	UnlockEdgeTransferUnit (dst_node);
}

// TODO
double
PLC_TwoPort::GetAttenuationApproxdB(void) { return 0; }

// TODO
double
PLC_TwoPort::GetIdealPropagationDelay(void) { return 0; }

}
