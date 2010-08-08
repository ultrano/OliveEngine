-- ÇÑ»ó¿î -- 
rollout rollout_export_select "export_node"
(
	button button_export "export" width:120
	progressbar pgbar_extstate ;
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
	)
	on button_export pressed do
	(
		local kSelectedArray = selection as array;
		local kfilename = getsavefilename caption:"export" types:"XML(*.xml)|*.xml";
		if kfilename != undefined then
		(
			kxml_export = OmsXML_Element();
			kxml_export.setvalue "SceneExport"
			
			kxml_export.insertchild (export_node_table kSelectedArray);
			kxml_export.insertchild (export_geom_table kSelectedArray);
			kxml_export.insertchild (export_camera_table kSelectedArray);
			
			---------------------------------------------------------------------------------------

			
			local kXMLDoc = OmsXML_Document();
			kXMLDoc.SetTopElement kxml_export;
			kXMLDoc.SaveXML kfilename;
			
		)
	)
)