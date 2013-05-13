# plc

An ns-3 module for simulations of power line communication networks

##Overview

The provided module enables simulations of power line communication networks with the network simulation
environment ns-3. It is intended for protocol development and application testing under realistic link
performance emulation between plc devices of a deterministic grid topology. The latter has to be specified by
the user in terms of its geometrical layout, the used cable types, the positions and values of network impedances
and the location of plc devices within the network. The module also supports the definition of two-port
network elements to reflect transfer characteristics of special components, e.g. transformer units.
Transfer functions of the channel realizations are computed efficiently according to the "bottom-up" approach by use of
two-conductor transmission line theory. The simulation module especially takes into account time-dependent channel 
conditions that change due to mains-synchronous or sporadic impedance variations. Communication as well as interfering signals 
are represented by approximated power spectral densities (PSD). At the receivers the signal to interference and noise 
ratio (SINR) is obtained, which allows statements to be made on the expectable link performance for an applied OFDM
modulation and coding scheme. Hence, the module is suitable for plc network simulations involving different types of
noise sources and temporal channel variations close to reality. The simulation module is also aimed on evaluating protocol 
functioning for novel communication strategies, such as Hybrid ARQ and Cooperative Relaying schemes, that will play an 
important role in future plc systems.

Further information can be found in the user guide and the API documentation.

##Prerequisites

A stable ns-3 release is needed to use the plc module. It is available on www.nsnam.org.
Besides the plc module uses the template-based boost graph library, which has to be accessible
via the system's include path. For installation see www.boost.org.

On an UNIX-like operating system the simulation environment can be set up as follows:

1.  Create target directory

    > mkdir ns-3 && cd ns-3

2.  Download a stable ns-3 release, e.g.

    > wget https://www.nsnam.org/release/ns-allinone-3.16.tar.bz2

3.  Extract ns-3 sources

    > tar xvjf ns-allinone-3.16.tar.bz2 

4.  Change to ns-3 modules' source directory

    > cd ns-allinone-3.16/ns-3.16/src

5.  Clone or copy the plc module into the source directory, e.g.

    > git clone https://github.com/ns3-plc-module/plc.git


##Build

NS-3 makes use of the waf build automation tool. NS-3 and the plc module can be built as follows:

1.  Change to the ns-3 root directory
    
    > cd ns-allinone-3.16/ns-3.16

2.  Run build configuration with enabled examples and tests

    > ./waf --enable-examples --enable-tests configure
    
3.  Build ns-3 modules

    > ./waf

##Running

The current release of the plc module provides a few simple examples for its usage. The sources
are located in the directory src/plc/examples. To run e.g. the plc net device example (plc-netdevice.cc)
go to the ns-3 root directory and type

> ./waf --run src/plc/examples/plc-netdevice


