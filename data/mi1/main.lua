package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path


engine = {
	device_size = { 320, 200 },
	window_size = { 640, 400 },
	title = "The secret of Monkey Island",
	shaders = { "unlit_textured", "unlit_color", "text" },
	assets = {
		fonts = {
	    	ui = {file  = "./fonts/monkeysmall.ttf" },
    		monkey = {file  = "./fonts/MonkeyIsland-1990.ttf"}
		},
		models = {},
		animations = {}
	},
	global_assets = {
		fonts = { "ui", "monkey" }
	},
	start_room = "kitchen",
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


-- the verbs for the game. You might have multiple sets here! Watch out
engine.config.verbs = {
 	open = { code="open", text = strings.ui.open, objects = 1 },
    close = { code="close", text = strings.ui.close, objects = 1 },
    push = { code="push", text = strings.ui.push, objects = 1 },
    pull = { code="pull", text = strings.ui.pull, objects = 1 },
    walk = { code="walk", text = strings.ui.walkto, objects = 1 },
    pick = { code="pickup", text = strings.ui.pickup, objects = 1 },
    talk = { code="talk", text = strings.ui.talkto, objects = 1 },
    give = { code="give", text = strings.ui.give, objects = 2, prep = strings.ui.giveprep },
    use = { code="use", text = strings.ui.use, objects = 2, prep= strings.ui.useprep },
    look = { code="look", text = strings.ui.lookat, objects = 1 },
    turnon = { code="turnon", text = strings.ui.turnon, objects = 1 },
    turnoff = { code="turnoff", text = strings.ui.turnoff, objects = 1 }
}
engine.config.verbset = {
    [1] = { "open", "close", "push", "pull", "walk", "pick", "talk", "give", "use", "look", "turnon", "turnoff" }

}

variables = {
-- 	_previousroom="",

 	first_time_mancomb = true,
 	first_time_estevan = true,
 	door_village_scummbar = 0,
    door_scummbar_kitchen = 0,
 	door_kitchen_pier = 0,
	door_voodoolady = 0,
	troll_in = true,
 	door_shop = 0,
    door_church = 0,
    cook_in_kitchen = true,
 	meat_in_pot = false,
-- 	can_pickup_fish = true,
    seagull_jump = 1,
    seagull_on_board = false,
-- 	talked_to_important_pirates = false,
    talked_to_citizen = false,
    talked_about_map = false,
 	fish_taken=false,
	troll_fed = false,
-- 	talking_to_voodoolady = false,
-- 	talked_to_voodoolady = false,
-- 	voodoolady_told_future = false,
 	sword_paid = false,
 	shovel_paid = false,
	chasing_shopkeeper = false,
	shopkeeper_away = 0,
-- 	know_sword_price = false,
-- 	know_shovel_price = false,
--     met_fester = false,
 	entered_circus = false,
 	circus_knows_trick = false,
 	circus_knows_helmet = false,
    circus_feat_done = false,
	map_looked = false,
	talked_to_otis = false,
	mint_given = false,
	swordmaster_trunk_open = false,
	know_where_sword_master_is = false,
	play_swordmaster_storekeeper_cutscene = false,
-- 	talked_to_troll = false,
 	inventory = { 	},

	save_states = {
		start = function()
			engine.state.room = "lookout"
			engine.state.previousRoom =""
		end,
		taken_stuff_from_kitchen = function()
			engine.state.scumm.inventory["kitchen.meat"] = 1
			engine.state.scumm.inventory["kitchen.pot"] = 1
			engine.state.scumm.inventory["kitchen.fish"] = 1
			variables.fish_taken = true
			engine.state.room = "clearing"
			engine.state.previousRoom ="scummbar"
		end,
		done_circus = function() 
			engine.state.scumm.inventory["kitchen.meat"] = 1
			engine.state.scumm.inventory["pieces_of_eight"] = 478
			engine.state.scumm.inventory["kitchen.fish"] = 1
			variables.fish_taken = true
			variables.circus_feat_done = true
			engine.state.room = "village2"
			engine.state.previousRoom ="circus"
		end,
		got_map = function() 
			engine.state.scumm.inventory["kitchen.meat"] = 1
			engine.state.scumm.inventory["pieces_of_eight"] = 478
			engine.state.scumm.inventory["kitchen.fish"] = 1
			engine.state.scumm.inventory["map"] = 1
			variables.fish_taken = true
			variables.circus_feat_done = true
			engine.state.room = "jail"
			engine.state.previousRoom ="village1"
		end,
		bought_store = function()
			engine.state.scumm.inventory["kitchen.meat"] = 1
			engine.state.scumm.inventory["pieces_of_eight"] = 478
			engine.state.scumm.inventory["kitchen.fish"] = 1
			engine.state.scumm.inventory["shop.sword"] = 1
			engine.state.scumm.inventory["shop.shovel"] = 1
			engine.state.scumm.inventory["map"] = 1
			variables.fish_taken = true
			variables.circus_feat_done = true
			variables.sword_paid = true
			variables.shovel_paid = true
			engine.state.room = "forest_6"
			engine.state.previousRoom ="forest_5"
			variables.chasing_shopkeeper = true
		end
	}

}

variables.save_states.bought_store()

--engine.state.scumm.inventory["kitchen.fish"] = 1
--engine.state.scumm.inventory["pieces_of_eight"] = 1000
--engine.state.scumm.inventory["shop.sword"] = 1
--engine.state.scumm.inventory["shop.shovel"] = 1
--engine.state.scumm.inventory["kitchen.meat"] = 1
--variables.sword_paid = true








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