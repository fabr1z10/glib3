--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
--require ("dialogues/lookout")

local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
    makeLookout(),
	makeStorekeeper(),
    {
        id = "fire",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 1, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 27, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 53, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 79, y = 1, width = 24, height = 32, anchor = {0, 0}}}}               
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
			bounds = {0, 0, 320, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
			{
				pos = {0, 0, -5},
				gfx = { image="gfx/lookout/bg1.png", width=320, height=144 }
			},
	        {
	            pos = {81, 16, 3},
	            gfx = { image="gfx/lookout/bg2.png" },
	            layer = 1
	        },
	        {
	            pos = {294, 33, 3},
	            gfx = { image="gfx/lookout/bg3.png" },
	            layer = 1
	        },
            {
                pos = {126, 52, -1},
                gfx = { model = "fire", anim = "default" },
                layer =1
            },--         
			{
                walkarea = { 
               	    tag = "walkarea",
					priority = 0,
			       	target = "player",
					shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
					scaling = {
					    depth = { 
						    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 0} } 
						},
                        scale = {
	                    	{ rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 1} } 
		                }
					}
		      	},
         	},
	        make_hotspot { 
                x=114, 
				y=36, 
				width=20, 
				height=47, 
				offset={-10, 0}, 
				priority = 1, 
				object = "lookout",
                gfx = { model="lookout", anim = "idle_right", flip = true }, 
				scaling = {} 
			},
	        make_hotspot { 
                x=221, 
				y=0, 
				width=50, 
				height=20, 
				priority = 1, 
				object = "stairs"
			},
	        make_hotspot { 
                x=288, 
				y=44, 
				width=32, 
				height=100, 
				priority = 1, 
				object = "path"
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
        village1 = { playerpos = {250, 0, 0}, anim = "idle_back" },
		meleemap = { playerpos = {314,52, 0}, anim = "idle_right", flip = true },
		--scummbar = { playerpos = {715, 13, 0}, anim = "idle_front" }
    }
	if (variables._previousroom ~= "village1" and variables.chase == 1) then
		variables.chase = 0
	end
	f = fromData[variables._previousroom]
	if (f == nil) then
		f = fromData["village1"]
	end
    -- add player
    table.insert (room.scene[1].children, {
        tag = "player",
        pos = f.playerpos,
        gfx = { model = "guybrush", anim = f.anim },
        scaling = {}
    })
end

function room.start()

end

function room.afterstartup() 
	print ("refreshing inventory")
	if (variables._previousroom == "village1") then
		local s = script:new()	
		s.actions[1] = { type="walkto", actor="player", pos={247, 30}}
	    monkey.play(s)
	elseif (variables._previousroom == "meleemap") then
		local s = script:new()	
		s.actions[1] = { type="walkto", actor="player", pos={247, 30}}
	    monkey.play(s)
	end

	if (variables.chase == 1) then
		local s = script:new("_chase")
		s.actions = {
			[1] = { type = "callfunc", func = curry (createObject, { 
				pos = {270, 62, 0},
				gfx = { model = "storekeeper", anim = "idle_right" },
				scaling = {},
				tag = "storekeeper"
			})},
			[2] = { type = "walkto", actor = "storekeeper", pos = {320, 75}, after={1} },
			[3] = { type="callfunc", func = curry(setActive, {id="storekeeper", active=false}), after={2} },
			[4] = {type="delay", sec=8, after={3}},
			[5] = {type="callfunc", func = function() variables.chase=0 end, after={4}},
		}
		monkey.play(s)
	end
	refreshInventory()
end



function prova2(a)
  a:parent():setcolor(255, 255, 255, 255)
  print "qua!!"
end



