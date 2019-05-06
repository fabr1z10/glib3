package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
    device_size = { 256, 256 },
    window_size = { 256, 256 },
    lang = "eng",
	--tilesize = 16,
    title = "Super Mario Bros",
    assets = {
    	fonts = {
	    	diag = { file  = "./fonts/arial.ttf" }
		},
		models = {}
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
	jump_height = 80,
	time_to_jump_apex = 0.5,
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

factory = {}
spritesheets = {}
models = {}
action={}
-- sprites = {}
require("factories/rect")
require("factories/bricks")
require("factories/bonusbrick")
require("factories/foe")
require("factories/actions")

