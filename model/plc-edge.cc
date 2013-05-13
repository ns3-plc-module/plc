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
	this->m_spectrum_model = sm;
	this->m_length = CalculateDistance(from->GetPosition(), to->GetPosition());

	PLC_EdgeTransferData dataInit;
	dataInit.input_impedance.second.IsUp2Date 		= false;
	dataInit.input_impedance.second.IsTimeVariant 	= false;
	dataInit.etf_initialized						= false;

	this->m_edge_transfer_data[PeekPointer(from)] 	= dataInit;
	this->m_edge_transfer_data[PeekPointer(to)] 	= dataInit;

	from->AddEdge(to, Ptr<PLC_Edge> (this));
	to->AddEdge(from, Ptr<PLC_Edge> (this));
}

PLC_Edge::~PLC_Edge(void)
{
}

void
PLC_Edge::DoDispose (void)
{
	PLC_LOG_FUNCTION(this);
	m_spectrum_model = 0;
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

	m_edge_transfer_data[dst_node].input_impedance = eq_imp;
	m_edge_transfer_data[dst_node].load_impedance = load_impedance;
}

PLC_Node *
PLC_Edge::GetConnectedNode (PLC_Node *src_node)
{
	PLC_LOG_FUNCTION(this << src_node);
	PLC_Node *ret;
	PLC_EdgeTransferDataMap::iterator it = this->m_edge_transfer_data.begin();

	NS_ASSERT((this->m_edge_transfer_data.size() == 2) && ((it->first == src_node) || ((++it)->first == src_node)));

	for (it = this->m_edge_transfer_data.begin(); it != this->m_edge_transfer_data.end(); it++)
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
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());

	return this->m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date;
}

void
PLC_Edge::SetInputImpedanceOutOfDate (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);;
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());

	this->m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date = false;
}

bool
PLC_Edge::IsEdgeTransferFactorUp2Date (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());

	return this->m_edge_transfer_data[dst_node].edge_transfer_unit->IsUp2Date();
}

void
PLC_Edge::SetEdgeTransferFactorOutOfDate (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());

	this->m_edge_transfer_data[dst_node].edge_transfer_unit->SetOutOfDate();
}

PLC_Impedance *
PLC_Edge::GetInputImpedance (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());

	if (this->m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date == false)
		this->CalculateInputImpedance(dst_node);

	return PeekPointer(this->m_edge_transfer_data[dst_node].input_impedance.first);
}

void
PLC_Edge::InitEdgeTransferFactor (PLC_Node *dst_node, bool time_variant)
{
	PLC_LOG_FUNCTION(this << dst_node << time_variant);
	NS_ASSERT(this->m_edge_transfer_data.find (dst_node) != this->m_edge_transfer_data.end());
	NS_ASSERT_MSG(m_spectrum_model, "Spectrum model of edge " << this << " not set");

	if (!this->m_edge_transfer_data[dst_node].etf_initialized) {
		g_smartpointer_mutex.Lock ();
		this->m_edge_transfer_data[dst_node].edge_transfer_unit = CreateObject<PLC_EdgeTransferUnit> (this, dst_node, this->m_spectrum_model, time_variant);
		g_smartpointer_mutex.Unlock ();

		this->m_edge_transfer_data[dst_node].etf_initialized = true;
	}

	else if (time_variant && !this->m_edge_transfer_data[dst_node].edge_transfer_unit->IsTimeVariant()) {
		g_smartpointer_mutex.Lock ();
		this->m_edge_transfer_data[dst_node].edge_transfer_unit = CreateObject<PLC_EdgeTransferUnit> (this, dst_node, this->m_spectrum_model, true);
		g_smartpointer_mutex.Unlock ();
	}
}

PLC_EdgeTransferUnit *
PLC_Edge::GetEdgeTransferUnit(PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this);
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());
	NS_ASSERT(this->m_edge_transfer_data[dst_node].edge_transfer_unit != NULL);

	return PeekPointer(this->m_edge_transfer_data[dst_node].edge_transfer_unit);
}

