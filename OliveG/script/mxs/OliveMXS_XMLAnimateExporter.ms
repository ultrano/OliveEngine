
struct XMLAnimateExporter
(
	XML_Root = undefined
	,
	node_node = undefined
	,
	value_totalprogressrate = 0
	,
	value_nowprogressrate = 0
	,
	fn ext_begin arg_node = ()
	,
	fn ext_end = ()
	,
	fn ext_anim_pos = ()
	,
	fn ext_anim_rot = ()
	,
	fn extractdata arg_node =
	(
		ext_begin arg_node;
		ext_anim_pos();
		ext_anim_rot();
		ext_end();
	)
	,
	fn ext_begin arg_node =
	(
		node_node = arg_node;
		XML_Root = OmsXML_Element();
		XML_Root.setvalue "Animation"
		
		local kName = node_node.name;
		local kHandle = node_node.inode.handle;
		kxml_name = omsxml_element();
		kxml_name.setvalue "NodeInfo";
		kxml_name.setattribute "Name"  kName;
		kxml_name.setattribute "Handle"  kHandle;
		
		XML_Root.insertchild kxml_name;
	)
	,
	fn ext_end = ()
	,
	fn ext_anim_pos = 
	(
		local kctrler = node_node.pos.controller;
		local kkeycount = (numkeys kctrler)
		kxml_anim = omsxml_element();
		kxml_anim.setvalue "Animate_Position";
		kxml_anim.setattribute "KeyCount" kkeycount;

		for i=1 to kkeycount do
		(
			kxml_anim_data = omsxml_element();
			kxml_anim_data.setvalue "AnimData";
			kxml_anim_data.setattribute "Tick" (kctrler.keys[i].time.ticks)
			
			local kpos_x = (at time (kctrler.keys[i].time) kctrler.x_position)
			local kpos_y = (at time (kctrler.keys[i].time) kctrler.y_position)
			local kpos_z = (at time (kctrler.keys[i].time) kctrler.z_position)
			
			kxml_anim_data.setattribute "x" kpos_x
			kxml_anim_data.setattribute "y" kpos_y
			kxml_anim_data.setattribute "z" kpos_z
			kxml_anim.insertchild kxml_anim_data;
		)
		XML_Root.insertchild kxml_anim;
	)
	,
	fn ext_anim_rot = 
	(
		local kctrler = node_node.rotation.controller;
		local kkeycount = (numkeys kctrler);
		kxml_anim = omsxml_element();
		kxml_anim.setvalue "Animate_Rotation";
		kxml_anim.setattribute "KeyCount" kkeycount;

		for i=1 to kkeycount do
		(
			kxml_anim_data = omsxml_element();
			kxml_anim_data.setvalue "AnimData";
			kxml_anim_data.setattribute "Tick" (kctrler.keys[i].time.ticks)
			
			local keuler_x = (at time (kctrler.keys[i].time) kctrler.x_rotation)
			local keuler_y = (at time (kctrler.keys[i].time) kctrler.y_rotation)
			local keuler_z = (at time (kctrler.keys[i].time) kctrler.z_rotation)
			
			kxml_anim_data.setattribute "x_rotation" keuler_x;
			kxml_anim_data.setattribute "y_rotation" keuler_y;
			kxml_anim_data.setattribute "z_rotation" keuler_z;
			kxml_anim.insertchild kxml_anim_data;
		)
		XML_Root.insertchild kxml_anim;
	)
	,
	fn exportdata arg_fileroute = 
	(
		local kXMLDoc = OmsXML_Document();
		kXMLDoc.SetTopElement XML_Root;
		kXMLDoc.SaveXML arg_fileroute;
	)
)