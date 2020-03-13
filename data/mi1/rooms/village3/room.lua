local items = engine.items

roomDefinition = {
	width = 800,
	height = 144,
	walkareas = { 'village3.walkarea'},
	collide=true,
	id = 'village3'
}

room = scumm.factory.room_ui  (roomDefinition)

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
	scumm.factory.object { id = "village3.door.shop" },
	scumm.factory.object { id = "village3.door.church" },
--	scumm.factory.object { id = "village3.jail" },
})

-- room.onexit = function(nextRoom) 
-- 	if (variables.chasing_shopkeeper == 1) then
-- 		-- reset to 0 unless going to village2
-- 		if (nextRoom ~= "village2") then
-- 			variables.chasing_shopkeeper = 0
-- 		end
-- 	end
-- end

table.insert(
	room.initstuff, 
	glib.curry (mi.addStorekeeper, { 
		from = 'store', 
		pos = {678, 15}, 
		dir = 'e', 
		parent = 'village3.walkarea',
		walkto = { mi.rooms.village3.to_village2 } 
	})) 
-- 	pos = {669, 15, 0}, 
-- 	parent="village3.walkarea", 
-- 	from = "store",
-- 	walkto = { items["village3.archway"].hotspot.walk_to }
-- }))