PLC_EdgeTransferUnit *
PLC_Edge::GetUpdatedEdgeTransferUnit(PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());
	NS_ASSERT(this->m_edge_transfer_data[dst_node].edge_transfer_unit != NULL);

	if (this->m_edge_transfer_data[dst_node].edge_transfer_unit->IsUp2Date() == false)
	{
		this->CalculateEdgeTransferFactor(dst_node);
	}

	return PeekPointer(this->m_edge_transfer_data[dst_node].edge_transfer_unit);
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
	added2graph = false;
	this->m_spectrum_model = cable_type->GetSpectrumModel();

	this->m_propagation_delay = this->m_length / cable_type->GetPropSpeedApprox();
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
	NS_LOG_FUNCTION(this << dst_node);
	NS_LOG_INFO("Destination Node Id: " << dst_node->GetVertexId());

	PLC_Impedance *z_l_ptr;

	PLC_NodeOutEdgesMap outEdges;
	PLC_NodeOutEdgesMap::iterator outEdges_it;

	// get transmission line characteristics
	this->m_cable->Lock();
	PLC_FreqSelectiveImpedance z_c 		= *(this->m_cable->GetCharImp());
	PLC_FreqSelectiveImpedance gamma 	= *(this->m_cable->GetTransConst());
	this->m_cable->Unlock();

	NS_LOG_LOGIC("Characteristic impedance of the cable segment: " << z_c);
	NS_LOG_LOGIC("Transmission constant of the cable segment: " << gamma);

	// get connected lines of destination node
	dst_node->Lock();
	outEdges = dst_node->GetEdges();
	dst_node->Unlock();

	// destination node is leaf
	if (outEdges.size() == 1) {
		NS_LOG_INFO("Destination node is leaf");

		TypeId tid;
		bool IsOpenCircuit;

		NS_ASSERT(PeekPointer(outEdges.begin()->second) == this);

		dst_node->Lock();
		IsOpenCircuit = dst_node->IsOpenCircuit();
		dst_node->Unlock();

		// use characteristic impedance for input impedance as approximation for long lines
		if (this->m_length > PL_CHAR_IMPEDANCE_APPROX_THRESHOLD) {
			if (IsOpenCircuit)
				this->CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance>(z_c), NULL);
			else
				this->CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance>(z_c), dst_node->GetImpedancePtr());

			return;
		}

		if (IsOpenCircuit) {
			NS_LOG_INFO("Destination node is open circuit");

			// access impedance: z_a = A/C
			PLC_FreqSelectiveImpedance tmp = exp(2 * gamma * this->m_length);
			Ptr<PLC_FreqSelectiveImpedance> res = CreateObject<PLC_FreqSelectiveImpedance> (z_c * (tmp + 1) / (tmp - 1));

			NS_LOG_LOGIC("Line access impedance: " << *res);

			this->CacheImpedances(dst_node, res, NULL);

			return;
		}

		dst_node->Lock();
		z_l_ptr = dst_node->GetImpedancePeekPtr();
		dst_node->Unlock();

		Ptr<PLC_Impedance> res;

		switch (z_l_ptr->GetValueType()) {

			case PLC_ValueBase::CONSTANT:
			{
				res = CreateObject<PLC_FreqSelectiveImpedance>
						(
								this->CalcLineInputImpedance<PLC_FreqSelectiveImpedance, PLC_ConstImpedance>
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
								this->CalcLineInputImpedance<PLC_FreqSelectiveImpedance, PLC_FreqSelectiveImpedance>
								(
								*static_cast<PLC_FreqSelectiveImpedance *> (z_l_ptr)
								)
						);

				NS_LOG_INFO("Destination node frequency selective shunt impedance");
				break;
			}

			case PLC_ValueBase::TIMEVARIANT_CONSTANT:
			{
				res = CreateObject<PLC_TimeVariantFreqSelectiveImpedance>
						(
								this->CalcLineInputImpedance<PLC_TimeVariantFreqSelectiveImpedance, PLC_TimeVariantConstImpedance>
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
								this->CalcLineInputImpedance<PLC_TimeVariantFreqSelectiveImpedance, PLC_TimeVariantFreqSelectiveImpedance>
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
		this->CacheImpedances(dst_node, res, dst_node->GetImpedancePtr());
	}

	// destination node is not leaf
	else {
		NS_LOG_INFO("Destination is not leaf");

		Ptr<PLC_Impedance> res;
		std::vector<PLC_Impedance *> parallel_impedances;
		bool EqImpIsTimeVariant = false;

		dst_node->Lock();
		if (!dst_node->IsOpenCircuit())
		{
			NS_LOG_INFO("Destination node has parallel shunt impedance");
			PLC_Impedance *node_impedance = dst_node->GetImpedancePeekPtr();
			NS_ASSERT(node_impedance != NULL);

			node_impedance->Lock();
			if (node_impedance->IsTimeVariant())
				EqImpIsTimeVariant = true;
			node_impedance->Unlock();

			parallel_impedances.push_back(node_impedance);
		}
		dst_node->Unlock();

		std::vector<PLC_Edge *> edges;
		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++)
		{
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
			edges[i]->Lock();
			PLC_Node *new_dst = edges[i]->GetConnectedNode(dst_node);
			if (edges[i]->IsInputImpedanceUp2Date(new_dst) == false)
			{
				edges[i]->CalculateInputImpedance(new_dst);
			}
			edges[i]->Unlock();
		}

		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++) {
			PLC_Edge *cur_edge;
			PLC_Impedance *cur_eq_imp;

			if ((cur_edge = PeekPointer(outEdges_it->second)) == this) continue;

			cur_edge->Lock();
			PLC_Node *new_dst = cur_edge->GetConnectedNode(dst_node);
			cur_eq_imp = cur_edge->GetInputImpedance(new_dst);
			cur_edge->Unlock();

			cur_eq_imp->Lock();
			if (cur_eq_imp->IsTimeVariant())
				EqImpIsTimeVariant = true;
			cur_eq_imp->Unlock();

			parallel_impedances.push_back(cur_eq_imp);
		}

		Ptr<PLC_Impedance> z_l_tmp;
		PLC_FreqSelectiveImpedance tmp = tanh(gamma * this->m_length);

		if (!EqImpIsTimeVariant) {

			Ptr<PLC_FreqSelectiveImpedance> z_l = CalcEquivalentImpedance<PLC_FreqSelectiveImpedance> (this->m_spectrum_model, parallel_impedances);

			if (this->m_length > PL_CHAR_IMPEDANCE_APPROX_THRESHOLD) {
				this->CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance> (z_c), z_l);
				return;
			}

			z_l_tmp = z_l;
			res = CreateObject<PLC_FreqSelectiveImpedance> (z_c * ((*z_l) + (z_c * tmp)) / (z_c + ((*z_l) * tmp)));
		}

		else {

			Ptr<PLC_TimeVariantFreqSelectiveImpedance> z_l = CalcEquivalentImpedance<PLC_TimeVariantFreqSelectiveImpedance> (this->m_spectrum_model, parallel_impedances);

			if (this->m_length > PL_CHAR_IMPEDANCE_APPROX_THRESHOLD) {
				this->CacheImpedances(dst_node, CreateObject<PLC_FreqSelectiveImpedance> (z_c), z_l);
				return;
			}

			z_l_tmp = z_l;
			res = CreateObject<PLC_TimeVariantFreqSelectiveImpedance> (z_c * ((*z_l) + (z_c * tmp)) / (z_c + ((*z_l) * tmp)));
		}

		PLC_LOG_LOGIC("Line load impedance:" << *z_l_tmp);
		NS_LOG_LOGIC("Line access impedance: " << *res);

		this->CacheImpedances(dst_node, res, z_l_tmp);
	}
}

