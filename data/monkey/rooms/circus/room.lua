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
	makeGreenClown(),
    {
        id = "explosion",
        sheet = "gfx/anims3.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 287, y = 46, width = 22, height = 20, anchor = {-246, -56}}}},
                { duration = dt, quads = { { x = 313, y = 44, width = 36, height = 36, anchor = {-244, -43}}}},
                { duration = dt, quads = { { x = 352, y = 45, width = 48, height = 41, anchor = {-244, -40}}}},
                { duration = dt, quads = { { x = 404, y = 46, width = 44, height = 46, anchor = {-244, -38}}}},               
				{ duration = dt, quads = { { x = 363, y = 108, width = 46, height = 50, anchor = {-244, -40}}, {x=320,y=97,width=32,height=29,anchor={-201,-72}}}},
				{ duration = dt, quads = { { x = 414, y = 99, width = 51, height = 48, anchor = {-244, -36}}, {x=363,y=87,width=33,height=20,anchor={-200,-78}}}},
                { duration = dt, quads = { { x = 337, y = 169, width = 48, height = 43, anchor = {-244, -35}}}},               
                { duration = dt, quads = { { x = 393, y = 165, width = 44, height = 46, anchor = {-244, -34}}}},               
			}
        }
        }
    },
    {
        id = "flyingguy",
        sheet = "gfx/anims3.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 322, y = 217, width = 20, height = 22, anchor = {-213, -75}}}},
				{ duration = dt, quads = { { x = 347, y = 217, width = 26, height = 16, anchor = {-190, -89}}}},
				{ duration = dt, quads = { { x = 377, y = 217, width = 26, height = 27, anchor = {-169, -96}}}},
				{ duration = dt, quads = { { x = 406, y = 217, width = 37, height = 24, anchor = {-148, -100}}}},
				{ duration = dt, quads = { { x = 447, y = 217, width = 31, height = 22, anchor = {-133, -98}}}},
				{ duration = dt, quads = { { x = 481, y = 217, width = 25, height = 24, anchor = {-111, -92}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -89}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -84}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -82}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -70}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -65}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -60}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -55}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -50}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -45}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -40}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -35}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -29}}}},
			}
        },
		{
			name="end",
			frames =
            { 
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -29}}}}
			}
		}
        }
    }
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
              tag = "mainbg",
              pos = {233, 1, 0.99},
              gfx = { image="gfx/circus/bg3.png" }
            },
        	{
              tag = "mainbg",
              pos = {247, 17, 0.99},
              gfx = { image="gfx/circus/bg4.png" }
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
	                    	{ rect = {0, 368, 0, 25}, dir = "y", bounds = {1, 1} },
	                    	{ rect = {0, 368, 25, 34}, dir = "y", bounds = {1, 0.57} },
 
		                }
					}
		      	},
         	},
			{
				pos = {37, 34, 0},
				gfx = { model = "purpleclown", anim = "idle_right" },
				scaling = {},
				tag = "purpleclown",
			    hotspot = {
			        group = 1,
			        priority = 1, 
			        shape = { type = "rect", width=20, height=40, offset={-12,0}},
			        onenter = curry(hoverOn, "purple_clown"),
        			onleave = hoverOff,
        			onclick = runAction
			    },
			},
			{
				pos = {51, 34, 0},
				gfx = { model = "greenclown", anim = "idle_right", flip = true },
				scaling = {},
				tag = "greenclown",
			    hotspot = {
			        group = 1,
			        priority = 1, 
			        shape = { type = "rect", width=20, height=40, offset={-12,0}},
			        onenter = curry(hoverOn, "green_clown"),
        			onleave = hoverOff,
        			onclick = runAction
			    },

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




