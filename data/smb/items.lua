characters = {
    guybrush = {
        tag = "player",
        color = {255, 255, 255, 255}
    },
    lookout = {
        tag = "lookout",
        text = strings.objects.lookout,
        pos = {160, 36},
        dir ="west",
        color = {170, 170, 170, 255},
        talk = curry(talk, { character = "lookout", node = 1})
    }
}

objects = {
    stairs = {
        text = strings.objects.stairs,
        pos = {250, 0}, -- location where the player will go
        walk = curry(changeRoom, "village1")
    },
    path = {
        text = strings.objects.path,
        pos = {8, 71},
        walk = curry(changeRoom, "lookout")
        
    },
    poster = {
        text = strings.objects.poster,
        pos = {269, 133},
        dir = "north",
        look = curry (say, {character = characters.guybrush, lines= { strings.village1[1], strings.village1[2] }})
    },
    village1_door = {
        text = strings.objects.door,
        tag = "door1",
        pos = {715, 133},
        dir = "north",
        openFlag = false
        --isopen = false,
    },
    scummbar_door_out = {
        text = strings.objects.door,
        tag = "door1",
        pos = {66, 19},
        dir = "west"        
    },
    door_bar_kitchen = {
        text = strings.objects.door,
        tag = "doorkitchen",
        pos = {600, 14},
		dir = "east",
		openFlag = false
    }
}

objects.village1_door.walk = curry(walkToDoor, {obj = objects.village1_door, roomId = "scummbar"} )
objects.village1_door.open = curry(operateDoor, {obj = objects.village1_door, open = true} )
objects.village1_door.close = curry(operateDoor, {obj = objects.village1_door, open = false} )
objects.village1_door.isopen = function() return objects.village1_door.openFlag end
objects.village1_door.setopen = function(open) objects.village1_door.openFlag = open end

objects.scummbar_door_out.isopen = function() return objects.village1_door.openFlag end
objects.scummbar_door_out.setopen = function(open) objects.village1_door.openFlag = open end
objects.scummbar_door_out.walk = curry(walkToDoor, {obj = objects.village1_door, roomId = "village1"} )
objects.scummbar_door_out.open = curry(operateDoor, {obj = objects.village1_door, open = true} )
objects.scummbar_door_out.close = curry(operateDoor, {obj = objects.village1_door, open = false} )

objects.door_bar_kitchen.walk = curry(walkToDoor, {obj = objects.door_bar_kitchen, roomId = "kitchen"} )
objects.door_bar_kitchen.open = curry(operateDoor, {obj = objects.door_bar_kitchen, open = true} )
objects.door_bar_kitchen.close = curry(operateDoor, {obj = objects.door_bar_kitchen, open = false} )
objects.door_bar_kitchen.isopen = function() return objects.door_bar_kitchen.openFlag end
objects.door_bar_kitchen.setopen = function(open) objects.door_bar_kitchen.openFlag = open end


