engine = {
    device_size = { 320, 200 },
    window_size = { 800, 600 },
    title = "The secret of Monkey Island",
}

-- this is constant config stuff
config = {
	lang = "eng",
    ui_unselected_color = { 0, 170, 0, 255},
    ui_selected_color = {255, 255, 85, 255},
    ui_currentaction_color ={0, 170, 170, 255},
	ui_inv_unselected = {170, 0, 170, 255},
	ui_inv_selected = {255, 85, 255, 255}
}

require ("text/" .. config.lang .."/text")


config.verbs = {
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






fonts = {
    { name = "ui", file  = "fonts/monkeysmall.ttf" },
    { name = "monkey", file  = "fonts/MonkeyIsland-1990.ttf" }
}


-- this stuff will change at gametime
variables = {
    _room = "clearing",
	_previousroom="",
	_actionInfo = {
        verb = nil,
        obj1 = nil,
        obj2 = nil,
        selectSecond = false
    },
	first_time_mancomb = true,
	first_time_estevan = true,
	door_village_scummbar = 0,
	door_scummbar_kitchen = 0,
	door_kitchen_pier = 0,
	door_voodoolady = 0,
	door_shop = 0,
	cook_in_kitchen = true,
	meat_in_pot = false,
	can_pickup_fish = true,
    seagull_jump = 1,
    seagull_flying = false,
	talked_to_important_pirates = false,
	talked_to_citizen = false,
    talked_about_map = false,
	fish_taken=false,
	talking_to_voodoolady = false,
	talked_to_voodoolady = false,
	voodoolady_told_future = false,
	sword_paid = false,
	shovel_paid = false,
	know_sword_price = false,
	know_shovel_price = false,
    met_fester = false,
	entered_circus = false,
	circus_knows_trick = false,
	circus_knows_helmet = false,
	inventory = {
		-- put here your belongings
		
	}
}

variables.inventory["pieces_of_eight"] = 10000

require ("script")
require ("funcs")


-- load room specific scripts
scripts = {}
factory = {}
action = {}
items = {}
dialogues = {}
sprites = {}
load_all("sprites")
load_all("factories")
load_all("scripts")

load_all("items")
load_all("dialogues")