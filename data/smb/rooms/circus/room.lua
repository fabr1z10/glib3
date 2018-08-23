--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")

local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
	makePurpleClown(),
	makeGreenClown()
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 368, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
        	{
              tag = "mainbg",
              pos = {0, 0, -5},
              gfx = { image="gfx/circus/bg1.png" }
            },
        	{
              tag = "mainbg",
              pos = {259, 1, 0.99},
              gfx = { image="gfx/circus/bg2.png" }
            },
			{
                walkarea = { 
               	    tag = "walkarea",
					priority = 0,
			       	target = "player",
					shape = { type = "poly", outline = {0,35,368,35,368,0,0,0}},
					scaling = {
					    depth = { 
						    { rect = {0, 368, 0, 144}, dir = "y", bounds = {1, 0} } 
						},
                        scale = {
	                    	{ rect = {0, 368, 0, 144}, dir = "y", bounds = {1, 1} } 
		                }
					}
		      	},
         	},
			{
				pos = {37, 34, 0},
				gfx = { model = "purpleclown", anim = "idle_right" },
				scaling = {},
				tag = "purpleclown"
			},
			{
				pos = {51, 34, 0},
				gfx = { model = "greenclown", anim = "idle_right", flip = true },
				scaling = {},
				tag = "greenclown"
			},
	        make_hotspot { 
                x=252, 
				y=30, 
				width=60, 
				height=90, 
				priority = 1, 
				object = "outside"
			},
		}
	},
	makescummui1(),
	{
		tag = "diag",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 200},
			bounds = {0, 0, 320, 200},
			viewport = {0, 0, 320, 200}
		},
		children = {}
	}
}
}
-- end room

function room.init()
	variables._actionInfo:reset()
	local fromData = {
		clearing = { playerpos = {279, 32, 0}, anim = "idle_right", flip = true },
    }

	f = fromData[variables._previousroom]
	if (f == nil) then
		f = fromData["clearing"]
	end
    -- add player
    table.insert (room.scene[1].children, {
        tag = "player",
        pos = f.playerpos,
        gfx = { model = "guybrush", anim = f.anim, flip = f.flip },
        --follow = { cam="maincam" },
        scaling = {}
    })

end

function room.afterstartup() 
	refreshInventory()
	local s = script:new("_circus")
	local d = strings.dialogues.fettbros.text
	if (variables.talkedToFettuccini == false) then
		s.actions = {
			[1] = { type="callfunc", func=startScript },
			[2] = { type= "walkto", actor="player", pos ={178, 9}, after={1} },
			[3] = say {character = "purple_clown", lines = {d[1]}, after={1}},
			[4] = say {character = "green_clown",lines = {d[2]}, after={3}},
			[5] = say {character = "purple_clown",lines = {d[3]}, after={4}},
			[6] = say {character = "green_clown",lines = {d[4]}, after={5}},
			[7] = say {character = "purple_clown",lines = {d[5]}, after={6}},
			[8] = say {character = "green_clown",lines = {d[5]}, after={7}},
			[9] = say {character = "purple_clown",lines = {d[6]}, after={8}},
			[10] = say {character = "green_clown",lines = {d[7]}, after={9}},
			[11] = say {character = "purple_clown",lines = {d[8]}, after={10}},
			[12] = say {character = "green_clown",lines = {d[9]}, after={11}},
			[14] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=1 }), after = {12} }
		}
	else 
		s.actions = {
			[1] = { type="callfunc", func=startScript },
			[2] = { type= "walkto", actor="player", pos ={178, 9}, after={1} },
			[3] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=1 }), after = {2} }
		}
	end
	
	local s1 = script:new()
	s1.actions = {
		[1] = say {character = "purple_clown",lines = {d[10]}},
		[2] = say {character = "green_clown",lines = {d[11]}, after={1}},
		[3] = say {character = "purple_clown",lines = {d[12]}, after={2}},
		[4] = say {character = "green_clown",lines = {d[13]}, after={3}},
		[5] = say {character = "purple_clown",lines = {d[14]}, after={4}},
		[6] = say {character = "green_clown",lines = {d[15]}, after={5}},
		[7] = say {character = "purple_clown",lines = {d[16]}, after={6}},
		[8] = say {character = "green_clown",lines = {d[17]}, after={7}},
		[9] = say {character = "purple_clown",lines = {d[18]}, after={8}},
		[10] = say {character = "green_clown",lines = {d[19]}, after={9}},
		[11] = say {character = "purple_clown",lines = {d[20]}, after={10}},
		[12] = say {character = "green_clown",lines = {d[21]}, after={11}},
		[13] = say {character = "purple_clown",lines = {d[22]}, after={12}},
		[14] = say {character = "green_clown",lines = {d[23]}, after={13}},
		[15] = say {character = "purple_clown",lines = {d[5]}, after={14}},
		[16] = say {character = "green_clown",lines = {d[5]}, after={15}},
		[17] = say {character = "purple_clown",lines = {d[24]}, after={16}},
		[18] = say {character = "green_clown",lines = {d[25]}, after={17}},
		[19] = say {character = "purple_clown",lines = {d[5]}, after={18}},
		[20] = say {character = "green_clown",lines = {d[5]}, after={19}},
		[21] = say {character = "purple_clown",lines = {d[26]}, after={20}},
		[22] = say {character = "green_clown",lines = {d[27]}, after={21}},
		[23] = say {character = "purple_clown",lines = {d[28]}, after={22}},
		[24] = say {character = "green_clown",lines = {d[22], d[23]}, after={23}},
		[25] = say {character = "purple_clown",lines = {d[5]}, after={24}},
		[26] = say {character = "green_clown",lines = {d[5]}, after={25}},
		[27] = say {character = "purple_clown",lines = {d[5]}, after={26}},
		[28] = say {character = "green_clown",lines = {d[5]}, after={27}}
	}
	s:push { script = s1, at ="end", id="main" }
	s.loop = s:getid("main", 1)
	monkey.play(s)
end




