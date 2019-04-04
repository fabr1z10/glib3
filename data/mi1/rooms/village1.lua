roomDefinition = {
	width = 1008,
	height = 144,
	startTable = {
		--lookout = { pos = items2["village1.cliffside"].hotspot.walk_to, facing = "east"},
		scummbar = { pos = items["village1.door"].hotspot.walk_to, dir = "south"},
		village2 = { pos = items["village1.archway"].hotspot.walk_to, dir="west"},
		lookout = { pos = items["village1.cliffside"].hotspot.walk_to, dir="east"}
	},
	defaultroom = "lookout",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = scumm.factory.basic_room (roomDefinition)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village1_1.png" }}},
	{ pos = {73, 0, 1}, components = { { type="gfx", image="gfx/village1_2.png" }}},
	{ pos = {229, 0, 1}, components = { { type="gfx", image="gfx/village1_3.png" }}},
	{ pos = {606, 0, 1}, components = { { type="gfx", image="gfx/village1_4.png" }}},
	scumm.factory.walkarea { shape = { type = "graph", 
		vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {770, 13}, {780,34}, {1000,34} }, 
		edges = { {0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7},{7,8} }}},
	scumm.factory.object { id="village1.archway" },
	scumm.factory.object { id="village1.cliffside" },
	scumm.factory.object { id="village1.door" },
	scumm.factory.object { id="village1.poster" },
})

local entry_cutscene = function() 
	local proom = variables._previousRoom or roomDefinition.defaultroom
	if (proom == "lookout") then
		local actions = {
			{ type = scumm.action.walkto, args = {tag="player", pos = {230, 0}}}
		}
		local s = script.make(actions)
		s.name = "_walk"
		monkey.play(s)
	end
end

table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { pos = {781, 34, 0}, walkto = { items["village1.cliffside"].hotspot.walk_to }}))
table.insert(room.initstuff, entry_cutscene)