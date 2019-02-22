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
}

factory = {}

require("factories/rect")
