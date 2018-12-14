require("template/room1")

local roomInfo = {
	width = 1008,
	height = 144,
	startTable = {
		lookout = { pos = items["village1.cliffside"].walk_to, facing = "east"},
		scummbar = { pos = items["village1.door"].walk_to, facing = "south"},
		village2 = { pos = items["village1.archway"].walk_to, facing="west"}
	},
	defaultroom = "lookout",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites.door_village_scummbar)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village1_1.png" }}},
	{ pos = {73, 0, 1}, components = { { type="gfx", image="gfx/village1_2.png" }}},
	{ pos = {229, 0, 1}, components = { { type="gfx", image="gfx/village1_3.png" }}},
	{ pos = {606, 0, 1}, components = { { type="gfx", image="gfx/village1_4.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = { type = "graph", vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {770, 13}, {780,34}, {1000,34} }, edges = { 
					{0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7},{7,8} }},
			}
      	}
	},
	factory.object.create { object = "village1.cliffside" },
	factory.object.create { object = "village1.door" },
	factory.object.create { object = "village1.poster" },
	factory.object.create { object = "village1.archway" },
})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


