
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
	fn extractdata arg_node =
	(
		ext_begin arg_node;
		
		ext_end();
	)
	,
	fn exportdata arg_fileroute = 
	(
		local kXMLDoc = OmsXML_Document();
		kXMLDoc.SetTopElement XML_Root;
		kXMLDoc.SaveXML arg_fileroute;
	)
	,
	fn ext_begin arg_node =
	(
		node_node = arg_node;
	)
	,
	fn ext_end = ()
	,
	fn ext_anim_pos = 
	(
		
	)
)