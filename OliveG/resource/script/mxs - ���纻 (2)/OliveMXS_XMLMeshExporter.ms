

struct XMLMeshExporter
(
	XML_Root = undefined
	,
	mesh_mesh = undefined
	,
	value_transform = undefined
	,
	value_totalprogressrate = 0
	,
	value_nowprogressrate = 0
	,
	fn increase_progress = ()
	,
	fn ext_begin arg_mesh arg_progressbar = ()
	,
	fn ext_end = ()
	,
	fn ext_count = ()
	,
	fn ext_position = ()
	,
	fn ext_normal = ()
	,
	fn ext_face = ()
	,
	fn extractdata arg_mesh  = 
	(
		ext_begin arg_mesh ;
		
		ext_count();
		ext_position();
		ext_normal();
		ext_face();
		
		ext_end();
		
	)
	,
	fn increase_progress = 
	(
		value_nowprogressrate += 1;
		local kprogress;
		kprogress = (value_nowprogressrate* 100/value_totalprogressrate) 
		progressupdate (kprogress as integer);
		--format "%\n" kprogress ;
	)
	,
	fn ext_begin arg_mesh  = 
	(
		progressstart "mesh data extract"

		mesh_mesh = copy arg_mesh.mesh;
-- 		local kobjtrans 		= arg_mesh.objecttransform;
-- 		local knodetrans 	= arg_mesh.transform;
-- 		local kmeshtrans 	= kobjtrans;
-- 		kmeshtrans = kobjtrans * (inverse knodetrans);
-- 		transform mesh_mesh kmeshtrans;
		
		
		value_totalprogressrate = 0;
		value_nowprogressrate = 0;
		XML_Root = OmsXML_Element();
		XML_Root.setvalue "Mesh"
	)
	,
	fn ext_end = 
	(
		progressupdate 100.0f;
		progressend();
		value_totalprogressrate = 0;
		value_nowprogressrate = 0;
		delete mesh_mesh;
	)
	,
	fn ext_count = 
	(
		local kVertCount = getnumverts mesh_mesh;
		local kFaceCount = getnumfaces mesh_mesh;
		kxml_count = omsxml_element();
		kxml_count.setvalue "Count";
		kxml_count.setattribute "VertCount"  kVertCount;
		kxml_count.setattribute "FaceCount"  kFaceCount;
		XML_Root.insertchild kxml_count;
		
		value_totalprogressrate += kVertCount; -- position;
		value_totalprogressrate += kVertCount; -- normal;
		value_totalprogressrate += kFaceCount; -- face;
	)
	,
	fn ext_position = 
	(
		local kVertCount = getnumverts mesh_mesh;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "Position"
		for i=1 to kVertCount do
		(
			local kTriPoint = getvert mesh_mesh i;
			kxml_pos = OmsXML_Element();
			kxml_pos.SetValue "Pos"
			kxml_pos.SetAttribute "index" (i-1);
			kxml_pos.SetAttribute "x" kTriPoint.x;
			kxml_pos.SetAttribute "y" kTriPoint.y;
			kxml_pos.SetAttribute "z" kTriPoint.z;
			
			kxml_elemental.InsertChild kxml_pos;
			
			increase_progress();
		)
		XML_Root.InsertChild kxml_elemental;
	)
	,
	fn ext_normal = 
	(
		local kVertCount = getnumverts mesh_mesh;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "Normal"
		for i=1 to kVertCount do
		(
			local kTriPoint = getnormal mesh_mesh i;
			kxml_norm = OmsXML_Element();
			kxml_norm.SetValue "Norm"
			kxml_norm.SetAttribute "index" (i-1);
			kxml_norm.SetAttribute "x" kTriPoint.x;
			kxml_norm.SetAttribute "y" kTriPoint.y;
			kxml_norm.SetAttribute "z" kTriPoint.z;
			
			kxml_elemental.InsertChild kxml_norm;
			
			increase_progress();
		)
		XML_Root.InsertChild kxml_elemental;
	)
	,
	fn ext_face = 
	(
		local kFaceCount = getnumfaces mesh_mesh;
		local kxml_elemental = OmsXML_Element();
		kxml_elemental.SetValue "FaceIndex"
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
			
			increase_progress();
		)
		XML_Root.InsertChild kxml_elemental;		
	)
	,
	fn exportdata arg_fileroute = 
	(
		local kXMLDoc = OmsXML_Document();
		kXMLDoc.SetTopElement XML_Root;
		kXMLDoc.SaveXML arg_fileroute;
	)
);