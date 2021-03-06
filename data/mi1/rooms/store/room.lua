local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { 'store.walkarea', 'store.walkarea.keeper'},
	collide=true,
	id = 'store'
}

room = scumm.factory.room_ui (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="shop.png" }}},
	 	{ pos = {239, 0, 0}, components = { { type="gfx", image="shop3.png" }}},	-- barrels
		scumm.factory.object { id = "shop.door" },
		scumm.factory.object { id="shop.sword" },
	    scumm.factory.object { id="shop.shovel" }
	}
)

room:add ( "store.walkarea",
	{ 
	 	{ pos = {117, 0, 1}, components = { { type="gfx", image="shop2.png" }}},	-- barrels
	    
	}
)	
-- room:add ( "store.walkarea.keeper",
--  	{ 
--  	    scumm.factory.object { id="storekeeper" },
-- 	}
-- )	
-- room:add( {
-- 	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/shop.png" }}},
-- 	scumm.factory.walkarea { shape = { type = "poly", outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
-- 		290,2,290,20,320,20,320,0,62,0}}},
-- 	--scumm.factory.object { id = "storekeeper" },
-- 	scumm.factory.object { id = "shop.sword" },
-- 	scumm.factory.object { id = "shop.shovel" },
-- })



local storekeeper = function() 
 	-- what we do here depends on shopkeeper_away
 	-- 0 means. Shopkeeper in
 	-- 1 means. Shopkeeper just returned from sword master
 	-- >1 means Shopkeeper away, decrement
 	if (variables.shopkeeper_away > 1) then
 		-- don't put the storekeeper in
 		variables.shopkeeper_away = variables.shopkeeper_away - 1
 		variables.chasing_shopkeeper = false
 		local actions = {
 			{ type = action.create_object, args = {factory=scumm.factory.object, args = { id = "shop.sign"}}},
 			{ type = action.create_object, args = {factory=scumm.factory.object, args = { id = "shop.bell"}}}
 		}	
 		local s = script.make(actions)
 		monkey.play(s)
 	else 
 		local d = strings.shop
 		local d1 = strings.dialogues.storekeeper
 		local s = nil
 		local startLines  ={}
 		if (variables.shopkeeper_away == 0) then 
 			startLines = {d[1]}
 		else
 			variables.shopkeeper_away = variables.shopkeeper_away - 1
 			startLines = {d1[51], d1[52], d1[53], d1[54], d1[55]}
 		end

 		local actions = {
 			{ type = action.create_object, args = {factory=scumm.factory.object, args = { id = "storekeeper"}, parent ="store.walkarea.keeper"}},
 			{ type = scumm.action.say, args = {tag="storekeeper", lines = startLines}},
 			{ ref=1, type = action.delay, args = {sec=5}},
 			{ type = scumm.action.say, args = {tag="storekeeper", lines = {d[10]}}},
 			{ type = action.delay, args = {sec=5}},
 			{ type = scumm.action.say, args = {tag="storekeeper", lines = {d[5]}}},
 			{ type = action.delay, args = {sec=5}},
 			{ type = scumm.action.say, args = {tag="storekeeper", lines = {d[4]}}},
 			{ type = action.delay, args = {sec=5}},
 			{ type = scumm.action.say, args = {tag="storekeeper", lines = {d[3]}}},
 			{ type = action.delay, args = {sec=5}},
 			{ type = scumm.action.say, args = {tag="storekeeper", lines = {d[2]}}},
		}
 		local s = script.make(actions, 1)
 		s.name = "_shopkeeper"
 		monkey.play(s)
 	end
end

table.insert(room.initstuff, storekeeper)

-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- 	local d = strings.shop
-- 	local s = script:new("shopkeeper")
-- 	s.actions = {
-- 		action.say { id=1, tag="storekeeper", lines = {d[1]} },
-- 		action.delay { id=2, sec=5},
-- 		action.say { id=3, tag="storekeeper", lines = {d[10]} },
-- 		action.delay { id=4, sec=5},
-- 		action.say { id=5, tag="storekeeper", lines = {d[5]} },
-- 		action.delay { id=6, sec=5},
-- 		action.say { id=7, tag="storekeeper", lines = {d[4]} },
-- 		action.delay { id=8, sec=5},
-- 		action.say { id=9, tag="storekeeper", lines = {d[3]} },
-- 		action.delay { id=10, sec=5},
-- 		action.say { id=11, tag="storekeeper", lines = {d[2]} },
-- 	}
-- 	s.loop = 2
-- 	monkey.play(s)
-- end


