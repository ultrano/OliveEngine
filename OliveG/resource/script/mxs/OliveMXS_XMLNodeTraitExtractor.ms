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
	fn extracttrait arg_node = 
	(
		if (ext_begin arg_node) then
		(
			ext_mesh();
			xml_trait.insertchild (ext_offset_coord arg_node.transform arg_node.objecttransform);
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
			if arg_node.ishidden == false then
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