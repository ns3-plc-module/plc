# -*- Mode:Python; -*-
# /*
#  * Copyright (c) 2010 INRIA
#  *
#  * This program is free software; you can redistribute it and/or modify
#  * it under the terms of the GNU General Public License version 2 as
#  * published by the Free Software Foundation;
#  *
#  * This program is distributed in the hope that it will be useful,
#  * but WITHOUT ANY WARRANTY; without even the implied warranty of
#  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  * GNU General Public License for more details.
#  *
#  * You should have received a copy of the GNU General Public License
#  * along with this program; if not, write to the Free Software
#  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#  *
#  * Authors: Alexander Schloegl <alexander.schloegl@gmx.de>
#  */

# Python version of plc-netdevice-example.cc

import ns.plc
import ns.core
import ns.spectrum
import ns.network

def send(dev, p, dst, proto):
    dev.Send(p,dst,proto)

def receivedACK():
    print 'ACK received'

def main(dummy_argv):

    ## Enable logging  
    ns.core.LogComponentEnableAll(ns.core.LOG_PREFIX_TIME)
    ns.core.LogComponentEnable('PLC_Mac', ns.core.LOG_LEVEL_INFO)

    ## Enable packet printing
    ns.network.Packet.EnablePrinting()

    ## Define spectrum model
    sm = ns.plc.PLC_SpectrumModelHelper().GetSpectrumModel(0,10e6,100)

    ## Define transmit power spectral density
    txPsd = ns.spectrum.SpectrumValue(sm)
    txPsd += 1e-8

    ## Create cable type
    cable = ns.plc.PLC_NAYY50SE_Cable(sm)

    ## Create nodes
    n1 = ns.plc.PLC_Node()
    n2 = ns.plc.PLC_Node()
    n1.SetPosition(0,0,0)
    n2.SetPosition(1000,0,0)
    n1.SetName('Node1')
    n2.SetName('Node2')
    nodes = [n1,n2]

    ## Link nodes
    ns.plc.PLC_Line(cable,n1,n2)

    ## Setup channel
    channelHelper = ns.plc.PLC_ChannelHelper()
    channelHelper.Install(nodes)
    channel = channelHelper.GetChannel()

    ## Create outlets
    o1 = ns.plc.PLC_Outlet(n1)
    o2 = ns.plc.PLC_Outlet(n2)

    ## Create PHYs
    phy1 = ns.plc.PLC_InformationRatePhy()
    phy2 = ns.plc.PLC_InformationRatePhy()

    ## Create net devices
    deviceHelper = ns.plc.PLC_NetDeviceHelper(sm, txPsd, nodes)
    deviceHelper.Setup()
                   
    ## Calculate channels
    channel.InitTransmissionChannels()
    channel.CalcTransmissionChannels()

    ## Create packet to send
    p = ns.network.Packet(1024)

    ## Get tx device
    txDev = deviceHelper.GetDevice('Node1')

    ## Get address of rx device
    rxAddr = deviceHelper.GetDevice('Node2').GetAddress() 

    ## Schedule transmission of packet p
    ns.core.Simulator.Schedule(ns.core.Seconds(1), send, txDev, p, rxAddr, 0)

    ## Start simulation
    ns.core.Simulator.Run()

    ## Cleanup simulation
    ns.core.Simulator.Destroy()

if __name__ == '__main__':
    import sys
    main(sys.argv)
