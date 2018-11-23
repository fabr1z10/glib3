require("template/room1")

room = generateBasicRoom { width = 320, height = 144 }

--local main = room.scene[1].children

-- set player location. It depends on the previous room
room:add_asset(sprites.lookout)

function say2(args)
return { type="say", actor=args.actor.tag, lines = args.lines, offset = args.actor.text_offset, color = args.actor.text_color, after = args.after }
end
function ciaooo() 
	print ("IIIDIDIDI")
	print (obj.lookout.text)
	local s = script:new()
	s.actions = {
		[1] = say2 { actor = objects.guybrush, lines= {strings.dialogues.lookout.text[1] }},
		[2] = say2 { actor = obj.lookout, lines = {strings.dialogues.lookout.text[2]}, after= {1} }
	}
	print ("DIDIDIDIDI!!!")
	return s
end


dialogues.lookout = {
	-- root
	[1] = { children = {2, 3, 4, 5} },
	[2] = { text = strings.dialogues.lookout.text[1], script = ciaooo },
	[3] = { text = strings.dialogues.lookout.text[2] },
	[4] = { text = strings.dialogues.lookout.text[3] },
	[5] = { text = strings.dialogues.lookout.text[4] },
}



-- the local objects
local obj = {
	stairs = {
		text = strings.objects.stairs,
		pos = {250, 0, 0},
		walk_to = {250, 0}, 
		face = "south",
		size = {10, 10},			
		actions = {
			walk = curry(changeRoom, "village1")
		}
	},
	lookout = {
		text = strings.objects.lookout,
		pos = {114, 36, 0},
		walk_to = {134, 36},
		size = {20, 47},
		face = "west",
		model ="lookout",
		anim ="idle_right",
		flip = true,
		actions = {
			talk = curry(start_dialogue, "lookout")
		}
	}
}






room:add( {
	{ pos = {0,0,-3}, components = { { type="gfx", image="gfx/lookout_1.png" }}},
    { pos = {81, 16, 3}, components = { { type="gfx", image="gfx/lookout_2.png" }}},
    { pos = {294, 33, 3}, components = { { type="gfx", image ="gfx/lookout_3.png" }}},
	items.player.create { pos={100, 100}, model="guybrush", facing ="east" },
	items.object.create { object = obj.stairs },
	items.object.create { object = obj.lookout },
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


-- engines = {
-- 	{ type = "hotspotmanager" },
-- 	{ type = "scheduler" }
-- },
-- assets = {
-- 	sprites.arrowup,
-- 	sprites.arrowdown,
-- 	sprites.guybrush
-- },
-- scene = {

-- 	{
-- 		tag = "main",
-- 		camera = {
-- 			tag = "maincam",
-- 			type="ortho",
-- 			size = {320, 144},
-- 			bounds = {0, 0, 320, 144},
-- 			viewport = {0, 56, 320, 144}
-- 		},
-- 		children = {
-- 			{ pos = {0,0,-3}, components = { { type="gfx", image="gfx/lookout_1.png" }}},
-- 	        { pos = {81, 16, 3}, components = { { type="gfx", image="gfx/lookout_2.png" }}},
-- 	        { pos = {294, 33, 3}, components = { { type="gfx", image ="gfx/lookout_3.png" }}},
-- 			items.object.create { object = objects.lookout.stairs },
-- 			items.player.create { pos={100, 100}, model="guybrush", facing ="east" },
-- 			{
-- 				pos = {0,0,0},
-- 				components = {
--                 	{ 
-- 						type ="walkarea",
-- 						priority = 0,
-- 			       		target = "player",
-- 						shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
-- 					}
-- 		      	}
-- 			}
-- 		}
-- 	},
-- 	{
-- 		tag = "main",
-- 		camera = {
-- 			tag = "maincam",
-- 			type="ortho",
-- 			size = {320, 56},
-- 			bounds = {0, 0, 320, 56},
-- 			viewport = {0, 0, 320, 56}
-- 		},
-- 		children = {
-- 			{
-- 		    	tag = "currentaction",
-- 		    	pos={160,48,0},
-- 				components = {
-- 		    		{ type="text", id = "ciao", font="ui", align = "bottom", color = config.ui_currentaction_color}
-- 				}
-- 		    },
-- 			items.verbbutton.create {pos={2, 40}, verb = config.verbs.open},
-- 			items.verbbutton.create {pos={2, 32}, verb = config.verbs.close},
-- 			items.verbbutton.create {pos={2, 24}, verb = config.verbs.push},
-- 			items.verbbutton.create {pos={2, 16}, verb = config.verbs.pull},
-- 			items.verbbutton.create {pos={48, 40}, verb = config.verbs.walk},
-- 			items.verbbutton.create {pos={48, 32}, verb = config.verbs.pick},
-- 			items.verbbutton.create {pos={48, 24}, verb = config.verbs.talk},
-- 			items.verbbutton.create {pos={48, 16}, verb = config.verbs.give},
-- 			items.verbbutton.create {pos={100, 40}, verb = config.verbs.use},
-- 			items.verbbutton.create {pos={100, 32}, verb = config.verbs.look},
-- 			items.verbbutton.create {pos={100, 24}, verb = config.verbs.turnon},
-- 			items.verbbutton.create {pos={100, 16}, verb = config.verbs.turnoff},
-- 			{
-- 				type = "textview", 
-- 				tag="inventory",
-- 				pos = {150, 0},
-- 				size = {170, 48},
-- 				font_size = 8,
-- 				lines = 6,
-- 				deltax = 26,
-- 				factory = items.inventorybutton.create
-- 				-- components = {
-- 				-- 	{ 
-- 				-- 		type="textview",
-- 				-- 		width = 170.0,
-- 				-- 		height = 48.0,
-- 		  --               --viewport = {150, 0, 170, 48},
-- 		  --               size = 8,
-- 				-- 		lines = 6,
-- 				-- 		deltax = 26,
-- 				-- 		factory = items.inventorybutton.create
-- 				-- 	}
-- 				-- }
-- 			}

-- 			--items.button.create { pos ={2, 40}, font="ui", text="Open", align="bottomleft", color = config.ui_unselected_color, size = 8, priority = 1,
-- 		--		onenter = curry2(changecolor, config.ui_selected_color), onleave = curry2(changecolor, config.ui_unselected_color) }
-- 			--items.button.create { pos ={0,0}, font="ui", text="ciao", size = 8, priority = 1, align="bottomleft"},
-- 			--items.button.create { pos ={320,0}, font="ui", text="ciao", size = 8, priority = 1, align="bottomright"},
-- 			--items.button.create { pos ={320,56}, font="ui", text="ciao", size = 8, priority = 1, align="topright"},

-- 		}
-- 	}

-- }


-- }

function room.afterstartup() 
	setverb (config.verbs.walk)

	local c = monkey.getEntity("inventory")
	c:addtext ( { text="ciao" })
	c:addtext ( { text="come" })
	c:addtext( { text ="stai" })
	c:addtext({ text="alleelelel"})
	c:addtext({ text="stronzo" })
	c:addtext( { text="duro"})
	c:addtext( {text="anvedi"})


	--monkey.addEntity(items.inventorybutton.create ("ciao",100), c)
end


