--package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
	device_size = { 320, 200 },
	window_size = { 640, 400 },
	title = "Maniac Mansion",
	shaders = { "unlit_textured", "unlit_color", "text" },
	global_assets = {
		fonts = { "ui" }
	},
	start_room = "1",
	lang = "eng",
	config = {
	    default_verb = "walk",
	    font_size = 8,
		style = "scumm",
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

require ("sc2")
require ("text/" .. engine.lang .. "/text")

-- the verbs for the game. You might have multiple sets here! Watch out
engine.config.verbs = {
 	open = { code="open", text = strings.ui.open, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[1]}) },
    close = { code="close", text = strings.ui.close, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    push = { code="push", text = strings.ui.push, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[3]}) },
    pull = { code="pull", text = strings.ui.pull, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[3]}) },
    walk = { code="walk", text = strings.ui.walkto, objects = 1, callback = scumm.script.default_handler },
    pick = { code="pickup", text = strings.ui.pickup, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[5]}) },
    talk = { code="talk", text = strings.ui.talkto, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    give = { code="give", text = strings.ui.give, objects = 2, prep = strings.ui.giveprep },
    use = { code="use", text = strings.ui.use, objects = 2, prep= strings.ui.useprep },
    look = { code="look", text = strings.ui.lookat, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[4]}) },
    turnon = { code="turnon", text = strings.ui.turnon, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) },
    turnoff = { code="turnoff", text = strings.ui.turnoff, objects = 1, callback = scumm.script.default_handler, def = glib.curry(scumm.script.say, {strings.defaultactions[2]}) }
}

engine.config.verbset = {
    [1] = { "open", "close", "push", "pull", "walk", "pick", "talk", "give", "use", "look", "turnon", "turnoff" }
}


variables = {
	current_player = 'dave_1',
	dynamic_items = {},
	players = { 'dave_1', 'dave_2', 'dave_3' },
	-- require one inventory for each player, do this dynamically!
	inventory = {
		dave_1 = {},
		dave_2 = {},
		dave_3 = {},
	},
	-- game status
	frontdoor_open = false,
	doormat_pulled = false,
	frontdoor_key_taken = false,
	frontdoor_bush_removed = false
}

variables.dynamic_items['1'] = {
	-- dynamic items for room 1
	-- when a room loads, it will look up in this table for dynamic items
	--dave_1 = {wa = 'gate.walkarea', pos = {180, 10}, dir='s'},
	dave_2 = {wa = 'gate.walkarea', pos = {200, 10}, dir='s'},
	dave_3 = {wa = 'gate.walkarea', pos = {220, 10}, dir='e'},
}
-- add any custom methods here
--require ("./func")
--require("ff")
engine.state.room = '1'

variables.dynamic_items['1'] = { dave_1 = { pos = {10, 10}, dir='e' }}

--variables.inventory['dave_1']['frontdoor.key'] = 1


glib.load_folder ('items')
glib.load_folder ('sprites')





--require("defaultscripts")

