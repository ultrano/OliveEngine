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
			local kprogressing = 0
			local kexporter = XMLMassExporter();
			for kSelectOne in kSelectedArray do
			(
				if (kSelectOne != undefined) and (iskindof  kSelectOne node) then 
				(
					kexporter.extractdata kSelectOne;		
				)
				kprogressing += 1;
				pgbar_extstate.value = kprogressing*100/kSelectedArray.count
			)
			kexporter.exportdata kfilename;
		)
	)
)