package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path


engine = {
	device_size = { 320, 200 },
	window_size = { 320, 200 },
	title = "Maniac Mansion",
	shaders = { "unlit_textured", "unlit_color", "text" },
	assets = {
		fonts = {
	    	ui = {file  = "./fonts/monkeysmall.ttf" },
    		monkey = {file  = "./fonts/MonkeyIsland-1990.ttf"}
		},
		models = {}
	},
	global_assets = {
		fonts = { "ui", "monkey" }
	},
	start_room = "frontdoor",
	lang = "eng",
	config = {
	    default_verb = "walk",
		style = "scumm",
	   	ui = {
			height = 56,
	    	verb_unselected_color = { 0, 170, 0, 255},
	    	verb_selected_color = {255, 255, 85, 255},
	    	currentaction_color ={0, 170, 170, 255},
			inv_unselected = {170, 0, 170, 255},
			inv_selected = {255, 85, 255, 255},
			font = "ui"
		}     	
	}
}

require("scumm")
--engine.state.scumm.inventory["kitchen.fish"] = 1
-- the verbs for the game. You might have multiple sets here! Watch out
engine.config.verbs = {
 	push = { code="push", text = strings.ui.push, objects = 1 },
    pull = { code="pull", text = strings.ui.pull, objects = 1 },
    give = { code="give", text = strings.ui.give, objects = 2, prep = strings.ui.giveprep },
    open = { code="open", text = strings.ui.open, objects = 1 },
    close = { code="close", text = strings.ui.close, objects = 1 },
    read = { code="read", text = strings.ui.read, objects = 1 },
    walk = { code="walk", text = strings.ui.walk, objects = 1 },
    pick = { code="pick", text = strings.ui.pick, objects = 2, prep = strings.ui.giveprep },
    use = { code="use", text = strings.ui.use, objects = 2, prep = strings.ui.useprep },
    turnon = { code="turnon", text = strings.ui.turnon, objects = 1 },
    turnoff = { code="turnoff", text = strings.ui.turnoff, objects = 1 },
    fix = { code="fix", text = strings.ui.fix, objects = 1 }

}
engine.config.verbset = {
    [1] = { "push","pull","give","open", "close", "read", "walk", "pick", "use", "turnon", "turnoff", "fix" }
    
}

variables = {

	inventory ={}
}









-- -- this stuff will change at gametime

-- -- DEBUG STUFF

-- -- END DEBUG

--require ("script")
--require ("funcs2")


-- -- load room specific scripts
-- scripts = {}
-- items = {}
-- spritesheets = {}
-- models = {}
-- dialogues = {}
-- sprites = {}


--glib.load_folder("dialogues")

require("defaultscripts")


--test.lookout()

--print (config.start_room)