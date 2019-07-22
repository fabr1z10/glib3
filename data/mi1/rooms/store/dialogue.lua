local d = strings.dialogues.storekeeper
local dialogues = engine.dialogues
local swordPrice = 75
local shovelPrice = 100

local cantAffordItem = function(n, checkChildren, m, putBackScript) 
	return {
		text = d[n], 
		active=true, 
		children = function()
			if (checkChildren()) then
				return {2,3,4}
			else
				return {}
			end
		end,
		script = function() 
			local actions = {
				{ type = scumm.action.say, args = {actor="guybrush", lines = {d[n]}}},
				{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines={d[m]}}},
 				putBackScript
			}
			if (not checkChildren()) then
				table.insert (actions, { type = scumm.action.say, args = {actor="guybrush", lines={d[2]}}})
			end
			return actions
 		end
	}
end

local buyShovel = function(n) 
 	variables.shovel_paid = true
 	--variables.inventory["pieces_of_eight"] = variables.inventory["pieces_of_eight"] - shovelPrice
	engine.state.scumm.remove_from_inventory ("pieces_of_eight", shovelPrice)
 	local actions = { 
 		{ type = scumm.action.say, args = {actor="guybrush", lines = {d[n]}}},
 		{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[47], d[48], d[49], d[50], d[33]}}}
 	}
 	return actions
end

local getPriceShovel = function(n)
    local lines = variables.know_shovel_price and {d[28], d[29]} or {d[23], d[24]}     		
 	variables.know_shovel_price = true
 	local actions = { 
 		{ type = scumm.action.say, args = {actor="guybrush", lines = {d[n]}}},
 		{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = lines}}
 	}
 	return actions
end

local buySword = function() 
 	variables.sword_paid = true
	engine.state.scumm.remove_from_inventory ("pieces_of_eight", swordPrice)
 	--variables.inventory["pieces_of_eight"] = variables.inventory["pieces_of_eight"] - swordPrice
 	local actions = { 
 		{ type = scumm.action.say, args = {actor="guybrush", lines = {d[n]}}},
 		{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[31], d[32], d[33]}}}
 	}
	return actions
end

local getPriceSword = function(n)
    local lines = variables.know_sword_price and {d[21], d[22]} or {d[16], d[17]}
 	variables.know_sword_price = true
 	local actions = { 
 		{ type = scumm.action.say, args = {actor="guybrush", lines = {d[n]}}},
 		{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = lines}}
 	}
 	return actions
end

local s1 = {
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.sword"} },
	{ type = action.animate, args = {tag="player", anim="operate_n"}},
	{ type = action.delay, args = {sec=0.5}},
	{ type = action.activate, args = {tag="shop.sword", active=true}},
	{ type = scumm.action.remove_from_inventory, args = {id="shop.sword"}},
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.shopkeeper"} },
	{ type = scumm.action.turn, args = {tag="player", dir="east"}},
	{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[20]}}}
}
	

local s2 = {
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.shovel"} },
	{ type = action.animate, args = {tag="player", anim="operate_e"}},
	{ type = action.delay, args = {sec=0.5}},
	{ type = action.activate, args = {tag="shop.shovel", active=true}},
	{ type = scumm.action.remove_from_inventory, args = {id="shop.shovel"}},
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.shopkeeper"} },
	{ type = scumm.action.turn, args = {tag="player", dir="east"}},
	{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[20]}}}
}

local hasSword = function() 
	return engine.state.scumm.has("shop.sword")
end

local hasPaidSword = function() 
	return (engine.state.scumm.has("shop.sword") and variables.sword_paid == true)
end

local hasUnpaidSword = function() 
	return (engine.state.scumm.has("shop.sword") and variables.sword_paid == false)
end

local hasUnpaidShovel = function()
	return (engine.state.scumm.has("shop.shovel") and variables.shovel_paid == false)
end

