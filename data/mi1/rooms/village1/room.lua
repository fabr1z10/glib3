local items = engine.items

roomDefinition = {
	width = 1008,
	height = 144,
	walkareas = { "village1.walkarea"},
	collide= true,
	id = 'village1'
}

room = scumm.factory.room_ui (roomDefinition)
room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="village1_1.png" }}},
		{ pos = {73, 0, 1}, components = { { type="gfx", image="village1_2.png" }}},
		{ pos = {229, 0, 1}, components = { { type="gfx", image="village1_3.png" }}},
		{ pos = {606, 0, 1}, components = { { type="gfx", image="village1_4.png" }}},
		scumm.factory.object { id="village1.archway" },
		scumm.factory.object { id="village1.cliffside" },
		scumm.factory.object { id="village1.door" },
		scumm.factory.object { id="village1.poster" },
	}
)

local entry_cutscene = function() 
 	local proom = engine.state.previousRoom
 	if (proom == "") then proom = roomDefinition.defaultroom end
 	if (proom == "lookout" or proom == 'meleemap') then
		local actions = {
			{ type = scumm.action.walkto, args = { tag="player", pos = {230, 0} }}
		}
		local s = script.make(actions)
		s.name="_walk"
		monkey.play(s)
 	end
end

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { pos = {781, 34, 0}, walkto = { items["village1.cliffside"].hotspot.walk_to }}))
table.insert(room.initstuff, entry_cutscene)

table.insert(
	room.initstuff, 
	glib.curry (mi.addStorekeeper, { 
		from = 'village2', 
		pos = {781, 34}, 
		dir = 'w', 
		parent = 'village1.walkarea',
		walkto = { mi.rooms.village1.to_lookout } 
	})) 

