include "OliveMXS_Structure.ms"
include "OliveMXS_XML.ms"
include "OliveMXS_XMLNodeTraitExtractor.ms"
include "OliveMXS_XMLMeshExporter.ms"
include "OliveMXS_XMLNodeExporter.ms"
include "OliveMXS_XMLMassExporter.ms"
include "OliveMXS_MeshExportRollout.ms"
include "OliveMXS_NodeExportRollout.ms"
include "OliveMXS_SelectExportRollout.ms"

utility OliveUtility "OliveUtility_version_0_1"
(
	label label_infoto1 "<2009>에 제작."
	label label_infoto2 "한해의 마지막에"
	label label_infoto3 "뜻깊은 가르침을 얻으며,"
	--label label_infoto4 "감사합니다. KHK."
	label label_infoto5 "hahasasa@nate.com"	

	button dlg_ext_mesh "mesh export dialog";
	button dlg_ext_node "node export dialog";
	button dlg_ext_select "select export dialog";
	
	on dlg_ext_mesh pressed do
	(
		kExtMeshRollout = newRolloutFloater "Export Mesh" 300 120
		addRollout rollout_export_mesh kExtMeshRollout;
	)

	on dlg_ext_node pressed do
	(
		kExtNodeRollout = newRolloutFloater "Export Node" 300 120
		addRollout rollout_export_node kExtNodeRollout;
	)
	
	on dlg_ext_select pressed do
	(
		kExtSelectRollout = newRolloutFloater "Export Select" 300 120
		addRollout rollout_export_select kExtSelectRollout;
	)
	
);