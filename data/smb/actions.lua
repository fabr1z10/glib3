function pippo()
    monkey.play(
        {
			startid = 0,
			id = "_walk",
            actions = {
				{
					id = 0,
					walkarea = "walkarea",
					actor = "player",
					type = "walkto",
					pos = {250, 0}
				},
				{
					id = 1,
					type = "gotoroom",
					room = "village1"
				}
				
			},
			edges = {
				{0, 1}	
			}
        }
    )
    
end

objects = {
    stairs = {
        text = strings.objects.stairs,
        pos = {250, 0}, -- location where the player will go
        open = pippo
    }
    
    
}

actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

