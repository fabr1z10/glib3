roomDefinition = {
	width = 320,
	height = 320,
	-- startTable = {
	-- 	village1 = { pos = items["lookout.stairs"].hotspot.walk_to, dir="north"},
	-- 	meleemap = { pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	-- },
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 190, 0} },
	collide=true

}

room = scumm.factory.sci_room (roomDefinition)

--local d = strings.dialogues.lookout.text

room:add( {
	{ pos = {0, 0,-1}, components = { { type="gfx", image="gfx/003.png" }}},
	{ pos = {0, 0, 0}, components = { { type="gfx", image="gfx/003a.png" }}},
	scumm.factory.walkarea {
		tag = "walkarea_1",
		priority = 0, 
		scale = { type="constant", value=0.5},
		depth = { type="constant", value=-0.5},
		handler = function(walkarea_from, x, y) 
			print ("sti cazzi! Cerco di andare da walkarea " .. walkarea_from .. " a walk1(" .. tostring(x) .. ", " .. tostring(y)) 
			local actions = {
			 	{ type = scumm.action.walkto, args = {tag="player", pos ={70,120}}},
			 	{ type = scumm.action.turn, args={tag="player", dir="north"}},
			 	{ type = action.treemove, args = {tag="player", parent="walkarea_2_back"}},
			 	{ type = action.move, args = {tag="player", to ={70,50}}},
			 	{ type = action.treemove, args = {tag="player", parent="walkarea_1"}},
			 	{ type = scumm.action.walkto, args = {tag="player", pos ={x,y}}},			 	
			}
			local s = script.make(actions)
			s.name="_walk"
			monkey.play(s)
		end,
		shape = { 
			type = "poly", 
			outline = {0,0,0,110,30,124,52,124,77,119,103,115,142,89,152,86,152,0}


		}
	},
	scumm.factory.walkarea {
		tag = "walkarea_2",
		priority = 1, 
		shape = { 
			type = "poly", 
			outline = {188,86,248,66,266,62,320,37,320,0,0,0,0,50,40,70,89,78,152,86}
		},
		--handler = 10,
		depth = { type="constant", value=0.5},		
		children = {
        	scumm.factory.object {
				id="graham", 
				pos={160,50, 0}, 
				dir = "south",
				follow = false,
				--collide = args.collide
			}
		}
	},
	scumm.factory.walkarea {
		tag = "walkarea_2_back",
		priority = 1, 
		shape = { 
			type = "poly", 
			outline = {188,86,248,66,266,62,320,37,320,0,0,0,0,50,40,70,89,78,152,86}
		},
		--handler = 10,
		depth = { type="constant", value=-0.5},				
	},

	--cumm.factory.trap { pos ={10, 0, 0}, tag="troll_sensor", shape = {type="rect", width=10, height = 144}, onenter = function() print("ciao stronzo") end}
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