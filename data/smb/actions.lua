function changeRoom(roomId, script)
    table.insert (script.actions,
    {
        id = #script.actions,
 	    type = "gotoroom",
		room = roomId
    })
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
        look = curry2_1(say, characters.guybrush, { strings.village1[1], strings.village1[2] })
    },
    village1_door = {
        text = strings.objects.door,
        pos = {715, 133},
        dir = "north",
        open = false
    }
}



actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

