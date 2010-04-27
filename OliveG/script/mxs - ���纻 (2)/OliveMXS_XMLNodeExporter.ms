

struct XMLNodeExporter
(
	XML_Root = undefined
	,
	node_node = undefined
	,
	value_totalprogressrate = 0
	,
	value_nowprogressrate = 0
	,
	value_world_transform = undefined
	,
	value_local_transform = undefined
	,
	extractor_nodetrait = undefined
	,
	fn increase_progress = ()
	,
	fn ext_begin arg_node  = ()
	,
	fn ext_end = ()
	,
	fn ext_nodeinfo = ()
	,
	fn ext_parentinfo = ()
	,
	fn ext_world_coord = ()
	,
	fn ext_local_coord = ()
	,
	fn ext_position arg_transform = ()
	,
	fn ext_rotation arg_transform = ()
	,
	fn ext_scale arg_transform = ()
	,
	fn ext_scale_rot arg_transform = ()
	,
	fn ext_nodetrait = ()
	,
	fn extractdata arg_node  = 
	(
		if iskindof arg_node node then
		(
			ext_begin arg_node ;
			value_totalprogressrate = 12;
			ext_nodeinfo();		-- step 1
			ext_parentinfo();		-- step 2
			ext_world_coord();	--	step 3~7
			ext_local_coord();	--	step 8~12
			ext_end();
			
		)
	)
	,
	fn increase_progress = 
	(
			value_nowprogressrate += 1;
			local kprogress;
			kprogress = (value_nowprogressrate* 100/value_totalprogressrate) 
			progressupdate (kprogress as integer);
			format "%\n" kprogress ;
	)
	,
	fn ext_begin arg_node  = 
	(
		progressstart "node data extract"
		node_node = arg_node;
		value_world_transform = node_node.transform;
		value_local_transform	=	node_node.transform;
		value_totalprogressrate = 0;
		value_nowprogressrate = 0;
		XML_Root = OmsXML_Element();
		XML_Root.setvalue "Node"
	)
	,
	fn ext_end = 
	(
		progressupdate 100.0f;
		progressend();
		value_totalprogressrate = 0;
		value_nowprogressrate = 0;
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
		increase_progress();
	)
	,
	fn ext_parentinfo = 
	(
		knode_parent = node_node.parent;
		if knode_parent != undefined then
		(
			value_local_transform = (value_world_transform * (inverse knode_parent.transform));
			kxml_parentinfo = omsxml_element();
			kxml_parentinfo.setvalue "ParentInfo";
			kxml_parentinfo.setattribute "Handle" knode_parent.handle;
			XML_Root.insertchild kxml_parentinfo;
		)
		increase_progress();
	)
	,
	fn ext_world_coord = 
	(
		kxml_world_coord = omsxml_element();		
		kxml_world_coord.setvalue "WorldCoord";
		kxml_world_coord.insertchild (ext_position(value_world_transform));		-- step 3
		kxml_world_coord.insertchild (ext_rotation(value_world_transform));		-- step 4
		kxml_world_coord.insertchild (ext_scale(value_world_transform));		-- step 5
		kxml_world_coord.insertchild (ext_scale_rot(value_world_transform));	-- step 6
		XML_Root.insertchild kxml_world_coord;
		increase_progress();																				--	step 7
	)
	,
	fn ext_local_coord = 
	(
		kxml_local_coord = OmsXML_Element();
		kxml_local_coord.SetValue "LocalCoord";
		kxml_local_coord.insertchild (ext_position(value_local_transform));		-- step 8
		kxml_local_coord.insertchild (ext_rotation(value_local_transform));    	-- step 9
		kxml_local_coord.insertchild (ext_scale(value_local_transform));      	-- step 10
		kxml_local_coord.insertchild (ext_scale_rot(value_local_transform));		-- step 11
		XML_Root.insertchild kxml_local_coord;                                                     
		increase_progress();																				--	step 12
	)
	,
	fn ext_position arg_transform = 
	(
		kxml_position = OmsXML_Element();
		kxml_position.SetValue "Position";
		kxml_position.SetAttribute "x" arg_transform.translationpart.x;
		kxml_position.SetAttribute "y" arg_transform.translationpart.y;
		kxml_position.SetAttribute "z" arg_transform.translationpart.z;
		increase_progress();
		return kxml_position;
	)
	,
	fn ext_rotation arg_transform = 
	(
		kxml_rotation = OmsXML_Element();
		kxml_rotation.SetValue "Rotation";
		kxml_rotation.SetAttribute "x" arg_transform.rotationpart.x;
		kxml_rotation.SetAttribute "y" arg_transform.rotationpart.y;
		kxml_rotation.SetAttribute "z" arg_transform.rotationpart.z;
		kxml_rotation.SetAttribute "w" arg_transform.rotationpart.w;
		increase_progress();
		return kxml_rotation;
	)
	,
	fn ext_scale arg_transform = 
	(
		kxml_scale = OmsXML_Element();
		kxml_scale.SetValue "Scale";
		kxml_scale.SetAttribute "x" arg_transform.scalepart.x;
		kxml_scale.SetAttribute "y" arg_transform.scalepart.y;
		kxml_scale.SetAttribute "z" arg_transform.scalepart.z;
		increase_progress();
		return kxml_scale;
	)
	,
	fn ext_scale_rot arg_transform = 
	(
		kxml_rotation_rot = OmsXML_Element();
		kxml_rotation_rot.SetValue "ScaleRotation";
		kxml_rotation_rot.SetAttribute "x" arg_transform.scalerotationpart.x;
		kxml_rotation_rot.SetAttribute "y" arg_transform.scalerotationpart.y;
		kxml_rotation_rot.SetAttribute "z" arg_transform.scalerotationpart.z;
		kxml_rotation_rot.SetAttribute "w" arg_transform.scalerotationpart.w;
		increase_progress();
		return kxml_rotation_rot;			
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
	,
	fn exportdata arg_fileroute = 
	(		
		if arg_fileroute != undefined then
		(
			
			ext_nodetrait();
			
			local kXMLDoc = OmsXML_Document();
			kXMLDoc.SetTopElement XML_Root;
			kXMLDoc.SaveXML arg_fileroute;
			
			extractor_nodetrait.exporttrait arg_fileroute;
		)
	)
)