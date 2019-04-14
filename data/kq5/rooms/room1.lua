roomDefinition = {
	width = 320,
	height = 320,
	-- startTable = {
	-- 	village1 = { pos = items["lookout.stairs"].hotspot.walk_to, dir="north"},
	-- 	meleemap = { pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	-- },
	defaultroom = "meleemap",
	
}

room = scumm.factory.sci_room (roomDefinition)

--local d = strings.dialogues.lookout.text

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/001.png" }}},
	{ pos = {78, 0,2}, components = { { type="gfx", image="gfx/001a.png" }}},
	scumm.factory.walkarea {
		tag = "walkarea_1",
		priority = 1, 
		scale = { type="constant", value=0.5},
		depth = { type="linear_y", values= {0, 1, 190, 0} },
		shape = { 
			type = "poly", 
			outline = {0,71,27,72,61,70,65,63,74,63,88,65,103,70,113,73,123,79,135,82,149,82,
				163,93,176,92,171,82,172,81,180,82,190,88,209,85,222,82,236,80,246,78,263,82,272,90,
				310,90,303,80,271,74,250,69,244,65,253,61,241,59,245,55,221,47,213,46,180,43,183,48,
				163,46,152,44,149,41,136,41,123,44,115,39,107,33,107,28,113,27,116,29,145,23,150,21,
				192,20,221,22,251,22,285,23,294,35,282,42,265,45,270,52,285,55,314,59,319,59,319,9,
				125,10,109,14,101,14,83,1,76,0,0,1,0,18,6,15,27,11,46,9,56,9,63,13,79,17,88,19,74,22,47,27,17,28,0,31},
			holes = {
				{83,33,90,41,110,47,92,46,80,52,63,49,65,44,70,41,62,38,69,34},
				{185,81,184,62,210,59,212,79}
			}

		},
		children = {
        	scumm.factory.object {
				id="graham", 
				pos={160,50, 0}, 
				dir = "south",
				follow = false,
				--collide = args.collide
			},
			-- you can supply additional info to the walkareas for instance: do not scale this!
			{ pos = {109, 28, 0}, components = { { type="gfx", image="gfx/001b.png" }, { type="properties", additional_info = { walkarea_scale = false }}}},

		}
	},

	scumm.factory.sciobject { id="crispins_house"},
	-- scumm.factory.message { 
	-- 	pos = {160, 100, 2}, 
	-- 	message = "The red fox jumped over the ceiling. I am very happy because of it.", 
 --        font="ui", 
 --        size = 8,
	-- 	maxwidth = 100, 
 --        color = {0,0,0,255}, 
 --        bgcolor = {235, 186, 130, 255}, 
 --        padding = 16,
	-- 	border = {
	-- 		img = "gfx/border2.png", thickness=3
	-- 	},
	-- 	corner = {
	-- 		img = "gfx/border.png"
	-- 	} 
 --    }	

 --    { pos = {81, 16, 3}, components = { { type="gfx", image="gfx/lookout_2.png" }}},
 --    { pos = {294, 33, 3}, components = { { type="gfx", image ="gfx/lookout_3.png" }}},
 --    scumm.factory.walkarea {
	-- 	shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}}
 --    },
	-- scumm.factory.object { id = "lookout.stairs" },
	-- scumm.factory.object { id = "lookout.lookout" },
	-- scumm.factory.object { id = "lookout.fire" },
	-- scumm.factory.object { id = "lookout.path" },
})

-- local entry_cutscene = function() 
-- 	local actions = {
-- 		{ type = scumm.action.walkto, args = {tag="player", pos = {240, 30}}}
-- 	}
-- 	local s = script.make(actions)
-- 	s.name = "_walk"
-- 	monkey.play(s)
-- end

-- table.insert(room.initstuff, entry_cutscene)