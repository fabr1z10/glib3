local items = engine.items

roomDefinition = {
	width = 1008,
	height = 144,
	startTable = {
		--lookout = { pos = items2["village1.cliffside"].hotspot.walk_to, facing = "east"},
		scummbar = {  walkarea = "village1.walkarea", pos = items["village1.door"].hotspot.walk_to, dir = "south"},
		village2 = {  walkarea = "village1.walkarea", pos = items["village1.archway"].hotspot.walk_to, dir="west"},
		lookout = {  walkarea = "village1.walkarea", pos = items["village1.cliffside"].hotspot.walk_to, dir="south"}
	},
	font_size = 8,
	playerid="guybrush",
	defaultroom = "lookout",
	walkareas = { "village1.walkarea"},
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	
}

room = scumm.factory.basic_room (roomDefinition)
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
 	if (proom == "lookout") then
		local actions = scumm.ui.walk { pos = {230, 0} }
		local s = script.make(actions)
		s.name="_walk"
		monkey.play(s)
 	end
end

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { pos = {781, 34, 0}, walkto = { items["village1.cliffside"].hotspot.walk_to }}))
table.insert(room.initstuff, entry_cutscene)
