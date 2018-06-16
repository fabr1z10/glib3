function changeRoom(roomId)
    return {
        { type = "gotoroom", room = roomId }
    }
end

function walkToDoor(args) 
    if (args.obj.isopen == true) then
        return {
            { type = "gotoroom", room = args.roomId }
        }
    end 
end

function operateDoor(args)
    -- if args.open == true then I need to something when it's closed
    -- and viceversa, so ...
    if (args.obj.isopen ~= args.open) then
        face = dirHelper[args.obj.dir]
        return { 
            { type="animate", actor="player", anim=("operate" .. face) },
            { type="delay", sec="0.5" },
            { type="animate", actor = args.obj.tag, anim = (args.open and "open" or "close") },
            { type="animate", actor="player", anim=("idle" .. face) },
            { type="callfunc", func = function() args.obj.isopen = args.open end }
        }
    end 
end

characters = {
    guybrush = {
        name = "player",
        color = {255, 255, 255, 255}
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



actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

