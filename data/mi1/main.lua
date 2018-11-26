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
    pick = { code="pick", text = strings.ui.pickup, objects = 1 },
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
    _room = "lookout",
	_previousroom="",
	_actionInfo = {
        verb = nil,
        obj1 = nil,
        obj2 = nil,
        selectSecond = false
    },
	door_village_scummbar = 0
}

require ("script")
require ("funcs")
require ("sprites")

-- load room specific scripts
scripts = {}
factory = {}
items = {}
dialogues = {}
load_all("scripts")
load_all("factories")
load_all("items")
load_all("dialogues")