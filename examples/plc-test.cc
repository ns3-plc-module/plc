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
	Ptr<PLC_Cable> mainCable = CreateObject<PLC_NAYY150SE_Cable> (sm);
	Ptr<PLC_Cable> houseCable = CreateObject<PLC_NAYY50SE_Cable> (sm);

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
	n2->SetPosition(10,0,0);
	n3->SetPosition(20,00,0);
	n4->SetPosition(30,0,0);
	n5->SetPosition(0,10,0);
	n6->SetPosition(10,10,0);
	n7->SetPosition(20,10,0);
	n8->SetPosition(30,10,0);

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

	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n1, sm));
	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n1, sm));
	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n6, sm));
	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n6, sm));
	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n7, sm));
	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n7, sm));
	channel->AddTxInterface(CreateObject<PLC_TxInterface> (n8, sm));
	channel->AddRxInterface(CreateObject<PLC_RxInterface> (n8, sm));

	channel->InitTransmissionChannels();
	channel->CalcTransmissionChannels();

	Simulator::Schedule(Seconds(0.5), &PLC_Outlet::SetImpedance, outlet7, Create<PLC_TimeVariantFreqSelectiveImpedance> (PLC_ConstImpedance(sm, PLC_Value(5,0))), true);
//	Simulator::Schedule(Seconds(1), &PLC_Outlet::SetImpedance, outlet3, Create<PLC_ConstImpedance> (sm, PLC_Value(5,0)), true);
//	Simulator::Schedule(Seconds(2), &PLC_Outlet::SetImpedance, outlet6, Create<PLC_ConstImpedance> (sm, PLC_Value(5,0)), true);

	time_t start, end;
	time (&start);

	Simulator::Run();
	time (&end);

	uint32_t i;
	for (i = 0; i < channel->GetNTxInterfaces(); i++)
	{
		uint32_t j;
		for (j = 0; j < channel->GetNRxInterfaces(); j++)
		{
			Ptr<PLC_TransferBase> ctv = channel->GetChannelTransferData(i,j);
			if (ctv)
			{
				Ptr<PLC_TxInterface> txIf = channel->GetTxInterface(i);
				Ptr<PLC_RxInterface> rxIf = channel->GetRxInterface(j);

				if (ctv->IsTimeVariant())
				{
					NS_LOG_UNCOND ("Channel transfer data between " << txIf->GetNode()->GetName() << " and " << rxIf->GetNode()->GetName() << " is time-variant");
				}
				else
				{
					NS_LOG_UNCOND ("Channel transfer data between " << txIf->GetNode()->GetName() << " and " << rxIf->GetNode()->GetName() << " is time-invariant");
				}
			}
		}
	}

	Simulator::Destroy();

	double dif = difftime (end, start);
	NS_LOG_UNCOND ("Simulation Execution Time: " << dif << "s");

	return EXIT_SUCCESS;
}
