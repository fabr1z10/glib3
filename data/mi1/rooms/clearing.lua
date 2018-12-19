require("template/room1")

local roomInfo = {
	width = 496,
	height = 144,
	startTable = {
		meleemap = { pos = items["clearing.path"].walk_to, facing = "west"},
		circus = { pos = items["clearing.tent"].walk_to, facing = "south"},
	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
   		{ pos = {0, 0}, size={229, 144}, type="constant", value = 0.2},
   		{ pos = {229,31}, size={85, 144}, type="constant", type="linear_x", values={229,0.2,314,1.0}},
 		{ pos = {314,0}, size={200, 144}, type="constant", type="constant", value=1.0},
		{ pos = {283,0}, size={100, 32}, type="constant", type="constant", value=1.0},
	}}	
}

room = generateBasicRoom (roomInfo)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/clearing1.png" }}},
	{ pos = {441, 0, 2}, components = { { type="gfx", image="gfx/clearing2.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = { type = "poly", outline = {496,38,496,0, 283, 0, 283, 20, 315, 28,315, 44, 229, 31, 92, 31, 41, 64,54, 75, 80, 64, 115, 58, 119, 48,
					165, 53, 180,64, 214, 64, 229, 33, 315, 46, 400,38}},
			}
      	}
	},
 	factory.object.create { object = "clearing.path"},
	factory.object.create { object = "clearing.tent" },

})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


