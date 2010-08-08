

struct XMLMeshExporter
(
	XML_Root = undefined
	,
	XML_Mesh = undefined
	,
	mesh_mesh = undefined
	,
	value_transform = undefined
	,
	fn ext_begin arg_mesh arg_progressbar = ()
	,
	fn ext_end = ()
	,
	fn ext_vert_position = ()
	,
	fn ext_normal = ()
	,
	fn ext_face = ()
	,
	fn ext_tvert = ()
	,
	fn ext_tface = ()
	,
	fn is_mesh_use_mapping =
	(
		return ((meshop.getNumMapVerts mesh_mesh 1) != 0);
	)
	,
	fn extractdata arg_mesh  = 
	(
		if canconvertto arg_mesh editable_mesh then
		(
			ext_begin arg_mesh ;
			
			ext_vert_position();
			ext_normal();
			ext_face();
			ext_tvert();
			ext_tface();
			
			ext_end();
			return XML_Root;
		)
		return undefined;
		
	)
	,
	fn ext_begin arg_mesh  = 
	(
		mesh_mesh = arg_mesh.mesh;

		XML_Root = OmsXML_Element();
		XML_Mesh = OmsXML_Element();
		XML_Mesh.setvalue "Mesh"
		XML_Root.setvalue "Geometry"
		XML_Root.setattribute "LinkedNode" arg_mesh.inode.handle;
		XML_Root.insertchild (ext_offset_coord arg_mesh.transform arg_mesh.objecttransform);
		XML_Root.insertchild XML_Mesh;
	)
	,
	fn ext_end = 
	(
	)
	,
	fn ext_vert_position = 
	(
		local kVertCount = getnumverts mesh_mesh;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "Vertex"
		kxml_elemental.setattribute "Count" kVertCount;
		for i=1 to kVertCount do
		(
			local kTriPoint = getvert mesh_mesh i;
			kxml_pos = ext_xml_point3 kTriPoint;
			
			kxml_elemental.InsertChild kxml_pos;
		)
		XML_Mesh.InsertChild kxml_elemental;
	)
	,
	fn ext_normal = 
	(
		local kVertCount = getnumverts mesh_mesh;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "Normal"
		kxml_elemental.setattribute "Count" kVertCount;
		for i=1 to kVertCount do
		(
			local kTriPoint = getnormal mesh_mesh i;
			kxml_norm = ext_xml_point3 kTriPoint;
			
			kxml_elemental.InsertChild kxml_norm;
		)
		XML_Mesh.InsertChild kxml_elemental;
	)
	,
	fn ext_face = 
	(
		local kFaceCount = getnumfaces mesh_mesh;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "VertexFace"
		kxml_elemental.setattribute "Count" kFaceCount;
		for i=1 to kFaceCount do
		(
			local kTriPoint = getface mesh_mesh i;
			kxml_face = OmsXML_Element();
			kxml_face.SetValue "Face"
			kxml_face.SetAttribute "index" (i-1);
			kxml_face.SetAttribute "a" (kTriPoint.x-1);
			kxml_face.SetAttribute "b" (kTriPoint.y-1);
			kxml_face.SetAttribute "c" (kTriPoint.z-1);
			
			kxml_elemental.InsertChild kxml_face;
			
		)
		XML_Mesh.InsertChild kxml_elemental;		
	)
	,
	fn ext_tvert = 
	(
		local kTVertCount = getnumtverts mesh_mesh ;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "TVertex"
		kxml_elemental.setattribute "Count" kTVertCount;
		for i=1 to kTVertCount do
		(
			local kTriPoint = gettvert mesh_mesh  i ;
			kxml_norm = ext_xml_point3 kTriPoint;
			
			kxml_elemental.InsertChild kxml_norm;
		)
		XML_Mesh.InsertChild kxml_elemental;	
	)
	,
	fn ext_tface = 
	(
		local kFaceCount = getnumfaces mesh_mesh ;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "TVertexFace"
		kxml_elemental.setattribute "Count" kFaceCount;
		for i=1 to kFaceCount do
		(
			local kTriPoint = gettvface mesh_mesh  i;
			kxml_face = OmsXML_Element();
			kxml_face.SetValue "Face"
			kxml_face.SetAttribute "index" (i-1);
			kxml_face.SetAttribute "a" (kTriPoint.x-1);
			kxml_face.SetAttribute "b" (kTriPoint.y-1);
			kxml_face.SetAttribute "c" (kTriPoint.z-1);
			
			kxml_elemental.InsertChild kxml_face;
			
		)
		XML_Mesh.InsertChild kxml_elemental;		
	)
);

fn export_geom_table arg_array = 
(
	kxml_table = OmsXML_Element();
	kxml_table.setvalue "GeomTable"
	
	local ktotal_count = arg_array.count;
	local kcomplete_extracted_count = 0;
	progressstart "geom table extract"
	
	for kSelectOne in arg_array do
	(
		kexporter = XMLMeshExporter();
		kxml_table.insertchild (kexporter.extractdata kSelectOne);
	
		kcomplete_extracted_count += 1;
		progressupdate ((kcomplete_extracted_count*100)/(ktotal_count));
	)
	progressupdate 100.0f;
	progressend();
	return kxml_table;
)