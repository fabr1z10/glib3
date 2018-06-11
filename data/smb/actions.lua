function changeRoom(roomId, script)
    table.insert (script.actions,
    {
        id = #script.actions,
 	    type = "gotoroom",
		room = roomId
    })
end

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
        
    }
    
    
}

actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

