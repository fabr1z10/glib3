require("template/room1")

local roomInfo = {
	width = 320,
	height = 144,
	startTable = {
		scummbar = { pos = items["kitchen.door"].walk_to, facing = "east"},
	},
	defaultroom = "scummbar",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true
}

room = generateBasicRoom (roomInfo)

table.insert (room.engines, 
	{ 
		type = "collision", 
		size = {128, 128}, 
		response = {
			{ tag = {1, 2}, onenter=nil }
		}
	}
)

room:add_asset(sprites.kitchen_table)
room:add_asset(sprites.door_kitchen)
room:add_asset(sprites.door_kitchen_pier)
room:add_asset(sprites.potostew)
room:add_asset(sprites.kitchen_pot)
room:add_asset(sprites.kitchen_meat)
room:add_asset(sprites.kitchen_fish)


room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/kitchen.png" }}},
	factory.object.create { object = "kitchen.door" },
	factory.object.create { object = "kitchen.door_pier" },
	factory.object.create { object = "kitchen.table" },
	factory.object.create { object = "kitchen.potostew" },
	factory.object.create { object = "kitchen.pot" },
	factory.object.create { object = "kitchen.meat" },
	factory.object.create { object = "kitchen.fish" },
	factory.walkarea.create {
    	shape = { type = "poly", outline = {40,16,59,21,155,21,180,18,192,18,294,18,307,12,199,9,207,0,160,0,149,11,112,11,100,0,40,0}},
		blockedlines = {
			{ A = {194, 0}, B = {194, 144}, active =true },
			{ A = {206, 0}, B = {206, 144}, active =true },
		},
	}
})



function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


