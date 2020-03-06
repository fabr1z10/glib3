--package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
	device_size = { 320, 200 },
	window_size = { 640, 400 },
	title = 'Maniac Mansion',
	lang = "eng",
	config = {
	    default_verb = 'walk',
	    font_size = 8,
	   	ui = {
			height = 56,
	    	verb_unselected_color = { 0, 170, 0, 255},
	    	verb_selected_color = {255, 255, 85, 255},
	    	currentaction_color ={0, 170, 170, 255},
			inv_unselected = {170, 0, 170, 255},
			inv_selected = {255, 85, 255, 255},
			font = "ui"
		},
		dialogue_font = 'ui'
	}
}

-- assets
engine.assets = {
	fonts = {
		ui = { type = "font", file = "./fonts/monkeysmall.ttf" },
	},
	models = {},
}

engine.global_assets = {
	fonts = { "ui" }
},

require ("scumm")

-- load strings
require ("text/" .. engine.lang .. "/text")

-- load game specific function
require ("./funcs")

-- the verbs for the game. You might have multiple sets here! Watch out
engine.config.verbs = {
 	open = { code="open", text = strings.ui.open, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[1]}) },
    close = { code="close", text = strings.ui.close, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    push = { code="push", text = strings.ui.push, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[3]}) },
    pull = { code="pull", text = strings.ui.pull, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[3]}) },
    walk = { code="walk", text = strings.ui.walkto, objects = 1, callback = scumm.func.default_handler },
    pick = { code="pickup", text = strings.ui.pickup, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[5]}) },
    talk = { code="talk", text = strings.ui.talkto, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    give = { code="give", text = strings.ui.give, objects = 2, prep = strings.ui.giveprep },
    use = { code="use", text = strings.ui.use, objects = 2, callback = scumm.func.d2_handler, prep= strings.ui.useprep, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    look = { code="look", text = strings.ui.lookat, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[4]}) },
    turnon = { code="turnon", text = strings.ui.turnon, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    turnoff = { code="turnoff", text = strings.ui.turnoff, objects = 1, callback = scumm.func.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
	newkid = { code="newkid", text = strings.ui.newkid, objects = 0, callback = newkid }
}

engine.config.verbset = {
    [1] = { "open", "close", "push", "pull", "walk", "pick", "newkid", "give", "use", "look", "turnon", "turnoff" }
}

variables = {
	-- game status
	frontdoor_open = false,
	cellar_door_open = false,
	doormat_pulled = false,
	frontdoor_key_taken = false,
	frontdoor_bush_removed = false,
	frontdoor_flag_up = false,
	cellar_light_on = false,
	fusebox_open = false
}



-- load items
glib.load_folder ('items')

-- load sprites
glib.load_folder ('sprites')

require('states')

-- initialize player position and initial room
states.start ()