local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	font_size = 8,
	defaultroom = "lookout",
	walkareas = { "gate.walkarea"},
	collide= true,
	id ='1'
}

room = scumm.factory.dynamic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="start.png" }}},
		{ pos = {0,0,3}, components = { { type="gfx", image="start1.png" }}},
		scumm.factory.object { id = 'gate.sign'},
		scumm.factory.object { id = 'gate.path'}

	}
)

print ("...")
print (room.scene[1].type)
print (#room.scene[1].children)

print (room.scene[1].children[1].model)
print (room.scene[1].children[1].pos[1])
print (room.scene[1].children[1].pos[2])