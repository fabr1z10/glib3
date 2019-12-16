package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
    device_size = { 256, 224 },
    window_size = { 256, 224 },
    lang = "eng",
	tilesize = 16,
	dt = 0.1,
    title = "Bubble Bobble",
    paused = false,
    assets = {
		bones = {},
		characters = {},
    	fonts = {
	    	diag = { file  = "./fonts/arial.ttf" },
			main = { file  = "./fonts/prstartk.ttf" }
		},
		models = {},
		animations = {}
    },
   	start_room = "01",
    global_assets = {
		fonts = { "diag" }
	},
	shaders = { "unlit_textured", "unlit_color", "text" }

}

require("platformer")

variables = {
    --_room = "world1_1",
	jump_height = 160,
	time_to_jump_apex = 0.5,
	world_name = "",
	score = 0,
	time = 400,
	coins = 0,
	energy = 3,
	player = nil,
	collision = {
		flags = {
			player = 1,
			platform = 2,
			foe = 4,
			player_attack = 8,
			foe_attack = 16,
			platform_passthrough = 32

		},
		tags = {
			player = 1,
			player_attack = 2,
			brick_sensor = 3,
			bonus_brick_sensor = 4,
			bonus = 5,
			basicfoe = 6,
			pickupitem = 7,
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

spritesheets = {}
models = {}

--glib.load_folder_r("models")

require("custom")

