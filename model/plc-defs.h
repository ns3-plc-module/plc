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

#ifndef PLC_DEFS_H_
#define PLC_DEFS_H_

#include <ns3/object.h>

#include <complex>
#include <climits>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/undirected_dfs.hpp>
#include <boost/pending/indirect_cmp.hpp>

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

/**
 * Global definition for the PLC simulation
 */

#ifdef _OPENMP
#include <omp.h>
#define PLC_MULTITHREADING
#endif

#define PLC_USE_IMPEDANCE_HASHING

namespace ns3 {

#define MAX_X	100000
#define MAX_Y	100000
#define MAX_Z	100000

#define PL_PERIOD_EUROPE	0.02 // s
#define PLC_RECEIVER_SENSIVITY -85 // dBm
//#define PLC_NODAL_ATT_COMP 3
#define PL_CHAR_IMPEDANCE_APPROX_THRESHOLD 10000

#define CCA_THRESHOLD_POWER	1e-6 // mW
#define CCA_NUM_SYMBOLS	8
#define MAX_REPLAY_ATTEMPTS 500
#define MAX_IR_PACKETS 100
#define REPLAY_TIMEOUT 20000 // replay timeout in us
#define MAX_CSMACA_ATTEMPTS 1000
#define MAX_RELAY_ADVANCE 300
#define REDUNDANCY_DIVISOR 20

#define EDGE_GEN_SEED	32u
#define LINE_GEN_SEED	124u
#define NODE_GEN_SEED	62u
#define CONST_IMP_NODE_GEN_SEED	723u
#define CONST_IMP_REAL_GEN_SEED	22u
#define CONST_IMP_IMAG_GEN_SEED 82u

#define CreateBestCaseBgNoise(sm) 	Create<PLC_ColoredNoiseFloor>(-145, 53.23, -0.337, sm)
#define CreateWorstCaseBgNoise(sm) 	Create<PLC_ColoredNoiseFloor>(-140, 38.75, -0.72, sm)

enum ModulationAndCodingType
{
	BPSK_1_4,
	BPSK_1_2,
	QPSK_1_2,
	QAM16_1_2,
	QAM64_16_21,
	BPSK_RATELESS,
	QAM4_RATELESS,
	QAM16_RATELESS,
	QAM32_RATELESS,
	QAM64_RATELESS
};

std::ostream& operator<<(std::ostream& os, ModulationAndCodingType type);
double GetCodeRate (ModulationAndCodingType mcs);
size_t GetBitsPerSymbol (ModulationAndCodingType mcs);

#define PLC_LOG_ENABLE(PLC_LOG_LEVEL)\
	do {\
		LogComponentEnable("PLC_Cable", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Edge", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Node", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Graph", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Interface", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Outlet", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Channel", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_ErrorModel", PLC_LOG_LEVEL);\
		LogComponentEnable("PLC_Phy", LOG_LEVEL_INFO);\
		LogComponentEnable("PLC_Mac", LOG_LEVEL_INFO);\
	} while(0)

struct PLC_Mutex;
extern PLC_Mutex g_log_mutex;
extern PLC_Mutex g_smartpointer_mutex;

#define PLC_LOG_FUNCTION(parameters)\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_FUNCTION(parameters);\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_LOG_FUNCTION_NOARGS()\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_FUNCTION_NOARGS();\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_LOG_LOGIC(msg)\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_LOGIC(msg);\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_LOG_ERROR(msg)\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_ERROR(msg));\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_LOG_WARN(msg)\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_WARN(msg);\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_LOG_DEBUG(msg))\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_DEBUG(msg);\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_LOG_INFO(msg)\
	do {\
		g_log_mutex.Lock();\
		NS_LOG_INFO(msg);\
		g_log_mutex.Unlock();\
	} while(0)

#define PLC_ASSERT_MSG(condition, msg)\
	do {\
		g_log_mutex.Lock();\
		NS_ASSERT_MSG(condition, msg);\
		g_log_mutex.Unlock();\
	} while(0)


#ifdef _OPENMP
struct PLC_Mutex
{
	PLC_Mutex() { omp_init_lock(&lock); }
	~PLC_Mutex() { omp_destroy_lock(&lock); }

	void Lock() const { omp_set_lock(&lock); }
	void Unlock() const { omp_unset_lock(&lock); }

	PLC_Mutex(const PLC_Mutex& ) { omp_init_lock(&lock); }
	PLC_Mutex& operator= (const PLC_Mutex& ) { return *this; }

public:
	mutable omp_lock_t lock;
};

#else

struct PLC_Mutex
{
	void Lock() {}
	void Unlock() {}
};
#endif

	typedef std::pair<unsigned int, std::pair<unsigned int, unsigned int> > PLC_BackboneBranchKey;

	class PLC_Edge;
	class PLC_Node;
	class PLC_Line;

	typedef std::vector<double> PLC_FreqSelectiveRealValue;
	typedef std::vector<double> PLC_TimeVariantRealValue;
	typedef std::vector<std::vector<double> > PLC_TimeVariantFreqSelectiveRealValue;
	typedef std::vector<double> PLC_FreqSelectiveResistance;
	typedef std::vector<double> PLC_FreqSelectiveConductance;
	typedef std::vector<double> PLC_FreqSelectiveCapacitance;
	typedef std::vector<double> PLC_FreqSelectiveInductance;

	typedef std::complex<double> 	PLC_Value;
	typedef std::vector<PLC_Value>	PLC_ValueSpectrum;
	typedef std::vector<PLC_Value> 	PLC_TimeVariantValue;
	typedef std::vector<PLC_ValueSpectrum> PLC_TimeVariantValueSpectrum;

	typedef PLC_Value			PLC_ImpedanceValue;
	typedef PLC_ValueSpectrum	PLC_ImpedanceSpectrum;

	class PLC_ConstValue;
	class PLC_FreqSelectiveValue;

	class PLC_ValueBase;
	class PLC_ConstValue;
	class PLC_FreqSelectiveValue;
	class PLC_TimeVariantConstValue;
	class PLC_TimeVariantFreqSelectiveValue;

	typedef PLC_Value							PLC_ImpedanceValue;
	typedef PLC_ValueSpectrum					PLC_ImpedanceSpectrum;
	typedef PLC_ValueBase						PLC_Impedance;
	typedef PLC_ConstValue						PLC_ConstImpedance;
	typedef PLC_FreqSelectiveValue				PLC_FreqSelectiveImpedance;
	typedef PLC_TimeVariantConstValue			PLC_TimeVariantConstImpedance;
	typedef PLC_TimeVariantFreqSelectiveValue	PLC_TimeVariantFreqSelectiveImpedance;

	typedef PLC_ValueBase						PLC_TransferBase;
	typedef PLC_FreqSelectiveValue				PLC_TransferVector;
	typedef PLC_TimeVariantFreqSelectiveValue	PLC_TimeVariantTransferVector;

	typedef struct PLC_ImpedanceIndicator_t
	{
		bool IsUp2Date;
		bool IsTimeVariant;
	} PLC_ImpedanceIndicator;

	typedef std::pair<Ptr<PLC_Impedance>, PLC_ImpedanceIndicator> 	PLC_InputImpedance;

	class PLC_EdgeTransferUnit;

	typedef struct PLC_EdgeTransferData_t
	{
		PLC_InputImpedance 			input_impedance;
		Ptr<PLC_Impedance>			load_impedance;
		Ptr<PLC_EdgeTransferUnit> 	edge_transfer_unit;
		bool 						etf_initialized;
	} PLC_EdgeTransferData;

	typedef std::map<PLC_Node *, PLC_EdgeTransferData> PLC_EdgeTransferDataMap;

	class PLC_BackboneBranch;

	typedef std::vector<Ptr<PLC_BackboneBranch> > PLC_BackbonePath;
	typedef std::map<PLC_Node *, Ptr<PLC_Line> > PLC_NodeOutlinesMap;

	typedef std::map<PLC_Node *, Ptr<PLC_Edge> > PLC_NodeOutEdgesMap;

	class PLC_TxInterface;
	class PLC_RxInterface;

	typedef std::set<std::pair<PLC_TxInterface *, PLC_RxInterface *> > PLC_InterfaceTupel;
	typedef std::pair<Ptr<PLC_Node>, double>		PLC_RandomNodeDescriptor;
	typedef std::vector<PLC_RandomNodeDescriptor> 	PLC_RandomLevelDescriptor;

	class SpectrumValue;
	typedef uint32_t Timeslot;

	typedef std::map<Timeslot, std::pair<Timeslot, Ptr<SpectrumValue> > >	PLC_RxPsdMap;
	// < rxInterface id, time variant rx PSDs >
	typedef std::map<uint32_t, PLC_RxPsdMap >				PLC_ReceiveDescriptorMap;
	// < txInterface id, receive descriptor >
	typedef std::map<uint32_t, PLC_ReceiveDescriptorMap>	PLC_TransmissionDescriptorMap;

	class PLC_Outlet;
	class PLC_NoiseSource;
	class PLC_TwoPort;
	class PLC_NetDevice;

	typedef PLC_TwoPort	PLC_Transformer;

	typedef std::vector<Ptr<PLC_Node> > 		PLC_NodeList;
	typedef std::vector<Ptr<PLC_Outlet> > 		PLC_OutletList;
	typedef std::vector<Ptr<PLC_NoiseSource> > 	PLC_NoiseSourceList;
	typedef std::vector<Ptr<PLC_Transformer> > 	PLC_TransformerList;
	typedef std::vector<Ptr<PLC_NetDevice> > 	PLC_NetdeviceList;

	typedef std::map<std::string, Ptr<PLC_NetDevice> > PLC_NetdeviceMap;
}

namespace boost {

	enum vertex_nodeptr_t { vertex_nodeptr };
	BOOST_INSTALL_PROPERTY(vertex, nodeptr);

	enum edge_plc_edgeptr_t { edge_plc_edgeptr };
	BOOST_INSTALL_PROPERTY(edge, plc_edgeptr);

	typedef property<vertex_nodeptr_t, ns3::PLC_Node *, property<vertex_color_t, default_color_type> > VertexProperty;
	typedef property<edge_weight_t, double, property<edge_color_t, default_color_type, property<edge_plc_edgeptr_t, ns3::PLC_Edge *> > > EdgeProperty;

	typedef adjacency_list <vecS, vecS, undirectedS, VertexProperty, EdgeProperty> UGraph;

	typedef std::pair<int, int> Edge;
	typedef graph_traits<UGraph>::vertex_descriptor vertex_descriptor;
	typedef graph_traits<UGraph>::edge_descriptor edge_descriptor;

	typedef property_map<UGraph, vertex_color_t>::type VertexColorMap;
	typedef property_map<UGraph, edge_color_t>::type EdgeColorMap;

	typedef graph_traits<UGraph>::vertex_iterator vertex_iterator;

	typedef property_traits<VertexColorMap>::value_type ColorValue;
	typedef color_traits<ColorValue> Color;

	typedef boost::minstd_rand base_generator_type;

	typedef boost::uniform_int<> distribution_type;
	typedef boost::variate_generator<boost::base_generator_type&, distribution_type> gen_type;
}

namespace ns3 {

	class PLC_BackboneBranch;
	class PLC_TxInterface;
	class PLC_RxInterface;

	typedef struct boostgraph_copy_t
	{
		boost::UGraph 			graph;
		mutable PLC_Mutex		graph_mutex;
	} boostgraph_copy;

	typedef struct thread_arg_t
	{
		boostgraph_copy *graph_copy;
		PLC_TxInterface *txInterface;
		PLC_RxInterface *rxInterface;
	} thread_arg;

	typedef struct sub_thread_arg_t
	{
		boostgraph_copy 	*graph_copy;
		PLC_BackboneBranch 	*bb;
	} sub_thread_arg;

	typedef struct backbone_branch_discover_thread_arg_t
	{
		boost::UGraph 		*graph_copy;
		PLC_Mutex			*graph_copy_mutex;
		PLC_BackboneBranch 	*bb;
	} backbone_branch_discover_thread_arg;
}

#endif /* PLC_DEFS_H_ */
