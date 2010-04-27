macroScript PF_tools
	category:"PF_tracking_tools"
	toolTip:"파티클플로우트레킹툴"
(
	(
	rollout TR_PFT "::TR PF tracking tools::"

	(
	----------------------------- menu start ------------------------------------
		groupBox grp3 "GroupBox" pos:[7,28] width:199 height:62
		groupBox grp4 "GroupBox" pos:[7,94] width:199 height:126
		label lbl2 "Label" pos:[16,11] width:0 height:0
		label lbl3 "PF Tracking Tools 1.0" pos:[35,6] width:150 height:21
		button start "start" pos:[54,292] width:102 height:18 toolTip:""
		spinner id "Particle ID : " pos:[58,56] width:128 height:16 range:[0,1000,0] type:#integer scale:1
		spinner fs "Start Frame : " pos:[54,121] width:128 height:16 range:[0,1000,0] type:#integer scale:1
		spinner fe "End Frame : " pos:[58,152] width:124 height:16 range:[0,10000,0] type:#integer scale:1
		spinner skip "Skip Frame : " pos:[54,185] width:128 height:16 range:[0,100,0] type:#integer scale:1
		checkbox m_key "move setkey" pos:[52,241] width:102 height:18
		checkbox r_key "rotate setkey" pos:[52,260] width:102 height:18
		groupBox animation "tracking save" pos:[8,226] width:198 height:57
		groupBox ab "about" pos:[9,315] width:198 height:77
		label ab_lb "http://rhaon.co.kr http://yhucks.com  yhucks@naver.com" pos:[39,338] width:134 height:50
	----------------------------- menu end ------------------------------------
		on start pressed  do
		(
			if (classof $) != PF_Source do
			(
				messagebox "Please, select PF_Source object."
				return OK
			)
			PF_node_current = $
		
				PF_node_current.particleId = id.value
				b = pf_node_current.particlePosition
				point pos:b isSelected:on Box:on size:2 name:"traking_p"
		
				for i = fs.value to fe.value by skip.value do
				(
						sliderTime = i
		
						PF_node_current.particleId = id.value
		
						a = pf_node_current.particlePosition
		
						axis_x = pf_node_current.particleOrientation.x
		
						axis_y = pf_node_current.particleOrientation.y
		
						axis_z = pf_node_current.particleOrientation.z
		
						--print a
		
						--print axis_x
		
						--print axis_y
		
						--print axis_z
		
						axis_x = axis_x as float
		
						axis_y = axis_y as float
		
						axis_z = axis_z as float
						
						if m_key.checked then
						(
							set animate on
						)
						
						$traking_p.pos = a
						
						set animate off
						
						if r_key.checked then
						(
							set animate on
						)
						in coordsys local $traking_p.rotation.x_rotation = axis_x
		
						in coordsys local $traking_p.rotation.y_rotation = axis_y
		
						in coordsys local $traking_p.rotation.z_rotation = axis_z
						set animate off
				)
				$traking_p.name = ("traking_p" + "_0" + (id.value as string))
		
		)
	)
	)
	Createdialog TR_PFT 214 399 40 75
)
