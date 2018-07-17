objects = {
    guybrush = {
        tag = "player",
        color = {255, 255, 255, 255},
		offset = {0, 60}
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
		openFlag = false,
		isopen = curry(isOpen, "door_kitchen_pier"),
		setopen = curry2(setOpen, "door_kitchen_pier"),
		posfunc = function () 
			player = monkey.getEntity("player")
			if (player.x > 200) then
				return { 210, 14}
			else
				return {190, 14}	
			end
		end,
		dirfunc = function () 
			player = monkey.getEntity("player")
			if (player.x > 200) then
				return "west"
			else
				return "east"	
			end
		end,
		open = openKitchenPierDoor,
		close = closeKitchenPierDoor
	},
	meat = {
		text = strings.objects.meat,
		tag = "meat",
		pos = {76, 19},
		dir = "north",
 		look = curry (say, { character="guybrush", lines= { strings.kitchen[1] }} ),
		pick = curry (pickup, {obj = "meat"})
	},
	pot = {
		text = strings.objects.pot,
		tag = "pot",
		pos = {109, 19},
		dir ="north",
		pickupAnim = "kneel_back",
		look = curry (say, { character="guybrush", lines= { strings.kitchen[2] }} ),
		pick = curry (pickup, {obj = "pot"})
	},
	fish = {
		text = strings.objects.fish,
		tag = "fish",
		pos = {239, 16},
		dir ="south",
		pickupAnim = "kneel_front",
		look = curry (say, { character="guybrush", lines= { strings.kitchen[3] }} ),
		pick = getFish
	},
	potostew = {
		text = strings.objects.potostew,
		tag ="potostew",
		pos = {161, 19},
		dir ="north",
		look = lookatPotoStew,
		meatin = false,
		pick = pickMeatInStew,
		use = {
			meat = stewMeat
		}
	},
	barrel = {
		text = strings.objects.barrel,
		tag ="barrel",
		pos = {47, 6},
		dir ="west",
		look = curry (say, { character="guybrush", lines= { strings.kitchen[6] }} )
	},
	kitchen_table = {		
		text = strings.objects.kitchen_table,
		tag ="kitchentable",
		pos = {132, 14},
		dir ="south"
	},
	fireplace = {
		text = strings.objects.fireplace,
		tag ="fireplace",
		pos = {506, 41},
		dir ="east",
		look = curry (say, { character="guybrush", lines= { strings.scummbar[1] }} )
	},
	ilp = {
		text = strings.objects.ilp,
		tag="ilp",
		pos={474,7},
		dir ="west",
 		talk = talkToPirates
	},
	ilp1 = {
		color = {85, 85, 255, 255},
		offset = {0, 60},
		tag ="ilp1"		

	},
	ilp2 = {
		color = {255, 255, 85, 255},
		offset = {0, 60},
		tag ="ilp2"		
	},
	ilp3 = {
		color = {255, 85, 255, 255},
		offset = {0, 60},
		tag ="ilp3"		
	},

}
