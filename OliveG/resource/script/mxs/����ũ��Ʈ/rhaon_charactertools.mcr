--Character Tools v1.3
--2007.12.27 addon
--hide bone and biped layer
--nic_name rename addon
--2007.12.22 edit
--rurf skin addon
--script rename is ch_tools
--2007.06.19 edit
--maki skin addon
--biped Figuremode addon and maki ghost skinpos rotate auto setting

macroScript CH_tools
	category:"RhaonScript"
	toolTip:"TR Character Tools v1.3 20071227"
(
(
rollout chr_tools "TR CHR tools"
(
	struct ExporterBoneInfo
	(
		m_name,
		m_bone,
		m_node,
		m_index
	)
	
	----------------------------------
	
	struct ExportPhysiqueInfo
	(
		m_node,
		
		fn init =
		(
			--subObjectLevel = 0
		),
		
		fn getBones =
		(
			return physiqueops.getBones m_node
		),
		
		fn getVertexBones vertIndex =
		(
			return physiqueops.getVertexBones m_node vertIndex
		),
		
		fn getVertexWeight vertIndex subBoneIndex =
		(
			return physiqueops.getVertexWeight m_node vertIndex subBoneIndex
		)
	)
	
	struct ExportSkinInfo
	(
		m_node,
		m_skin = undefined,
		m_bones = undefined,
		
		fn init =
		(
			print m_node
			m_skin = m_node.modifiers[#skin]
			max modify mode
			modpanel.setCurrentObject m_skin
			m_bones = for i = 1 to (skinops.getNumberBones m_skin) collect (getNodeByName (skinops.getBoneName m_skin i 0))
		),

		fn getBones =
		(
			return m_bones
		),

		fn getVertexBones vertIndex =
		(
			return for i = 1 to (skinops.getVertexWeightCount m_skin vertIndex) collect
				m_bones[skinops.getVertexWeightBoneID m_skin vertIndex i]
		),
		
		fn getVertexWeight vertIndex subBoneIndex =
		(
			return skinops.getVertexWeight m_skin vertIndex subBoneIndex
		)
	)

	----------------------------------
	
	struct ExportMesh
	(	
		fout, -- file output stream
		bIncludeBones = false,
		m_exportedBones = #(),
		m_bonesInfos = #(),  -- array of ExporterBoneInfo
		
		m_numFrames = (animationrange.end - animationrange.start) as float / 1f as float,
		
		-- progress info
		m_progressCurrent = 0.0,
		m_progressEnd = 100.0,
		m_progressEndCheckObjs = #(),
		m_isCanceled = false,


		fn isExportable obj =
		(
			if not (isKindOf obj node) or not (canConvertTo obj Editable_Mesh) do
			(
				return false
			)
			
			if not bIncludeBones do
			(
				if (isKindOf obj Biped_Object) do
				(
					return false
				)
				
				if (isKindOf obj Bone) or (isKindOf obj BoneGeometry) do
				(
					return false
				)
			)
			
			return true
		),
		
		fn getSkinExporter obj =
		(
			local exporter = undefined
		
			try
			(
				local v = physiqueops.getAPIVersion obj
				exporter = ExportPhysiqueInfo m_node:obj
			)
			catch
			(
			)
			
			if exporter == undefined do
			(
				local m = obj.modifiers[1]
				if m != undefined and (classof m) == skin do
				(
					exporter = ExportSkinInfo m_node:obj
				)
			)

			if exporter != undefined do
			(
				exporter.init()
			)
			
			return exporter
		),

		fn isAnimatedController ctrllr =
		(
			local ctrlcls = classof ctrllr
			
			if ctrlcls == Vertical_Horizontal_Turn or ctrlcls == IKControl or \
				ctrllr.isAnimated or ctrllr.keys.count > 0
				do
			(
				return true
			)
		),
		
		fn isAnimated obj =
		(
			if obj.isAnimated do return true

			if classof obj.controller != Position_Rotation_Scale or obj.controller.keys.count > 0
				do return true

			if classof obj.pos.controller != Position_XYZ or obj.pos.controller.keys.count > 0
				do return true
			
			if classof obj.rotation.controller != Euler_XYZ or obj.rotation.controller.keys.count > 0
				do return true

			if classof obj.scale.controller != Bezier_Scale or obj.scale.controller.keys.count > 0
				do return true

			return false
		),
		
		-----------------------------------------------------------------
		
		fn beginExport =
		(
			--progressStart "Export scene objects..."
		),
		
		fn endExport =
		(
			writeLong fout 0
			
			--progressUpdate 100.0
			--progressEnd()
			FClose fout
		),
		
		fn progress val =
		(
			m_progressCurrent += val
			--local bRet = progressUpdate (m_progressCurrent/m_progressEnd * 100)
			--if not bRet do
			--(
			--	m_isCanceled = true
			--	FClose fout
			--	throw "Canceled."
			--)
		),
		

		------------------------------------------------------------------
		
		fn addProgressEndBone bn =
		(
			if bn == undefined then
			(
				return OK
			)
		
			if 0 != findItem m_progressEndCheckObjs bn then
			(
				-- checked bone
				return OK
			)
			
			append m_progressEndCheckObjs bn
			
			addProgressEndBone bn.parent
		
			if isAnimated bn then
			(
				m_progressEnd += m_numFrames * 4.0
			)
			
			if isKindOf bn Biped_Object do
			(
				for i in bn.children do
				(
					addProgressEndBone i
				)
			)
		),

		
		fn addProgressEndSkinnedMeshBones exporter =
		(
			local bones = exporter.getBones()
			
			for bn in bones do
			(
				addProgressEndBone bn
			)
		),
		
		fn addProgressEndMaterial m =
		(
			local cls = classof m
			
			if (cls == StandardMaterial) then
			(
				m_progressEnd += 4.0
			)
			else if (cls == MultiMaterial) then
			(
				for subm in m.materiallist do
				(
					addProgressEndMaterial subm
				)
			)
			else
			(
				m_progressEnd += 1.0
			)
		),
		
		fn addProgressEndObj obj =
		(
			if not isExportable obj do
			(
				return OK
			)

			local obj_mesh = undefined
			
			if isKindOf obj Editable_Mesh then
			(
				obj_mesh = obj
			)
			else
			(
				try
				(
					obj_mesh = obj.mesh
				)
				catch
				(
					return OK
				)
			)
			
			local exporter = getSkinExporter obj
			
			-- bones --------------------

			addProgressEndBone obj

			if exporter != undefined do
			(
				addProgressEndSkinnedMeshBones exporter
			)
			
			
			-- material -----------------
			
			addProgressEndMaterial obj.material
			
			-- vertices -----------------
			
			m_progressEnd += obj_mesh.numVerts
			
			-- texture vertices ---------
			
			local hasMaps = numMapsUsed obj > 0
			
			if hasMaps do
			(
				m_progressEnd += obj_mesh.numTVerts
			)
			
			-- faces --------------------
			
			local numFaces = obj_mesh.numFaces
			
			m_progressEnd += numFaces
		),

		------------------------------------------------------------------
		
		fn outputTime t =
		(
			writeFloat fout ((t as float) / (1s as float))
		),
	
		fn outputColor c =
		(
			writeFloat fout (c.r/255)
			writeFloat fout (c.g/255)
			writeFloat fout (c.b/255)
			writeFloat fout (c.a/255)
		),
		
		fn outputString s =
		(
			writeShort fout s.count
			writeString fout s
		),
		
		fn outputPoint3 p =
		(
			writeFloat fout p[1]
			writeFloat fout p[2]
			writeFloat fout p[3]
		),
	
		fn outputMatrix m =
		(
			outputPoint3 m[1]
			outputPoint3 m[2]
			outputPoint3 m[3]
			outputPoint3 m[4]
		),
		
		fn outputMaterial m =
		(
			local cls = classof m

			if (cls == UndefinedClass) then
			(
			)
			else
			(
				writeLong fout 99
				outputString m.name
			)
			
			if (cls == StandardMaterial) then
			(
				writeLong fout 0
				
				if m.diffuseMapEnable then
				(
					outputColor (color 255 255 255 255)
				)
				else
				(
					outputColor m.diffuse
				)
				
				outputColor (color 255 255 255 255)
				outputColor (color 255 255 255 255)
				
				if (m.diffusemap != undefined and m.diffusemap.filename != undefined) then
				(
					outputString m.diffusemap.filename
				)
				else
				(
					outputString ""
				)
				
				progress 4.0
			)
			else if (cls == MultiMaterial) then
			(
				local matlist = m.materiallist
		
				writeLong fout 1

				writeLong fout m.materialIDList.count

				for matID in m.materialIDList do
				(
					writeLong fout matID
				)

				writeLong fout matlist.count
				
				for subm in matlist do
				(
					outputMaterial subm
				)
			)
			else
			(
				writeLong fout 0
				outputColor (color 255 255 255 255)
				outputColor (color 255 255 255 255)
				outputColor (color 255 255 255 255)
				outputString ""
				
				progress 1.0
			)
		),
		

		fn outputHeader =
		(
			writeString fout "<RhaonCharacterExporter002>"
			
			local maxVer = maxVersion()
			
			for i = 1 to 3 do
			(
				if maxVer[i] != undefined then
				(
					writeLong fout maxVer[i]
				)
				else
				(
					writeLong fout 0
				)
			)
			
			outputTime animationrange.start
			outputTime animationrange.end
			
			progress 1.0
		),
	
		-------------------------------------------------------------
		
		fn getBoneInfo bn =
		(
			for en in m_bonesInfos do
			(
				if (en.m_bone == bn) do
				(
					return en
				)
			)
			return undefined
		),

		fn getBoneInfoByName name =
		(
			for en in m_bonesInfos do
			(
				if (en.m_name == name) do
				(
					return en
				)
			)
			return undefined
		),
	
		fn addBoneInfo bn node index =
		(
			local bninfo = getBoneInfo bn
			
			if bninfo != undefined do
			(
				-- already exported.
				if node != undefined do
				(
					bninfo.m_node = node
					bninfo.m_index = index
				)
				
				return bninfo
			)
		
			local name = bn.name
			
			if name == "" do
			(
				name = "noname"
			)
			
			-- 이름이 충돌하는지 채크한다.
			
			if (getBoneInfoByName name) != undefined do
			(
				local newname
				local count = 0
				
				while true do
				(
					count += 1
					newname = name + "_" + (count as string)
					
					local bn2 = getBoneInfoByName newname
					
					if bn2 == undefined do
					(
						exit
					)
				)
				
				name = newname
			)
			
			local boneinfo = (ExporterBoneInfo name bn node index)
			append m_bonesInfos boneinfo
			return boneinfo
		),
	
	
		fn outputBoneTM bn t =
		(
			if bn != undefined do
			(
				if bn.parent != undefined then
				(
					local parenttransform = (at time t bn.parent.transform)
					local thistransform = (at time t bn.transform)
					(outputMatrix (thistransform * (inverse parenttransform)))
				)
				else
				(
					outputMatrix (at time t bn.transform)
				)
			)
		),
		
		fn outputBone bn =
		(
			if bn == undefined then
			(
				return OK
			)
		
			if 0 != findItem m_exportedBones bn then
			(
				-- written bone
				return OK
			)
			
			append m_exportedBones bn
			
			outputBone bn.parent
		
			local boneinfo = getBoneInfo bn
			
			if boneinfo == undefined do
			(
				boneinfo = addBoneInfo bn undefined 0
			)
		
			writeLong fout 1
			outputString boneinfo.m_name
			
			if bn.parent != undefined then
			(
				local parentBoneinfo = getBoneInfo bn.parent
				outputString parentBoneinfo.m_name
			)
			else
			(
				outputString ""
			)
			
			outputBoneTM bn animationrange.start
	
			
			if isAnimated bn then
			(
				local count = (((animationrange.end - animationrange.start) as float) / (1.f as float)) as integer
				
				writeLong fout (count + 1)
				
				local t = animationrange.start
				for i = 1 to count do
				(
					outputTime t
					outputBoneTM bn t
					t += 1f
					progress 4.0
				)
				
				outputTime animationrange.end
				outputBoneTM bn animationrange.end
			)
			else
			(
				writeLong fout 0
			)
			
			if isKindOf bn Biped_Object do
			(
				for i in bn.children do
				(
					outputBone i
				)
			)
		),
		
		fn outputSkinnedMeshBones exporter =
		(
			local obj = exporter.m_node
			local bones = exporter.getBones()
			
			for i = 1 to bones.count do
			(
				addBoneInfo bones[i] obj i
			)
			
			for bn in bones do
			(
				outputBone bn
			)
			
			outputBone obj
			
			--end of bones
			writeLong fout 0
			outputString (getBoneInfo obj).m_name
			
			-- num mesh bones
			writeLong fout bones.count
			
			for i = 1 to bones.count do
			(
				outputString (getBoneInfo bones[i]).m_name
			)
		),
		
		
		fn outputNormalMeshBones obj =
		(
			outputBone obj
	
			--end of bones
			writeLong fout 0
			outputString (getBoneInfo obj).m_name
			
			-- num mesh bones = 0
			writeLong fout 0
		),
	
		-------------------------------------------------------------
	
	
		fn outputExportMesh obj =
		(
			if not isExportable obj do
			(
				return OK
			)

			local obj_mesh = undefined
			
			try
			(
				obj_mesh = at time animationrange.start obj.mesh
				obj_mesh = copy obj_mesh
			)
			catch
			(
				return OK
			)
						
			local exporter = getSkinExporter obj

			if exporter != undefined then
			(
				transform obj_mesh (at time animationrange.start obj.objecttransform)
			)
			else
			(
				local objtrans = (at time animationrange.start obj.objecttransform)
				local trans = (at time animationrange.start obj.transform)
				local localtrans = objtrans * (inverse trans)
				transform obj_mesh localtrans
			)
		
			(
				writeLong fout 1
				outputString obj.name
				
				-- bones --------------------
	
				if exporter != undefined then
				(
					writeLong fout 1
					outputSkinnedMeshBones exporter
				)
				else
				(
					writeLong fout 0
					outputNormalMeshBones obj
				)
				-- material -----------------
				
				local material = obj.material
		
				outputMaterial material
				
				-- vertices -----------------
				
				local numVerts = obj_mesh.numVerts
		
				writeLong fout numVerts
				
				if exporter != undefined then
				(
					for vertIndex = 1 to numVerts do
					(
						local v = (meshOp.getVert obj_mesh vertIndex)
						
						outputPoint3 v
			
						local vbn = exporter.getVertexBones vertIndex
		
						if vbn.count > 4 do
						(
							print "Number of vertex bones > 4 !!!"
						)
						
						writeLong fout vbn.count
	
						for i = 1 to vbn.count do
						(
							local bn = vbn[i]
							local boneinfo = getBoneInfo bn
							writeLong fout boneinfo.m_index
							writeFloat fout (exporter.getVertexWeight vertIndex i)
						)
						
						progress 1.0
					)
				)
				else
				(
					for vertIndex = 1 to numVerts do
					(
						local v = (meshOp.getVert obj_mesh vertIndex)
						
						outputPoint3 v
						writeLong fout 0
					)
					
					progress numVerts
				)
				
				-- texture vertices ---------

				local numTVerts = obj_mesh.numTVerts
				local hasMaps = numMapsUsed obj > 0 and numTVerts > 0

				if hasMaps then
				(
					writeLong fout numTVerts
					
					for tvertIndex = 1 to numTVerts do
					(
						outputPoint3 (getTVert obj_mesh tvertIndex)
					)
					
					progress numTVerts
				)
				else
				(
					writeLong fout 1
					outputPoint3 [0,0,0]
				)
				
				-- faces --------------------
				
				local numFaces = obj_mesh.numFaces
				
				writeLong fout numFaces
				
				for faceIndex = 1 to numFaces do
				(
					local faceVerts = (getFace obj_mesh faceIndex)
					local faceTVerts = if hasMaps then (getTVFace obj_mesh faceIndex) else [1,1,1]
					local n = (meshop.getFaceRNormals obj_mesh faceIndex)

					for j = 1 to 3 do
					(
						writeLong fout (faceVerts[j] as integer)
						writeLong fout (faceTVerts[j] as integer)
					
						if n[j] == undefined do
						(
							n[j] =  (getFaceNormal obj_mesh faceIndex)
						)
						
						outputPoint3 n[j]
					)
					
					writeLong fout (getFaceSmoothGroup obj_mesh faceIndex)
					writeLong fout (getFaceMatID obj_mesh faceIndex)
					progress 1.0
				)
			)
			
			delete obj_mesh
			obj_mesh = undefined
		) -- fn outputExportMesh
	)
	
	-------------------------------------------------------------
	
	local lastExportedFileName = undefined
	
	
	fn fileOutSelected fname bIncludeBones:false =
	(
		local fout = fopen fname "wbS"
		
		if fout == undefined do
		(
			messageBox "Cannot open file for writting." title:"Export Error" beep:false
			return OK
		)

		local exp = ExportMesh fout:fout bIncludeBones:bIncludeBones
		local old_selection = selection as array
		local old_curObj = modpanel.getCurrentObject()
		
		--try
		(
			local startTime = timeStamp()
		
			exp.beginExport()
	
			exp.outputHeader()
			
			for obj in old_selection do
			(
				exp.addProgressEndObj obj
			)
			
			exp.progress 5.0
			
			for obj in old_selection do
			(
				exp.outputExportMesh obj
			)
			
			exp.endExport()
			
			format "% secs.\n" ((timeStamp() - startTime) / 1000.0)
			
			lastExportedFileName = fname
		)
		--catch
		(
			--if not exp.m_isCanceled do
			(
				--throw()
			)
		)
		
		select old_selection
		if old_curObj != undefined do
		(
			modpanel.setCurrentObject old_curObj
		)
		--max utility mode
	)

	

------------------------------------menu---------------------------------------------
	groupBox index "infomation" pos:[7,7] width:147 height:48
	label lbl4 "Rhaon Character tools v1.3" pos:[13,22] width:130 height:31
	groupBox view_tools "tools" pos:[7,64] width:147 height:265
	button autoskin "Auto Skin" pos:[62,96] width:80 height:18 toolTip:"TalesRunner Character Auto Skining"
	label lbl5 "character skin" pos:[15,78] width:99 height:19
	label lbl6 "2004-2007 Rhaon Ent." pos:[11,422] width:137 height:14
	label lbl9 "Viewport" pos:[16,160] width:100 height:15
	button viewR "Right" pos:[17,179] width:50 height:18
	button view_b "back" pos:[88,179] width:50 height:18
	button view_f "Front" pos:[17,199] width:50 height:18
	button view_p "perspec" pos:[88,199] width:50 height:18
	button btn_exportSelected "Export Selected" pos:[25,356] width:100 height:18
	checkbox chk_includeBones "Include bones" pos:[32,376] width:87 height:14
	button btn_openLast "Open Last Exported" pos:[25,395] width:100 height:18
	checkButton ch_figurebtn "Figuremode" pos:[65,138] width:75 height:19 toolTip:"바이패드 피규어모드" checked:false
	label biptitle "Biped FigureMode" pos:[16,118] width:127 height:15
	label bip_ly "Biped_layer:" pos:[11,238] width:83 height:14
	label bon_ly "Bone_layer:" pos:[11,259] width:84 height:16
	checkButton bip_ck "hidden" pos:[103,236] width:42 height:18 enabled:true
	checkButton bon_ck "hidden" pos:[103,258] width:42 height:18
	groupBox exp_title "Export v0.4.1" pos:[8,333] width:146 height:86
	editText base_name "" pos:[16,303] width:75 height:17
	button rename_them "RENAME" pos:[98,302] width:52 height:20
	label nictitle "CH_NIC name edit" pos:[16,282] width:127 height:16
-----------------------------------------------------------------------------------------
	on ch_figurebtn changed state do
	(
		if $bip01 == undefined
			then
			(
			messageBox "NO biped"
			ch_figurebtn.state = off
			ok
			)
			else
			(
			biped_ctrl=$bip01.controller
			fig_mod = biped_ctrl.figuremode
			if state == on
				then
					(
					biped_ctrl.figuremode = true
					(
						if classof $ghost_top == dummy then 
						(
							messagebox "maki ghost skinpose set"
							rotate $main_top (angleaxis -90 [0,0,1])
						)
						else ok
					)			
					)
				else
					(
					biped_ctrl.figuremode = false
					(
						if classof $ghost_top == dummy then 
						(
							messagebox "maki ghost anipose set"
							rotate $main_top (angleaxis 90 [0,0,1])
						)
						else ok
					)	
					)
			)
	)


	on btn_exportSelected pressed do
	(
		local fname = lastExportedFileName
		
		if fname != undefined then
		(
			fname = GetSaveFileName filename:fname types:"Rhaon Export Files (*.rm2)|*.rm2|"
		)
		else
		(
			fname = GetSaveFileName types:"Rhaon Export Files (*.rm2)|*.rm2|"
		)
		
		if fname == undefined do
		(
			return OK
		)
	
		fileOutSelected fname bIncludeBones:chk_includeBones.checked
		messagebox "export END."
	)
	
	
	on btn_openLast pressed do
	(
		if lastExportedFileName == undefined do
		(
			messageBox "No exported files." title:"Export Error" beep:false
			return OK
		)
		
		ShellLaunch lastExportedFileName ""
	)

	on autoskin pressed  do
--autoskin
(
if ($ != undefined) then
(
	case of
	(
	((findstring $.name "rf") == 1):
--rurf skin start
	(
	modPanel.addModToSelection (Skin ()) ui:on
	skinOps.addBone $.modifiers[#Skin] $Bip01 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger31' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger41' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 LUpArmTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 LUpArmTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger31' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger41' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 RUpArmTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 RUpArmTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine2' 1
	skinOps.addBone $.modifiers[#Skin] $Bone01 1
	skinOps.addBone $.modifiers[#Skin] $Bone02 1
	skinOps.addBone $.modifiers[#Skin] $Bone03 1
	skinOps.addBone $.modifiers[#Skin] $Bone04 1
	skinOps.addBone $.modifiers[#Skin] $Bone05 1
	skinOps.addBone $.modifiers[#Skin] $Bone06 1
	skinOps.addBone $.modifiers[#Skin] $Bone07 1
	skinOps.addBone $.modifiers[#Skin] $Bone08 1
	skinOps.addBone $.modifiers[#Skin] $Bone09 1
	skinOps.addBone $.modifiers[#Skin] $Bone10 1
	skinOps.addBone $.modifiers[#Skin] $Bone11 1
	skinOps.addBone $.modifiers[#Skin] $Bone12 1
	skinOps.addBone $.modifiers[#Skin] $hair_root 1
	skinOps.addBone $.modifiers[#Skin] $Point01 1
	skinOps.addBone $.modifiers[#Skin] $Point02 1
	skinOps.addBone $.modifiers[#Skin] $Point03 1
	skinOps.addBone $.modifiers[#Skin] $Point04 1
	$.modifiers[#Skin].cross_radius = 13.6399
	subobjectLevel = 1
	toolMode.coordsys #view
	$.modifiers[#Skin].filter_vertices = on
	skinOps.weightTool $.modifiers[#Skin]
	messagebox "Rurf 스킨완료"
	)
--Rurf skin end
((findstring $.name "mk") == 1):
--maki skin start
	(
	modPanel.addModToSelection (Skin ()) ui:on
	skinOps.addBone $.modifiers[#Skin] $Bip01 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine2' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger31' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger41' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 LUpArmTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 LUpArmTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 HeadNub' 1
	skinOps.addBone $.modifiers[#Skin] $Bone65 1
	skinOps.addBone $.modifiers[#Skin] $Bone66 1
	skinOps.addBone $.modifiers[#Skin] $Bone67 1
	skinOps.addBone $.modifiers[#Skin] $Bone68 1
	skinOps.addBone $.modifiers[#Skin] $Bone69 1
	skinOps.addBone $.modifiers[#Skin] $Bone70 1
	skinOps.addBone $.modifiers[#Skin] $Dummy_hair 1
	skinOps.addBone $.modifiers[#Skin] $Bone13 1
	skinOps.addBone $.modifiers[#Skin] $Bone14 1
	skinOps.addBone $.modifiers[#Skin] $Bone15 1
	skinOps.addBone $.modifiers[#Skin] $Bone16 1
	skinOps.addBone $.modifiers[#Skin] $Bone17 1
	skinOps.addBone $.modifiers[#Skin] $Bone18 1
	skinOps.addBone $.modifiers[#Skin] $Bone19 1
	skinOps.addBone $.modifiers[#Skin] $Bone20 1
	skinOps.addBone $.modifiers[#Skin] $Bone21 1
	skinOps.addBone $.modifiers[#Skin] $Bone22 1
	skinOps.addBone $.modifiers[#Skin] $Bone23 1
	skinOps.addBone $.modifiers[#Skin] $Bone24 1
	skinOps.addBone $.modifiers[#Skin] $hand_p_L 1
	skinOps.addBone $.modifiers[#Skin] $hand_p_R 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger31' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger41' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4Nub' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 RUpArmTwist' 1
	skinOps.addBone $.modifiers[#Skin] $'Bip01 RUpArmTwist1' 1
	skinOps.addBone $.modifiers[#Skin] $Dummy_skirt 1
	skinOps.addBone $.modifiers[#Skin] $Bone01 1
	skinOps.addBone $.modifiers[#Skin] $Bone02 1
	skinOps.addBone $.modifiers[#Skin] $Bone03 1
	skinOps.addBone $.modifiers[#Skin] $Bone04 1
	skinOps.addBone $.modifiers[#Skin] $Bone05 1
	skinOps.addBone $.modifiers[#Skin] $Bone06 1
	skinOps.addBone $.modifiers[#Skin] $Bone83 1
	skinOps.addBone $.modifiers[#Skin] $Bone84 1
	skinOps.addBone $.modifiers[#Skin] $Bone85 1
	skinOps.addBone $.modifiers[#Skin] $Bone86 1
	skinOps.addBone $.modifiers[#Skin] $Bone87 1
	skinOps.addBone $.modifiers[#Skin] $Bone88 1
	skinOps.addBone $.modifiers[#Skin] $Bone89 1
	skinOps.addBone $.modifiers[#Skin] $Bone90 1
	skinOps.addBone $.modifiers[#Skin] $Bone91 1
	skinOps.addBone $.modifiers[#Skin] $Bone92 1
	skinOps.addBone $.modifiers[#Skin] $Bone93 1
	skinOps.addBone $.modifiers[#Skin] $Bone94 1
	skinOps.addBone $.modifiers[#Skin] $main_top 1
	skinOps.addBone $.modifiers[#Skin] $Character01 1
	skinOps.addBone $.modifiers[#Skin] $ghost_top 1
	skinOps.addBone $.modifiers[#Skin] $ghost_bodytop 1
	skinOps.addBone $.modifiers[#Skin] $Bone46 1
	skinOps.addBone $.modifiers[#Skin] $Bone47 1
	skinOps.addBone $.modifiers[#Skin] $Bone48 1
	skinOps.addBone $.modifiers[#Skin] $Dummy01 1
	skinOps.addBone $.modifiers[#Skin] $Bone49 1
	skinOps.addBone $.modifiers[#Skin] $Bone50 1
	skinOps.addBone $.modifiers[#Skin] $Bone51 1
	skinOps.addBone $.modifiers[#Skin] $Bone52 1
	skinOps.addBone $.modifiers[#Skin] $Bone53 1
	skinOps.addBone $.modifiers[#Skin] $Bone54 1
	skinOps.addBone $.modifiers[#Skin] $Bone55 1
	skinOps.addBone $.modifiers[#Skin] $Dummy02 1
	skinOps.addBone $.modifiers[#Skin] $Bone37 1
	skinOps.addBone $.modifiers[#Skin] $Bone38 1
	skinOps.addBone $.modifiers[#Skin] $BoneLH_roco 1
	skinOps.addBone $.modifiers[#Skin] $Bone40 1
	skinOps.addBone $.modifiers[#Skin] $Bone41 1
	skinOps.addBone $.modifiers[#Skin] $Bone71 1
	skinOps.addBone $.modifiers[#Skin] $Bone72 1
	skinOps.addBone $.modifiers[#Skin] $Bone43 1
	skinOps.addBone $.modifiers[#Skin] $Bone44 1
	skinOps.addBone $.modifiers[#Skin] $Bone45 1
	skinOps.addBone $.modifiers[#Skin] $Bone73 1
	skinOps.addBone $.modifiers[#Skin] $Bone74 1
	skinOps.addBone $.modifiers[#Skin] $BoneRH_roco 1
	skinOps.addBone $.modifiers[#Skin] $Bone76 1
	skinOps.addBone $.modifiers[#Skin] $Bone77 1
	skinOps.addBone $.modifiers[#Skin] $Bone78 1
	skinOps.addBone $.modifiers[#Skin] $Bone79 1
	skinOps.addBone $.modifiers[#Skin] $Bone80 1
	skinOps.addBone $.modifiers[#Skin] $Bone81 1
	skinOps.addBone $.modifiers[#Skin] $Bone82 1
	$.modifiers[#Skin].cross_radius = 4.9875
	subobjectLevel = 1
	toolMode.coordsys #view
	$.modifiers[#Skin].filter_vertices = on
	skinOps.weightTool $.modifiers[#Skin]
	messagebox "Maki 스킨완료"
	)
--maki skin end

	((findstring $.name "ns") == 1):
--narsis skin start
(
		modPanel.addModToSelection (Skin ()) ui:on

		skinOps.addBone $.modifiers[#Skin] $Bip01 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 LUpArmTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 RUpArmTwist' 1

		$.modifiers[#Skin].cross_radius = 5.3128

		subobjectLevel = 1

		$.modifiers[#Skin].filter_vertices = on
		skinOps.weightTool $.modifiers[#Skin]
			messagebox "narsis 스킨완료"
	)

--narsis skin end
	((findstring $.name "dn") == 1):
--dnd skin start
(
		modPanel.addModToSelection (Skin ()) ui:on

		skinOps.addBone $.modifiers[#Skin] $Bip01 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 HeadNub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L ForeTwist2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 LThighTwist2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R ForeTwist2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0Nub' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 RThighTwist2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine2' 1

		skinOps.addBone $.modifiers[#Skin] $Bone01 1

		skinOps.addBone $.modifiers[#Skin] $Bone02 1

		skinOps.addBone $.modifiers[#Skin] $Bone03 1

		skinOps.addBone $.modifiers[#Skin] $Bone04 1

		skinOps.addBone $.modifiers[#Skin] $Bone52 1

		skinOps.addBone $.modifiers[#Skin] $Bone53 1

		skinOps.addBone $.modifiers[#Skin] $Bone54 1

		skinOps.addBone $.modifiers[#Skin] $Bone55 1

		$.modifiers[#Skin].cross_radius = 14.8327

		subobjectLevel = 1

		$.modifiers[#Skin].filter_vertices = on

		skinOps.SelectBone $.modifiers[#Skin] 2

		skinOps.SelectEndPoint $.modifiers[#Skin]

		actionMan.executeAction 0 "40021"  -- Selection: Select All

		max select all

		skinOps.weightTool $.modifiers[#Skin]

		skinOps.setWeight $.modifiers[#Skin] 1

		subobjectLevel = 0
		
		$.modifiers[#Skin].mirrorEnabled = off
		messagebox "dnd 스킨완료"
	)

--dnd skin end
	((findstring $.name "bb") == 1):
--bigbo skin start
(
		max modify mode

		modPanel.addModToSelection (Skin ()) ui:on

		skinOps.addBone $.modifiers[#Skin] $Bip01 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine3' 1

		skinOps.addBone $.modifiers[#Skin] $Bone01 1

		skinOps.addBone $.modifiers[#Skin] $Bone02 1

		skinOps.addBone $.modifiers[#Skin] $Bone03 1

		skinOps.addBone $.modifiers[#Skin] $Bone04 1

		$.modifiers[#Skin].cross_radius = 9.20376

		subobjectLevel = 1

		$.modifiers[#Skin].filter_vertices = on

		skinOps.weightTool $.modifiers[#Skin]

		subobjectLevel = 0

		$.modifiers[#Skin].mirrorEnabled = off

		modPanel.setCurrentObject $.modifiers[#Skin]
		messagebox "Bigbo 스킨완료"
	)

--bigbo skin end
	((findstring $.name "rn") == 1):
--rina skin start
(
		modPanel.addModToSelection (Skin ()) ui:on

		skinOps.addBone $.modifiers[#Skin] $Bip01 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger3' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger4' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger31' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger41' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine2' 1

		$.modifiers[#Skin].cross_radius = 14.186

		subobjectLevel = 1

		$.modifiers[#Skin].filter_vertices = on

		skinOps.weightTool $.modifiers[#Skin]
		messagebox "Rina 스킨완료"
	)
--rina skin end
	((findstring $.name "mm") == 1):
--mingming skin start
(
		modPanel.addModToSelection (Skin ()) ui:on

		skinOps.addBone $.modifiers[#Skin] $Bip01 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Head' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 L UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Neck' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Pelvis' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Calf' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Clavicle' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger01' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger1' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger2' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger11' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Finger21' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Foot' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Forearm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Hand' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Thigh' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R Toe0' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 R UpperArm' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine' 1

		skinOps.addBone $.modifiers[#Skin] $'Bip01 Spine1' 1

		skinOp