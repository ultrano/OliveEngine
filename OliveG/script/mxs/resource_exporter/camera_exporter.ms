


fn camera_export file_location obj = 
(
	
	if iskindof obj camera then
	(
		local data_structure = #();
		
		ovcamera_property obj data_structure;
		
		
		local file_handle = createfile file_location;
		
		format "<ObjectTable>" to: file_handle;
		
		format "<Object type=\"OvCamera\" id=\"0\">" to: file_handle;
		
		for data in data_structure do
		(
			data = data as string;
			print data
			format "<prop>%</prop>" data to: file_handle;
		)
		
		format "</Object>" to: file_handle;
		
		format "</ObjectTable>" to: file_handle;
		
		
		flush file_handle;
		close file_handle;
	)
	
)
/*
<OvCamera>
		<m_spLookTarget />
		<m_eCameraType />
		<m_fFOV />
		<m_fNearClip />
		<m_fFarClip />
		<m_aspect />
		<m_clectrChildCollect />
		<m_pParent />
		<m_tfLocalTransform.Scale />
		<m_tfLocalTransform.Position />
		<m_tfLocalTransform.Quaternion />
		<m_extraComponents />
		<m_strObjectName />
		<m_extraPropertyTable />
</OvCamera>
*/


export_location = getsavefilename caption:"export" types:"camera export text version(*.xml)|*.xml";

camera_export export_location selection[1];