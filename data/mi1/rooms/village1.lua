require("template/room1")

local startPosTable = {
	lookout = { pos = items.village1.cliffside.walk_to, facing = "west"},
}

room = generateBasicRoom { width = 1008, height = 144, startTable = startPosTable, defaultroom = "lookout"}

room:add_asset(sprites.door_village_scummbar)

room:add( {
	{ pos = {0,0,-3}, components = { { type="gfx", image="gfx/village1_1.png" }}},
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
	factory.object.create { object = items.village1.cliffside },
	factory.object.create { object = items.village1.door },

})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


