rollout rollout_export_node "export_node"
	(
		button button_export "export" width:120
		progressbar pgbar_extstate ;
		
		on button_export pressed do
		(
			local kSelectedArray = selection as array;
			local kSelectOne = kSelectedArray[1];
			if kSelectOne != undefined then 
			(
				if iskindof  kSelectOne node then
				(
					local kexporter = XMLNodeExporter();
					local kfilename = getsavefilename caption:"export" types:"XML(*.xml)|*.xml";
					if kfilename != undefined then
					(
						kexporter.extractdata kSelectOne pgbar_extstate;		
						
						kexporter.exportdata (kfilename);
					)
				)
			)
		)
	)