local items = engine.items

roomDefinition = {
	width = 800,
	height = 144,
	startTable = {
		village2 = { walkarea="village3.walkarea", pos = items["village3.archway"].hotspot.walk_to, dir = "west"},
		shop = { walkarea = "village3.walkarea", pos = items["village3.shop_door"].hotspot.walk_to, dir="south"}
	},
	walkareas = {"village3.walkarea"},
	defaultroom = "village2",
	font_size = 8
}

room = scumm.factory.basic_room  (roomDefinition)

room:add( "main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="village3_1.png" }}},
    { pos = {166, 0, 2}, components = {{type="gfx", image="village3_2.png" }}},
	-- scumm.factory.walkarea { 
	-- 	shape = { 
	--         type = "poly", 
	--         outline = {406,49,425,49,436,63,494,63,494,42,594,42,594,71,600,71,638,23,745,23,752,17,770,17,770,10,762,10,775,0,374,0,396,22}
	--     },
	-- },
	scumm.factory.object { id = "village3.archway" },
	scumm.factory.object { id = "village3.alley" },
	scumm.factory.object { id = "village3.shop_door" },
	scumm.factory.object { id = "village3.church_door" },
})

room.onexit = function(nextRoom) 
	if (variables.chasing_shopkeeper == 1) then
		-- reset to 0 unless going to village2
		if (nextRoom ~= "village2") then
			variables.chasing_shopkeeper = 0
		end
	end
end

-- local addStorekeeper = function() 
-- 	if (variables.chasing_shopkeeper == true) then
-- 		local actions = {
-- 			{ type = action.create_object, args = { factory = scumm.factory.object, args = { id="village3.shopkeeper" }}},
-- 			{ type = scumm.action.walkto, args ={tag="village3.shopkeeper", pos = items["village3.archway"].hotspot.walk_to}},
-- 			{ type = action.activate, args = {tag="village3.shopkeeper", value=false}},
-- 			{ type = action.delay, args = {sec=10}},
-- 			{ type = action.set_variable, args = {var="chasing_shopkeeper", value=false}}
-- 		}
-- 		local s = script.make(actions)
-- 		monkey.play(s)
-- 	end


-- end

-- add the storekeeper if you are chasing him!
table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { pos = {669, 15, 0}, walkto = { items["village3.archway"].hotspot.walk_to }}))

-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- 	if (variables.met_fester == false) then
-- 		local s = script:new()
-- 		s.actions = {
-- 			action.delay { id=1, sec=5},
-- 			action.show_message { id = 2, message = strings.village3[1], color = items["fester"].text_color, pos= {594,67,1}},
-- 			action.delay { id=3, sec=5},
-- 			action.show_message { id = 4, message = strings.village3[2], color = items["fester"].text_color, pos= {594,67,1}},
-- 			action.delay { id=5, sec=5},
-- 			action.show_message { id = 6, message = strings.village3[3], color = items["fester"].text_color, pos= {594,67,1}},
-- 		}
-- 		s.loop = 1
-- 		monkey.play(s)	
-- 	end
-- end


