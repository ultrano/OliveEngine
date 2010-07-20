-------------------------------------------------------------
--
-- Rhaon Ent.
--
-- 2004. 09. Pyo Taesu
--
--
--
-------------------------------------------------------------

utility RhaonExportTRMap "Rhaon Export TR Map v0.4"
(
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
		
		fn addProgressBaseLine obj =
		(
			m_progressEnd += numKnots obj
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
			writeString fout "<RhaonTRMap001>"
			
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

		fn outputBaseLine obj =
		(
			local iNumPoints = numKnots obj 1

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
		
		--try
		(
			local startTime = timeStamp()
		
			exp.beginExport()
	
			exp.outputHeader()
			
			for obj in old_selection do
			(
				exp.addProgressEndObj obj
			)

			exp.addProgressBaseLine $baseline
			
			exp.progress 5.0

			exp.outputBaseLine $baseline
			
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
	
	------------------------------------------------------------
	
	button btn_exportSelected "Export Selected" width:120
	label lb_about1 "2004. Rhaon Ent."
	label lb_about2 "pyotaesu@hotmain.com"
	
	
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
	
	
) -- utility RhaonExportTRMap

