require ("sprites")
require ("funcs")
require ("script")

engine = {
    device_size = { 256, 256 },
    window_size = { 256, 256 },
	tilesize = 16,
    title = "Super Mario Bros",
	shaders = { "unlit_textured", "unlit_color", "text" }

}

fonts = {
    diag = { file  = "./fonts/arial.ttf" }
}

global_assets = {
	fonts = { "diag" }
}


variables = {
    _room = "world1_1",
	jump_height = 80,
	time_to_jump_apex = 0.5
}

variables.gravity = -(2.0 * variables.jump_height) / (variables.time_to_jump_apex * variables.time_to_jump_apex)
variables.jump_velocity = math.abs(variables.gravity) * variables.time_to_jump_apex

factory = {}
spritesheets = {}
models = {}

-- sprites = {}
require("factories/rect")
require("sprites/smbs")
require("sprites/smbd")