require ("text")

engine = {
    device_size = { 320, 200 },
    window_size = { 800, 600 },
    title = "Hello world!",
    prova = 10
}

fonts = {
    { name = "ui", file  = "fonts/monkeysmall.ttf" },
    { name = "monkey", file  = "fonts/MonkeyIsland-1990.ttf" }
}

-- inventory keeps a table with objects
inventory = {
}


variables = {
    _verbs = {
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
    },
    -- sets the start room
    _room = "scummbar",
    _previousroom = "loom",
	_pause = false,
    talkedToLookout = false,
    lookoutKnowsName = false,	
	talkedToPirates = false,
	doneTalkDog = false,
	doneTalkLoom = false,
	seagull = 0
}



variables._actionInfo = {
        verb = variables._verbs.walk,
        obj1 = nil,
        obj2 = nil,
        selectSecond = false
    }

function variables._actionInfo:toString ()
    local t = { self.verb.text }
    if (self.obj1 ~= nil) then
		o1 = objects[self.obj1]
        t[2] = o1.text
        if (self.obj2 ~= nil) then
            o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = o2.text
        else
            if (self.selectSecond == true) then
               t[3] = self.verb.prep 
            end
        end 
    end
    return table.concat(t," ")
end

function variables._actionInfo:reset()
   self.verb = variables._verbs.walk
   self.obj1 = nil
   self.obj2 = nil
   self.selectSecond = false
end

dirHelper = {
    north = "back",
    south = "front",
    east = "right",
    west = "right"
    
}

config = {
    
    ui_unselected_color = { 0, 170, 0, 255},
    ui_selected_color = {255, 255, 85, 255},
    ui_currentaction_color ={0, 170, 170, 255},
	ui_inv_unselected = {170, 0, 170, 255},
	ui_inv_selected = {255, 85, 255, 255}
    
}

function pause()

	variables._pause = not variables._pause
	print ("pause = " .. tostring(variables._pause))
	monkey.enablescriptengine(not variables._pause)
	monkey.enablemouse(not variables._pause)
	monkey.enablekeyboard(not variables._pause)
	monkey.enablekey(32, true)
	monkey.enableupdate(not variables._pause)
	d = monkey.getEntity("diag")
	if (variables._pause == true) then
		monkey.addEntity({
			pos = {0, 108, 6},
			gfx = { shape = { type="rect", width=320.0, height=10.0}, color = {0, 0, 0, 255}, draw = "solid" }
		}, d)
		monkey.addEntity({
			pos = {160, 110, 6.1},
			text = { id=strings.ui.pause_message, font="ui", color = {255,85,85,255}, align="bottom"}
		}, d)
		monkey.addEntity({
			pos = {-1,108,6.1},
			gfx = { shape = { type="rect", width=322.0, height=10.0}, color = {255,85,85,255}, draw = "outline" }
		}, d)
	else
		d:clear()
	end
end

hotkeys = {
	{ key = 299, func = function() monkey.endroom() end },
	{ key = 32, func = pause }
}

-- hotkeys = {
-- 	space = pause,
-- 	f8 = restart

-- }