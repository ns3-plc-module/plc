## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    # Create the module with the appropriate name and the list of
    # modules it depends on.
    module = bld.create_ns3_module('plc', ['core', 'network', 'spectrum', 'csma', 'applications', 'config-store'])
    # Set the C++ source files for this module.
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

	'helper/plc-spectrum-helper.cc',
	'helper/plc-helper.cc',
	'helper/plc-device-helper.cc',
    ]

    module.env.append_value('CXXFLAGS', ['-fopenmp', '-D_REENTRANT', '-Wno-deprecated', '-Wno-unused-function', '-DQT_NO_DEBUG', '-DQT_GUI_LIB', '-DQT_SHARED', '-DQT_CORE_LIB', '-DQT_SHARED'])
    module.env.append_value('LINKFLAGS', ['-fopenmp'])
    module.env.append_value('INCLUDES', ['/usr/share/qt4/mkspecs/linux-g++', '/usr/include/qt4', '/usr/include/qt4/QtCore', '/usr/include/qt4/QtGui', '/usr/local/qwt-6.0.2-svn/include'])
    module.env.append_value('LIBPATH', ['/usr/lib', '/usr/local/qwt-6.0.2-svn/lib'])    
    module.env.append_value('LIB', ['QtGui', 'QtCore', 'qwt']) 
    module.env.append_value('OMP_THREAD_LIMIT', ['15'])
    # Create the module's test library.
    module_test = bld.create_ns3_module_test_library('plc')

    # Set the C++ source files for the module's test library.
    module_test.source = [
        # Uncomment these lines to compile these test suites.
        #'test/sample-test-suite-1.cc',
        #'test/sample-test-suite-2.cc',
        ]

    # Make headers be installed for this module.
    headers = bld.new_task_gen(features=['ns3header'])
    headers.module = 'plc'

    # Set the C++ header files for this module.
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

    # Uncomment these lines if this module needs a library such as the
    # real-time (RT) library to be linked in at build time.
    module.uselib = 'BOOST'

    # Look for examples if they are enabled. 
    if (bld.env['ENABLE_EXAMPLES']):
        bld.add_subdirs('examples')