Ptr<const PLC_FreqSelectiveImpedance> PLC_Line::GetCharLineImp (void) const
{
	this->m_cable->Lock();
	Ptr <const PLC_FreqSelectiveImpedance> ret = this->m_cable->GetCharImp ();
	this->m_cable->Unlock();

	return ret;
}

Ptr<const PLC_FreqSelectiveImpedance> PLC_Line::GetTransLineConst (void) const
{
	PLC_LOG_FUNCTION(this);
	this->m_cable->Lock();
	Ptr<const PLC_FreqSelectiveImpedance> ret = this->m_cable->GetTransConst ();
	this->m_cable->Unlock();

	return ret;
}

void PLC_Line::CalculateEdgeTransferFactor (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);
	NS_ASSERT(this->m_edge_transfer_data.find(dst_node) != this->m_edge_transfer_data.end());

	PLC_FreqSelectiveImpedance gamma 	= *(this->GetTransLineConst());
	PLC_FreqSelectiveImpedance z_c 		= *(this->GetCharLineImp());

	NS_ASSERT(this->m_length > 0);
	PLC_FreqSelectiveImpedance tmp = gamma * this->m_length;
	PLC_FreqSelectiveImpedance e_valp = exp(tmp);
	PLC_FreqSelectiveImpedance e_valm = exp(-tmp);

	if (this->m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date == false)
		this->CalculateInputImpedance(dst_node);

	NS_ASSERT(this->m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date);

	Ptr<PLC_ValueBase> load_impedance = this->m_edge_transfer_data[dst_node].load_impedance;

	// indicates destination node is leaf and open circuit
	if (load_impedance == NULL) {

		PLC_LOG_LOGIC("Destination node is leaf and open circuit");

		dst_node->Lock();
		NS_ASSERT(dst_node->IsOpenCircuit());
		NS_ASSERT(dst_node->GetNumEdges() == 1);
		dst_node->Unlock();

		Ptr<PLC_FreqSelectiveValue> etv = CreateObject<PLC_FreqSelectiveValue> (2 / (e_valp + e_valm));
		this->m_edge_transfer_data[dst_node].edge_transfer_unit->SetEdgeTransferVector(etv);

		PLC_LOG_LOGIC("Calculated edge transfer vector: " << *etv);
	}

	else {

		load_impedance->Lock();
		PLC_ValueBase::PLC_ValueType imp_type = load_impedance->GetValueType();
		load_impedance->Unlock();

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

		this->m_edge_transfer_data[dst_node].edge_transfer_unit->SetEdgeTransferVector(etf);
		this->m_edge_transfer_data[dst_node].etf_initialized = true;
	}
}

