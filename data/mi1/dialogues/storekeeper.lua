local d = strings.dialogues.storekeeper


local s1 = {
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.sword"} },
	{ type = action.animate, args = {tag="player", anim="operate_n"}},
	{ type = action.delay, args = {sec=0.5}},
	{ type = action.activate, args = {tag="shop.sword", value=true}},
	{ type = scumm.action.remove_from_inventory, args = {id="shop.sword"}},
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.shopkeeper"} },
	{ type = scumm.action.turn, args = {tag="player", dir="east"}},
	{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[20]}}}
}
	

local s2 = {
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.shovel"} },
	{ type = action.animate, args = {tag="player", anim="operate_e"}},
	{ type = action.delay, args = {sec=0.5}},
	{ type = action.activate, args = {tag="shop.shovel", value=true}},
	{ type = scumm.action.remove_from_inventory, args = {id="shop.shovel"}},
 	{ type = scumm.action.walkto, args = {tag="player", obj="shop.shopkeeper"} },
	{ type = scumm.action.turn, args = {tag="player", dir="east"}},
	{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[20]}}}
}
-- 	{ action.walkto, {id=2, actor="guybrush", pos={150, 30}}},
-- 	{ action.scroll, {id=3, speed=50, to ={160, 72}, after={1}}},
-- 	{ action.activate, {id = 4, tag="bg1", value=true, after={1}}},
-- 	{ action.activate, {id = 5, tag="bg2", value=false, after={3}}},
-- 	{ action.set_variable, {id=6, var="talking_to_voodoolady", value=false }}
-- }

-- local s2 = {
-- 	{ action.noop, {id = 1}},
-- 	{ action.say, {id = 2,actor="voodoolady.voodoolady", lines = {d[29]}, animstart="talk", animend="idle"}},
-- 	{ action.animate_once, {id=3, actor="voodoolady.voodoolady_body", anim="raisehands"}},
-- 	{ action.animate, {id=4, actor="voodoolady.voodoolady_body", anim="idle"}},
-- 	{ action.say, {id =5, actor="voodoolady.voodoolady", lines = {d[30], d[31]}, animstart="talk", animend="idle"}},
-- 	{ action.say, {id =6,actor="guybrush", lines = {d[32]}}},
-- 	{ action.say, {id =7, actor="voodoolady.voodoolady", lines = {d[33]}, animstart="talk", animend="idle"}},
-- 	{ action.delay, {id=8, sec=0.5}},
-- 	{ action.say, {id =9,actor="guybrush", lines = {d[34], d[35]}}},
-- 	{ action.animate_once, {id=10, actor="voodoolady.voodoolady_body", anim="raisehands"}},
-- 	{ action.animate, {id=16, actor="voodoolady.voodoolady_body", anim="idle", after={10}}},
-- 	{ action.say, {id =11, actor="voodoolady.voodoolady", lines = {d[36]}, animstart="talk", animend="idle", after={10}}},
-- 	{ action.say, {id =12, actor="guybrush", lines = {d[37]}}},
-- 	{ action.say, {id =13, actor="voodoolady.voodoolady", lines = {d[38]}, animstart="talk", animend="idle"}},
-- 	{ action.say, {id =14, actor="guybrush", lines = {d[39]}}},
-- 	{ action.say, {id =15, actor="voodoolady.voodoolady", lines = {d[40], d[41]}, animstart="talk", animend="idle"}},
-- 	{ action.animate_once, {id=17, actor="voodoolady.voodoolady_body", anim="raisehands", after={15}}},
-- 	{ action.animate, {id=18, actor="voodoolady.voodoolady_body", anim="idle"}},
-- 	{ action.say, {id =19, after={17}, actor="voodoolady.voodoolady", lines = {d[42], d[43], d[44], d[45]}, animstart="talk", animend="idle"}},
-- 	{ action.say, {id =20, actor="guybrush", lines = {d[46], d[47]}}},
-- 	{ action.say, {id =21, actor="voodoolady.voodoolady", lines = {d[48], d[49], d[50], d[51]}, animstart="talk", animend="idle"}},
-- 	{ action.delay, {id = 22, sec=1}},
-- 	{ action.activate, {id = 23, name="voodoolady.voodoolady", value=false}},
-- 	{ action.activate, {id = 24, name="voodoolady.voodoolady_body", value=false}},
-- 	{ action.delay, {id = 25, sec=0.5}},
-- 	{ action.say, {id =26, actor="guybrush", lines = {d[37]}}},
-- 	{ action.set_variable, {id=27, var="voodoolady_told_future", value=true}}
-- }

dialogues.storekeeper = {
	close = function()
		local s = script:new()
		s.actions = { {id=1, type="callfunc", func= function() refresh_inventory() end}}
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2,3,4} },
		[2] = {text= d[4], children={5,6,7}, active=function() return ((variables.inventory["shop.sword"] ~= nil) and (variables.sword_paid == false)) end, 
			script = {
				{ type = scumm.action.say, args = {actor="guybrush", lines = {d[4]}}},
				{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = {d[12]}}}
			}
		},
		[3] = {text= d[5], children = {9,10,11}, active=function() return ((variables.inventory["shop.shovel"] ~= nil) and (variables.shovel_paid == false)) end,
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
 		[5] = {text=d[13], active=true, children = 
 			function() 
	 			if (mi.checkfunds(100)) then 
	 				return {2,3,4} 
	 			else 
	 				return {8,7} 
	 			end
 			end, 
 			script = function() 
	 			local lines = nil
	 			if (mi.checkfunds(100)==true) then
 				    variables.sword_paid = true
 				    variables.inventory["pieces_of_eight"] = variables.inventory["pieces_of_eight"] - 100
 				    lines = {d[31], d[32]}
 			    else
    				lines = variables.know_sword_price and {d[21], d[22]} or {d[16], d[17]}
 	     		end
 			    variables.know_sword_price = true
 			    local actions = { 
 				    { type = scumm.action.say, args = {actor="guybrush", lines = {d[13]}}},
 				    { type = scumm.action.say, args = {actor="shop.shopkeeper", lines = lines}}
 				}
 				return actions
 			end
 		},
 		[6] = {text=d[14], active=true, children = {8,7}, script = function() 
 			local lines = variables.know_sword_price and {d[21], d[22]} or {d[16], d[17]}
 			variables.know_sword_price = true
 			local actions = { 
 				{ type = scumm.action.say, args = {actor="guybrush", lines = {d[14]}}},
 				{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines = lines}}
 			}
 			return actions
 			end
 		},
 		[7] = {text=d[15], active=true, script = {
			{ type = scumm.action.say, args = {actor="guybrush", lines = {d[15]}}},
			{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines={d[19]}}},
 			s1
 		}},
 		[8] = {text=d[18], children={2,3,4}, active=function() return (not mi.checkfunds(100)) end, script = {
			{ type = scumm.action.say, args = {actor="guybrush", lines = {d[18]}}},
			{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines={d[19]}}},
 			s1
 		} },
 		[9] = {text=d[13], active=true},
 		[10] = {text=d[14], active=true},
 		[11] = {text=d[15], active=true, script = {
			{ type = scumm.action.say, args = {actor="guybrush", lines = {d[15]}}},
			{ type = scumm.action.say, args = {actor="shop.shopkeeper", lines={d[19]}}},
 			s2
 		} },



	}	
}