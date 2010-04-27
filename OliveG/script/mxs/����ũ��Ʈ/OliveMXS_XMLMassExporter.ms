
fn getselectfilename arg_filename arg_name arg_handle = 
(
	local strdirectory = getFilenamePath arg_filename;
	local strfilename = getFilenameFile arg_filename;
	local strextentiontype = getFilenameType arg_filename;
	
	local strfinalname = "";
	
	strfinalname = strfinalname as stringstream;
	
	format "%%_%_%%" strdirectory strfilename arg_name arg_handle strextentiontype to:strfinalname;
	
	strfinalname = strfinalname as string;
	return strfinalname;
);

struct XMLMassExporter
(
	XML_Root = undefined
	,
	node_node = undefined
	,
	value_totalprogressrate = 0
	,
	value_nowprogressrate = 0
	,
	array_nodeexporters = #()
	,
	fn increase_progress = ()
	,
	fn addexportnode arg_node = 
	(
	)
	,
	fn extractdata arg_node =
	(
		kexporter = XMLNodeExporter();
		if (arg_node != undefined)and(iskindof arg_node node) then
		(
			kexporter.extractdata arg_node;
			append array_nodeexporters kexporter;
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
	fn ext_selected_nodes arg_fileroute = 
	(
		for kexporter in array_nodeexporters do
		(
			local kelementnodefile = getselectfilename arg_fileroute kexporter.node_node.name kexporter.node_node.handle;
			kxml_element = omsxml_element();
			kxml_element.setvalue "ExportNode";
			kxml_element.setattribute "File" (filenameFromPath kelementnodefile);
			XML_Root.insertchild kxml_element;
			
			kexporter.exportdata kelementnodefile;
		)
	)
	,
	fn exportdata arg_fileroute = 
	(		
		if arg_fileroute != undefined then
		(
			
			XML_Root = OmsXML_Element();
			XML_Root.setvalue "Mass"
			XML_Root.setattribute "NodeCount" (array_nodeexporters.count);
			
			ext_selected_nodes arg_fileroute;
			
			local kXMLDoc = OmsXML_Document();
			kXMLDoc.SetTopElement XML_Root;
			kXMLDoc.SaveXML arg_fileroute;
		)
	)
)