print("Hello world!")

require ("text")
require ("defaultactions")

function ciao() 
    print "Chiamo ciao "
    print (engine.prova)
end

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
inventory = {}


defaultActions = {
   walk = defaultWalk,
   look = defaultLook
   
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
    _room = "village1",
    _previousroom = "lookout"
    
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
        t[2] = self.obj1.text
        if (self.obj2 ~= nil) then
            t[3] = self.verb.prep
            t[4] = self.obj2.text
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
   obj1 = nil
   obj2 = nil
   selectSecond = false
end

config = {
    
    ui_unselected_color = { 0, 170, 0, 255},
    ui_selected_color = {255, 255, 85, 255},
    ui_currentaction_color ={0, 170, 170, 255}
    
}

