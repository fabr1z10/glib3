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
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 496, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
        	{
              tag = "mainbg",
              pos = {0, 0, -5},
              gfx = { image="gfx/clearing/bg1.png" }
            },
       		{
              tag = "mainbg",
              pos = {441, 0, 2},
              gfx = { image="gfx/clearing/bg2.png" }
            },
			{
                walkarea = { 
               	    tag = "walkarea",
					priority = 0,
			       	target = "player",
					shape = { type = "poly", outline = {496,38,496,0, 283, 0, 283, 20, 315, 28,315, 44, 229, 31, 92, 31, 41, 64,54, 75, 80, 64, 115, 58, 119, 48,
									165, 53, 180,64, 214, 64, 229, 33, 315, 46, 400,38}},
					scaling = {
					    depth = { 
						    { rect = {0, 496, 0, 144}, dir = "y", bounds = {1, 0} } 
						},
                        scale = {
	                    	{ rect = {0, 496, 0, 144}, dir = "y", bounds = {1, 1} } 
		                }
					}
		      	},
         	},
	        make_hotspot { 
                x=458, 
				y=0, 
				width=38, 
				height=100, 
				priority = 1, 
				object = "clearing_path"
			},
	        make_hotspot { 
                x=48, 
				y=61, 
				width=120, 
				height=60, 
				priority = 1, 
				object = "circus_tent"
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
		meleemap = { playerpos = {490,24, 0}, anim = "idle_right", flip = true },
		circus = { playerpos ={82,69,0}, anim = "idle_front", flip=false }
    }

	f = fromData[variables._previousroom]
	if (f == nil) then
		f = fromData["meleemap"]
	end
    -- add player
    table.insert (room.scene[1].children, {
        tag = "player",
        pos = f.playerpos,
        gfx = { model = "guybrush", anim = f.anim, flip = f.flip },
        follow = { cam="maincam" },
        scaling = {}
    })
end

function room.afterstartup() 
refreshInventory()
end




