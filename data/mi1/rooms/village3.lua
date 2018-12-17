require("template/room1")

local roomInfo = {
	width = 800,
	height = 144,
	startTable = {
		village2 = { pos = items["village3.archway"].walk_to, facing = "west"},
		shop = { pos = items["village3.shop_door"].walk_to, facing="south"}
	},
	defaultroom = "village2",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="constant", value=0.3 }
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites["village3.shop_door"])

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/village3_1.png" }}},
    { pos = {166, 0, 2}, components = {{type="gfx", image="gfx/village3_2.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {406,49,425,49,436,63,494,63,494,42,594,42,594,71,600,71,638,23,745,23,752,17,770,17,770,10,762,10,775,0,374,0,396,22}
	            },
			}
      	}
	},
	factory.object.create { object = "village3.archway" },
	factory.object.create { object = "village3.shop_door" },


})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


