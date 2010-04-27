
fn ext_xml_point3 arg_value = 
(
	kxml_element = OmsXML_Element();
	kxml_element.SetValue "Point3";
	kxml_element.SetAttribute "x" arg_value[1];
	kxml_element.SetAttribute "y" arg_value[2];
	kxml_element.SetAttribute "z" arg_value[3];
	return kxml_element;
)
fn ext_xml_point2 arg_value = 
(
	kxml_element = OmsXML_Element();
	kxml_element.SetValue "Point2";
	kxml_element.SetAttribute "x" arg_value[1];
	kxml_element.SetAttribute "y" arg_value[2];
	return kxml_element;
)

fn ext_position arg_transform = 
(
	kxml_position = OmsXML_Element();
	kxml_position.SetValue "Position";
	kxml_position.SetAttribute "x" arg_transform.translationpart.x;
	kxml_position.SetAttribute "y" arg_transform.translationpart.y;
	kxml_position.SetAttribute "z" arg_transform.translationpart.z;

	return kxml_position;
)

fn ext_rotation arg_transform = 
(
	kxml_rotation = OmsXML_Element();
	kxml_rotation.SetValue "Rotation";
	kxml_rotation.SetAttribute "x" arg_transform.rotationpart.x;
	kxml_rotation.SetAttribute "y" arg_transform.rotationpart.y;
	kxml_rotation.SetAttribute "z" arg_transform.rotationpart.z;
	kxml_rotation.SetAttribute "w" arg_transform.rotationpart.w;

	return kxml_rotation;
)

fn ext_scale arg_transform = 
(
	kxml_scale = OmsXML_Element();
	kxml_scale.SetValue "Scale";
	kxml_scale.SetAttribute "x" arg_transform.scalepart.x;
	kxml_scale.SetAttribute "y" arg_transform.scalepart.y;
	kxml_scale.SetAttribute "z" arg_transform.scalepart.z;

	return kxml_scale;
)

fn ext_scale_rot arg_transform = 
(
	kxml_rotation_rot = OmsXML_Element();
	kxml_rotation_rot.SetValue "ScaleRotation";
	kxml_rotation_rot.SetAttribute "x" arg_transform.scalerotationpart.x;
	kxml_rotation_rot.SetAttribute "y" arg_transform.scalerotationpart.y;
	kxml_rotation_rot.SetAttribute "z" arg_transform.scalerotationpart.z;
	kxml_rotation_rot.SetAttribute "w" arg_transform.scalerotationpart.w;

	return kxml_rotation_rot;			
)
fn ext_transform arg_transform = 
(
	kxml_transform = OmsXML_Element();
	kxml_transform.SetValue "Transform";
	kxml_transform.insertchild (ext_position(arg_transform));		
	kxml_transform.insertchild (ext_rotation(arg_transform));    	
	kxml_transform.insertchild (ext_scale(arg_transform));      	
	kxml_transform.insertchild (ext_scale_rot(arg_transform));	
	return kxml_transform;
)
fn ext_offset_coord arg_stadard_trans arg_trans=
(
	local knodetrans 	= arg_stadard_trans;
	local kobjtrans 		= arg_trans;
	local kmeshtrans 	= kobjtrans * (inverse knodetrans);
	
	kxml_offset_coord = OmsXML_Element();
	kxml_offset_coord.SetValue "OffsetCoord";
	kxml_offset_coord.insertchild (ext_position(kmeshtrans));		
	kxml_offset_coord.insertchild (ext_rotation(kmeshtrans));    	
	kxml_offset_coord.insertchild (ext_scale(kmeshtrans));      	
	kxml_offset_coord.insertchild (ext_scale_rot(kmeshtrans));	
	return kxml_offset_coord;
)