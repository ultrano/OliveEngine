-- kTestSelect = selection as array;
-- kTestSelect = kTestSelect[1]
-- kTestSelect.pos.controller
-- kTestSelect.rotation.controller
-- kTestSelect.scale.controller
-- animationrange = interval 0 100
-- at time 0 kTestSelect.pos.controller.x_position = 100

-- at time 100 kTestSelect.pos.controller.x_position= 2000
-- controller test bed 1

b=box height:10

at time 5 animate on b.height=50

at time 10 animate on b.height=100

bhc=b.height.controller

bhk=bhc.keys

supportstimeoperations bhc

deletetime bhc 4 5

bhk

deletetime bhc 4 5 #incLeft

bhk

deletetime bhc 1 4 #noslide

bhk

at time 5 animate on b.height=50

deletetime bhc (interval 5 8) #incLeft

bhk

at time 10 animate on b.height=150

for k in bhk do format "%:%\n" k.time k.value

reversetime bhc 5 15 #incLeft #incRight

for k in bhk do format "%:%\n" k.time k.value

insertTime bhc 12 5

bhk

getTimeRange bhc

