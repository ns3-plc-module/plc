from pybindgen import Module, FileCodeSink, param, retval, cppclass, typehandlers


import pybindgen.settings
import warnings

class ErrorHandler(pybindgen.settings.ErrorHandler):
    def handle_error(self, wrapper, exception, traceback_):
        warnings.warn("exception %r in wrapper %s" % (exception, wrapper))
        return True
pybindgen.settings.error_handler = ErrorHandler()


import sys

def module_init():
    root_module = Module('ns.plc', cpp_namespace='::ns3')
    return root_module

def register_types(module):
    root_module = module.get_root()
    
    ## plc-mac.h (module 'plc'): ns3::PLC_CsmaCaState [enumeration]
    module.add_enum('PLC_CsmaCaState', ['CHANNEL_IDLE', 'CHANNEL_ACCESS_FAILURE'])
    ## plc-phy.h (module 'plc'): ns3::PLC_PhyCcaResult [enumeration]
    module.add_enum('PLC_PhyCcaResult', ['CHANNEL_CLEAR', 'CHANNEL_OCCUPIED'])
    ## log.h (module 'core'): ns3::LogLevel [enumeration]
    module.add_enum('LogLevel', ['LOG_NONE', 'LOG_ERROR', 'LOG_LEVEL_ERROR', 'LOG_WARN', 'LOG_LEVEL_WARN', 'LOG_DEBUG', 'LOG_LEVEL_DEBUG', 'LOG_INFO', 'LOG_LEVEL_INFO', 'LOG_FUNCTION', 'LOG_LEVEL_FUNCTION', 'LOG_LOGIC', 'LOG_LEVEL_LOGIC', 'LOG_ALL', 'LOG_LEVEL_ALL', 'LOG_PREFIX_FUNC', 'LOG_PREFIX_TIME', 'LOG_PREFIX_NODE', 'LOG_PREFIX_LEVEL', 'LOG_PREFIX_ALL'], import_from_module='ns.core')
    ## plc-dcmc-capacity.h (module 'plc'): ns3::Modulation [enumeration]
    module.add_enum('Modulation', ['QAM', 'PSK'])
    ## plc-defs.h (module 'plc'): ns3::ModulationAndCodingType [enumeration]
    module.add_enum('ModulationAndCodingType', ['BPSK_1_4', 'BPSK_1_2', 'QPSK_1_2', 'QAM16_1_2', 'QAM64_16_21', 'BPSK_RATELESS', 'QAM4_RATELESS', 'QAM16_RATELESS', 'QAM32_RATELESS', 'QAM64_RATELESS'])
    ## address.h (module 'network'): ns3::Address [class]
    module.add_class('Address', import_from_module='ns.network')
    ## address.h (module 'network'): ns3::Address::MaxSize_e [enumeration]
    module.add_enum('MaxSize_e', ['MAX_SIZE'], outer_class=root_module['ns3::Address'], import_from_module='ns.network')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList [class]
    module.add_class('AttributeConstructionList', import_from_module='ns.core')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item [struct]
    module.add_class('Item', import_from_module='ns.core', outer_class=root_module['ns3::AttributeConstructionList'])
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo [struct]
    module.add_class('BandInfo', import_from_module='ns.spectrum')
    ## buffer.h (module 'network'): ns3::Buffer [class]
    module.add_class('Buffer', import_from_module='ns.network')
    ## buffer.h (module 'network'): ns3::Buffer::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::Buffer'])
    ## packet.h (module 'network'): ns3::ByteTagIterator [class]
    module.add_class('ByteTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagIterator'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList [class]
    module.add_class('ByteTagList', import_from_module='ns.network')
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList::Iterator'])
    ## callback.h (module 'core'): ns3::CallbackBase [class]
    module.add_class('CallbackBase', import_from_module='ns.core')
    ## data-rate.h (module 'network'): ns3::DataRate [class]
    module.add_class('DataRate', import_from_module='ns.network')
    ## event-id.h (module 'core'): ns3::EventId [class]
    module.add_class('EventId', import_from_module='ns.core')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    module.add_class('Ipv4Address', import_from_module='ns.network')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    root_module['ns3::Ipv4Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask [class]
    module.add_class('Ipv4Mask', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    module.add_class('Ipv6Address', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    root_module['ns3::Ipv6Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix [class]
    module.add_class('Ipv6Prefix', import_from_module='ns.network')
    ## log.h (module 'core'): ns3::LogComponent [class]
    module.add_class('LogComponent', import_from_module='ns.core')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    module.add_class('Mac48Address', import_from_module='ns.network')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    root_module['ns3::Mac48Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## object-base.h (module 'core'): ns3::ObjectBase [class]
    module.add_class('ObjectBase', allow_subclassing=True, import_from_module='ns.core')
    ## object.h (module 'core'): ns3::ObjectDeleter [struct]
    module.add_class('ObjectDeleter', import_from_module='ns.core')
    ## object-factory.h (module 'core'): ns3::ObjectFactory [class]
    module.add_class('ObjectFactory', import_from_module='ns.core')
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t [struct]
    module.add_class('PLC_EdgeTransferData_t')
    ## plc-defs.h (module 'plc'): ns3::PLC_ImpedanceIndicator_t [struct]
    module.add_class('PLC_ImpedanceIndicator_t')
    ## plc-defs.h (module 'plc'): ns3::PLC_Mutex [struct]
    module.add_class('PLC_Mutex')
    ## plc-time.h (module 'plc'): ns3::PLC_Time [class]
    module.add_class('PLC_Time')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata [class]
    module.add_class('PacketMetadata', import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [enumeration]
    module.add_enum('', ['PAYLOAD', 'HEADER', 'TRAILER'], outer_class=root_module['ns3::PacketMetadata::Item'], import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator [class]
    module.add_class('ItemIterator', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet.h (module 'network'): ns3::PacketTagIterator [class]
    module.add_class('PacketTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagIterator'])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList [class]
    module.add_class('PacketTagList', import_from_module='ns.network')
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData [struct]
    module.add_class('TagData', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagList'])
    ## random-variable.h (module 'core'): ns3::RandomVariable [class]
    module.add_class('RandomVariable', import_from_module='ns.core')
    ## rng-seed-manager.h (module 'core'): ns3::RngSeedManager [class]
    module.add_class('RngSeedManager', import_from_module='ns.core')
    ## random-variable.h (module 'core'): ns3::SequentialVariable [class]
    module.add_class('SequentialVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Object', 'ns3::ObjectBase', 'ns3::ObjectDeleter'], parent=root_module['ns3::ObjectBase'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## tag.h (module 'network'): ns3::Tag [class]
    module.add_class('Tag', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer [class]
    module.add_class('TagBuffer', import_from_module='ns.network')
    ## random-variable.h (module 'core'): ns3::TriangularVariable [class]
    module.add_class('TriangularVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## type-id.h (module 'core'): ns3::TypeId [class]
    module.add_class('TypeId', import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeFlag [enumeration]
    module.add_enum('AttributeFlag', ['ATTR_GET', 'ATTR_SET', 'ATTR_CONSTRUCT', 'ATTR_SGC'], outer_class=root_module['ns3::TypeId'], import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation [struct]
    module.add_class('AttributeInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation [struct]
    module.add_class('TraceSourceInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## random-variable.h (module 'core'): ns3::UniformVariable [class]
    module.add_class('UniformVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## vector.h (module 'core'): ns3::Vector2D [class]
    module.add_class('Vector2D', import_from_module='ns.core')
    ## vector.h (module 'core'): ns3::Vector3D [class]
    module.add_class('Vector3D', import_from_module='ns.core')
    ## random-variable.h (module 'core'): ns3::WeibullVariable [class]
    module.add_class('WeibullVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ZetaVariable [class]
    module.add_class('ZetaVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ZipfVariable [class]
    module.add_class('ZipfVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## plc-defs.h (module 'plc'): ns3::backbone_branch_discover_thread_arg_t [struct]
    module.add_class('backbone_branch_discover_thread_arg_t')
    ## plc-defs.h (module 'plc'): ns3::boostgraph_copy_t [struct]
    module.add_class('boostgraph_copy_t')
    ## empty.h (module 'core'): ns3::empty [class]
    module.add_class('empty', import_from_module='ns.core')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t [class]
    module.add_class('int64x64_t', import_from_module='ns.core')
    ## plc-defs.h (module 'plc'): ns3::sub_thread_arg_t [struct]
    module.add_class('sub_thread_arg_t')
    ## plc-defs.h (module 'plc'): ns3::thread_arg_t [struct]
    module.add_class('thread_arg_t')
    ## chunk.h (module 'network'): ns3::Chunk [class]
    module.add_class('Chunk', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## random-variable.h (module 'core'): ns3::ConstantVariable [class]
    module.add_class('ConstantVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::DeterministicVariable [class]
    module.add_class('DeterministicVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::EmpiricalVariable [class]
    module.add_class('EmpiricalVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ErlangVariable [class]
    module.add_class('ErlangVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable [class]
    module.add_class('ExponentialVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::GammaVariable [class]
    module.add_class('GammaVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## header.h (module 'network'): ns3::Header [class]
    module.add_class('Header', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## random-variable.h (module 'core'): ns3::IntEmpiricalVariable [class]
    module.add_class('IntEmpiricalVariable', import_from_module='ns.core', parent=root_module['ns3::EmpiricalVariable'])
    ## random-variable.h (module 'core'): ns3::LogNormalVariable [class]
    module.add_class('LogNormalVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::NormalVariable [class]
    module.add_class('NormalVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## object.h (module 'core'): ns3::Object [class]
    module.add_class('Object', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    ## object.h (module 'core'): ns3::Object::AggregateIterator [class]
    module.add_class('AggregateIterator', import_from_module='ns.core', outer_class=root_module['ns3::Object'])
    ## plc-backbone.h (module 'plc'): ns3::PLC_BackboneBranch [class]
    module.add_class('PLC_BackboneBranch', parent=root_module['ns3::Object'])
    ## plc-cable.h (module 'plc'): ns3::PLC_Cable [class]
    module.add_class('PLC_Cable', parent=root_module['ns3::Object'])
    ## plc-helper.h (module 'plc'): ns3::PLC_ChannelHelper [class]
    module.add_class('PLC_ChannelHelper', parent=root_module['ns3::Object'])
    ## plc-channel.h (module 'plc'): ns3::PLC_ChannelTransferImpl [class]
    module.add_class('PLC_ChannelTransferImpl', parent=root_module['ns3::Object'])
    ## plc-edge.h (module 'plc'): ns3::PLC_Edge [class]
    module.add_class('PLC_Edge', parent=root_module['ns3::Object'])
    ## plc-channel.h (module 'plc'): ns3::PLC_EdgeTransferUnit [class]
    module.add_class('PLC_EdgeTransferUnit', parent=root_module['ns3::Object'])
    ## plc-cable.h (module 'plc'): ns3::PLC_FourSectorPowerSupplyCable [class]
    module.add_class('PLC_FourSectorPowerSupplyCable', parent=root_module['ns3::PLC_Cable'])
    ## plc-graph.h (module 'plc'): ns3::PLC_Graph [class]
    module.add_class('PLC_Graph', parent=root_module['ns3::Object'])
    ## plc-helper.h (module 'plc'): ns3::PLC_ImpedanceHelper [class]
    module.add_class('PLC_ImpedanceHelper', parent=root_module['ns3::Object'])
    ## plc-interface.h (module 'plc'): ns3::PLC_Interface [class]
    module.add_class('PLC_Interface', parent=root_module['ns3::Object'])
    ## plc-interference.h (module 'plc'): ns3::PLC_Interference [class]
    module.add_class('PLC_Interference', parent=root_module['ns3::Object'])
    ## plc-edge.h (module 'plc'): ns3::PLC_Line [class]
    module.add_class('PLC_Line', parent=root_module['ns3::PLC_Edge'])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_LinkPerformanceModel [class]
    module.add_class('PLC_LinkPerformanceModel', parent=root_module['ns3::Object'])
    ## plc-mac.h (module 'plc'): ns3::PLC_Mac [class]
    module.add_class('PLC_Mac', parent=root_module['ns3::Object'])
    ## plc-header.h (module 'plc'): ns3::PLC_MacHeader [class]
    module.add_class('PLC_MacHeader', parent=root_module['ns3::Header'])
    ## plc-header.h (module 'plc'): ns3::PLC_MacHeader::MacHdrType [enumeration]
    module.add_enum('MacHdrType', ['DATA', 'ACK', 'NACK'], outer_class=root_module['ns3::PLC_MacHeader'])
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY150SE_Cable [class]
    module.add_class('PLC_NAYY150SE_Cable', parent=root_module['ns3::PLC_FourSectorPowerSupplyCable'])
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY50SE_Cable [class]
    module.add_class('PLC_NAYY50SE_Cable', parent=root_module['ns3::PLC_FourSectorPowerSupplyCable'])
    ## plc-device-helper.h (module 'plc'): ns3::PLC_NetDeviceHelper [class]
    module.add_class('PLC_NetDeviceHelper', parent=root_module['ns3::Object'])
    ## plc-node.h (module 'plc'): ns3::PLC_Node [class]
    module.add_class('PLC_Node', parent=root_module['ns3::Object'])
    ## plc-noise.h (module 'plc'): ns3::PLC_NoiseSource [class]
    module.add_class('PLC_NoiseSource', parent=root_module['ns3::Object'])
    ## plc-noise.h (module 'plc'): ns3::PLC_NoiseSource::NoiseSourceType [enumeration]
    module.add_enum('NoiseSourceType', ['STATIC', 'TIMEVARIANT', 'IMPULSIVE'], outer_class=root_module['ns3::PLC_NoiseSource'])
    ## plc-outlet.h (module 'plc'): ns3::PLC_Outlet [class]
    module.add_class('PLC_Outlet', parent=root_module['ns3::Object'])
    ## plc-phy.h (module 'plc'): ns3::PLC_Phy [class]
    module.add_class('PLC_Phy', parent=root_module['ns3::Object'])
    ## plc-header.h (module 'plc'): ns3::PLC_PhyFrameControlHeader [class]
    module.add_class('PLC_PhyFrameControlHeader', parent=root_module['ns3::Header'])
    ## plc-header.h (module 'plc'): ns3::PLC_PhyFrameControlHeader::DelimiterType [enumeration]
    module.add_enum('DelimiterType', ['DATA', 'ACK', 'NACK'], outer_class=root_module['ns3::PLC_PhyFrameControlHeader'])
    ## plc-header.h (module 'plc'): ns3::PLC_PhyRatelessFrameControlHeader [class]
    module.add_class('PLC_PhyRatelessFrameControlHeader', parent=root_module['ns3::Header'])
    ## plc-header.h (module 'plc'): ns3::PLC_PhyRatelessFrameControlHeader::DelimiterType [enumeration]
    module.add_enum('DelimiterType', ['DATA', 'ACK', 'NACK'], outer_class=root_module['ns3::PLC_PhyRatelessFrameControlHeader'])
    ## plc-header.h (module 'plc'): ns3::PLC_Preamble [class]
    module.add_class('PLC_Preamble', parent=root_module['ns3::Header'])
    ## plc-interface.h (module 'plc'): ns3::PLC_RxInterface [class]
    module.add_class('PLC_RxInterface', parent=root_module['ns3::PLC_Interface'])
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_SpectrumModelHelper [class]
    module.add_class('PLC_SpectrumModelHelper', parent=root_module['ns3::Object'])
    ## plc-noise.h (module 'plc'): ns3::PLC_StaticNoiseSource [class]
    module.add_class('PLC_StaticNoiseSource', parent=root_module['ns3::PLC_NoiseSource'])
    ## plc-cable.h (module 'plc'): ns3::PLC_ThreeCoreConcentricCable [class]
    module.add_class('PLC_ThreeCoreConcentricCable', parent=root_module['ns3::PLC_Cable'])
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_TimeInvariantSpectrumHelper [class]
    module.add_class('PLC_TimeInvariantSpectrumHelper', parent=root_module['ns3::Object'])
    ## plc-channel.h (module 'plc'): ns3::PLC_TrxMetaInfo [class]
    module.add_class('PLC_TrxMetaInfo', parent=root_module['ns3::Object'])
    ## plc-edge.h (module 'plc'): ns3::PLC_TwoPort [class]
    module.add_class('PLC_TwoPort', parent=root_module['ns3::PLC_Edge'])
    ## plc-interface.h (module 'plc'): ns3::PLC_TxInterface [class]
    module.add_class('PLC_TxInterface', parent=root_module['ns3::PLC_Interface'])
    ## plc-value.h (module 'plc'): ns3::PLC_ValueBase [class]
    module.add_class('PLC_ValueBase', parent=root_module['ns3::Object'])
    ## plc-value.h (module 'plc'): ns3::PLC_ValueBase::PLC_ValueType [enumeration]
    module.add_enum('PLC_ValueType', ['CONSTANT', 'FREQ_SELECTIVE', 'TIMEVARIANT_CONSTANT', 'TIMEVARIANT_FREQ_SELECTIVE'], outer_class=root_module['ns3::PLC_ValueBase'])
    ## packet-burst.h (module 'network'): ns3::PacketBurst [class]
    module.add_class('PacketBurst', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## random-variable.h (module 'core'): ns3::ParetoVariable [class]
    module.add_class('ParetoVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## scheduler.h (module 'core'): ns3::Scheduler [class]
    module.add_class('Scheduler', import_from_module='ns.core', parent=root_module['ns3::Object'])
    ## scheduler.h (module 'core'): ns3::Scheduler::Event [struct]
    module.add_class('Event', import_from_module='ns.core', outer_class=root_module['ns3::Scheduler'])
    ## scheduler.h (module 'core'): ns3::Scheduler::EventKey [struct]
    module.add_class('EventKey', import_from_module='ns.core', outer_class=root_module['ns3::Scheduler'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeAccessor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeChecker', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeChecker>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeValue', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeValue>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::CallbackImplBase', 'ns3::empty', 'ns3::DefaultDeleter<ns3::CallbackImplBase>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::EventImpl', 'ns3::empty', 'ns3::DefaultDeleter<ns3::EventImpl>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::NixVector', 'ns3::empty', 'ns3::DefaultDeleter<ns3::NixVector>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, template_parameters=['ns3::PLC_ColoredNoiseFloor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Packet', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Packet>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::SpectrumModel', 'ns3::empty', 'ns3::DefaultDeleter<ns3::SpectrumModel>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::SpectrumValue', 'ns3::empty', 'ns3::DefaultDeleter<ns3::SpectrumValue>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::SystemThread', 'ns3::empty', 'ns3::DefaultDeleter<ns3::SystemThread>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::TraceSourceAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::TraceSourceAccessor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simulator-impl.h (module 'core'): ns3::SimulatorImpl [class]
    module.add_class('SimulatorImpl', import_from_module='ns.core', parent=root_module['ns3::Object'])
    ## spectrum-model.h (module 'spectrum'): ns3::SpectrumModel [class]
    module.add_class('SpectrumModel', import_from_module='ns.spectrum', parent=root_module['ns3::SimpleRefCount< ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> >'])
    ## spectrum-value.h (module 'spectrum'): ns3::SpectrumValue [class]
    module.add_class('SpectrumValue', import_from_module='ns.spectrum', parent=root_module['ns3::SimpleRefCount< ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> >'])
    ## system-thread.h (module 'core'): ns3::SystemThread [class]
    module.add_class('SystemThread', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> >'])
    ## nstime.h (module 'core'): ns3::Time [class]
    module.add_class('Time', import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time::Unit [enumeration]
    module.add_enum('Unit', ['S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST'], outer_class=root_module['ns3::Time'], import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time [class]
    root_module['ns3::Time'].implicitly_converts_to(root_module['ns3::int64x64_t'])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor [class]
    module.add_class('TraceSourceAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    ## trailer.h (module 'network'): ns3::Trailer [class]
    module.add_class('Trailer', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## attribute.h (module 'core'): ns3::AttributeAccessor [class]
    module.add_class('AttributeAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    ## attribute.h (module 'core'): ns3::AttributeChecker [class]
    module.add_class('AttributeChecker', allow_subclassing=False, automatic_type_narrowing=True, import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    ## attribute.h (module 'core'): ns3::AttributeValue [class]
    module.add_class('AttributeValue', allow_subclassing=False, automatic_type_narrowing=True, import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    ## boolean.h (module 'core'): ns3::BooleanChecker [class]
    module.add_class('BooleanChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## boolean.h (module 'core'): ns3::BooleanValue [class]
    module.add_class('BooleanValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## callback.h (module 'core'): ns3::CallbackChecker [class]
    module.add_class('CallbackChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## callback.h (module 'core'): ns3::CallbackImplBase [class]
    module.add_class('CallbackImplBase', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >'])
    ## callback.h (module 'core'): ns3::CallbackValue [class]
    module.add_class('CallbackValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## channel.h (module 'network'): ns3::Channel [class]
    module.add_class('Channel', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## data-rate.h (module 'network'): ns3::DataRateChecker [class]
    module.add_class('DataRateChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## data-rate.h (module 'network'): ns3::DataRateValue [class]
    module.add_class('DataRateValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## double.h (module 'core'): ns3::DoubleValue [class]
    module.add_class('DoubleValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue [class]
    module.add_class('EmptyAttributeValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## enum.h (module 'core'): ns3::EnumChecker [class]
    module.add_class('EnumChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## enum.h (module 'core'): ns3::EnumValue [class]
    module.add_class('EnumValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## event-impl.h (module 'core'): ns3::EventImpl [class]
    module.add_class('EventImpl', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    ## integer.h (module 'core'): ns3::IntegerValue [class]
    module.add_class('IntegerValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker [class]
    module.add_class('Ipv4AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue [class]
    module.add_class('Ipv4AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker [class]
    module.add_class('Ipv4MaskChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue [class]
    module.add_class('Ipv4MaskValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker [class]
    module.add_class('Ipv6AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue [class]
    module.add_class('Ipv6AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker [class]
    module.add_class('Ipv6PrefixChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue [class]
    module.add_class('Ipv6PrefixValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker [class]
    module.add_class('Mac48AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue [class]
    module.add_class('Mac48AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## net-device.h (module 'network'): ns3::NetDevice [class]
    module.add_class('NetDevice', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## net-device.h (module 'network'): ns3::NetDevice::PacketType [enumeration]
    module.add_enum('PacketType', ['PACKET_HOST', 'NS3_PACKET_HOST', 'PACKET_BROADCAST', 'NS3_PACKET_BROADCAST', 'PACKET_MULTICAST', 'NS3_PACKET_MULTICAST', 'PACKET_OTHERHOST', 'NS3_PACKET_OTHERHOST'], outer_class=root_module['ns3::NetDevice'], import_from_module='ns.network')
    ## nix-vector.h (module 'network'): ns3::NixVector [class]
    module.add_class('NixVector', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >'])
    ## node.h (module 'network'): ns3::Node [class]
    module.add_class('Node', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker [class]
    module.add_class('ObjectFactoryChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue [class]
    module.add_class('ObjectFactoryValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## plc-cable.h (module 'plc'): ns3::PLC_AL3x95XLPE_Cable [class]
    module.add_class('PLC_AL3x95XLPE_Cable', parent=root_module['ns3::PLC_ThreeCoreConcentricCable'])
    ## plc-mac.h (module 'plc'): ns3::PLC_ArqMac [class]
    module.add_class('PLC_ArqMac', parent=root_module['ns3::PLC_Mac'])
    ## plc-channel.h (module 'plc'): ns3::PLC_Channel [class]
    module.add_class('PLC_Channel', parent=root_module['ns3::Channel'])
    ## plc-noise.h (module 'plc'): ns3::PLC_ColoredNoiseFloor [class]
    module.add_class('PLC_ColoredNoiseFloor', parent=root_module['ns3::SimpleRefCount< ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> >'])
    ## plc-value.h (module 'plc'): ns3::PLC_ConstValue [class]
    module.add_class('PLC_ConstValue', parent=root_module['ns3::PLC_ValueBase'])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_ErrorRateModel [class]
    module.add_class('PLC_ErrorRateModel', parent=root_module['ns3::PLC_LinkPerformanceModel'])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_ErrorRateModel::ChannelCondition [enumeration]
    module.add_enum('ChannelCondition', ['EXCELLENT', 'GOOD', 'MEDIUM', 'BAD'], outer_class=root_module['ns3::PLC_ErrorRateModel'])
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue [class]
    module.add_class('PLC_FreqSelectiveValue', parent=root_module['ns3::PLC_ValueBase'])
    ## plc-phy.h (module 'plc'): ns3::PLC_HalfDuplexOfdmPhy [class]
    module.add_class('PLC_HalfDuplexOfdmPhy', parent=root_module['ns3::PLC_Phy'])
    ## plc-phy.h (module 'plc'): ns3::PLC_HalfDuplexOfdmPhy::State [enumeration]
    module.add_enum('State', ['IDLE', 'TX', 'RX'], outer_class=root_module['ns3::PLC_HalfDuplexOfdmPhy'])
    ## plc-mac.h (module 'plc'): ns3::PLC_HarqMac [class]
    module.add_class('PLC_HarqMac', parent=root_module['ns3::PLC_Mac'])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulseNoiseSource [class]
    module.add_class('PLC_ImpulseNoiseSource', parent=root_module['ns3::PLC_NoiseSource'])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulsiveNoiseSource [class]
    module.add_class('PLC_ImpulsiveNoiseSource', parent=root_module['ns3::PLC_NoiseSource'])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel [class]
    module.add_class('PLC_InformationRateModel', parent=root_module['ns3::PLC_LinkPerformanceModel'])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::McsInfo [struct]
    module.add_class('McsInfo', outer_class=root_module['ns3::PLC_InformationRateModel'])
    ## plc-phy.h (module 'plc'): ns3::PLC_InformationRatePhy [class]
    module.add_class('PLC_InformationRatePhy', parent=root_module['ns3::PLC_HalfDuplexOfdmPhy'])
    ## plc-cable.h (module 'plc'): ns3::PLC_NYCY70SM35_Cable [class]
    module.add_class('PLC_NYCY70SM35_Cable', parent=root_module['ns3::PLC_ThreeCoreConcentricCable'])
    ## plc-net-device.h (module 'plc'): ns3::PLC_NetDevice [class]
    module.add_class('PLC_NetDevice', parent=root_module['ns3::NetDevice'])
    ## plc-simulator-impl.h (module 'plc'): ns3::PLC_SimulatorImpl [class]
    module.add_class('PLC_SimulatorImpl', parent=root_module['ns3::SimulatorImpl'])
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_SincSpectrumHelper [class]
    module.add_class('PLC_SincSpectrumHelper', parent=root_module['ns3::PLC_TimeInvariantSpectrumHelper'])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantConstValue [class]
    module.add_class('PLC_TimeVariantConstValue', parent=root_module['ns3::PLC_ValueBase'])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue [class]
    module.add_class('PLC_TimeVariantFreqSelectiveValue', parent=root_module['ns3::PLC_ValueBase'])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet [struct]
    module.add_class('PLC_TimeVariantParamSet', outer_class=root_module['ns3::PLC_TimeVariantFreqSelectiveValue'])
    ## packet.h (module 'network'): ns3::Packet [class]
    module.add_class('Packet', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >'])
    ## random-variable.h (module 'core'): ns3::RandomVariableChecker [class]
    module.add_class('RandomVariableChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## random-variable.h (module 'core'): ns3::RandomVariableValue [class]
    module.add_class('RandomVariableValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## nstime.h (module 'core'): ns3::TimeChecker [class]
    module.add_class('TimeChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## nstime.h (module 'core'): ns3::TimeValue [class]
    module.add_class('TimeValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## type-id.h (module 'core'): ns3::TypeIdChecker [class]
    module.add_class('TypeIdChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## type-id.h (module 'core'): ns3::TypeIdValue [class]
    module.add_class('TypeIdValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## uinteger.h (module 'core'): ns3::UintegerValue [class]
    module.add_class('UintegerValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## vector.h (module 'core'): ns3::Vector2DChecker [class]
    module.add_class('Vector2DChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## vector.h (module 'core'): ns3::Vector2DValue [class]
    module.add_class('Vector2DValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## vector.h (module 'core'): ns3::Vector3DChecker [class]
    module.add_class('Vector3DChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## vector.h (module 'core'): ns3::Vector3DValue [class]
    module.add_class('Vector3DValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## address.h (module 'network'): ns3::AddressChecker [class]
    module.add_class('AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## address.h (module 'network'): ns3::AddressValue [class]
    module.add_class('AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## bridge-channel.h (module 'bridge'): ns3::BridgeChannel [class]
    module.add_class('BridgeChannel', import_from_module='ns.bridge', parent=root_module['ns3::Channel'])
    ## bridge-net-device.h (module 'bridge'): ns3::BridgeNetDevice [class]
    module.add_class('BridgeNetDevice', import_from_module='ns.bridge', parent=root_module['ns3::NetDevice'])
    ## plc-phy.h (module 'plc'): ns3::PLC_ChaseCombiningPhy [class]
    module.add_class('PLC_ChaseCombiningPhy', parent=root_module['ns3::PLC_InformationRatePhy'])
    ## plc-phy.h (module 'plc'): ns3::PLC_ErrorRatePhy [class]
    module.add_class('PLC_ErrorRatePhy', parent=root_module['ns3::PLC_HalfDuplexOfdmPhy'])
    ## plc-phy.h (module 'plc'): ns3::PLC_IncrementalRedundancyPhy [class]
    module.add_class('PLC_IncrementalRedundancyPhy', parent=root_module['ns3::PLC_InformationRatePhy'])
    module.add_container('ns3::PLC_TimeVariantFreqSelectiveRealValue', 'std::vector< double >', container_type='vector')
    module.add_container('ns3::PLC_TimeVariantRealValue', 'double', container_type='vector')
    module.add_container('ns3::PLC_FreqSelectiveRealValue', 'double', container_type='vector')
    module.add_container('std::vector< double >', 'double', container_type='vector')
    module.add_container('ns3::PLC_NodeList', 'ns3::Ptr< ns3::PLC_Node >', container_type='vector')
    module.add_container('std::list< ns3::PLC_BackboneBranch * >', 'ns3::PLC_BackboneBranch *', container_type='list')
    module.add_container('std::vector< ns3::PLC_Node * >', 'ns3::PLC_Node *', container_type='vector')
    module.add_container('std::vector< ns3::Ptr< ns3::PLC_RxInterface > >', 'ns3::Ptr< ns3::PLC_RxInterface >', container_type='vector')
    module.add_container('std::vector< ns3::PLC_RxInterface * >', 'ns3::PLC_RxInterface *', container_type='vector')
    module.add_container('std::vector< ns3::Ptr< ns3::PLC_Node > >', 'ns3::Ptr< ns3::PLC_Node >', container_type='vector')
    module.add_container('std::list< ns3::Ptr< ns3::PLC_Node > >', 'ns3::Ptr< ns3::PLC_Node >', container_type='list')
    module.add_container('ns3::PLC_NetdeviceMap', ('std::string', 'ns3::Ptr< ns3::PLC_NetDevice >'), container_type='map')
    module.add_container('ns3::PLC_NodeOutEdgesMap', ('ns3::PLC_Node *', 'ns3::Ptr< ns3::PLC_Edge >'), container_type='map')
    module.add_container('std::list< ns3::Ptr< ns3::Packet > >', 'ns3::Ptr< ns3::Packet >', container_type='list')
    module.add_container('ns3::Bands', 'ns3::BandInfo', container_type='vector')
    module.add_container('std::vector< std::complex< double > >', 'std::complex< double >', container_type='vector')
    module.add_container('ns3::PLC_ValueSpectrum', 'std::complex< double >', container_type='vector')
    module.add_container('ns3::PLC_TimeVariantValue', 'std::complex< double >', container_type='vector')
    module.add_container('std::vector< std::vector< std::complex< double > > >', 'std::vector< std::complex< double > >', container_type='vector')
    module.add_container('ns3::PLC_TimeVariantValueSpectrum', 'std::vector< std::complex< double > >', container_type='vector')
    typehandlers.add_type_alias('std::map< unsigned int, std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > > > > >', 'ns3::PLC_TransmissionDescriptorMap')
    typehandlers.add_type_alias('std::map< unsigned int, std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > > > > >*', 'ns3::PLC_TransmissionDescriptorMap*')
    typehandlers.add_type_alias('std::map< unsigned int, std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > > > > >&', 'ns3::PLC_TransmissionDescriptorMap&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PLC_MacTransmissionFailedCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PLC_MacTransmissionFailedCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PLC_MacTransmissionFailedCallback&')
    typehandlers.add_type_alias('std::set< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * >, std::less< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * > >, std::allocator< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * > > >', 'ns3::PLC_InterfaceTupel')
    typehandlers.add_type_alias('std::set< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * >, std::less< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * > >, std::allocator< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * > > >*', 'ns3::PLC_InterfaceTupel*')
    typehandlers.add_type_alias('std::set< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * >, std::less< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * > >, std::allocator< std::pair< ns3::PLC_TxInterface *, ns3::PLC_RxInterface * > > >&', 'ns3::PLC_InterfaceTupel&')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantFreqSelectiveValue', 'ns3::PLC_TimeVariantTransferVector')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantFreqSelectiveValue*', 'ns3::PLC_TimeVariantTransferVector*')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantFreqSelectiveValue&', 'ns3::PLC_TimeVariantTransferVector&')
    module.add_typedef(root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], 'PLC_TimeVariantTransferVector')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PhyRxEndOkCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PhyRxEndOkCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PhyRxEndOkCallback&')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *', 'ns3::LogNodePrinter')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) **', 'ns3::LogNodePrinter*')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *&', 'ns3::LogNodePrinter&')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::PLC_FreqSelectiveResistance')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::PLC_FreqSelectiveResistance*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::PLC_FreqSelectiveResistance&')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_Node >, std::allocator< ns3::Ptr< ns3::PLC_Node > > >', 'ns3::PLC_NodeList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_Node >, std::allocator< ns3::Ptr< ns3::PLC_Node > > >*', 'ns3::PLC_NodeList*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_Node >, std::allocator< ns3::Ptr< ns3::PLC_Node > > >&', 'ns3::PLC_NodeList&')
    typehandlers.add_type_alias('ns3::PLC_ValueSpectrum', 'ns3::PLC_ImpedanceSpectrum')
    typehandlers.add_type_alias('ns3::PLC_ValueSpectrum*', 'ns3::PLC_ImpedanceSpectrum*')
    typehandlers.add_type_alias('ns3::PLC_ValueSpectrum&', 'ns3::PLC_ImpedanceSpectrum&')
    typehandlers.add_type_alias('ns3::backbone_branch_discover_thread_arg_t', 'ns3::backbone_branch_discover_thread_arg')
    typehandlers.add_type_alias('ns3::backbone_branch_discover_thread_arg_t*', 'ns3::backbone_branch_discover_thread_arg*')
    typehandlers.add_type_alias('ns3::backbone_branch_discover_thread_arg_t&', 'ns3::backbone_branch_discover_thread_arg&')
    module.add_typedef(root_module['ns3::backbone_branch_discover_thread_arg_t'], 'backbone_branch_discover_thread_arg')
    typehandlers.add_type_alias('ns3::PLC_Value', 'ns3::PLC_ImpedanceValue')
    typehandlers.add_type_alias('ns3::PLC_Value*', 'ns3::PLC_ImpedanceValue*')
    typehandlers.add_type_alias('ns3::PLC_Value&', 'ns3::PLC_ImpedanceValue&')
    typehandlers.add_type_alias('ns3::PLC_ConstValue', 'ns3::PLC_ConstImpedance')
    typehandlers.add_type_alias('ns3::PLC_ConstValue*', 'ns3::PLC_ConstImpedance*')
    typehandlers.add_type_alias('ns3::PLC_ConstValue&', 'ns3::PLC_ConstImpedance&')
    module.add_typedef(root_module['ns3::PLC_ConstValue'], 'PLC_ConstImpedance')
    typehandlers.add_type_alias('std::vector< std::complex< double >, std::allocator< std::complex< double > > >', 'ns3::PLC_TimeVariantValue')
    typehandlers.add_type_alias('std::vector< std::complex< double >, std::allocator< std::complex< double > > >*', 'ns3::PLC_TimeVariantValue*')
    typehandlers.add_type_alias('std::vector< std::complex< double >, std::allocator< std::complex< double > > >&', 'ns3::PLC_TimeVariantValue&')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::Values')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::Values*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::Values&')
    typehandlers.add_type_alias('std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >', 'ns3::PLC_TimeVariantFreqSelectiveRealValue')
    typehandlers.add_type_alias('std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >*', 'ns3::PLC_TimeVariantFreqSelectiveRealValue*')
    typehandlers.add_type_alias('std::vector< std::vector< double, std::allocator< double > >, std::allocator< std::vector< double, std::allocator< double > > > >&', 'ns3::PLC_TimeVariantFreqSelectiveRealValue&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PhyRxEndErrorCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PhyRxEndErrorCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PhyRxEndErrorCallback&')
    typehandlers.add_type_alias('ns3::PLC_FreqSelectiveValue', 'ns3::PLC_FreqSelectiveImpedance')
    typehandlers.add_type_alias('ns3::PLC_FreqSelectiveValue*', 'ns3::PLC_FreqSelectiveImpedance*')
    typehandlers.add_type_alias('ns3::PLC_FreqSelectiveValue&', 'ns3::PLC_FreqSelectiveImpedance&')
    module.add_typedef(root_module['ns3::PLC_FreqSelectiveValue'], 'PLC_FreqSelectiveImpedance')
    typehandlers.add_type_alias('std::map< std::string, ns3::Ptr< ns3::PLC_NetDevice >, std::less< std::string >, std::allocator< std::pair< std::string const, ns3::Ptr< ns3::PLC_NetDevice > > > >', 'ns3::PLC_NetdeviceMap')
    typehandlers.add_type_alias('std::map< std::string, ns3::Ptr< ns3::PLC_NetDevice >, std::less< std::string >, std::allocator< std::pair< std::string const, ns3::Ptr< ns3::PLC_NetDevice > > > >*', 'ns3::PLC_NetdeviceMap*')
    typehandlers.add_type_alias('std::map< std::string, ns3::Ptr< ns3::PLC_NetDevice >, std::less< std::string >, std::allocator< std::pair< std::string const, ns3::Ptr< ns3::PLC_NetDevice > > > >&', 'ns3::PLC_NetdeviceMap&')
    typehandlers.add_type_alias('std::vector< std::pair< ns3::Time, ns3::Ptr< ns3::SpectrumValue const > >, std::allocator< std::pair< ns3::Time, ns3::Ptr< ns3::SpectrumValue const > > > >', 'ns3::PLC_SinrTrace')
    typehandlers.add_type_alias('std::vector< std::pair< ns3::Time, ns3::Ptr< ns3::SpectrumValue const > >, std::allocator< std::pair< ns3::Time, ns3::Ptr< ns3::SpectrumValue const > > > >*', 'ns3::PLC_SinrTrace*')
    typehandlers.add_type_alias('std::vector< std::pair< ns3::Time, ns3::Ptr< ns3::SpectrumValue const > >, std::allocator< std::pair< ns3::Time, ns3::Ptr< ns3::SpectrumValue const > > > >&', 'ns3::PLC_SinrTrace&')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_NetDevice >, std::allocator< ns3::Ptr< ns3::PLC_NetDevice > > >', 'ns3::PLC_NetdeviceList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_NetDevice >, std::allocator< ns3::Ptr< ns3::PLC_NetDevice > > >*', 'ns3::PLC_NetdeviceList*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_NetDevice >, std::allocator< ns3::Ptr< ns3::PLC_NetDevice > > >&', 'ns3::PLC_NetdeviceList&')
    typehandlers.add_type_alias('uint32_t', 'ns3::Timeslot')
    typehandlers.add_type_alias('uint32_t*', 'ns3::Timeslot*')
    typehandlers.add_type_alias('uint32_t&', 'ns3::Timeslot&')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::PLC_EdgeTransferData_t, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::PLC_EdgeTransferData_t > > >', 'ns3::PLC_EdgeTransferDataMap')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::PLC_EdgeTransferData_t, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::PLC_EdgeTransferData_t > > >*', 'ns3::PLC_EdgeTransferDataMap*')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::PLC_EdgeTransferData_t, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::PLC_EdgeTransferData_t > > >&', 'ns3::PLC_EdgeTransferDataMap&')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::PLC_FreqSelectiveCapacitance')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::PLC_FreqSelectiveCapacitance*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::PLC_FreqSelectiveCapacitance&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PLC_PhyFrameSentCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PLC_PhyFrameSentCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PLC_PhyFrameSentCallback&')
    typehandlers.add_type_alias('std::pair< ns3::Ptr< ns3::PLC_Node >, double >', 'ns3::PLC_RandomNodeDescriptor')
    typehandlers.add_type_alias('std::pair< ns3::Ptr< ns3::PLC_Node >, double >*', 'ns3::PLC_RandomNodeDescriptor*')
    typehandlers.add_type_alias('std::pair< ns3::Ptr< ns3::PLC_Node >, double >&', 'ns3::PLC_RandomNodeDescriptor&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Mac48Address, ns3::Mac48Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PLC_MacDataCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Mac48Address, ns3::Mac48Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PLC_MacDataCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Mac48Address, ns3::Mac48Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PLC_MacDataCallback&')
    typehandlers.add_type_alias('std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >', 'ns3::PLC_RxPsdMap')
    typehandlers.add_type_alias('std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >*', 'ns3::PLC_RxPsdMap*')
    typehandlers.add_type_alias('std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >&', 'ns3::PLC_RxPsdMap&')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantConstValue', 'ns3::PLC_TimeVariantConstImpedance')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantConstValue*', 'ns3::PLC_TimeVariantConstImpedance*')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantConstValue&', 'ns3::PLC_TimeVariantConstImpedance&')
    module.add_typedef(root_module['ns3::PLC_TimeVariantConstValue'], 'PLC_TimeVariantConstImpedance')
    typehandlers.add_type_alias('ns3::sub_thread_arg_t', 'ns3::sub_thread_arg')
    typehandlers.add_type_alias('ns3::sub_thread_arg_t*', 'ns3::sub_thread_arg*')
    typehandlers.add_type_alias('ns3::sub_thread_arg_t&', 'ns3::sub_thread_arg&')
    module.add_typedef(root_module['ns3::sub_thread_arg_t'], 'sub_thread_arg')
    typehandlers.add_type_alias('ns3::PLC_ImpedanceIndicator_t', 'ns3::PLC_ImpedanceIndicator')
    typehandlers.add_type_alias('ns3::PLC_ImpedanceIndicator_t*', 'ns3::PLC_ImpedanceIndicator*')
    typehandlers.add_type_alias('ns3::PLC_ImpedanceIndicator_t&', 'ns3::PLC_ImpedanceIndicator&')
    module.add_typedef(root_module['ns3::PLC_ImpedanceIndicator_t'], 'PLC_ImpedanceIndicator')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::PLC_FreqSelectiveConductance')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::PLC_FreqSelectiveConductance*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::PLC_FreqSelectiveConductance&')
    typehandlers.add_type_alias('ns3::PLC_ValueBase', 'ns3::PLC_TransferBase')
    typehandlers.add_type_alias('ns3::PLC_ValueBase*', 'ns3::PLC_TransferBase*')
    typehandlers.add_type_alias('ns3::PLC_ValueBase&', 'ns3::PLC_TransferBase&')
    module.add_typedef(root_module['ns3::PLC_ValueBase'], 'PLC_TransferBase')
    typehandlers.add_type_alias('std::pair< unsigned int, std::pair< unsigned int, unsigned int > >', 'ns3::PLC_BackboneBranchKey')
    typehandlers.add_type_alias('std::pair< unsigned int, std::pair< unsigned int, unsigned int > >*', 'ns3::PLC_BackboneBranchKey*')
    typehandlers.add_type_alias('std::pair< unsigned int, std::pair< unsigned int, unsigned int > >&', 'ns3::PLC_BackboneBranchKey&')
    typehandlers.add_type_alias('ns3::Vector3DChecker', 'ns3::VectorChecker')
    typehandlers.add_type_alias('ns3::Vector3DChecker*', 'ns3::VectorChecker*')
    typehandlers.add_type_alias('ns3::Vector3DChecker&', 'ns3::VectorChecker&')
    module.add_typedef(root_module['ns3::Vector3DChecker'], 'VectorChecker')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *', 'ns3::LogTimePrinter')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) **', 'ns3::LogTimePrinter*')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *&', 'ns3::LogTimePrinter&')
    typehandlers.add_type_alias('ns3::PLC_ValueBase', 'ns3::PLC_Impedance')
    typehandlers.add_type_alias('ns3::PLC_ValueBase*', 'ns3::PLC_Impedance*')
    typehandlers.add_type_alias('ns3::PLC_ValueBase&', 'ns3::PLC_Impedance&')
    module.add_typedef(root_module['ns3::PLC_ValueBase'], 'PLC_Impedance')
    typehandlers.add_type_alias('std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > >', 'ns3::PLC_ReceiveDescriptorMap')
    typehandlers.add_type_alias('std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > >*', 'ns3::PLC_ReceiveDescriptorMap*')
    typehandlers.add_type_alias('std::map< unsigned int, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::map< unsigned int, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > >, std::less< unsigned int >, std::allocator< std::pair< unsigned int const, std::pair< unsigned int, ns3::Ptr< ns3::SpectrumValue > > > > > > > >&', 'ns3::PLC_ReceiveDescriptorMap&')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::PLC_FreqSelectiveRealValue')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::PLC_FreqSelectiveRealValue*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::PLC_FreqSelectiveRealValue&')
    typehandlers.add_type_alias('ns3::RngSeedManager', 'ns3::SeedManager')
    typehandlers.add_type_alias('ns3::RngSeedManager*', 'ns3::SeedManager*')
    typehandlers.add_type_alias('ns3::RngSeedManager&', 'ns3::SeedManager&')
    module.add_typedef(root_module['ns3::RngSeedManager'], 'SeedManager')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_Outlet >, std::allocator< ns3::Ptr< ns3::PLC_Outlet > > >', 'ns3::PLC_OutletList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_Outlet >, std::allocator< ns3::Ptr< ns3::PLC_Outlet > > >*', 'ns3::PLC_OutletList*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_Outlet >, std::allocator< ns3::Ptr< ns3::PLC_Outlet > > >&', 'ns3::PLC_OutletList&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PLC_CcaRequestCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PLC_CcaRequestCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PLC_CcaRequestCallback&')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::PLC_TimeVariantRealValue')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::PLC_TimeVariantRealValue*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::PLC_TimeVariantRealValue&')
    typehandlers.add_type_alias('std::vector< std::pair< ns3::Ptr< ns3::PLC_Node >, double >, std::allocator< std::pair< ns3::Ptr< ns3::PLC_Node >, double > > >', 'ns3::PLC_RandomLevelDescriptor')
    typehandlers.add_type_alias('std::vector< std::pair< ns3::Ptr< ns3::PLC_Node >, double >, std::allocator< std::pair< ns3::Ptr< ns3::PLC_Node >, double > > >*', 'ns3::PLC_RandomLevelDescriptor*')
    typehandlers.add_type_alias('std::vector< std::pair< ns3::Ptr< ns3::PLC_Node >, double >, std::allocator< std::pair< ns3::Ptr< ns3::PLC_Node >, double > > >&', 'ns3::PLC_RandomLevelDescriptor&')
    typehandlers.add_type_alias('std::vector< ns3::BandInfo, std::allocator< ns3::BandInfo > >', 'ns3::Bands')
    typehandlers.add_type_alias('std::vector< ns3::BandInfo, std::allocator< ns3::BandInfo > >*', 'ns3::Bands*')
    typehandlers.add_type_alias('std::vector< ns3::BandInfo, std::allocator< ns3::BandInfo > >&', 'ns3::Bands&')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_NoiseSource >, std::allocator< ns3::Ptr< ns3::PLC_NoiseSource > > >', 'ns3::PLC_NoiseSourceList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_NoiseSource >, std::allocator< ns3::Ptr< ns3::PLC_NoiseSource > > >*', 'ns3::PLC_NoiseSourceList*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_NoiseSource >, std::allocator< ns3::Ptr< ns3::PLC_NoiseSource > > >&', 'ns3::PLC_NoiseSourceList&')
    typehandlers.add_type_alias('uint32_t', 'ns3::SpectrumModelUid_t')
    typehandlers.add_type_alias('uint32_t*', 'ns3::SpectrumModelUid_t*')
    typehandlers.add_type_alias('uint32_t&', 'ns3::SpectrumModelUid_t&')
    typehandlers.add_type_alias('ns3::boostgraph_copy_t', 'ns3::boostgraph_copy')
    typehandlers.add_type_alias('ns3::boostgraph_copy_t*', 'ns3::boostgraph_copy*')
    typehandlers.add_type_alias('ns3::boostgraph_copy_t&', 'ns3::boostgraph_copy&')
    module.add_typedef(root_module['ns3::boostgraph_copy_t'], 'boostgraph_copy')
    typehandlers.add_type_alias('ns3::PLC_FreqSelectiveValue', 'ns3::PLC_TransferVector')
    typehandlers.add_type_alias('ns3::PLC_FreqSelectiveValue*', 'ns3::PLC_TransferVector*')
    typehandlers.add_type_alias('ns3::PLC_FreqSelectiveValue&', 'ns3::PLC_TransferVector&')
    module.add_typedef(root_module['ns3::PLC_FreqSelectiveValue'], 'PLC_TransferVector')
    typehandlers.add_type_alias('ns3::Vector3D', 'ns3::Vector')
    typehandlers.add_type_alias('ns3::Vector3D*', 'ns3::Vector*')
    typehandlers.add_type_alias('ns3::Vector3D&', 'ns3::Vector&')
    module.add_typedef(root_module['ns3::Vector3D'], 'Vector')
    typehandlers.add_type_alias('std::vector< std::complex< double >, std::allocator< std::complex< double > > >', 'ns3::PLC_ValueSpectrum')
    typehandlers.add_type_alias('std::vector< std::complex< double >, std::allocator< std::complex< double > > >*', 'ns3::PLC_ValueSpectrum*')
    typehandlers.add_type_alias('std::vector< std::complex< double >, std::allocator< std::complex< double > > >&', 'ns3::PLC_ValueSpectrum&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PLC_MacAcknowledgementCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PLC_MacAcknowledgementCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PLC_MacAcknowledgementCallback&')
    typehandlers.add_type_alias('ns3::Vector3DValue', 'ns3::VectorValue')
    typehandlers.add_type_alias('ns3::Vector3DValue*', 'ns3::VectorValue*')
    typehandlers.add_type_alias('ns3::Vector3DValue&', 'ns3::VectorValue&')
    module.add_typedef(root_module['ns3::Vector3DValue'], 'VectorValue')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_BackboneBranch >, std::allocator< ns3::Ptr< ns3::PLC_BackboneBranch > > >', 'ns3::PLC_BackbonePath')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_BackboneBranch >, std::allocator< ns3::Ptr< ns3::PLC_BackboneBranch > > >*', 'ns3::PLC_BackbonePath*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_BackboneBranch >, std::allocator< ns3::Ptr< ns3::PLC_BackboneBranch > > >&', 'ns3::PLC_BackbonePath&')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >', 'ns3::PLC_FreqSelectiveInductance')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >*', 'ns3::PLC_FreqSelectiveInductance*')
    typehandlers.add_type_alias('std::vector< double, std::allocator< double > >&', 'ns3::PLC_FreqSelectiveInductance&')
    typehandlers.add_type_alias('ns3::thread_arg_t', 'ns3::thread_arg')
    typehandlers.add_type_alias('ns3::thread_arg_t*', 'ns3::thread_arg*')
    typehandlers.add_type_alias('ns3::thread_arg_t&', 'ns3::thread_arg&')
    module.add_typedef(root_module['ns3::thread_arg_t'], 'thread_arg')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::Ptr< ns3::PLC_Line >, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Line > > > >', 'ns3::PLC_NodeOutlinesMap')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::Ptr< ns3::PLC_Line >, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Line > > > >*', 'ns3::PLC_NodeOutlinesMap*')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::Ptr< ns3::PLC_Line >, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Line > > > >&', 'ns3::PLC_NodeOutlinesMap&')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::Ptr< ns3::PLC_Edge >, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Edge > > > >', 'ns3::PLC_NodeOutEdgesMap')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::Ptr< ns3::PLC_Edge >, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Edge > > > >*', 'ns3::PLC_NodeOutEdgesMap*')
    typehandlers.add_type_alias('std::map< ns3::PLC_Node *, ns3::Ptr< ns3::PLC_Edge >, std::less< ns3::PLC_Node * >, std::allocator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Edge > > > >&', 'ns3::PLC_NodeOutEdgesMap&')
    typehandlers.add_type_alias('ns3::PLC_EdgeTransferData_t', 'ns3::PLC_EdgeTransferData')
    typehandlers.add_type_alias('ns3::PLC_EdgeTransferData_t*', 'ns3::PLC_EdgeTransferData*')
    typehandlers.add_type_alias('ns3::PLC_EdgeTransferData_t&', 'ns3::PLC_EdgeTransferData&')
    module.add_typedef(root_module['ns3::PLC_EdgeTransferData_t'], 'PLC_EdgeTransferData')
    typehandlers.add_type_alias('std::pair< ns3::Ptr< ns3::PLC_ValueBase >, ns3::PLC_ImpedanceIndicator_t >', 'ns3::PLC_InputImpedance')
    typehandlers.add_type_alias('std::pair< ns3::Ptr< ns3::PLC_ValueBase >, ns3::PLC_ImpedanceIndicator_t >*', 'ns3::PLC_InputImpedance*')
    typehandlers.add_type_alias('std::pair< ns3::Ptr< ns3::PLC_ValueBase >, ns3::PLC_ImpedanceIndicator_t >&', 'ns3::PLC_InputImpedance&')
    typehandlers.add_type_alias('ns3::PLC_TwoPort', 'ns3::PLC_Transformer')
    typehandlers.add_type_alias('ns3::PLC_TwoPort*', 'ns3::PLC_Transformer*')
    typehandlers.add_type_alias('ns3::PLC_TwoPort&', 'ns3::PLC_Transformer&')
    module.add_typedef(root_module['ns3::PLC_TwoPort'], 'PLC_Transformer')
    typehandlers.add_type_alias('std::vector< std::vector< std::complex< double >, std::allocator< std::complex< double > > >, std::allocator< std::vector< std::complex< double >, std::allocator< std::complex< double > > > > >', 'ns3::PLC_TimeVariantValueSpectrum')
    typehandlers.add_type_alias('std::vector< std::vector< std::complex< double >, std::allocator< std::complex< double > > >, std::allocator< std::vector< std::complex< double >, std::allocator< std::complex< double > > > > >*', 'ns3::PLC_TimeVariantValueSpectrum*')
    typehandlers.add_type_alias('std::vector< std::vector< std::complex< double >, std::allocator< std::complex< double > > >, std::allocator< std::vector< std::complex< double >, std::allocator< std::complex< double > > > > >&', 'ns3::PLC_TimeVariantValueSpectrum&')
    typehandlers.add_type_alias('std::complex< double >', 'ns3::PLC_Value')
    typehandlers.add_type_alias('std::complex< double >*', 'ns3::PLC_Value*')
    typehandlers.add_type_alias('std::complex< double >&', 'ns3::PLC_Value&')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantFreqSelectiveValue', 'ns3::PLC_TimeVariantFreqSelectiveImpedance')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantFreqSelectiveValue*', 'ns3::PLC_TimeVariantFreqSelectiveImpedance*')
    typehandlers.add_type_alias('ns3::PLC_TimeVariantFreqSelectiveValue&', 'ns3::PLC_TimeVariantFreqSelectiveImpedance&')
    module.add_typedef(root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], 'PLC_TimeVariantFreqSelectiveImpedance')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_TwoPort >, std::allocator< ns3::Ptr< ns3::PLC_TwoPort > > >', 'ns3::PLC_TransformerList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_TwoPort >, std::allocator< ns3::Ptr< ns3::PLC_TwoPort > > >*', 'ns3::PLC_TransformerList*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::PLC_TwoPort >, std::allocator< ns3::Ptr< ns3::PLC_TwoPort > > >&', 'ns3::PLC_TransformerList&')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::PLC_PhyCcaResult, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ns3::PLC_PhyCcaConfirmCallback')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::PLC_PhyCcaResult, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >*', 'ns3::PLC_PhyCcaConfirmCallback*')
    typehandlers.add_type_alias('ns3::Callback< void, ns3::PLC_PhyCcaResult, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >&', 'ns3::PLC_PhyCcaConfirmCallback&')
    
    ## Register a nested module for the namespace FatalImpl
    
    nested_module = module.add_cpp_namespace('FatalImpl')
    register_types_ns3_FatalImpl(nested_module)
    
    
    ## Register a nested module for the namespace internal
    
    nested_module = module.add_cpp_namespace('internal')
    register_types_ns3_internal(nested_module)
    

def register_types_ns3_FatalImpl(module):
    root_module = module.get_root()
    

def register_types_ns3_internal(module):
    root_module = module.get_root()
    

def register_methods(root_module):
    register_Ns3Address_methods(root_module, root_module['ns3::Address'])
    register_Ns3AttributeConstructionList_methods(root_module, root_module['ns3::AttributeConstructionList'])
    register_Ns3AttributeConstructionListItem_methods(root_module, root_module['ns3::AttributeConstructionList::Item'])
    register_Ns3BandInfo_methods(root_module, root_module['ns3::BandInfo'])
    register_Ns3Buffer_methods(root_module, root_module['ns3::Buffer'])
    register_Ns3BufferIterator_methods(root_module, root_module['ns3::Buffer::Iterator'])
    register_Ns3ByteTagIterator_methods(root_module, root_module['ns3::ByteTagIterator'])
    register_Ns3ByteTagIteratorItem_methods(root_module, root_module['ns3::ByteTagIterator::Item'])
    register_Ns3ByteTagList_methods(root_module, root_module['ns3::ByteTagList'])
    register_Ns3ByteTagListIterator_methods(root_module, root_module['ns3::ByteTagList::Iterator'])
    register_Ns3ByteTagListIteratorItem_methods(root_module, root_module['ns3::ByteTagList::Iterator::Item'])
    register_Ns3CallbackBase_methods(root_module, root_module['ns3::CallbackBase'])
    register_Ns3DataRate_methods(root_module, root_module['ns3::DataRate'])
    register_Ns3EventId_methods(root_module, root_module['ns3::EventId'])
    register_Ns3Ipv4Address_methods(root_module, root_module['ns3::Ipv4Address'])
    register_Ns3Ipv4Mask_methods(root_module, root_module['ns3::Ipv4Mask'])
    register_Ns3Ipv6Address_methods(root_module, root_module['ns3::Ipv6Address'])
    register_Ns3Ipv6Prefix_methods(root_module, root_module['ns3::Ipv6Prefix'])
    register_Ns3LogComponent_methods(root_module, root_module['ns3::LogComponent'])
    register_Ns3Mac48Address_methods(root_module, root_module['ns3::Mac48Address'])
    register_Ns3ObjectBase_methods(root_module, root_module['ns3::ObjectBase'])
    register_Ns3ObjectDeleter_methods(root_module, root_module['ns3::ObjectDeleter'])
    register_Ns3ObjectFactory_methods(root_module, root_module['ns3::ObjectFactory'])
    register_Ns3PLC_EdgeTransferData_t_methods(root_module, root_module['ns3::PLC_EdgeTransferData_t'])
    register_Ns3PLC_ImpedanceIndicator_t_methods(root_module, root_module['ns3::PLC_ImpedanceIndicator_t'])
    register_Ns3PLC_Mutex_methods(root_module, root_module['ns3::PLC_Mutex'])
    register_Ns3PLC_Time_methods(root_module, root_module['ns3::PLC_Time'])
    register_Ns3PacketMetadata_methods(root_module, root_module['ns3::PacketMetadata'])
    register_Ns3PacketMetadataItem_methods(root_module, root_module['ns3::PacketMetadata::Item'])
    register_Ns3PacketMetadataItemIterator_methods(root_module, root_module['ns3::PacketMetadata::ItemIterator'])
    register_Ns3PacketTagIterator_methods(root_module, root_module['ns3::PacketTagIterator'])
    register_Ns3PacketTagIteratorItem_methods(root_module, root_module['ns3::PacketTagIterator::Item'])
    register_Ns3PacketTagList_methods(root_module, root_module['ns3::PacketTagList'])
    register_Ns3PacketTagListTagData_methods(root_module, root_module['ns3::PacketTagList::TagData'])
    register_Ns3RandomVariable_methods(root_module, root_module['ns3::RandomVariable'])
    register_Ns3RngSeedManager_methods(root_module, root_module['ns3::RngSeedManager'])
    register_Ns3SequentialVariable_methods(root_module, root_module['ns3::SequentialVariable'])
    register_Ns3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_methods(root_module, root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    register_Ns3Tag_methods(root_module, root_module['ns3::Tag'])
    register_Ns3TagBuffer_methods(root_module, root_module['ns3::TagBuffer'])
    register_Ns3TriangularVariable_methods(root_module, root_module['ns3::TriangularVariable'])
    register_Ns3TypeId_methods(root_module, root_module['ns3::TypeId'])
    register_Ns3TypeIdAttributeInformation_methods(root_module, root_module['ns3::TypeId::AttributeInformation'])
    register_Ns3TypeIdTraceSourceInformation_methods(root_module, root_module['ns3::TypeId::TraceSourceInformation'])
    register_Ns3UniformVariable_methods(root_module, root_module['ns3::UniformVariable'])
    register_Ns3Vector2D_methods(root_module, root_module['ns3::Vector2D'])
    register_Ns3Vector3D_methods(root_module, root_module['ns3::Vector3D'])
    register_Ns3WeibullVariable_methods(root_module, root_module['ns3::WeibullVariable'])
    register_Ns3ZetaVariable_methods(root_module, root_module['ns3::ZetaVariable'])
    register_Ns3ZipfVariable_methods(root_module, root_module['ns3::ZipfVariable'])
    register_Ns3Backbone_branch_discover_thread_arg_t_methods(root_module, root_module['ns3::backbone_branch_discover_thread_arg_t'])
    register_Ns3Boostgraph_copy_t_methods(root_module, root_module['ns3::boostgraph_copy_t'])
    register_Ns3Empty_methods(root_module, root_module['ns3::empty'])
    register_Ns3Int64x64_t_methods(root_module, root_module['ns3::int64x64_t'])
    register_Ns3Sub_thread_arg_t_methods(root_module, root_module['ns3::sub_thread_arg_t'])
    register_Ns3Thread_arg_t_methods(root_module, root_module['ns3::thread_arg_t'])
    register_Ns3Chunk_methods(root_module, root_module['ns3::Chunk'])
    register_Ns3ConstantVariable_methods(root_module, root_module['ns3::ConstantVariable'])
    register_Ns3DeterministicVariable_methods(root_module, root_module['ns3::DeterministicVariable'])
    register_Ns3EmpiricalVariable_methods(root_module, root_module['ns3::EmpiricalVariable'])
    register_Ns3ErlangVariable_methods(root_module, root_module['ns3::ErlangVariable'])
    register_Ns3ExponentialVariable_methods(root_module, root_module['ns3::ExponentialVariable'])
    register_Ns3GammaVariable_methods(root_module, root_module['ns3::GammaVariable'])
    register_Ns3Header_methods(root_module, root_module['ns3::Header'])
    register_Ns3IntEmpiricalVariable_methods(root_module, root_module['ns3::IntEmpiricalVariable'])
    register_Ns3LogNormalVariable_methods(root_module, root_module['ns3::LogNormalVariable'])
    register_Ns3NormalVariable_methods(root_module, root_module['ns3::NormalVariable'])
    register_Ns3Object_methods(root_module, root_module['ns3::Object'])
    register_Ns3ObjectAggregateIterator_methods(root_module, root_module['ns3::Object::AggregateIterator'])
    register_Ns3PLC_BackboneBranch_methods(root_module, root_module['ns3::PLC_BackboneBranch'])
    register_Ns3PLC_Cable_methods(root_module, root_module['ns3::PLC_Cable'])
    register_Ns3PLC_ChannelHelper_methods(root_module, root_module['ns3::PLC_ChannelHelper'])
    register_Ns3PLC_ChannelTransferImpl_methods(root_module, root_module['ns3::PLC_ChannelTransferImpl'])
    register_Ns3PLC_Edge_methods(root_module, root_module['ns3::PLC_Edge'])
    register_Ns3PLC_EdgeTransferUnit_methods(root_module, root_module['ns3::PLC_EdgeTransferUnit'])
    register_Ns3PLC_FourSectorPowerSupplyCable_methods(root_module, root_module['ns3::PLC_FourSectorPowerSupplyCable'])
    register_Ns3PLC_Graph_methods(root_module, root_module['ns3::PLC_Graph'])
    register_Ns3PLC_ImpedanceHelper_methods(root_module, root_module['ns3::PLC_ImpedanceHelper'])
    register_Ns3PLC_Interface_methods(root_module, root_module['ns3::PLC_Interface'])
    register_Ns3PLC_Interference_methods(root_module, root_module['ns3::PLC_Interference'])
    register_Ns3PLC_Line_methods(root_module, root_module['ns3::PLC_Line'])
    register_Ns3PLC_LinkPerformanceModel_methods(root_module, root_module['ns3::PLC_LinkPerformanceModel'])
    register_Ns3PLC_Mac_methods(root_module, root_module['ns3::PLC_Mac'])
    register_Ns3PLC_MacHeader_methods(root_module, root_module['ns3::PLC_MacHeader'])
    register_Ns3PLC_NAYY150SE_Cable_methods(root_module, root_module['ns3::PLC_NAYY150SE_Cable'])
    register_Ns3PLC_NAYY50SE_Cable_methods(root_module, root_module['ns3::PLC_NAYY50SE_Cable'])
    register_Ns3PLC_NetDeviceHelper_methods(root_module, root_module['ns3::PLC_NetDeviceHelper'])
    register_Ns3PLC_Node_methods(root_module, root_module['ns3::PLC_Node'])
    register_Ns3PLC_NoiseSource_methods(root_module, root_module['ns3::PLC_NoiseSource'])
    register_Ns3PLC_Outlet_methods(root_module, root_module['ns3::PLC_Outlet'])
    register_Ns3PLC_Phy_methods(root_module, root_module['ns3::PLC_Phy'])
    register_Ns3PLC_PhyFrameControlHeader_methods(root_module, root_module['ns3::PLC_PhyFrameControlHeader'])
    register_Ns3PLC_PhyRatelessFrameControlHeader_methods(root_module, root_module['ns3::PLC_PhyRatelessFrameControlHeader'])
    register_Ns3PLC_Preamble_methods(root_module, root_module['ns3::PLC_Preamble'])
    register_Ns3PLC_RxInterface_methods(root_module, root_module['ns3::PLC_RxInterface'])
    register_Ns3PLC_SpectrumModelHelper_methods(root_module, root_module['ns3::PLC_SpectrumModelHelper'])
    register_Ns3PLC_StaticNoiseSource_methods(root_module, root_module['ns3::PLC_StaticNoiseSource'])
    register_Ns3PLC_ThreeCoreConcentricCable_methods(root_module, root_module['ns3::PLC_ThreeCoreConcentricCable'])
    register_Ns3PLC_TimeInvariantSpectrumHelper_methods(root_module, root_module['ns3::PLC_TimeInvariantSpectrumHelper'])
    register_Ns3PLC_TrxMetaInfo_methods(root_module, root_module['ns3::PLC_TrxMetaInfo'])
    register_Ns3PLC_TwoPort_methods(root_module, root_module['ns3::PLC_TwoPort'])
    register_Ns3PLC_TxInterface_methods(root_module, root_module['ns3::PLC_TxInterface'])
    register_Ns3PLC_ValueBase_methods(root_module, root_module['ns3::PLC_ValueBase'])
    register_Ns3PacketBurst_methods(root_module, root_module['ns3::PacketBurst'])
    register_Ns3ParetoVariable_methods(root_module, root_module['ns3::ParetoVariable'])
    register_Ns3Scheduler_methods(root_module, root_module['ns3::Scheduler'])
    register_Ns3SchedulerEvent_methods(root_module, root_module['ns3::Scheduler::Event'])
    register_Ns3SchedulerEventKey_methods(root_module, root_module['ns3::Scheduler::EventKey'])
    register_Ns3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    register_Ns3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    register_Ns3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    register_Ns3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >'])
    register_Ns3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    register_Ns3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >'])
    register_Ns3SimpleRefCount__Ns3PLC_ColoredNoiseFloor_Ns3Empty_Ns3DefaultDeleter__lt__ns3PLC_ColoredNoiseFloor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> >'])
    register_Ns3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >'])
    register_Ns3SimpleRefCount__Ns3SpectrumModel_Ns3Empty_Ns3DefaultDeleter__lt__ns3SpectrumModel__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> >'])
    register_Ns3SimpleRefCount__Ns3SpectrumValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3SpectrumValue__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> >'])
    register_Ns3SimpleRefCount__Ns3SystemThread_Ns3Empty_Ns3DefaultDeleter__lt__ns3SystemThread__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> >'])
    register_Ns3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    register_Ns3SimulatorImpl_methods(root_module, root_module['ns3::SimulatorImpl'])
    register_Ns3SpectrumModel_methods(root_module, root_module['ns3::SpectrumModel'])
    register_Ns3SpectrumValue_methods(root_module, root_module['ns3::SpectrumValue'])
    register_Ns3SystemThread_methods(root_module, root_module['ns3::SystemThread'])
    register_Ns3Time_methods(root_module, root_module['ns3::Time'])
    register_Ns3TraceSourceAccessor_methods(root_module, root_module['ns3::TraceSourceAccessor'])
    register_Ns3Trailer_methods(root_module, root_module['ns3::Trailer'])
    register_Ns3AttributeAccessor_methods(root_module, root_module['ns3::AttributeAccessor'])
    register_Ns3AttributeChecker_methods(root_module, root_module['ns3::AttributeChecker'])
    register_Ns3AttributeValue_methods(root_module, root_module['ns3::AttributeValue'])
    register_Ns3BooleanChecker_methods(root_module, root_module['ns3::BooleanChecker'])
    register_Ns3BooleanValue_methods(root_module, root_module['ns3::BooleanValue'])
    register_Ns3CallbackChecker_methods(root_module, root_module['ns3::CallbackChecker'])
    register_Ns3CallbackImplBase_methods(root_module, root_module['ns3::CallbackImplBase'])
    register_Ns3CallbackValue_methods(root_module, root_module['ns3::CallbackValue'])
    register_Ns3Channel_methods(root_module, root_module['ns3::Channel'])
    register_Ns3DataRateChecker_methods(root_module, root_module['ns3::DataRateChecker'])
    register_Ns3DataRateValue_methods(root_module, root_module['ns3::DataRateValue'])
    register_Ns3DoubleValue_methods(root_module, root_module['ns3::DoubleValue'])
    register_Ns3EmptyAttributeValue_methods(root_module, root_module['ns3::EmptyAttributeValue'])
    register_Ns3EnumChecker_methods(root_module, root_module['ns3::EnumChecker'])
    register_Ns3EnumValue_methods(root_module, root_module['ns3::EnumValue'])
    register_Ns3EventImpl_methods(root_module, root_module['ns3::EventImpl'])
    register_Ns3IntegerValue_methods(root_module, root_module['ns3::IntegerValue'])
    register_Ns3Ipv4AddressChecker_methods(root_module, root_module['ns3::Ipv4AddressChecker'])
    register_Ns3Ipv4AddressValue_methods(root_module, root_module['ns3::Ipv4AddressValue'])
    register_Ns3Ipv4MaskChecker_methods(root_module, root_module['ns3::Ipv4MaskChecker'])
    register_Ns3Ipv4MaskValue_methods(root_module, root_module['ns3::Ipv4MaskValue'])
    register_Ns3Ipv6AddressChecker_methods(root_module, root_module['ns3::Ipv6AddressChecker'])
    register_Ns3Ipv6AddressValue_methods(root_module, root_module['ns3::Ipv6AddressValue'])
    register_Ns3Ipv6PrefixChecker_methods(root_module, root_module['ns3::Ipv6PrefixChecker'])
    register_Ns3Ipv6PrefixValue_methods(root_module, root_module['ns3::Ipv6PrefixValue'])
    register_Ns3Mac48AddressChecker_methods(root_module, root_module['ns3::Mac48AddressChecker'])
    register_Ns3Mac48AddressValue_methods(root_module, root_module['ns3::Mac48AddressValue'])
    register_Ns3NetDevice_methods(root_module, root_module['ns3::NetDevice'])
    register_Ns3NixVector_methods(root_module, root_module['ns3::NixVector'])
    register_Ns3Node_methods(root_module, root_module['ns3::Node'])
    register_Ns3ObjectFactoryChecker_methods(root_module, root_module['ns3::ObjectFactoryChecker'])
    register_Ns3ObjectFactoryValue_methods(root_module, root_module['ns3::ObjectFactoryValue'])
    register_Ns3PLC_AL3x95XLPE_Cable_methods(root_module, root_module['ns3::PLC_AL3x95XLPE_Cable'])
    register_Ns3PLC_ArqMac_methods(root_module, root_module['ns3::PLC_ArqMac'])
    register_Ns3PLC_Channel_methods(root_module, root_module['ns3::PLC_Channel'])
    register_Ns3PLC_ColoredNoiseFloor_methods(root_module, root_module['ns3::PLC_ColoredNoiseFloor'])
    register_Ns3PLC_ConstValue_methods(root_module, root_module['ns3::PLC_ConstValue'])
    register_Ns3PLC_ErrorRateModel_methods(root_module, root_module['ns3::PLC_ErrorRateModel'])
    register_Ns3PLC_FreqSelectiveValue_methods(root_module, root_module['ns3::PLC_FreqSelectiveValue'])
    register_Ns3PLC_HalfDuplexOfdmPhy_methods(root_module, root_module['ns3::PLC_HalfDuplexOfdmPhy'])
    register_Ns3PLC_HarqMac_methods(root_module, root_module['ns3::PLC_HarqMac'])
    register_Ns3PLC_ImpulseNoiseSource_methods(root_module, root_module['ns3::PLC_ImpulseNoiseSource'])
    register_Ns3PLC_ImpulsiveNoiseSource_methods(root_module, root_module['ns3::PLC_ImpulsiveNoiseSource'])
    register_Ns3PLC_InformationRateModel_methods(root_module, root_module['ns3::PLC_InformationRateModel'])
    register_Ns3PLC_InformationRateModelMcsInfo_methods(root_module, root_module['ns3::PLC_InformationRateModel::McsInfo'])
    register_Ns3PLC_InformationRatePhy_methods(root_module, root_module['ns3::PLC_InformationRatePhy'])
    register_Ns3PLC_NYCY70SM35_Cable_methods(root_module, root_module['ns3::PLC_NYCY70SM35_Cable'])
    register_Ns3PLC_NetDevice_methods(root_module, root_module['ns3::PLC_NetDevice'])
    register_Ns3PLC_SimulatorImpl_methods(root_module, root_module['ns3::PLC_SimulatorImpl'])
    register_Ns3PLC_SincSpectrumHelper_methods(root_module, root_module['ns3::PLC_SincSpectrumHelper'])
    register_Ns3PLC_TimeVariantConstValue_methods(root_module, root_module['ns3::PLC_TimeVariantConstValue'])
    register_Ns3PLC_TimeVariantFreqSelectiveValue_methods(root_module, root_module['ns3::PLC_TimeVariantFreqSelectiveValue'])
    register_Ns3PLC_TimeVariantFreqSelectiveValuePLC_TimeVariantParamSet_methods(root_module, root_module['ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet'])
    register_Ns3Packet_methods(root_module, root_module['ns3::Packet'])
    register_Ns3RandomVariableChecker_methods(root_module, root_module['ns3::RandomVariableChecker'])
    register_Ns3RandomVariableValue_methods(root_module, root_module['ns3::RandomVariableValue'])
    register_Ns3TimeChecker_methods(root_module, root_module['ns3::TimeChecker'])
    register_Ns3TimeValue_methods(root_module, root_module['ns3::TimeValue'])
    register_Ns3TypeIdChecker_methods(root_module, root_module['ns3::TypeIdChecker'])
    register_Ns3TypeIdValue_methods(root_module, root_module['ns3::TypeIdValue'])
    register_Ns3UintegerValue_methods(root_module, root_module['ns3::UintegerValue'])
    register_Ns3Vector2DChecker_methods(root_module, root_module['ns3::Vector2DChecker'])
    register_Ns3Vector2DValue_methods(root_module, root_module['ns3::Vector2DValue'])
    register_Ns3Vector3DChecker_methods(root_module, root_module['ns3::Vector3DChecker'])
    register_Ns3Vector3DValue_methods(root_module, root_module['ns3::Vector3DValue'])
    register_Ns3AddressChecker_methods(root_module, root_module['ns3::AddressChecker'])
    register_Ns3AddressValue_methods(root_module, root_module['ns3::AddressValue'])
    register_Ns3BridgeChannel_methods(root_module, root_module['ns3::BridgeChannel'])
    register_Ns3BridgeNetDevice_methods(root_module, root_module['ns3::BridgeNetDevice'])
    register_Ns3PLC_ChaseCombiningPhy_methods(root_module, root_module['ns3::PLC_ChaseCombiningPhy'])
    register_Ns3PLC_ErrorRatePhy_methods(root_module, root_module['ns3::PLC_ErrorRatePhy'])
    register_Ns3PLC_IncrementalRedundancyPhy_methods(root_module, root_module['ns3::PLC_IncrementalRedundancyPhy'])
    return

def register_Ns3Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('<')
    ## address.h (module 'network'): ns3::Address::Address() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::Address::Address(uint8_t type, uint8_t const * buffer, uint8_t len) [constructor]
    cls.add_constructor([param('uint8_t', 'type'), param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): ns3::Address::Address(ns3::Address const & address) [copy constructor]
    cls.add_constructor([param('ns3::Address const &', 'address')])
    ## address.h (module 'network'): bool ns3::Address::CheckCompatible(uint8_t type, uint8_t len) const [member function]
    cls.add_method('CheckCompatible', 
                   'bool', 
                   [param('uint8_t', 'type'), param('uint8_t', 'len')], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::CopyAllFrom(uint8_t const * buffer, uint8_t len) [member function]
    cls.add_method('CopyAllFrom', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): uint32_t ns3::Address::CopyAllTo(uint8_t * buffer, uint8_t len) const [member function]
    cls.add_method('CopyAllTo', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint8_t', 'len')], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::CopyFrom(uint8_t const * buffer, uint8_t len) [member function]
    cls.add_method('CopyFrom', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): uint32_t ns3::Address::CopyTo(uint8_t * buffer) const [member function]
    cls.add_method('CopyTo', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer')], 
                   is_const=True)
    ## address.h (module 'network'): void ns3::Address::Deserialize(ns3::TagBuffer buffer) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'buffer')])
    ## address.h (module 'network'): uint8_t ns3::Address::GetLength() const [member function]
    cls.add_method('GetLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): bool ns3::Address::IsInvalid() const [member function]
    cls.add_method('IsInvalid', 
                   'bool', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): bool ns3::Address::IsMatchingType(uint8_t type) const [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('uint8_t', 'type')], 
                   is_const=True)
    ## address.h (module 'network'): static uint8_t ns3::Address::Register() [member function]
    cls.add_method('Register', 
                   'uint8_t', 
                   [], 
                   is_static=True)
    ## address.h (module 'network'): void ns3::Address::Serialize(ns3::TagBuffer buffer) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'buffer')], 
                   is_const=True)
    return

def register_Ns3AttributeConstructionList_methods(root_module, cls):
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::AttributeConstructionList(ns3::AttributeConstructionList const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeConstructionList const &', 'arg0')])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::AttributeConstructionList() [constructor]
    cls.add_constructor([])
    ## attribute-construction-list.h (module 'core'): void ns3::AttributeConstructionList::Add(std::string name, ns3::Ptr<ns3::AttributeChecker const> checker, ns3::Ptr<ns3::AttributeValue> value) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker'), param('ns3::Ptr< ns3::AttributeValue >', 'value')])
    ## attribute-construction-list.h (module 'core'): std::_List_const_iterator<ns3::AttributeConstructionList::Item> ns3::AttributeConstructionList::Begin() const [member function]
    cls.add_method('Begin', 
                   'std::_List_const_iterator< ns3::AttributeConstructionList::Item >', 
                   [], 
                   is_const=True)
    ## attribute-construction-list.h (module 'core'): std::_List_const_iterator<ns3::AttributeConstructionList::Item> ns3::AttributeConstructionList::End() const [member function]
    cls.add_method('End', 
                   'std::_List_const_iterator< ns3::AttributeConstructionList::Item >', 
                   [], 
                   is_const=True)
    ## attribute-construction-list.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeConstructionList::Find(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('Find', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True)
    return

def register_Ns3AttributeConstructionListItem_methods(root_module, cls):
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::Item() [constructor]
    cls.add_constructor([])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::Item(ns3::AttributeConstructionList::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeConstructionList::Item const &', 'arg0')])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::checker [variable]
    cls.add_instance_attribute('checker', 'ns3::Ptr< ns3::AttributeChecker const >', is_const=False)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::value [variable]
    cls.add_instance_attribute('value', 'ns3::Ptr< ns3::AttributeValue >', is_const=False)
    return

def register_Ns3BandInfo_methods(root_module, cls):
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo::BandInfo() [constructor]
    cls.add_constructor([])
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo::BandInfo(ns3::BandInfo const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::BandInfo const &', 'arg0')])
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo::fc [variable]
    cls.add_instance_attribute('fc', 'double', is_const=False)
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo::fh [variable]
    cls.add_instance_attribute('fh', 'double', is_const=False)
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo::fl [variable]
    cls.add_instance_attribute('fl', 'double', is_const=False)
    return

def register_Ns3Buffer_methods(root_module, cls):
    ## buffer.h (module 'network'): ns3::Buffer::Buffer() [constructor]
    cls.add_constructor([])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(uint32_t dataSize) [constructor]
    cls.add_constructor([param('uint32_t', 'dataSize')])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(uint32_t dataSize, bool initialize) [constructor]
    cls.add_constructor([param('uint32_t', 'dataSize'), param('bool', 'initialize')])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(ns3::Buffer const & o) [copy constructor]
    cls.add_constructor([param('ns3::Buffer const &', 'o')])
    ## buffer.h (module 'network'): bool ns3::Buffer::AddAtEnd(uint32_t end) [member function]
    cls.add_method('AddAtEnd', 
                   'bool', 
                   [param('uint32_t', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::AddAtEnd(ns3::Buffer const & o) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::Buffer const &', 'o')])
    ## buffer.h (module 'network'): bool ns3::Buffer::AddAtStart(uint32_t start) [member function]
    cls.add_method('AddAtStart', 
                   'bool', 
                   [param('uint32_t', 'start')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator ns3::Buffer::Begin() const [member function]
    cls.add_method('Begin', 
                   'ns3::Buffer::Iterator', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::CopyData(std::ostream * os, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'void', 
                   [param('std::ostream *', 'os'), param('uint32_t', 'size')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::CopyData(uint8_t * buffer, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')], 
                   is_const=True)
    ## buffer.h (module 'network'): ns3::Buffer ns3::Buffer::CreateFragment(uint32_t start, uint32_t length) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::Buffer', 
                   [param('uint32_t', 'start'), param('uint32_t', 'length')], 
                   is_const=True)
    ## buffer.h (module 'network'): ns3::Buffer ns3::Buffer::CreateFullCopy() const [member function]
    cls.add_method('CreateFullCopy', 
                   'ns3::Buffer', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Deserialize(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator ns3::Buffer::End() const [member function]
    cls.add_method('End', 
                   'ns3::Buffer::Iterator', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): int32_t ns3::Buffer::GetCurrentEndOffset() const [member function]
    cls.add_method('GetCurrentEndOffset', 
                   'int32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): int32_t ns3::Buffer::GetCurrentStartOffset() const [member function]
    cls.add_method('GetCurrentStartOffset', 
                   'int32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint8_t const * ns3::Buffer::PeekData() const [member function]
    cls.add_method('PeekData', 
                   'uint8_t const *', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::RemoveAtEnd(uint32_t end) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::RemoveAtStart(uint32_t start) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3BufferIterator_methods(root_module, cls):
    ## buffer.h (module 'network'): ns3::Buffer::Iterator::Iterator(ns3::Buffer::Iterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Buffer::Iterator const &', 'arg0')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator::Iterator() [constructor]
    cls.add_constructor([])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::CalculateIpChecksum(uint16_t size) [member function]
    cls.add_method('CalculateIpChecksum', 
                   'uint16_t', 
                   [param('uint16_t', 'size')])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::CalculateIpChecksum(uint16_t size, uint32_t initialChecksum) [member function]
    cls.add_method('CalculateIpChecksum', 
                   'uint16_t', 
                   [param('uint16_t', 'size'), param('uint32_t', 'initialChecksum')])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetDistanceFrom(ns3::Buffer::Iterator const & o) const [member function]
    cls.add_method('GetDistanceFrom', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator const &', 'o')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): bool ns3::Buffer::Iterator::IsEnd() const [member function]
    cls.add_method('IsEnd', 
                   'bool', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): bool ns3::Buffer::Iterator::IsStart() const [member function]
    cls.add_method('IsStart', 
                   'bool', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Next() [member function]
    cls.add_method('Next', 
                   'void', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Next(uint32_t delta) [member function]
    cls.add_method('Next', 
                   'void', 
                   [param('uint32_t', 'delta')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Prev() [member function]
    cls.add_method('Prev', 
                   'void', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Prev(uint32_t delta) [member function]
    cls.add_method('Prev', 
                   'void', 
                   [param('uint32_t', 'delta')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Read(uint8_t * buffer, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadLsbtohU16() [member function]
    cls.add_method('ReadLsbtohU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadLsbtohU32() [member function]
    cls.add_method('ReadLsbtohU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadLsbtohU64() [member function]
    cls.add_method('ReadLsbtohU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadNtohU16() [member function]
    cls.add_method('ReadNtohU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadNtohU32() [member function]
    cls.add_method('ReadNtohU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadNtohU64() [member function]
    cls.add_method('ReadNtohU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadU16() [member function]
    cls.add_method('ReadU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadU32() [member function]
    cls.add_method('ReadU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadU64() [member function]
    cls.add_method('ReadU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint8_t ns3::Buffer::Iterator::ReadU8() [member function]
    cls.add_method('ReadU8', 
                   'uint8_t', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Write(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Write(ns3::Buffer::Iterator start, ns3::Buffer::Iterator end) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start'), param('ns3::Buffer::Iterator', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU16(uint16_t data) [member function]
    cls.add_method('WriteHtolsbU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU32(uint32_t data) [member function]
    cls.add_method('WriteHtolsbU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU64(uint64_t data) [member function]
    cls.add_method('WriteHtolsbU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU16(uint16_t data) [member function]
    cls.add_method('WriteHtonU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU32(uint32_t data) [member function]
    cls.add_method('WriteHtonU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU64(uint64_t data) [member function]
    cls.add_method('WriteHtonU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU16(uint16_t data) [member function]
    cls.add_method('WriteU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU32(uint32_t data) [member function]
    cls.add_method('WriteU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU64(uint64_t data) [member function]
    cls.add_method('WriteU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU8(uint8_t data) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU8(uint8_t data, uint32_t len) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'data'), param('uint32_t', 'len')])
    return

def register_Ns3ByteTagIterator_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::ByteTagIterator::ByteTagIterator(ns3::ByteTagIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagIterator const &', 'arg0')])
    ## packet.h (module 'network'): bool ns3::ByteTagIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item ns3::ByteTagIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::ByteTagIterator::Item', 
                   [])
    return

def register_Ns3ByteTagIteratorItem_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item::Item(ns3::ByteTagIterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagIterator::Item const &', 'arg0')])
    ## packet.h (module 'network'): uint32_t ns3::ByteTagIterator::Item::GetEnd() const [member function]
    cls.add_method('GetEnd', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::ByteTagIterator::Item::GetStart() const [member function]
    cls.add_method('GetStart', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::ByteTagIterator::Item::GetTag(ns3::Tag & tag) const [member function]
    cls.add_method('GetTag', 
                   'void', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::TypeId ns3::ByteTagIterator::Item::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    return

def register_Ns3ByteTagList_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::ByteTagList() [constructor]
    cls.add_constructor([])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::ByteTagList(ns3::ByteTagList const & o) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList const &', 'o')])
    ## byte-tag-list.h (module 'network'): ns3::TagBuffer ns3::ByteTagList::Add(ns3::TypeId tid, uint32_t bufferSize, int32_t start, int32_t end) [member function]
    cls.add_method('Add', 
                   'ns3::TagBuffer', 
                   [param('ns3::TypeId', 'tid'), param('uint32_t', 'bufferSize'), param('int32_t', 'start'), param('int32_t', 'end')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::Add(ns3::ByteTagList const & o) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::ByteTagList const &', 'o')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::AddAtEnd(int32_t adjustment, int32_t appendOffset) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('int32_t', 'adjustment'), param('int32_t', 'appendOffset')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::AddAtStart(int32_t adjustment, int32_t prependOffset) [member function]
    cls.add_method('AddAtStart', 
                   'void', 
                   [param('int32_t', 'adjustment'), param('int32_t', 'prependOffset')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator ns3::ByteTagList::Begin(int32_t offsetStart, int32_t offsetEnd) const [member function]
    cls.add_method('Begin', 
                   'ns3::ByteTagList::Iterator', 
                   [param('int32_t', 'offsetStart'), param('int32_t', 'offsetEnd')], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::RemoveAll() [member function]
    cls.add_method('RemoveAll', 
                   'void', 
                   [])
    return

def register_Ns3ByteTagListIterator_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Iterator(ns3::ByteTagList::Iterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList::Iterator const &', 'arg0')])
    ## byte-tag-list.h (module 'network'): uint32_t ns3::ByteTagList::Iterator::GetOffsetStart() const [member function]
    cls.add_method('GetOffsetStart', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): bool ns3::ByteTagList::Iterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item ns3::ByteTagList::Iterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::ByteTagList::Iterator::Item', 
                   [])
    return

def register_Ns3ByteTagListIteratorItem_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::Item(ns3::ByteTagList::Iterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList::Iterator::Item const &', 'arg0')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::Item(ns3::TagBuffer buf) [constructor]
    cls.add_constructor([param('ns3::TagBuffer', 'buf')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::buf [variable]
    cls.add_instance_attribute('buf', 'ns3::TagBuffer', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::end [variable]
    cls.add_instance_attribute('end', 'int32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::size [variable]
    cls.add_instance_attribute('size', 'uint32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::start [variable]
    cls.add_instance_attribute('start', 'int32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3CallbackBase_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase(ns3::CallbackBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackBase const &', 'arg0')])
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::Ptr<ns3::CallbackImplBase> ns3::CallbackBase::GetImpl() const [member function]
    cls.add_method('GetImpl', 
                   'ns3::Ptr< ns3::CallbackImplBase >', 
                   [], 
                   is_const=True)
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase(ns3::Ptr<ns3::CallbackImplBase> impl) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::CallbackImplBase >', 'impl')], 
                        visibility='protected')
    ## callback.h (module 'core'): static std::string ns3::CallbackBase::Demangle(std::string const & mangled) [member function]
    cls.add_method('Demangle', 
                   'std::string', 
                   [param('std::string const &', 'mangled')], 
                   is_static=True, visibility='protected')
    return

def register_Ns3DataRate_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>')
    cls.add_binary_comparison_operator('>=')
    ## data-rate.h (module 'network'): ns3::DataRate::DataRate(ns3::DataRate const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DataRate const &', 'arg0')])
    ## data-rate.h (module 'network'): ns3::DataRate::DataRate() [constructor]
    cls.add_constructor([])
    ## data-rate.h (module 'network'): ns3::DataRate::DataRate(uint64_t bps) [constructor]
    cls.add_constructor([param('uint64_t', 'bps')])
    ## data-rate.h (module 'network'): ns3::DataRate::DataRate(std::string rate) [constructor]
    cls.add_constructor([param('std::string', 'rate')])
    ## data-rate.h (module 'network'): double ns3::DataRate::CalculateTxTime(uint32_t bytes) const [member function]
    cls.add_method('CalculateTxTime', 
                   'double', 
                   [param('uint32_t', 'bytes')], 
                   is_const=True)
    ## data-rate.h (module 'network'): uint64_t ns3::DataRate::GetBitRate() const [member function]
    cls.add_method('GetBitRate', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    return

def register_Ns3EventId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('==')
    ## event-id.h (module 'core'): ns3::EventId::EventId(ns3::EventId const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventId const &', 'arg0')])
    ## event-id.h (module 'core'): ns3::EventId::EventId() [constructor]
    cls.add_constructor([])
    ## event-id.h (module 'core'): ns3::EventId::EventId(ns3::Ptr<ns3::EventImpl> const & impl, uint64_t ts, uint32_t context, uint32_t uid) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::EventImpl > const &', 'impl'), param('uint64_t', 'ts'), param('uint32_t', 'context'), param('uint32_t', 'uid')])
    ## event-id.h (module 'core'): void ns3::EventId::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-id.h (module 'core'): uint32_t ns3::EventId::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): uint64_t ns3::EventId::GetTs() const [member function]
    cls.add_method('GetTs', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): uint32_t ns3::EventId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): bool ns3::EventId::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): bool ns3::EventId::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): ns3::EventImpl * ns3::EventId::PeekEventImpl() const [member function]
    cls.add_method('PeekEventImpl', 
                   'ns3::EventImpl *', 
                   [], 
                   is_const=True)
    return

def register_Ns3Ipv4Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('<')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(ns3::Ipv4Address const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Address const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(uint32_t address) [constructor]
    cls.add_constructor([param('uint32_t', 'address')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(char const * address) [constructor]
    cls.add_constructor([param('char const *', 'address')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4Address::CombineMask(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('CombineMask', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::Deserialize(uint8_t const * buf) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Ipv4Address', 
                   [param('uint8_t const *', 'buf')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Address::Get() const [member function]
    cls.add_method('Get', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetAny() [member function]
    cls.add_method('GetAny', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetBroadcast() [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4Address::GetSubnetDirectedBroadcast(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('GetSubnetDirectedBroadcast', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsEqual(ns3::Ipv4Address const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'other')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsLocalMulticast() const [member function]
    cls.add_method('IsLocalMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static bool ns3::Ipv4Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsSubnetDirectedBroadcast(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('IsSubnetDirectedBroadcast', 
                   'bool', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Serialize(uint8_t * buf) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Set(uint32_t address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint32_t', 'address')])
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Set(char const * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('char const *', 'address')])
    return

def register_Ns3Ipv4Mask_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(ns3::Ipv4Mask const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Mask const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(uint32_t mask) [constructor]
    cls.add_constructor([param('uint32_t', 'mask')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(char const * mask) [constructor]
    cls.add_constructor([param('char const *', 'mask')])
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Mask::Get() const [member function]
    cls.add_method('Get', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Mask::GetInverse() const [member function]
    cls.add_method('GetInverse', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): uint16_t ns3::Ipv4Mask::GetPrefixLength() const [member function]
    cls.add_method('GetPrefixLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Mask::IsEqual(ns3::Ipv4Mask other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv4Mask', 'other')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Mask::IsMatch(ns3::Ipv4Address a, ns3::Ipv4Address b) const [member function]
    cls.add_method('IsMatch', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'a'), param('ns3::Ipv4Address', 'b')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Mask::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Mask::Set(uint32_t mask) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint32_t', 'mask')])
    return

def register_Ns3Ipv6Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('<')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(char const * address) [constructor]
    cls.add_constructor([param('char const *', 'address')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(uint8_t * address) [constructor]
    cls.add_constructor([param('uint8_t *', 'address')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(ns3::Ipv6Address const & addr) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Address const &', 'addr')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(ns3::Ipv6Address const * addr) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address const *', 'addr')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address ns3::Ipv6Address::CombinePrefix(ns3::Ipv6Prefix const & prefix) [member function]
    cls.add_method('CombinePrefix', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv6Prefix const &', 'prefix')])
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::Deserialize(uint8_t const * buf) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Ipv6Address', 
                   [param('uint8_t const *', 'buf')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllHostsMulticast() [member function]
    cls.add_method('GetAllHostsMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllNodesMulticast() [member function]
    cls.add_method('GetAllNodesMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllRoutersMulticast() [member function]
    cls.add_method('GetAllRoutersMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAny() [member function]
    cls.add_method('GetAny', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::GetBytes(uint8_t * buf) const [member function]
    cls.add_method('GetBytes', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv6Address::GetIpv4MappedAddress() const [member function]
    cls.add_method('GetIpv4MappedAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllHostsMulticast() const [member function]
    cls.add_method('IsAllHostsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllNodesMulticast() const [member function]
    cls.add_method('IsAllNodesMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllRoutersMulticast() const [member function]
    cls.add_method('IsAllRoutersMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAny() const [member function]
    cls.add_method('IsAny', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsEqual(ns3::Ipv6Address const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv6Address const &', 'other')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsIpv4MappedAddress() [member function]
    cls.add_method('IsIpv4MappedAddress', 
                   'bool', 
                   [])
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLinkLocal() const [member function]
    cls.add_method('IsLinkLocal', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLinkLocalMulticast() const [member function]
    cls.add_method('IsLinkLocalMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLocalhost() const [member function]
    cls.add_method('IsLocalhost', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static bool ns3::Ipv6Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsSolicitedMulticast() const [member function]
    cls.add_method('IsSolicitedMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredAddress(ns3::Mac48Address addr, ns3::Ipv6Address prefix) [member function]
    cls.add_method('MakeAutoconfiguredAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac48Address', 'addr'), param('ns3::Ipv6Address', 'prefix')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredLinkLocalAddress(ns3::Mac48Address mac) [member function]
    cls.add_method('MakeAutoconfiguredLinkLocalAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac48Address', 'mac')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeIpv4MappedAddress(ns3::Ipv4Address addr) [member function]
    cls.add_method('MakeIpv4MappedAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv4Address', 'addr')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeSolicitedAddress(ns3::Ipv6Address addr) [member function]
    cls.add_method('MakeSolicitedAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Serialize(uint8_t * buf) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Set(char const * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('char const *', 'address')])
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Set(uint8_t * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint8_t *', 'address')])
    return

def register_Ns3Ipv6Prefix_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(uint8_t * prefix) [constructor]
    cls.add_constructor([param('uint8_t *', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(char const * prefix) [constructor]
    cls.add_constructor([param('char const *', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(uint8_t prefix) [constructor]
    cls.add_constructor([param('uint8_t', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(ns3::Ipv6Prefix const & prefix) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const &', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(ns3::Ipv6Prefix const * prefix) [constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const *', 'prefix')])
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Prefix::GetBytes(uint8_t * buf) const [member function]
    cls.add_method('GetBytes', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): uint8_t ns3::Ipv6Prefix::GetPrefixLength() const [member function]
    cls.add_method('GetPrefixLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Prefix::IsEqual(ns3::Ipv6Prefix const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv6Prefix const &', 'other')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Prefix::IsMatch(ns3::Ipv6Address a, ns3::Ipv6Address b) const [member function]
    cls.add_method('IsMatch', 
                   'bool', 
                   [param('ns3::Ipv6Address', 'a'), param('ns3::Ipv6Address', 'b')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Prefix::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    return

def register_Ns3LogComponent_methods(root_module, cls):
    ## log.h (module 'core'): ns3::LogComponent::LogComponent(ns3::LogComponent const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::LogComponent const &', 'arg0')])
    ## log.h (module 'core'): ns3::LogComponent::LogComponent(char const * name) [constructor]
    cls.add_constructor([param('char const *', 'name')])
    ## log.h (module 'core'): void ns3::LogComponent::Disable(ns3::LogLevel level) [member function]
    cls.add_method('Disable', 
                   'void', 
                   [param('ns3::LogLevel', 'level')])
    ## log.h (module 'core'): void ns3::LogComponent::Enable(ns3::LogLevel level) [member function]
    cls.add_method('Enable', 
                   'void', 
                   [param('ns3::LogLevel', 'level')])
    ## log.h (module 'core'): void ns3::LogComponent::EnvVarCheck(char const * name) [member function]
    cls.add_method('EnvVarCheck', 
                   'void', 
                   [param('char const *', 'name')])
    ## log.h (module 'core'): std::string ns3::LogComponent::GetLevelLabel(ns3::LogLevel const level) const [member function]
    cls.add_method('GetLevelLabel', 
                   'std::string', 
                   [param('ns3::LogLevel const', 'level')], 
                   is_const=True)
    ## log.h (module 'core'): bool ns3::LogComponent::IsEnabled(ns3::LogLevel level) const [member function]
    cls.add_method('IsEnabled', 
                   'bool', 
                   [param('ns3::LogLevel', 'level')], 
                   is_const=True)
    ## log.h (module 'core'): bool ns3::LogComponent::IsNoneEnabled() const [member function]
    cls.add_method('IsNoneEnabled', 
                   'bool', 
                   [], 
                   is_const=True)
    ## log.h (module 'core'): char const * ns3::LogComponent::Name() const [member function]
    cls.add_method('Name', 
                   'char const *', 
                   [], 
                   is_const=True)
    return

def register_Ns3Mac48Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('<')
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address(ns3::Mac48Address const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48Address const &', 'arg0')])
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address(char const * str) [constructor]
    cls.add_constructor([param('char const *', 'str')])
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::Allocate() [member function]
    cls.add_method('Allocate', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Mac48Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): void ns3::Mac48Address::CopyFrom(uint8_t const * buffer) [member function]
    cls.add_method('CopyFrom', 
                   'void', 
                   [param('uint8_t const *', 'buffer')])
    ## mac48-address.h (module 'network'): void ns3::Mac48Address::CopyTo(uint8_t * buffer) const [member function]
    cls.add_method('CopyTo', 
                   'void', 
                   [param('uint8_t *', 'buffer')], 
                   is_const=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetBroadcast() [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast(ns3::Ipv4Address address) [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv4Address', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast(ns3::Ipv6Address address) [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv6Address', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast6Prefix() [member function]
    cls.add_method('GetMulticast6Prefix', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticastPrefix() [member function]
    cls.add_method('GetMulticastPrefix', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48Address::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48Address::IsGroup() const [member function]
    cls.add_method('IsGroup', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): static bool ns3::Mac48Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    return

def register_Ns3ObjectBase_methods(root_module, cls):
    ## object-base.h (module 'core'): ns3::ObjectBase::ObjectBase() [constructor]
    cls.add_constructor([])
    ## object-base.h (module 'core'): ns3::ObjectBase::ObjectBase(ns3::ObjectBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectBase const &', 'arg0')])
    ## object-base.h (module 'core'): void ns3::ObjectBase::GetAttribute(std::string name, ns3::AttributeValue & value) const [member function]
    cls.add_method('GetAttribute', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue &', 'value')], 
                   is_const=True)
    ## object-base.h (module 'core'): bool ns3::ObjectBase::GetAttributeFailSafe(std::string name, ns3::AttributeValue & attribute) const [member function]
    cls.add_method('GetAttributeFailSafe', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::AttributeValue &', 'attribute')], 
                   is_const=True)
    ## object-base.h (module 'core'): ns3::TypeId ns3::ObjectBase::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## object-base.h (module 'core'): static ns3::TypeId ns3::ObjectBase::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## object-base.h (module 'core'): void ns3::ObjectBase::SetAttribute(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('SetAttribute', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::SetAttributeFailSafe(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('SetAttributeFailSafe', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceConnect(std::string name, std::string context, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceConnect', 
                   'bool', 
                   [param('std::string', 'name'), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceConnectWithoutContext(std::string name, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceConnectWithoutContext', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceDisconnect(std::string name, std::string context, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceDisconnect', 
                   'bool', 
                   [param('std::string', 'name'), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceDisconnectWithoutContext(std::string name, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceDisconnectWithoutContext', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): void ns3::ObjectBase::ConstructSelf(ns3::AttributeConstructionList const & attributes) [member function]
    cls.add_method('ConstructSelf', 
                   'void', 
                   [param('ns3::AttributeConstructionList const &', 'attributes')], 
                   visibility='protected')
    ## object-base.h (module 'core'): void ns3::ObjectBase::NotifyConstructionCompleted() [member function]
    cls.add_method('NotifyConstructionCompleted', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectDeleter_methods(root_module, cls):
    ## object.h (module 'core'): ns3::ObjectDeleter::ObjectDeleter() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): ns3::ObjectDeleter::ObjectDeleter(ns3::ObjectDeleter const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectDeleter const &', 'arg0')])
    ## object.h (module 'core'): static void ns3::ObjectDeleter::Delete(ns3::Object * object) [member function]
    cls.add_method('Delete', 
                   'void', 
                   [param('ns3::Object *', 'object')], 
                   is_static=True)
    return

def register_Ns3ObjectFactory_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory(ns3::ObjectFactory const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactory const &', 'arg0')])
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory(std::string typeId) [constructor]
    cls.add_constructor([param('std::string', 'typeId')])
    ## object-factory.h (module 'core'): ns3::Ptr<ns3::Object> ns3::ObjectFactory::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::Object >', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): ns3::TypeId ns3::ObjectFactory::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::Set(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(ns3::TypeId tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('ns3::TypeId', 'tid')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(char const * tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('char const *', 'tid')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(std::string tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('std::string', 'tid')])
    return

def register_Ns3PLC_EdgeTransferData_t_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t::PLC_EdgeTransferData_t() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t::PLC_EdgeTransferData_t(ns3::PLC_EdgeTransferData_t const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_EdgeTransferData_t const &', 'arg0')])
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t::edge_transfer_unit [variable]
    cls.add_instance_attribute('edge_transfer_unit', 'ns3::Ptr< ns3::PLC_EdgeTransferUnit >', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t::etf_initialized [variable]
    cls.add_instance_attribute('etf_initialized', 'bool', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t::input_impedance [variable]
    cls.add_instance_attribute('input_impedance', 'ns3::PLC_InputImpedance', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::PLC_EdgeTransferData_t::load_impedance [variable]
    cls.add_instance_attribute('load_impedance', 'ns3::Ptr< ns3::PLC_ValueBase >', is_const=False)
    return

def register_Ns3PLC_ImpedanceIndicator_t_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::PLC_ImpedanceIndicator_t::PLC_ImpedanceIndicator_t() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::PLC_ImpedanceIndicator_t::PLC_ImpedanceIndicator_t(ns3::PLC_ImpedanceIndicator_t const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ImpedanceIndicator_t const &', 'arg0')])
    ## plc-defs.h (module 'plc'): ns3::PLC_ImpedanceIndicator_t::IsTimeVariant [variable]
    cls.add_instance_attribute('IsTimeVariant', 'bool', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::PLC_ImpedanceIndicator_t::IsUp2Date [variable]
    cls.add_instance_attribute('IsUp2Date', 'bool', is_const=False)
    return

def register_Ns3PLC_Mutex_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::PLC_Mutex::PLC_Mutex() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::PLC_Mutex::PLC_Mutex(ns3::PLC_Mutex const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Mutex const &', 'arg0')])
    ## plc-defs.h (module 'plc'): void ns3::PLC_Mutex::Lock() [member function]
    cls.add_method('Lock', 
                   'void', 
                   [])
    ## plc-defs.h (module 'plc'): void ns3::PLC_Mutex::Unlock() [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [])
    return

def register_Ns3PLC_Time_methods(root_module, cls):
    ## plc-time.h (module 'plc'): ns3::PLC_Time::PLC_Time() [constructor]
    cls.add_constructor([])
    ## plc-time.h (module 'plc'): ns3::PLC_Time::PLC_Time(ns3::PLC_Time const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Time const &', 'arg0')])
    ## plc-time.h (module 'plc'): static ns3::Time ns3::PLC_Time::GetMainsPeriod() [member function]
    cls.add_method('GetMainsPeriod', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## plc-time.h (module 'plc'): static size_t ns3::PLC_Time::GetNumTimeslots() [member function]
    cls.add_method('GetNumTimeslots', 
                   'size_t', 
                   [], 
                   is_static=True)
    ## plc-time.h (module 'plc'): static double ns3::PLC_Time::GetPeriodS() [member function]
    cls.add_method('GetPeriodS', 
                   'double', 
                   [], 
                   is_static=True)
    ## plc-time.h (module 'plc'): static double ns3::PLC_Time::GetResolutionS() [member function]
    cls.add_method('GetResolutionS', 
                   'double', 
                   [], 
                   is_static=True)
    ## plc-time.h (module 'plc'): static ns3::Timeslot ns3::PLC_Time::GetTimeslot(ns3::Time t) [member function]
    cls.add_method('GetTimeslot', 
                   'ns3::Timeslot', 
                   [param('ns3::Time', 't')], 
                   is_static=True)
    ## plc-time.h (module 'plc'): static void ns3::PLC_Time::SetTimeModel(double mainsFreq, ns3::Time tSymbol) [member function]
    cls.add_method('SetTimeModel', 
                   'void', 
                   [param('double', 'mainsFreq'), param('ns3::Time', 'tSymbol')], 
                   is_static=True)
    ## plc-time.h (module 'plc'): static void ns3::PLC_Time::SetTimeModel(double mainsFreq, size_t timeslots, ns3::Time tSymbol) [member function]
    cls.add_method('SetTimeModel', 
                   'void', 
                   [param('double', 'mainsFreq'), param('size_t', 'timeslots'), param('ns3::Time', 'tSymbol')], 
                   is_static=True)
    return

def register_Ns3PacketMetadata_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::PacketMetadata(uint64_t uid, uint32_t size) [constructor]
    cls.add_constructor([param('uint64_t', 'uid'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::PacketMetadata(ns3::PacketMetadata const & o) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata const &', 'o')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddAtEnd(ns3::PacketMetadata const & o) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::PacketMetadata const &', 'o')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddHeader(ns3::Header const & header, uint32_t size) [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddPaddingAtEnd(uint32_t end) [member function]
    cls.add_method('AddPaddingAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddTrailer(ns3::Trailer const & trailer, uint32_t size) [member function]
    cls.add_method('AddTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator ns3::PacketMetadata::BeginItem(ns3::Buffer buffer) const [member function]
    cls.add_method('BeginItem', 
                   'ns3::PacketMetadata::ItemIterator', 
                   [param('ns3::Buffer', 'buffer')], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata ns3::PacketMetadata::CreateFragment(uint32_t start, uint32_t end) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::PacketMetadata', 
                   [param('uint32_t', 'start'), param('uint32_t', 'end')], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::Deserialize(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): static void ns3::PacketMetadata::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet-metadata.h (module 'network'): static void ns3::PacketMetadata::EnableChecking() [member function]
    cls.add_method('EnableChecking', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): uint64_t ns3::PacketMetadata::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveAtEnd(uint32_t end) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveAtStart(uint32_t start) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveHeader(ns3::Header const & header, uint32_t size) [member function]
    cls.add_method('RemoveHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveTrailer(ns3::Trailer const & trailer, uint32_t size) [member function]
    cls.add_method('RemoveTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3PacketMetadataItem_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::Item() [constructor]
    cls.add_constructor([])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::Item(ns3::PacketMetadata::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata::Item const &', 'arg0')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::current [variable]
    cls.add_instance_attribute('current', 'ns3::Buffer::Iterator', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentSize [variable]
    cls.add_instance_attribute('currentSize', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentTrimedFromEnd [variable]
    cls.add_instance_attribute('currentTrimedFromEnd', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentTrimedFromStart [variable]
    cls.add_instance_attribute('currentTrimedFromStart', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::isFragment [variable]
    cls.add_instance_attribute('isFragment', 'bool', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3PacketMetadataItemIterator_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator::ItemIterator(ns3::PacketMetadata::ItemIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata::ItemIterator const &', 'arg0')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator::ItemIterator(ns3::PacketMetadata const * metadata, ns3::Buffer buffer) [constructor]
    cls.add_constructor([param('ns3::PacketMetadata const *', 'metadata'), param('ns3::Buffer', 'buffer')])
    ## packet-metadata.h (module 'network'): bool ns3::PacketMetadata::ItemIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item ns3::PacketMetadata::ItemIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::PacketMetadata::Item', 
                   [])
    return

def register_Ns3PacketTagIterator_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::PacketTagIterator::PacketTagIterator(ns3::PacketTagIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagIterator const &', 'arg0')])
    ## packet.h (module 'network'): bool ns3::PacketTagIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item ns3::PacketTagIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::PacketTagIterator::Item', 
                   [])
    return

def register_Ns3PacketTagIteratorItem_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item::Item(ns3::PacketTagIterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagIterator::Item const &', 'arg0')])
    ## packet.h (module 'network'): void ns3::PacketTagIterator::Item::GetTag(ns3::Tag & tag) const [member function]
    cls.add_method('GetTag', 
                   'void', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::TypeId ns3::PacketTagIterator::Item::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    return

def register_Ns3PacketTagList_methods(root_module, cls):
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::PacketTagList() [constructor]
    cls.add_constructor([])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::PacketTagList(ns3::PacketTagList const & o) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagList const &', 'o')])
    ## packet-tag-list.h (module 'network'): void ns3::PacketTagList::Add(ns3::Tag const & tag) const [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData const * ns3::PacketTagList::Head() const [member function]
    cls.add_method('Head', 
                   'ns3::PacketTagList::TagData const *', 
                   [], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Peek(ns3::Tag & tag) const [member function]
    cls.add_method('Peek', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Remove(ns3::Tag & tag) [member function]
    cls.add_method('Remove', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet-tag-list.h (module 'network'): void ns3::PacketTagList::RemoveAll() [member function]
    cls.add_method('RemoveAll', 
                   'void', 
                   [])
    return

def register_Ns3PacketTagListTagData_methods(root_module, cls):
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData() [constructor]
    cls.add_constructor([])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData(ns3::PacketTagList::TagData const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagList::TagData const &', 'arg0')])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::count [variable]
    cls.add_instance_attribute('count', 'uint32_t', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::data [variable]
    cls.add_instance_attribute('data', 'uint8_t [ 20 ]', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::next [variable]
    cls.add_instance_attribute('next', 'ns3::PacketTagList::TagData *', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3RandomVariable_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## random-variable.h (module 'core'): ns3::RandomVariable::RandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::RandomVariable::RandomVariable(ns3::RandomVariable const & o) [copy constructor]
    cls.add_constructor([param('ns3::RandomVariable const &', 'o')])
    ## random-variable.h (module 'core'): uint32_t ns3::RandomVariable::GetInteger() const [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::RandomVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    return

def register_Ns3RngSeedManager_methods(root_module, cls):
    ## rng-seed-manager.h (module 'core'): ns3::RngSeedManager::RngSeedManager() [constructor]
    cls.add_constructor([])
    ## rng-seed-manager.h (module 'core'): ns3::RngSeedManager::RngSeedManager(ns3::RngSeedManager const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RngSeedManager const &', 'arg0')])
    ## rng-seed-manager.h (module 'core'): static uint64_t ns3::RngSeedManager::GetNextStreamIndex() [member function]
    cls.add_method('GetNextStreamIndex', 
                   'uint64_t', 
                   [], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static uint64_t ns3::RngSeedManager::GetRun() [member function]
    cls.add_method('GetRun', 
                   'uint64_t', 
                   [], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static uint32_t ns3::RngSeedManager::GetSeed() [member function]
    cls.add_method('GetSeed', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static void ns3::RngSeedManager::SetRun(uint64_t run) [member function]
    cls.add_method('SetRun', 
                   'void', 
                   [param('uint64_t', 'run')], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static void ns3::RngSeedManager::SetSeed(uint32_t seed) [member function]
    cls.add_method('SetSeed', 
                   'void', 
                   [param('uint32_t', 'seed')], 
                   is_static=True)
    return

def register_Ns3SequentialVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::SequentialVariable::SequentialVariable(ns3::SequentialVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SequentialVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::SequentialVariable::SequentialVariable(double f, double l, double i=1, uint32_t c=1) [constructor]
    cls.add_constructor([param('double', 'f'), param('double', 'l'), param('double', 'i', default_value='1'), param('uint32_t', 'c', default_value='1')])
    ## random-variable.h (module 'core'): ns3::SequentialVariable::SequentialVariable(double f, double l, ns3::RandomVariable const & i, uint32_t c=1) [constructor]
    cls.add_constructor([param('double', 'f'), param('double', 'l'), param('ns3::RandomVariable const &', 'i'), param('uint32_t', 'c', default_value='1')])
    return

def register_Ns3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::SimpleRefCount(ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3Tag_methods(root_module, cls):
    ## tag.h (module 'network'): ns3::Tag::Tag() [constructor]
    cls.add_constructor([])
    ## tag.h (module 'network'): ns3::Tag::Tag(ns3::Tag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Tag const &', 'arg0')])
    ## tag.h (module 'network'): void ns3::Tag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_pure_virtual=True, is_virtual=True)
    ## tag.h (module 'network'): uint32_t ns3::Tag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## tag.h (module 'network'): static ns3::TypeId ns3::Tag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## tag.h (module 'network'): void ns3::Tag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## tag.h (module 'network'): void ns3::Tag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3TagBuffer_methods(root_module, cls):
    ## tag-buffer.h (module 'network'): ns3::TagBuffer::TagBuffer(ns3::TagBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TagBuffer const &', 'arg0')])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer::TagBuffer(uint8_t * start, uint8_t * end) [constructor]
    cls.add_constructor([param('uint8_t *', 'start'), param('uint8_t *', 'end')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::CopyFrom(ns3::TagBuffer o) [member function]
    cls.add_method('CopyFrom', 
                   'void', 
                   [param('ns3::TagBuffer', 'o')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::Read(uint8_t * buffer, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')])
    ## tag-buffer.h (module 'network'): double ns3::TagBuffer::ReadDouble() [member function]
    cls.add_method('ReadDouble', 
                   'double', 
                   [])
    ## tag-buffer.h (module 'network'): uint16_t ns3::TagBuffer::ReadU16() [member function]
    cls.add_method('ReadU16', 
                   'uint16_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint32_t ns3::TagBuffer::ReadU32() [member function]
    cls.add_method('ReadU32', 
                   'uint32_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint64_t ns3::TagBuffer::ReadU64() [member function]
    cls.add_method('ReadU64', 
                   'uint64_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint8_t ns3::TagBuffer::ReadU8() [member function]
    cls.add_method('ReadU8', 
                   'uint8_t', 
                   [])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::TrimAtEnd(uint32_t trim) [member function]
    cls.add_method('TrimAtEnd', 
                   'void', 
                   [param('uint32_t', 'trim')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::Write(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteDouble(double v) [member function]
    cls.add_method('WriteDouble', 
                   'void', 
                   [param('double', 'v')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU16(uint16_t data) [member function]
    cls.add_method('WriteU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU32(uint32_t data) [member function]
    cls.add_method('WriteU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU64(uint64_t v) [member function]
    cls.add_method('WriteU64', 
                   'void', 
                   [param('uint64_t', 'v')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU8(uint8_t v) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'v')])
    return

def register_Ns3TriangularVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::TriangularVariable::TriangularVariable(ns3::TriangularVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TriangularVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::TriangularVariable::TriangularVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::TriangularVariable::TriangularVariable(double s, double l, double mean) [constructor]
    cls.add_constructor([param('double', 's'), param('double', 'l'), param('double', 'mean')])
    return

def register_Ns3TypeId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('<')
    ## type-id.h (module 'core'): ns3::TypeId::TypeId(char const * name) [constructor]
    cls.add_constructor([param('char const *', 'name')])
    ## type-id.h (module 'core'): ns3::TypeId::TypeId() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::TypeId(ns3::TypeId const & o) [copy constructor]
    cls.add_constructor([param('ns3::TypeId const &', 'o')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddAttribute(std::string name, std::string help, ns3::AttributeValue const & initialValue, ns3::Ptr<ns3::AttributeAccessor const> accessor, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('AddAttribute', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::AttributeValue const &', 'initialValue'), param('ns3::Ptr< ns3::AttributeAccessor const >', 'accessor'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddAttribute(std::string name, std::string help, uint32_t flags, ns3::AttributeValue const & initialValue, ns3::Ptr<ns3::AttributeAccessor const> accessor, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('AddAttribute', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('uint32_t', 'flags'), param('ns3::AttributeValue const &', 'initialValue'), param('ns3::Ptr< ns3::AttributeAccessor const >', 'accessor'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddTraceSource(std::string name, std::string help, ns3::Ptr<ns3::TraceSourceAccessor const> accessor) [member function]
    cls.add_method('AddTraceSource', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::Ptr< ns3::TraceSourceAccessor const >', 'accessor')])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation ns3::TypeId::GetAttribute(uint32_t i) const [member function]
    cls.add_method('GetAttribute', 
                   'ns3::TypeId::AttributeInformation', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetAttributeFullName(uint32_t i) const [member function]
    cls.add_method('GetAttributeFullName', 
                   'std::string', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetAttributeN() const [member function]
    cls.add_method('GetAttributeN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::Callback<ns3::ObjectBase*,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ns3::TypeId::GetConstructor() const [member function]
    cls.add_method('GetConstructor', 
                   'ns3::Callback< ns3::ObjectBase *, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetGroupName() const [member function]
    cls.add_method('GetGroupName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetName() const [member function]
    cls.add_method('GetName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::GetParent() const [member function]
    cls.add_method('GetParent', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::GetRegistered(uint32_t i) [member function]
    cls.add_method('GetRegistered', 
                   'ns3::TypeId', 
                   [param('uint32_t', 'i')], 
                   is_static=True)
    ## type-id.h (module 'core'): static uint32_t ns3::TypeId::GetRegisteredN() [member function]
    cls.add_method('GetRegisteredN', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation ns3::TypeId::GetTraceSource(uint32_t i) const [member function]
    cls.add_method('GetTraceSource', 
                   'ns3::TypeId::TraceSourceInformation', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetTraceSourceN() const [member function]
    cls.add_method('GetTraceSourceN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): uint16_t ns3::TypeId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::HasConstructor() const [member function]
    cls.add_method('HasConstructor', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::HasParent() const [member function]
    cls.add_method('HasParent', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::HideFromDocumentation() [member function]
    cls.add_method('HideFromDocumentation', 
                   'ns3::TypeId', 
                   [])
    ## type-id.h (module 'core'): bool ns3::TypeId::IsChildOf(ns3::TypeId other) const [member function]
    cls.add_method('IsChildOf', 
                   'bool', 
                   [param('ns3::TypeId', 'other')], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::LookupAttributeByName(std::string name, ns3::TypeId::AttributeInformation * info) const [member function]
    cls.add_method('LookupAttributeByName', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::TypeId::AttributeInformation *', 'info', transfer_ownership=False)], 
                   is_const=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::LookupByName(std::string name) [member function]
    cls.add_method('LookupByName', 
                   'ns3::TypeId', 
                   [param('std::string', 'name')], 
                   is_static=True)
    ## type-id.h (module 'core'): ns3::Ptr<ns3::TraceSourceAccessor const> ns3::TypeId::LookupTraceSourceByName(std::string name) const [member function]
    cls.add_method('LookupTraceSourceByName', 
                   'ns3::Ptr< ns3::TraceSourceAccessor const >', 
                   [param('std::string', 'name')], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::MustHideFromDocumentation() const [member function]
    cls.add_method('MustHideFromDocumentation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::SetAttributeInitialValue(uint32_t i, ns3::Ptr<ns3::AttributeValue const> initialValue) [member function]
    cls.add_method('SetAttributeInitialValue', 
                   'bool', 
                   [param('uint32_t', 'i'), param('ns3::Ptr< ns3::AttributeValue const >', 'initialValue')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetGroupName(std::string groupName) [member function]
    cls.add_method('SetGroupName', 
                   'ns3::TypeId', 
                   [param('std::string', 'groupName')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetParent(ns3::TypeId tid) [member function]
    cls.add_method('SetParent', 
                   'ns3::TypeId', 
                   [param('ns3::TypeId', 'tid')])
    ## type-id.h (module 'core'): void ns3::TypeId::SetUid(uint16_t tid) [member function]
    cls.add_method('SetUid', 
                   'void', 
                   [param('uint16_t', 'tid')])
    return

def register_Ns3TypeIdAttributeInformation_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::AttributeInformation() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::AttributeInformation(ns3::TypeId::AttributeInformation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeId::AttributeInformation const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::accessor [variable]
    cls.add_instance_attribute('accessor', 'ns3::Ptr< ns3::AttributeAccessor const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::checker [variable]
    cls.add_instance_attribute('checker', 'ns3::Ptr< ns3::AttributeChecker const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::flags [variable]
    cls.add_instance_attribute('flags', 'uint32_t', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::help [variable]
    cls.add_instance_attribute('help', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::initialValue [variable]
    cls.add_instance_attribute('initialValue', 'ns3::Ptr< ns3::AttributeValue const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::originalInitialValue [variable]
    cls.add_instance_attribute('originalInitialValue', 'ns3::Ptr< ns3::AttributeValue const >', is_const=False)
    return

def register_Ns3TypeIdTraceSourceInformation_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::TraceSourceInformation() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::TraceSourceInformation(ns3::TypeId::TraceSourceInformation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeId::TraceSourceInformation const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::accessor [variable]
    cls.add_instance_attribute('accessor', 'ns3::Ptr< ns3::TraceSourceAccessor const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::help [variable]
    cls.add_instance_attribute('help', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    return

def register_Ns3UniformVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::UniformVariable::UniformVariable(ns3::UniformVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::UniformVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::UniformVariable::UniformVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::UniformVariable::UniformVariable(double s, double l) [constructor]
    cls.add_constructor([param('double', 's'), param('double', 'l')])
    ## random-variable.h (module 'core'): uint32_t ns3::UniformVariable::GetInteger(uint32_t s, uint32_t l) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 's'), param('uint32_t', 'l')])
    ## random-variable.h (module 'core'): double ns3::UniformVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::UniformVariable::GetValue(double s, double l) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 's'), param('double', 'l')])
    return

def register_Ns3Vector2D_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## vector.h (module 'core'): ns3::Vector2D::Vector2D(ns3::Vector2D const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector2D const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector2D::Vector2D(double _x, double _y) [constructor]
    cls.add_constructor([param('double', '_x'), param('double', '_y')])
    ## vector.h (module 'core'): ns3::Vector2D::Vector2D() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector2D::x [variable]
    cls.add_instance_attribute('x', 'double', is_const=False)
    ## vector.h (module 'core'): ns3::Vector2D::y [variable]
    cls.add_instance_attribute('y', 'double', is_const=False)
    return

def register_Ns3Vector3D_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## vector.h (module 'core'): ns3::Vector3D::Vector3D(ns3::Vector3D const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector3D const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector3D::Vector3D(double _x, double _y, double _z) [constructor]
    cls.add_constructor([param('double', '_x'), param('double', '_y'), param('double', '_z')])
    ## vector.h (module 'core'): ns3::Vector3D::Vector3D() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector3D::x [variable]
    cls.add_instance_attribute('x', 'double', is_const=False)
    ## vector.h (module 'core'): ns3::Vector3D::y [variable]
    cls.add_instance_attribute('y', 'double', is_const=False)
    ## vector.h (module 'core'): ns3::Vector3D::z [variable]
    cls.add_instance_attribute('z', 'double', is_const=False)
    return

def register_Ns3WeibullVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(ns3::WeibullVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WeibullVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(double m) [constructor]
    cls.add_constructor([param('double', 'm')])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(double m, double s) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's')])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(double m, double s, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's'), param('double', 'b')])
    return

def register_Ns3ZetaVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ZetaVariable::ZetaVariable(ns3::ZetaVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ZetaVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ZetaVariable::ZetaVariable(double alpha) [constructor]
    cls.add_constructor([param('double', 'alpha')])
    ## random-variable.h (module 'core'): ns3::ZetaVariable::ZetaVariable() [constructor]
    cls.add_constructor([])
    return

def register_Ns3ZipfVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ZipfVariable::ZipfVariable(ns3::ZipfVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ZipfVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ZipfVariable::ZipfVariable(long int N, double alpha) [constructor]
    cls.add_constructor([param('long int', 'N'), param('double', 'alpha')])
    ## random-variable.h (module 'core'): ns3::ZipfVariable::ZipfVariable() [constructor]
    cls.add_constructor([])
    return

def register_Ns3Backbone_branch_discover_thread_arg_t_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::backbone_branch_discover_thread_arg_t::backbone_branch_discover_thread_arg_t() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::backbone_branch_discover_thread_arg_t::backbone_branch_discover_thread_arg_t(ns3::backbone_branch_discover_thread_arg_t const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::backbone_branch_discover_thread_arg_t const &', 'arg0')])
    ## plc-defs.h (module 'plc'): ns3::backbone_branch_discover_thread_arg_t::bb [variable]
    cls.add_instance_attribute('bb', 'ns3::PLC_BackboneBranch *', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::backbone_branch_discover_thread_arg_t::graph_copy [variable]
    cls.add_instance_attribute('graph_copy', 'boost::UGraph *', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::backbone_branch_discover_thread_arg_t::graph_copy_mutex [variable]
    cls.add_instance_attribute('graph_copy_mutex', 'ns3::PLC_Mutex *', is_const=False)
    return

def register_Ns3Boostgraph_copy_t_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::boostgraph_copy_t::boostgraph_copy_t() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::boostgraph_copy_t::boostgraph_copy_t(ns3::boostgraph_copy_t const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::boostgraph_copy_t const &', 'arg0')])
    ## plc-defs.h (module 'plc'): ns3::boostgraph_copy_t::graph [variable]
    cls.add_instance_attribute('graph', 'boost::UGraph', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::boostgraph_copy_t::graph_mutex [variable]
    cls.add_instance_attribute('graph_mutex', 'ns3::PLC_Mutex', is_const=False)
    return

def register_Ns3Empty_methods(root_module, cls):
    ## empty.h (module 'core'): ns3::empty::empty() [constructor]
    cls.add_constructor([])
    ## empty.h (module 'core'): ns3::empty::empty(ns3::empty const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::empty const &', 'arg0')])
    return

def register_Ns3Int64x64_t_methods(root_module, cls):
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('*=', param('ns3::int64x64_t const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::int64x64_t const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::int64x64_t const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::int64x64_t const &', 'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t() [constructor]
    cls.add_constructor([])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long int v) [constructor]
    cls.add_constructor([param('long int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long long int v) [constructor]
    cls.add_constructor([param('long long int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(unsigned int v) [constructor]
    cls.add_constructor([param('unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long unsigned int v) [constructor]
    cls.add_constructor([param('long unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long long unsigned int v) [constructor]
    cls.add_constructor([param('long long unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(int64_t hi, uint64_t lo) [constructor]
    cls.add_constructor([param('int64_t', 'hi'), param('uint64_t', 'lo')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(ns3::int64x64_t const & o) [copy constructor]
    cls.add_constructor([param('ns3::int64x64_t const &', 'o')])
    ## int64x64-double.h (module 'core'): double ns3::int64x64_t::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): int64_t ns3::int64x64_t::GetHigh() const [member function]
    cls.add_method('GetHigh', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): uint64_t ns3::int64x64_t::GetLow() const [member function]
    cls.add_method('GetLow', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): static ns3::int64x64_t ns3::int64x64_t::Invert(uint64_t v) [member function]
    cls.add_method('Invert', 
                   'ns3::int64x64_t', 
                   [param('uint64_t', 'v')], 
                   is_static=True)
    ## int64x64-double.h (module 'core'): void ns3::int64x64_t::MulByInvert(ns3::int64x64_t const & o) [member function]
    cls.add_method('MulByInvert', 
                   'void', 
                   [param('ns3::int64x64_t const &', 'o')])
    return

def register_Ns3Sub_thread_arg_t_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::sub_thread_arg_t::sub_thread_arg_t() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::sub_thread_arg_t::sub_thread_arg_t(ns3::sub_thread_arg_t const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::sub_thread_arg_t const &', 'arg0')])
    ## plc-defs.h (module 'plc'): ns3::sub_thread_arg_t::bb [variable]
    cls.add_instance_attribute('bb', 'ns3::PLC_BackboneBranch *', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::sub_thread_arg_t::graph_copy [variable]
    cls.add_instance_attribute('graph_copy', 'ns3::boostgraph_copy *', is_const=False)
    return

def register_Ns3Thread_arg_t_methods(root_module, cls):
    ## plc-defs.h (module 'plc'): ns3::thread_arg_t::thread_arg_t() [constructor]
    cls.add_constructor([])
    ## plc-defs.h (module 'plc'): ns3::thread_arg_t::thread_arg_t(ns3::thread_arg_t const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::thread_arg_t const &', 'arg0')])
    ## plc-defs.h (module 'plc'): ns3::thread_arg_t::graph_copy [variable]
    cls.add_instance_attribute('graph_copy', 'ns3::boostgraph_copy *', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::thread_arg_t::rxInterface [variable]
    cls.add_instance_attribute('rxInterface', 'ns3::PLC_RxInterface *', is_const=False)
    ## plc-defs.h (module 'plc'): ns3::thread_arg_t::txInterface [variable]
    cls.add_instance_attribute('txInterface', 'ns3::PLC_TxInterface *', is_const=False)
    return

def register_Ns3Chunk_methods(root_module, cls):
    ## chunk.h (module 'network'): ns3::Chunk::Chunk() [constructor]
    cls.add_constructor([])
    ## chunk.h (module 'network'): ns3::Chunk::Chunk(ns3::Chunk const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Chunk const &', 'arg0')])
    ## chunk.h (module 'network'): uint32_t ns3::Chunk::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_virtual=True)
    ## chunk.h (module 'network'): static ns3::TypeId ns3::Chunk::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## chunk.h (module 'network'): void ns3::Chunk::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3ConstantVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ConstantVariable::ConstantVariable(ns3::ConstantVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ConstantVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ConstantVariable::ConstantVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ConstantVariable::ConstantVariable(double c) [constructor]
    cls.add_constructor([param('double', 'c')])
    ## random-variable.h (module 'core'): void ns3::ConstantVariable::SetConstant(double c) [member function]
    cls.add_method('SetConstant', 
                   'void', 
                   [param('double', 'c')])
    return

def register_Ns3DeterministicVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::DeterministicVariable::DeterministicVariable(ns3::DeterministicVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DeterministicVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::DeterministicVariable::DeterministicVariable(double * d, uint32_t c) [constructor]
    cls.add_constructor([param('double *', 'd'), param('uint32_t', 'c')])
    return

def register_Ns3EmpiricalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::EmpiricalVariable::EmpiricalVariable(ns3::EmpiricalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmpiricalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::EmpiricalVariable::EmpiricalVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): void ns3::EmpiricalVariable::CDF(double v, double c) [member function]
    cls.add_method('CDF', 
                   'void', 
                   [param('double', 'v'), param('double', 'c')])
    return

def register_Ns3ErlangVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ErlangVariable::ErlangVariable(ns3::ErlangVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ErlangVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ErlangVariable::ErlangVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ErlangVariable::ErlangVariable(unsigned int k, double lambda) [constructor]
    cls.add_constructor([param('unsigned int', 'k'), param('double', 'lambda')])
    ## random-variable.h (module 'core'): double ns3::ErlangVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::ErlangVariable::GetValue(unsigned int k, double lambda) const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('unsigned int', 'k'), param('double', 'lambda')], 
                   is_const=True)
    return

def register_Ns3ExponentialVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable(ns3::ExponentialVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ExponentialVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable(double m) [constructor]
    cls.add_constructor([param('double', 'm')])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable(double m, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 'b')])
    return

def register_Ns3GammaVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::GammaVariable::GammaVariable(ns3::GammaVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::GammaVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::GammaVariable::GammaVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::GammaVariable::GammaVariable(double alpha, double beta) [constructor]
    cls.add_constructor([param('double', 'alpha'), param('double', 'beta')])
    ## random-variable.h (module 'core'): double ns3::GammaVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::GammaVariable::GetValue(double alpha, double beta) const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'alpha'), param('double', 'beta')], 
                   is_const=True)
    return

def register_Ns3Header_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## header.h (module 'network'): ns3::Header::Header() [constructor]
    cls.add_constructor([])
    ## header.h (module 'network'): ns3::Header::Header(ns3::Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Header const &', 'arg0')])
    ## header.h (module 'network'): uint32_t ns3::Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_virtual=True)
    ## header.h (module 'network'): uint32_t ns3::Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## header.h (module 'network'): static ns3::TypeId ns3::Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## header.h (module 'network'): void ns3::Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## header.h (module 'network'): void ns3::Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3IntEmpiricalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::IntEmpiricalVariable::IntEmpiricalVariable(ns3::IntEmpiricalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntEmpiricalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::IntEmpiricalVariable::IntEmpiricalVariable() [constructor]
    cls.add_constructor([])
    return

def register_Ns3LogNormalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::LogNormalVariable::LogNormalVariable(ns3::LogNormalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::LogNormalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::LogNormalVariable::LogNormalVariable(double mu, double sigma) [constructor]
    cls.add_constructor([param('double', 'mu'), param('double', 'sigma')])
    return

def register_Ns3NormalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable(ns3::NormalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NormalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable(double m, double v) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 'v')])
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable(double m, double v, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 'v'), param('double', 'b')])
    return

def register_Ns3Object_methods(root_module, cls):
    ## object.h (module 'core'): ns3::Object::Object() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): void ns3::Object::AggregateObject(ns3::Ptr<ns3::Object> other) [member function]
    cls.add_method('AggregateObject', 
                   'void', 
                   [param('ns3::Ptr< ns3::Object >', 'other')])
    ## object.h (module 'core'): void ns3::Object::Dispose() [member function]
    cls.add_method('Dispose', 
                   'void', 
                   [])
    ## object.h (module 'core'): ns3::Object::AggregateIterator ns3::Object::GetAggregateIterator() const [member function]
    cls.add_method('GetAggregateIterator', 
                   'ns3::Object::AggregateIterator', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::TypeId ns3::Object::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## object.h (module 'core'): static ns3::TypeId ns3::Object::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## object.h (module 'core'): void ns3::Object::Start() [member function]
    cls.add_method('Start', 
                   'void', 
                   [])
    ## object.h (module 'core'): ns3::Object::Object(ns3::Object const & o) [copy constructor]
    cls.add_constructor([param('ns3::Object const &', 'o')], 
                        visibility='protected')
    ## object.h (module 'core'): void ns3::Object::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## object.h (module 'core'): void ns3::Object::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## object.h (module 'core'): void ns3::Object::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectAggregateIterator_methods(root_module, cls):
    ## object.h (module 'core'): ns3::Object::AggregateIterator::AggregateIterator(ns3::Object::AggregateIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Object::AggregateIterator const &', 'arg0')])
    ## object.h (module 'core'): ns3::Object::AggregateIterator::AggregateIterator() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): bool ns3::Object::AggregateIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::Ptr<ns3::Object const> ns3::Object::AggregateIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::Ptr< ns3::Object const >', 
                   [])
    return

def register_Ns3PLC_BackboneBranch_methods(root_module, cls):
    ## plc-backbone.h (module 'plc'): ns3::PLC_BackboneBranch::PLC_BackboneBranch(ns3::PLC_BackboneBranch const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_BackboneBranch const &', 'arg0')])
    ## plc-backbone.h (module 'plc'): ns3::PLC_BackboneBranch::PLC_BackboneBranch(ns3::Ptr<ns3::PLC_Node> node, ns3::Ptr<ns3::PLC_Node> before, ns3::Ptr<ns3::PLC_Node> next, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'node'), param('ns3::Ptr< ns3::PLC_Node >', 'before'), param('ns3::Ptr< ns3::PLC_Node >', 'next'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::AddInterfacePair(ns3::PLC_TxInterface * txInterface, ns3::PLC_RxInterface * rxInterface) [member function]
    cls.add_method('AddInterfacePair', 
                   'void', 
                   [param('ns3::PLC_TxInterface *', 'txInterface'), param('ns3::PLC_RxInterface *', 'rxInterface')])
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::CalculateEquivalentBridgeTapImpedance() [member function]
    cls.add_method('CalculateEquivalentBridgeTapImpedance', 
                   'void', 
                   [])
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::DiscoverOutlets(boost::UGraph & graph_copy, ns3::PLC_Mutex * graph_copy_mutex) [member function]
    cls.add_method('DiscoverOutlets', 
                   'void', 
                   [param('boost::UGraph &', 'graph_copy'), param('ns3::PLC_Mutex *', 'graph_copy_mutex')])
    ## plc-backbone.h (module 'plc'): ns3::PLC_Node * ns3::PLC_BackboneBranch::GetBeforeNodePeekPtr() [member function]
    cls.add_method('GetBeforeNodePeekPtr', 
                   'ns3::PLC_Node *', 
                   [])
    ## plc-backbone.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_BackboneBranch::GetBeforeNodePtr() [member function]
    cls.add_method('GetBeforeNodePtr', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-backbone.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_BackboneBranch::GetEquivalentBridgeTapImpedance() const [member function]
    cls.add_method('GetEquivalentBridgeTapImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [], 
                   is_const=True)
    ## plc-backbone.h (module 'plc'): std::pair<unsigned int, std::pair<unsigned int, unsigned int> > ns3::PLC_BackboneBranch::GetKey() [member function]
    cls.add_method('GetKey', 
                   'std::pair< unsigned int, std::pair< unsigned int, unsigned int > >', 
                   [])
    ## plc-backbone.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_BackboneBranch::GetNextNodePtr() [member function]
    cls.add_method('GetNextNodePtr', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-backbone.h (module 'plc'): ns3::PLC_Node * ns3::PLC_BackboneBranch::GetNodePeekPtr() [member function]
    cls.add_method('GetNodePeekPtr', 
                   'ns3::PLC_Node *', 
                   [])
    ## plc-backbone.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_BackboneBranch::GetNodePtr() [member function]
    cls.add_method('GetNodePtr', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-backbone.h (module 'plc'): static ns3::TypeId ns3::PLC_BackboneBranch::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-backbone.h (module 'plc'): bool ns3::PLC_BackboneBranch::IsTimeVariant() const [member function]
    cls.add_method('IsTimeVariant', 
                   'bool', 
                   [], 
                   is_const=True)
    ## plc-backbone.h (module 'plc'): bool ns3::PLC_BackboneBranch::IsUp2Date() const [member function]
    cls.add_method('IsUp2Date', 
                   'bool', 
                   [], 
                   is_const=True)
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::Lock() [member function]
    cls.add_method('Lock', 
                   'void', 
                   [])
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::SetTimeVariant() [member function]
    cls.add_method('SetTimeVariant', 
                   'void', 
                   [])
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::Unlock() [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [])
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-backbone.h (module 'plc'): void ns3::PLC_BackboneBranch::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_Cable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_Cable::PLC_Cable(ns3::PLC_Cable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Cable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_Cable::PLC_Cable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_Cable::PLC_Cable(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): ns3::PLC_Cable::PLC_Cable(ns3::PLC_FreqSelectiveResistance const & R, ns3::PLC_FreqSelectiveConductance const & G, ns3::PLC_FreqSelectiveInductance const & L, ns3::PLC_FreqSelectiveCapacitance const & C, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::PLC_FreqSelectiveResistance const &', 'R'), param('ns3::PLC_FreqSelectiveConductance const &', 'G'), param('ns3::PLC_FreqSelectiveInductance const &', 'L'), param('ns3::PLC_FreqSelectiveCapacitance const &', 'C'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-cable.h (module 'plc'): ns3::Ptr<const ns3::PLC_FreqSelectiveValue> ns3::PLC_Cable::GetCharImp() const [member function]
    cls.add_method('GetCharImp', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue const >', 
                   [], 
                   is_const=True)
    ## plc-cable.h (module 'plc'): ns3::PLC_FreqSelectiveResistance * ns3::PLC_Cable::GetDistConRef() [member function]
    cls.add_method('GetDistConRef', 
                   'ns3::PLC_FreqSelectiveResistance *', 
                   [])
    ## plc-cable.h (module 'plc'): ns3::PLC_FreqSelectiveResistance * ns3::PLC_Cable::GetDistResRef() [member function]
    cls.add_method('GetDistResRef', 
                   'ns3::PLC_FreqSelectiveResistance *', 
                   [])
    ## plc-cable.h (module 'plc'): double ns3::PLC_Cable::GetPropSpeedApprox() [member function]
    cls.add_method('GetPropSpeedApprox', 
                   'double', 
                   [])
    ## plc-cable.h (module 'plc'): ns3::Ptr<ns3::SpectrumModel const> ns3::PLC_Cable::GetSpectrumModel() [member function]
    cls.add_method('GetSpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [])
    ## plc-cable.h (module 'plc'): ns3::Ptr<ns3::SpectrumModel const> ns3::PLC_Cable::GetSpectrumModel() const [member function]
    cls.add_method('GetSpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [], 
                   is_const=True)
    ## plc-cable.h (module 'plc'): ns3::Ptr<const ns3::PLC_FreqSelectiveValue> ns3::PLC_Cable::GetTransConst() const [member function]
    cls.add_method('GetTransConst', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue const >', 
                   [], 
                   is_const=True)
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_Cable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::Lock() [member function]
    cls.add_method('Lock', 
                   'void', 
                   [])
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::SetSpectrumModel(ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('SetSpectrumModel', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::Unlock() [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [])
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::CalcCharImp() [member function]
    cls.add_method('CalcCharImp', 
                   'void', 
                   [], 
                   visibility='protected')
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::CalcTransConst() [member function]
    cls.add_method('CalcTransConst', 
                   'void', 
                   [], 
                   visibility='protected')
    ## plc-cable.h (module 'plc'): void ns3::PLC_Cable::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_ChannelHelper_methods(root_module, cls):
    ## plc-helper.h (module 'plc'): ns3::PLC_ChannelHelper::PLC_ChannelHelper(ns3::PLC_ChannelHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ChannelHelper const &', 'arg0')])
    ## plc-helper.h (module 'plc'): ns3::PLC_ChannelHelper::PLC_ChannelHelper() [constructor]
    cls.add_constructor([])
    ## plc-helper.h (module 'plc'): ns3::PLC_ChannelHelper::PLC_ChannelHelper(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_Channel> ns3::PLC_ChannelHelper::GetChannel() [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::PLC_Channel >', 
                   [])
    ## plc-helper.h (module 'plc'): static ns3::TypeId ns3::PLC_ChannelHelper::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-helper.h (module 'plc'): void ns3::PLC_ChannelHelper::Install(ns3::PLC_NodeList nodes) [member function]
    cls.add_method('Install', 
                   'void', 
                   [param('ns3::PLC_NodeList', 'nodes')])
    ## plc-helper.h (module 'plc'): void ns3::PLC_ChannelHelper::SetSpectrumModel(ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('SetSpectrumModel', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    return

def register_Ns3PLC_ChannelTransferImpl_methods(root_module, cls):
    ## plc-channel.h (module 'plc'): ns3::PLC_ChannelTransferImpl::PLC_ChannelTransferImpl(ns3::PLC_ChannelTransferImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ChannelTransferImpl const &', 'arg0')])
    ## plc-channel.h (module 'plc'): ns3::PLC_ChannelTransferImpl::PLC_ChannelTransferImpl(ns3::PLC_TxInterface * txInterface, ns3::PLC_RxInterface * rxInterface, ns3::Ptr<ns3::SpectrumModel const> sm, bool create_backbone_path=true) [constructor]
    cls.add_constructor([param('ns3::PLC_TxInterface *', 'txInterface'), param('ns3::PLC_RxInterface *', 'rxInterface'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('bool', 'create_backbone_path', default_value='true')])
    ## plc-channel.h (module 'plc'): __gnu_cxx::__normal_iterator<ns3::Ptr<ns3::PLC_BackboneBranch>*,std::vector<ns3::Ptr<ns3::PLC_BackboneBranch>, std::allocator<ns3::Ptr<ns3::PLC_BackboneBranch> > > > ns3::PLC_ChannelTransferImpl::BackbonePathBegin() [member function]
    cls.add_method('BackbonePathBegin', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::PLC_BackboneBranch >, std::vector< ns3::Ptr< ns3::PLC_BackboneBranch > > >', 
                   [])
    ## plc-channel.h (module 'plc'): __gnu_cxx::__normal_iterator<ns3::Ptr<ns3::PLC_BackboneBranch>*,std::vector<ns3::Ptr<ns3::PLC_BackboneBranch>, std::allocator<ns3::Ptr<ns3::PLC_BackboneBranch> > > > ns3::PLC_ChannelTransferImpl::BackbonePathEnd() [member function]
    cls.add_method('BackbonePathEnd', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::PLC_BackboneBranch >, std::vector< ns3::Ptr< ns3::PLC_BackboneBranch > > >', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::CalculateChannelTransferVector() [member function]
    cls.add_method('CalculateChannelTransferVector', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue> ns3::PLC_ChannelTransferImpl::CalculateRxPowerSpectralDensity(ns3::Ptr<ns3::SpectrumValue const> txPsd, ns3::Timeslot timeslot=0) [member function]
    cls.add_method('CalculateRxPowerSpectralDensity', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'txPsd'), param('ns3::Timeslot', 'timeslot', default_value='0')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::CreateBackbonePath() [member function]
    cls.add_method('CreateBackbonePath', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::DiscoverBackboneBranches() [member function]
    cls.add_method('DiscoverBackboneBranches', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::GenerateAbsSqrCtf() [member function]
    cls.add_method('GenerateAbsSqrCtf', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue> ns3::PLC_ChannelTransferImpl::GetAbsSqrCtf(unsigned int timeslot=0) [member function]
    cls.add_method('GetAbsSqrCtf', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [param('unsigned int', 'timeslot', default_value='0')])
    ## plc-channel.h (module 'plc'): std::list<ns3::PLC_BackboneBranch*,std::allocator<ns3::PLC_BackboneBranch*> > ns3::PLC_ChannelTransferImpl::GetBackbonePath() [member function]
    cls.add_method('GetBackbonePath', 
                   'std::list< ns3::PLC_BackboneBranch * >', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_ChannelTransferImpl::GetChannelTransferVector() [member function]
    cls.add_method('GetChannelTransferVector', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::Time ns3::PLC_ChannelTransferImpl::GetDirectPathPropagationDelay() [member function]
    cls.add_method('GetDirectPathPropagationDelay', 
                   'ns3::Time', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_Graph> ns3::PLC_ChannelTransferImpl::GetGraph() [member function]
    cls.add_method('GetGraph', 
                   'ns3::Ptr< ns3::PLC_Graph >', 
                   [])
    ## plc-channel.h (module 'plc'): static ns3::TypeId ns3::PLC_ChannelTransferImpl::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::InitializeChannelTransferVector(bool set_time_variant=false) [member function]
    cls.add_method('InitializeChannelTransferVector', 
                   'void', 
                   [param('bool', 'set_time_variant', default_value='false')])
    ## plc-channel.h (module 'plc'): bool ns3::PLC_ChannelTransferImpl::IsTimeVariant() [member function]
    cls.add_method('IsTimeVariant', 
                   'bool', 
                   [])
    ## plc-channel.h (module 'plc'): bool ns3::PLC_ChannelTransferImpl::IsUp2Date() [member function]
    cls.add_method('IsUp2Date', 
                   'bool', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::Lock() const [member function]
    cls.add_method('Lock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::SetTimeVariant() [member function]
    cls.add_method('SetTimeVariant', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::Unlock() const [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::UpdateImmediately(bool value) [member function]
    cls.add_method('UpdateImmediately', 
                   'void', 
                   [param('bool', 'value')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_ChannelTransferImpl::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_Edge_methods(root_module, cls):
    ## plc-edge.h (module 'plc'): ns3::PLC_Edge::PLC_Edge(ns3::PLC_Edge const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Edge const &', 'arg0')])
    ## plc-edge.h (module 'plc'): ns3::PLC_Edge::PLC_Edge(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::Ptr<ns3::PLC_Node> from, ns3::Ptr<ns3::PLC_Node> to) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::Ptr< ns3::PLC_Node >', 'from'), param('ns3::Ptr< ns3::PLC_Node >', 'to')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::CacheImpedances(ns3::PLC_Node * dst_node, ns3::Ptr<ns3::PLC_ValueBase> input_impedance, ns3::Ptr<ns3::PLC_ValueBase> load_impedance) [member function]
    cls.add_method('CacheImpedances', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'input_impedance'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'load_impedance')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::CalculateEdgeTransferFactor(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('CalculateEdgeTransferFactor', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::CalculateInputImpedance(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('CalculateInputImpedance', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-edge.h (module 'plc'): double ns3::PLC_Edge::GetAttenuationApproxdB() [member function]
    cls.add_method('GetAttenuationApproxdB', 
                   'double', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-edge.h (module 'plc'): ns3::PLC_Node * ns3::PLC_Edge::GetConnectedNode(ns3::PLC_Node * src_node) [member function]
    cls.add_method('GetConnectedNode', 
                   'ns3::PLC_Node *', 
                   [param('ns3::PLC_Node *', 'src_node')])
    ## plc-edge.h (module 'plc'): ns3::PLC_EdgeTransferUnit * ns3::PLC_Edge::GetEdgeTransferUnit(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('GetEdgeTransferUnit', 
                   'ns3::PLC_EdgeTransferUnit *', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): double ns3::PLC_Edge::GetIdealPropagationDelay() [member function]
    cls.add_method('GetIdealPropagationDelay', 
                   'double', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-edge.h (module 'plc'): ns3::PLC_Impedance * ns3::PLC_Edge::GetInputImpedance(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('GetInputImpedance', 
                   'ns3::PLC_Impedance *', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): double ns3::PLC_Edge::GetLength() [member function]
    cls.add_method('GetLength', 
                   'double', 
                   [])
    ## plc-edge.h (module 'plc'): std::vector<ns3::PLC_Node*,std::allocator<ns3::PLC_Node*> > ns3::PLC_Edge::GetNodes() [member function]
    cls.add_method('GetNodes', 
                   'std::vector< ns3::PLC_Node * >', 
                   [])
    ## plc-edge.h (module 'plc'): static ns3::TypeId ns3::PLC_Edge::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-edge.h (module 'plc'): ns3::PLC_EdgeTransferUnit * ns3::PLC_Edge::GetUpdatedEdgeTransferUnit(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('GetUpdatedEdgeTransferUnit', 
                   'ns3::PLC_EdgeTransferUnit *', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::InitEdgeTransferFactor(ns3::PLC_Node * dst_node, bool time_variant=false) [member function]
    cls.add_method('InitEdgeTransferFactor', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node'), param('bool', 'time_variant', default_value='false')])
    ## plc-edge.h (module 'plc'): bool ns3::PLC_Edge::IsEdgeTransferFactorUp2Date(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('IsEdgeTransferFactorUp2Date', 
                   'bool', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): bool ns3::PLC_Edge::IsInputImpedanceUp2Date(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('IsInputImpedanceUp2Date', 
                   'bool', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::Lock() const [member function]
    cls.add_method('Lock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::SetEdgeTransferFactorOutOfDate(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('SetEdgeTransferFactorOutOfDate', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::SetInputImpedanceOutOfDate(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('SetInputImpedanceOutOfDate', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::Unlock() const [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_Edge::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_EdgeTransferUnit_methods(root_module, cls):
    ## plc-channel.h (module 'plc'): ns3::PLC_EdgeTransferUnit::PLC_EdgeTransferUnit(ns3::PLC_EdgeTransferUnit const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_EdgeTransferUnit const &', 'arg0')])
    ## plc-channel.h (module 'plc'): ns3::PLC_EdgeTransferUnit::PLC_EdgeTransferUnit(ns3::PLC_Edge * edge, ns3::PLC_Node * dst_node, ns3::Ptr<ns3::SpectrumModel const> sm, bool time_variant=false) [constructor]
    cls.add_constructor([param('ns3::PLC_Edge *', 'edge'), param('ns3::PLC_Node *', 'dst_node'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('bool', 'time_variant', default_value='false')])
    ## plc-channel.h (module 'plc'): ns3::PLC_Node * ns3::PLC_EdgeTransferUnit::GetDstNode() const [member function]
    cls.add_method('GetDstNode', 
                   'ns3::PLC_Node *', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::PLC_Edge * ns3::PLC_EdgeTransferUnit::GetEdge() const [member function]
    cls.add_method('GetEdge', 
                   'ns3::PLC_Edge *', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_EdgeTransferUnit::GetEdgeTransferVector() [member function]
    cls.add_method('GetEdgeTransferVector', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::PLC_TransferBase * ns3::PLC_EdgeTransferUnit::GetEdgeTransferVectorPtr() [member function]
    cls.add_method('GetEdgeTransferVectorPtr', 
                   'ns3::PLC_TransferBase *', 
                   [])
    ## plc-channel.h (module 'plc'): static ns3::TypeId ns3::PLC_EdgeTransferUnit::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-channel.h (module 'plc'): bool ns3::PLC_EdgeTransferUnit::IsTimeVariant() [member function]
    cls.add_method('IsTimeVariant', 
                   'bool', 
                   [])
    ## plc-channel.h (module 'plc'): bool ns3::PLC_EdgeTransferUnit::IsUp2Date() const [member function]
    cls.add_method('IsUp2Date', 
                   'bool', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_EdgeTransferUnit::Lock() const [member function]
    cls.add_method('Lock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_EdgeTransferUnit::SetEdgeTransferVector(ns3::Ptr<ns3::PLC_ValueBase> ctv) [member function]
    cls.add_method('SetEdgeTransferVector', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'ctv')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_EdgeTransferUnit::SetOutOfDate() [member function]
    cls.add_method('SetOutOfDate', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_EdgeTransferUnit::Unlock() const [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_EdgeTransferUnit::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_FourSectorPowerSupplyCable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_FourSectorPowerSupplyCable::PLC_FourSectorPowerSupplyCable(ns3::PLC_FourSectorPowerSupplyCable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_FourSectorPowerSupplyCable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_FourSectorPowerSupplyCable::PLC_FourSectorPowerSupplyCable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_FourSectorPowerSupplyCable::PLC_FourSectorPowerSupplyCable(double radius, double conductor_distance, double tan_loss_angle, double epsilon_r, double rho, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('double', 'radius'), param('double', 'conductor_distance'), param('double', 'tan_loss_angle'), param('double', 'epsilon_r'), param('double', 'rho'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): ns3::PLC_FourSectorPowerSupplyCable::PLC_FourSectorPowerSupplyCable(double radius, double conductor_distance, ns3::PLC_FreqSelectiveRealValue tan_loss_angle, ns3::PLC_FreqSelectiveRealValue epsilon_r, double rho, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('double', 'radius'), param('double', 'conductor_distance'), param('ns3::PLC_FreqSelectiveRealValue', 'tan_loss_angle'), param('ns3::PLC_FreqSelectiveRealValue', 'epsilon_r'), param('double', 'rho'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_FourSectorPowerSupplyCable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-cable.h (module 'plc'): void ns3::PLC_FourSectorPowerSupplyCable::Calculate(double radius, double conductor_distance, double tan_loss_angle, double epsilon_r, double rho, ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [param('double', 'radius'), param('double', 'conductor_distance'), param('double', 'tan_loss_angle'), param('double', 'epsilon_r'), param('double', 'rho'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_FourSectorPowerSupplyCable::Calculate(double radius, double conductor_distance, ns3::PLC_FreqSelectiveRealValue tan_loss_angle, ns3::PLC_FreqSelectiveRealValue epsilon_r, double rho, ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [param('double', 'radius'), param('double', 'conductor_distance'), param('ns3::PLC_FreqSelectiveRealValue', 'tan_loss_angle'), param('ns3::PLC_FreqSelectiveRealValue', 'epsilon_r'), param('double', 'rho'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_FourSectorPowerSupplyCable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_Graph_methods(root_module, cls):
    ## plc-graph.h (module 'plc'): ns3::PLC_Graph::PLC_Graph(ns3::PLC_Graph const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Graph const &', 'arg0')])
    ## plc-graph.h (module 'plc'): ns3::PLC_Graph::PLC_Graph() [constructor]
    cls.add_constructor([])
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::AddNode(ns3::Ptr<ns3::PLC_Node> node) [member function]
    cls.add_method('AddNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'node')])
    ## plc-graph.h (module 'plc'): bool ns3::PLC_Graph::BackboneBranchExists(ns3::PLC_BackboneBranchKey key) [member function]
    cls.add_method('BackboneBranchExists', 
                   'bool', 
                   [param('ns3::PLC_BackboneBranchKey', 'key')])
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::CreatePLCGraph() [member function]
    cls.add_method('CreatePLCGraph', 
                   'void', 
                   [])
    ## plc-graph.h (module 'plc'): ns3::Ptr<ns3::PLC_BackboneBranch> ns3::PLC_Graph::GetBackboneBranch(ns3::PLC_BackboneBranchKey bb_key) [member function]
    cls.add_method('GetBackboneBranch', 
                   'ns3::Ptr< ns3::PLC_BackboneBranch >', 
                   [param('ns3::PLC_BackboneBranchKey', 'bb_key')])
    ## plc-graph.h (module 'plc'): ns3::Ptr<ns3::PLC_Channel> ns3::PLC_Graph::GetChannel() [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::PLC_Channel >', 
                   [])
    ## plc-graph.h (module 'plc'): ns3::Ptr<ns3::PLC_Channel> ns3::PLC_Graph::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::PLC_Channel >', 
                   [], 
                   is_const=True)
    ## plc-graph.h (module 'plc'): std::vector<ns3::PLC_RxInterface*,std::allocator<ns3::PLC_RxInterface*> > ns3::PLC_Graph::GetConnectedRxInterfacePeekPtrs() [member function]
    cls.add_method('GetConnectedRxInterfacePeekPtrs', 
                   'std::vector< ns3::PLC_RxInterface * >', 
                   [])
    ## plc-graph.h (module 'plc'): std::vector<ns3::Ptr<ns3::PLC_RxInterface>, std::allocator<ns3::Ptr<ns3::PLC_RxInterface> > > ns3::PLC_Graph::GetConnectedRxInterfaces() [member function]
    cls.add_method('GetConnectedRxInterfaces', 
                   'std::vector< ns3::Ptr< ns3::PLC_RxInterface > >', 
                   [])
    ## plc-graph.h (module 'plc'): double ns3::PLC_Graph::GetDistance(ns3::Ptr<ns3::PLC_Node> from, ns3::Ptr<ns3::PLC_Node> to) [member function]
    cls.add_method('GetDistance', 
                   'double', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'from'), param('ns3::Ptr< ns3::PLC_Node >', 'to')])
    ## plc-graph.h (module 'plc'): boost::UGraph * ns3::PLC_Graph::GetGraphPtr() [member function]
    cls.add_method('GetGraphPtr', 
                   'boost::UGraph *', 
                   [])
    ## plc-graph.h (module 'plc'): ns3::PLC_Node * ns3::PLC_Graph::GetNodePeekPtr(unsigned int id) [member function]
    cls.add_method('GetNodePeekPtr', 
                   'ns3::PLC_Node *', 
                   [param('unsigned int', 'id')])
    ## plc-graph.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_Graph::GetNodePtr(unsigned int id) [member function]
    cls.add_method('GetNodePtr', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [param('unsigned int', 'id')])
    ## plc-graph.h (module 'plc'): std::vector<ns3::Ptr<ns3::PLC_Node>, std::allocator<ns3::Ptr<ns3::PLC_Node> > > ns3::PLC_Graph::GetNodes() [member function]
    cls.add_method('GetNodes', 
                   'std::vector< ns3::Ptr< ns3::PLC_Node > >', 
                   [])
    ## plc-graph.h (module 'plc'): std::list<ns3::Ptr<ns3::PLC_Node>,std::allocator<ns3::Ptr<ns3::PLC_Node> > > ns3::PLC_Graph::GetShortestPath(ns3::Ptr<ns3::PLC_Node> from, ns3::Ptr<ns3::PLC_Node> to) [member function]
    cls.add_method('GetShortestPath', 
                   'std::list< ns3::Ptr< ns3::PLC_Node > >', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'from'), param('ns3::Ptr< ns3::PLC_Node >', 'to')])
    ## plc-graph.h (module 'plc'): static ns3::TypeId ns3::PLC_Graph::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::Lock() [member function]
    cls.add_method('Lock', 
                   'void', 
                   [])
    ## plc-graph.h (module 'plc'): bool ns3::PLC_Graph::PathExists(ns3::Ptr<ns3::PLC_Node> from, ns3::Ptr<ns3::PLC_Node> to) [member function]
    cls.add_method('PathExists', 
                   'bool', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'from'), param('ns3::Ptr< ns3::PLC_Node >', 'to')])
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::RegisterBackboneBranch(ns3::PLC_BackboneBranchKey bb_key, ns3::Ptr<ns3::PLC_BackboneBranch> bb_branch) [member function]
    cls.add_method('RegisterBackboneBranch', 
                   'void', 
                   [param('ns3::PLC_BackboneBranchKey', 'bb_key'), param('ns3::Ptr< ns3::PLC_BackboneBranch >', 'bb_branch')])
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::SetChannel(ns3::Ptr<ns3::PLC_Channel> channel) [member function]
    cls.add_method('SetChannel', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Channel >', 'channel')])
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::Unlock() [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [])
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::CalculateShortestPaths() [member function]
    cls.add_method('CalculateShortestPaths', 
                   'void', 
                   [], 
                   visibility='protected')
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-graph.h (module 'plc'): void ns3::PLC_Graph::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_ImpedanceHelper_methods(root_module, cls):
    ## plc-helper.h (module 'plc'): ns3::PLC_ImpedanceHelper::PLC_ImpedanceHelper(ns3::PLC_ImpedanceHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ImpedanceHelper const &', 'arg0')])
    ## plc-helper.h (module 'plc'): ns3::PLC_ImpedanceHelper::PLC_ImpedanceHelper(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_ConstValue> ns3::PLC_ImpedanceHelper::CreateConstImpedance() [member function]
    cls.add_method('CreateConstImpedance', 
                   'ns3::Ptr< ns3::PLC_ConstValue >', 
                   [])
    ## plc-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_FreqSelectiveValue> ns3::PLC_ImpedanceHelper::CreateFreqSelectiveImpedance() [member function]
    cls.add_method('CreateFreqSelectiveImpedance', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue >', 
                   [])
    ## plc-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_FreqSelectiveValue> ns3::PLC_ImpedanceHelper::CreateIdleTransformerImpedance(double R, double C, double L) [member function]
    cls.add_method('CreateIdleTransformerImpedance', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue >', 
                   [param('double', 'R'), param('double', 'C'), param('double', 'L')])
    ## plc-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_FreqSelectiveValue> ns3::PLC_ImpedanceHelper::CreateSeriesResonanceImpedance(double R, double C, double L) [member function]
    cls.add_method('CreateSeriesResonanceImpedance', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue >', 
                   [param('double', 'R'), param('double', 'C'), param('double', 'L')])
    ## plc-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_TimeVariantFreqSelectiveValue> ns3::PLC_ImpedanceHelper::CreateTimeVariantFreqSelectiveImpedance() [member function]
    cls.add_method('CreateTimeVariantFreqSelectiveImpedance', 
                   'ns3::Ptr< ns3::PLC_TimeVariantFreqSelectiveValue >', 
                   [])
    ## plc-helper.h (module 'plc'): static ns3::TypeId ns3::PLC_ImpedanceHelper::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-helper.h (module 'plc'): void ns3::PLC_ImpedanceHelper::SetConstImpedanceBounds(double rmin, double rmax, double imin, double imax) [member function]
    cls.add_method('SetConstImpedanceBounds', 
                   'void', 
                   [param('double', 'rmin'), param('double', 'rmax'), param('double', 'imin'), param('double', 'imax')])
    ## plc-helper.h (module 'plc'): void ns3::PLC_ImpedanceHelper::SetFreqSelectiveImpedanceBounds(double Rmin, double Rmax, double Qmin, double Qmax, double f0min, double f0max) [member function]
    cls.add_method('SetFreqSelectiveImpedanceBounds', 
                   'void', 
                   [param('double', 'Rmin'), param('double', 'Rmax'), param('double', 'Qmin'), param('double', 'Qmax'), param('double', 'f0min'), param('double', 'f0max')])
    ## plc-helper.h (module 'plc'): void ns3::PLC_ImpedanceHelper::SetTimeVariantFreqSelectiveImpedanceBounds(double RoffsMin, double RoffsMax, double QoffsMin, double QoffsMax, double f0offsMin, double f0offsMax, double RamplMin, double RamplMax, double QamplMin, double QamplMax, double f0amplMin, double f0amplMax, double phiMin, double phiMax) [member function]
    cls.add_method('SetTimeVariantFreqSelectiveImpedanceBounds', 
                   'void', 
                   [param('double', 'RoffsMin'), param('double', 'RoffsMax'), param('double', 'QoffsMin'), param('double', 'QoffsMax'), param('double', 'f0offsMin'), param('double', 'f0offsMax'), param('double', 'RamplMin'), param('double', 'RamplMax'), param('double', 'QamplMin'), param('double', 'QamplMax'), param('double', 'f0amplMin'), param('double', 'f0amplMax'), param('double', 'phiMin'), param('double', 'phiMax')])
    return

def register_Ns3PLC_Interface_methods(root_module, cls):
    ## plc-interface.h (module 'plc'): ns3::PLC_Interface::PLC_Interface(ns3::PLC_Interface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Interface const &', 'arg0')])
    ## plc-interface.h (module 'plc'): ns3::PLC_Interface::PLC_Interface(ns3::Ptr<ns3::PLC_Node> associated_plc_node, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'associated_plc_node'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-interface.h (module 'plc'): ns3::Ptr<ns3::PLC_Channel> ns3::PLC_Interface::GetChannel() [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::PLC_Channel >', 
                   [])
    ## plc-interface.h (module 'plc'): ns3::Ptr<ns3::PLC_Graph> ns3::PLC_Interface::GetGraph() [member function]
    cls.add_method('GetGraph', 
                   'ns3::Ptr< ns3::PLC_Graph >', 
                   [])
    ## plc-interface.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_Interface::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [], 
                   is_const=True)
    ## plc-interface.h (module 'plc'): ns3::PLC_Node * ns3::PLC_Interface::GetNodePeekPointer() const [member function]
    cls.add_method('GetNodePeekPointer', 
                   'ns3::PLC_Node *', 
                   [], 
                   is_const=True)
    ## plc-interface.h (module 'plc'): ns3::Ptr<ns3::PLC_Phy> ns3::PLC_Interface::GetPhy() [member function]
    cls.add_method('GetPhy', 
                   'ns3::Ptr< ns3::PLC_Phy >', 
                   [])
    ## plc-interface.h (module 'plc'): static ns3::TypeId ns3::PLC_Interface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_Interface::Lock() [member function]
    cls.add_method('Lock', 
                   'void', 
                   [])
    ## plc-interface.h (module 'plc'): void ns3::PLC_Interface::SetNode(ns3::Ptr<ns3::PLC_Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'node')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_Interface::SetPhy(ns3::Ptr<ns3::PLC_Phy> phy) [member function]
    cls.add_method('SetPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'phy')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_Interface::Unlock() [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [])
    ## plc-interface.h (module 'plc'): void ns3::PLC_Interface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_Interface::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_Interference_methods(root_module, cls):
    ## plc-interference.h (module 'plc'): ns3::PLC_Interference::PLC_Interference(ns3::PLC_Interference const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Interference const &', 'arg0')])
    ## plc-interference.h (module 'plc'): ns3::PLC_Interference::PLC_Interference() [constructor]
    cls.add_constructor([])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::AddInterferenceSignal(ns3::Ptr<ns3::SpectrumValue const> spd) [member function]
    cls.add_method('AddInterferenceSignal', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'spd')])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::AlterRxSignal(ns3::Ptr<ns3::SpectrumValue const> rxSignal) [member function]
    cls.add_method('AlterRxSignal', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'rxSignal')])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::EndRx() [member function]
    cls.add_method('EndRx', 
                   'void', 
                   [])
    ## plc-interference.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue const> ns3::PLC_Interference::GetNoiseFloor() [member function]
    cls.add_method('GetNoiseFloor', 
                   'ns3::Ptr< ns3::SpectrumValue const >', 
                   [])
    ## plc-interference.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue> ns3::PLC_Interference::GetSinr() [member function]
    cls.add_method('GetSinr', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [])
    ## plc-interference.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue const> ns3::PLC_Interference::GetSinrBase() [member function]
    cls.add_method('GetSinrBase', 
                   'ns3::Ptr< ns3::SpectrumValue const >', 
                   [])
    ## plc-interference.h (module 'plc'): double ns3::PLC_Interference::GetTotalNoisePower() [member function]
    cls.add_method('GetTotalNoisePower', 
                   'double', 
                   [])
    ## plc-interference.h (module 'plc'): double ns3::PLC_Interference::GetTotalRxPower() [member function]
    cls.add_method('GetTotalRxPower', 
                   'double', 
                   [])
    ## plc-interference.h (module 'plc'): static ns3::TypeId ns3::PLC_Interference::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::RemoveInterferenceSignal(ns3::Ptr<ns3::SpectrumValue const> spd) [member function]
    cls.add_method('RemoveInterferenceSignal', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'spd')])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::SetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [member function]
    cls.add_method('SetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::SetSinrBase(ns3::Ptr<ns3::SpectrumValue const> baseSinr) [member function]
    cls.add_method('SetSinrBase', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'baseSinr')])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::StartRx(ns3::Ptr<ns3::SpectrumValue const> rxPsd) [member function]
    cls.add_method('StartRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'rxPsd')])
    ## plc-interference.h (module 'plc'): void ns3::PLC_Interference::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_Line_methods(root_module, cls):
    ## plc-edge.h (module 'plc'): ns3::PLC_Line::PLC_Line(ns3::PLC_Line const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Line const &', 'arg0')])
    ## plc-edge.h (module 'plc'): ns3::PLC_Line::PLC_Line(ns3::Ptr<ns3::PLC_Cable> cable_type, ns3::Ptr<ns3::PLC_Node> from, ns3::Ptr<ns3::PLC_Node> to) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Cable >', 'cable_type'), param('ns3::Ptr< ns3::PLC_Node >', 'from'), param('ns3::Ptr< ns3::PLC_Node >', 'to')])
    ## plc-edge.h (module 'plc'): void ns3::PLC_Line::CalculateEdgeTransferFactor(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('CalculateEdgeTransferFactor', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')], 
                   is_virtual=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_Line::CalculateInputImpedance(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('CalculateInputImpedance', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')], 
                   is_virtual=True)
    ## plc-edge.h (module 'plc'): double ns3::PLC_Line::GetAttenuationApproxdB() [member function]
    cls.add_method('GetAttenuationApproxdB', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## plc-edge.h (module 'plc'): ns3::Ptr<ns3::PLC_Cable const> ns3::PLC_Line::GetCable() const [member function]
    cls.add_method('GetCable', 
                   'ns3::Ptr< ns3::PLC_Cable const >', 
                   [], 
                   is_const=True)
    ## plc-edge.h (module 'plc'): ns3::Ptr<const ns3::PLC_FreqSelectiveValue> ns3::PLC_Line::GetCharLineImp() const [member function]
    cls.add_method('GetCharLineImp', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue const >', 
                   [], 
                   is_const=True)
    ## plc-edge.h (module 'plc'): double ns3::PLC_Line::GetIdealPropagationDelay() [member function]
    cls.add_method('GetIdealPropagationDelay', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## plc-edge.h (module 'plc'): ns3::Ptr<const ns3::PLC_FreqSelectiveValue> ns3::PLC_Line::GetTransLineConst() const [member function]
    cls.add_method('GetTransLineConst', 
                   'ns3::Ptr< ns3::PLC_FreqSelectiveValue const >', 
                   [], 
                   is_const=True)
    ## plc-edge.h (module 'plc'): static ns3::TypeId ns3::PLC_Line::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_Line::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_LinkPerformanceModel_methods(root_module, cls):
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_LinkPerformanceModel::PLC_LinkPerformanceModel(ns3::PLC_LinkPerformanceModel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_LinkPerformanceModel const &', 'arg0')])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_LinkPerformanceModel::PLC_LinkPerformanceModel() [constructor]
    cls.add_constructor([])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_LinkPerformanceModel::PLC_LinkPerformanceModel(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::AddNoiseSignal(ns3::Ptr<ns3::SpectrumValue const> noisePsd) [member function]
    cls.add_method('AddNoiseSignal', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noisePsd')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::AlterRxSignal(ns3::Ptr<ns3::SpectrumValue const> rxPsd) [member function]
    cls.add_method('AlterRxSignal', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'rxPsd')])
    ## plc-link-performance-model.h (module 'plc'): bool ns3::PLC_LinkPerformanceModel::EndRx() [member function]
    cls.add_method('EndRx', 
                   'bool', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::EvaluateChunk() [member function]
    cls.add_method('EvaluateChunk', 
                   'void', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): ns3::Ptr<ns3::PLC_Interference> ns3::PLC_LinkPerformanceModel::GetInterference() [member function]
    cls.add_method('GetInterference', 
                   'ns3::Ptr< ns3::PLC_Interference >', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): double ns3::PLC_LinkPerformanceModel::GetTotalNoisePower() [member function]
    cls.add_method('GetTotalNoisePower', 
                   'double', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): double ns3::PLC_LinkPerformanceModel::GetTotalRxPower() [member function]
    cls.add_method('GetTotalRxPower', 
                   'double', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): static ns3::TypeId ns3::PLC_LinkPerformanceModel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::RemoveNoiseSignal(ns3::Ptr<ns3::SpectrumValue const> noisePsd) [member function]
    cls.add_method('RemoveNoiseSignal', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noisePsd')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::SetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [member function]
    cls.add_method('SetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::SetSinrBase(ns3::Ptr<ns3::SpectrumValue const> sinrBase) [member function]
    cls.add_method('SetSinrBase', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'sinrBase')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::StartRx(ns3::ModulationAndCodingType mcs, ns3::Ptr<ns3::SpectrumValue const> rxPsd, double requiredInformationBits=0) [member function]
    cls.add_method('StartRx', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs'), param('ns3::Ptr< ns3::SpectrumValue const >', 'rxPsd'), param('double', 'requiredInformationBits', default_value='0')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): bool ns3::PLC_LinkPerformanceModel::DoEndRx() [member function]
    cls.add_method('DoEndRx', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::DoEvaluateChunk() [member function]
    cls.add_method('DoEvaluateChunk', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_LinkPerformanceModel::DoStartRx(double requiredInformationBits) [member function]
    cls.add_method('DoStartRx', 
                   'void', 
                   [param('double', 'requiredInformationBits')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_Mac_methods(root_module, cls):
    ## plc-mac.h (module 'plc'): ns3::PLC_Mac::PLC_Mac(ns3::PLC_Mac const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Mac const &', 'arg0')])
    ## plc-mac.h (module 'plc'): ns3::PLC_Mac::PLC_Mac() [constructor]
    cls.add_constructor([])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::CcaConfirm(ns3::PLC_PhyCcaResult status) [member function]
    cls.add_method('CcaConfirm', 
                   'void', 
                   [param('ns3::PLC_PhyCcaResult', 'status')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::CsmaCaConfirm(ns3::PLC_CsmaCaState state) [member function]
    cls.add_method('CsmaCaConfirm', 
                   'void', 
                   [param('ns3::PLC_CsmaCaState', 'state')])
    ## plc-mac.h (module 'plc'): ns3::Mac48Address ns3::PLC_Mac::GetAddress() [member function]
    cls.add_method('GetAddress', 
                   'ns3::Mac48Address', 
                   [])
    ## plc-mac.h (module 'plc'): ns3::Mac48Address ns3::PLC_Mac::GetBroadcastAddress() [member function]
    cls.add_method('GetBroadcastAddress', 
                   'ns3::Mac48Address', 
                   [])
    ## plc-mac.h (module 'plc'): ns3::Mac48Address ns3::PLC_Mac::GetMulticastAddress() [member function]
    cls.add_method('GetMulticastAddress', 
                   'ns3::Mac48Address', 
                   [])
    ## plc-mac.h (module 'plc'): ns3::Ptr<ns3::PLC_Phy> ns3::PLC_Mac::GetPhy() [member function]
    cls.add_method('GetPhy', 
                   'ns3::Ptr< ns3::PLC_Phy >', 
                   [])
    ## plc-mac.h (module 'plc'): static ns3::TypeId ns3::PLC_Mac::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::NotifyCcaConfirm(ns3::PLC_PhyCcaResult status) [member function]
    cls.add_method('NotifyCcaConfirm', 
                   'void', 
                   [param('ns3::PLC_PhyCcaResult', 'status')], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::NotifyCsmaCaConfirm(ns3::PLC_CsmaCaState state) [member function]
    cls.add_method('NotifyCsmaCaConfirm', 
                   'void', 
                   [param('ns3::PLC_CsmaCaState', 'state')], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::NotifyReceptionEndOk(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('NotifyReceptionEndOk', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::NotifyTransmissionEnd() [member function]
    cls.add_method('NotifyTransmissionEnd', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::RandomBackoffDelay() [member function]
    cls.add_method('RandomBackoffDelay', 
                   'void', 
                   [])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::RequestCca() [member function]
    cls.add_method('RequestCca', 
                   'void', 
                   [])
    ## plc-mac.h (module 'plc'): bool ns3::PLC_Mac::Send(ns3::Ptr<ns3::Packet> p, ns3::Mac48Address dst) [member function]
    cls.add_method('Send', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Mac48Address', 'dst')])
    ## plc-mac.h (module 'plc'): bool ns3::PLC_Mac::SendFrom(ns3::Ptr<ns3::Packet> p, ns3::Mac48Address src, ns3::Mac48Address dst) [member function]
    cls.add_method('SendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Mac48Address', 'src'), param('ns3::Mac48Address', 'dst')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetAddress(ns3::Mac48Address addr) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Mac48Address', 'addr')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetBroadcastAddress(ns3::Mac48Address addr) [member function]
    cls.add_method('SetBroadcastAddress', 
                   'void', 
                   [param('ns3::Mac48Address', 'addr')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetCcaRequestCallback(ns3::PLC_CcaRequestCallback c) [member function]
    cls.add_method('SetCcaRequestCallback', 
                   'void', 
                   [param('ns3::PLC_CcaRequestCallback', 'c')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetMacAcknowledgementCallback(ns3::PLC_MacAcknowledgementCallback c) [member function]
    cls.add_method('SetMacAcknowledgementCallback', 
                   'void', 
                   [param('ns3::PLC_MacAcknowledgementCallback', 'c')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetMacDataCallback(ns3::PLC_MacDataCallback c) [member function]
    cls.add_method('SetMacDataCallback', 
                   'void', 
                   [param('ns3::PLC_MacDataCallback', 'c')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetMulticastAddress(ns3::Mac48Address addr) [member function]
    cls.add_method('SetMulticastAddress', 
                   'void', 
                   [param('ns3::Mac48Address', 'addr')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetPhy(ns3::Ptr<ns3::PLC_Phy> phy) [member function]
    cls.add_method('SetPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'phy')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetPromiscuousMacDataCallback(ns3::PLC_MacDataCallback c) [member function]
    cls.add_method('SetPromiscuousMacDataCallback', 
                   'void', 
                   [param('ns3::PLC_MacDataCallback', 'c')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::SetTransmissionFailedCallback(ns3::PLC_MacTransmissionFailedCallback c) [member function]
    cls.add_method('SetTransmissionFailedCallback', 
                   'void', 
                   [param('ns3::PLC_MacTransmissionFailedCallback', 'c')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::StartCsmaCa() [member function]
    cls.add_method('StartCsmaCa', 
                   'void', 
                   [])
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-mac.h (module 'plc'): ns3::Ptr<ns3::PLC_Phy> ns3::PLC_Mac::DoGetPhy() [member function]
    cls.add_method('DoGetPhy', 
                   'ns3::Ptr< ns3::PLC_Phy >', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::DoProcess(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('DoProcess', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-mac.h (module 'plc'): bool ns3::PLC_Mac::DoSendFrom(ns3::Ptr<ns3::Packet> p, ns3::Mac48Address src, ns3::Mac48Address dst) [member function]
    cls.add_method('DoSendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Mac48Address', 'src'), param('ns3::Mac48Address', 'dst')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::DoSetPhy(ns3::Ptr<ns3::PLC_Phy> phy) [member function]
    cls.add_method('DoSetPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'phy')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_Mac::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_MacHeader_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## plc-header.h (module 'plc'): ns3::PLC_MacHeader::PLC_MacHeader(ns3::PLC_MacHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_MacHeader const &', 'arg0')])
    ## plc-header.h (module 'plc'): ns3::PLC_MacHeader::PLC_MacHeader() [constructor]
    cls.add_constructor([])
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_MacHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## plc-header.h (module 'plc'): ns3::Mac48Address ns3::PLC_MacHeader::GetDstAddress() const [member function]
    cls.add_method('GetDstAddress', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## plc-header.h (module 'plc'): ns3::TypeId ns3::PLC_MacHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_MacHeader::GetMessageLength() const [member function]
    cls.add_method('GetMessageLength', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## plc-header.h (module 'plc'): uint16_t ns3::PLC_MacHeader::GetSequenceNumber() const [member function]
    cls.add_method('GetSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_MacHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): ns3::Mac48Address ns3::PLC_MacHeader::GetSrcAddress() const [member function]
    cls.add_method('GetSrcAddress', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## plc-header.h (module 'plc'): ns3::PLC_MacHeader::MacHdrType ns3::PLC_MacHeader::GetType() const [member function]
    cls.add_method('GetType', 
                   'ns3::PLC_MacHeader::MacHdrType', 
                   [], 
                   is_const=True)
    ## plc-header.h (module 'plc'): static ns3::TypeId ns3::PLC_MacHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::SetDstAddress(ns3::Mac48Address addr) [member function]
    cls.add_method('SetDstAddress', 
                   'void', 
                   [param('ns3::Mac48Address', 'addr')])
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::SetMessageLength(uint32_t length) [member function]
    cls.add_method('SetMessageLength', 
                   'void', 
                   [param('uint32_t', 'length')])
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::SetSequenceNumber(uint16_t sqn) [member function]
    cls.add_method('SetSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'sqn')])
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::SetSrcAddress(ns3::Mac48Address addr) [member function]
    cls.add_method('SetSrcAddress', 
                   'void', 
                   [param('ns3::Mac48Address', 'addr')])
    ## plc-header.h (module 'plc'): void ns3::PLC_MacHeader::SetType(ns3::PLC_MacHeader::MacHdrType type) [member function]
    cls.add_method('SetType', 
                   'void', 
                   [param('ns3::PLC_MacHeader::MacHdrType', 'type')])
    return

def register_Ns3PLC_NAYY150SE_Cable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY150SE_Cable::PLC_NAYY150SE_Cable(ns3::PLC_NAYY150SE_Cable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_NAYY150SE_Cable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY150SE_Cable::PLC_NAYY150SE_Cable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY150SE_Cable::PLC_NAYY150SE_Cable(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_NAYY150SE_Cable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_NAYY150SE_Cable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_NAYY50SE_Cable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY50SE_Cable::PLC_NAYY50SE_Cable(ns3::PLC_NAYY50SE_Cable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_NAYY50SE_Cable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY50SE_Cable::PLC_NAYY50SE_Cable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_NAYY50SE_Cable::PLC_NAYY50SE_Cable(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_NAYY50SE_Cable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_NAYY50SE_Cable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_NetDeviceHelper_methods(root_module, cls):
    ## plc-device-helper.h (module 'plc'): ns3::PLC_NetDeviceHelper::PLC_NetDeviceHelper(ns3::PLC_NetDeviceHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_NetDeviceHelper const &', 'arg0')])
    ## plc-device-helper.h (module 'plc'): ns3::PLC_NetDeviceHelper::PLC_NetDeviceHelper(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::Ptr<ns3::SpectrumValue> txPsd, ns3::PLC_NodeList & netdevices) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::Ptr< ns3::SpectrumValue >', 'txPsd'), param('ns3::PLC_NodeList &', 'netdevices')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::CreateNodes(bool create) [member function]
    cls.add_method('CreateNodes', 
                   'void', 
                   [param('bool', 'create')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::DefineMacType(ns3::TypeId tid) [member function]
    cls.add_method('DefineMacType', 
                   'void', 
                   [param('ns3::TypeId', 'tid')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::DefinePhyType(ns3::TypeId tid) [member function]
    cls.add_method('DefinePhyType', 
                   'void', 
                   [param('ns3::TypeId', 'tid')])
    ## plc-device-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_NetDevice> ns3::PLC_NetDeviceHelper::GetDevice(std::string name) [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::PLC_NetDevice >', 
                   [param('std::string', 'name')])
    ## plc-device-helper.h (module 'plc'): ns3::PLC_NetdeviceMap ns3::PLC_NetDeviceHelper::GetNetdeviceMap() [member function]
    cls.add_method('GetNetdeviceMap', 
                   'ns3::PLC_NetdeviceMap', 
                   [])
    ## plc-device-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_NetDeviceHelper::GetRxImpedance() [member function]
    cls.add_method('GetRxImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-device-helper.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_NetDeviceHelper::GetTxImpedance() [member function]
    cls.add_method('GetTxImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-device-helper.h (module 'plc'): static ns3::TypeId ns3::PLC_NetDeviceHelper::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::SetHeaderModulationAndCodingScheme(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetHeaderModulationAndCodingScheme', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::SetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> psd) [member function]
    cls.add_method('SetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'psd')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::SetPayloadModulationAndCodingScheme(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetPayloadModulationAndCodingScheme', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::SetRxImpedance(ns3::Ptr<ns3::PLC_ValueBase> rxImpedance) [member function]
    cls.add_method('SetRxImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'rxImpedance')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::SetTxImpedance(ns3::Ptr<ns3::PLC_ValueBase> txImpedance) [member function]
    cls.add_method('SetTxImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'txImpedance')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::SetTxPowerSpectralDensity(ns3::Ptr<ns3::SpectrumValue> txPsd) [member function]
    cls.add_method('SetTxPowerSpectralDensity', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue >', 'txPsd')])
    ## plc-device-helper.h (module 'plc'): void ns3::PLC_NetDeviceHelper::Setup() [member function]
    cls.add_method('Setup', 
                   'void', 
                   [])
    return

def register_Ns3PLC_Node_methods(root_module, cls):
    ## plc-node.h (module 'plc'): ns3::PLC_Node::PLC_Node(ns3::PLC_Node const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Node const &', 'arg0')])
    ## plc-node.h (module 'plc'): ns3::PLC_Node::PLC_Node() [constructor]
    cls.add_constructor([])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::AddEdge(ns3::Ptr<ns3::PLC_Node> to, ns3::Ptr<ns3::PLC_Edge> edge) [member function]
    cls.add_method('AddEdge', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'to'), param('ns3::Ptr< ns3::PLC_Edge >', 'edge')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::AssociateBackboneBranch(ns3::Ptr<ns3::PLC_BackboneBranch> backboneBranch) [member function]
    cls.add_method('AssociateBackboneBranch', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_BackboneBranch >', 'backboneBranch')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::CloseCircuit() [member function]
    cls.add_method('CloseCircuit', 
                   'void', 
                   [])
    ## plc-node.h (module 'plc'): ns3::Ptr<ns3::PLC_Channel> ns3::PLC_Node::GetChannel() [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::PLC_Channel >', 
                   [])
    ## plc-node.h (module 'plc'): ns3::PLC_Edge * ns3::PLC_Node::GetEdge(ns3::PLC_Node * node) [member function]
    cls.add_method('GetEdge', 
                   'ns3::PLC_Edge *', 
                   [param('ns3::PLC_Node *', 'node')])
    ## plc-node.h (module 'plc'): ns3::PLC_NodeOutEdgesMap ns3::PLC_Node::GetEdges() [member function]
    cls.add_method('GetEdges', 
                   'ns3::PLC_NodeOutEdgesMap', 
                   [])
    ## plc-node.h (module 'plc'): ns3::Ptr<ns3::PLC_Graph> ns3::PLC_Node::GetGraph() [member function]
    cls.add_method('GetGraph', 
                   'ns3::Ptr< ns3::PLC_Graph >', 
                   [])
    ## plc-node.h (module 'plc'): static uint64_t ns3::PLC_Node::GetImpedanceHashSum() [member function]
    cls.add_method('GetImpedanceHashSum', 
                   'uint64_t', 
                   [], 
                   is_static=True)
    ## plc-node.h (module 'plc'): ns3::PLC_Impedance * ns3::PLC_Node::GetImpedancePeekPtr() const [member function]
    cls.add_method('GetImpedancePeekPtr', 
                   'ns3::PLC_Impedance *', 
                   [], 
                   is_const=True)
    ## plc-node.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_Node::GetImpedancePtr() [member function]
    cls.add_method('GetImpedancePtr', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-node.h (module 'plc'): std::string ns3::PLC_Node::GetName() [member function]
    cls.add_method('GetName', 
                   'std::string', 
                   [])
    ## plc-node.h (module 'plc'): size_t ns3::PLC_Node::GetNumEdges() [member function]
    cls.add_method('GetNumEdges', 
                   'size_t', 
                   [])
    ## plc-node.h (module 'plc'): ns3::Ptr<ns3::PLC_Outlet> ns3::PLC_Node::GetOutlet() [member function]
    cls.add_method('GetOutlet', 
                   'ns3::Ptr< ns3::PLC_Outlet >', 
                   [])
    ## plc-node.h (module 'plc'): ns3::PLC_Outlet * ns3::PLC_Node::GetOutletPeekPtr() [member function]
    cls.add_method('GetOutletPeekPtr', 
                   'ns3::PLC_Outlet *', 
                   [])
    ## plc-node.h (module 'plc'): ns3::Vector3D ns3::PLC_Node::GetPosition() [member function]
    cls.add_method('GetPosition', 
                   'ns3::Vector3D', 
                   [])
    ## plc-node.h (module 'plc'): static ns3::TypeId ns3::PLC_Node::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-node.h (module 'plc'): unsigned int ns3::PLC_Node::GetVertexId() [member function]
    cls.add_method('GetVertexId', 
                   'unsigned int', 
                   [])
    ## plc-node.h (module 'plc'): bool ns3::PLC_Node::HasOutlet() [member function]
    cls.add_method('HasOutlet', 
                   'bool', 
                   [])
    ## plc-node.h (module 'plc'): bool ns3::PLC_Node::IsOpenCircuit() [member function]
    cls.add_method('IsOpenCircuit', 
                   'bool', 
                   [])
    ## plc-node.h (module 'plc'): bool ns3::PLC_Node::IsTimeVariant() [member function]
    cls.add_method('IsTimeVariant', 
                   'bool', 
                   [])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::Lock() [member function]
    cls.add_method('Lock', 
                   'void', 
                   [])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::OpenCircuit() [member function]
    cls.add_method('OpenCircuit', 
                   'void', 
                   [])
    ## plc-node.h (module 'plc'): std::_Rb_tree_iterator<std::pair<ns3::PLC_Node* const, ns3::Ptr<ns3::PLC_Edge> > > ns3::PLC_Node::OutEdgesBegin() [member function]
    cls.add_method('OutEdgesBegin', 
                   'std::_Rb_tree_iterator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Edge > > >', 
                   [])
    ## plc-node.h (module 'plc'): std::_Rb_tree_iterator<std::pair<ns3::PLC_Node* const, ns3::Ptr<ns3::PLC_Edge> > > ns3::PLC_Node::OutEdgesEnd() [member function]
    cls.add_method('OutEdgesEnd', 
                   'std::_Rb_tree_iterator< std::pair< ns3::PLC_Node * const, ns3::Ptr< ns3::PLC_Edge > > >', 
                   [])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::SetGraph(ns3::Ptr<ns3::PLC_Graph> graph) [member function]
    cls.add_method('SetGraph', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Graph >', 'graph')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::SetImpedance(ns3::Ptr<ns3::PLC_ValueBase> impedance) [member function]
    cls.add_method('SetImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'impedance')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::SetName(std::string name) [member function]
    cls.add_method('SetName', 
                   'void', 
                   [param('std::string', 'name')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::SetOutlet(ns3::Ptr<ns3::PLC_Outlet> outlet) [member function]
    cls.add_method('SetOutlet', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Outlet >', 'outlet')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::SetPosition(ns3::Vector3D pos) [member function]
    cls.add_method('SetPosition', 
                   'void', 
                   [param('ns3::Vector3D', 'pos')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::SetPosition(double pos_x, double pos_y, double pos_z) [member function]
    cls.add_method('SetPosition', 
                   'void', 
                   [param('double', 'pos_x'), param('double', 'pos_y'), param('double', 'pos_z')])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::Unlock() [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [])
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-node.h (module 'plc'): void ns3::PLC_Node::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_NoiseSource_methods(root_module, cls):
    ## plc-noise.h (module 'plc'): ns3::PLC_NoiseSource::PLC_NoiseSource(ns3::PLC_NoiseSource const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_NoiseSource const &', 'arg0')])
    ## plc-noise.h (module 'plc'): ns3::PLC_NoiseSource::PLC_NoiseSource() [constructor]
    cls.add_constructor([])
    ## plc-noise.h (module 'plc'): ns3::PLC_NoiseSource::PLC_NoiseSource(ns3::Ptr<ns3::PLC_Node> src_node, ns3::Ptr<ns3::SpectrumValue> noisePsd, ns3::PLC_NoiseSource::NoiseSourceType type) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'src_node'), param('ns3::Ptr< ns3::SpectrumValue >', 'noisePsd'), param('ns3::PLC_NoiseSource::NoiseSourceType', 'type')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::Disable() [member function]
    cls.add_method('Disable', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-noise.h (module 'plc'): ns3::Ptr<ns3::PLC_Channel> ns3::PLC_NoiseSource::GetChannel() [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::PLC_Channel >', 
                   [])
    ## plc-noise.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_NoiseSource::GetNode() [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-noise.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue> ns3::PLC_NoiseSource::GetNoisePsd() [member function]
    cls.add_method('GetNoisePsd', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [])
    ## plc-noise.h (module 'plc'): ns3::PLC_NoiseSource::NoiseSourceType ns3::PLC_NoiseSource::GetNoiseSourceType() [member function]
    cls.add_method('GetNoiseSourceType', 
                   'ns3::PLC_NoiseSource::NoiseSourceType', 
                   [])
    ## plc-noise.h (module 'plc'): static ns3::TypeId ns3::PLC_NoiseSource::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::Init() [member function]
    cls.add_method('Init', 
                   'void', 
                   [])
    ## plc-noise.h (module 'plc'): bool ns3::PLC_NoiseSource::IsEnabled() [member function]
    cls.add_method('IsEnabled', 
                   'bool', 
                   [])
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::SetChannel(ns3::Ptr<ns3::PLC_Channel> channel) [member function]
    cls.add_method('SetChannel', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Channel >', 'channel')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::SetNode(ns3::Ptr<ns3::PLC_Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'node')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::SetNoisePsd(ns3::Ptr<ns3::SpectrumValue> psd) [member function]
    cls.add_method('SetNoisePsd', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue >', 'psd')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_NoiseSource::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_Outlet_methods(root_module, cls):
    ## plc-outlet.h (module 'plc'): ns3::PLC_Outlet::PLC_Outlet(ns3::PLC_Outlet const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Outlet const &', 'arg0')])
    ## plc-outlet.h (module 'plc'): ns3::PLC_Outlet::PLC_Outlet(ns3::Ptr<ns3::PLC_Node> node, ns3::Ptr<ns3::PLC_ValueBase> impedance=0) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'node'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'impedance', default_value='0')])
    ## plc-outlet.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_Outlet::GetImpedance() [member function]
    cls.add_method('GetImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-outlet.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_Outlet::GetNode() [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-outlet.h (module 'plc'): ns3::Ptr<ns3::PLC_RxInterface> ns3::PLC_Outlet::GetRxInterface() [member function]
    cls.add_method('GetRxInterface', 
                   'ns3::Ptr< ns3::PLC_RxInterface >', 
                   [])
    ## plc-outlet.h (module 'plc'): static ns3::TypeId ns3::PLC_Outlet::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-outlet.h (module 'plc'): bool ns3::PLC_Outlet::IsTimeVariant() [member function]
    cls.add_method('IsTimeVariant', 
                   'bool', 
                   [])
    ## plc-outlet.h (module 'plc'): void ns3::PLC_Outlet::Lock() const [member function]
    cls.add_method('Lock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-outlet.h (module 'plc'): void ns3::PLC_Outlet::RegisterBackboneBranch(ns3::Ptr<ns3::PLC_BackboneBranch> bb_branch) [member function]
    cls.add_method('RegisterBackboneBranch', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_BackboneBranch >', 'bb_branch')])
    ## plc-outlet.h (module 'plc'): void ns3::PLC_Outlet::SetImpedance(ns3::Ptr<ns3::PLC_ValueBase> impedance, bool updateImmediately=true) [member function]
    cls.add_method('SetImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'impedance'), param('bool', 'updateImmediately', default_value='true')])
    ## plc-outlet.h (module 'plc'): void ns3::PLC_Outlet::SetRxInterface(ns3::Ptr<ns3::PLC_RxInterface> interface) [member function]
    cls.add_method('SetRxInterface', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_RxInterface >', 'interface')])
    ## plc-outlet.h (module 'plc'): void ns3::PLC_Outlet::Unlock() const [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-outlet.h (module 'plc'): void ns3::PLC_Outlet::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_Phy_methods(root_module, cls):
    ## plc-phy.h (module 'plc'): ns3::PLC_Phy::PLC_Phy() [constructor]
    cls.add_constructor([])
    ## plc-phy.h (module 'plc'): ns3::PLC_Phy::PLC_Phy(ns3::PLC_Phy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Phy const &', 'arg0')])
    ## plc-phy.h (module 'plc'): ns3::PLC_ChannelTransferImpl * ns3::PLC_Phy::GetChannelTransferImpl(ns3::Ptr<ns3::PLC_Phy> rxPhy) [member function]
    cls.add_method('GetChannelTransferImpl', 
                   'ns3::PLC_ChannelTransferImpl *', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'rxPhy')])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_Phy::GetChannelTransferVector(ns3::Ptr<ns3::PLC_Phy> rxPhy) [member function]
    cls.add_method('GetChannelTransferVector', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'rxPhy')])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_Phy::GetNode() [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-phy.h (module 'plc'): static ns3::Time ns3::PLC_Phy::GetSymbolDuration() [member function]
    cls.add_method('GetSymbolDuration', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): static ns3::TypeId ns3::PLC_Phy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::NotifyFrameSent() [member function]
    cls.add_method('NotifyFrameSent', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::RxPsdChanged(uint32_t txId, ns3::Ptr<ns3::SpectrumValue> newRxPsd) [member function]
    cls.add_method('RxPsdChanged', 
                   'void', 
                   [param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue >', 'newRxPsd')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::SetFrameSentCallback(ns3::PLC_PhyFrameSentCallback c) [member function]
    cls.add_method('SetFrameSentCallback', 
                   'void', 
                   [param('ns3::PLC_PhyFrameSentCallback', 'c')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::SetReceiveErrorCallback(ns3::PhyRxEndErrorCallback c) [member function]
    cls.add_method('SetReceiveErrorCallback', 
                   'void', 
                   [param('ns3::PhyRxEndErrorCallback', 'c')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::SetReceiveSuccessCallback(ns3::PhyRxEndOkCallback c) [member function]
    cls.add_method('SetReceiveSuccessCallback', 
                   'void', 
                   [param('ns3::PhyRxEndOkCallback', 'c')])
    ## plc-phy.h (module 'plc'): static void ns3::PLC_Phy::SetSymbolDuration(ns3::Time tSymbol) [member function]
    cls.add_method('SetSymbolDuration', 
                   'void', 
                   [param('ns3::Time', 'tSymbol')], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::StartRx(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('StartRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')])
    ## plc-phy.h (module 'plc'): bool ns3::PLC_Phy::StartTx(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('StartTx', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): ns3::PLC_ChannelTransferImpl * ns3::PLC_Phy::DoGetChannelTransferImpl(ns3::Ptr<ns3::PLC_Phy> rxPhy) [member function]
    cls.add_method('DoGetChannelTransferImpl', 
                   'ns3::PLC_ChannelTransferImpl *', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'rxPhy')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::DoStartRx(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('DoStartRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_Phy::DoStartTx(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('DoStartTx', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_Phy::DoUpdateRxPsd(uint32_t txId, ns3::Ptr<ns3::SpectrumValue> newRxPsd) [member function]
    cls.add_method('DoUpdateRxPsd', 
                   'void', 
                   [param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue >', 'newRxPsd')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_PhyFrameControlHeader_methods(root_module, cls):
    ## plc-header.h (module 'plc'): ns3::PLC_PhyFrameControlHeader::PLC_PhyFrameControlHeader(ns3::PLC_PhyFrameControlHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_PhyFrameControlHeader const &', 'arg0')])
    ## plc-header.h (module 'plc'): ns3::PLC_PhyFrameControlHeader::PLC_PhyFrameControlHeader() [constructor]
    cls.add_constructor([])
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_PhyFrameControlHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## plc-header.h (module 'plc'): ns3::PLC_PhyFrameControlHeader::DelimiterType ns3::PLC_PhyFrameControlHeader::GetDelimiterType() [member function]
    cls.add_method('GetDelimiterType', 
                   'ns3::PLC_PhyFrameControlHeader::DelimiterType', 
                   [])
    ## plc-header.h (module 'plc'): uint8_t ns3::PLC_PhyFrameControlHeader::GetFccs() [member function]
    cls.add_method('GetFccs', 
                   'uint8_t', 
                   [])
    ## plc-header.h (module 'plc'): ns3::TypeId ns3::PLC_PhyFrameControlHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_PhyFrameControlHeader::GetPayloadMcs() [member function]
    cls.add_method('GetPayloadMcs', 
                   'ns3::ModulationAndCodingType', 
                   [])
    ## plc-header.h (module 'plc'): uint16_t ns3::PLC_PhyFrameControlHeader::GetPayloadSymbols() [member function]
    cls.add_method('GetPayloadSymbols', 
                   'uint16_t', 
                   [])
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_PhyFrameControlHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): static ns3::TypeId ns3::PLC_PhyFrameControlHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyFrameControlHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyFrameControlHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyFrameControlHeader::SetDelimiterType(ns3::PLC_PhyFrameControlHeader::DelimiterType type) [member function]
    cls.add_method('SetDelimiterType', 
                   'void', 
                   [param('ns3::PLC_PhyFrameControlHeader::DelimiterType', 'type')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyFrameControlHeader::SetFccs(uint8_t fccs) [member function]
    cls.add_method('SetFccs', 
                   'void', 
                   [param('uint8_t', 'fccs')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyFrameControlHeader::SetPayloadMcs(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetPayloadMcs', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyFrameControlHeader::SetPayloadSymbols(uint16_t symbols) [member function]
    cls.add_method('SetPayloadSymbols', 
                   'void', 
                   [param('uint16_t', 'symbols')])
    return

def register_Ns3PLC_PhyRatelessFrameControlHeader_methods(root_module, cls):
    ## plc-header.h (module 'plc'): ns3::PLC_PhyRatelessFrameControlHeader::PLC_PhyRatelessFrameControlHeader(ns3::PLC_PhyRatelessFrameControlHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_PhyRatelessFrameControlHeader const &', 'arg0')])
    ## plc-header.h (module 'plc'): ns3::PLC_PhyRatelessFrameControlHeader::PLC_PhyRatelessFrameControlHeader() [constructor]
    cls.add_constructor([])
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_PhyRatelessFrameControlHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## plc-header.h (module 'plc'): ns3::PLC_PhyRatelessFrameControlHeader::DelimiterType ns3::PLC_PhyRatelessFrameControlHeader::GetDelimiterType() [member function]
    cls.add_method('GetDelimiterType', 
                   'ns3::PLC_PhyRatelessFrameControlHeader::DelimiterType', 
                   [])
    ## plc-header.h (module 'plc'): uint8_t ns3::PLC_PhyRatelessFrameControlHeader::GetFccs() [member function]
    cls.add_method('GetFccs', 
                   'uint8_t', 
                   [])
    ## plc-header.h (module 'plc'): ns3::TypeId ns3::PLC_PhyRatelessFrameControlHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_PhyRatelessFrameControlHeader::GetNumBlocks() [member function]
    cls.add_method('GetNumBlocks', 
                   'uint32_t', 
                   [])
    ## plc-header.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_PhyRatelessFrameControlHeader::GetPayloadMcs() [member function]
    cls.add_method('GetPayloadMcs', 
                   'ns3::ModulationAndCodingType', 
                   [])
    ## plc-header.h (module 'plc'): uint16_t ns3::PLC_PhyRatelessFrameControlHeader::GetPayloadSymbols() [member function]
    cls.add_method('GetPayloadSymbols', 
                   'uint16_t', 
                   [])
    ## plc-header.h (module 'plc'): uint16_t ns3::PLC_PhyRatelessFrameControlHeader::GetPrngSeed() [member function]
    cls.add_method('GetPrngSeed', 
                   'uint16_t', 
                   [])
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_PhyRatelessFrameControlHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): static ns3::TypeId ns3::PLC_PhyRatelessFrameControlHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::SetDelimiterType(ns3::PLC_PhyRatelessFrameControlHeader::DelimiterType type) [member function]
    cls.add_method('SetDelimiterType', 
                   'void', 
                   [param('ns3::PLC_PhyRatelessFrameControlHeader::DelimiterType', 'type')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::SetFccs(uint8_t fccs) [member function]
    cls.add_method('SetFccs', 
                   'void', 
                   [param('uint8_t', 'fccs')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::SetNumBlocks(uint32_t num_blocks) [member function]
    cls.add_method('SetNumBlocks', 
                   'void', 
                   [param('uint32_t', 'num_blocks')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::SetPayloadMcs(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetPayloadMcs', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::SetPayloadSymbols(uint16_t symbols) [member function]
    cls.add_method('SetPayloadSymbols', 
                   'void', 
                   [param('uint16_t', 'symbols')])
    ## plc-header.h (module 'plc'): void ns3::PLC_PhyRatelessFrameControlHeader::SetPrngSeed(uint16_t prng_seed) [member function]
    cls.add_method('SetPrngSeed', 
                   'void', 
                   [param('uint16_t', 'prng_seed')])
    return

def register_Ns3PLC_Preamble_methods(root_module, cls):
    ## plc-header.h (module 'plc'): ns3::PLC_Preamble::PLC_Preamble(ns3::PLC_Preamble const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Preamble const &', 'arg0')])
    ## plc-header.h (module 'plc'): ns3::PLC_Preamble::PLC_Preamble() [constructor]
    cls.add_constructor([])
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_Preamble::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## plc-header.h (module 'plc'): static ns3::Time ns3::PLC_Preamble::GetDuration() [member function]
    cls.add_method('GetDuration', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## plc-header.h (module 'plc'): ns3::TypeId ns3::PLC_Preamble::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): uint32_t ns3::PLC_Preamble::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): static ns3::TypeId ns3::PLC_Preamble::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_Preamble::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): void ns3::PLC_Preamble::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## plc-header.h (module 'plc'): static void ns3::PLC_Preamble::SetDuration(ns3::Time duration) [member function]
    cls.add_method('SetDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')], 
                   is_static=True)
    return

def register_Ns3PLC_RxInterface_methods(root_module, cls):
    ## plc-interface.h (module 'plc'): ns3::PLC_RxInterface::PLC_RxInterface(ns3::PLC_RxInterface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_RxInterface const &', 'arg0')])
    ## plc-interface.h (module 'plc'): ns3::PLC_RxInterface::PLC_RxInterface(ns3::Ptr<ns3::PLC_Node> associated_node, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'associated_node'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-interface.h (module 'plc'): ns3::Ptr<ns3::PLC_Outlet> ns3::PLC_RxInterface::GetOutlet() [member function]
    cls.add_method('GetOutlet', 
                   'ns3::Ptr< ns3::PLC_Outlet >', 
                   [])
    ## plc-interface.h (module 'plc'): uint32_t ns3::PLC_RxInterface::GetRxIfIdx() const [member function]
    cls.add_method('GetRxIfIdx', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## plc-interface.h (module 'plc'): static ns3::TypeId ns3::PLC_RxInterface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::RxPsdChanged(uint32_t txId, ns3::Ptr<ns3::SpectrumValue> rxSignal) [member function]
    cls.add_method('RxPsdChanged', 
                   'void', 
                   [param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue >', 'rxSignal')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::SetIdx(uint32_t idx) [member function]
    cls.add_method('SetIdx', 
                   'void', 
                   [param('uint32_t', 'idx')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::SetOutlet(ns3::Ptr<ns3::PLC_Outlet> outlet) [member function]
    cls.add_method('SetOutlet', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Outlet >', 'outlet')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::StartRx(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('StartRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_RxInterface::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_SpectrumModelHelper_methods(root_module, cls):
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_SpectrumModelHelper::PLC_SpectrumModelHelper() [constructor]
    cls.add_constructor([])
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_SpectrumModelHelper::PLC_SpectrumModelHelper(ns3::PLC_SpectrumModelHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_SpectrumModelHelper const &', 'arg0')])
    ## plc-spectrum-helper.h (module 'plc'): double ns3::PLC_SpectrumModelHelper::GetCenterFreq() [member function]
    cls.add_method('GetCenterFreq', 
                   'double', 
                   [])
    ## plc-spectrum-helper.h (module 'plc'): ns3::Ptr<ns3::SpectrumModel const> ns3::PLC_SpectrumModelHelper::GetG3SpectrumModel() [member function]
    cls.add_method('GetG3SpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [])
    ## plc-spectrum-helper.h (module 'plc'): ns3::Ptr<ns3::SpectrumModel const> ns3::PLC_SpectrumModelHelper::GetSpectrumModel(double fl, double fh, size_t numbands) [member function]
    cls.add_method('GetSpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [param('double', 'fl'), param('double', 'fh'), param('size_t', 'numbands')])
    ## plc-spectrum-helper.h (module 'plc'): static ns3::TypeId ns3::PLC_SpectrumModelHelper::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_StaticNoiseSource_methods(root_module, cls):
    ## plc-noise.h (module 'plc'): ns3::PLC_StaticNoiseSource::PLC_StaticNoiseSource(ns3::PLC_StaticNoiseSource const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_StaticNoiseSource const &', 'arg0')])
    ## plc-noise.h (module 'plc'): ns3::PLC_StaticNoiseSource::PLC_StaticNoiseSource(ns3::Ptr<ns3::PLC_Node> src_node, ns3::Ptr<ns3::SpectrumValue> noisePsd) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'src_node'), param('ns3::Ptr< ns3::SpectrumValue >', 'noisePsd')])
    ## plc-noise.h (module 'plc'): static ns3::TypeId ns3::PLC_StaticNoiseSource::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-noise.h (module 'plc'): void ns3::PLC_StaticNoiseSource::Start(ns3::Time duration) [member function]
    cls.add_method('Start', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_StaticNoiseSource::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_ThreeCoreConcentricCable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_ThreeCoreConcentricCable::PLC_ThreeCoreConcentricCable(ns3::PLC_ThreeCoreConcentricCable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ThreeCoreConcentricCable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_ThreeCoreConcentricCable::PLC_ThreeCoreConcentricCable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_ThreeCoreConcentricCable::PLC_ThreeCoreConcentricCable(double eps_r, double kappa, double r_a, double r_i, double tand, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('double', 'eps_r'), param('double', 'kappa'), param('double', 'r_a'), param('double', 'r_i'), param('double', 'tand'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): ns3::PLC_ThreeCoreConcentricCable::PLC_ThreeCoreConcentricCable(ns3::PLC_FreqSelectiveRealValue eps_r, double kappa, double r_a, double r_i, ns3::PLC_FreqSelectiveRealValue tand, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::PLC_FreqSelectiveRealValue', 'eps_r'), param('double', 'kappa'), param('double', 'r_a'), param('double', 'r_i'), param('ns3::PLC_FreqSelectiveRealValue', 'tand'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_ThreeCoreConcentricCable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## plc-cable.h (module 'plc'): void ns3::PLC_ThreeCoreConcentricCable::Calculate(double eps_r, double kappa, double r_a, double r_i, double tand, ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [param('double', 'eps_r'), param('double', 'kappa'), param('double', 'r_a'), param('double', 'r_i'), param('double', 'tand'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_ThreeCoreConcentricCable::Calculate(ns3::PLC_FreqSelectiveRealValue eps_r, double kappa, double r_a, double r_i, ns3::PLC_FreqSelectiveRealValue tand, ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [param('ns3::PLC_FreqSelectiveRealValue', 'eps_r'), param('double', 'kappa'), param('double', 'r_a'), param('double', 'r_i'), param('ns3::PLC_FreqSelectiveRealValue', 'tand'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_ThreeCoreConcentricCable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_TimeInvariantSpectrumHelper_methods(root_module, cls):
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_TimeInvariantSpectrumHelper::PLC_TimeInvariantSpectrumHelper(ns3::PLC_TimeInvariantSpectrumHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TimeInvariantSpectrumHelper const &', 'arg0')])
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_TimeInvariantSpectrumHelper::PLC_TimeInvariantSpectrumHelper(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-spectrum-helper.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue> ns3::PLC_TimeInvariantSpectrumHelper::GetPowerSpectralDensity() [member function]
    cls.add_method('GetPowerSpectralDensity', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [])
    ## plc-spectrum-helper.h (module 'plc'): static ns3::TypeId ns3::PLC_TimeInvariantSpectrumHelper::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_TrxMetaInfo_methods(root_module, cls):
    ## plc-channel.h (module 'plc'): ns3::PLC_TrxMetaInfo::PLC_TrxMetaInfo(ns3::PLC_TrxMetaInfo const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TrxMetaInfo const &', 'arg0')])
    ## plc-channel.h (module 'plc'): ns3::PLC_TrxMetaInfo::PLC_TrxMetaInfo() [constructor]
    cls.add_constructor([])
    ## plc-channel.h (module 'plc'): ns3::Time ns3::PLC_TrxMetaInfo::GetHeaderDuration() const [member function]
    cls.add_method('GetHeaderDuration', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_TrxMetaInfo::GetHeaderMcs() const [member function]
    cls.add_method('GetHeaderMcs', 
                   'ns3::ModulationAndCodingType', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::Time ns3::PLC_TrxMetaInfo::GetPayloadDuration() const [member function]
    cls.add_method('GetPayloadDuration', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_TrxMetaInfo::GetPayloadMcs() const [member function]
    cls.add_method('GetPayloadMcs', 
                   'ns3::ModulationAndCodingType', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): static ns3::TypeId ns3::PLC_TrxMetaInfo::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::Packet const> ns3::PLC_TrxMetaInfo::GetUncodedMessage() const [member function]
    cls.add_method('GetUncodedMessage', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_TrxMetaInfo::SetHeaderDuration(ns3::Time duration) [member function]
    cls.add_method('SetHeaderDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_TrxMetaInfo::SetHeaderMcs(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetHeaderMcs', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_TrxMetaInfo::SetPayloadDuration(ns3::Time duration) [member function]
    cls.add_method('SetPayloadDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_TrxMetaInfo::SetPayloadMcs(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetPayloadMcs', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_TrxMetaInfo::SetUncodedMessage(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetUncodedMessage', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    return

def register_Ns3PLC_TwoPort_methods(root_module, cls):
    ## plc-edge.h (module 'plc'): ns3::PLC_TwoPort::PLC_TwoPort(ns3::PLC_TwoPort const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TwoPort const &', 'arg0')])
    ## plc-edge.h (module 'plc'): ns3::PLC_TwoPort::PLC_TwoPort(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::Ptr<ns3::PLC_Node> from, ns3::Ptr<ns3::PLC_Node> to, ns3::Ptr<ns3::PLC_ValueBase> A, ns3::Ptr<ns3::PLC_ValueBase> B, ns3::Ptr<ns3::PLC_ValueBase> C, ns3::Ptr<ns3::PLC_ValueBase> D) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::Ptr< ns3::PLC_Node >', 'from'), param('ns3::Ptr< ns3::PLC_Node >', 'to'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'A'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'B'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'C'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'D')])
    ## plc-edge.h (module 'plc'): static ns3::TypeId ns3::PLC_TwoPort::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_TwoPort::CalculateEdgeTransferFactor(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('CalculateEdgeTransferFactor', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')], 
                   visibility='private', is_virtual=True)
    ## plc-edge.h (module 'plc'): void ns3::PLC_TwoPort::CalculateInputImpedance(ns3::PLC_Node * dst_node) [member function]
    cls.add_method('CalculateInputImpedance', 
                   'void', 
                   [param('ns3::PLC_Node *', 'dst_node')], 
                   visibility='private', is_virtual=True)
    ## plc-edge.h (module 'plc'): double ns3::PLC_TwoPort::GetAttenuationApproxdB() [member function]
    cls.add_method('GetAttenuationApproxdB', 
                   'double', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-edge.h (module 'plc'): double ns3::PLC_TwoPort::GetIdealPropagationDelay() [member function]
    cls.add_method('GetIdealPropagationDelay', 
                   'double', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_TxInterface_methods(root_module, cls):
    ## plc-interface.h (module 'plc'): ns3::PLC_TxInterface::PLC_TxInterface(ns3::PLC_TxInterface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TxInterface const &', 'arg0')])
    ## plc-interface.h (module 'plc'): ns3::PLC_TxInterface::PLC_TxInterface(ns3::Ptr<ns3::PLC_Node> associated_plc_node, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'associated_plc_node'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-interface.h (module 'plc'): __gnu_cxx::__normal_iterator<ns3::Ptr<ns3::PLC_BackboneBranch>*,std::vector<ns3::Ptr<ns3::PLC_BackboneBranch>, std::allocator<ns3::Ptr<ns3::PLC_BackboneBranch> > > > ns3::PLC_TxInterface::BackbonePathBegin(ns3::PLC_RxInterface * sink) [member function]
    cls.add_method('BackbonePathBegin', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::PLC_BackboneBranch >, std::vector< ns3::Ptr< ns3::PLC_BackboneBranch > > >', 
                   [param('ns3::PLC_RxInterface *', 'sink')])
    ## plc-interface.h (module 'plc'): __gnu_cxx::__normal_iterator<ns3::Ptr<ns3::PLC_BackboneBranch>*,std::vector<ns3::Ptr<ns3::PLC_BackboneBranch>, std::allocator<ns3::Ptr<ns3::PLC_BackboneBranch> > > > ns3::PLC_TxInterface::BackbonePathEnd(ns3::PLC_RxInterface * sink) [member function]
    cls.add_method('BackbonePathEnd', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::PLC_BackboneBranch >, std::vector< ns3::Ptr< ns3::PLC_BackboneBranch > > >', 
                   [param('ns3::PLC_RxInterface *', 'sink')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::CalculateChannels() [member function]
    cls.add_method('CalculateChannels', 
                   'void', 
                   [])
    ## plc-interface.h (module 'plc'): std::list<ns3::PLC_BackboneBranch*,std::allocator<ns3::PLC_BackboneBranch*> > ns3::PLC_TxInterface::GetBackbonePath(ns3::PLC_RxInterface * sink) [member function]
    cls.add_method('GetBackbonePath', 
                   'std::list< ns3::PLC_BackboneBranch * >', 
                   [param('ns3::PLC_RxInterface *', 'sink')])
    ## plc-interface.h (module 'plc'): ns3::PLC_ChannelTransferImpl * ns3::PLC_TxInterface::GetChannelTransferImpl(ns3::PLC_RxInterface * rxInterface) [member function]
    cls.add_method('GetChannelTransferImpl', 
                   'ns3::PLC_ChannelTransferImpl *', 
                   [param('ns3::PLC_RxInterface *', 'rxInterface')])
    ## plc-interface.h (module 'plc'): uint32_t ns3::PLC_TxInterface::GetTxIfIdx() const [member function]
    cls.add_method('GetTxIfIdx', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## plc-interface.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue const> ns3::PLC_TxInterface::GetTxPsd() [member function]
    cls.add_method('GetTxPsd', 
                   'ns3::Ptr< ns3::SpectrumValue const >', 
                   [])
    ## plc-interface.h (module 'plc'): static ns3::TypeId ns3::PLC_TxInterface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::InitializeChannelTransferImpls() [member function]
    cls.add_method('InitializeChannelTransferImpls', 
                   'void', 
                   [])
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::SetIdx(uint32_t idx) [member function]
    cls.add_method('SetIdx', 
                   'void', 
                   [param('uint32_t', 'idx')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::StartTx(ns3::Ptr<ns3::Packet const> p, ns3::Ptr<ns3::SpectrumValue const> txPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('StartTx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ptr< ns3::SpectrumValue const >', 'txPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')])
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-interface.h (module 'plc'): void ns3::PLC_TxInterface::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_ValueBase_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## plc-value.h (module 'plc'): ns3::PLC_ValueBase::PLC_ValueBase(ns3::PLC_ValueBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ValueBase const &', 'arg0')])
    ## plc-value.h (module 'plc'): ns3::PLC_ValueBase::PLC_ValueBase() [constructor]
    cls.add_constructor([])
    ## plc-value.h (module 'plc'): ns3::PLC_ValueBase::PLC_ValueBase(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_ValueBase::PLC_ValueType type) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_ValueBase::PLC_ValueType', 'type')])
    ## plc-value.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_ValueBase::Copy() [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-value.h (module 'plc'): size_t ns3::PLC_ValueBase::GetNumBands() const [member function]
    cls.add_method('GetNumBands', 
                   'size_t', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): ns3::Ptr<ns3::SpectrumModel const> ns3::PLC_ValueBase::GetSpectrumModel() const [member function]
    cls.add_method('GetSpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): static ns3::TypeId ns3::PLC_ValueBase::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-value.h (module 'plc'): ns3::PLC_ValueBase::PLC_ValueType ns3::PLC_ValueBase::GetValueType() const [member function]
    cls.add_method('GetValueType', 
                   'ns3::PLC_ValueBase::PLC_ValueType', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): bool ns3::PLC_ValueBase::IsTimeVariant() const [member function]
    cls.add_method('IsTimeVariant', 
                   'bool', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): void ns3::PLC_ValueBase::Lock() const [member function]
    cls.add_method('Lock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): void ns3::PLC_ValueBase::Unlock() const [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): void ns3::PLC_ValueBase::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3PacketBurst_methods(root_module, cls):
    ## packet-burst.h (module 'network'): ns3::PacketBurst::PacketBurst(ns3::PacketBurst const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketBurst const &', 'arg0')])
    ## packet-burst.h (module 'network'): ns3::PacketBurst::PacketBurst() [constructor]
    cls.add_constructor([])
    ## packet-burst.h (module 'network'): void ns3::PacketBurst::AddPacket(ns3::Ptr<ns3::Packet> packet) [member function]
    cls.add_method('AddPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet')])
    ## packet-burst.h (module 'network'): std::_List_const_iterator<ns3::Ptr<ns3::Packet> > ns3::PacketBurst::Begin() const [member function]
    cls.add_method('Begin', 
                   'std::_List_const_iterator< ns3::Ptr< ns3::Packet > >', 
                   [], 
                   is_const=True)
    ## packet-burst.h (module 'network'): ns3::Ptr<ns3::PacketBurst> ns3::PacketBurst::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::PacketBurst >', 
                   [], 
                   is_const=True)
    ## packet-burst.h (module 'network'): std::_List_const_iterator<ns3::Ptr<ns3::Packet> > ns3::PacketBurst::End() const [member function]
    cls.add_method('End', 
                   'std::_List_const_iterator< ns3::Ptr< ns3::Packet > >', 
                   [], 
                   is_const=True)
    ## packet-burst.h (module 'network'): uint32_t ns3::PacketBurst::GetNPackets() const [member function]
    cls.add_method('GetNPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet-burst.h (module 'network'): std::list<ns3::Ptr<ns3::Packet>, std::allocator<ns3::Ptr<ns3::Packet> > > ns3::PacketBurst::GetPackets() const [member function]
    cls.add_method('GetPackets', 
                   'std::list< ns3::Ptr< ns3::Packet > >', 
                   [], 
                   is_const=True)
    ## packet-burst.h (module 'network'): uint32_t ns3::PacketBurst::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet-burst.h (module 'network'): static ns3::TypeId ns3::PacketBurst::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## packet-burst.h (module 'network'): void ns3::PacketBurst::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3ParetoVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(ns3::ParetoVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ParetoVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(double m) [constructor]
    cls.add_constructor([param('double', 'm')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(double m, double s) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(double m, double s, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's'), param('double', 'b')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(std::pair<double,double> params) [constructor]
    cls.add_constructor([param('std::pair< double, double >', 'params')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(std::pair<double,double> params, double b) [constructor]
    cls.add_constructor([param('std::pair< double, double >', 'params'), param('double', 'b')])
    return

def register_Ns3Scheduler_methods(root_module, cls):
    ## scheduler.h (module 'core'): ns3::Scheduler::Scheduler() [constructor]
    cls.add_constructor([])
    ## scheduler.h (module 'core'): ns3::Scheduler::Scheduler(ns3::Scheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scheduler const &', 'arg0')])
    ## scheduler.h (module 'core'): static ns3::TypeId ns3::Scheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## scheduler.h (module 'core'): void ns3::Scheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## scheduler.h (module 'core'): bool ns3::Scheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## scheduler.h (module 'core'): ns3::Scheduler::Event ns3::Scheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## scheduler.h (module 'core'): void ns3::Scheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## scheduler.h (module 'core'): ns3::Scheduler::Event ns3::Scheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3SchedulerEvent_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    ## scheduler.h (module 'core'): ns3::Scheduler::Event::Event() [constructor]
    cls.add_constructor([])
    ## scheduler.h (module 'core'): ns3::Scheduler::Event::Event(ns3::Scheduler::Event const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scheduler::Event const &', 'arg0')])
    ## scheduler.h (module 'core'): ns3::Scheduler::Event::impl [variable]
    cls.add_instance_attribute('impl', 'ns3::EventImpl *', is_const=False)
    ## scheduler.h (module 'core'): ns3::Scheduler::Event::key [variable]
    cls.add_instance_attribute('key', 'ns3::Scheduler::EventKey', is_const=False)
    return

def register_Ns3SchedulerEventKey_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    ## scheduler.h (module 'core'): ns3::Scheduler::EventKey::EventKey() [constructor]
    cls.add_constructor([])
    ## scheduler.h (module 'core'): ns3::Scheduler::EventKey::EventKey(ns3::Scheduler::EventKey const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scheduler::EventKey const &', 'arg0')])
    ## scheduler.h (module 'core'): ns3::Scheduler::EventKey::m_context [variable]
    cls.add_instance_attribute('m_context', 'uint32_t', is_const=False)
    ## scheduler.h (module 'core'): ns3::Scheduler::EventKey::m_ts [variable]
    cls.add_instance_attribute('m_ts', 'uint64_t', is_const=False)
    ## scheduler.h (module 'core'): ns3::Scheduler::EventKey::m_uid [variable]
    cls.add_instance_attribute('m_uid', 'uint32_t', is_const=False)
    return

def register_Ns3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter< ns3::AttributeAccessor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter< ns3::AttributeChecker > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter< ns3::AttributeValue > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::SimpleRefCount(ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter< ns3::CallbackImplBase > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::SimpleRefCount(ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter< ns3::EventImpl > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::SimpleRefCount(ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter< ns3::NixVector > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3PLC_ColoredNoiseFloor_Ns3Empty_Ns3DefaultDeleter__lt__ns3PLC_ColoredNoiseFloor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter< ns3::PLC_ColoredNoiseFloor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::PLC_ColoredNoiseFloor, ns3::empty, ns3::DefaultDeleter<ns3::PLC_ColoredNoiseFloor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter< ns3::Packet > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3SpectrumModel_Ns3Empty_Ns3DefaultDeleter__lt__ns3SpectrumModel__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> >::SimpleRefCount(ns3::SimpleRefCount<ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter< ns3::SpectrumModel > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::SpectrumModel, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumModel> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3SpectrumValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3SpectrumValue__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> >::SimpleRefCount(ns3::SimpleRefCount<ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter< ns3::SpectrumValue > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::SpectrumValue, ns3::empty, ns3::DefaultDeleter<ns3::SpectrumValue> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3SystemThread_Ns3Empty_Ns3DefaultDeleter__lt__ns3SystemThread__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> >::SimpleRefCount(ns3::SimpleRefCount<ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::SystemThread, ns3::empty, ns3::DefaultDeleter< ns3::SystemThread > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::SystemThread, ns3::empty, ns3::DefaultDeleter<ns3::SystemThread> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter< ns3::TraceSourceAccessor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimulatorImpl_methods(root_module, cls):
    ## simulator-impl.h (module 'core'): ns3::SimulatorImpl::SimulatorImpl() [constructor]
    cls.add_constructor([])
    ## simulator-impl.h (module 'core'): ns3::SimulatorImpl::SimulatorImpl(ns3::SimulatorImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SimulatorImpl const &', 'arg0')])
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::Cancel(ns3::EventId const & ev) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): uint32_t ns3::SimulatorImpl::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): ns3::Time ns3::SimulatorImpl::GetDelayLeft(ns3::EventId const & id) const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): ns3::Time ns3::SimulatorImpl::GetMaximumSimulationTime() const [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): uint32_t ns3::SimulatorImpl::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): static ns3::TypeId ns3::SimulatorImpl::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## simulator-impl.h (module 'core'): bool ns3::SimulatorImpl::IsExpired(ns3::EventId const & ev) const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): bool ns3::SimulatorImpl::IsFinished() const [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): ns3::Time ns3::SimulatorImpl::Now() const [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::Remove(ns3::EventId const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::Run() [member function]
    cls.add_method('Run', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): ns3::EventId ns3::SimulatorImpl::Schedule(ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): ns3::EventId ns3::SimulatorImpl::ScheduleDestroy(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleDestroy', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): ns3::EventId ns3::SimulatorImpl::ScheduleNow(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleNow', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::ScheduleWithContext(uint32_t context, ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h (module 'core'): void ns3::SimulatorImpl::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3SpectrumModel_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## spectrum-model.h (module 'spectrum'): ns3::SpectrumModel::SpectrumModel(ns3::SpectrumModel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SpectrumModel const &', 'arg0')])
    ## spectrum-model.h (module 'spectrum'): ns3::SpectrumModel::SpectrumModel(std::vector<double, std::allocator<double> > centerFreqs) [constructor]
    cls.add_constructor([param('std::vector< double >', 'centerFreqs')])
    ## spectrum-model.h (module 'spectrum'): ns3::SpectrumModel::SpectrumModel(ns3::Bands bands) [constructor]
    cls.add_constructor([param('ns3::Bands', 'bands')])
    ## spectrum-model.h (module 'spectrum'): __gnu_cxx::__normal_iterator<const ns3::BandInfo*,std::vector<ns3::BandInfo, std::allocator<ns3::BandInfo> > > ns3::SpectrumModel::Begin() const [member function]
    cls.add_method('Begin', 
                   '__gnu_cxx::__normal_iterator< ns3::BandInfo const *, std::vector< ns3::BandInfo > >', 
                   [], 
                   is_const=True)
    ## spectrum-model.h (module 'spectrum'): __gnu_cxx::__normal_iterator<const ns3::BandInfo*,std::vector<ns3::BandInfo, std::allocator<ns3::BandInfo> > > ns3::SpectrumModel::End() const [member function]
    cls.add_method('End', 
                   '__gnu_cxx::__normal_iterator< ns3::BandInfo const *, std::vector< ns3::BandInfo > >', 
                   [], 
                   is_const=True)
    ## spectrum-model.h (module 'spectrum'): size_t ns3::SpectrumModel::GetNumBands() const [member function]
    cls.add_method('GetNumBands', 
                   'size_t', 
                   [], 
                   is_const=True)
    ## spectrum-model.h (module 'spectrum'): ns3::SpectrumModelUid_t ns3::SpectrumModel::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'ns3::SpectrumModelUid_t', 
                   [], 
                   is_const=True)
    return

def register_Ns3SpectrumValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('-', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('ns3::SpectrumValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('ns3::SpectrumValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('ns3::SpectrumValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::SpectrumValue'], root_module['ns3::SpectrumValue'], param('ns3::SpectrumValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::SpectrumValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('double', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::SpectrumValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('double', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::SpectrumValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('double', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::SpectrumValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('double', 'right'))
    ## spectrum-value.h (module 'spectrum'): ns3::SpectrumValue::SpectrumValue(ns3::SpectrumValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SpectrumValue const &', 'arg0')])
    ## spectrum-value.h (module 'spectrum'): ns3::SpectrumValue::SpectrumValue(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## spectrum-value.h (module 'spectrum'): ns3::SpectrumValue::SpectrumValue() [constructor]
    cls.add_constructor([])
    ## spectrum-value.h (module 'spectrum'): __gnu_cxx::__normal_iterator<const ns3::BandInfo*,std::vector<ns3::BandInfo, std::allocator<ns3::BandInfo> > > ns3::SpectrumValue::ConstBandsBegin() const [member function]
    cls.add_method('ConstBandsBegin', 
                   '__gnu_cxx::__normal_iterator< ns3::BandInfo const *, std::vector< ns3::BandInfo > >', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): __gnu_cxx::__normal_iterator<const ns3::BandInfo*,std::vector<ns3::BandInfo, std::allocator<ns3::BandInfo> > > ns3::SpectrumValue::ConstBandsEnd() const [member function]
    cls.add_method('ConstBandsEnd', 
                   '__gnu_cxx::__normal_iterator< ns3::BandInfo const *, std::vector< ns3::BandInfo > >', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): __gnu_cxx::__normal_iterator<const double*,std::vector<double, std::allocator<double> > > ns3::SpectrumValue::ConstValuesBegin() const [member function]
    cls.add_method('ConstValuesBegin', 
                   '__gnu_cxx::__normal_iterator< double const *, std::vector< double > >', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): __gnu_cxx::__normal_iterator<const double*,std::vector<double, std::allocator<double> > > ns3::SpectrumValue::ConstValuesEnd() const [member function]
    cls.add_method('ConstValuesEnd', 
                   '__gnu_cxx::__normal_iterator< double const *, std::vector< double > >', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): ns3::Ptr<ns3::SpectrumValue> ns3::SpectrumValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): ns3::Ptr<ns3::SpectrumModel const> ns3::SpectrumValue::GetSpectrumModel() const [member function]
    cls.add_method('GetSpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): ns3::SpectrumModelUid_t ns3::SpectrumValue::GetSpectrumModelUid() const [member function]
    cls.add_method('GetSpectrumModelUid', 
                   'ns3::SpectrumModelUid_t', 
                   [], 
                   is_const=True)
    ## spectrum-value.h (module 'spectrum'): __gnu_cxx::__normal_iterator<double*,std::vector<double, std::allocator<double> > > ns3::SpectrumValue::ValuesBegin() [member function]
    cls.add_method('ValuesBegin', 
                   '__gnu_cxx::__normal_iterator< double *, std::vector< double > >', 
                   [])
    ## spectrum-value.h (module 'spectrum'): __gnu_cxx::__normal_iterator<double*,std::vector<double, std::allocator<double> > > ns3::SpectrumValue::ValuesEnd() [member function]
    cls.add_method('ValuesEnd', 
                   '__gnu_cxx::__normal_iterator< double *, std::vector< double > >', 
                   [])
    return

def register_Ns3SystemThread_methods(root_module, cls):
    ## system-thread.h (module 'core'): ns3::SystemThread::SystemThread(ns3::SystemThread const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SystemThread const &', 'arg0')])
    ## system-thread.h (module 'core'): ns3::SystemThread::SystemThread(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [constructor]
    cls.add_constructor([param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')])
    ## system-thread.h (module 'core'): static bool ns3::SystemThread::Equals(pthread_t id) [member function]
    cls.add_method('Equals', 
                   'bool', 
                   [param('pthread_t', 'id')], 
                   is_static=True)
    ## system-thread.h (module 'core'): void ns3::SystemThread::Join() [member function]
    cls.add_method('Join', 
                   'void', 
                   [])
    ## system-thread.h (module 'core'): static pthread_t ns3::SystemThread::Self() [member function]
    cls.add_method('Self', 
                   'pthread_t', 
                   [], 
                   is_static=True)
    ## system-thread.h (module 'core'): void ns3::SystemThread::Start() [member function]
    cls.add_method('Start', 
                   'void', 
                   [])
    return

def register_Ns3Time_methods(root_module, cls):
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('+=', param('ns3::Time const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::Time const &', 'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    cls.add_binary_numeric_operator('-', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    ## nstime.h (module 'core'): ns3::Time::Time() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::Time::Time(ns3::Time const & o) [copy constructor]
    cls.add_constructor([param('ns3::Time const &', 'o')])
    ## nstime.h (module 'core'): ns3::Time::Time(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long int v) [constructor]
    cls.add_constructor([param('long int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long long int v) [constructor]
    cls.add_constructor([param('long long int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(unsigned int v) [constructor]
    cls.add_constructor([param('unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long unsigned int v) [constructor]
    cls.add_constructor([param('long unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long long unsigned int v) [constructor]
    cls.add_constructor([param('long long unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(std::string const & s) [constructor]
    cls.add_constructor([param('std::string const &', 's')])
    ## nstime.h (module 'core'): ns3::Time::Time(ns3::int64x64_t const & value) [constructor]
    cls.add_constructor([param('ns3::int64x64_t const &', 'value')])
    ## nstime.h (module 'core'): int ns3::Time::Compare(ns3::Time const & o) const [member function]
    cls.add_method('Compare', 
                   'int', 
                   [param('ns3::Time const &', 'o')], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::From(ns3::int64x64_t const & from, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('From', 
                   'ns3::Time', 
                   [param('ns3::int64x64_t const &', 'from'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::From(ns3::int64x64_t const & value) [member function]
    cls.add_method('From', 
                   'ns3::Time', 
                   [param('ns3::int64x64_t const &', 'value')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::FromDouble(double value, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('FromDouble', 
                   'ns3::Time', 
                   [param('double', 'value'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::FromInteger(uint64_t value, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('FromInteger', 
                   'ns3::Time', 
                   [param('uint64_t', 'value'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h (module 'core'): double ns3::Time::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetFemtoSeconds() const [member function]
    cls.add_method('GetFemtoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetInteger() const [member function]
    cls.add_method('GetInteger', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetMicroSeconds() const [member function]
    cls.add_method('GetMicroSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetMilliSeconds() const [member function]
    cls.add_method('GetMilliSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetNanoSeconds() const [member function]
    cls.add_method('GetNanoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetPicoSeconds() const [member function]
    cls.add_method('GetPicoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time::Unit ns3::Time::GetResolution() [member function]
    cls.add_method('GetResolution', 
                   'ns3::Time::Unit', 
                   [], 
                   is_static=True)
    ## nstime.h (module 'core'): double ns3::Time::GetSeconds() const [member function]
    cls.add_method('GetSeconds', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetTimeStep() const [member function]
    cls.add_method('GetTimeStep', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsNegative() const [member function]
    cls.add_method('IsNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsPositive() const [member function]
    cls.add_method('IsPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsStrictlyNegative() const [member function]
    cls.add_method('IsStrictlyNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsStrictlyPositive() const [member function]
    cls.add_method('IsStrictlyPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsZero() const [member function]
    cls.add_method('IsZero', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): static void ns3::Time::SetResolution(ns3::Time::Unit resolution) [member function]
    cls.add_method('SetResolution', 
                   'void', 
                   [param('ns3::Time::Unit', 'resolution')], 
                   is_static=True)
    ## nstime.h (module 'core'): ns3::int64x64_t ns3::Time::To(ns3::Time::Unit timeUnit) const [member function]
    cls.add_method('To', 
                   'ns3::int64x64_t', 
                   [param('ns3::Time::Unit', 'timeUnit')], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::ToDouble(ns3::Time::Unit timeUnit) const [member function]
    cls.add_method('ToDouble', 
                   'double', 
                   [param('ns3::Time::Unit', 'timeUnit')], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::ToInteger(ns3::Time::Unit timeUnit) const [member function]
    cls.add_method('ToInteger', 
                   'int64_t', 
                   [param('ns3::Time::Unit', 'timeUnit')], 
                   is_const=True)
    return

def register_Ns3TraceSourceAccessor_methods(root_module, cls):
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor::TraceSourceAccessor(ns3::TraceSourceAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TraceSourceAccessor const &', 'arg0')])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor::TraceSourceAccessor() [constructor]
    cls.add_constructor([])
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::Connect(ns3::ObjectBase * obj, std::string context, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('Connect', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::ConnectWithoutContext(ns3::ObjectBase * obj, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('ConnectWithoutContext', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::Disconnect(ns3::ObjectBase * obj, std::string context, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('Disconnect', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::DisconnectWithoutContext(ns3::ObjectBase * obj, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('DisconnectWithoutContext', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3Trailer_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## trailer.h (module 'network'): ns3::Trailer::Trailer() [constructor]
    cls.add_constructor([])
    ## trailer.h (module 'network'): ns3::Trailer::Trailer(ns3::Trailer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Trailer const &', 'arg0')])
    ## trailer.h (module 'network'): uint32_t ns3::Trailer::Deserialize(ns3::Buffer::Iterator end) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'end')], 
                   is_pure_virtual=True, is_virtual=True)
    ## trailer.h (module 'network'): uint32_t ns3::Trailer::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trailer.h (module 'network'): static ns3::TypeId ns3::Trailer::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## trailer.h (module 'network'): void ns3::Trailer::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trailer.h (module 'network'): void ns3::Trailer::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeAccessor_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeAccessor::AttributeAccessor(ns3::AttributeAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeAccessor const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeAccessor::AttributeAccessor() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::Get(ns3::ObjectBase const * object, ns3::AttributeValue & attribute) const [member function]
    cls.add_method('Get', 
                   'bool', 
                   [param('ns3::ObjectBase const *', 'object'), param('ns3::AttributeValue &', 'attribute')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::HasGetter() const [member function]
    cls.add_method('HasGetter', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::HasSetter() const [member function]
    cls.add_method('HasSetter', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::Set(ns3::ObjectBase * object, ns3::AttributeValue const & value) const [member function]
    cls.add_method('Set', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'object', transfer_ownership=False), param('ns3::AttributeValue const &', 'value')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeChecker_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeChecker::AttributeChecker(ns3::AttributeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeChecker const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeChecker::AttributeChecker() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::Copy(ns3::AttributeValue const & source, ns3::AttributeValue & destination) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'source'), param('ns3::AttributeValue &', 'destination')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeChecker::CreateValidValue(ns3::AttributeValue const & value) const [member function]
    cls.add_method('CreateValidValue', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeValue_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeValue::AttributeValue(ns3::AttributeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeValue const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeValue::AttributeValue() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_pure_virtual=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3BooleanChecker_methods(root_module, cls):
    ## boolean.h (module 'core'): ns3::BooleanChecker::BooleanChecker() [constructor]
    cls.add_constructor([])
    ## boolean.h (module 'core'): ns3::BooleanChecker::BooleanChecker(ns3::BooleanChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::BooleanChecker const &', 'arg0')])
    return

def register_Ns3BooleanValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## boolean.h (module 'core'): ns3::BooleanValue::BooleanValue(ns3::BooleanValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::BooleanValue const &', 'arg0')])
    ## boolean.h (module 'core'): ns3::BooleanValue::BooleanValue() [constructor]
    cls.add_constructor([])
    ## boolean.h (module 'core'): ns3::BooleanValue::BooleanValue(bool value) [constructor]
    cls.add_constructor([param('bool', 'value')])
    ## boolean.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::BooleanValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## boolean.h (module 'core'): bool ns3::BooleanValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## boolean.h (module 'core'): bool ns3::BooleanValue::Get() const [member function]
    cls.add_method('Get', 
                   'bool', 
                   [], 
                   is_const=True)
    ## boolean.h (module 'core'): std::string ns3::BooleanValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## boolean.h (module 'core'): void ns3::BooleanValue::Set(bool value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('bool', 'value')])
    return

def register_Ns3CallbackChecker_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackChecker::CallbackChecker() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackChecker::CallbackChecker(ns3::CallbackChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackChecker const &', 'arg0')])
    return

def register_Ns3CallbackImplBase_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackImplBase::CallbackImplBase() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackImplBase::CallbackImplBase(ns3::CallbackImplBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackImplBase const &', 'arg0')])
    ## callback.h (module 'core'): bool ns3::CallbackImplBase::IsEqual(ns3::Ptr<ns3::CallbackImplBase const> other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ptr< ns3::CallbackImplBase const >', 'other')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3CallbackValue_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue(ns3::CallbackValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackValue const &', 'arg0')])
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue(ns3::CallbackBase const & base) [constructor]
    cls.add_constructor([param('ns3::CallbackBase const &', 'base')])
    ## callback.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::CallbackValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## callback.h (module 'core'): bool ns3::CallbackValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## callback.h (module 'core'): std::string ns3::CallbackValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## callback.h (module 'core'): void ns3::CallbackValue::Set(ns3::CallbackBase base) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::CallbackBase', 'base')])
    return

def register_Ns3Channel_methods(root_module, cls):
    ## channel.h (module 'network'): ns3::Channel::Channel(ns3::Channel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Channel const &', 'arg0')])
    ## channel.h (module 'network'): ns3::Channel::Channel() [constructor]
    cls.add_constructor([])
    ## channel.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Channel::GetDevice(uint32_t i) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'i')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## channel.h (module 'network'): uint32_t ns3::Channel::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## channel.h (module 'network'): uint32_t ns3::Channel::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## channel.h (module 'network'): static ns3::TypeId ns3::Channel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3DataRateChecker_methods(root_module, cls):
    ## data-rate.h (module 'network'): ns3::DataRateChecker::DataRateChecker() [constructor]
    cls.add_constructor([])
    ## data-rate.h (module 'network'): ns3::DataRateChecker::DataRateChecker(ns3::DataRateChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DataRateChecker const &', 'arg0')])
    return

def register_Ns3DataRateValue_methods(root_module, cls):
    ## data-rate.h (module 'network'): ns3::DataRateValue::DataRateValue() [constructor]
    cls.add_constructor([])
    ## data-rate.h (module 'network'): ns3::DataRateValue::DataRateValue(ns3::DataRateValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DataRateValue const &', 'arg0')])
    ## data-rate.h (module 'network'): ns3::DataRateValue::DataRateValue(ns3::DataRate const & value) [constructor]
    cls.add_constructor([param('ns3::DataRate const &', 'value')])
    ## data-rate.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::DataRateValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## data-rate.h (module 'network'): bool ns3::DataRateValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## data-rate.h (module 'network'): ns3::DataRate ns3::DataRateValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::DataRate', 
                   [], 
                   is_const=True)
    ## data-rate.h (module 'network'): std::string ns3::DataRateValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## data-rate.h (module 'network'): void ns3::DataRateValue::Set(ns3::DataRate const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::DataRate const &', 'value')])
    return

def register_Ns3DoubleValue_methods(root_module, cls):
    ## double.h (module 'core'): ns3::DoubleValue::DoubleValue() [constructor]
    cls.add_constructor([])
    ## double.h (module 'core'): ns3::DoubleValue::DoubleValue(ns3::DoubleValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DoubleValue const &', 'arg0')])
    ## double.h (module 'core'): ns3::DoubleValue::DoubleValue(double const & value) [constructor]
    cls.add_constructor([param('double const &', 'value')])
    ## double.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::DoubleValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## double.h (module 'core'): bool ns3::DoubleValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## double.h (module 'core'): double ns3::DoubleValue::Get() const [member function]
    cls.add_method('Get', 
                   'double', 
                   [], 
                   is_const=True)
    ## double.h (module 'core'): std::string ns3::DoubleValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## double.h (module 'core'): void ns3::DoubleValue::Set(double const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('double const &', 'value')])
    return

def register_Ns3EmptyAttributeValue_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue::EmptyAttributeValue(ns3::EmptyAttributeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmptyAttributeValue const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue::EmptyAttributeValue() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EmptyAttributeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   visibility='private', is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::EmptyAttributeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, visibility='private', is_virtual=True)
    return

def register_Ns3EnumChecker_methods(root_module, cls):
    ## enum.h (module 'core'): ns3::EnumChecker::EnumChecker(ns3::EnumChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EnumChecker const &', 'arg0')])
    ## enum.h (module 'core'): ns3::EnumChecker::EnumChecker() [constructor]
    cls.add_constructor([])
    ## enum.h (module 'core'): void ns3::EnumChecker::Add(int v, std::string name) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('int', 'v'), param('std::string', 'name')])
    ## enum.h (module 'core'): void ns3::EnumChecker::AddDefault(int v, std::string name) [member function]
    cls.add_method('AddDefault', 
                   'void', 
                   [param('int', 'v'), param('std::string', 'name')])
    ## enum.h (module 'core'): bool ns3::EnumChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumChecker::Copy(ns3::AttributeValue const & src, ns3::AttributeValue & dst) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'src'), param('ns3::AttributeValue &', 'dst')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EnumChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): std::string ns3::EnumChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): std::string ns3::EnumChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3EnumValue_methods(root_module, cls):
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue(ns3::EnumValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EnumValue const &', 'arg0')])
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue() [constructor]
    cls.add_constructor([])
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## enum.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EnumValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## enum.h (module 'core'): int ns3::EnumValue::Get() const [member function]
    cls.add_method('Get', 
                   'int', 
                   [], 
                   is_const=True)
    ## enum.h (module 'core'): std::string ns3::EnumValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): void ns3::EnumValue::Set(int v) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('int', 'v')])
    return

def register_Ns3EventImpl_methods(root_module, cls):
    ## event-impl.h (module 'core'): ns3::EventImpl::EventImpl(ns3::EventImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventImpl const &', 'arg0')])
    ## event-impl.h (module 'core'): ns3::EventImpl::EventImpl() [constructor]
    cls.add_constructor([])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [])
    ## event-impl.h (module 'core'): bool ns3::EventImpl::IsCancelled() [member function]
    cls.add_method('IsCancelled', 
                   'bool', 
                   [])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Notify() [member function]
    cls.add_method('Notify', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3IntegerValue_methods(root_module, cls):
    ## integer.h (module 'core'): ns3::IntegerValue::IntegerValue() [constructor]
    cls.add_constructor([])
    ## integer.h (module 'core'): ns3::IntegerValue::IntegerValue(ns3::IntegerValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntegerValue const &', 'arg0')])
    ## integer.h (module 'core'): ns3::IntegerValue::IntegerValue(int64_t const & value) [constructor]
    cls.add_constructor([param('int64_t const &', 'value')])
    ## integer.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::IntegerValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## integer.h (module 'core'): bool ns3::IntegerValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## integer.h (module 'core'): int64_t ns3::IntegerValue::Get() const [member function]
    cls.add_method('Get', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## integer.h (module 'core'): std::string ns3::IntegerValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## integer.h (module 'core'): void ns3::IntegerValue::Set(int64_t const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('int64_t const &', 'value')])
    return

def register_Ns3Ipv4AddressChecker_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker::Ipv4AddressChecker() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker::Ipv4AddressChecker(ns3::Ipv4AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4AddressChecker const &', 'arg0')])
    return

def register_Ns3Ipv4AddressValue_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue(ns3::Ipv4AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4AddressValue const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue(ns3::Ipv4Address const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address const &', 'value')])
    ## ipv4-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv4AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): std::string ns3::Ipv4AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4AddressValue::Set(ns3::Ipv4Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'value')])
    return

def register_Ns3Ipv4MaskChecker_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker::Ipv4MaskChecker() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker::Ipv4MaskChecker(ns3::Ipv4MaskChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MaskChecker const &', 'arg0')])
    return

def register_Ns3Ipv4MaskValue_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue(ns3::Ipv4MaskValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MaskValue const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue(ns3::Ipv4Mask const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv4Mask const &', 'value')])
    ## ipv4-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv4MaskValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4MaskValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask ns3::Ipv4MaskValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): std::string ns3::Ipv4MaskValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4MaskValue::Set(ns3::Ipv4Mask const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv4Mask const &', 'value')])
    return

def register_Ns3Ipv6AddressChecker_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker::Ipv6AddressChecker() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker::Ipv6AddressChecker(ns3::Ipv6AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6AddressChecker const &', 'arg0')])
    return

def register_Ns3Ipv6AddressValue_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue(ns3::Ipv6AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6AddressValue const &', 'arg0')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue(ns3::Ipv6Address const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address const &', 'value')])
    ## ipv6-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv6AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address ns3::Ipv6AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): std::string ns3::Ipv6AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6AddressValue::Set(ns3::Ipv6Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv6Address const &', 'value')])
    return

def register_Ns3Ipv6PrefixChecker_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker::Ipv6PrefixChecker() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker::Ipv6PrefixChecker(ns3::Ipv6PrefixChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6PrefixChecker const &', 'arg0')])
    return

def register_Ns3Ipv6PrefixValue_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue(ns3::Ipv6PrefixValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6PrefixValue const &', 'arg0')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue(ns3::Ipv6Prefix const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const &', 'value')])
    ## ipv6-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv6PrefixValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6PrefixValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix ns3::Ipv6PrefixValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): std::string ns3::Ipv6PrefixValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6PrefixValue::Set(ns3::Ipv6Prefix const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv6Prefix const &', 'value')])
    return

def register_Ns3Mac48AddressChecker_methods(root_module, cls):
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker::Mac48AddressChecker() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker::Mac48AddressChecker(ns3::Mac48AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48AddressChecker const &', 'arg0')])
    return

def register_Ns3Mac48AddressValue_methods(root_module, cls):
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue(ns3::Mac48AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48AddressValue const &', 'arg0')])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue(ns3::Mac48Address const & value) [constructor]
    cls.add_constructor([param('ns3::Mac48Address const &', 'value')])
    ## mac48-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Mac48AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## mac48-address.h (module 'network'): ns3::Mac48Address ns3::Mac48AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): std::string ns3::Mac48AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## mac48-address.h (module 'network'): void ns3::Mac48AddressValue::Set(ns3::Mac48Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Mac48Address const &', 'value')])
    return

def register_Ns3NetDevice_methods(root_module, cls):
    ## net-device.h (module 'network'): ns3::NetDevice::NetDevice() [constructor]
    cls.add_constructor([])
    ## net-device.h (module 'network'): ns3::NetDevice::NetDevice(ns3::NetDevice const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NetDevice const &', 'arg0')])
    ## net-device.h (module 'network'): void ns3::NetDevice::AddLinkChangeCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [member function]
    cls.add_method('AddLinkChangeCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Channel> ns3::NetDevice::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::Channel >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): uint32_t ns3::NetDevice::GetIfIndex() const [member function]
    cls.add_method('GetIfIndex', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): uint16_t ns3::NetDevice::GetMtu() const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetMulticast(ns3::Ipv4Address multicastGroup) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv4Address', 'multicastGroup')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetMulticast(ns3::Ipv6Address addr) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Node> ns3::NetDevice::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): static ns3::TypeId ns3::NetDevice::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsBridge() const [member function]
    cls.add_method('IsBridge', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsLinkUp() const [member function]
    cls.add_method('IsLinkUp', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsPointToPoint() const [member function]
    cls.add_method('IsPointToPoint', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::NeedsArp() const [member function]
    cls.add_method('NeedsArp', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::Send(ns3::Ptr<ns3::Packet> packet, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('Send', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SendFrom(ns3::Ptr<ns3::Packet> packet, ns3::Address const & source, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('SendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetAddress(ns3::Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Address', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetIfIndex(uint32_t const index) [member function]
    cls.add_method('SetIfIndex', 
                   'void', 
                   [param('uint32_t const', 'index')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SetMtu(uint16_t const mtu) [member function]
    cls.add_method('SetMtu', 
                   'bool', 
                   [param('uint16_t const', 'mtu')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetPromiscReceiveCallback(ns3::Callback<bool, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetPromiscReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetReceiveCallback(ns3::Callback<bool, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SupportsSendFrom() const [member function]
    cls.add_method('SupportsSendFrom', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3NixVector_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## nix-vector.h (module 'network'): ns3::NixVector::NixVector() [constructor]
    cls.add_constructor([])
    ## nix-vector.h (module 'network'): ns3::NixVector::NixVector(ns3::NixVector const & o) [copy constructor]
    cls.add_constructor([param('ns3::NixVector const &', 'o')])
    ## nix-vector.h (module 'network'): void ns3::NixVector::AddNeighborIndex(uint32_t newBits, uint32_t numberOfBits) [member function]
    cls.add_method('AddNeighborIndex', 
                   'void', 
                   [param('uint32_t', 'newBits'), param('uint32_t', 'numberOfBits')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::BitCount(uint32_t numberOfNeighbors) const [member function]
    cls.add_method('BitCount', 
                   'uint32_t', 
                   [param('uint32_t', 'numberOfNeighbors')], 
                   is_const=True)
    ## nix-vector.h (module 'network'): ns3::Ptr<ns3::NixVector> ns3::NixVector::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::NixVector >', 
                   [], 
                   is_const=True)
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::Deserialize(uint32_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint32_t const *', 'buffer'), param('uint32_t', 'size')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::ExtractNeighborIndex(uint32_t numberOfBits) [member function]
    cls.add_method('ExtractNeighborIndex', 
                   'uint32_t', 
                   [param('uint32_t', 'numberOfBits')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::GetRemainingBits() [member function]
    cls.add_method('GetRemainingBits', 
                   'uint32_t', 
                   [])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::Serialize(uint32_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint32_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3Node_methods(root_module, cls):
    ## node.h (module 'network'): ns3::Node::Node(ns3::Node const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Node const &', 'arg0')])
    ## node.h (module 'network'): ns3::Node::Node() [constructor]
    cls.add_constructor([])
    ## node.h (module 'network'): ns3::Node::Node(uint32_t systemId) [constructor]
    cls.add_constructor([param('uint32_t', 'systemId')])
    ## node.h (module 'network'): uint32_t ns3::Node::AddApplication(ns3::Ptr<ns3::Application> application) [member function]
    cls.add_method('AddApplication', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::Application >', 'application')])
    ## node.h (module 'network'): uint32_t ns3::Node::AddDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddDevice', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## node.h (module 'network'): static bool ns3::Node::ChecksumEnabled() [member function]
    cls.add_method('ChecksumEnabled', 
                   'bool', 
                   [], 
                   is_static=True)
    ## node.h (module 'network'): ns3::Ptr<ns3::Application> ns3::Node::GetApplication(uint32_t index) const [member function]
    cls.add_method('GetApplication', 
                   'ns3::Ptr< ns3::Application >', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## node.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Node::GetDevice(uint32_t index) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetNApplications() const [member function]
    cls.add_method('GetNApplications', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): static ns3::TypeId ns3::Node::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## node.h (module 'network'): void ns3::Node::RegisterDeviceAdditionListener(ns3::Callback<void,ns3::Ptr<ns3::NetDevice>,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> listener) [member function]
    cls.add_method('RegisterDeviceAdditionListener', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'listener')])
    ## node.h (module 'network'): void ns3::Node::RegisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler, uint16_t protocolType, ns3::Ptr<ns3::NetDevice> device, bool promiscuous=false) [member function]
    cls.add_method('RegisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler'), param('uint16_t', 'protocolType'), param('ns3::Ptr< ns3::NetDevice >', 'device'), param('bool', 'promiscuous', default_value='false')])
    ## node.h (module 'network'): void ns3::Node::UnregisterDeviceAdditionListener(ns3::Callback<void,ns3::Ptr<ns3::NetDevice>,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> listener) [member function]
    cls.add_method('UnregisterDeviceAdditionListener', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'listener')])
    ## node.h (module 'network'): void ns3::Node::UnregisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler) [member function]
    cls.add_method('UnregisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler')])
    ## node.h (module 'network'): void ns3::Node::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## node.h (module 'network'): void ns3::Node::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectFactoryChecker_methods(root_module, cls):
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker::ObjectFactoryChecker() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker::ObjectFactoryChecker(ns3::ObjectFactoryChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactoryChecker const &', 'arg0')])
    return

def register_Ns3ObjectFactoryValue_methods(root_module, cls):
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue(ns3::ObjectFactoryValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactoryValue const &', 'arg0')])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue(ns3::ObjectFactory const & value) [constructor]
    cls.add_constructor([param('ns3::ObjectFactory const &', 'value')])
    ## object-factory.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::ObjectFactoryValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## object-factory.h (module 'core'): bool ns3::ObjectFactoryValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## object-factory.h (module 'core'): ns3::ObjectFactory ns3::ObjectFactoryValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::ObjectFactory', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): std::string ns3::ObjectFactoryValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## object-factory.h (module 'core'): void ns3::ObjectFactoryValue::Set(ns3::ObjectFactory const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::ObjectFactory const &', 'value')])
    return

def register_Ns3PLC_AL3x95XLPE_Cable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_AL3x95XLPE_Cable::PLC_AL3x95XLPE_Cable(ns3::PLC_AL3x95XLPE_Cable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_AL3x95XLPE_Cable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_AL3x95XLPE_Cable::PLC_AL3x95XLPE_Cable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_AL3x95XLPE_Cable::PLC_AL3x95XLPE_Cable(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_AL3x95XLPE_Cable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_AL3x95XLPE_Cable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_ArqMac_methods(root_module, cls):
    ## plc-mac.h (module 'plc'): ns3::PLC_ArqMac::PLC_ArqMac(ns3::PLC_ArqMac const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ArqMac const &', 'arg0')])
    ## plc-mac.h (module 'plc'): ns3::PLC_ArqMac::PLC_ArqMac() [constructor]
    cls.add_constructor([])
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::AcknowledgementTimeout() [member function]
    cls.add_method('AcknowledgementTimeout', 
                   'void', 
                   [])
    ## plc-mac.h (module 'plc'): size_t ns3::PLC_ArqMac::GetMaxReplays() [member function]
    cls.add_method('GetMaxReplays', 
                   'size_t', 
                   [])
    ## plc-mac.h (module 'plc'): ns3::Time ns3::PLC_ArqMac::GetTimeout() [member function]
    cls.add_method('GetTimeout', 
                   'ns3::Time', 
                   [])
    ## plc-mac.h (module 'plc'): static ns3::TypeId ns3::PLC_ArqMac::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::NotifyCcaConfirm(ns3::PLC_PhyCcaResult status) [member function]
    cls.add_method('NotifyCcaConfirm', 
                   'void', 
                   [param('ns3::PLC_PhyCcaResult', 'status')], 
                   is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::NotifyCsmaCaConfirm(ns3::PLC_CsmaCaState state) [member function]
    cls.add_method('NotifyCsmaCaConfirm', 
                   'void', 
                   [param('ns3::PLC_CsmaCaState', 'state')], 
                   is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::NotifyTransmissionEnd() [member function]
    cls.add_method('NotifyTransmissionEnd', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::SetMaxReplays(size_t max_replays) [member function]
    cls.add_method('SetMaxReplays', 
                   'void', 
                   [param('size_t', 'max_replays')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::SetTimeout(ns3::Time timeout) [member function]
    cls.add_method('SetTimeout', 
                   'void', 
                   [param('ns3::Time', 'timeout')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): ns3::Ptr<ns3::PLC_Phy> ns3::PLC_ArqMac::DoGetPhy() [member function]
    cls.add_method('DoGetPhy', 
                   'ns3::Ptr< ns3::PLC_Phy >', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::DoProcess(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('DoProcess', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): bool ns3::PLC_ArqMac::DoSendFrom(ns3::Ptr<ns3::Packet> p, ns3::Mac48Address src, ns3::Mac48Address dst) [member function]
    cls.add_method('DoSendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Mac48Address', 'src'), param('ns3::Mac48Address', 'dst')], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::DoSetPhy(ns3::Ptr<ns3::PLC_Phy> phy) [member function]
    cls.add_method('DoSetPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'phy')], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_ArqMac::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_Channel_methods(root_module, cls):
    ## plc-channel.h (module 'plc'): ns3::PLC_Channel::PLC_Channel(ns3::PLC_Channel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_Channel const &', 'arg0')])
    ## plc-channel.h (module 'plc'): ns3::PLC_Channel::PLC_Channel() [constructor]
    cls.add_constructor([])
    ## plc-channel.h (module 'plc'): ns3::PLC_Channel::PLC_Channel(ns3::Ptr<ns3::PLC_Graph> graph) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Graph >', 'graph')])
    ## plc-channel.h (module 'plc'): uint32_t ns3::PLC_Channel::AddDevice(ns3::Ptr<ns3::NetDevice> arg0) [member function]
    cls.add_method('AddDevice', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'arg0')])
    ## plc-channel.h (module 'plc'): uint32_t ns3::PLC_Channel::AddRxInterface(ns3::Ptr<ns3::PLC_RxInterface> rxInterface) [member function]
    cls.add_method('AddRxInterface', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::PLC_RxInterface >', 'rxInterface')])
    ## plc-channel.h (module 'plc'): uint32_t ns3::PLC_Channel::AddTxInterface(ns3::Ptr<ns3::PLC_TxInterface> txInterface) [member function]
    cls.add_method('AddTxInterface', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::PLC_TxInterface >', 'txInterface')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::CalcTransmissionChannels() [member function]
    cls.add_method('CalcTransmissionChannels', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::DeleteOutOfDatePSDs(ns3::Ptr<ns3::PLC_TxInterface> tx, ns3::Ptr<ns3::PLC_RxInterface> rx) [member function]
    cls.add_method('DeleteOutOfDatePSDs', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_TxInterface >', 'tx'), param('ns3::Ptr< ns3::PLC_RxInterface >', 'rx')])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_Channel::GetChannelTransferData(uint32_t txId, uint32_t rxId) [member function]
    cls.add_method('GetChannelTransferData', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [param('uint32_t', 'txId'), param('uint32_t', 'rxId')])
    ## plc-channel.h (module 'plc'): ns3::Timeslot ns3::PLC_Channel::GetCurrentTimeslot() [member function]
    cls.add_method('GetCurrentTimeslot', 
                   'ns3::Timeslot', 
                   [])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::NetDevice> ns3::PLC_Channel::GetDevice(uint32_t i) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_Graph> ns3::PLC_Channel::GetGraph() [member function]
    cls.add_method('GetGraph', 
                   'ns3::Ptr< ns3::PLC_Graph >', 
                   [])
    ## plc-channel.h (module 'plc'): uint32_t ns3::PLC_Channel::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-channel.h (module 'plc'): uint32_t ns3::PLC_Channel::GetNRxInterfaces() const [member function]
    cls.add_method('GetNRxInterfaces', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): uint32_t ns3::PLC_Channel::GetNTxInterfaces() const [member function]
    cls.add_method('GetNTxInterfaces', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::Time ns3::PLC_Channel::GetRemainingSlotTime(ns3::Time t) [member function]
    cls.add_method('GetRemainingSlotTime', 
                   'ns3::Time', 
                   [param('ns3::Time', 't')])
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_RxInterface> ns3::PLC_Channel::GetRxInterface(uint32_t i) const [member function]
    cls.add_method('GetRxInterface', 
                   'ns3::Ptr< ns3::PLC_RxInterface >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): ns3::Ptr<ns3::PLC_TxInterface> ns3::PLC_Channel::GetTxInterface(uint32_t i) const [member function]
    cls.add_method('GetTxInterface', 
                   'ns3::Ptr< ns3::PLC_TxInterface >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): static ns3::TypeId ns3::PLC_Channel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::InitTransmissionChannels() [member function]
    cls.add_method('InitTransmissionChannels', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::Lock() const [member function]
    cls.add_method('Lock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::ProcessTimeslotTasks(ns3::Timeslot timeslot) [member function]
    cls.add_method('ProcessTimeslotTasks', 
                   'void', 
                   [param('ns3::Timeslot', 'timeslot')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::PropagationCompleteEvent(uint32_t txId) [member function]
    cls.add_method('PropagationCompleteEvent', 
                   'void', 
                   [param('uint32_t', 'txId')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::ScheduleNextTimeslotTasks() [member function]
    cls.add_method('ScheduleNextTimeslotTasks', 
                   'void', 
                   [])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::SetGraph(ns3::Ptr<ns3::PLC_Graph> graph) [member function]
    cls.add_method('SetGraph', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Graph >', 'graph')])
    ## plc-channel.h (module 'plc'): bool ns3::PLC_Channel::TransmissionEnd(uint32_t txId, ns3::Time propagation_delay) [member function]
    cls.add_method('TransmissionEnd', 
                   'bool', 
                   [param('uint32_t', 'txId'), param('ns3::Time', 'propagation_delay')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::TransmissionStart(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue const> txPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('TransmissionStart', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue const >', 'txPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::Unlock() const [member function]
    cls.add_method('Unlock', 
                   'void', 
                   [], 
                   is_const=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::UpdateReceivePSDs(ns3::Timeslot timeslot, bool channel_changed=false) [member function]
    cls.add_method('UpdateReceivePSDs', 
                   'void', 
                   [param('ns3::Timeslot', 'timeslot'), param('bool', 'channel_changed', default_value='false')])
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-channel.h (module 'plc'): void ns3::PLC_Channel::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_ColoredNoiseFloor_methods(root_module, cls):
    ## plc-noise.h (module 'plc'): ns3::PLC_ColoredNoiseFloor::PLC_ColoredNoiseFloor(ns3::PLC_ColoredNoiseFloor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ColoredNoiseFloor const &', 'arg0')])
    ## plc-noise.h (module 'plc'): ns3::PLC_ColoredNoiseFloor::PLC_ColoredNoiseFloor(double a, double b, double c, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('double', 'a'), param('double', 'b'), param('double', 'c'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-noise.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue> ns3::PLC_ColoredNoiseFloor::GetNoisePsd() [member function]
    cls.add_method('GetNoisePsd', 
                   'ns3::Ptr< ns3::SpectrumValue >', 
                   [])
    return

def register_Ns3PLC_ConstValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('double', 'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_ConstValue'], root_module['ns3::PLC_ConstValue'], param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('double', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('double', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('double', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_ConstValue const &', 'right'))
    ## plc-value.h (module 'plc'): ns3::PLC_ConstValue::PLC_ConstValue() [constructor]
    cls.add_constructor([])
    ## plc-value.h (module 'plc'): ns3::PLC_ConstValue::PLC_ConstValue(ns3::Ptr<ns3::SpectrumModel const> sm, double real) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('double', 'real')])
    ## plc-value.h (module 'plc'): ns3::PLC_ConstValue::PLC_ConstValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_Value value=std::complex<double>(0.0, 0.0)) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_Value', 'value', default_value='std::complex<double>(0.0, 0.0)')])
    ## plc-value.h (module 'plc'): ns3::PLC_ConstValue::PLC_ConstValue(ns3::PLC_ConstValue const & value) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): static ns3::TypeId ns3::PLC_ConstValue::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-value.h (module 'plc'): std::complex<double> ns3::PLC_ConstValue::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'std::complex< double >', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): void ns3::PLC_ConstValue::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_ErrorRateModel_methods(root_module, cls):
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_ErrorRateModel::PLC_ErrorRateModel(ns3::PLC_ErrorRateModel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ErrorRateModel const &', 'arg0')])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_ErrorRateModel::PLC_ErrorRateModel() [constructor]
    cls.add_constructor([])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_ErrorRateModel::PLC_ErrorRateModel(ns3::Time block_duration) [constructor]
    cls.add_constructor([param('ns3::Time', 'block_duration')])
    ## plc-link-performance-model.h (module 'plc'): ns3::Time ns3::PLC_ErrorRateModel::GetBlockDuration() [member function]
    cls.add_method('GetBlockDuration', 
                   'ns3::Time', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): static ns3::TypeId ns3::PLC_ErrorRateModel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_ErrorRateModel::SetBlockDuration(ns3::Time duration) [member function]
    cls.add_method('SetBlockDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_ErrorRateModel::SetChannelCondition(ns3::PLC_ErrorRateModel::ChannelCondition cond) [member function]
    cls.add_method('SetChannelCondition', 
                   'void', 
                   [param('ns3::PLC_ErrorRateModel::ChannelCondition', 'cond')])
    ## plc-link-performance-model.h (module 'plc'): bool ns3::PLC_ErrorRateModel::DoEndRx() [member function]
    cls.add_method('DoEndRx', 
                   'bool', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_ErrorRateModel::DoEvaluateChunk() [member function]
    cls.add_method('DoEvaluateChunk', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_ErrorRateModel::DoStartRx(double requiredInformationBits) [member function]
    cls.add_method('DoStartRx', 
                   'void', 
                   [param('double', 'requiredInformationBits')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_FreqSelectiveValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('double', 'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_FreqSelectiveValue'], root_module['ns3::PLC_FreqSelectiveValue'], param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('double', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('double', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('double', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue::PLC_FreqSelectiveValue() [constructor]
    cls.add_constructor([])
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_Value value=std::complex<double>(0.0, 0.0)) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_Value', 'value', default_value='std::complex<double>(0.0, 0.0)')])
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_ValueSpectrum const & values) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_ValueSpectrum const &', 'values')])
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, double R, double Q, double f_0) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('double', 'R'), param('double', 'Q'), param('double', 'f_0')])
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(ns3::PLC_ConstValue const & value) [constructor]
    cls.add_constructor([param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): ns3::PLC_FreqSelectiveValue::PLC_FreqSelectiveValue(ns3::PLC_FreqSelectiveValue const & value) [copy constructor]
    cls.add_constructor([param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): static ns3::TypeId ns3::PLC_FreqSelectiveValue::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-value.h (module 'plc'): ns3::PLC_ValueSpectrum ns3::PLC_FreqSelectiveValue::GetValues() const [member function]
    cls.add_method('GetValues', 
                   'ns3::PLC_ValueSpectrum', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): ns3::PLC_ValueSpectrum * ns3::PLC_FreqSelectiveValue::GetValuesRef() [member function]
    cls.add_method('GetValuesRef', 
                   'ns3::PLC_ValueSpectrum *', 
                   [])
    ## plc-value.h (module 'plc'): void ns3::PLC_FreqSelectiveValue::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_HalfDuplexOfdmPhy_methods(root_module, cls):
    ## plc-phy.h (module 'plc'): ns3::PLC_HalfDuplexOfdmPhy::PLC_HalfDuplexOfdmPhy(ns3::PLC_HalfDuplexOfdmPhy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_HalfDuplexOfdmPhy const &', 'arg0')])
    ## plc-phy.h (module 'plc'): ns3::PLC_HalfDuplexOfdmPhy::PLC_HalfDuplexOfdmPhy() [constructor]
    cls.add_constructor([])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::CancelCca() [member function]
    cls.add_method('CancelCca', 
                   'void', 
                   [])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::CcaRequest() [member function]
    cls.add_method('CcaRequest', 
                   'void', 
                   [])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::ChangeState(ns3::PLC_HalfDuplexOfdmPhy::State newState) [member function]
    cls.add_method('ChangeState', 
                   'void', 
                   [param('ns3::PLC_HalfDuplexOfdmPhy::State', 'newState')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::CreateInterfaces(ns3::Ptr<ns3::PLC_Outlet> outlet, ns3::Ptr<ns3::SpectrumValue> txPsd, ns3::Ptr<ns3::PLC_ValueBase> rxImpedance=0, ns3::Ptr<ns3::PLC_ValueBase> txImpedance=0) [member function]
    cls.add_method('CreateInterfaces', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Outlet >', 'outlet'), param('ns3::Ptr< ns3::SpectrumValue >', 'txPsd'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'rxImpedance', default_value='0'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'txImpedance', default_value='0')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::EndCca() [member function]
    cls.add_method('EndCca', 
                   'void', 
                   [])
    ## plc-phy.h (module 'plc'): static ns3::Time ns3::PLC_HalfDuplexOfdmPhy::GetGuardIntervalDuration() [member function]
    cls.add_method('GetGuardIntervalDuration', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_Outlet> ns3::PLC_HalfDuplexOfdmPhy::GetOutlet() [member function]
    cls.add_method('GetOutlet', 
                   'ns3::Ptr< ns3::PLC_Outlet >', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_HalfDuplexOfdmPhy::GetRxImpedance() [member function]
    cls.add_method('GetRxImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_RxInterface> ns3::PLC_HalfDuplexOfdmPhy::GetRxInterface() [member function]
    cls.add_method('GetRxInterface', 
                   'ns3::Ptr< ns3::PLC_RxInterface >', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_HalfDuplexOfdmPhy::GetShuntImpedance() [member function]
    cls.add_method('GetShuntImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::PLC_HalfDuplexOfdmPhy::State ns3::PLC_HalfDuplexOfdmPhy::GetState() [member function]
    cls.add_method('GetState', 
                   'ns3::PLC_HalfDuplexOfdmPhy::State', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_HalfDuplexOfdmPhy::GetTxImpedance() [member function]
    cls.add_method('GetTxImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::PLC_TxInterface> ns3::PLC_HalfDuplexOfdmPhy::GetTxInterface() [member function]
    cls.add_method('GetTxInterface', 
                   'ns3::Ptr< ns3::PLC_TxInterface >', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::SpectrumValue const> ns3::PLC_HalfDuplexOfdmPhy::GetTxPowerSpectralDensity() [member function]
    cls.add_method('GetTxPowerSpectralDensity', 
                   'ns3::Ptr< ns3::SpectrumValue const >', 
                   [])
    ## plc-phy.h (module 'plc'): static ns3::TypeId ns3::PLC_HalfDuplexOfdmPhy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_HalfDuplexOfdmPhy::IsBusy() [member function]
    cls.add_method('IsBusy', 
                   'bool', 
                   [])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SetCcaConfirmCallback(ns3::PLC_PhyCcaConfirmCallback c) [member function]
    cls.add_method('SetCcaConfirmCallback', 
                   'void', 
                   [param('ns3::PLC_PhyCcaConfirmCallback', 'c')])
    ## plc-phy.h (module 'plc'): static void ns3::PLC_HalfDuplexOfdmPhy::SetGuardIntervalDuration(ns3::Time duration) [member function]
    cls.add_method('SetGuardIntervalDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [member function]
    cls.add_method('SetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SetRxImpedance(ns3::Ptr<ns3::PLC_ValueBase> rxImpedance) [member function]
    cls.add_method('SetRxImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'rxImpedance')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SetShuntImpedance(ns3::Ptr<ns3::PLC_ValueBase> shuntImpedance) [member function]
    cls.add_method('SetShuntImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'shuntImpedance')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SetTxImpedance(ns3::Ptr<ns3::PLC_ValueBase> txImpedance) [member function]
    cls.add_method('SetTxImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'txImpedance')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SetTxPowerSpectralDensity(ns3::Ptr<ns3::SpectrumValue> txPsd) [member function]
    cls.add_method('SetTxPowerSpectralDensity', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue >', 'txPsd')])
    ## plc-phy.h (module 'plc'): ns3::Time ns3::PLC_HalfDuplexOfdmPhy::CalculateTxDuration(size_t nSymbols) [member function]
    cls.add_method('CalculateTxDuration', 
                   'ns3::Time', 
                   [param('size_t', 'nSymbols')], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): ns3::PLC_PhyCcaResult ns3::PLC_HalfDuplexOfdmPhy::ClearChannelAssessment() [member function]
    cls.add_method('ClearChannelAssessment', 
                   'ns3::PLC_PhyCcaResult', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::ComputeEquivalentImpedances() [member function]
    cls.add_method('ComputeEquivalentImpedances', 
                   'void', 
                   [], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): ns3::PLC_ChannelTransferImpl * ns3::PLC_HalfDuplexOfdmPhy::DoGetChannelTransferImpl(ns3::Ptr<ns3::PLC_Phy> rxPhy) [member function]
    cls.add_method('DoGetChannelTransferImpl', 
                   'ns3::PLC_ChannelTransferImpl *', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'rxPhy')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::DoSetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [member function]
    cls.add_method('DoSetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_HalfDuplexOfdmPhy::SwitchImpedance(ns3::PLC_HalfDuplexOfdmPhy::State state) [member function]
    cls.add_method('SwitchImpedance', 
                   'void', 
                   [param('ns3::PLC_HalfDuplexOfdmPhy::State', 'state')], 
                   visibility='protected')
    return

def register_Ns3PLC_HarqMac_methods(root_module, cls):
    ## plc-mac.h (module 'plc'): ns3::PLC_HarqMac::PLC_HarqMac(ns3::PLC_HarqMac const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_HarqMac const &', 'arg0')])
    ## plc-mac.h (module 'plc'): ns3::PLC_HarqMac::PLC_HarqMac() [constructor]
    cls.add_constructor([])
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::AcknowledgementTimeout() [member function]
    cls.add_method('AcknowledgementTimeout', 
                   'void', 
                   [])
    ## plc-mac.h (module 'plc'): ns3::Time ns3::PLC_HarqMac::GetAcknowledgementTimeout() [member function]
    cls.add_method('GetAcknowledgementTimeout', 
                   'ns3::Time', 
                   [])
    ## plc-mac.h (module 'plc'): size_t ns3::PLC_HarqMac::GetMaxRedundancyFrames() [member function]
    cls.add_method('GetMaxRedundancyFrames', 
                   'size_t', 
                   [])
    ## plc-mac.h (module 'plc'): static ns3::TypeId ns3::PLC_HarqMac::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::NotifyCcaConfirm(ns3::PLC_PhyCcaResult status) [member function]
    cls.add_method('NotifyCcaConfirm', 
                   'void', 
                   [param('ns3::PLC_PhyCcaResult', 'status')], 
                   is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::NotifyCsmaCaConfirm(ns3::PLC_CsmaCaState state) [member function]
    cls.add_method('NotifyCsmaCaConfirm', 
                   'void', 
                   [param('ns3::PLC_CsmaCaState', 'state')], 
                   is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::NotifyTransmissionEnd() [member function]
    cls.add_method('NotifyTransmissionEnd', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::SetAcknowledgementTimeout(ns3::Time timeout) [member function]
    cls.add_method('SetAcknowledgementTimeout', 
                   'void', 
                   [param('ns3::Time', 'timeout')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::SetMaxRedundancyFrames(size_t max_frames) [member function]
    cls.add_method('SetMaxRedundancyFrames', 
                   'void', 
                   [param('size_t', 'max_frames')])
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): ns3::Ptr<ns3::PLC_Phy> ns3::PLC_HarqMac::DoGetPhy() [member function]
    cls.add_method('DoGetPhy', 
                   'ns3::Ptr< ns3::PLC_Phy >', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::DoProcess(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('DoProcess', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): bool ns3::PLC_HarqMac::DoSendFrom(ns3::Ptr<ns3::Packet> p, ns3::Mac48Address src, ns3::Mac48Address dst) [member function]
    cls.add_method('DoSendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Mac48Address', 'src'), param('ns3::Mac48Address', 'dst')], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::DoSetPhy(ns3::Ptr<ns3::PLC_Phy> phy) [member function]
    cls.add_method('DoSetPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'phy')], 
                   visibility='private', is_virtual=True)
    ## plc-mac.h (module 'plc'): void ns3::PLC_HarqMac::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_ImpulseNoiseSource_methods(root_module, cls):
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulseNoiseSource::PLC_ImpulseNoiseSource(ns3::PLC_ImpulseNoiseSource const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ImpulseNoiseSource const &', 'arg0')])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulseNoiseSource::PLC_ImpulseNoiseSource() [constructor]
    cls.add_constructor([])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulseNoiseSource::PLC_ImpulseNoiseSource(ns3::Ptr<ns3::PLC_Node> m_src_node, ns3::Ptr<ns3::SpectrumValue> noisePsd, double p) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'm_src_node'), param('ns3::Ptr< ns3::SpectrumValue >', 'noisePsd'), param('double', 'p')])
    ## plc-noise.h (module 'plc'): double ns3::PLC_ImpulseNoiseSource::GetProbability() [member function]
    cls.add_method('GetProbability', 
                   'double', 
                   [])
    ## plc-noise.h (module 'plc'): static ns3::TypeId ns3::PLC_ImpulseNoiseSource::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-noise.h (module 'plc'): void ns3::PLC_ImpulseNoiseSource::SetProbability(double p) [member function]
    cls.add_method('SetProbability', 
                   'void', 
                   [param('double', 'p')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_ImpulseNoiseSource::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_ImpulsiveNoiseSource_methods(root_module, cls):
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource(ns3::PLC_ImpulsiveNoiseSource const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ImpulsiveNoiseSource const &', 'arg0')])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource() [constructor]
    cls.add_constructor([])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource(ns3::Ptr<ns3::PLC_Node> m_src_node, ns3::Ptr<ns3::SpectrumValue> noisePsd) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'm_src_node'), param('ns3::Ptr< ns3::SpectrumValue >', 'noisePsd')])
    ## plc-noise.h (module 'plc'): ns3::PLC_ImpulsiveNoiseSource::PLC_ImpulsiveNoiseSource(ns3::Ptr<ns3::PLC_Node> src_node, ns3::Ptr<ns3::SpectrumValue> noisePsd, ns3::RandomVariable * pulselen_gen, ns3::RandomVariable * pulsegap_gen) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::PLC_Node >', 'src_node'), param('ns3::Ptr< ns3::SpectrumValue >', 'noisePsd'), param('ns3::RandomVariable *', 'pulselen_gen'), param('ns3::RandomVariable *', 'pulsegap_gen')])
    ## plc-noise.h (module 'plc'): void ns3::PLC_ImpulsiveNoiseSource::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-noise.h (module 'plc'): static ns3::TypeId ns3::PLC_ImpulsiveNoiseSource::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-noise.h (module 'plc'): void ns3::PLC_ImpulsiveNoiseSource::PulseEnd() [member function]
    cls.add_method('PulseEnd', 
                   'void', 
                   [])
    ## plc-noise.h (module 'plc'): void ns3::PLC_ImpulsiveNoiseSource::PulseStart() [member function]
    cls.add_method('PulseStart', 
                   'void', 
                   [])
    ## plc-noise.h (module 'plc'): void ns3::PLC_ImpulsiveNoiseSource::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_InformationRateModel_methods(root_module, cls):
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::PLC_InformationRateModel(ns3::PLC_InformationRateModel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_InformationRateModel const &', 'arg0')])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::PLC_InformationRateModel() [constructor]
    cls.add_constructor([])
    ## plc-link-performance-model.h (module 'plc'): double ns3::PLC_InformationRateModel::GetGatheredMutualInformation() [member function]
    cls.add_method('GetGatheredMutualInformation', 
                   'double', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): ns3::Time ns3::PLC_InformationRateModel::GetGuardIntervalDuration() [member function]
    cls.add_method('GetGuardIntervalDuration', 
                   'ns3::Time', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): ns3::Time ns3::PLC_InformationRateModel::GetSymbolDuration() [member function]
    cls.add_method('GetSymbolDuration', 
                   'ns3::Time', 
                   [])
    ## plc-link-performance-model.h (module 'plc'): static ns3::TypeId ns3::PLC_InformationRateModel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_InformationRateModel::SetGuardIntervalDuration(ns3::Time duration) [member function]
    cls.add_method('SetGuardIntervalDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_InformationRateModel::SetSymbolDuration(ns3::Time duration) [member function]
    cls.add_method('SetSymbolDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## plc-link-performance-model.h (module 'plc'): bool ns3::PLC_InformationRateModel::DoEndRx() [member function]
    cls.add_method('DoEndRx', 
                   'bool', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_InformationRateModel::DoEvaluateChunk() [member function]
    cls.add_method('DoEvaluateChunk', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-link-performance-model.h (module 'plc'): void ns3::PLC_InformationRateModel::DoStartRx(double requiredInformationBits) [member function]
    cls.add_method('DoStartRx', 
                   'void', 
                   [param('double', 'requiredInformationBits')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_InformationRateModelMcsInfo_methods(root_module, cls):
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::McsInfo::McsInfo() [constructor]
    cls.add_constructor([])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::McsInfo::McsInfo(ns3::PLC_InformationRateModel::McsInfo const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_InformationRateModel::McsInfo const &', 'arg0')])
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::McsInfo::cardinality [variable]
    cls.add_instance_attribute('cardinality', 'short int', is_const=False)
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::McsInfo::code_rate [variable]
    cls.add_instance_attribute('code_rate', 'double', is_const=False)
    ## plc-link-performance-model.h (module 'plc'): ns3::PLC_InformationRateModel::McsInfo::mod [variable]
    cls.add_instance_attribute('mod', 'ns3::Modulation', is_const=False)
    return

def register_Ns3PLC_InformationRatePhy_methods(root_module, cls):
    ## plc-phy.h (module 'plc'): ns3::PLC_InformationRatePhy::PLC_InformationRatePhy(ns3::PLC_InformationRatePhy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_InformationRatePhy const &', 'arg0')])
    ## plc-phy.h (module 'plc'): ns3::PLC_InformationRatePhy::PLC_InformationRatePhy() [constructor]
    cls.add_constructor([])
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::EndRxHeader(ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('EndRxHeader', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::EndRxPayload(ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('EndRxPayload', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_InformationRatePhy::GetHeaderModulationAndCodingScheme() [member function]
    cls.add_method('GetHeaderModulationAndCodingScheme', 
                   'ns3::ModulationAndCodingType', 
                   [])
    ## plc-phy.h (module 'plc'): size_t ns3::PLC_InformationRatePhy::GetOfdmSymbolsPerCodeBlock() [member function]
    cls.add_method('GetOfdmSymbolsPerCodeBlock', 
                   'size_t', 
                   [])
    ## plc-phy.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_InformationRatePhy::GetPayloadModulationAndCodingScheme() [member function]
    cls.add_method('GetPayloadModulationAndCodingScheme', 
                   'ns3::ModulationAndCodingType', 
                   [])
    ## plc-phy.h (module 'plc'): static double ns3::PLC_InformationRatePhy::GetRatelessCodingOverhead() [member function]
    cls.add_method('GetRatelessCodingOverhead', 
                   'double', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): static ns3::TypeId ns3::PLC_InformationRatePhy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::PreambleDetectionSuccessful(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('PreambleDetectionSuccessful', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::ReceptionFailure() [member function]
    cls.add_method('ReceptionFailure', 
                   'void', 
                   [])
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::SendFrame(ns3::Ptr<ns3::Packet> p, ns3::Ptr<ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('SendFrame', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo >', 'metaInfo')])
    ## plc-phy.h (module 'plc'): bool ns3::PLC_InformationRatePhy::SendRedundancy() [member function]
    cls.add_method('SendRedundancy', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::SetHeaderModulationAndCodingScheme(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetHeaderModulationAndCodingScheme', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-phy.h (module 'plc'): static void ns3::PLC_InformationRatePhy::SetOfdmSymbolsPerCodeBlock(size_t spb) [member function]
    cls.add_method('SetOfdmSymbolsPerCodeBlock', 
                   'void', 
                   [param('size_t', 'spb')], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::SetPayloadModulationAndCodingScheme(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetPayloadModulationAndCodingScheme', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-phy.h (module 'plc'): static void ns3::PLC_InformationRatePhy::SetRatelessCodingOverhead(double overhead) [member function]
    cls.add_method('SetRatelessCodingOverhead', 
                   'void', 
                   [param('double', 'overhead')], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): size_t ns3::PLC_InformationRatePhy::ChunksInByte(size_t num_chunks, size_t raw_bits_per_symbol) [member function]
    cls.add_method('ChunksInByte', 
                   'size_t', 
                   [param('size_t', 'num_chunks'), param('size_t', 'raw_bits_per_symbol')], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): ns3::PLC_PhyCcaResult ns3::PLC_InformationRatePhy::ClearChannelAssessment() [member function]
    cls.add_method('ClearChannelAssessment', 
                   'ns3::PLC_PhyCcaResult', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::Packet> ns3::PLC_InformationRatePhy::CreateEncodedPacket(ns3::Ptr<ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('CreateEncodedPacket', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('ns3::Ptr< ns3::PLC_TrxMetaInfo >', 'metaInfo')], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::Packet> ns3::PLC_InformationRatePhy::CreateFixedRateEncodedFrame(ns3::Ptr<ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('CreateFixedRateEncodedFrame', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('ns3::Ptr< ns3::PLC_TrxMetaInfo >', 'metaInfo')], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): ns3::Ptr<ns3::Packet> ns3::PLC_InformationRatePhy::CreateRatelessEncodedFrame(ns3::Ptr<ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('CreateRatelessEncodedFrame', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('ns3::Ptr< ns3::PLC_TrxMetaInfo >', 'metaInfo')], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::DoSetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [member function]
    cls.add_method('DoSetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::DoStartRx(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('DoStartRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_InformationRatePhy::DoStartTx(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('DoStartTx', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::DoUpdateRxPsd(uint32_t txId, ns3::Ptr<ns3::SpectrumValue> newRxPsd) [member function]
    cls.add_method('DoUpdateRxPsd', 
                   'void', 
                   [param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue >', 'newRxPsd')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::NotifySuccessfulReception() [member function]
    cls.add_method('NotifySuccessfulReception', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): size_t ns3::PLC_InformationRatePhy::RequiredChunks(size_t num_blocks) [member function]
    cls.add_method('RequiredChunks', 
                   'size_t', 
                   [param('size_t', 'num_blocks')], 
                   visibility='protected')
    ## plc-phy.h (module 'plc'): void ns3::PLC_InformationRatePhy::StartReception(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('StartReception', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_NYCY70SM35_Cable_methods(root_module, cls):
    ## plc-cable.h (module 'plc'): ns3::PLC_NYCY70SM35_Cable::PLC_NYCY70SM35_Cable(ns3::PLC_NYCY70SM35_Cable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_NYCY70SM35_Cable const &', 'arg0')])
    ## plc-cable.h (module 'plc'): ns3::PLC_NYCY70SM35_Cable::PLC_NYCY70SM35_Cable() [constructor]
    cls.add_constructor([])
    ## plc-cable.h (module 'plc'): ns3::PLC_NYCY70SM35_Cable::PLC_NYCY70SM35_Cable(ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-cable.h (module 'plc'): void ns3::PLC_NYCY70SM35_Cable::Calculate() [member function]
    cls.add_method('Calculate', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-cable.h (module 'plc'): static ns3::TypeId ns3::PLC_NYCY70SM35_Cable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_NetDevice_methods(root_module, cls):
    ## plc-net-device.h (module 'plc'): ns3::PLC_NetDevice::PLC_NetDevice(ns3::PLC_NetDevice const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_NetDevice const &', 'arg0')])
    ## plc-net-device.h (module 'plc'): ns3::PLC_NetDevice::PLC_NetDevice() [constructor]
    cls.add_constructor([])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::AddLinkChangeCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [member function]
    cls.add_method('AddLinkChangeCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::ConfigComplete() [member function]
    cls.add_method('ConfigComplete', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Address ns3::PLC_NetDevice::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Address ns3::PLC_NetDevice::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::Channel> ns3::PLC_NetDevice::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::Channel >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::PLC_ChannelTransferImpl * ns3::PLC_NetDevice::GetChannelTransferImpl(ns3::Ptr<ns3::PLC_NetDevice> dev) [member function]
    cls.add_method('GetChannelTransferImpl', 
                   'ns3::PLC_ChannelTransferImpl *', 
                   [param('ns3::Ptr< ns3::PLC_NetDevice >', 'dev')])
    ## plc-net-device.h (module 'plc'): uint32_t ns3::PLC_NetDevice::GetIfIndex() const [member function]
    cls.add_method('GetIfIndex', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_Mac> ns3::PLC_NetDevice::GetMac() [member function]
    cls.add_method('GetMac', 
                   'ns3::Ptr< ns3::PLC_Mac >', 
                   [], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): uint16_t ns3::PLC_NetDevice::GetMtu() const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Address ns3::PLC_NetDevice::GetMulticast(ns3::Ipv4Address multicastGroup) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv4Address', 'multicastGroup')], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Address ns3::PLC_NetDevice::GetMulticast(ns3::Ipv6Address addr) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::Node> ns3::PLC_NetDevice::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_Outlet> ns3::PLC_NetDevice::GetOutlet() [member function]
    cls.add_method('GetOutlet', 
                   'ns3::Ptr< ns3::PLC_Outlet >', 
                   [])
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_Phy> ns3::PLC_NetDevice::GetPhy() [member function]
    cls.add_method('GetPhy', 
                   'ns3::Ptr< ns3::PLC_Phy >', 
                   [], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_Node> ns3::PLC_NetDevice::GetPlcNode() [member function]
    cls.add_method('GetPlcNode', 
                   'ns3::Ptr< ns3::PLC_Node >', 
                   [])
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_NetDevice::GetRxImpedance() [member function]
    cls.add_method('GetRxImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_NetDevice::GetShuntImpedance() [member function]
    cls.add_method('GetShuntImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::SpectrumModel const> ns3::PLC_NetDevice::GetSpectrumModel() [member function]
    cls.add_method('GetSpectrumModel', 
                   'ns3::Ptr< ns3::SpectrumModel const >', 
                   [])
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::PLC_ValueBase> ns3::PLC_NetDevice::GetTxImpedance() [member function]
    cls.add_method('GetTxImpedance', 
                   'ns3::Ptr< ns3::PLC_ValueBase >', 
                   [])
    ## plc-net-device.h (module 'plc'): static ns3::TypeId ns3::PLC_NetDevice::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::IsBridge() const [member function]
    cls.add_method('IsBridge', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::IsLinkUp() const [member function]
    cls.add_method('IsLinkUp', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::IsPointToPoint() const [member function]
    cls.add_method('IsPointToPoint', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::LinkDown() [member function]
    cls.add_method('LinkDown', 
                   'void', 
                   [])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::LinkUp() [member function]
    cls.add_method('LinkUp', 
                   'void', 
                   [])
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::NeedsArp() const [member function]
    cls.add_method('NeedsArp', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::Receive(ns3::Ptr<ns3::Packet> p, ns3::Mac48Address from, ns3::Mac48Address to) [member function]
    cls.add_method('Receive', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Mac48Address', 'from'), param('ns3::Mac48Address', 'to')])
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::Send(ns3::Ptr<ns3::Packet> packet, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('Send', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::SendFrom(ns3::Ptr<ns3::Packet> packet, ns3::Address const & source, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('SendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetAddress(ns3::Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Address', 'address')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetIfIndex(uint32_t const index) [member function]
    cls.add_method('SetIfIndex', 
                   'void', 
                   [param('uint32_t const', 'index')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetMac(ns3::Ptr<ns3::PLC_Mac> mac) [member function]
    cls.add_method('SetMac', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Mac >', 'mac')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::SetMtu(uint16_t const mtu) [member function]
    cls.add_method('SetMtu', 
                   'bool', 
                   [param('uint16_t const', 'mtu')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> psd) [member function]
    cls.add_method('SetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'psd')])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetPhy(ns3::Ptr<ns3::PLC_Phy> phy) [member function]
    cls.add_method('SetPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Phy >', 'phy')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetPlcNode(ns3::Ptr<ns3::PLC_Node> plc_node) [member function]
    cls.add_method('SetPlcNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_Node >', 'plc_node')])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetPromiscReceiveCallback(ns3::Callback<bool, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetPromiscReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetReceiveCallback(ns3::Callback<bool, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetRxImpedance(ns3::Ptr<ns3::PLC_ValueBase> rxImpedance) [member function]
    cls.add_method('SetRxImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'rxImpedance')])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetShuntImpedance(ns3::Ptr<ns3::PLC_ValueBase> shuntImpedance) [member function]
    cls.add_method('SetShuntImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'shuntImpedance')])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetSpectrumModel(ns3::Ptr<ns3::SpectrumModel const> sm) [member function]
    cls.add_method('SetSpectrumModel', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetTxImpedance(ns3::Ptr<ns3::PLC_ValueBase> txImpedance) [member function]
    cls.add_method('SetTxImpedance', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_ValueBase >', 'txImpedance')])
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::SetTxPowerSpectralDensity(ns3::Ptr<ns3::SpectrumValue> txPsd) [member function]
    cls.add_method('SetTxPowerSpectralDensity', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue >', 'txPsd')])
    ## plc-net-device.h (module 'plc'): bool ns3::PLC_NetDevice::SupportsSendFrom() const [member function]
    cls.add_method('SupportsSendFrom', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::CompleteConfig() [member function]
    cls.add_method('CompleteConfig', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-net-device.h (module 'plc'): ns3::Ptr<ns3::Channel> ns3::PLC_NetDevice::DoGetChannel() const [member function]
    cls.add_method('DoGetChannel', 
                   'ns3::Ptr< ns3::Channel >', 
                   [], 
                   is_const=True, visibility='protected')
    ## plc-net-device.h (module 'plc'): void ns3::PLC_NetDevice::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_SimulatorImpl_methods(root_module, cls):
    ## plc-simulator-impl.h (module 'plc'): ns3::PLC_SimulatorImpl::PLC_SimulatorImpl(ns3::PLC_SimulatorImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_SimulatorImpl const &', 'arg0')])
    ## plc-simulator-impl.h (module 'plc'): ns3::PLC_SimulatorImpl::PLC_SimulatorImpl() [constructor]
    cls.add_constructor([])
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::Cancel(ns3::EventId const & ev) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): uint32_t ns3::PLC_SimulatorImpl::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::Time ns3::PLC_SimulatorImpl::GetDelayLeft(ns3::EventId const & id) const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::Time ns3::PLC_SimulatorImpl::GetGranularity() [member function]
    cls.add_method('GetGranularity', 
                   'ns3::Time', 
                   [])
    ## plc-simulator-impl.h (module 'plc'): ns3::Time ns3::PLC_SimulatorImpl::GetMaximumSimulationTime() const [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): uint64_t ns3::PLC_SimulatorImpl::GetQuantizedTicks(ns3::Time time) [member function]
    cls.add_method('GetQuantizedTicks', 
                   'uint64_t', 
                   [param('ns3::Time', 'time')])
    ## plc-simulator-impl.h (module 'plc'): uint32_t ns3::PLC_SimulatorImpl::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): static ns3::TypeId ns3::PLC_SimulatorImpl::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-simulator-impl.h (module 'plc'): bool ns3::PLC_SimulatorImpl::IsExpired(ns3::EventId const & ev) const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): bool ns3::PLC_SimulatorImpl::IsFinished() const [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::Time ns3::PLC_SimulatorImpl::Next() const [member function]
    cls.add_method('Next', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::Time ns3::PLC_SimulatorImpl::Now() const [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::Remove(ns3::EventId const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::Run() [member function]
    cls.add_method('Run', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::RunOneEvent() [member function]
    cls.add_method('RunOneEvent', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::EventId ns3::PLC_SimulatorImpl::Schedule(ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::EventId ns3::PLC_SimulatorImpl::ScheduleDestroy(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleDestroy', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): ns3::EventId ns3::PLC_SimulatorImpl::ScheduleNow(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleNow', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::ScheduleWithContext(uint32_t context, ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::SetGranularity(ns3::Time granularity) [member function]
    cls.add_method('SetGranularity', 
                   'void', 
                   [param('ns3::Time', 'granularity')])
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_virtual=True)
    ## plc-simulator-impl.h (module 'plc'): void ns3::PLC_SimulatorImpl::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_SincSpectrumHelper_methods(root_module, cls):
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_SincSpectrumHelper::PLC_SincSpectrumHelper(ns3::PLC_SincSpectrumHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_SincSpectrumHelper const &', 'arg0')])
    ## plc-spectrum-helper.h (module 'plc'): ns3::PLC_SincSpectrumHelper::PLC_SincSpectrumHelper(double f_c, double main_lobe_bw, double peakPwr, ns3::Ptr<ns3::SpectrumModel const> sm) [constructor]
    cls.add_constructor([param('double', 'f_c'), param('double', 'main_lobe_bw'), param('double', 'peakPwr'), param('ns3::Ptr< ns3::SpectrumModel const >', 'sm')])
    ## plc-spectrum-helper.h (module 'plc'): static ns3::TypeId ns3::PLC_SincSpectrumHelper::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3PLC_TimeVariantConstValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('double', 'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantConstValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantConstValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('double', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('double', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('double', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantConstValue::PLC_TimeVariantConstValue() [constructor]
    cls.add_constructor([])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_Value value=std::complex<double>(0.0, 0.0), size_t timeslots=ns3::PLC_Time::GetNumTimeslots()) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_Value', 'value', default_value='std::complex<double>(0.0, 0.0)'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_TimeVariantValue const & values) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_TimeVariantValue const &', 'values')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(ns3::PLC_ConstValue const & value, size_t timeslots=ns3::PLC_Time::GetNumTimeslots()) [constructor]
    cls.add_constructor([param('ns3::PLC_ConstValue const &', 'value'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantConstValue::PLC_TimeVariantConstValue(ns3::PLC_TimeVariantConstValue const & value) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): size_t ns3::PLC_TimeVariantConstValue::GetNumTimeSlots() const [member function]
    cls.add_method('GetNumTimeSlots', 
                   'size_t', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): static ns3::TypeId ns3::PLC_TimeVariantConstValue::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantValue ns3::PLC_TimeVariantConstValue::GetValues() const [member function]
    cls.add_method('GetValues', 
                   'ns3::PLC_TimeVariantValue', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): void ns3::PLC_TimeVariantConstValue::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_TimeVariantFreqSelectiveValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('double', 'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('double', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('ns3::PLC_Value const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], root_module['ns3::PLC_TimeVariantFreqSelectiveValue'], param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('double', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('*=', param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('double', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('double', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('double', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_Value const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_ConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_FreqSelectiveValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_TimeVariantConstValue const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'right'))
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue() [constructor]
    cls.add_constructor([])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, size_t timeslots=ns3::PLC_Time::GetNumTimeslots(), ns3::PLC_Value value=std::complex<double>(0.0, 0.0)) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()'), param('ns3::PLC_Value', 'value', default_value='std::complex<double>(0.0, 0.0)')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_TimeVariantValue const & values) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_TimeVariantValue const &', 'values')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_TimeVariantValueSpectrum const & values) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_TimeVariantValueSpectrum const &', 'values')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::PLC_ConstValue const & value, size_t timeslots=ns3::PLC_Time::GetNumTimeslots()) [constructor]
    cls.add_constructor([param('ns3::PLC_ConstValue const &', 'value'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::PLC_FreqSelectiveValue const & value, size_t timeslots=ns3::PLC_Time::GetNumTimeslots()) [constructor]
    cls.add_constructor([param('ns3::PLC_FreqSelectiveValue const &', 'value'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::PLC_TimeVariantConstValue const & value) [constructor]
    cls.add_constructor([param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::PLC_FreqSelectiveValue & offset, ns3::PLC_FreqSelectiveValue & amplitude, double phi, size_t timeslots=ns3::PLC_Time::GetNumTimeslots()) [constructor]
    cls.add_constructor([param('ns3::PLC_FreqSelectiveValue &', 'offset'), param('ns3::PLC_FreqSelectiveValue &', 'amplitude'), param('double', 'phi'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantFreqSelectiveValue(ns3::Ptr<ns3::SpectrumModel const> sm, ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet & paramSet, size_t timeslots=ns3::PLC_Time::GetNumTimeslots()) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::SpectrumModel const >', 'sm'), param('ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet &', 'paramSet'), param('size_t', 'timeslots', default_value='ns3::PLC_Time::GetNumTimeslots()')])
    ## plc-value.h (module 'plc'): size_t ns3::PLC_TimeVariantFreqSelectiveValue::GetNumTimeSlots() const [member function]
    cls.add_method('GetNumTimeSlots', 
                   'size_t', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): static ns3::TypeId ns3::PLC_TimeVariantFreqSelectiveValue::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantValueSpectrum ns3::PLC_TimeVariantFreqSelectiveValue::GetValues() const [member function]
    cls.add_method('GetValues', 
                   'ns3::PLC_TimeVariantValueSpectrum', 
                   [], 
                   is_const=True)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantValueSpectrum * ns3::PLC_TimeVariantFreqSelectiveValue::GetValuesRef() [member function]
    cls.add_method('GetValuesRef', 
                   'ns3::PLC_TimeVariantValueSpectrum *', 
                   [])
    ## plc-value.h (module 'plc'): void ns3::PLC_TimeVariantFreqSelectiveValue::pureVirtualDummy() [member function]
    cls.add_method('pureVirtualDummy', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_TimeVariantFreqSelectiveValuePLC_TimeVariantParamSet_methods(root_module, cls):
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::PLC_TimeVariantParamSet() [constructor]
    cls.add_constructor([])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::PLC_TimeVariantParamSet(ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet const &', 'arg0')])
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::Q_amplitude [variable]
    cls.add_instance_attribute('Q_amplitude', 'double', is_const=False)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::Q_offset [variable]
    cls.add_instance_attribute('Q_offset', 'double', is_const=False)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::R_amplitude [variable]
    cls.add_instance_attribute('R_amplitude', 'double', is_const=False)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::R_offset [variable]
    cls.add_instance_attribute('R_offset', 'double', is_const=False)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::f0_amplitude [variable]
    cls.add_instance_attribute('f0_amplitude', 'double', is_const=False)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::f_0_offset [variable]
    cls.add_instance_attribute('f_0_offset', 'double', is_const=False)
    ## plc-value.h (module 'plc'): ns3::PLC_TimeVariantFreqSelectiveValue::PLC_TimeVariantParamSet::phi [variable]
    cls.add_instance_attribute('phi', 'double', is_const=False)
    return

def register_Ns3Packet_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## packet.h (module 'network'): ns3::Packet::Packet() [constructor]
    cls.add_constructor([])
    ## packet.h (module 'network'): ns3::Packet::Packet(ns3::Packet const & o) [copy constructor]
    cls.add_constructor([param('ns3::Packet const &', 'o')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint32_t size) [constructor]
    cls.add_constructor([param('uint32_t', 'size')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint8_t const * buffer, uint32_t size, bool magic) [constructor]
    cls.add_constructor([param('uint8_t const *', 'buffer'), param('uint32_t', 'size'), param('bool', 'magic')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint8_t const * buffer, uint32_t size) [constructor]
    cls.add_constructor([param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::AddAtEnd(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## packet.h (module 'network'): void ns3::Packet::AddByteTag(ns3::Tag const & tag) const [member function]
    cls.add_method('AddByteTag', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::AddHeader(ns3::Header const & header) [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header')])
    ## packet.h (module 'network'): void ns3::Packet::AddPacketTag(ns3::Tag const & tag) const [member function]
    cls.add_method('AddPacketTag', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::AddPaddingAtEnd(uint32_t size) [member function]
    cls.add_method('AddPaddingAtEnd', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::AddTrailer(ns3::Trailer const & trailer) [member function]
    cls.add_method('AddTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer')])
    ## packet.h (module 'network'): ns3::PacketMetadata::ItemIterator ns3::Packet::BeginItem() const [member function]
    cls.add_method('BeginItem', 
                   'ns3::PacketMetadata::ItemIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Packet::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::Packet >', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::CopyData(uint8_t * buffer, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::CopyData(std::ostream * os, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'void', 
                   [param('std::ostream *', 'os'), param('uint32_t', 'size')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Packet::CreateFragment(uint32_t start, uint32_t length) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'start'), param('uint32_t', 'length')], 
                   is_const=True)
    ## packet.h (module 'network'): static void ns3::Packet::EnableChecking() [member function]
    cls.add_method('EnableChecking', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet.h (module 'network'): static void ns3::Packet::EnablePrinting() [member function]
    cls.add_method('EnablePrinting', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet.h (module 'network'): bool ns3::Packet::FindFirstMatchingByteTag(ns3::Tag & tag) const [member function]
    cls.add_method('FindFirstMatchingByteTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::ByteTagIterator ns3::Packet::GetByteTagIterator() const [member function]
    cls.add_method('GetByteTagIterator', 
                   'ns3::ByteTagIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::NixVector> ns3::Packet::GetNixVector() const [member function]
    cls.add_method('GetNixVector', 
                   'ns3::Ptr< ns3::NixVector >', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::PacketTagIterator ns3::Packet::GetPacketTagIterator() const [member function]
    cls.add_method('GetPacketTagIterator', 
                   'ns3::PacketTagIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint64_t ns3::Packet::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint8_t const * ns3::Packet::PeekData() const [member function]
    cls.add_method('PeekData', 
                   'uint8_t const *', 
                   [], 
                   deprecated=True, is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::PeekHeader(ns3::Header & header) const [member function]
    cls.add_method('PeekHeader', 
                   'uint32_t', 
                   [param('ns3::Header &', 'header')], 
                   is_const=True)
    ## packet.h (module 'network'): bool ns3::Packet::PeekPacketTag(ns3::Tag & tag) const [member function]
    cls.add_method('PeekPacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::PeekTrailer(ns3::Trailer & trailer) [member function]
    cls.add_method('PeekTrailer', 
                   'uint32_t', 
                   [param('ns3::Trailer &', 'trailer')])
    ## packet.h (module 'network'): void ns3::Packet::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::PrintByteTags(std::ostream & os) const [member function]
    cls.add_method('PrintByteTags', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::PrintPacketTags(std::ostream & os) const [member function]
    cls.add_method('PrintPacketTags', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::RemoveAllByteTags() [member function]
    cls.add_method('RemoveAllByteTags', 
                   'void', 
                   [])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAllPacketTags() [member function]
    cls.add_method('RemoveAllPacketTags', 
                   'void', 
                   [])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAtEnd(uint32_t size) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAtStart(uint32_t size) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::RemoveHeader(ns3::Header & header) [member function]
    cls.add_method('RemoveHeader', 
                   'uint32_t', 
                   [param('ns3::Header &', 'header')])
    ## packet.h (module 'network'): bool ns3::Packet::RemovePacketTag(ns3::Tag & tag) [member function]
    cls.add_method('RemovePacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::RemoveTrailer(ns3::Trailer & trailer) [member function]
    cls.add_method('RemoveTrailer', 
                   'uint32_t', 
                   [param('ns3::Trailer &', 'trailer')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::SetNixVector(ns3::Ptr<ns3::NixVector> arg0) [member function]
    cls.add_method('SetNixVector', 
                   'void', 
                   [param('ns3::Ptr< ns3::NixVector >', 'arg0')])
    return

def register_Ns3RandomVariableChecker_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::RandomVariableChecker::RandomVariableChecker() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::RandomVariableChecker::RandomVariableChecker(ns3::RandomVariableChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RandomVariableChecker const &', 'arg0')])
    return

def register_Ns3RandomVariableValue_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::RandomVariableValue::RandomVariableValue() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::RandomVariableValue::RandomVariableValue(ns3::RandomVariableValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RandomVariableValue const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::RandomVariableValue::RandomVariableValue(ns3::RandomVariable const & value) [constructor]
    cls.add_constructor([param('ns3::RandomVariable const &', 'value')])
    ## random-variable.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::RandomVariableValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## random-variable.h (module 'core'): bool ns3::RandomVariableValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## random-variable.h (module 'core'): ns3::RandomVariable ns3::RandomVariableValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::RandomVariable', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): std::string ns3::RandomVariableValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## random-variable.h (module 'core'): void ns3::RandomVariableValue::Set(ns3::RandomVariable const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::RandomVariable const &', 'value')])
    return

def register_Ns3TimeChecker_methods(root_module, cls):
    ## nstime.h (module 'core'): ns3::TimeChecker::TimeChecker() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::TimeChecker::TimeChecker(ns3::TimeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeChecker const &', 'arg0')])
    return

def register_Ns3TimeValue_methods(root_module, cls):
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue(ns3::TimeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeValue const &', 'arg0')])
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue(ns3::Time const & value) [constructor]
    cls.add_constructor([param('ns3::Time const &', 'value')])
    ## nstime.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::TimeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## nstime.h (module 'core'): bool ns3::TimeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## nstime.h (module 'core'): ns3::Time ns3::TimeValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): std::string ns3::TimeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## nstime.h (module 'core'): void ns3::TimeValue::Set(ns3::Time const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Time const &', 'value')])
    return

def register_Ns3TypeIdChecker_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeIdChecker::TypeIdChecker() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeIdChecker::TypeIdChecker(ns3::TypeIdChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeIdChecker const &', 'arg0')])
    return

def register_Ns3TypeIdValue_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue(ns3::TypeIdValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeIdValue const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue(ns3::TypeId const & value) [constructor]
    cls.add_constructor([param('ns3::TypeId const &', 'value')])
    ## type-id.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::TypeIdValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## type-id.h (module 'core'): bool ns3::TypeIdValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeIdValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeIdValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## type-id.h (module 'core'): void ns3::TypeIdValue::Set(ns3::TypeId const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::TypeId const &', 'value')])
    return

def register_Ns3UintegerValue_methods(root_module, cls):
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue() [constructor]
    cls.add_constructor([])
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue(ns3::UintegerValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::UintegerValue const &', 'arg0')])
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue(uint64_t const & value) [constructor]
    cls.add_constructor([param('uint64_t const &', 'value')])
    ## uinteger.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::UintegerValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## uinteger.h (module 'core'): bool ns3::UintegerValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## uinteger.h (module 'core'): uint64_t ns3::UintegerValue::Get() const [member function]
    cls.add_method('Get', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## uinteger.h (module 'core'): std::string ns3::UintegerValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## uinteger.h (module 'core'): void ns3::UintegerValue::Set(uint64_t const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint64_t const &', 'value')])
    return

def register_Ns3Vector2DChecker_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector2DChecker::Vector2DChecker() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector2DChecker::Vector2DChecker(ns3::Vector2DChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector2DChecker const &', 'arg0')])
    return

def register_Ns3Vector2DValue_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector2DValue::Vector2DValue() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector2DValue::Vector2DValue(ns3::Vector2DValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector2DValue const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector2DValue::Vector2DValue(ns3::Vector2D const & value) [constructor]
    cls.add_constructor([param('ns3::Vector2D const &', 'value')])
    ## vector.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::Vector2DValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): bool ns3::Vector2DValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## vector.h (module 'core'): ns3::Vector2D ns3::Vector2DValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Vector2D', 
                   [], 
                   is_const=True)
    ## vector.h (module 'core'): std::string ns3::Vector2DValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): void ns3::Vector2DValue::Set(ns3::Vector2D const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Vector2D const &', 'value')])
    return

def register_Ns3Vector3DChecker_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector3DChecker::Vector3DChecker() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector3DChecker::Vector3DChecker(ns3::Vector3DChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector3DChecker const &', 'arg0')])
    return

def register_Ns3Vector3DValue_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector3DValue::Vector3DValue() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector3DValue::Vector3DValue(ns3::Vector3DValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector3DValue const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector3DValue::Vector3DValue(ns3::Vector3D const & value) [constructor]
    cls.add_constructor([param('ns3::Vector3D const &', 'value')])
    ## vector.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::Vector3DValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): bool ns3::Vector3DValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## vector.h (module 'core'): ns3::Vector3D ns3::Vector3DValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Vector3D', 
                   [], 
                   is_const=True)
    ## vector.h (module 'core'): std::string ns3::Vector3DValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): void ns3::Vector3DValue::Set(ns3::Vector3D const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Vector3D const &', 'value')])
    return

def register_Ns3AddressChecker_methods(root_module, cls):
    ## address.h (module 'network'): ns3::AddressChecker::AddressChecker() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::AddressChecker::AddressChecker(ns3::AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AddressChecker const &', 'arg0')])
    return

def register_Ns3AddressValue_methods(root_module, cls):
    ## address.h (module 'network'): ns3::AddressValue::AddressValue() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::AddressValue::AddressValue(ns3::AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AddressValue const &', 'arg0')])
    ## address.h (module 'network'): ns3::AddressValue::AddressValue(ns3::Address const & value) [constructor]
    cls.add_constructor([param('ns3::Address const &', 'value')])
    ## address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## address.h (module 'network'): bool ns3::AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## address.h (module 'network'): ns3::Address ns3::AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): std::string ns3::AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## address.h (module 'network'): void ns3::AddressValue::Set(ns3::Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Address const &', 'value')])
    return

def register_Ns3BridgeChannel_methods(root_module, cls):
    ## bridge-channel.h (module 'bridge'): static ns3::TypeId ns3::BridgeChannel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## bridge-channel.h (module 'bridge'): ns3::BridgeChannel::BridgeChannel() [constructor]
    cls.add_constructor([])
    ## bridge-channel.h (module 'bridge'): void ns3::BridgeChannel::AddChannel(ns3::Ptr<ns3::Channel> bridgedChannel) [member function]
    cls.add_method('AddChannel', 
                   'void', 
                   [param('ns3::Ptr< ns3::Channel >', 'bridgedChannel')])
    ## bridge-channel.h (module 'bridge'): uint32_t ns3::BridgeChannel::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-channel.h (module 'bridge'): ns3::Ptr<ns3::NetDevice> ns3::BridgeChannel::GetDevice(uint32_t i) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3BridgeNetDevice_methods(root_module, cls):
    ## bridge-net-device.h (module 'bridge'): ns3::BridgeNetDevice::BridgeNetDevice() [constructor]
    cls.add_constructor([])
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::AddBridgePort(ns3::Ptr<ns3::NetDevice> bridgePort) [member function]
    cls.add_method('AddBridgePort', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'bridgePort')])
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::AddLinkChangeCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [member function]
    cls.add_method('AddLinkChangeCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Address ns3::BridgeNetDevice::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Ptr<ns3::NetDevice> ns3::BridgeNetDevice::GetBridgePort(uint32_t n) const [member function]
    cls.add_method('GetBridgePort', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'n')], 
                   is_const=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Address ns3::BridgeNetDevice::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Ptr<ns3::Channel> ns3::BridgeNetDevice::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::Channel >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): uint32_t ns3::BridgeNetDevice::GetIfIndex() const [member function]
    cls.add_method('GetIfIndex', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): uint16_t ns3::BridgeNetDevice::GetMtu() const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Address ns3::BridgeNetDevice::GetMulticast(ns3::Ipv4Address multicastGroup) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv4Address', 'multicastGroup')], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Address ns3::BridgeNetDevice::GetMulticast(ns3::Ipv6Address addr) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): uint32_t ns3::BridgeNetDevice::GetNBridgePorts() const [member function]
    cls.add_method('GetNBridgePorts', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## bridge-net-device.h (module 'bridge'): ns3::Ptr<ns3::Node> ns3::BridgeNetDevice::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): static ns3::TypeId ns3::BridgeNetDevice::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::IsBridge() const [member function]
    cls.add_method('IsBridge', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::IsLinkUp() const [member function]
    cls.add_method('IsLinkUp', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::IsPointToPoint() const [member function]
    cls.add_method('IsPointToPoint', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::NeedsArp() const [member function]
    cls.add_method('NeedsArp', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::Send(ns3::Ptr<ns3::Packet> packet, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('Send', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::SendFrom(ns3::Ptr<ns3::Packet> packet, ns3::Address const & source, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('SendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::SetAddress(ns3::Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Address', 'address')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::SetIfIndex(uint32_t const index) [member function]
    cls.add_method('SetIfIndex', 
                   'void', 
                   [param('uint32_t const', 'index')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::SetMtu(uint16_t const mtu) [member function]
    cls.add_method('SetMtu', 
                   'bool', 
                   [param('uint16_t const', 'mtu')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::SetPromiscReceiveCallback(ns3::Callback<bool, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetPromiscReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::SetReceiveCallback(ns3::Callback<bool, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): bool ns3::BridgeNetDevice::SupportsSendFrom() const [member function]
    cls.add_method('SupportsSendFrom', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::ForwardBroadcast(ns3::Ptr<ns3::NetDevice> incomingPort, ns3::Ptr<ns3::Packet const> packet, uint16_t protocol, ns3::Mac48Address src, ns3::Mac48Address dst) [member function]
    cls.add_method('ForwardBroadcast', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'incomingPort'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint16_t', 'protocol'), param('ns3::Mac48Address', 'src'), param('ns3::Mac48Address', 'dst')], 
                   visibility='protected')
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::ForwardUnicast(ns3::Ptr<ns3::NetDevice> incomingPort, ns3::Ptr<ns3::Packet const> packet, uint16_t protocol, ns3::Mac48Address src, ns3::Mac48Address dst) [member function]
    cls.add_method('ForwardUnicast', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'incomingPort'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint16_t', 'protocol'), param('ns3::Mac48Address', 'src'), param('ns3::Mac48Address', 'dst')], 
                   visibility='protected')
    ## bridge-net-device.h (module 'bridge'): ns3::Ptr<ns3::NetDevice> ns3::BridgeNetDevice::GetLearnedState(ns3::Mac48Address source) [member function]
    cls.add_method('GetLearnedState', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('ns3::Mac48Address', 'source')], 
                   visibility='protected')
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::Learn(ns3::Mac48Address source, ns3::Ptr<ns3::NetDevice> port) [member function]
    cls.add_method('Learn', 
                   'void', 
                   [param('ns3::Mac48Address', 'source'), param('ns3::Ptr< ns3::NetDevice >', 'port')], 
                   visibility='protected')
    ## bridge-net-device.h (module 'bridge'): void ns3::BridgeNetDevice::ReceiveFromDevice(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::Packet const> packet, uint16_t protocol, ns3::Address const & source, ns3::Address const & destination, ns3::NetDevice::PacketType packetType) [member function]
    cls.add_method('ReceiveFromDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint16_t', 'protocol'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'destination'), param('ns3::NetDevice::PacketType', 'packetType')], 
                   visibility='protected')
    return

def register_Ns3PLC_ChaseCombiningPhy_methods(root_module, cls):
    ## plc-phy.h (module 'plc'): ns3::PLC_ChaseCombiningPhy::PLC_ChaseCombiningPhy(ns3::PLC_ChaseCombiningPhy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ChaseCombiningPhy const &', 'arg0')])
    ## plc-phy.h (module 'plc'): ns3::PLC_ChaseCombiningPhy::PLC_ChaseCombiningPhy() [constructor]
    cls.add_constructor([])
    ## plc-phy.h (module 'plc'): static ns3::TypeId ns3::PLC_ChaseCombiningPhy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_ChaseCombiningPhy::SendRedundancy() [member function]
    cls.add_method('SendRedundancy', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ChaseCombiningPhy::TraceSinr(ns3::Time t, ns3::Ptr<ns3::SpectrumValue const> sinr) [member function]
    cls.add_method('TraceSinr', 
                   'void', 
                   [param('ns3::Time', 't'), param('ns3::Ptr< ns3::SpectrumValue const >', 'sinr')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_ChaseCombiningPhy::UpdateSinrBase(ns3::Ptr<ns3::SpectrumValue const> newSinrBase) [member function]
    cls.add_method('UpdateSinrBase', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'newSinrBase')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_ChaseCombiningPhy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ChaseCombiningPhy::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_ChaseCombiningPhy::DoStartTx(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('DoStartTx', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ChaseCombiningPhy::NotifySuccessfulReception() [member function]
    cls.add_method('NotifySuccessfulReception', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ChaseCombiningPhy::StartReception(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('StartReception', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3PLC_ErrorRatePhy_methods(root_module, cls):
    ## plc-phy.h (module 'plc'): ns3::PLC_ErrorRatePhy::PLC_ErrorRatePhy(ns3::PLC_ErrorRatePhy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_ErrorRatePhy const &', 'arg0')])
    ## plc-phy.h (module 'plc'): ns3::PLC_ErrorRatePhy::PLC_ErrorRatePhy() [constructor]
    cls.add_constructor([])
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::EndRx(uint32_t txId) [member function]
    cls.add_method('EndRx', 
                   'void', 
                   [param('uint32_t', 'txId')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): ns3::ModulationAndCodingType ns3::PLC_ErrorRatePhy::GetModulationAndCodingScheme() [member function]
    cls.add_method('GetModulationAndCodingScheme', 
                   'ns3::ModulationAndCodingType', 
                   [])
    ## plc-phy.h (module 'plc'): static ns3::TypeId ns3::PLC_ErrorRatePhy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::PreambleDetectionSuccessful(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('PreambleDetectionSuccessful', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::SetModulationAndCodingScheme(ns3::ModulationAndCodingType mcs) [member function]
    cls.add_method('SetModulationAndCodingScheme', 
                   'void', 
                   [param('ns3::ModulationAndCodingType', 'mcs')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): ns3::PLC_PhyCcaResult ns3::PLC_ErrorRatePhy::ClearChannelAssessment() [member function]
    cls.add_method('ClearChannelAssessment', 
                   'ns3::PLC_PhyCcaResult', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::DoSetNoiseFloor(ns3::Ptr<ns3::SpectrumValue const> noiseFloor) [member function]
    cls.add_method('DoSetNoiseFloor', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue const >', 'noiseFloor')], 
                   visibility='private', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::DoStartRx(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('DoStartRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   visibility='private', is_virtual=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_ErrorRatePhy::DoStartTx(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('DoStartTx', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')], 
                   visibility='private', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_ErrorRatePhy::DoUpdateRxPsd(uint32_t txId, ns3::Ptr<ns3::SpectrumValue> newRxPsd) [member function]
    cls.add_method('DoUpdateRxPsd', 
                   'void', 
                   [param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue >', 'newRxPsd')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PLC_IncrementalRedundancyPhy_methods(root_module, cls):
    ## plc-phy.h (module 'plc'): ns3::PLC_IncrementalRedundancyPhy::PLC_IncrementalRedundancyPhy(ns3::PLC_IncrementalRedundancyPhy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PLC_IncrementalRedundancyPhy const &', 'arg0')])
    ## plc-phy.h (module 'plc'): ns3::PLC_IncrementalRedundancyPhy::PLC_IncrementalRedundancyPhy() [constructor]
    cls.add_constructor([])
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::EndRxHeader(ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('EndRxHeader', 
                   'void', 
                   [param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::EndRxPayload(ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('EndRxPayload', 
                   'void', 
                   [param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): static ns3::Time ns3::PLC_IncrementalRedundancyPhy::GetReceptionFailureTimeout() [member function]
    cls.add_method('GetReceptionFailureTimeout', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): size_t ns3::PLC_IncrementalRedundancyPhy::GetRedundancyFrameChunks() [member function]
    cls.add_method('GetRedundancyFrameChunks', 
                   'size_t', 
                   [])
    ## plc-phy.h (module 'plc'): static ns3::TypeId ns3::PLC_IncrementalRedundancyPhy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::ReceptionFailureTimeout() [member function]
    cls.add_method('ReceptionFailureTimeout', 
                   'void', 
                   [])
    ## plc-phy.h (module 'plc'): bool ns3::PLC_IncrementalRedundancyPhy::SendRedundancy() [member function]
    cls.add_method('SendRedundancy', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## plc-phy.h (module 'plc'): static void ns3::PLC_IncrementalRedundancyPhy::SetReceptionFailureTimeout(ns3::Time timeout) [member function]
    cls.add_method('SetReceptionFailureTimeout', 
                   'void', 
                   [param('ns3::Time', 'timeout')], 
                   is_static=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::SetRedundancyFrameChunks(size_t chunks) [member function]
    cls.add_method('SetRedundancyFrameChunks', 
                   'void', 
                   [param('size_t', 'chunks')])
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): bool ns3::PLC_IncrementalRedundancyPhy::DoStartTx(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('DoStartTx', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')], 
                   visibility='protected', is_virtual=True)
    ## plc-phy.h (module 'plc'): void ns3::PLC_IncrementalRedundancyPhy::StartReception(ns3::Ptr<ns3::Packet const> p, uint32_t txId, ns3::Ptr<ns3::SpectrumValue> & rxPsd, ns3::Time duration, ns3::Ptr<const ns3::PLC_TrxMetaInfo> metaInfo) [member function]
    cls.add_method('StartReception', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint32_t', 'txId'), param('ns3::Ptr< ns3::SpectrumValue > &', 'rxPsd'), param('ns3::Time', 'duration'), param('ns3::Ptr< ns3::PLC_TrxMetaInfo const >', 'metaInfo')], 
                   visibility='protected', is_virtual=True)
    return

def register_functions(root_module):
    module = root_module
    ## plc-value.h (module 'plc'): extern ns3::Ptr<ns3::PLC_ValueBase> ns3::Add(ns3::Ptr<ns3::PLC_ValueBase> op1, ns3::Ptr<ns3::PLC_ValueBase> op2) [free function]
    module.add_function('Add', 
                        'ns3::Ptr< ns3::PLC_ValueBase >', 
                        [param('ns3::Ptr< ns3::PLC_ValueBase >', 'op1'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'op2')])
    ## plc-value.h (module 'plc'): extern void ns3::AddInverseValue(ns3::PLC_ValueBase * res, ns3::PLC_ValueBase * imp) [free function]
    module.add_function('AddInverseValue', 
                        'void', 
                        [param('ns3::PLC_ValueBase *', 'res'), param('ns3::PLC_ValueBase *', 'imp')])
    ## plc-phy.h (module 'plc'): extern ns3::Time ns3::CalculateTransmissionDuration(size_t encoded_bits, ns3::ModulationAndCodingType mcs, size_t subbands) [free function]
    module.add_function('CalculateTransmissionDuration', 
                        'ns3::Time', 
                        [param('size_t', 'encoded_bits'), param('ns3::ModulationAndCodingType', 'mcs'), param('size_t', 'subbands')])
    ## plc-value.h (module 'plc'): extern ns3::Ptr<ns3::PLC_ValueBase> ns3::Divide(ns3::Ptr<ns3::PLC_ValueBase> op1, ns3::Ptr<ns3::PLC_ValueBase> op2) [free function]
    module.add_function('Divide', 
                        'ns3::Ptr< ns3::PLC_ValueBase >', 
                        [param('ns3::Ptr< ns3::PLC_ValueBase >', 'op1'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'op2')])
    ## plc-defs.h (module 'plc'): extern size_t ns3::GetBitsPerSymbol(ns3::ModulationAndCodingType mcs) [free function]
    module.add_function('GetBitsPerSymbol', 
                        'size_t', 
                        [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-dcmc-capacity.h (module 'plc'): extern ns3::SpectrumValue ns3::GetCapacity(ns3::SpectrumValue const & SINR, ns3::Modulation mod, short int cardinality) [free function]
    module.add_function('GetCapacity', 
                        'ns3::SpectrumValue', 
                        [param('ns3::SpectrumValue const &', 'SINR'), param('ns3::Modulation', 'mod'), param('short int', 'cardinality')])
    ## plc-defs.h (module 'plc'): extern double ns3::GetCodeRate(ns3::ModulationAndCodingType mcs) [free function]
    module.add_function('GetCodeRate', 
                        'double', 
                        [param('ns3::ModulationAndCodingType', 'mcs')])
    ## plc-value.h (module 'plc'): extern ns3::Ptr<ns3::PLC_ValueBase> ns3::Multiply(ns3::Ptr<ns3::PLC_ValueBase> op1, ns3::Ptr<ns3::PLC_ValueBase> op2) [free function]
    module.add_function('Multiply', 
                        'ns3::Ptr< ns3::PLC_ValueBase >', 
                        [param('ns3::Ptr< ns3::PLC_ValueBase >', 'op1'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'op2')])
    ## plc-value.h (module 'plc'): extern double ns3::Pwr(ns3::SpectrumValue const & value) [free function]
    module.add_function('Pwr', 
                        'double', 
                        [param('ns3::SpectrumValue const &', 'value')])
    ## plc-phy.h (module 'plc'): extern size_t ns3::RequiredSymbols(size_t encoded_bits, ns3::ModulationAndCodingType mcs, size_t subbands) [free function]
    module.add_function('RequiredSymbols', 
                        'size_t', 
                        [param('size_t', 'encoded_bits'), param('ns3::ModulationAndCodingType', 'mcs'), param('size_t', 'subbands')])
    ## plc-value.h (module 'plc'): extern ns3::Ptr<ns3::PLC_ValueBase> ns3::Subtract(ns3::Ptr<ns3::PLC_ValueBase> op1, ns3::Ptr<ns3::PLC_ValueBase> op2) [free function]
    module.add_function('Subtract', 
                        'ns3::Ptr< ns3::PLC_ValueBase >', 
                        [param('ns3::Ptr< ns3::PLC_ValueBase >', 'op1'), param('ns3::Ptr< ns3::PLC_ValueBase >', 'op2')])
    ## plc-value.h (module 'plc'): extern double ns3::W2dBm(double watt) [free function]
    module.add_function('W2dBm', 
                        'double', 
                        [param('double', 'watt')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveRealValue ns3::abs(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('abs', 
                        'ns3::PLC_FreqSelectiveRealValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveRealValue ns3::abs(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('abs', 
                        'ns3::PLC_TimeVariantFreqSelectiveRealValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantRealValue ns3::abs(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('abs', 
                        'ns3::PLC_TimeVariantRealValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::abs(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('abs', 
                        'double', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveRealValue ns3::absSqr(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('absSqr', 
                        'ns3::PLC_FreqSelectiveRealValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveRealValue ns3::absSqr(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('absSqr', 
                        'ns3::PLC_TimeVariantFreqSelectiveRealValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantRealValue ns3::absSqr(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('absSqr', 
                        'ns3::PLC_TimeVariantRealValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::absSqr(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('absSqr', 
                        'double', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveRealValue ns3::arg(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('arg', 
                        'ns3::PLC_FreqSelectiveRealValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveRealValue ns3::arg(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('arg', 
                        'ns3::PLC_TimeVariantFreqSelectiveRealValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantRealValue ns3::arg(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('arg', 
                        'ns3::PLC_TimeVariantRealValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::arg(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('arg', 
                        'double', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_ConstValue ns3::cosh(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('cosh', 
                        'ns3::PLC_ConstValue', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveValue ns3::cosh(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('cosh', 
                        'ns3::PLC_FreqSelectiveValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantConstValue ns3::cosh(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('cosh', 
                        'ns3::PLC_TimeVariantConstValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveValue ns3::cosh(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('cosh', 
                        'ns3::PLC_TimeVariantFreqSelectiveValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_ConstValue ns3::exp(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('exp', 
                        'ns3::PLC_ConstValue', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveValue ns3::exp(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('exp', 
                        'ns3::PLC_FreqSelectiveValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantConstValue ns3::exp(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('exp', 
                        'ns3::PLC_TimeVariantConstValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveValue ns3::exp(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('exp', 
                        'ns3::PLC_TimeVariantFreqSelectiveValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveRealValue ns3::imag(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('imag', 
                        'ns3::PLC_FreqSelectiveRealValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveRealValue ns3::imag(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('imag', 
                        'ns3::PLC_TimeVariantFreqSelectiveRealValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantRealValue ns3::imag(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('imag', 
                        'ns3::PLC_TimeVariantRealValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::imag(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('imag', 
                        'double', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_ConstValue ns3::log10(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('log10', 
                        'ns3::PLC_ConstValue', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveValue ns3::log10(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('log10', 
                        'ns3::PLC_FreqSelectiveValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantConstValue ns3::log10(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('log10', 
                        'ns3::PLC_TimeVariantConstValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveValue ns3::log10(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('log10', 
                        'ns3::PLC_TimeVariantFreqSelectiveValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::max(ns3::PLC_FreqSelectiveRealValue & value) [free function]
    module.add_function('max', 
                        'double', 
                        [param('ns3::PLC_FreqSelectiveRealValue &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::max(ns3::SpectrumValue & value) [free function]
    module.add_function('max', 
                        'double', 
                        [param('ns3::SpectrumValue &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::min(ns3::PLC_FreqSelectiveRealValue & value) [free function]
    module.add_function('min', 
                        'double', 
                        [param('ns3::PLC_FreqSelectiveRealValue &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::min(ns3::SpectrumValue & value) [free function]
    module.add_function('min', 
                        'double', 
                        [param('ns3::SpectrumValue &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveRealValue ns3::real(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('real', 
                        'ns3::PLC_FreqSelectiveRealValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveRealValue ns3::real(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('real', 
                        'ns3::PLC_TimeVariantFreqSelectiveRealValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantRealValue ns3::real(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('real', 
                        'ns3::PLC_TimeVariantRealValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern double ns3::real(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('real', 
                        'double', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_ConstValue ns3::sinh(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('sinh', 
                        'ns3::PLC_ConstValue', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveValue ns3::sinh(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('sinh', 
                        'ns3::PLC_FreqSelectiveValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantConstValue ns3::sinh(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('sinh', 
                        'ns3::PLC_TimeVariantConstValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveValue ns3::sinh(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('sinh', 
                        'ns3::PLC_TimeVariantFreqSelectiveValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_ConstValue ns3::tan(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('tan', 
                        'ns3::PLC_ConstValue', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveValue ns3::tan(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('tan', 
                        'ns3::PLC_FreqSelectiveValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantConstValue ns3::tan(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('tan', 
                        'ns3::PLC_TimeVariantConstValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveValue ns3::tan(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('tan', 
                        'ns3::PLC_TimeVariantFreqSelectiveValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_ConstValue ns3::tanh(ns3::PLC_ConstValue const & value) [free function]
    module.add_function('tanh', 
                        'ns3::PLC_ConstValue', 
                        [param('ns3::PLC_ConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_FreqSelectiveValue ns3::tanh(ns3::PLC_FreqSelectiveValue const & value) [free function]
    module.add_function('tanh', 
                        'ns3::PLC_FreqSelectiveValue', 
                        [param('ns3::PLC_FreqSelectiveValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantConstValue ns3::tanh(ns3::PLC_TimeVariantConstValue const & value) [free function]
    module.add_function('tanh', 
                        'ns3::PLC_TimeVariantConstValue', 
                        [param('ns3::PLC_TimeVariantConstValue const &', 'value')])
    ## plc-value.h (module 'plc'): extern ns3::PLC_TimeVariantFreqSelectiveValue ns3::tanh(ns3::PLC_TimeVariantFreqSelectiveValue const & value) [free function]
    module.add_function('tanh', 
                        'ns3::PLC_TimeVariantFreqSelectiveValue', 
                        [param('ns3::PLC_TimeVariantFreqSelectiveValue const &', 'value')])
    register_functions_ns3_FatalImpl(module.get_submodule('FatalImpl'), root_module)
    register_functions_ns3_internal(module.get_submodule('internal'), root_module)
    return

def register_functions_ns3_FatalImpl(module, root_module):
    return

def register_functions_ns3_internal(module, root_module):
    return

def main():
    out = FileCodeSink(sys.stdout)
    root_module = module_init()
    register_types(root_module)
    register_methods(root_module)
    register_functions(root_module)
    root_module.generate(out)

if __name__ == '__main__':
    main()

