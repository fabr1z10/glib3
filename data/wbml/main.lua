-- place here the path to the lualib folder
package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
    device_size = { 256, 256 },
    window_size = { 256, 256 },
    lang = "eng",
	tilesize = 16,
	dt = 0.1,
    title = "Hello world!",
    assets = {
    	fonts = {
	    	--diag = { file  = "./fonts/arial.ttf" },
			--main = { file  = "./fonts/prstartk.ttf" }
		},
		models = {},
		animations = {}
    },
   	start_room = "start_room",
    global_assets = {
		--fonts = { "diag" }
	},
	shaders = { "unlit_textured", "unlit_color", "text" }
}

require("platformer")

variables = {
	jump_height = 160,
	time_to_jump_apex = 0.5,
	collision = {
		flags = {
			player = 1,
			platform = 2,
			foe = 4,
			player_attack = 8,
			foe_attack = 16,
		},
		tags = {
			player = 1,
		}
	},
}

variables.collider = { 
	type = "collision", 
	size = {128, 128}, 
	response = {}
}


variables.gravity = -(2.0 * variables.jump_height) / (variables.time_to_jump_apex * variables.time_to_jump_apex)
variables.jump_velocity = math.abs(variables.gravity) * variables.time_to_jump_apex

require("script/custom")

