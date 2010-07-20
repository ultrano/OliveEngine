-------------------------------------------------------------
--
-- Rhaon Ent.
--
-- 2004. 09. Pyo Taesu (bigflood@hitel.net)
--
-- 
--
-------------------------------------------------------------

macroScript Rhaon_SetScale_1_1_1
	category:"RhaonScript"
	buttonText:"SetScale_1_1_1"
	toolTip:"Set scale property [1,1,1] without changing appearance"
(
	fn applyMatrix v m = (in coordsys #local v.pos = v.pos * m)
	
	fn setScaleMeshVerts obj =
	(
		m = in coordsys #world (scaleMatrix obj.scale)
	
		for v in obj.verts do
		(
			applyMatrix v m
		)
		
		obj.scale = [1,1,1]
	)

	on execute do
	(
		local sel = selection as array
		local count = 0
		for i in sel do
		(
			if (isKindOf i Editable_Mesh) or (isKindOf i Editable_Poly) do
			(
				count = count + 1
				setScaleMeshVerts i
			)
		)
			
		if (0 == count) then
		(
			messageBox "No mesh objects selected." title:"SetScale_1_1_1" beep:false
		)
		else
		(
			messageBox ((count as string) + " object(s) modified.") title:"SetScale_1_1_1" beep:false
		)
	)
)

