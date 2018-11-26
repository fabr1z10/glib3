require("template/room1")



local startPosTable = {
	village1 = { pos = {248, 0}, facing = "north", func = curry(walk_player_to, {pos={229, 36}} )},
	meleemap = { pos = {310, 52}, facing = "west", func = curry(walk_player_to, {pos={229, 36}} )}
}

room = generateBasicRoom { width = 320, height = 144, startTable = startPosTable, defaultroom = "village1" }

--local main = room.scene[1].children

-- set player location. It depends on the previous room
room:add_asset(sprites.lookout)
room:add_asset(sprites.fire)

local d = strings.dialogues.lookout.text

room:add( {
	{ pos = {0,0,-3}, components = { { type="gfx", image="gfx/lookout_1.png" }}},
    { pos = {81, 16, 3}, components = { { type="gfx", image="gfx/lookout_2.png" }}},
    { pos = {294, 33, 3}, components = { { type="gfx", image ="gfx/lookout_3.png" }}},
	factory.object.create { object = items.lookout.stairs },
	factory.object.create { object = items.lookout.lookout },
	factory.object.create { object = items.lookout.fire },
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
			}
      	}
	}

})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end



	--monkey.addEntity(items.inventorybutton.create ("ciao",100), c)
end


