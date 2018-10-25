local dt = 0.1

-- set player start position
local startPositionTable = {
    lookout = { pos = objects.cliffside.pos, anim = "idle_front" },
	scummbar = { pos = objects.village1_door.pos, anim = "idle_front" },
	village2 = { pos = objects.archway.pos, anim = "idle_right", flip=true },
	default = { pos = objects.cliffside.pos, anim = "idle_front" },
}

local startPosition = startPositionTable[variables._previousroom]
if (startPosition == nil) then
	startPosition = startPositionTable.default
end


room = {
engines = {
	{ type = "hotspotmanager" },
	{ type = "scheduler" }
},
assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
	makeStorekeeper(),
    {
        id = "door",
        sheet = "gfx/sprite2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 33, y = 35, width = 31, height = 52, anchor = {0, 0}}}}              
		    }
        },
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 1, y = 35, width = 31, height = 52, anchor = {0, 0}}}}              
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
			bounds = {0, 0, 1008, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
            {
              pos = {0, 0, -5},
              gfx = { image="gfx/village1/bg1.png" }
            },
			makePlayer(startPosition, true),       
            {
              walkarea = { 
                  tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {770, 13}, {780,34}, {1000,34} }, edges = { 
					{0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7},{7,8} }},
                  scaling = {
					    depth = { type="linear_y", values = {0, 1, 144, 0}},
                        scale = { type="linear_y", values = {0, 1, 144, 0.2}}
                }
              }
            },
	        make_hotspot { 
                x=0, 
				y=58, 
				width=74, 
				height=50, 
				priority = 1, 
				object = "cliffside"
			},
	        make_hotspot { 
                x=258, 
				y=26, 
				width=24, 
				height=26, 
				priority = 1, 
				object = "poster"
			},
			make_hotspot { 
				x=699, 
				y=7, 
				width=31, 
				height=47, 
				offset={0,5},
				priority = 1, 
				object = "village1_door", 
				gfx = { 
					model="door", 
					anim = ((objects.village1_door.isopen() == true) and "open" or "close") 
				}
			},
	        make_hotspot { 
                x=992, 
				y=30, 
				width=16, 
				height=40, 
				priority = 1, 
				object = "archway"
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
    -- previous room was lookout
end


function room.start() 
	if (variables._previousroom == "lookout" or variables._previousroom=="meleemap") then
		local s = script:new()	
		s.actions[1] = { type="walkto", actor="player", pos={120, 80}}
	    monkey.play(s)
	end

end


function room.afterstartup() 
	refreshInventory()
	storeKeeperChase(820, 34, "idle_right", false, objects.cliffside.pos, "village2")
end



