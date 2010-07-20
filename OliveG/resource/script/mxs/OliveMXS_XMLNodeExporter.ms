
include "OliveMXS_XMLAnimateExporter.ms"

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
	fn ext_animation = ()
	,
	fn extractdata arg_node  = 
	(
		if iskindof arg_node node then
		(
			ext_begin arg_node ;
			value_totalprogressrate = 13;
			ext_nodeinfo();		-- step 1
			ext_parentinfo();		-- step 2
			ext_world_coord();	--	step 3~7
			ext_local_coord();	--	step 8~12
			ext_animation();		--	step 13
			ext_end();
			return XML_Root;
		)
	)
	,
	fn ext_begin arg_node  = 
	(
		node_node = arg_node;
		local ktransform;
		ktransform = at time animationrange.start node_node.transform;
		value_world_transform = ktransform;
		value_local_transform	=	ktransform;
		XML_Root = OmsXML_Element();
		XML_Root.setvalue "Node"
		XML_Root.setattribute "Handle" arg_node.inode.handle;
		
		local knode_parent = node_node.parent;
		if knode_parent != undefined then
		(
			XML_Root.setattribute "ParentHandle" knode_parent.inode.handle;
		)
	)
	,
	fn ext_end = 
	(
	)
	,
	fn ext_nodeinfo = 
	(
		local kName = node_node.name;
		local kHandle = node_node.inode.handle;
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
	fn ext_parentinfo = 
	(
		knode_parent = node_node.parent;
		if knode_parent != undefined then
		(
			local ktransform;
			ktransform = at time animationrange.start knode_parent.transform;
			value_local_transform = (value_world_transform * (inverse ktransform));
			kxml_parentinfo = omsxml_element();
			kxml_parentinfo.setvalue "ParentInfo";
			kxml_parentinfo.setattribute "Handle" knode_parent.handle;
			XML_Root.insertchild kxml_parentinfo;
		)
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
	)
	,
	fn ext_animation = 
	(
		if (iskindof node_node biped_object )==false then
		(
			if node_node.isanimated then
			(
				kext_anim = XMLAnimateExporter();
				kext_anim.extractdata node_node;
				XML_Root.insertchild kext_anim.XML_Root;		
			)
		)
	)
)

fn export_node_table arg_node_array = 
(
	kxml_node_table = OmsXML_Element();
	kxml_node_table.setvalue "NodeTable"
	
	local ktotal_count = arg_node_array.count;
	local kcomplete_extracted_count = 0;
	progressstart "node table extract"
	for kSelectOne in arg_node_array do
	(
		kexporter = XMLNodeExporter();
		kxml_node_table.insertchild (kexporter.extractdata kSelectOne);
		kcomplete_extracted_count += 1;
		progressupdate ((kcomplete_extracted_count*100)/(ktotal_count));
	)
	progressupdate 100.0f;
	progressend();
	return kxml_node_table;
)