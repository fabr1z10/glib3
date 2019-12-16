local inventory = engine.state.scumm.inventory

engine.items["009.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes = {},
		outline = {0,0,0,105,150,105,40,36,40,32,66,32,185,105,316,105,316,0}},
	priority = 0,
	depth = { 
		type="isoline", 
		lines = {
			{ z = 1, points = {0, 0, 316, 0} },			
			{ z = 0.5, points = {0, 32, 66, 32, 185, 105, 316, 105 } },
			{ z = 0, points = {0, 166, 316, 166 } },


		}
	},
}

engine.items["009.wall"] = makeItem { 
	x =43,y= 35,
	outline = {0,0,0,20,132,89,273,89, 273,73, 140,73,21,0},
	msg = strings.room009[1],
}

engine.items["009.field"] = makeItem { 
	x =85,y= 27,
	outline = {0,0,113,73,231,73,231,0},
	msg = strings.room009[2],
	use = function() 
		if (inventory["carrot"] == nil) then
			return {
				{ type = scumm.action.walkto, args = { tag="player", pos = {210, 61}}},
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