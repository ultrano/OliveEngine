--------------------hucks_Utillity v1.3-------------------------
--yhucks@naver.com | http://yhucks.com | http://rhaon.co.kr-----
--v1.3                                                        --
--add emp button, add solver linkto point, add reset_mtl      --
----------------------------------------------------------------
macroScript Helper_rescale
	category:"hucks_script"
	toolTip:"hucks_utillity v0.5"
(
(
rollout Helper_Gloval_reScale "re_Scale Helper" width:162 height:493
(
-------------ui_start----------------------
	groupBox grp1 "HI solver" pos:[8,39] width:147 height:92
	label lbl1 "helper Global rescale" pos:[12,11] width:140 height:19
	button run "HI solver" pos:[33,158] width:95 height:20
	spinner g_size "size : " pos:[28,65] width:108 height:16 range:[0,100,0] type:#float scale:1
	button reset_s "resize" pos:[33,95] width:96 height:27
	groupBox grp2 "helper tool" pos:[9,139] width:146 height:106
	checkButton ckb1 "Manipulate" pos:[33,186] width:95 height:20 checked:false
	groupBox grp3 "Manipulate" pos:[10,369] width:146 height:84
	spinner spn2 "Size : " pos:[39,396] width:102 height:16 range:[0,100,0]
	spinner spn3 "Length : " pos:[24,423] width:117 height:16 range:[0,100,0]
	label lbl2 "http://rhaon.co.kr http://yhucks.com" pos:[8,458] width:142 height:30
	button btn5 "Button" pos:[160,37] width:0 height:0
	button svlink "sover link point" pos:[33,213] width:95 height:20
	button resetmtl "reset_mtl" pos:[35,338] width:95 height:20
	groupBox utillity "Utillity" pos:[9,251] width:146 height:114
	button autolock "autolock" pos:[35,313] width:95 height:20 enabled:false
	button btn7 "Button" pos:[25,275] width:50 height:29 enabled:false
	button btn8 "Button" pos:[88,274] width:50 height:29 enabled:false
---------------ui_end------------------------
	on svlink pressed  do
	(
	--select ($'IK Chain'*)
	-- IK chain select all

	mySelection = #()
	-- copy content of $ into mySelection

	for i = 1 to $.count do -- append selection
		(
		append mySelection $[i]
		)
		for i = 1 to mySelection.count do --make point and link ikchan.parent
		(
		ikpos = mySelection[i].pos
		pt = Point Box:on pos:ikpos size:10
		mySelection[i].parent = pt
		)
	)

	on resetmtl pressed  do
	(
	max unfreeze all
	clearselection()
	macros.run "Medit Tools" "clear_medit_slots"
	select $*
	for i = 1 to $.count do 
		(
		if ((classof $[i]) == Editable_Poly) do
			(
			$[i].material = meditMaterials[i]
			)
		)
	macros.run "Medit Tools" "condense_medit_slots"
	messagebox "END Material Editor Clear"
	)
	
	on run pressed  do
	(
		if (classof $) != BoneGeometry do
		(
		messagebox "Please, select BoneGeometry object."
		return OK
		)
		macros.run "Inverse Kinematics" "HI_IK"
	)
	on g_size changed val do
	(
	if (classof $) == ObjectSet do
		(
		for i = 1 to $.count do
	 		(
	 			if ((classof $[i]) == IK_Chain_Object) do
				(
					--messagebox "IK_Chain_Object"
					$[i].transform.controller.goalSize = g_size.value
				)
				if ((classof $[i]) == point) do
	 			(
					--messagebox "point"
	 				$[i].size = g_size.value
				)
				if ((classof $[i]) == BoneGeometry) do
				( 				--messagebox "BoneGeometry"
	 				$[i].width = g_size.value
	 				$[i].height = g_size.value
	 			)
		 	)
		)
	if ((classof $) == IK_Chain_Object) do
		(
			--messagebox "IK_Chain_Object"
			$.transform.controller.goalSize = g_size.value
		)
	if ((classof $) == point) do
	 	(
			--messagebox "point"
	 		$.size = g_size.value
		)
	if ((classof $) == BoneGeometry) do
		(
	 		--messagebox "BoneGeometry"
	 		$.width = g_size.value
	 		$.height = g_size.value
	 	)
	)
	on reset_s pressed  do
	(
	if (classof $) == ObjectSet do
		(
		for i = 1 to $.count do
	 		(
	 			if ((classof $[i]) == IK_Chain_Object) do
				(
					--messagebox "IK_Chain_Object"
					$[i].transform.controller.goalSize = g_size.value
				)
				if ((classof $[i]) == point) do
	 			(
					--messagebox "point"
	 				$[i].size = g_size.value
				)
				if ((classof $[i]) == BoneGeometry) do
				( 				--messagebox "BoneGeometry"
	 				$[i].width = g_size.value
	 				$[i].height = g_size.value
	 			)
		 	)
		)
	if ((classof $) == IK_Chain_Object) do
		(
			--messagebox "IK_Chain_Object"
			$.transform.controller.goalSize = g_size.value
		)
	if ((classof $) == point) do
	 	(
			--messagebox "point"
	 		$.size = g_size.value
		)
	if ((classof $) == BoneGeometry) do
		(
	 		--messagebox "BoneGeometry"
	 		$.width = g_size.value
	 		$.height = g_size.value
	 	)
	)
	on ckb1 changed state do
		actionMan.executeAction 0 "59225"
)
)
createdialog Helper_Gloval_reScale
)