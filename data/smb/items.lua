characters = {
    guybrush = {
        name = "player",
        color = {255, 255, 255, 255}
    },
    lookout = {
        name = "lookout",
        text = strings.objects.lookout,
        pos = {0, 0},
        dir ="west",
        color = {255,255,255,255},
        talk = curry(startDialogue, { dialogueId="lookout", nodeId = 1})
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
        isopen = false,
    }
}

objects.village1_door.walk = curry(walkToDoor, {obj = objects.village1_door, roomId = "lookout"} )
objects.village1_door.open = curry(operateDoor, {obj = objects.village1_door, open = true} )
objects.village1_door.close = curry(operateDoor, {obj = objects.village1_door, open = false} )