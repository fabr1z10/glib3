local inventory = engine.state.scumm.inventory

engine.items["010.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes = {},
		outline = {0,0,0,105,161,105,283,32,301,32,185,105,316,105,316,0}},
	priority = 0,
	depth = { 
		type="isoline", 
		lines = {
			{ z = 1, points = {0, 0, 316, 0} },			
			{ z = 0.5, points = {0, 105, 161, 105, 283, 32, 301,32,316, 32 } },
			{ z = 0, points = {0, 166, 316, 166 } },
		}
	},
}
engine.items["010.wall"] = makeItem { 
	x =0,y=0,
	outline = {0,124,171,124,297,54,297,35,281,35,160,107,0,107},
	msg = strings.room010[2],
}

engine.items["010.garden"] = makeItem { 
	x =0,y= 0,
	outline = {0,101,155,101,250,30,0,30},
	msg = strings.room010[1],
	use = function() 
		if (inventory["carrot"] == nil) then
			return {
				{ type = scumm.action.walkto, args = { tag="player", pos = {50, 61}}},
				{ type = action.kq.showmessage, args = { msg = strings.room009[3] }},
				{ type = scumm.action.add_to_inventory_sci, args= {id = "carrot"}}
			}
		else
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room009[4] }},
			}

		end
	end	
}