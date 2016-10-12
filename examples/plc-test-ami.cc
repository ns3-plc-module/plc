/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 University of British Columbia, Vancouver
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
 * Author: Fariba Aalamifar <faribaa@ece.ubc.ca>
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

//#include <QApplication>

#include <ns3/core-module.h>
#include <ns3/nstime.h>
#include <ns3/simulator.h>
#include <ns3/packet.h>
#include <ns3/output-stream-wrapper.h>
#include <ns3/gnuplot.h>
#include <ns3/trace-source-accessor.h>

#include "ns3/plc.h"

using namespace ns3;


int main (int argc, char *argv[])
{
	// Initialize physical environment
	PLC_Time::SetTimeModel(60, MicroSeconds(735)); // 60Hz main frequency, symbol length 735us (G3) (defines time granularity)

	// Define spectrum model
    PLC_SpectrumModelHelper smHelper;
    Ptr<const SpectrumModel> sm;
    sm = smHelper.GetG3SpectrumModel();

    Ptr<SpectrumValue> txPsd = Create<SpectrumValue> (sm);
    (*txPsd) = 1e-8; // -50dBm/Hz

    // Create cable types
	Ptr<PLC_Cable> mainCable = CreateObject<PLC_MV_Overhead_Cable> (sm);
	Ptr<PLC_Cable> houseCable = CreateObject<PLC_NAYY150SE_Cable> (sm);

	// Node shunt impedance
	Ptr<PLC_ConstImpedance> shuntImp = Create<PLC_ConstImpedance> (sm, PLC_Value(50, 0));

	Ptr<PLC_Graph> graph = CreateObject<PLC_Graph> ();

	Ptr<PLC_Node> n1 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n2 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n3 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n4 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n5 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n6 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n7 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n8 = CreateObject<PLC_Node> ();

	n1->SetPosition(0,0,0);
	n2->SetPosition(20,0,0);
	n3->SetPosition(40,00,0);
	n4->SetPosition(60,0,0);
	n5->SetPosition(0,100,0);
	n6->SetPosition(20,100,0);
	n7->SetPosition(40,100,0);
	n8->SetPosition(60,100,0);

	n5->SetName("TX/RX Node1");
	n6->SetName("TX/RX Node2");
	n7->SetName("TX/RX Node3");
	n8->SetName("TX/RX Node4");
	n1->SetName("Outlet1");
	n2->SetName("Outlet2");
	n3->SetName("Outlet3");
	n4->SetName("Outlet4");

	graph->AddNode(n1);
	graph->AddNode(n2);
	graph->AddNode(n3);
	graph->AddNode(n4);
	graph->AddNode(n5);
	graph->AddNode(n6);
	graph->AddNode(n7);
	graph->AddNode(n8);

	CreateObject<PLC_Line> (mainCable, n1, n2);
	CreateObject<PLC_Line> (mainCable, n2, n3);
	CreateObject<PLC_Line> (mainCable, n3, n4);
	CreateObject<PLC_Line> (houseCable, n1, n5);
	CreateObject<PLC_Line> (houseCable, n2, n6);
	CreateObject<PLC_Line> (houseCable, n3, n7);
	CreateObject<PLC_Line> (houseCable, n4, n8);

	Ptr<PLC_Channel> channel = CreateObject<PLC_Channel> ();
	channel->SetGraph(graph);

	Ptr<PLC_Outlet> outlet1 = CreateObject<PLC_Outlet> (n1, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet2 = CreateObject<PLC_Outlet> (n2, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet3 = CreateObject<PLC_Outlet> (n3, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet4 = CreateObject<PLC_Outlet> (n4, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet5 = CreateObject<PLC_Outlet> (n5, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet6 = CreateObject<PLC_Outlet> (n6, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet7 = CreateObject<PLC_Outlet> (n7, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));
	Ptr<PLC_Outlet> outlet8 = CreateObject<PLC_Outlet> (n8, Create<PLC_ConstImpedance> (sm, PLC_Value(50,0)));

//	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n4, sm));
	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n4, sm));
	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n5, sm));
//	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n5, sm));
//	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n7, sm));
//	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n7, sm));
//	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n8, sm));
//	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n8, sm));

	channel->InitTransmissionChannels();
	channel->CalcTransmissionChannels();

//	Simulator::Schedule(Seconds(0.5), &PLC_Outlet::SetImpedance, outlet7, Create<PLC_TimeVariantFreqSelectiveImpedance> (PLC_ConstImpedance(sm, PLC_Value(5,0))), true);
//	Simulator::Schedule(Seconds(1), &PLC_Outlet::SetImpedance, outlet3, Create<PLC_ConstImpedance> (sm, PLC_Value(5,0)), true);
//	Simulator::Schedule(Seconds(2), &PLC_Outlet::SetImpedance, outlet6, Create<PLC_ConstImpedance> (sm, PLC_Value(5,0)), true);

	time_t start, end;
	time (&start);

	Simulator::Run();
	time (&end);

	uint32_t i;
	for (i = 1; i <= channel->GetNTxInterfaces(); i++)
	{
		uint32_t j;
		for (j = 1; j <= channel->GetNRxInterfaces(); j++)
		{
			Ptr<PLC_TransferBase> ctv = channel->GetChannelTransferData(i,j);
			if (ctv)
			{
				Ptr<PLC_TxInterface> txIf = channel->GetTxInterface(i);
				Ptr<PLC_RxInterface> rxIf = channel->GetRxInterface(j);
				PLC_TimeVariantTransferVector *tv_ctv = NULL;
				PLC_TransferVector *tiv_ctv = NULL;

				if (ctv->IsTimeVariant())
				{
					NS_LOG_UNCOND ("Channel transfer data between " << txIf->GetNode()->GetName() << " and " << rxIf->GetNode()->GetName() << " is time-variant" <<
							(*ctv));
					tv_ctv = static_cast<PLC_TimeVariantTransferVector *>  (PeekPointer (ctv));
				}
				else
				{
					NS_LOG_UNCOND ("Channel transfer data between " << txIf->GetNode()->GetName() << " and " << rxIf->GetNode()->GetName() << " is time-invariant " <<
							(*ctv));
					tiv_ctv = static_cast<PLC_TransferVector *>  (PeekPointer (ctv));
				}
				std::vector<Ptr<SpectrumValue> > my_abs_sqr_ctf;

				for  (uint32_t k = 0; k < PLC_Time::GetNumTimeslots(); k++)
				{
					Ptr<SpectrumValue> abs_sqr_ctf = Create<SpectrumValue> (ctv->GetSpectrumModel());

					PLC_ValueSpectrum vs;

					if (ctv->IsTimeVariant())
						vs = (*tv_ctv)[k];

					Values::iterator it;
					uint32_t l;
					for  (it = abs_sqr_ctf->ValuesBegin (), l = 0; it != abs_sqr_ctf->ValuesEnd (); it++, l++)
					{
						PLC_Value value;
						if (ctv->IsTimeVariant())
							value = vs[l];
						else
							value = (*tiv_ctv)[l];
						*it = pow (real (value), 2) + pow (imag (value), 2);
					}

					my_abs_sqr_ctf.push_back (abs_sqr_ctf);
				}

				NS_LOG_UNCOND ("abs sqr channel transfer (dB): " << 10*Log10(*my_abs_sqr_ctf[0]));
			}
		}
	}

	Simulator::Destroy();

	double dif = difftime (end, start);
	NS_LOG_UNCOND ("Simulation Execution Time: " << dif << "s");

	return EXIT_SUCCESS;
}