dialogues.storekeeper = {
	close = function()
		if (variables.chasing_shopkeeper == true) then
			local actions = {
				{ type = action.delay, args = {sec = 5}},
				{ type = action.set_variable, args = {var="chasing_shopkeeper", value=false}},
				--{ type = action.callfunc, args = {func= function() print("ciaociao") end}}
			}
			local s = script.make(actions)
			monkey.play(s)
		end
		--local s = script:new()
		--s.actions = { {id=1, type="callfunc", func= function() refresh_inventory() end}}
		--monkey.play(s)
	end,
	nodes = {
		[1] = { children = {15, 16, 2, 3, 4} },
		-- about this sword...
		[2] = {text= d[4], children={5,6,7}, active=function() return (engine.state.scumm.has("shop.sword") and (variables.sword_paid == false)) end, 
			script = {
				{ type = scumm.action.say, args = {actor="guybrush", lines = {d[4]}}},
				{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[12]}}}
			}
		},
		-- about this shovel...
		[3] = {text= d[5], children = {9,10,11}, active=function() return (engine.state.scumm.has("shop.shovel") and (variables.shovel_paid == false)) end,
			script = {
				{ type = scumm.action.say, args = {actor="guybrush", lines = {d[5]}}},
				{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[12]}}}
			}
		},
		[4] = {text=d[35], active=true, 
			script = {
				{ type = scumm.action.say, args = {actor="guybrush", lines = {d[35]}}},
				{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[9], d[10]}}}
			}
		},
		-- I want the sword
 		[5] = {text=d[13], active=true, children = 
 			function() 
	 			if (engine.state.scumm.has_at_least("pieces_of_eight", 100)) then 
	 				return {15, 2, 3, 4} 
	 			else 
	 				return {8,7} 
	 			end
 			end, 
 			script = function() 
	 			local lines = nil
	 			if (engine.state.scumm.has_at_least("pieces_of_eight", 100)) then
					return buySword(13)
 			    else
					return getPriceSword(13)
				end
 			end
 		},
		-- How much is the sword
 		[6] = {text=d[14], active=true, children = {14, 8, 7}, script = glib.curry(getPriceSword, 14)},
		-- can't afford the sword
 		[7] = cantAffordItem(15, hasUnpaidShovel, 19, s1),
 		[8] = cantAffordItem(18, hasUnpaidShovel, 19, s1),
		-- I want the shovel
 		[9] = {text=d[13], active=true, 
			children = function() 
				if (engine.state.scumm.has_at_least("pieces_of_eight", 75)) then 
					-- If I have the sword, whether paid or unpaid, I will have something to say afterwards...
					if (hasSword()) then
	 					return {15,2,3,4}
					else
						return {}
					end 
	 			else 
	 				return {11, 12} 
	 			end
			end,
 			script = function() 
	 			if (engine.state.scumm.has_at_least("pieces_of_eight", 75)) then
					return buyShovel(13)
 			    else
					return getPriceShovel(13)
				end
 			end
		},
		-- how much is the shovel?
 		[10] = {text=d[14], active=true, children = {13, 11, 12}, script = glib.curry(getPriceShovel, 14)},
		-- I can't afford the sword
 		[11] = cantAffordItem (25, hasUnpaidSword, 26, s2),
		[12] = cantAffordItem (15, hasUnpaidSword, 26, s2),
		-- I'll take it (the shovel)
		[13] = {text=d[46], 
			active = function()
				--only active if Guybrush has enough money
				return (engine.state.scumm.has_at_least("pieces_of_eight", 75))
			end,
			script = glib.curry(buyShovel, 46)
		},
		-- I'll take it (the sword)
		[14] = {text=d[46], 
			active = function()
				--only active if Guybrush has enough money
				return engine.state.scumm.has_at_least("pieces_of_eight", 100)
			end,
			children = function() 
				if (hasSword()) then return {15,2,3,4} else return {} end
			end,
			script = glib.curry(buySword, 46)
		},
		[15] = { text = d[34], act = {16}, deact={15}, active = function() return hasPaidSword() end, 
			script = function()
				return {
					{ type = scumm.action.say, args = { actor="guybrush", lines = {d[34]}}},
					{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[36], d[37], d[38], d[39], d[40], d[41], d[42], d[43]}}},
					{ type = action.create_object, args = {factory = scumm.factory.object, args = {id="shop.sign"}, parent="store.walkarea"}},
					{ type = action.create_object, args = {factory = scumm.factory.object, args = {id="shop.bell"}, parent="store.walkarea"}},
					{ type = scumm.action.walkto, args = {tag="shop.shopkeeper", pos = {289, 0}}},
					{ type = scumm.action.walkto, args = {tag="shop.shopkeeper", pos = {260, 0}}},
					{ type = scumm.action.walkto, args = {tag="shop.shopkeeper", obj = "shop.door"}},
					{ type = scumm.action.turn, args = {tag="shop.shopkeeper", dir="east"}},
					{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[45]}}},
					{ type = scumm.action.turn, args = {tag="shop.shopkeeper", dir="west"}},
					{ type = action.animate, args = {tag="shop.door", anim="open"}},
					{ type = action.delay, args = {sec=0.5}},
					{ type = action.activate, args = {tag="shop.shopkeeper", active=false}},
					{ type = action.animate, args = {tag="shop.door", anim="close"}},
					{ type = action.set_variable, args = {var="door_shop", value = 0}},
					{ type = action.set_variable, args = {var="chasing_shopkeeper", value=true}},
					{ type = action.set_variable, args = {var="shopkeeper_away", value=2}}
				}
			end
		},
		[16] = { text = d[56], active = false, 
			script = function()
				return {
					{ type = scumm.action.say, args = { actor="guybrush", lines = {d[56]}}},
					{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[57]}}},
					{ type = scumm.action.say, args = { actor="guybrush", lines = {d[58]}}},
					{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[41], d[42], d[59]}}},
					{ type = action.create_object, args = {factory = scumm.factory.object, args = {id="shop.sign"}, parent = "store.walkarea"}},
					{ type = action.create_object, args = {factory = scumm.factory.object, args = {id="shop.bell"}, parent = "store.walkarea"}},
					{ type = scumm.action.walkto, args = {tag="shop.shopkeeper", pos = {289, 0}}},
					{ type = scumm.action.walkto, args = {tag="shop.shopkeeper", pos = {260, 0}}},
					{ type = scumm.action.walkto, args = {tag="shop.shopkeeper", obj = "shop.door"}},
					{ type = scumm.action.turn, args = {tag="shop.shopkeeper", dir="east"}},
					{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[45]}}},
					{ type = scumm.action.turn, args = {tag="shop.shopkeeper", dir="west"}},
					{ type = action.animate, args = {tag="shop.door", anim="open"}},
					{ type = action.delay, args = {sec=0.5}},
					{ type = action.activate, args = {tag="shop.shopkeeper", active=false}},
					{ type = action.animate, args = {tag="shop.door", anim="close"}},
					{ type = action.set_variable, args = {var="door_shop", value = 0}},
					{ type = action.set_variable, args = {var="chasing_shopkeeper", value=true}},
					{ type = action.set_variable, args = {var="shopkeeper_away", value=2}}
				}
			end
		}
	}	
}