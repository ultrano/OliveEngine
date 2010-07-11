
fn gettangent normal pt1 pt2 pt3 u1 u2 u3= 
(
	local tempaxis = -(u3 - u1)*(pt2 - pt1) + (u2 - u1)*(pt3 - pt1);
	tempaxis = normalize( tempaxis );
	local tangent = cross normal tempaxis;
	return tangent;
)
struct mesh_exporter
(
	fn export resource file_location = 
	(
		local file_handle = createfile file_location;
		if resource != undefined and canconvertto resource editable_mesh then
		(
			progressstart "mesh exporting"
			
			progressupdate 0
			
			local mesh_data = resource.mesh;
			
			local face_count = getnumfaces mesh_data;
			local vertex_count = face_count * 3;
			
			-- descript vertex count
			format "%\n" vertex_count to: file_handle;
			
			-- descript face count
			format "%\n" face_count to: file_handle;			
			
			-- descript vertex count
			format "%\n" vertex_count to: file_handle;
			for i=1 to face_count do
			(
				local face = getface mesh_data i;
				-- descript position
				local position;
				position = getvert mesh_data face[1];
				format "%,%,%\n" position.x position.z position.y to: file_handle;
				position = getvert mesh_data face[2];
				format "%,%,%\n" position.x position.z position.y to: file_handle;
				position = getvert mesh_data face[3];
				format "%,%,%\n" position.x position.z position.y to: file_handle;
			)
			
			progressupdate 20
			
			for i=1 to face_count do
			(
				local face = getface mesh_data i;
				-- descript normal
				local normal;
				normal = getnormal mesh_data face[1];
				format "%,%,%\n" normal.x normal.z normal.y to: file_handle;
				normal = getnormal mesh_data face[2];
				format "%,%,%\n" normal.x normal.z normal.y to: file_handle;
				normal = getnormal mesh_data face[3];
				format "%,%,%\n" normal.x normal.z normal.y to: file_handle;
			)
			
			progressupdate 40
			
			for i=1 to face_count do
			(
				local face = getface mesh_data i;
				local tface = gettvface mesh_data i;
				
				-- descript tangent
				local pt1 = getvert mesh_data face[1];
				local pt2 = getvert mesh_data face[2];
				local pt3 = getvert mesh_data face[3];
				
				local uv1 = gettvert mesh_data tface[1];
				local uv2 = gettvert mesh_data tface[2];
				local uv3 = gettvert mesh_data tface[3];
				
				local norm1 = getnormal mesh_data face[1];
				local norm2 = getnormal mesh_data face[2];
				local norm3 = getnormal mesh_data face[3];
				
				local tangent;
				tangent = gettangent norm1 pt1 pt2 pt3 uv1.x uv2.x uv3.x;
				format "%,%,%\n" tangent.x tangent.z tangent.y to: file_handle;
				tangent = gettangent norm2 pt1 pt2 pt3 uv1.x uv2.x uv3.x;
				format "%,%,%\n" tangent.x tangent.z tangent.y to: file_handle;
				tangent = gettangent norm3 pt1 pt2 pt3 uv1.x uv2.x uv3.x;
				format "%,%,%\n" tangent.x tangent.z tangent.y to: file_handle;
			)
			
			progressupdate 60
			
			-- descript texcoord0 count
			format "%\n" vertex_count to: file_handle;
			for i=1 to face_count do
			(
				-- descript texcoord0
				local tface = gettvface mesh_data i;
				local texcoord;
				texcoord = gettvert mesh_data tface[1];
				format "%,%\n" texcoord.x (1.0 - texcoord.y) to: file_handle;
				texcoord = gettvert mesh_data tface[2];
				format "%,%\n" texcoord.x (1.0 - texcoord.y) to: file_handle;
				texcoord = gettvert mesh_data tface[3];
				format "%,%\n" texcoord.x (1.0 - texcoord.y) to: file_handle;
			)
			
			progressupdate 90
			
			-- descript face count
			format "%\n" face_count to: file_handle;
			for i=1 to face_count do
			(
				local offsetIndex = ((i-1) * 3);
				local index1 = offsetIndex + 0;
				local index2 = offsetIndex + 2;
				local index3 = offsetIndex + 1;
				format "%,%,%\n" index1 index2 index3 to: file_handle;
			)
			progressupdate 100
			progressend();
		)
		flush file_handle;
		close file_handle;
	)
)

resource_exporter = mesh_exporter;

export_location = getsavefilename caption:"export" types:"mesh file version_0(*.msf0)|*.msf0";

resource_exporter.export selection[1] export_location;

