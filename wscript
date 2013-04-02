# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('plc', ['core', 'spectrum', 'network'])
    module.source = [
    'model/plc-simulator-impl.cc',
	'model/plc-defs.cc',
	'model/plc-time.cc',
	'model/plc-value.cc',
	'model/plc-cable.cc',
	'model/plc-edge.cc',
	'model/plc-node.cc',
	'model/plc-graph.cc',
	'model/plc-channel.cc',
	'model/plc-backbone.cc',
	'model/plc-outlet.cc',
	'model/plc-interface.cc',
	'model/plc-noise.cc',
	'model/plc-dcmc-capacity.cc',
	'model/plc-link-performance-model.cc',
	'model/plc-interference.cc',
	'model/plc-header.cc',
	'model/plc-phy.cc',
	'model/plc-mac.cc',
	'model/plc-net-device.cc',
	'helper/plc-helper.cc',
    'helper/plc-spectrum-helper.cc',
	'helper/plc-device-helper.cc',
        ]

    module_test = bld.create_ns3_module_test_library('plc')
    module_test.source = [
        'test/plc-test-suite.cc',
        ]

    headers = bld.new_task_gen(features=['ns3header'])
    headers.module = 'plc'
    headers.source = [
    'model/plc-simulator-impl.h',
	'model/plc.h',
	'model/plc-defs.h',
	'model/plc-time.h',
	'model/plc-value.h',
	'model/plc-cable.h',
	'model/plc-edge.h',
	'model/plc-node.h',
	'model/plc-graph.h',
	'model/plc-visitor.h',
	'model/plc-channel.h',
	'model/plc-backbone.h',
	'model/plc-outlet.h',
	'model/plc-interface.h',
	'model/plc-undirected-dfs.h',
	'model/plc-noise.h',
	'model/plc-dcmc-capacity.h',
	'model/plc-link-performance-model.h',
	'model/plc-interference.h',
	'model/plc-header.h',
	'model/plc-phy.h',
	'model/plc-mac.h',
	'model/plc-net-device.h',
	'helper/plc-spectrum-helper.h',
	'helper/plc-helper.h',
	'helper/plc-device-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.add_subdirs('examples')

    bld.ns3_python_bindings()

