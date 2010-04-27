-- Filename		: max2xml.ms
-- Made by		: 김용준(kim yong-joon, newtype@chollian.net)
-- License		: GPL
-- System  		: Tested on MAX 5.x
-- Target API	: Direct 3D
-- Version      : 1.09 beta
-- 1st Revision : 2003.02.24
-- 2nd Revision : 2003.03.04(composite material fixed)
-- 3rd Revision : 2003.03.16(Bounding Box export)
-- 4th Revision : 2003.03.28('count' attribute removed, 'parent' element changed to attribute, doubtful hasproperty func -_- )
-- 5th Revision : 2003.04.03(<Opacity> added at Material Element)
-- 6th Revision : 2003.04.19(BoneTable을 일반 오브젝트외에 따로 추가하여 관리), physique, skin modifier자동 선택
-- 7th Revision : 2003.07.21(실제로 전용 파서를 만들면서 버그패치)
-- 8th Revision : 2004.10.05(Helper지원 추가 DumpObjects함수 수정)
-- To Do        :

-- XML Element string
g_strBody			= "Body"
g_strInfo			= "Info"
g_strFilename		= "Filename"
g_strObjectCount	= "ObjectCount"
g_strMeshCount		= "MeshCount"
g_strAniStart		= "AnimationStart"
g_strAniEnd			= "AnimationEnd"
g_strTypeKey		= "KeyType"			-- KeyFrame, Sampling(ik,biped)

g_strMaterial		= "Material"
g_strSlot			= "Slot"
g_strObject			= "Object"
g_strTriVertex		= "Vertex"
g_strVertexNormal	= "VertexNormal"
g_strTriIndex		= "TriIndex"
g_strTexVertex		= "TexVertex"
g_strTexIndex		= "TexIndex"
g_strVertexWeight	= "VertexWeight"
g_strLocalTM		= "LocalTM"
g_strWorldTM		= "WorldTM"
g_strParent			= "Parent"
g_strKey			= "Key"
g_strValue			= "Value"
g_strPosition		= "Position"
g_strRotation		= "Quaternion"
g_strScale			= "Scale"
g_strBoundingBox	= "BoundingBox"
g_strMax			= "Max"
g_strMin			= "Min"
g_strCenter			= "Center"
g_strBone			= "Bone"

g_strMtrlDiffuse	= "Diffuse"
g_strMtrlAmbient	= "Ambient"
g_strMtrlSpecular	= "Specular"
g_strMtrlEmissive	= "Emissive"
g_strMtrlOpacity	= "Opacity"
g_strMtrlPower		= "Power"
g_strMtrlMapDiffuse	= "DiffuseMap"
g_strMtrlMapSpecualr= "SpecularMap"
g_strMtrlMapBump	= "BumpMap"
g_strMtrlMapDisplace= "DisplacementMap"

-- XML Attribute string
g_strID				= "ID"
g_strBoneID			= "BoneID"
g_strIndex			= "Index"
g_strName			= "Name"
g_strClass			= "Class"
g_strBoneCount		= "BoneCount"
g_strMtrlCount		= "MaterialCount"
g_strMtrlID			= "MaterialID"
g_strFrameNo		= "Frame"

g_uiObjectName		= 0
g_uiProgress		= 0

g_nObjectIDRef		= 1
g_bObjectIDWithName = true
g_bMultiplyQuaternion = false
g_bSampling			= false
g_nSampling			= 1
g_strKeyType		= "Keyframe"
g_snapObjects		= undefined

-- [MAX quaterion]            [D3D quaternion]
-- x,y,z,w                    -x,-z,-y,w

-- [D3D matrix]               [MAX matrix]
-- _11 _12 _13 0              _11 _13 _12 0
-- _21 _22 _23 0       <->    _31 _33 _32 0
-- _31 _32 _33 0              _21 _23 _22 0
-- _41 _42 _43 1              _41 _43 _42 1

-- Basic type definitions
struct MATRIX_D3D
( 
	_11, _12, _13, _14,
	_21, _22, _23, _24,
	_31, _32, _33, _34,
	_41, _42, _43, _44
)

struct MTRL_ID_FACE
(
	ID,
	faceSet
)

struct BONE_WEIGHT
(
	strName,		-- bone name
	weight
)

struct OBJECT_WEIGHT
(
	nBoneCount,
	vertexSet
)

fn FindObject name =
(
	for o in objects do
	(
		if o.name == name then return o
	)
	
	undefined
)

-- qsort는 struct를 지원하지 않는다.(적어도 테스트 해본 결과는 그렇다.)
-- 아래의 문장을 돌려보면 struct배열에서 qsort가 작동하지 않는것을 확인할 수 있다.
--struct T 
--( 
--	name, 
--	weight 
--)
--arr = #()
--for i=1 to 3 do
--(
--	local tmp = T 0 0
--	tmp = T (i as string) (random 0.0 1.0)
--	append arr tmp
--)
--
--"before"
--for i in arr do print i 
--"after"
--qsort arr (fn compare v1 v2 = (v2.weight- v1.weight))
--for i=1 to a.count do print arr[i]

-- 간단한 거품정렬함수
fn mysort arr fnCompare = 
(
	for i = 1 to arr.count do
		for j = i to arr.count do
		(
			if (fnCompare arr[i] arr[j]) > 0 then
			(
				t = arr[i]
				arr[i] = arr[j]
				arr[j] = t
			)
		)
)

