package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

--require("test")

engine = {
	device_size = { 320, 200 },
	window_size = { 320, 200 },
	title = "King's quest V",
	shaders = { "unlit_textured", "unlit_color", "text" }
}

fonts = {
    ui = {file  = "./fonts/monkeysmall.ttf" },
    monkey = {file  = "./fonts/MonkeyIsland-1990.ttf"}
}

-- this is configuration for scumm
config = {
	start_room = "room1",
	lang = "eng",
    default_verb = "walk",
}

--require ("text/" .. config.lang .."/text")

variables = {
    verbs = {
        [1] = { mnemonic = "use", anim = "hand" },
        [2] = { mnemonic = "talk", anim ="talk" },
        [3] = { mnemonic = "walk", anim ="walk" },
        [4] = { mnemonic = "look", anim = "look"}
    },
    currentverb = 1,
    inventory = { 	}
}

require ("scumm")

global_assets = {
	fonts = { "ui", "monkey" }
}

items = {}
spritesheets = {}
models = {}
dialogues = {}
-- sprites = {}

glib.load_folder("sprites")
--glib.load_folder("factories")
glib.load_folder("items")
--glib.load_folder("dialogues")

--require("defaultscripts")

--test.scummbar()
variables._room = "room1"

