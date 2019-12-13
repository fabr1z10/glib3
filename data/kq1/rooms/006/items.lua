engine.items["006.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes = {
		},
		outline = {0,0,0,125,316,125,316,0}
	},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["006.hole"] = makeItem { 
	x = 244, y= 43,
	--x=0,y=0,
	outline = {0,0,16,0,16,4,0,4},
	msg = strings.room006[2],
	look = function() 
		if (variables.dagger_taken == 0) then 
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room006[2] }},
			}
		else
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room006[6] }},
			}
		end

	end,
	use = function() 
		if (variables.dagger_taken == 0) then 
			variables.dagger_taken = 1
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room006[3] }},
				{ type = scumm.action.add_to_inventory_sci, args= {id = "dagger"}}
			}
		else
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room006[6] }},
			}
		end

	
	end
	--gfx = "bg002.png",
}

engine.items["006.rock"] = makeItem { 
	x = 236, y= 33,
	--x=0,y=0,
	priority=2,
	outline = {0,0,34,0,34,23,0,23},
	msg = strings.room006[4],
	--gfx = "bg002.png",
	model = "006.rock",
	hole = { 
	--s	outline = {50, 50, 50, 150, 250, 150, 250, 50}
		outline = {0,0,0,2,34,2,34,0}
	},
	use = function() 
		if (variables.rock_moved == 0) then 
			variables.rock_moved = 1
			return {
				{ type = scumm.action.walkto, args = { tag="player", pos = {252, 40}}},
				{ type = scumm.action.turn, args = {tag="player", dir="s"}},
				{ type = action.kq.showmessage, args = { msg = strings.room006[1] }},
				{ type = action.move, args= {tag="006.rock", by = {0,-12}, speed=10}}
			}
		else
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room006[5] }},
			}
		end
	end
}