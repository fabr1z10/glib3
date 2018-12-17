require("template/room1")

local roomInfo = {
	width = 320,
	height = 144,
	startTable = {
		village3 = { pos = items["shop.door"].walk_to, facing = "east"},
	},
	defaultroom = "village3",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites["shop.door"])
room:add_asset(sprites["shop.shopkeeper"])
room:add_asset(sprites["shop.sword"])
room:add_asset(sprites["shop.shovel"])
room:add_asset(sprites["shop.sign"])
room:add_asset(sprites["shop.bell"])

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/shop.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
	                290,2,290,20,320,20,320,0,62,0}
	            },
			}
      	}
	},
	factory.object.create { object = "shop.door" },
	factory.object.create { object = "shop.shopkeeper" },
	factory.object.create { object = "shop.sword" },
	factory.object.create { object = "shop.shovel" },
})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	local d = strings.shop
	local s = script:new("shopkeeper")
	s.actions = {
		action.say { id=1, actor="shop.shopkeeper", lines = {d[1]} },
		action.delay { id=2, sec=5},
		action.say { id=3, actor="shop.shopkeeper", lines = {d[10]} },
		action.delay { id=4, sec=5},
		action.say { id=5, actor="shop.shopkeeper", lines = {d[5]} },
		action.delay { id=6, sec=5},
		action.say { id=7, actor="shop.shopkeeper", lines = {d[4]} },
		action.delay { id=8, sec=5},
		action.say { id=9, actor="shop.shopkeeper", lines = {d[3]} },
		action.delay { id=10, sec=5},
		action.say { id=11, actor="shop.shopkeeper", lines = {d[2]} },
	}
	s.loop = 2
	monkey.play(s)
end


