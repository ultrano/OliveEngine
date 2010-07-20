--------------------------- te tool v0.91------------------------
---- yhucks@naver.com / http://yhucks.com / http://rhaon.co.kr --
---- 2007.12.22 edit v0.91                                     --
---- TR Exporter map addon                                     --
---- v0.9                                                      --
-----manual search button add                                  --
-----------------------------------------------------------------
macroScript TE_tools
	category:"RhaonScript"
	toolTip:"Terrain edit tool v0.91 20071222"
(
(
rollout TEdittool "TR MAP tools" width:221 height:495
(
	local targeo = "ABC"
	local target = #()
	local editobj = #()
	local match_tv = #()
	local match_ev = #()
	local sel = #()
-------------------trmap expoter----------------------------
struct ExportMesh
	(	
		fout, -- file output stream
		
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
			
			return true
		),
		
		------------------------------------------------------------------

		fn isTrackExportable obj =
		(
			if obj == undefined do
			(
				return false 
			)

			if not (isKindOf obj line) do
			(
				return false
			)

			if (numSplines obj) == 0 do
			(
				return false
			)

			if (numSplines obj) > 1 do
			(
				return false
			)

			--if not (isClosed obj 1) do
			--(
			--	return false
			--)

			return true
		),

	
		-----------------------------------------------------------------
		
		fn beginExport =
		(
			progressStart "Export TR Map..."
		),
		
		fn endExport =
		(
			writeLong fout 0
			
			progressUpdate 100.0
			progressEnd()
			FClose fout
		),
		
		fn progress val =
		(
			m_progressCurrent += val
			local bRet = progressUpdate (m_progressCurrent/m_progressEnd * 100)
			if not bRet do
			(
				m_isCanceled = true
				FClose fout
				throw "Canceled."
			)
		),


		------------------------------------------------------------------
		
		fn addProgressTrack obj =
		(
			if isTrackExportable obj do
			(
				m_progressEnd += numKnots obj
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
			
			-- material -----------------
			
			addProgressEndMaterial obj.material
			
			-- vertices -----------------
			
			m_progressEnd += obj_mesh.numVerts

			-- vertex color -------------

			m_progressEnd += getNumCPVVerts obj_mesh
			
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
			writeString fout "<RhaonTRMap008>"
			
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
			
			progress 1.0
		),
	

		-------------------------------------------------------------

		fn outputTrack obj =
		(
			if not isTrackExportable obj do
			(
				return OK
			)

			local iNumPoints = numKnots obj 1

			writeLong fout 1
			outputString obj.name
			writeLong fout iNumPoints
			
			for i = 1 to iNumPoints do
			(
				local v = in coordsys #world getKnotPoint obj 1 i
				local vIn = in coordsys #world getInVec obj 1 i
				local vOut = in coordsys #world getOutVec obj 1 i
				outputPoint3 v
				outputPoint3 vIn
				outputPoint3 vOut
			)
		),

		fn outputTrackEnd =
		(
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
						
			transform obj_mesh (at time animationrange.start obj.objecttransform)
		
			(
				writeLong fout 1
				outputString obj.name
				
				-- material -----------------
				
				local material = obj.material
		
				outputMaterial material
				
				-- vertices -----------------
				
				local numVerts = obj_mesh.numVerts
		
				writeLong fout numVerts
				
				(
					for vertIndex = 1 to numVerts do
					(
						local v = (meshOp.getVert obj_mesh vertIndex)
						
						outputPoint3 v
					)
					
					progress numVerts
				)

				-- vertex color -------------

				local numCVerts = getNumCPVVerts obj_mesh

				writeLong fout numCVerts
				for cvertIndex = 1 to numCVerts do
				(
					outputColor (getVertColor obj_mesh cvertIndex)
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
					local faceCVerts = [0,0,0]
					if numCVerts > 0 do
					(
						faceCVerts = (getVCFace obj_mesh faceIndex)
					)
					local faceTVerts = if hasMaps then (getTVFace obj_mesh faceIndex) else [1,1,1]
					local n = (meshop.getFaceRNormals obj_mesh faceIndex)

					for j = 1 to 3 do
					(
						writeLong fout (faceVerts[j] as integer)
						writeLong fout (faceCVerts[j] as integer)
						writeLong fout (faceTVerts[j] as integer)
					
						if n[j] == undefined do
						(
							n[j] =  (getFaceNormal obj_mesh faceIndex)
						)
						
						outputPoint3 n[j]
						--outputPoint3 (getFaceNormal obj_mesh faceIndex)
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
	
	
	fn fileOutSelected fname =
	(
		local fout = fopen fname "wbS"
		
		if fout == undefined do
		(
			messageBox "Cannot open file for writting." title:"Export Error" beep:false
			return OK
		)

		local exp = ExportMesh fout:fout
		local old_selection = selection as array
		local tracks = $track* as array
		
		--try
		(
			local startTime = timeStamp()
		
			exp.beginExport()
	
			exp.outputHeader()
			
			for obj in old_selection do
			(
				exp.addProgressEndObj obj
			)

			exp.addProgressTrack $baseline

			for obj in tracks do
			(
				exp.addProgressTrack obj
			)
			
			exp.progress 5.0

			exp.outputTrack $baseline
			
			for obj in tracks do
			(
				exp.outputTrack obj
			)

			exp.outputTrackEnd()
			
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
		--max utility mode
	)
-------------------trmap expoter----------------------------

----------- ui start ----------------------------------------
	label mtitle "Terrain Edit Tool v0.9" pos:[54,5] width:112 height:18
	groupBox match_vertex_Search "Match_vertex_Search" pos:[7,24] width:207 height:161
	label lbl1 "Terrain select" pos:[18,56] width:94 height:18
	pickButton pickobj "Pick object" pos:[122,53] width:72 height:26 message:"select terrain"
	spinner scope "Error scope :" pos:[44,101] width:141 height:16 range:[0,100,0.1]
	button alls "all Vertex Search" pos:[51,125] width:120 height:25
	button Manuals "Manual Vertex Search" pos:[51,155] width:120 height:25
	groupBox edit_Terrain "Edit_Terrain" pos:[7,195] width:205 height:151
	spinner relaxam "relaxAmount :" pos:[44,236] width:146 height:16 range:[0,1,0.5] scale:0.1
	spinner relaxit "relaxIterations :" pos:[34,262] width:156 height:16 range:[0,100,50] scale:1
	spinner glownum "glow_vertex :" pos:[47,211] width:143 height:16 range:[0,100,2] type:#float scale:1 
	button update "Update Terrain" pos:[52,301] width:120 height:30
	groupBox tr_export_map "Export TR Map v0.12" pos:[7,355] width:205 height:86
	button btn_exportSelected "Export Selected" pos:[54,388] width:120
	label lbl2 "Rhaon Entertainment      http://www.Talesrunner.com" pos:[40,447] width:154 height:37
-------------- ui end --------------------------------------------

--------------------export btn----------------------------------
on btn_exportSelected pressed do
	(
		if $baseline == undefined do
		(
			messageBox "$baseline object not found !" title:"Export Error" beep:false
			return OK
		)

		if not (isKindOf $baseline line) do
		(
			messageBox "$baseline object is not line !" title:"Export Error" beep:false
			return OK
		)

		if (numSplines $baseline) == 0 do
		(
			messageBox "$baseline has no splines !" title:"Export Error" beep:false
			return OK
		)

		if (numSplines $baseline) > 1 do
		(
			messageBox "$baseline has multiple splines !" title:"Export Error" beep:false
			return OK
		)

		if not (isClosed $baseline 1) do
		(
			messageBox "$baseline must be closed !" title:"Export Error" beep:false
			return OK
		)
		local fname = lastExportedFileName
		
		if fname != undefined then
		(
			fname = GetSaveFileName filename:fname types:"Rhaon Export Files (*.tm1)|*.tm1|"
		)
		else
		(
			fname = GetSaveFileName types:"Rhaon Export Files (*.tm1)|*.tm1|"
		)
		
		if fname == undefined do
		(
			return OK
		)
	
		fileOutSelected fname
	)

--------------------export btn end------------------------------
	on pickobj picked obj do
	(
		format "targeo  = %\n" targeo
		
		if obj != undefined do
		 (
			obj.wirecolor = blue
			pickobj.text = obj.name
			select obj
			targeo = $
		 )
	)
	
	on alls pressed  do
	(
	for i = 1 to $.selectedverts.count do 
		(
		append target $.selectedverts[i]
		)
	select targeo
	subobjectLevel = 1
	max select all
	for i = 1 to $.selectedverts.count do 
	(
	 for tgi = 1 to target.count do 
	 (
		a = length($.selectedverts[i].pos - target[tgi].pos)
		format "length:%target:%\n" a target[tgi].index
	 if length($.selectedverts[i].pos - target[tgi].pos) < scope.value do 
	 	(
		append match_ev $.selectedverts[i]
		append match_tv target[tgi]
		)
	 )
	)
	if match_tv.count != match_ev.count do
	(
	messagebox "bad"
	format "target:% editobj:%\n" match_tv.count match_ev.count

	)
	if match_tv.count == match_ev.count do
	(
	messagebox "good"
	)
	)
	
	on Manuals pressed  do
	(
	for i = 1 to $.selectedverts.count do 
		(
		append target $.selectedverts[i]
		)
	select targeo
	subobjectLevel = 1
	for i = 1 to $.selectedverts.count do 
	(
	 for tgi = 1 to target.count do 
	 (
		a = length($.selectedverts[i].pos - target[tgi].pos)
		format "length:%target:%\n" a target[tgi].index
	 if length($.selectedverts[i].pos - target[tgi].pos) < scope.value do 
	 	(
		append match_ev $.selectedverts[i]
		append match_tv target[tgi]
		)
	 )
	)
	if match_tv.count != match_ev.count do
	(
	messagebox "bad"
	format "target: 5.097984e-201ditobj:" match_tv.count match_ev.count
	)
	if match_tv.count == match_ev.count do
	(
	messagebox "good"
	)
	)

	
	on update pressed  do
	(
	for ti = 1 to match_ev.count do 
		(
		match_ev[ti].pos = match_tv[ti].pos
		)
	select targeo
	subobjectLevel = 1
	for i = 1 to match_ev.count do 
	(
	append sel match_ev[i].index
	)
	$.EditablePoly.SetSelection #Vertex #{}
	$.selectedverts = sel
	for glow = 1 to glownum.value do
	(
	$.EditablePoly.GrowSelection ()
	)	
	$.relaxAmount = relaxam.value
	$.relaxIterations = relaxit.value
	$.relaxHoldBoundaryPoints = on
	$.relaxHoldOuterPoints = off
	$.EditablePoly.Relax ()
	clearSelection()
	)
)
)
createdialog TEdittool
)