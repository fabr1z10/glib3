function changeRoom(roomId, script)
    table.insert (script.actions,
    {
        id = #script.actions,
 	    type = "gotoroom",
		room = roomId
    })
end

function walkToDoor(args, script) 
    if (args.obj.isopen == true) then
        table.insert (script.actions, {
            id = #script.actions,
            type = "gotoroom",
            room = args.roomId
        })
    end 
end

function useDoor(args, script) 
    cond = args.open and false or true

    if (args.obj.isopen == cond) then
        table.insert (script.actions, 
        { id = #script.actions, type="animate", actor="player", anim="operate_back" })
        table.insert (script.actions, 
        { id = #script.actions, type="delay", sec="0.5" })
        table.insert (script.actions,
        {
            id = #script.actions,
            type = "animate",
            actor = args.obj.tag,
            anim = "open"
        })
        table.insert (script.actions, 
        { id = #script.actions, type="animate", actor="player", anim="idle_back" })        
        args.obj.isopen = true
    end 
end

function closeDoor(args, script) 
    if (args.obj.isopen == true) then
        table.insert (script.actions, 
        { id = #script.actions, type="animate", actor="player", anim="operate_back" })
        table.insert (script.actions, 
        { id = #script.actions, type="delay", sec="0.5" })
        table.insert (script.actions,
        {
            id = #script.actions,
            type = "animate",
            actor = args.obj.tag,
            anim = "close"
        })
        table.insert (script.actions, 
        { id = #script.actions, type="animate", actor="player", anim="idle_back" })        
        args.obj.isopen = false
    end 
end

characters = {
    guybrush = {
        name = "player",
        color = {255, 255, 255, 255}
    }
}
print ("QUI CI ARRIVO")
print (characters.guybrush.name)
objects = {
    stairs = {
        text = strings.objects.stairs,
        pos = {250, 0}, -- location where the player will go
        walk = curry2(changeRoom, "village1")
    },
    path = {
        text = strings.objects.path,
        pos = {8, 71},
        walk = curry2(changeRoom, "lookout")
        
    },
    poster = {
        text = strings.objects.poster,
        pos = {269, 133},
        dir = "north",
        look = curry(say, {character = characters.guybrush, lines = { strings.village1[1], strings.village1[2] }})        
    },
    village1_door = {
        text = strings.objects.door,
        tag = "door1",
        pos = {715, 133},
        dir = "north",
        isopen = false,
    }
}

objects.village1_door.walk = curry2(walkToDoor, {obj = objects.village1_door, roomId = "lookout"})
objects.village1_door.open = curry2(openDoor, {obj = objects.village1_door} )
objects.village1_door.close = curry2(closeDoor, {obj = objects.village1_door} )



actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

