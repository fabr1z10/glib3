engine = {
	device_size = { 320, 200 },
	window_size = { 640, 400 },
	title = "Test Physics",
	shaders = { "light_color", "light_textured", "text" },
	assets = {
		fonts = {
	    	main = {type ="font", file  = "./fonts/arial.ttf" },
		},
		models = {},
		animations = {}
	},
	global_assets = {
		fonts = { "main" }
	},
	start_room = "01",
	lang = "eng",
}

require("glib")
glib.load_folder ('models')