struct ZUtility
(
	m_varSetObjectNames = #(),		-- object의 이름대신 ID값을 사용하기위한 table
	m_varSetBoneNames = #(),
	m_varSetMaterials = #(),		-- 현재 scene에서 사용중인 모든 material table
	
	-- 정의 : collect을 할때 겹치지 않게 collect한다.
	-- 설명 : 단순히 append하면 동일한 object가 중복 collect될수 있다.
	fn SafeAppend sets item =
	(
		for i = 1 to sets.count do
		(
			if sets[i] == item then
			(
				return undefined
			)
		)
		
		append sets item
	),
	
	-- 정의 : object의 이름대신 ID값을 사용하기위한 table을 만든다.
	-- 주의 : Constructor()에서 자동으로 불린다.
	fn CollectNames =
	(
		temp = dummy()
		temp.name = "NULL"
		SafeAppend m_varSetObjectNames temp.name
		for o in objects do
		(
			SafeAppend m_varSetObjectNames o.name
		)
	),
	
	-- 정의 : material의 이름대신 ID값을 사용하기위한 table을 만든다.
	-- 주의 : Constructor()에서 자동으로 불린다.
	fn CollectMaterials =
	(
		temp = standard()
		SafeAppend m_varSetMaterials temp	--material을 지정하지 않은 오브젝트는 0번 재질을 사용한다.
		for i = 1 to objects.count do
		(
			if objects[i].material == undefined do continue
			if classof objects[i].material == Standardmaterial then			-- material이 하나일 경우
			(
				SafeAppend m_varSetMaterials objects[i].material
			)
			
			if classof objects[i].material == Multimaterial then				-- materials이 여러개일 경우
			(
				for j = 1 to objects[i].material.count do
				(
					SafeAppend m_varSetMaterials objects[i].material[j]
				)
			)
		)
	),
	
	fn CollectBoneID = 
	(
		SafeAppend m_varSetBoneNames "NULL"
		for o in objects do
		(
			if ( classOf o == Biped_Object ) or ( classOf o == BoneGeometry ) or ( classOf o == bone ) or ( superclassof o == helper ) then
			(
				SafeAppend m_varSetBoneNames o.name
			)
		)
	),
	
	fn GetBoneID obj =
	(
		if obj != undefined then
		(
			for i = 1 to m_varSetBoneID.count do
			(
				if obj.name == m_varSetBoneNames[i] do return i-1
			)
		)
		0
	),
	
	fn GetBoneIDByName obj_name =
	(
		if obj_name != undefined then
		(
			for i = 1 to m_varSetBoneNames.count do
			(
				if obj_name == m_varSetBoneNames[i] do return i-1
			)
		)
		0
	),
	
	-- 정의 : object의 ID값을 돌려준다.
	--        실패할 경우 0을 돌려준다.
	fn GetObjectID obj =
	(
		if obj != undefined then
		(
			for i = 1 to m_varSetObjectNames.count do
			(
				if obj.name == m_varSetObjectNames[i] do return i
			)
		)
		0
	),		
	
	-- 정의 : object의 ID값을 돌려준다.
	--        실패할 경우 0을 돌려준다.
	fn GetObjectIDByName obj_name =
	(
		if obj_name != undefined then
		(
			for i = 1 to m_varSetObjectNames.count do
			(
				if obj_name == m_varSetObjectNames[i] do return i
			)
		)
		0
	),		
	
	-- 정의 : material의 ID값을 돌려준다.
	--        실패할 경우 0을 돌려준다.
	fn GetMaterialID mtrl =
	(
		if mtrl != undefined then
		(
			for i = 1 to m_varSetMaterials.count do
			(
				if m_varSetMaterials[i] == mtrl do return i
			)
		)		
		0
	),
	
		
	-- 정의 : MAX의 TM을 D3D의 TM으로 바꿔준다.
	fn ConvertToD3D_TM max_tm =
	(
		local	d3d_tm = MATRIX_D3D	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
		d3d_tm._11 = max_tm.row1.x
		d3d_tm._12 = max_tm.row1.z
		d3d_tm._13 = max_tm.row1.y
		d3d_tm._14 = 0.0
		
		d3d_tm._21 = max_tm.row3.x
		d3d_tm._22 = max_tm.row3.z
		d3d_tm._23 = max_tm.row3.y
		d3d_tm._24 = 0.0
		
		d3d_tm._31 = max_tm.row2.x
		d3d_tm._32 = max_tm.row2.z
		d3d_tm._33 = max_tm.row2.y
		d3d_tm._34 = 0.0
		
		d3d_tm._41 = max_tm.row4.x
		d3d_tm._42 = max_tm.row4.z
		d3d_tm._43 = max_tm.row4.y
		d3d_tm._44 = 1.0
		
		d3d_tm
	),
	
	-- 정의 : MAX의 POS좌표를 D3D의 POS좌표로 바꿔준다.
	fn ConvertToD3D_POS max_pos =
	(
		local	d3d_pos = [0,0,0]
		d3d_pos.x = max_pos.x
		d3d_pos.y = max_pos.z
		d3d_pos.z = max_pos.y
		
		d3d_pos
	),
	
	-- 정의 : MAX의 QUATERNIONS좌표를 D3D의 좌표로 바꿔준다.
	-- MAX_quat -> D3D_quat
	-- x,y,z,w  -> -x,-z,-y,w
	fn ConvertToD3D_QUAT max_quat =
	(
		local	d3d_quat = quat 0 0 0 0
		d3d_quat.x = -max_quat.x
		d3d_quat.y = -max_quat.z
		d3d_quat.z = -max_quat.y
		d3d_quat.w =  max_quat.w
		
		d3d_quat
	),
	
	-- 정의 : MAX의 텍스쳐 좌표를 D3D의 uv좌표로 바꿔준다.
	fn ConvertToD3D_UV max_pos =
	(
		local	d3d_uv = [0,0]
		d3d_uv.x = max_pos.x
		d3d_uv.y = 1.0 - Max_pos.y
		
		d3d_uv
	),
	
	-- 정의 : MAX의 vertex index를 D3D의 index 순서로 바꿔준다.
	fn ConvertToD3D_INDEX max_index =
	(
		local d3d_index = [0,0,0]
		d3d_index.x = max_index.x - 1
		d3d_index.y = max_index.z - 1
		d3d_index.z = max_index.y - 1
		
		d3d_index
	),
	
	-- 정의 : class로 object를 선택해주는 함수
	-- 사용 :
	-- a = SelectClass Editable_mesh
	-- print "a="
	-- for i in a do print (classof i)
	fn GetObjectsByClass cl =
	(
		varSetSameClass = #()
	
		for o in objects do
		(
			if classOf o == cl then 
			(
				append varSetSameClass o
			)
		)
		
		varSetSameClass	
	),
	
	-- 정의 : class로 object를 선택해주는 함수
	-- 사용 :
	-- a = SelectClass Editable_mesh
	-- print "a="
	-- for i in a do print (classof i)
	fn GetObjectsBySuperClass cl =
	(
		varSetSameClass = #()
	
		for o in objects do
		(
			if SuperClassOf o == cl then 
			(
				append varSetSameClass o
			)
		)
		
		varSetSameClass	
	),
	
	-- 정의 : Biped 오브젝트를 배열로 리턴한다.
	-- 사용 : a = GetObjects_Biped()
	fn GetObjects_Biped =
	(
		GetObjectsByClass Biped_Object
	),
	
	-- 정의 : Bone 오브젝트를 배열로 리턴한다.
	-- 사용 : b = GetObjects_BoneGeometry()
	fn GetObjects_BoneGeometry =
	(
		GetObjectsByClass BoneGeometry
	),
	
	-- 정의 : Editable Mesh를 배열로 리턴한다.
	-- 사용 : c = GetObjects_Mesh()
	fn GetObjects_Mesh =
	(
		GetObjectsByClass Editable_mesh
	),
	
	-- 정의 : Hierarchy를 고려한 Local Transform Matrix(TM)를 리턴한다.
	fn GetLocalTM obj =
	(
		local matLocal = copy obj.transform
		if obj.parent != undefined then
		(
			matLocal = obj.transform * ( inverse obj.parent.transform )
		)
		
		matLocal
	),
	
	-- 정의 : Pivot을 고려한 Local Vertex를 리턴한다.
	-- 주의 : in coordsys local getvert obj i하면 손쉽게 local vertex를 구할수 있다고
	--        생각할수 있으나, MAX에서 pivot은 local좌표계의 원점이 아니라 회전의 중심축일 뿐이다.
	--        그래서 local vertex를 직접 구하면 pivot을 무시한 잘못된 local vertex를 구하게 된다.(offset연산이 필요하다.)
	--        이 함수에서는 world vertex를 구해서 inverse tm을 곱하는 방법을 사용하고 있다.
	fn GetLocalVertices obj =
	(
		varSetVertex= #()
		
		TM = obj.transform
		InvTM = inverse TM
		
		for i = 1 to obj.numverts do
		(
			local vl -- vertex local
			local vw -- vertex world
			vw = in coordsys world getvert obj i
			vl = vw * InvTM
			append varSetVertex vl
		)
		
		varSetVertex
	),
	
	-- 정의 : vertex의 normal을 리턴한다.
	fn GetVertexNormals obj =
	(
		varSetNormal = #()
		for i = 1 to obj.numverts do
		(
			local n
			append varSetNormal (getnormal obj i)
		)
		
		varSetNormal
	),
	
	-- 정의 : Skin modifier로 구성된 vertex의 weight를 리턴한다.
	fn GetVertexWeightsBySkin obj =
	(
		ow = OBJECT_WEIGHT 0 #()
		
		if classof obj != Editable_mesh then return undefined			-- skin은 mesh에 붙는다.
		local sm														-- skin object
		max modify mode													-- max를 modify mode로 변환
		sm = obj.modifiers[#Skin]										-- skin modifier
		if sm == undefined then return undefined						-- 이 mesh는 skin이 없군
	 	modPanel.setCurrentObject sm									-- mesh의 modifier중에서 skin을 선택한다.
		if obj.numverts == 0 then return undefined						-- vertex가 없는데 뭘 어쩌라구?
		
		nBoneCount = SkinOps.GetNumberBones sm							-- 적용된 bone이 몇개지?
		nVertCount = SkinOps.GetNumberVertices sm						-- 이 skin에서 제어하는 vertex의 갯수는?
		if nVertCount == 0 then return undefined						-- 제어하는 vertex가 없는데 뭘 어쩌라구?
		
		ow.nBoneCount = nBoneCount
		for i = 1 to nVertCount do
		(
			nVertexWeightCount = SkinOps.GetVertexWeightCount sm i		-- vertex i에 적용된 weight(가중치)의 갯수
			local bwSet = #()
			for j = 1 to nVertexWeightCount do
			(
				nBoneID = SkinOps.GetVertexWeightBoneID sm i j			-- 어느 bone에서 가중치를 적용하고 있나? bone의 ID
				local strTemp = SkinOps.GetBoneName sm nBoneID 0		-- 가중치 적용중인 bone의 이름
				local wTemp = SkinOps.GetVertexWeight sm i j			-- vertex에 적용중인 bone의 가중치 값(0.0 ~ 1.0)
				local bw = BONE_WEIGHT 0 0
				bw.strName = strTemp
				bw.weight = wTemp
				append bwSet bw
			)
			append ow.VertexSet bwSet
		)
		ow
	),
		
	-- 정의 : Physique modifier로 구성된 vertex의 weight를 리턴한다.
	--        이 함수를 사용하기 위해서는 IPhysique.gup 플러그인이 필요하다.
	function GetVertexWeightsByPhysique obj = 
	( 
		ow = OBJECT_WEIGHT 0 #()
		if classof obj != Editable_mesh then return undefined			-- skin은 mesh에 붙는다.
		
		max modify mode													-- max를 modify mode로 변환
		pm = physiqueOps.getPhysiqueModifier obj 
		bones = physiqueOps.getBones obj modifier:pm
		nVertCount = physiqueOps.getVertexCount obj modifier:pm
		if bones != undefined then nBoneCount = bones.count
		else return undefined
		
		if nVertCount == 0 then return undefined						-- 제어하는 vertex가 없는데 뭘 어쩌라구?
		
		ow.nBoneCount = nBoneCount
		for i = 1 to nVertCount do
		( 
			nVertexWeightCount = physiqueOps.getVertexBoneCount obj i modifier:pm
			local bwSet = #()
			for j = 1 to nVertexWeightCount do 
			(
				local strTemp = (physiqueOps.getVertexBone obj i j modifier:pm).name
				local wTemp = (physiqueOps.getVertexWeight obj i j modifier:pm)
				local bw = BONE_WEIGHT 0 0
				bw.strName = strTemp
				bw.weight = wTemp
				append bwSet bw
			) 
			append ow.VertexSet bwSet
		) 
		ow
	),
	
	
	-- 정의 : materialID와 동일한 face들을 collect해서 리턴한다
	fn GetFacesByMaterial obj materialID =
	(
		faceSet = #()
		for i = 1 to obj.faces.count do
		(
			if (getfacematid obj i ) == materialID then
			(
				append faceSet i
			)
		)
		
		faceSet
	),
	
	-- 정의 : object를 동일한 face들끼리 묶어서 group화 한다.
	fn SplitFacesByMaterial obj =
	(
		fmSet = #()
		
--		if obj.material == undefined then return undefined

		if classOf obj.material == UndefinedClass then
		(
			local fm = MTRL_ID_FACE 0 #()
			fm.id = 0
			for i = 1 to obj.faces.count do ( append fm.faceSet i )
			append fmSet fm
		)
		
		if classOf obj.material == Standardmaterial then
		(
			local fm = MTRL_ID_FACE 0 #()
			fm.id = GetMaterialID obj.material
			for i = 1 to obj.faces.count do ( append fm.faceSet i )
			append fmSet fm
		)
		
		if classOf obj.material == Multimaterial then
		(
			for i = 1 to obj.material.count do
			(
				local fm = MTRL_ID_FACE 0 #()
				fm.id = GetMaterialID obj.material[i]
				fm.faceSet =  GetFacesByMaterial obj i
				if fm.faceSet.count != 0 then ( append fmSet fm )
			)
		)
		
		fmSet
	),
	
	-- 정의 : Biped나 IK사용시 키값을 추출하기 위해서 TM샘플링을 사용하고 있다.
	--        이때, snapshot으로 임시 오브젝트를 생성하여 TM값을 샘플링(Sampling or Dump)한다.
	fn DumpObjects obj =
	(
	    origbiped = #()
	    snapset = #()

		if obj == helper then ( select (GetObjectsBySuperClass obj) )
		else ( select (GetObjectsByClass obj) )
	    
	    selectionSets ["OrigBiped"] = selection
	
	    for i in selection do 
	    (
	        append origbiped i
	        b = snapshot i name:(i.name as string + "_snap")
	        b.parent = undefined
	        b.transform = i.transform
	        b.position.track = bezier_position()
	        b.rotation.track = tcb_rotation()
	        append snapset b
	    )
	    selectionSets ["Snapset"] = Snapset
	    
	    for i in 1 to snapset.count do
	    (
	        try
	        (
	            snapset[i].parent = execute ("$'" + origbiped[i].parent.name + "_snap'")
	        )
	        catch()
	    )
	    
		for i in 1 to Snapset.count do
		(
			--h = execute ("$" + selectionSets["Linkset"][i].name + "_Scrpt")
			snapset[i].position.track = bezier_position()
			snapset[i].rotation.track = tcb_rotation() --euler_xyz()
		)
		 
	    animate on
	    undo off
	    for t = animationRange.start to animationRange.end by g_nSampling do at time t
	    (
	        for i in 1 to Snapset.count do
	        (
	            snapset[i].transform = origbiped[i].transform
	        )
	    )
	    
	    snapset
	--	g_snapObjects = SnapSet
	),

	-- 정의 : 최초 스크립트를 초기화 한다.
	-- 설명 : 현재 scene의 object-id table과 material table을 만든다.
	fn Constructor =
	(
		CollectNames()	
		CollectMaterials()
		CollectBoneID()
	),
	
	fn Destructor = 
	(
		if $ != undefined then deselect $
		select $'NULL'
		delete $
	)
)

---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------

struct ZExport
(
	m_oUtil = 0,
	m_strFilename = 0,
	m_fileTarget = 0,
	m_strAttrName = #(),
	m_strAttrValue = #(),
	
	fn Constructor =
	(
		m_oUtil = ZUtility #() #()
		m_oUtil.Constructor()		-- 객체 초기와
		
		if m_strFilename == "debug" then
		(
			m_fileTarget = newScript()
		)
		else
		(
			format "Creating %...\n" m_strFilename
			m_fileTarget = createFile m_strFilename
		)
	),
	
	fn Destructor =
	(
		m_oUtil.Destructor()
		if m_strFilename != "debug" then
		( 
			close m_fileTarget
		)
	),

	fn StackClearAttr =
	(
		m_strAttrName = #()
		m_strAttrValue = #()
	),
	
	fn StackPushAttr vName vValue =
	(
		append m_strAttrName vName
		append m_strAttrValue vValue
	),
	
	fn XMLElementBegin nTabCount ElementName bCR =
	(
		local str = ""
		for i = 1 to nTabCount do ( str += "\t" )
		
		str += ("<" + ElementName)
		if m_strAttrName != undefined then
		(
			for i = 1 to m_strAttrName.count do
			(
				str += " "
				str += ( m_strAttrName[i] + "=" )
				str += ( "\"" + (m_strAttrValue[i] as string) + "\"" )
			)
		)
		if bCR == true then
		(
			str+=">\n"
		)
		else
		(
			str += ">"
		)
		
		format "%" str to:m_fileTarget
	),
	
	fn XMLElementEnd nTabCount ElementName =
	(
		local str = ""
		for i = 1 to nTabCount do
		(
			str += "\t"
		)
		str += ("</" + ElementName + ">\n")
		format "%" str to:m_fileTarget
	),
	
	fn WriteParent obj nTabCount =
	(
		StackClearAttr()
		StackPushAttr g_strID ((m_oUtil.GetObjectID obj.parent) - g_nObjectIDRef)
		if g_bObjectIDWithName then
		(
			if obj.parent != undefined then
			(
				StackPushAttr g_strName obj.parent.name
			)
			else
			(
				StackPushAttr g_strName "undefined"
			)
		)
		XMLElementBegin nTabCount g_strParent true
		XMLElementEnd nTabCount g_strParent
	),
	
	fn WriteTM obj nTabCount =
	(
		StackClearAttr()
		XMLElementBegin nTabCount g_strLocalTM true
		tm = m_oUtil.ConvertToD3D_TM (m_oUtil.GetLocalTM obj)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._11 tm._12 tm._13 tm._14 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._21 tm._22 tm._23 tm._24 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._31 tm._32 tm._33 tm._34 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._41 tm._42 tm._43 tm._44 to:m_fileTarget
			XMLElementEnd 0 g_strValue
		XMLElementEnd nTabCount g_strLocalTM
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strWorldTM true
		tm = m_oUtil.ConvertToD3D_TM (obj.transform)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._11 tm._12 tm._13 tm._14 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._21 tm._22 tm._23 tm._24 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._31 tm._32 tm._33 tm._34 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._41 tm._42 tm._43 tm._44 to:m_fileTarget
			XMLElementEnd 0 g_strValue
		XMLElementEnd nTabCount g_strWorldTM
	),

	fn WriteBoundingBox obj nTabCount =
	(
		StackClearAttr()
		XMLElementBegin nTabCount g_strBoundingBox true
		invTM = inverse (obj.transform)
			XMLElementBegin (nTabCount+1) g_strMax false
			format "%" (m_oUtil.ConvertToD3D_POS (obj.max * invTM)) to:m_fileTarget
			XMLElementEnd 0 g_strMax
			XMLElementBegin (nTabCount+1) g_strMin false
			format "%" (m_oUtil.ConvertToD3D_POS (obj.min * invTM)) to:m_fileTarget
			XMLElementEnd 0 g_strMin
			XMLElementBegin (nTabCount+1) g_strCenter false
			format "%" (m_oUtil.ConvertToD3D_POS (obj.center * invTM)) to:m_fileTarget
			XMLElementEnd 0 g_strCenter
		XMLElementEnd nTabCount g_strBoundingBox
	),
	
	fn WriteTriVertex obj nTabCount =
	(
		if classOf obj != Editable_mesh then return undefined
		vertSet = #()
		
		vertSet = m_oUtil.GetLocalVertices obj
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strTriVertex true
		for i = 1 to vertSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i - 1)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "%" (m_oUtil.ConvertToD3D_POS vertSet[i]) to:m_fileTarget
			XMLElementEnd 0 g_strValue
		)
		XMLElementEnd nTabCount g_strTriVertex
	),

	fn WriteVertexNormal obj nTabCount =
	(
		if classOf obj != Editable_mesh then return undefined
		vertSet = #()
		
		vertSet = m_oUtil.GetVertexNormals obj
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strVertexNormal true
		for i = 1 to vertSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i - 1)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "%" (m_oUtil.ConvertToD3D_POS vertSet[i]) to:m_fileTarget
			XMLElementEnd 0 g_strValue
		)
		XMLElementEnd nTabCount g_strVertexNormal
	),

	fn WriteTriIndex obj nTabCount =
	(
		if classOf obj != Editable_mesh then return undefined
		
		fmSet = m_oUtil.SplitFacesByMaterial obj
		if fmSet == undefined then return undefined
		
		StackClearAttr()
		StackPushAttr g_strMtrlCount fmSet.count
		XMLElementBegin nTabCount g_strTriIndex true
		for i = 1 to fmSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strMtrlID (fmSet[i].ID-1)
			for j = 1 to fmSet[i].faceSet.count do
			(
				XMLElementBegin (nTabCount+1) g_strValue false
				format "%" ( m_oUtil.ConvertToD3D_INDEX (getFace obj fmSet[i].faceSet[j]) ) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
		)
		XMLElementEnd nTabCount g_strTriIndex
	),
	
	fn WriteTexVertex obj nTabCount =
	(
		if classOf obj != Editable_mesh then return undefined
		if obj.numtverts == 0 do return undefined
		
		tvertCount = obj.numTVerts
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strTexVertex true
		for i = 1 to tvertCount do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i - 1)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "%" (m_oUtil.ConvertToD3D_UV (getTVert obj i)) to:m_fileTarget
			XMLElementEnd 0 g_strValue
		)
		XMLElementEnd nTabCount g_strTexVertex
	),
	
	fn WriteTexIndex obj nTabCount =
	(
		if classOf obj != Editable_mesh then return undefined
		if obj.numtverts == 0 then return undefined

		fmSet = m_oUtil.SplitFacesByMaterial obj
		StackClearAttr()
		StackPushAttr g_strMtrlCount fmSet.count
		XMLElementBegin nTabCount g_strTexIndex true
		for i = 1 to fmSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strMtrlID (fmSet[i].ID-1)
			for j = 1 to fmSet[i].faceSet.count do
			(
				XMLElementBegin (nTabCount+1) g_strValue false
				format "%" ( m_oUtil.ConvertToD3D_INDEX (getTVFace obj fmSet[i].faceSet[j]) ) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
		)
		XMLElementEnd nTabCount g_strTexIndex
	),
	
	fn WriteKey obj nTabCount =
	(
		if (not obj.pos.isAnimated) and (not obj.rotation.isAnimated) and (not obj.scale.isAnimated) then return undefined
		
		StackClearAttr()
		
		XMLElementBegin nTabCount g_strKey true
		
		if obj.pos.isAnimated then
		(
			obj.pos.controller = tcb_position()
			local keys = obj.pos.controller.keys
			StackClearAttr()
			XMLElementBegin (nTabCount+1) g_strPosition true
			for i = 1 to keys.count do
			(
				StackClearAttr()
				StackPushAttr g_strFrameNo keys[i].time
				XMLElementBegin (nTabCount+2) g_strValue false
				format "%" (m_oUtil.ConvertToD3D_POS keys[i].value) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strPosition
		)
		
		if obj.rotation.isAnimated then
		(
			obj.rotation.controller = tcb_rotation()
			local keys = obj.rotation.controller.keys
			StackClearAttr()
			local MultQuat = quat 0 0 0 1 -- identity quaternion
			XMLElementBegin (nTabCount+1) g_strRotation true
			for i = 1 to keys.count do
			(
				StackClearAttr()
				StackPushAttr g_strFrameNo keys[i].time
				XMLElementBegin (nTabCount+2) g_strValue false
				local k = keys[i].value
				if i == 1 then k = (quat 0 0 0 1)
				if g_bMultiplyQuaternion then
				(
					MultQuat = MultQuat * k
				)
				else
				(
					MultQuat = k
				)
				q = (m_oUtil.ConvertToD3D_QUAT (MultQuat as quat))
				format "[%,%,%,%]" q.x q.y q.z q.w to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strrotation
		)
		
		if obj.scale.isAnimated then
		(
			obj.scale.controller = tcb_scale()
			local keys = obj.scale.controller.keys
			StackClearAttr()
			XMLElementBegin (nTabCount+1) g_strScale true
			for i = 1 to keys.count do
			(
				StackClearAttr()
				StackPushAttr g_strFrameNo keys[i].time
				XMLElementBegin (nTabCount+2) g_strValue false
				format "%" (m_oUtil.ConvertToD3D_POS keys[i].value) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strScale
		)
		
		XMLElementEnd nTabCount g_strKey
	),
	
	fn WriteInfo nTabCount =
	(
		StackClearAttr()
		XMLElementBegin (nTabCount+1) g_strInfo true
			-- filename
			XMLElementBegin (nTabCount+2) g_strFilename false
			format "%" maxFileName to:m_fileTarget
			XMLElementEnd 0 g_strFilename
			-- ObjectCount
			XMLElementBegin (nTabCount+2) g_strObjectCount false
			format "%" objects.count to:m_fileTarget
			XMLElementEnd 0 g_strObjectCount
			-- MeshCount
			XMLElementBegin (nTabCount+2) g_strMeshCount false
			s = 0; for i = 1 to objects.count do ( if classOf objects[i] == Editable_mesh then s=s+1 )
			format "%" s to:m_fileTarget
			XMLElementEnd 0 g_strMeshCount
			-- Animation Start
			XMLElementBegin (nTabCount+2) g_strAniStart false
			format "%" animationRange.start to:m_fileTarget
			XMLElementEnd 0 g_strAniStart
			-- Animation End
			XMLElementBegin (nTabCount+2) g_strAniEnd false
			format "%" animationRange.end to:m_fileTarget
			XMLElementEnd 0 g_strAniEnd
			-- Animation Key type : KeyFrame, Sampling(ik,biped)
			XMLElementBegin (nTabCount+2) g_strTypeKey false
			format "%" g_strKeyType to:m_fileTarget
			XMLElementEnd 0 g_strTypeKey
			-- Object list
			StackClearAttr()
			XMLElementBegin (nTabCount+2) g_strObject true
			for i = 1 to m_oUtil.m_varSetObjectNames.count do
			(
				StackClearAttr()
				StackPushAttr g_strID (i - g_nObjectIDRef)
				XMLElementBegin (nTabCount+3) g_strValue false
				format "%" m_oUtil.m_varSetObjectNames[i] to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+2) g_strObject
			-- Bone list
			StackClearAttr()
			XMLElementBegin (nTabCount+2) g_strBone true
			for i = 1 to m_oUtil.m_varSetBoneNames.count do
			(
				StackClearAttr()
				StackPushAttr g_strBoneID (i-1)
				StackPushAttr g_strID (m_oUtil.GetObjectIDByName(m_oUtil.m_varSetBoneNames[i]) - g_nObjectIDRef)
				XMLElementBegin (nTabCount+3) g_strValue false
				format "%" m_oUtil.m_varSetBoneNames[i] to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+2) g_strBone

		XMLElementEnd (nTabCount+1) g_strInfo
	),
		
	fn WriteMaterial nTabCount =
	(
		StackClearAttr()
		XMLElementBegin (nTabCount+1) g_strMaterial true
		
		for i = 1 to m_oUtil.m_varSetMaterials.count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i-1)
			XMLElementBegin (nTabCount+2) g_strSlot true
			StackClearAttr()
			-- Diffuse
				XMLElementBegin (nTabCount+3) g_strMtrlDiffuse false
				format "%" m_oUtil.m_varSetMaterials[i].Diffuse to:m_fileTarget
				XMLElementEnd 0 g_strMtrlDiffuse
			-- Ambient
				XMLElementBegin (nTabCount+3) g_strMtrlAmbient false
				format "%" m_oUtil.m_varSetMaterials[i].Ambient to:m_fileTarget
				XMLElementEnd 0 g_strMtrlAmbient
			-- Specular
				XMLElementBegin (nTabCount+3) g_strMtrlSpecular false
				format "%" m_oUtil.m_varSetMaterials[i].Specular to:m_fileTarget
				XMLElementEnd 0 g_strMtrlSpecular
			-- Emissive
				XMLElementBegin (nTabCount+3) g_strMtrlEmissive false
				format "%" m_oUtil.m_varSetMaterials[i].selfIllumColor to:m_fileTarget
				XMLElementEnd 0 g_strMtrlEmissive
			-- Opacity
				XMLElementBegin (nTabCount+3) g_strMtrlOpacity false
				format "%" m_oUtil.m_varSetMaterials[i].Opacity to:m_fileTarget
				XMLElementEnd 0 g_strMtrlOpacity				
			-- Power
				XMLElementBegin (nTabCount+3) g_strMtrlPower false
				format "%" m_oUtil.m_varSetMaterials[i].SpecularLevel to:m_fileTarget
				XMLElementEnd 0 g_strMtrlPower
			-- Diffuse Map
				if m_oUtil.m_varSetMaterials[i].DiffuseMap != undefined then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapDiffuse false
					format "<![CDATA[%]]>" m_oUtil.m_varSetMaterials[i].DiffuseMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapDiffuse
				)
			-- Specular Map
				if m_oUtil.m_varSetMaterials[i].SpecularMap != undefined  then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapSpecualr false
					format "%" m_oUtil.m_varSetMaterials[i].SpecularMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapSpecualr
				)
			-- Bump Map
				if m_oUtil.m_varSetMaterials[i].BumpMap != undefined  then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapBump false
					format "%" m_oUtil.m_varSetMaterials[i].BumpMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapBump
				)
			-- Displacement Map
				if m_oUtil.m_varSetMaterials[i].DisplacementMap != undefined  then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapDisplace false
					format "%" m_oUtil.m_varSetMaterials[i].DisplacementMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapDisplace
				)
			XMLElementEnd (nTabCount+2) g_strSlot
		)
		
		XMLElementEnd (nTabCount+1) g_strMaterial
	),

	fn WriteVertexWeight obj nTabCount =
	(
		ret = undefined
		if obj.modifiers[#skin] != undefined then ret = m_oUtil.GetVertexWeightsBySkin obj
		if obj.modifiers[#physique] != undefined then ret = m_oUtil.GetVertexWeightsByPhysique obj
		if undefined == ret then return undefined
		
		StackClearAttr()
		StackPushAttr g_strBoneCount ret.nBoneCount
		XMLElementBegin nTabCount g_strVertexWeight true
		for i = 1 to ret.VertexSet.Count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i-1)
			XMLElementBegin (nTabCount+1) g_strTriVertex true
			vs = ret.VertexSet[i]
			mysort vs (fn compare v1 v2 = (v2.weight - v1.weight))
			for j = 1 to vs.count do
			(
				StackClearAttr()
				StackPushAttr g_strBoneID (m_oUtil.GetBoneIDByName vs[j].strName)
				if g_bObjectIDWithName then StackPushAttr g_strName vs[j].strName
				XMLElementBegin (nTabCount+2) g_strValue false
				format "%" vs[j].weight to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strTriVertex
		)		
		XMLElementEnd nTabCount g_strVertexWeight
	),
			
	fn WriteObject obj nTabCount =
	(
		if obj == undefined then return undefined
		StackClearAttr()
		StackPushAttr g_strID ((m_oUtil.GetObjectID obj) - g_nObjectIDRef)
		if g_bObjectIDWithName then StackPushAttr g_strName (obj.name)
		StackPushAttr g_strClass (classOf obj as string)
		XMLElementBegin nTabCount g_strObject true
			WriteParent obj (nTabCount+1)
			WriteTM obj (nTabCount+1)
			WriteBoundingBox obj (nTabCount+1)
			WriteTriVertex obj (nTabCount+1)
			WriteVertexNormal obj (nTabCount+1)
			WriteTriIndex obj (nTabCount+1)
			WriteTexVertex obj (nTabCount+1)
			WriteTexIndex obj (nTabCount+1)
			WriteVertexWeight obj (nTabCount+1)
			if g_bSampling then 
			(
				o = FindObject (obj.name + "_snap")
				if o != undefined then
				(
					format "%:%\n" obj.name o.name
					WriteKey o (nTabCount+1)
				)
				
			)
			else
			(
				WriteKey obj (nTabCount+1)
			)
		XMLElementEnd nTabCount g_strObject
	),

	fn Main =
	(
		StackClearAttr()
		format "<?xml version=\"1.0\" encoding=\"euc-kr\"?>\n" to:m_fileTarget
		XMLElementBegin 1 g_strBody true
		if g_bSampling then
		(
			m_oUtil.DumpObjects Biped_Object
			m_oUtil.DumpObjects BoneGeometry
			m_oUtil.DumpObjects Bone
			m_oUtil.DumpObjects helper
		)
			WriteInfo 1
			WriteMaterial 1
			for i = 1 to m_oUtil.m_varSetObjectNames.count do
			(
				g_uiObjectName.text = m_oUtil.m_varSetObjectNames[i]
				g_uiProgress.value = 100.*i/m_oUtil.m_varSetObjectNames.count
				WriteObject (FindObject m_oUtil.m_varSetObjectNames[i]) 2
			)
		if $ != undefined then deselect $
		select $'*snap'
		delete selection
		g_snapObjects  = undefined
		XMLElementEnd 1 g_strBody
	)
)

