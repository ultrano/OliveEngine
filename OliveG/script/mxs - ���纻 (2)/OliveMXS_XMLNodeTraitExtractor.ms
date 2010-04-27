include "OliveMXS_XML.ms"
include "OliveMXS_XMLNodeExporter.ms"
include "OliveMXS_XMLMeshExporter.ms"

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
	,
	fn exporttrait arg_filename = ()
)


struct XMLMeshTraitExtractor
(
	node_node = undefined
	,
	handle_node = 0
	,
	xml_trait = undefined
	,
	meshdata = undefined
	,
	fn ext_begin arg_node = ()
	,
	fn ext_end = ()
	,
	fn ext_mesh = ()
	,
	fn ext_offset_coord =()
	,
	fn ext_position arg_transform = 
	(
		kxml_position = OmsXML_Element();
		kxml_position.SetValue "Position";
		kxml_position.SetAttribute "x" arg_transform.translationpart.x;
		kxml_position.SetAttribute "y" arg_transform.translationpart.y;
		kxml_position.SetAttribute "z" arg_transform.translationpart.z;
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
		return kxml_rotation_rot;			
	)
	,
	fn extracttrait arg_node = 
	(
		if (ext_begin arg_node) then
		(
			ext_mesh();
			ext_offset_coord();
			ext_end();
		)
		return xml_trait;
	)
	,
	fn ext_begin arg_node = 
	(
		handle_node = 0;
		meshdata = undefined;
		xml_trait = undefined;
		node_node = arg_node;
		if node_node != undefined then
		(
			if iskindof node_node geometryclass then
			(
				handle_node = node_node.handle;
				xml_trait = OmsXML_Element();
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
		xml_trait.setvalue "mesh";
		xml_trait.setattribute "Handle" (node_node.handle);
		meshdata = XMLMeshExporter();
		meshdata.extractdata node_node;		
	)
	,
	fn ext_offset_coord =
	(
		local kobjtrans 		= node_node.objecttransform;
		local knodetrans 	= node_node.transform;
		local kmeshtrans 	= kobjtrans * (inverse knodetrans);
		
		kxml_offset_coord = OmsXML_Element();
		kxml_offset_coord.SetValue "OffsetCoord";
		kxml_offset_coord.insertchild (ext_position(kmeshtrans));		
		kxml_offset_coord.insertchild (ext_rotation(kmeshtrans));    	
		kxml_offset_coord.insertchild (ext_scale(kmeshtrans));      	
		kxml_offset_coord.insertchild (ext_scale_rot(kmeshtrans));	
		xml_trait.insertchild kxml_offset_coord;
	)
	,
	fn exporttrait arg_filename = 
	(
		local strdirectory = getFilenamePath arg_filename;
		local strfilename = getFilenameFile arg_filename;
		local strextentiontype = getFilenameType arg_filename;
		local strfinalname = "";
		strfinalname = strfinalname as stringstream;
		format "%%_mesh_%%" strdirectory strfilename handle_node strextentiontype to:strfinalname;
		strfinalname = strfinalname as string;
		
		if meshdata != undefined then
		(
			meshdata.exportdata strfinalname;
		)
	)
)

struct XMLNodeTraitExtractor
(
	extractor = undefined
	,	
	fn extracttrait arg_node = 
	(
		local kextractor = undefined;
		local kBaseClass = (superclassof arg_node);
		
		print (kBaseClass as string);
		if kBaseClass == camera then
		(
			extractor = XMLCameraTraitExtractor();
		)
		else if kBaseClass == geometryclass then
		(
			extractor = XMLMeshTraitExtractor();
		)
		
		if extractor != undefined then
		(
			return (extractor.extracttrait arg_node);
		)
		return undefined;
	)
	,
	fn exporttrait arg_filename =
	(
		if extractor != undefined then
		(
			return (extractor.exporttrait (arg_filename));
		)		
	)
	
)