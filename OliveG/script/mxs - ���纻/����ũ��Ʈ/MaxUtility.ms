include "OliveMXS_Structure.ms"
include "OliveMXS_XML.ms"
include "OliveMXS_XMLMeshData.ms"

utility OliveUtility "OliveUtility_version_0_1"
(


	label label_infoto1 "<2009>에 제작."
	label label_infoto2 "한해의 마지막에"
	label label_infoto3 "뜻깊은 가르침을 얻으며,"
	--label label_infoto4 "감사합니다. KHK."
	label label_infoto5 "hahasasa@nate.com"	
	
	group "common_base"
	(
		edittext base_folder "folder :"
	)
	fn getfolderfile arg_filename = 
	(
		return base_folder.text + arg_filename;
	)
	rollout rollout_export_mesh "export_mesh"
	(
		edittext filename "filename :"
		button button_export "export" width:120
		button button_close "close"
		on button_export pressed do
		(
			local kSelectedArray = selection as array;
			local kSelectOne = kSelectedArray[1];
			local kSelectMesh = kSelectOne.mesh;
			local kmeshdata = XMLMeshData();
			kmeshdata.extractmeshdata kSelectMesh;		
			kmeshdata.exportdata (getfolderfile filename.text);
		)
		on button_close pressed do
		(
			destroydialog rollout_export_mesh;
		)
	)
	button dlg_ext_mesh "mesh dialog";
	on dlg_ext_mesh pressed do
	(
		createdialog rollout_export_mesh;
	)
	
);