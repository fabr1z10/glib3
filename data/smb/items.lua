objects = {
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
        talk = curry(talk, { character = "lookout", node = 1}),
		look = curry(say,{character ="guybrush", lines = {strings.dialogues.lookout.text[50]}})
    },
    cook = {
        tag = "cook",
        color = {85, 255, 255, 255},
    },
    stairs = {
        text = strings.objects.stairs,
        pos = {250, 0}, -- location where the player will go
        walk = curry(changeRoom, "village1")
    },
	cliffside = {
		text = strings.objects.cliffside,
		pos = {8, 71},
		walk = curry(changeRoom, "lookout")
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
        look = curry (say, { character="guybrush", lines= { strings.village1[1], strings.village1[2] }} )
    },
    village1_door = {
        text = strings.objects.door,
        tag = "door1",
        pos = {715, 13},
        dir = "north",
        openFlag = false,
		walk = curry(walkToDoor, { obj = "village1_door", roomId = "scummbar"}),
		open = curry(operateDoor, { obj = "village1_door", open = true }),
		close = curry(operateDoor, { obj = "village1_door", open = false }),
		isopen = curry(isOpen, "village1_door"),
		setopen = curry2(setOpen, "village1_door")
    },
    scummbar_door_out = {
        text = strings.objects.door,
        tag = "door1",
        pos = {66, 19},
        dir = "west",
		walk = curry(walkToDoor, {obj = "scummbar_door_out", roomId = "village1"}),
		open = curry(operateDoor, { obj = "scummbar_door_out", open = true }),
		close = curry(operateDoor, { obj = "scummbar_door_out", open = false }),
		isopen = curry(isOpen, "village1_door"),
		setopen = curry2(setOpen, "village1_door")
    },
    door_bar_kitchen = {
        text = strings.objects.door,
        tag = "door_bar_kitchen",
        pos = {600, 14},
		dir = "east",
		openFlag = false,
		open = openBarKitchen,
		walk = enterBarKitchen,
		close = curry(operateDoor, {obj = "door_bar_kitchen", open = false} ),
		isopen = curry(isOpen, "door_bar_kitchen"),
		setopen = curry2(setOpen, "door_bar_kitchen")		
    },
	door_kitchen_bar = {
		text = strings.objects.door,
		tag = "door_kitchen_bar",
        pos = {50, 15},
		dir = "west",
		walk = curry(walkToDoor, {obj = "door_kitchen_bar", roomId = "scummbar"}),
		open = curry(operateDoor, { obj = "door_kitchen_bar", open = true }),
		close = curry(operateDoor, { obj = "door_kitchen_bar", open = false }),
		isopen = curry(isOpen, "door_bar_kitchen"),
		setopen = curry2(setOpen, "door_bar_kitchen")		
	},
	door_kitchen_pier = {
		text = strings.objects.door,
		tag = "door_kitchen_pier",
		openFlag = false
	},
	meat = {
		text = strings.objects.meat,
		tag = "meat",
		pos = {76, 19},
		dir = "north",
 		look = curry (say, { character="guybrush", lines= { strings.kitchen[1] }} ),
		pick = curry (pickup, {obj = "meat"})
	}
}

--objects.village1_door.walk = curry(walkToDoor, {obj = objects.village1_door, roomId = "scummbar"} )
--objects.village1_door.open = curry(operateDoor, {obj = objects.village1_door, open = true} )
--objects.village1_door.close = curry(operateDoor, {obj = objects.village1_door, open = false} )
--objects.village1_door.isopen = function() return objects.village1_door.openFlag end
--objects.village1_door.setopen = function(open) objects.village1_door.openFlag = open end


--objects.scummbar_door_out.setopen = function(open) objects.village1_door.openFlag = open end
--objects.scummbar_door_out.walk = curry(walkToDoor, {obj = objects.village1_door, roomId = "village1"} )
--objects.scummbar_door_out.open = curry(operateDoor, {obj = objects.village1_door, open = true} )
--objects.scummbar_door_out.close = curry(operateDoor, {obj = objects.village1_door, open = false} )

--objects.door_bar_kitchen.walk = curry(walkToDoor, {obj = objects.door_bar_kitchen, roomId = "kitchen"} )
--objects.door_bar_kitchen.open = curry(operateDoor, {obj = objects.door_bar_kitchen, open = true} )

objects.door_bar_kitchen.isopen = function() return objects.door_bar_kitchen.openFlag end
objects.door_bar_kitchen.setopen = function(open) objects.door_bar_kitchen.openFlag = open end


objects.door_kitchen_bar.isopen = objects.door_bar_kitchen.isopen
objects.door_kitchen_bar.setopen = objects.door_bar_kitchen.setopen
objects.door_kitchen_pier.posfunc = function () 
	player = monkey.getEntity("player")
	if (player.x > 200) then
		return { 210, 14}
	else
		return {190, 14}	
	end
end
objects.door_kitchen_pier.dirfunc = function () 
	player = monkey.getEntity("player")
	if (player.x > 200) then
		return "west"
	else
		return "east"	
	end
end
objects.door_kitchen_pier.isopen = function() return objects.door_kitchen_pier.openFlag end
objects.door_kitchen_pier.setopen = function(open) objects.door_bar_kitchen.openFlag = open end
objects.door_kitchen_pier.open = openKitchenPierDoor
objects.door_kitchen_pier.close = closeKitchenPierDoor