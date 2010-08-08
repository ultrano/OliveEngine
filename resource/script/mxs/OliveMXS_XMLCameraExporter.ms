
struct XMLCameraExporter
(
	node_node = undefined
	,
	XML_Root = undefined
	,
	fn ext_begin arg_node = ()
	,
	fn ext_end = ()
	,
	fn ext_camerainfo = ()
	,
	fn ext_clipplane = ()
	,
	fn extractdata arg_node = 
	(
		if (ext_begin arg_node) then
		(
			ext_camerainfo();
			ext_clipplane();
			
			ext_end();
			return XML_Root;
		)
		return undefined;
	)
	,
	fn ext_begin arg_node = 
	(
		XML_Root = undefined;
		node_node = arg_node;
		if node_node != undefined then
		(
			if iskindof node_node camera then
			(
				XML_Root = OmsXML_Element();
				XML_Root.setvalue "Camera";
				XML_Root.setattribute "Handle" node_node.inode.handle;
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
	fn ext_camerainfo = 
	(
		local kxml_element = OmsXML_Element();
		kxml_element.setvalue "CameraInfo"
		kxml_element.setattribute "Type" node_node.type;
		kxml_element.setattribute "FOV"  node_node.fov;
		XML_Root.insertchild kxml_element;
	)
	,
	fn ext_clipplane = 
	(
		local kxml_element = OmsXML_Element();
		kxml_element.setvalue "ClipPlane"
		kxml_element.setattribute "NearClip"  node_node.nearclip;
		kxml_element.setattribute "FarClip"  node_node.farclip;
		XML_Root.insertchild kxml_element;
	)
)

fn export_camera_table arg_array = 
(
	kxml_table = OmsXML_Element();
	kxml_table.setvalue "CameraTable"
	for kSelectOne in arg_array do
	(
		kexporter = XMLCameraExporter();
		kxml_table.insertchild (kexporter.extractdata kSelectOne);
	)
	return kxml_table;
)