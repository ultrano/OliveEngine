include "OliveMXS_XML.ms"
struct XMLCameraTraitExtractor
(
	node_node = undefined
	,
	xml_trait = undefined
	,
	fn ext_begin arg_node = ()
	,
	fn ext_end = ()
	,
	fn ext_fov = ()
	,
	fn ext_nearclip = ()
	,
	fn ext_farclip = ()
	,
	fn extracttrait arg_node = 
	(
		if (ext_begin arg_node) then
		(
			ext_fov();
			ext_nearclip();
			ext_farclip();
			ext_end();
			return xml_trait;
		)
		return undefined;
	)
	,
	fn ext_begin arg_node = 
	(
		xml_trait = undefined;
		node_node = arg_node;
		if node_node != undefined then
		(
			if iskindof node_node camera then
			(
				xml_trait = OmsXML_Element();
				xml_trait.setvalue "camera";
				xml_trait.setattribute "type" node_node.type;
				return true;
			)
		)
		return false;
	)
	,
	fn ext_end = 
	(
		node_node = undefined;
	)
	,
	fn ext_fov = 
	(
		xml_trait.setattribute "FOV"  node_node.fov;
	)
	,
	fn ext_nearclip = 
	(
		xml_trait.setattribute "NearClip"  node_node.nearclip;
	)
	,
	fn ext_farclip = 
	(
		xml_trait.setattribute "FarClip"  node_node.farclip;
	)
)
struct XMLMeshTraitExtractor
(
	node_node = undefined
	,
	xml_trait = undefined
	,
	fn ext_begin arg_node = ()
	,
	fn ext_end = ()
	,
	fn ext_mesh = ()
	,
	fn extracttrait arg_node = 
	(
		if (ext_begin arg_node) then
		(
		)
	)
	,
	fn ext_begin arg_node = 
	(
		xml_trait = undefined;
		node_node = arg_node;
		if node_node != undefined then
		(
			if iskindof node_node editable_mesh then
			(
				xml_trait = OmsXML_Element();
				xml_trait.setvalue "mesh";
				xml_trait.setattribute "Handle" (node_node.handle);
				return true;
			)
		)
		return false;
	)
	,
	fn ext_end = 
	(
		node_node = undefined;
	)
	,
	fn ext_mesh = 
	(
	)
)

struct XMLNodeTraitExtractor
(
	
	fn extracttrait arg_node = 
	(
		local kextractor = undefined;
		local kBaseClass = (superclassof arg_node);
		
		if kBaseClass == camera then
		(
			kextractor = XMLCameraTraitExtractor();
		)
		
		if kextractor != undefined then
		(
			return (kextractor.extracttrait arg_node);
		)
		return undefined;
	)
	
)