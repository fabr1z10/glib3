engine = {
	device_size = { 320, 200 },
	window_size = { 640, 400 },
	title = "Test",
	shaders = { "unlit_textured", "unlit_color", "text" },
	assets = {
		fonts = {
	    	main = {type ="font", file  = "./fonts/prstartk.ttf" },
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