rollout ui "Properties" width:387 height:266
(
	local strFilename = "default.xml"
	
	checkbox chkObjectIDWithName "Object ID와 Obejct Name함께 출력" pos:[20,23] width:327 height:17
	GroupBox grp3 "출력형식" pos:[8,8] width:370 height:95
	checkbox chkMultiplyQuaternion "Quaternion값을 누적해서 출력" pos:[20,63] width:330 height:17 enabled:false
	edittext editPathName "" pos:[80,149] width:260 height:17 enabled:true
	button btnPathName "..." pos:[342,149] width:24 height:17
	button btnRun "실행" pos:[151,228] width:77 height:30
	label lbl2 "newtype@chollian.net" pos:[254,237] width:107 height:17
	checkbox chkWriteToDebug "Debug창에 출력" pos:[20,43] width:327 height:17
	label lbl4 "출력파일명:" pos:[19,150] width:63 height:17
	checkbox chkSampling "애니메이션 샘플링(Biped 혹은 Bone IK사용시 반드시 체크)" pos:[20,84] width:352 height:17 enabled:true
	progressBar pb1 "" pos:[9,207] width:369 height:16
	label lbl17 "처리중인 object :" pos:[10,186] width:87 height:16
	label lblObjectName "" pos:[100,185] width:275 height:15
	spinner spnSamplingGap "" pos:[83,126] width:49 height:16 enabled:false range:[1,100,0] type:#integer scale:1 value:1
	label lbl39 "샘플링간격:" pos:[19,127] width:63 height:17
	GroupBox grp4 "특성값" pos:[8,111] width:370 height:69
	
	on chkObjectIDWithName changed state do
	(
		g_bObjectIDWithName = state
	)
	on chkMultiplyQuaternion changed state do
	(
		g_bMultiplyQuaternion = state
	)
	on btnPathName pressed do
	(
	    temp = getSaveFileName filename:strFilename types:"XML(*.xml)|*.xml|All|*.*|"
	    if temp != undefined then editPathName.text = temp
	)
	on btnRun pressed do
	(
		g_uiObjectName = lblObjectName
		g_uiProgress = pb1
		if spnSamplingGap.value < 1 then spnSamplingGap.value = 1
		g_nSampling = spnSamplingGap.value
		if editPathName.text == "" then editPathName.text = "default.xml"
	    strFilename = editPathName.text
		oExport = ZExport 0 strFilename 0 #() #()
		oExport.Constructor()						-- 생성자. 반드시 호출해줘야 한다.
		oExport.Main()								-- 메인함수.
		oExport.Destructor()						-- 소멸자. 반드시 호출해줘야 한다.
		gc()
	)
	on chkWriteToDebug changed state do
	(
		if state then
		(
			editPathName.text = "debug"
			editPathName.enabled = false
			btnPathName.enabled = false
		)
		else
		(
			editPathName.enabled = true
			btnPathName.enabled = true
		)
	)
	on chkSampling changed state do
	(
		g_bSampling = state
		spnSamplingGap.enabled = state
		if g_bSampling then
		(
			g_strKeyType = "Sampling"
		)
		else
		(
			g_strKeyType = "Keyframe"
		)
	
	)
)
MainUI = newRolloutFloater "MAX to XML" 400 300
addrollout ui MainUI