double
PLC_Line::GetAttenuationApproxdB (void)
{
	PLC_LOG_FUNCTION(this);
	Ptr<const PLC_FreqSelectiveImpedance> gamma = this->GetTransLineConst();
	NS_ASSERT(this->m_spectrum_model == gamma->GetSpectrumModel());

	PLC_Value fc_g = (*gamma)[gamma->GetSpectrumModel()->GetNumBands()/2];

	return (-20*log(abs(exp(-this->m_length * fc_g))));
}

template<typename ImpedanceReturnType, typename LoadImpedanceType>
ImpedanceReturnType
PLC_Line::CalcLineInputImpedance (const LoadImpedanceType& z_l)
{
	PLC_LOG_FUNCTION(this);
	ImpedanceReturnType ret(z_l.GetSpectrumModel());

	this->m_cable->Lock();
	PLC_FreqSelectiveImpedance z_c 		= *(this->m_cable->GetCharImp());
	PLC_FreqSelectiveImpedance gamma 	= *(this->m_cable->GetTransConst());
	this->m_cable->Unlock();

	PLC_FreqSelectiveImpedance tmp = tanh(gamma * this->m_length);
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

	// get connected edges of destination node
	dst_node->Lock();
	outEdges = dst_node->GetEdges();
	dst_node->Unlock();

	// no connected nodes on transformer output side
	if (outEdges.size() == 1) {
		load_impedance = Ptr<PLC_Impedance> (Divide(m_A, m_C));
	}
	else {
		Ptr<PLC_Impedance> res;
		std::vector<PLC_Impedance *> parallel_impedances;
		bool EqImpIsTimeVariant = false;

		dst_node->Lock();
		if (!dst_node->IsOpenCircuit()) {
			PLC_Impedance *node_impedance = dst_node->GetImpedancePeekPtr();
			NS_ASSERT(node_impedance != NULL);

			node_impedance->Lock();
			if (node_impedance->IsTimeVariant())
				EqImpIsTimeVariant = true;
			node_impedance->Unlock();

			parallel_impedances.push_back(node_impedance);
		}
		dst_node->Unlock();

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
			edges[i]->Lock();
			PLC_Node *new_dst = edges[i]->GetConnectedNode(dst_node);
			if (edges[i]->IsInputImpedanceUp2Date(new_dst) == false) {
				edges[i]->CalculateInputImpedance(new_dst);
			}
			edges[i]->Unlock();
		}

		for (outEdges_it = outEdges.begin(); outEdges_it != outEdges.end(); outEdges_it++) {
			PLC_Edge *cur_edge;
			PLC_Impedance *cur_eq_imp;

			if ((cur_edge = PeekPointer(outEdges_it->second)) == this) continue;

			cur_edge->Lock();
			PLC_Node *new_dst = cur_edge->GetConnectedNode(dst_node);
			cur_eq_imp = cur_edge->GetInputImpedance(new_dst);
			cur_edge->Unlock();

			cur_eq_imp->Lock();
			if (cur_eq_imp->IsTimeVariant())
				EqImpIsTimeVariant = true;
			cur_eq_imp->Unlock();

			parallel_impedances.push_back(cur_eq_imp);
		}

		if (!EqImpIsTimeVariant)
			load_impedance = CalcEquivalentImpedance<PLC_FreqSelectiveImpedance> (this->m_spectrum_model, parallel_impedances);
		else
			load_impedance = CalcEquivalentImpedance<PLC_TimeVariantFreqSelectiveImpedance> (this->m_spectrum_model, parallel_impedances);
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

	this->CacheImpedances(dst_node, result, load_impedance);
}

void
PLC_TwoPort::CalculateEdgeTransferFactor (PLC_Node *dst_node)
{
	PLC_LOG_FUNCTION(this << dst_node);
	if (this->m_edge_transfer_data[dst_node].input_impedance.second.IsUp2Date == false)
		this->CalculateInputImpedance(dst_node);

	Ptr<PLC_Impedance> input_impedance = this->m_edge_transfer_data[dst_node].input_impedance.first;

	Ptr<PLC_ValueBase> prod = Multiply(m_A, input_impedance);
	Ptr<PLC_ValueBase> sum = Add(prod, m_B);
	Ptr<PLC_TransferBase> result = Divide(input_impedance, sum);

	this->m_edge_transfer_data[dst_node].edge_transfer_unit->SetEdgeTransferVector(result);
	this->m_edge_transfer_data[dst_node].etf_initialized = true;
}

// TODO
double
PLC_TwoPort::GetAttenuationApproxdB(void) { return 0; }

// TODO
double
PLC_TwoPort::GetIdealPropagationDelay(void) { return 0; }

}
