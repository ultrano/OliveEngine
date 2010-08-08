include "OliveMXS_XML.ms"
include "OliveMXS_XMLNodeTraitExtractor.ms"

struct XMLNodeExporter
(
	XML_Root = undefined
	,
	node_node = undefined
	,
	ctrl_progressbar = undefined
	,
	value_transform = undefined
	,
	fn increase_progress = ()
	,
	fn ext_begin arg_node arg_progressbar = ()
	,
	fn ext_end = ()
	,
	fn ext_nodeinfo = ()
	,
	fn ext_position = ()
	,
	fn ext_rotation = ()
	,
	fn ext_scale = ()
	,
	fn ext_scale_rot = ()
	,
	fn ext_nodetrait = ()
	,
	fn extractdata arg_node arg_progressbar = 
	(
		if iskindof arg_node node then
		(
			ext_begin arg_node arg_progressbar;
			ext_nodeinfo();
			ext_position();
			ext_rotation();
			ext_scale();
			ext_scale_rot();
			ext_nodetrait();
		)
	)
	,
	fn ext_begin arg_node arg_progressbar = 
	(
		node_node = arg_node;
		value_transform = node_node.transform;
		ctrl_progressbar = arg_progressbar;
		XML_Root = OmsXML_Element();
		XML_Root.setvalue "Node"
	)
	,
	fn ext_end = 
	(
		if ctrl_progressbar != undefined then
		(
			ctrl_progressbar.value = 0;
		)
		ctrl_progressbar = undefined;
	)
	,
	fn ext_nodeinfo = 
	(
		local kName = node_node.name;
		local kHandle = node_node.handle;
		local kClass = (classof node_node);
		local kBaseClass = (superClassOf  node_node);
		kxml_name = omsxml_element();
		kxml_name.setvalue "NodeInfo";
		kxml_name.setattribute "Name"  kName;
		kxml_name.setattribute "Handle"  kHandle;
		kxml_name.setattribute "Class"  kClass;
		kxml_name.setattribute "BaseClass"  kBaseClass;
		XML_Root.insertchild kxml_name;
	)
	,
	fn ext_position = 
	(
		kxml_position = OmsXML_Element();
		kxml_position.SetValue "Position";
		kxml_position.SetAttribute "x" value_transform.translationpart.x;
		kxml_position.SetAttribute "y" value_transform.translationpart.y;
		kxml_position.SetAttribute "z" value_transform.translationpart.z;
		XML_Root.insertchild kxml_position;
	)
	,
	fn ext_rotation = 
	(
		kxml_rotation = OmsXML_Element();
		kxml_rotation.SetValue "Rotation";
		kxml_rotation.SetAttribute "x" value_transform.rotationpart.x;
		kxml_rotation.SetAttribute "y" value_transform.rotationpart.y;
		kxml_rotation.SetAttribute "z" value_transform.rotationpart.z;
		kxml_rotation.SetAttribute "w" value_transform.rotationpart.w;
		XML_Root.insertchild kxml_rotation;		
	)
	,
	fn ext_scale = 
	(
		kxml_scale = OmsXML_Element();
		kxml_scale.SetValue "Scale";
		kxml_scale.SetAttribute "x" value_transform.scalepart.x;
		kxml_scale.SetAttribute "y" value_transform.scalepart.y;
		kxml_scale.SetAttribute "z" value_transform.scalepart.z;
		XML_Root.insertchild kxml_scale;		
	)
	,
	fn ext_scale_rot = 
	(
		kxml_rotation_rot = OmsXML_Element();
		kxml_rotation_rot.SetValue "ScaleRotation";
		kxml_rotation_rot.SetAttribute "x" value_transform.scalerotationpart.x;
		kxml_rotation_rot.SetAttribute "y" value_transform.scalerotationpart.y;
		kxml_rotation_rot.SetAttribute "z" value_transform.scalerotationpart.z;
		kxml_rotation_rot.SetAttribute "w" value_transform.scalerotationpart.w;
		XML_Root.insertchild kxml_rotation_rot;				
	)
	,
	fn exportdata arg_fileroute = 
	(		
		if arg_fileroute != undefined then
		(
			local kXMLDoc = OmsXML_Document();
			kXMLDoc.SetTopElement XML_Root;
			kXMLDoc.SaveXML arg_fileroute;
		)
	)
	,
	fn ext_nodetrait = 
	(
		kxml_trait = OmsXML_Element();
		kxml_trait.SetValue "NodeTrait";
		extractor_nodetrait = XMLNodeTraitExtractor();
		kxml_trait.insertchild (extractor_nodetrait.extracttrait node_node );	
		XML_Root.insertchild kxml_trait		
	)
)