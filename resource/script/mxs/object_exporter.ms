
fn print_vec3 arg data_stream = 
(
	format "%,%,%\n" arg.x arg.y arg.z to: data_stream;
)
fn print_vec4 arg data_stream = 
(
	format "%,%,%,%\n" arg.x arg.y arg.z arg.w to: data_stream;
)

fn ovobject_property obj data_stream = 
(
	print (obj.name) to: data_stream;
	print ("0:") to: data_stream;
);

fn ovxobject_property obj data_stream = 
(
	local parent_handle = 0;
	if obj.parent != undefined then parent_handle = obj.parent.handle;
	print parent_handle to: data_stream
	
	print_vec3 obj.scale data_stream
	
	print_vec3 obj.pos data_stream
		
	print_vec4 obj.rotation data_stream

	print "0:" to: data_stream
	
	---------------------------------------------------------------
	---------------- inheritance property ----------------------------	
	ovobject_property obj data_stream;	
	---------------------------------------------------------------
	---------------------------------------------------------------
);

fn ovxnode_property obj data_stream =
(
	print "0:" to: data_stream
	
	---------------------------------------------------------------
	---------------- inheritance property ----------------------------	
	ovxobject_property obj data_stream	
	---------------------------------------------------------------
	---------------------------------------------------------------
	
);

fn ovcamera_property obj data_stream =
(
	print "0:" to: data_stream
	
	print "0:" to: data_stream
	
	print (obj.fov*(pi/180.0)) to: data_stream
	
	print obj.nearclip to: data_stream
	
	print obj.farclip to: data_stream
	
	print "1.0" to: data_stream

	---------------------------------------------------------------
	---------------- inheritance property ----------------------------	
	ovxnode_property obj data_stream	
	---------------------------------------------------------------
	---------------------------------------------------------------
);

fn test_export = 
(
	export_location = getsavefilename caption:"export" types:"mesh file version_0(*.msf0)|*.msf0";
	file_handle = createfile export_location;

	ovcamera_property cameras[1] file_handle;

	flush file_handle;
	close file_handle;
);
test_export();

