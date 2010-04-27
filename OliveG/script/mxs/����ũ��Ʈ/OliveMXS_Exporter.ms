struct OliveMXS_Exporter
(
-- 	begin_member_values
	struct_ExportFile = Oms_File()
	,
	string_ExportDirectory = ""
	,
-- 	end_member_values
	
-- 	begin_member_functions_declare
-- 	end_member_functions_declare
	
-- 	begin_member_functions_implement
	fn OmsExportDirectory arg_Directory = 
	(
		if iskindof arg_Directory string then
		(
			string_ExportDirectory = arg_Directory;
		)
	)
	,
	fn OmsExportMesh arg_Mesh arg_ExportFileName = 
	(
		if canconvertto arg_Mesh editable_mesh  then
		(
			local kMesh = arg_Mesh.mesh;
			if kMesh != undefined and arg_ExportFileName != undefined then
			(
				
				local kXMLDoc = OmsXML_Document();
				local kXMLEle_Mesh = OmsXML_Element();

				kXMLEle_Mesh.SetValue "Mesh"
				
				-- Geometry Export --
				local kXMLEle_Geometry = OmsXML_Element();
				kXMLEle_Geometry.SetValue "Geometry";
				
				---- Vertex Export ----
				
				------ Position Export ------
				local kXMLEle_Verties = OmsXML_Element();
				kXMLEle_Verties.SetValue "Verties";
				local kVertCount = getnumverts kMesh;
				kXMLEle_Verties.SetAttribute "Count" kVertCount;
				
				local kXMLEle_Position = OmsXML_Element();
				kXMLEle_Position.SetValue "Position"
				for i=1 to kVertCount do
				(
					local kTriPoint = getvert kMesh i;
					kXMLEle_Pos = OmsXML_Element();
					kXMLEle_Pos.SetValue "Pos"
					kXMLEle_Pos.SetAttribute "index" (i-1);
					kXMLEle_Pos.SetAttribute "x" kTriPoint.x;
					kXMLEle_Pos.SetAttribute "y" kTriPoint.y;
					kXMLEle_Pos.SetAttribute "z" kTriPoint.z;
					
					kXMLEle_Position.InsertChild kXMLEle_Pos;
				)
				kXMLEle_Verties.InsertChild kXMLEle_Position;
				------------------------------------------------
				
				------ Normal Export ------
				local kXMLEle_Normal = OmsXML_Element();
				kXMLEle_Normal.SetValue "Normal"
				for i=1 to kVertCount do
				(
					local kTriPoint = getnormal kMesh i;
					kXMLEle_Norm = OmsXML_Element();
					kXMLEle_Norm.SetValue "Norm"
					kXMLEle_Norm.SetAttribute "index" (i-1);
					kXMLEle_Norm.SetAttribute "x" kTriPoint.x;
					kXMLEle_Norm.SetAttribute "y" kTriPoint.y;
					kXMLEle_Norm.SetAttribute "z" kTriPoint.z;
					
					kXMLEle_Normal.InsertChild kXMLEle_Norm;
				)
				kXMLEle_Verties.InsertChild kXMLEle_Normal;
				------------------------------------------------
				
				kXMLEle_Geometry.InsertChild kXMLEle_Verties;
				------------------------------------------------
				
				---- Faces Export ----
				local kXMLEle_Faces = OmsXML_Element();
				kXMLEle_Faces.SetValue "Faces";
				local kFaceCount = getnumfaces kMesh;
				kXMLEle_Faces.SetAttribute "Count" kFaceCount;
				for i = 1 to kFaceCount do
				(
					local kTriPoint = getface kMesh i;
					kXMLEle_Face = OmsXML_Element();
					kXMLEle_Face.SetValue "Face"
					kXMLEle_Face.SetAttribute "index" (i-1);
					kXMLEle_Face.SetAttribute "a" (kTriPoint.x-1);
					kXMLEle_Face.SetAttribute "b" (kTriPoint.y-1);
					kXMLEle_Face.SetAttribute "c" (kTriPoint.z-1);

					kXMLEle_Faces.InsertChild kXMLEle_Face;
				)
				kXMLEle_Geometry.InsertChild kXMLEle_Faces;
				------------------------------------------------
				
				kXMLEle_Mesh.InsertChild kXMLEle_Geometry;
				------------------------------------------------
				
				------------------------------------------------
				
				-- Texture Info Export --
				local kXMLEle_Texture = OmsXML_Element();
				kXMLEle_Texture.SetValue "Texture"
				
				---- TexCoord Export ----
				------ TPosition Export ------
				local kXMLEle_TPosition = OmsXML_Element();
				local kTVertCount = getnumtverts kMesh;
				kXMLEle_TPosition.SetValue "TVerties";
				kXMLEle_TPosition.setattribute "Count" kTVertCount;
				for i=1 to kTVertCount do
				(
					local kTriPoint = gettvert kMesh i;
					kXMLEle_TPos = OmsXML_Element();
					kXMLEle_TPos.SetValue "TPos"
					kXMLEle_TPos.SetAttribute "index" (i-1);
					kXMLEle_TPos.SetAttribute "x" kTriPoint.x;
					kXMLEle_TPos.SetAttribute "y" kTriPoint.y;
					kXMLEle_TPos.SetAttribute "z" kTriPoint.z;
					
					kXMLEle_TPosition.InsertChild kXMLEle_TPos;
				)
				kXMLEle_Texture.InsertChild  kXMLEle_TPosition
				------------------------------------------------
				
				------ TFace Export ------
				local kXMLEle_TFaces = OmsXML_Element();
				local kTFaceCount = getnumfaces kMesh;
				kXMLEle_TFaces.SetValue "TFaces" ;
				kXMLEle_TFaces.setattribute "Count" kTFaceCount;
				for i=1 to kTFaceCount do
				(
					local kTriPoint = gettvface kMesh i;
					kXMLEle_TFace = OmsXML_Element();
					kXMLEle_TFace.SetValue "TFace"
					kXMLEle_TFace.SetAttribute "index" (i-1);
					kXMLEle_TFace.SetAttribute "a" (kTriPoint.x-1);
					kXMLEle_TFace.SetAttribute "b" (kTriPoint.y-1);
					kXMLEle_TFace.SetAttribute "c" (kTriPoint.z-1);
					
					kXMLEle_TFaces.InsertChild kXMLEle_TFace;
				)
				kXMLEle_Texture.InsertChild  kXMLEle_TFaces
				------------------------------------------------
				
				------------------------------------------------
				
				kXMLEle_Mesh.InsertChild kXMLEle_Texture;
				------------------------------------------------
				
				kXMLDoc.SetTopElement kXMLEle_Mesh;
				local kFileName = stringstream "";
				format "%/Mesh_%.xml" string_ExportDirectory arg_ExportFileName to:kFileName
				kFileName = kFileName as string;
				kXMLDoc.SaveXML kFileName;
				return true;
			)
			return false;
		)
	)
	,
	fn OmsExportNode arg_Node = 
	(
		local kNode = arg_Node;
		local kNodeIndex = 0;
		local kMeshIndex = 0;

		if iskindof kNode node then
		(
			
			local kXMLDoc = OmsXML_Document();
			local kXMLEle_Node = OmsXML_Element();
			kXMLEle_Node.SetValue "Node";
			
			-- Name --
			local kXMLEle_Name = OmsXML_Element();
			kXMLEle_Name.SetValue "Name";
			kXMLEle_Name.SetText kNode.name;
			kXMLEle_Node.InsertChild kXMLEle_Name;
			-----------
			
			-- DefaultTransform --
			local kXMLEle_DT = OmsXML_Element();
			kXMLEle_DT.SetValue "DefaultTransform";
			
			---- Matrix ----
			local kXMLEle_Mat = OmsXML_Element();
			kXMLEle_Mat.SetValue "Matrix";
			
			------ MatRow ------
			local kTransMat = kNode.transform;
			for i = 1 to 4 do
			(
				local kXMLEle_Row = OmsXML_Element();
				local kRowName = stringstream "";
				format "Row%" i to:kRowName;
				kRowName = kRowName as string;
				
				kXMLEle_Row.SetValue kRowName;
				kXMLEle_Row.SetAttribute "Col1" kTransMat[i][1];
				kXMLEle_Row.SetAttribute "Col2" kTransMat[i][2];
				kXMLEle_Row.SetAttribute "Col3" kTransMat[i][3];
				kXMLEle_Row.SetAttribute "Col4" 0;
				
				kXMLEle_Mat.InsertChild kXMLEle_Row;				
			)
			--------------------
			
			kXMLEle_DT.InsertChild kXMLEle_Mat
			---------------
			
			---- ScaleRot ----
			local kXMLEle_DSCRot = OmsXML_Element();
			kXMLEle_DSCRot.SetValue "ScaleRot";
			kXMLEle_DSCRot.SetAttribute "x" kTransMat.scalerotationpart.x;
			kXMLEle_DSCRot.SetAttribute "y" kTransMat.scalerotationpart.y;
			kXMLEle_DSCRot.SetAttribute "z" kTransMat.scalerotationpart.z;
			kXMLEle_DSCRot.SetAttribute "w" kTransMat.scalerotationpart.w;
			
			kXMLEle_DT.InsertChild kXMLEle_DSCRot;
			----------------
			
			---- Scale ----
			local kXMLEle_DScale = OmsXML_Element();
			kXMLEle_DScale.SetValue "Scale";
			kXMLEle_DScale.SetAttribute "x" kTransMat.scalepart.x;
			kXMLEle_DScale.SetAttribute "y" kTransMat.scalepart.y;
			kXMLEle_DScale.SetAttribute "z" kTransMat.scalepart.z;
			
			kXMLEle_DT.InsertChild kXMLEle_DScale;
			----------------
			
			---- Rotation ----
			local kXMLEle_DRot = OmsXML_Element();
			kXMLEle_DRot.SetValue "Rotation";
			kXMLEle_DRot.SetAttribute "x" kTransMat.rotationpart.x;
			kXMLEle_DRot.SetAttribute "y" kTransMat.rotationpart.y;
			kXMLEle_DRot.SetAttribute "z" kTransMat.rotationpart.z;
			kXMLEle_DRot.SetAttribute "w" kTransMat.rotationpart.w;
			
			kXMLEle_DT.InsertChild kXMLEle_DRot;
			----------------
			
			---- Position ----
			local kXMLEle_DPos = OmsXML_Element();
			kXMLEle_DPos.SetValue "Position";
			kXMLEle_DPos.SetAttribute "x" kTransMat.translationpart.x;
			kXMLEle_DPos.SetAttribute "y" kTransMat.translationpart.y;
			kXMLEle_DPos.SetAttribute "z" kTransMat.translationpart.z;
			
			kXMLEle_DT.InsertChild kXMLEle_DPos;
			----------------
			
			kXMLEle_Node.InsertChild kXMLEle_DT;
			--------------------
			
			-- Parent --
			if kNode.parent != undefined then
			(
				local kXMLEle_Parent = OmsXML_Element();
				kXMLEle_Parent.SetValue "Parent";
				kXMLEle_Parent.SetText kNode.parent.name;
				kXMLEle_Node.insertchild kXMLEle_Parent;
			)
			-----------
			
			-- MeshLink --
			local kbIsHasMesh = OmsExportMesh kNode kNode.name;
			if kbIsHasMesh == true then
			(
				local kXMLEle_MeshLink = OmsXML_Element();
				kXMLEle_MeshLink.SetValue "MeshLink"
				kXMLEle_MeshLink.SetText kNode.name;
				
				kXMLEle_Node.InsertChild kXMLEle_MeshLink;
				kMeshIndex += 1;
			)
			-------------
			
			-- export --
			kXMLDoc.SetTopElement kXMLEle_Node;
			local kFileName = stringstream "";
			format "%/Node_%.xml" string_ExportDirectory kNode.name to:kFileName
			kFileName = kFileName as string;
			kXMLDoc.SaveXML kFileName;
			-----------
			
			kNodeIndex += 1;
		)
	)
	,
	fn OmsDistributeExport = 
	(
		local kSelectedArray = selection as array;
		
		
		for kObj in kSelectedArray do
		(
			OmsExportNode kObj;
		)
		
	)
	
	
-- 	end_member_fucntions_implement
);
