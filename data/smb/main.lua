	package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
    device_size = { 256, 256 },
    window_size = { 256, 256 },
    lang = "eng",
	tilesize = 16,
	dt = 0.1,
    title = "Super Mario Bros",
    assets = {
    	fonts = {
	    	diag = { file  = "./fonts/arial.ttf" },
			main = { file  = "./fonts/prstartk.ttf" }
		},
		models = {},
		animations = {}
    },
   	start_room = "world1_1",
    global_assets = {
		fonts = { "diag" }
	},
	shaders = { "unlit_textured", "unlit_color", "text" }

}
require("platformer")


variables = {
    --_room = "world1_1",
	state = 1,
	jump_height = 160,
	time_to_jump_apex = 0.5,
	world_name = "",
	score = 0,
	time = 400,
	coins = 0,
	can_fire = false,
	cut_scene_done = true,
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
			mushroom = 11,
			goomba = 12,
			koopa = 13,
			moving_platform =14,
			coin = 15,
			spawn = 16,
			mushroom1up = 17,
			starman = 18,
			warp = 19,
			brick_sensor = 20,			
			bonus_brick_sensor = 21,
			hotspot = 22,
			flower = 23,
			fire = 24,
			plant = 25
		}
	},
	tags = {

		basic_brick = 10,
		mushroom = 11,
		bonus_brick = 12,
		mushroom1up = 13,
		goomba = 14,
		koopa = 15

	}
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

-- sprites = {}
-- require("factories/rect")
-- require("factories/bricks")
-- require("factories/bonusbrick")
-- require("factories/basicbrick")
-- require("factories/foe")
-- require("factories/mushroom")
-- require("factories/mario")
-- require("factories/goomba")

--require("factories/actions")
require("script/mario")

