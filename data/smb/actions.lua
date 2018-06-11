function pippo(script)
    table.insert (script.actions,
    {
        id = #script.actions,
 	    type = "gotoroom",
		room = "village1"
    })
end

objects = {
    stairs = {
        text = strings.objects.stairs,
        pos = {250, 0}, -- location where the player will go
        open = pippo
    },
    path = {
        text = strings.objects.path,
        pos = {8, 71}
    }
    
    
}

actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

