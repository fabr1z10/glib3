engine = {
    device_size = { 320, 200 },
    window_size = { 800, 600 },
    title = "King's quest I",
    collision = true,
    collision_size={40, 40}
}

fonts = {
    { name = "ui", file  = "fonts/sierra1.ttf" },
    --{ name = "monkey", file  = "fonts/MonkeyIsland-1990.ttf" }
}

require("script")
require("sprites")
require("funcs")


variables = {
    _room = "001",
	status = 0,
pause = false
}

