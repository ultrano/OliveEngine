
rollout rollout_export_mesh "export_mesh"
	(
		button button_export "export" width:120
		progressbar pgbar_extstate ;
		
		on button_export pressed do
		(
			local kSelectedArray = selection as array;
			if kSelectedArray != undefined then
			(
				local kSelectOne = (kSelectedArray[1]);
				if kSelectOne != undefined then 
				(
					if canconvertto kSelectOne editable_mesh then
					(
						local kSelectMesh = kSelectOne.mesh;
						if (classof XMLMeshExporter) != UndefinedClass then
						(
							local kmeshdata = XMLMeshExporter();
							local kfilename = getsavefilename caption:"export" types:"XML(*.xml)|*.xml";
							if kfilename != undefined then
							(
								kmeshdata.extractmeshdata kSelectMesh pgbar_extstate;		
								
								kmeshdata.exportdata (kfilename);
							)
						)
					)
				)
			)
		)
	)