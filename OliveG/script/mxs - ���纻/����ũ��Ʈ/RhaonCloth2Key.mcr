-------------------------------------------------------------
--
-- Rhaon Ent.
--
-- 2006. 05. Pyo Taesu (flood@rhaon.co.kr)
--
--
-- Cloth simulation의 결과에서 bone animation의 key정보를 생성하는 스크립트.
--
-- * cloth simulation이 아니라도 메쉬형태의 것이면 적용가능하다.
--
-------------------------------------------------------------

macroScript Rhaon_Cloth2Key
	category:"RhaonScript"
	buttonText:"Cloth2Key"
	tooltip:"Cloth simulation to bone animation keys"
(
	struct RhaonCloth2Key
	(
		bonecount = 30,
		self, -- 자신 오브젝트, MAXScript는 C++의 this같은게 없는걸까?
		clothObject,
		ui_rollout,

		fn getAllSnapState =
		(
			r = for i = 1 to snapmode.numOSnaps collect
			( 
				for j = 1 to (snapmode.getOSnapNumItems i) collect (snapmode.getOSnapItemActive i j)
			)
			
			return #(snapmode.active, r)
		),

		fn restoreAllSnapState vals =
		(
			snapMode.active = vals[1]
			vals = vals[2]

			for i = 1 to snapmode.numOSnaps do
			( 
				for j = 1 to (snapmode.getOSnapNumItems i) do (snapmode.setOSnapItemActive i j vals[i][j])
			)
		),

		fn clearAllSnapState =
		(
			for i = 1 to snapmode.numOSnaps do
			( 
				for j = 1 to (snapmode.getOSnapNumItems i) do (snapmode.setOSnapItemActive i j false)
			)
		),

		fn setSnapStateTrue name =
		(
			for i = 1 to snapmode.numOSnaps do
			( 
				for j = 1 to (snapmode.getOSnapNumItems i) do
				(
					if name == (snapmode.getOSnapItemName i j) then
					(
						(snapmode.setOSnapItemActive i j true)
						return OK
					)
				)
			)
		),


		fn pickVertex meshObj =
		(
				local oldSnapMode = getAllSnapState()
				
				snapMode.active = true
				clearAllSnapState()
				setSnapStateTrue "Vertex"
				
				local vertPos = pickPoint snap:#3d rubberBand:meshObj.center
				
				for i = 1 to meshOp.getNumVerts meshObj do
				(
					if (meshOp.getVert meshObj i) == vertPos then
					(
						restoreAllSnapState oldSnapMode
						return i
					)
				)
				
				restoreAllSnapState oldSnapMode
				return undefined
		),

		fn checkClothObject obj message:false =
		(
			-- 선택된 오프젝트 가 적합한지 체크한다. --
			
			if obj == undefined then
			(
				if message then messagebox "No object selected."
				return false
			)
			
			if (classof obj) == ObjectSet then
			(
				if message then messagebox "Select one object, please."
				return false
			)
		
			try
			(
				-- 이 오브젝트에대해 사용할 함수들을 지원하는지 체크 --
				v = meshOp.getVert obj 1
				n = getNormal obj 1
				k = meshOp.getNumVerts obj
			)
			catch
			(
				if message then messagebox "Selected object is not acceptable"
				return false
			)

			return true
		),
		
		fn prepareClothObject =
		(
			clothObject = getNodeByName ui_rollout.textClothObject.text
			
			if not (checkClothObject clothObject message:true) then
			(
				clothObject = undefined
				return false
			)
			return true
		),

		-- cloth에서 bone정보를 생성하는 함수 --
		
		fn doRun = 
		(
			if not prepareClothObject() then
			(
				return ok
			)
			
			vertBones = #()
			numVerts = meshOp.getNumVerts clothObject
			
			for i = 1 to bonecount do
			(
				vertIndex = ui_rollout.editVertexes[i].text as integer
				boneName = ui_rollout.editBones[i].text
				
				if vertIndex == undefined or vertIndex <= 0 or vertIndex > numVerts then continue
				if boneName == "" then continue
				
				bone = getNodeByName boneName
				
				if (classof bone) != BoneGeometry then continue
				
				append vertBones #(vertIndex, bone)
				
				format "vert=%, bone=%\n" vertIndex boneName
			)

			
			for i = 1 to vertBones.count do
			(
				hasPrevLink = false
				if i > 1 then hasPrevLink = vertBones[i-1][4]
				
				hasNextLink = false
				if i < vertBones.count then hasNextLink =  (vertBones[i+1][2].parent == vertBones[i][2])
				
				append vertBones[i] hasPrevLink
				append vertBones[i] hasNextLink
			)
			
			local boneRot = ui_rollout.spinBoneRotation.value
			local frameStride = 1.f * (ui_rollout.spinFrameStride.value)
			local cosBoneRot = cos boneRot
			local sinBoneRot = sin boneRot
			local framecount = 1 + (((animationrange.end - animationrange.start) as float) / (frameStride as float)) as integer
			local bonePosOffsetArr = #()
			
			for i = 1 to vertBones.count do
			(
				local t = animationrange.start
				local vertIndex = vertBones[i][1]
				local bone = vertBones[i][2]
				local hasNextLink = vertBones[i][4]
				local hasPrevLink = vertBones[i][3]
				
				deleteKeys bone #allKeys

				with animate on
				(
					for j = 1 to framecount do
					(
						at time t in coordsys world
						(
							vertPos = meshOp.getVert clothObject vertIndex
						
							if not hasPrevLink then
							(
								if j == 1 then
								(
									bonePosOffsetArr = #()
								)
								
								append bonePosOffsetArr (bone.pos - vertPos)
							)

							bonePosOffset = bonePosOffsetArr[j]
							
							if hasNextLink then
							(
								vertPos2 = meshOp.getVert clothObject vertBones[i+1][1]
								
								za0 = - (getNormal clothObject vertIndex)
								xa0 = normalize (vertPos2 - vertPos)
								za0 -= xa0 * (dot xa0 za0)
								ya0 = cross za0 xa0
								
								-- boneRot 만큼 bone을 x축을 중심으로 회전 --
								xa = xa0
								ya = ya0 * cosBoneRot + za0 * sinBoneRot
								za = za0 * cosBoneRot - ya0 * sinBoneRot
								
								m = matrix3 0
								m[1] = [xa.x, ya.x, za.x]
								m[2] = [xa.y, ya.y, za.y]
								m[3] = [xa.z, ya.z, za.z]
								
								bone.rotation = m as quat
							)
							else if hasPrevLink then
							(
								bone.rotation = vertBones[i-1][2].rotation
							)
							
							bone.pos = bonePosOffset + vertPos
						)
		
						t += frameStride
					)
				)
			)
		),
		
		fn doClear =
		(
			ui_rollout.spinBoneRotation.value = 0.0
			ui_rollout.spinFrameStride.value = 1.0
			ui_rollout.editFileName.text = ""
			ui_rollout.textClothObject.text = ""

			for i = 1 to bonecount do
			(
				ui_rollout.editVertexes[i].text = ""
				ui_rollout.editBones[i].text = ""
			)
		),

		fn doLoad =
		(
			fname = ui_rollout.editFileName.text
			fname = GetOpenFileName filename:fname types:"Cloth2key file(*.c2k)|*.c2k|"
			if fname == undefined then return ok
			
			f = openFile fname mode:"r"

			-- 파일 버젼 확인 --

			local version = readLine f

			if version == "hasversion" then
			(
				version = (readLine f) as integer
			)
			else
			(
				version = 0

				close f
				f = openFile fname mode:"r"
			)


			if version > 0 then
			(
				ui_rollout.spinBoneRotation.value = (readLine f) as float
				ui_rollout.spinFrameStride.value = (readLine f) as float
			)
			else
			(
				ui_rollout.spinBoneRotation.value = 0.0
				ui_rollout.spinFrameStride.value = 1.0
			)

			
			ui_rollout.textClothObject.text = readLine f
			
			vertBoneNames = #()
			
			while not (eof f) and vertBoneNames.count < bonecount do
			(
				v = readLine f
				b = readLine f
				
				append vertBoneNames #(v, b)
			)
			
			for i = 1 to bonecount do
			(
				v = b = ""
				
				if i <= vertBoneNames.count then
				(
					v = vertBoneNames[i][1]
					b = vertBoneNames[i][2]
				)
				
				ui_rollout.editVertexes[i].text = v
				ui_rollout.editBones[i].text = b
			)
			
			close f
			
			ui_rollout.editFileName.text = fname
		),

		fn doSave =
		(
			fname = ui_rollout.editFileName.text
			fname = GetSaveFileName filename:fname types:"Cloth2key file(*.c2k)|*.c2k|"
			if fname == undefined then return ok
			
			f = openFile fname mode:"w"

			-- version --
			format "hasversion\n" to:f
			format "1\n" to:f

			format "%\n" ui_rollout.spinBoneRotation.value to:f
			format "%\n" ui_rollout.spinFrameStride.value to:f

			format "%\n" ui_rollout.textClothObject.text to:f
			
			for i = 1 to bonecount do
			(
				format "%\n" ui_rollout.editVertexes[i].text to:f
				format "%\n" ui_rollout.editBones[i].text to:f
			)
			
			close f
			
			ui_rollout.editFileName.text = fname
		),


		fn doPickVertex vertNum =
		(
			if not prepareClothObject() then return ok
		
			pt = pickVertex clothObject
			
			if pt == undefined then return OK

			format "doPickVertex %, %...\n" vertNum pt
			
			pos = meshOp.getVert clothObject pt
			
			gw.text pos (pt as string)

			ui_rollout.editVertexes[vertNum].text = pt as string
		),

		fn doPickBone boneNum obj =
		(
			format "doPickBone %, %...\n" boneNum obj

			while (classof obj) == BoneGeometry do
			(
				ui_rollout.editBones[boneNum].text = obj.name
				
				if 1 != obj.children.count then exit
				
				boneNum += 1
				obj = obj.children[1]

				if boneNum > bonecount then exit
				if ui_rollout.editBones[boneNum].text != "" then exit
			)
		),
		
		fn doPickClothObject obj =
		(
			if not (checkClothObject obj message:true) then
			(
				return ok
			)
			
			ui_rollout.textClothObject.text = obj.name
		),

		fn run =
		(
			-- 사용자 인터페이스 생성 --
		
			rof = newRolloutFloater "Rhaon_Cloth2Key" 430  400

			clothObject = undefined

			txt = "rollout Rhaon_Cloth2Key \"Rhaon Cloth2Key (Pyo Taesu)...\" (\n"
			txt += "local cloth2key\n"
			txt += "fn filterBone obj = classof obj == BoneGeometry \n"
			txt += "fn filterClothObject obj = (cloth2key.checkClothObject obj) \n"
			
			txt += "editText editFileName \"File:\" pos:[15,15] width:220 height:20 readOnly:true\n"
			txt += "button btnLoad \"Load\" pos:[245,15] width:80 height:22\n"
			txt += "button btnSave \"Save\" pos:[330,15] width:80 height:22\n"

			txt += "editText textClothObject \"ClothObject:\" pos:[15,50] width:200 height:20\n"
			txt += "pickbutton btnPickClothObject \"Pick\" filter:filterClothObject pos:[250,50] width:100 height:20\n"
			
			txt += "spinner spinBoneRotation \"BoneRot:\" range:[-360,360,0] pos:[50,85] width:100 height:20\n"
			txt += "spinner spinFrameStride \"FrameStride:\" range:[1,30,1] pos:[50,115] scale:1 width:100 height:20\n"
			
			txt += "button btnClear \"Clear\" pos:[190,85] width:100 height:20\n"
			txt += "button btnRun \"Run\" pos:[300,85] width:100 height:20\n"

			for i = 1 to bonecount do
			(
				y = (i * 35 + 115) as string
				n = i as string
				txt += "editText editVertex" + n + " \"V" + n + ":\" pos:[15," + y + "] width:103 height:20\n"
				txt += "button btnVertex" + n + "pick \"Pick\" pos:[131," + y + "] width:43 height:22\n"
				txt += "editText editBone" + n + " \"Bone" + n + ":\" pos:[189," + y + "] width:157 height:21\n"
				txt += "pickbutton btnBone" + n + "Pick \"Pick\" filter:filterBone pos:[360," + y + "] width:43 height:22\n"
			)

			txt += "on btnPickClothObject picked obj do (cloth2key.doPickClothObject obj)\n"
			txt += "on btnRun pressed do cloth2key.doRun()\n"
			txt += "on btnClear pressed do cloth2key.doClear()\n"
			txt += "on btnLoad pressed do cloth2key.doLoad()\n"
			txt += "on btnSave pressed do cloth2key.doSave()\n"


			for i = 1 to bonecount do
			(
				n = i as string
				txt += "on btnVertex" + n + "pick pressed do (cloth2key.doPickVertex " + n + ")\n"
				txt += "on btnBone" + n + "Pick picked obj do (cloth2key.doPickBone " + n + " obj)\n"
			)

			txt_editVerts = "local editVertexes = #("
			txt_editBones = "local editBones = #("

			for i = 1 to bonecount do
			(
				n = i as string
				
				if 1 != i then
				(
					txt_editVerts += ", "
					txt_editBones += ", "
				)
				
				txt_editVerts += "editVertex" + n
				txt_editBones += "editBone" + n
			)
			
			txt_editVerts += ")\n"
			txt_editBones += ")\n"

			txt += txt_editVerts
			txt += txt_editBones

			txt += ")\n"

			--format "self=%\n" self

			ui_rollout = execute txt
			addRollout ui_rollout rof

			ui_rollout.cloth2key = self
		)
	)

	on execute do
	(
		local cloth2key = RhaonCloth2Key()
		cloth2key.self = cloth2key
		cloth2key.run()
	)
)

