
fn ovobject_property obj data_structure = 
(
	append data_structure obj.name;
	append data_structure "0:";
)

fn ovxobject_property obj data_structure = 
(
	local parent_handle = 0;
	
	if obj.parent != undefined then
		parent_handle = obj.parent.handle;
	
	append data_structure (parent_handle as string);
	
	local data = "";
	
	data = "";
	data = data as stringstream;
	format "%,%,%" obj.scale.x obj.scale.z obj.scale.y to: data;
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "%,%,%" obj.pos.x obj.pos.z obj.pos.y to: data;
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "%,%,%,%" obj.rotation.x obj.rotation.z obj.rotation.y -obj.rotation.w to: data;
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "0:" to: data;
	append data_structure (data);
	
	---------------------------------------------------------------
	---------------- inheritance property ----------------------------	
	ovobject_property obj data_structure;	
	---------------------------------------------------------------
	---------------------------------------------------------------
)

fn ovxnode_property obj data_structure =
(
	append data_structure ("0:");
	
	---------------------------------------------------------------
	---------------- inheritance property ----------------------------	
	ovxobject_property obj data_structure	
	---------------------------------------------------------------
	---------------------------------------------------------------
	
)

fn ovcamera_property obj data_structure =
(
	
	local data = "";
	
	data = "";
	data = data as stringstream;
	format "0" to: data; -- <m_spLookTarget />
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "0" to: data; -- <m_eCameraType />
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "%" (obj.fov*(pi/180.0)) to:data; -- <m_fFOV />
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "%" obj.nearclip to:data; -- <m_fNearClip />
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "%" obj.farclip to:data; -- <m_fFarClip />
	append data_structure (data);
	
	data = "";
	data = data as stringstream;
	format "1.0" to:data; -- <m_aspect />
	append data_structure (data);
		
	---------------------------------------------------------------
	---------------- inheritance property ----------------------------	
	ovxnode_property obj data_structure	
	---------------------------------------------------------------
	---------------------------------------------------------------
)
