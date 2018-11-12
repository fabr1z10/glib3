-- Super Mario World
require ("strings")
require ("sprites")
require ("funcs")
require ("script")

engine = {
    device_size = { 256, 224 },
    window_size = { 512, 448 },
    title = "Super Mario World",
}

fonts = {
    { name = "diag", file  = "fonts/arial.ttf" }
}



variables = {
    _room = "world1_1",
	advice = false
}

