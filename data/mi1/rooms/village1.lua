require("template/room1")

roomDefinition = {
	width = 1008,
	height = 144,
	startTable = {
		--lookout = { pos = items2["village1.cliffside"].hotspot.walk_to, facing = "east"},
		scummbar = { pos = items2["village1.door"].hotspot.walk_to, dir = "south"},
		village2 = { pos = items2["village1.archway"].hotspot.walk_to, dir="west"}
	},
	defaultroom = "lookout",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = generateBasicRoom (roomDefinition)


room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village1_1.png" }}},
	{ pos = {73, 0, 1}, components = { { type="gfx", image="gfx/village1_2.png" }}},
	{ pos = {229, 0, 1}, components = { { type="gfx", image="gfx/village1_3.png" }}},
	{ pos = {606, 0, 1}, components = { { type="gfx", image="gfx/village1_4.png" }}},
	factory.walkarea { shape = { type = "graph", 
		vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {770, 13}, {780,34}, {1000,34} }, 
		edges = { {0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7},{7,8} }}},
	factory.objc { id="village1.archway" },
	factory.objc { id="village1.cliffside" },
	factory.objc { id="village1.door" },
	factory.objc { id="village1.poster" },


	--factory.object.create { object = "village1.cliffside" },
	--factory.object.create { object = "village1.door" },
	--factory.object.create { object = "village1.poster" },
	--factory.object.create { object = "village1.archway" },
})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


