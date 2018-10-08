local dt = 0.1

local centerPos = {247, 40}

-- set player start position
local startPositionTable = {
	village1 = { pos = objects.stairs.pos, anim = "idle_back" },
	meleemap = { pos = objects.path.pos, anim = "idle_right", flip = true },
	default = { pos = objects.path.pos, anim = "idle_right", flip = true },
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
	        },
	        {
	            pos = {294, 33, 3},
	            gfx = { image="gfx/lookout/bg3.png" },
	          
	        },
            {
                pos = {126, 52, -1},
                gfx = { model = "fire", anim = "default" },
            },--  
			makePlayer(startPosition, false),       
			{
                walkarea = { 
               	    tag = "walkarea",
					priority = 0,
			       	target = "player",
					shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
					scaling = {
					    depth = { type="linear_y", values = {0, 1, 144, 0}},
                        scale = { type="linear_y", values = {0, 1, 144, 1}}
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
end

function room.start()

end

function room.afterstartup() 
	if (variables._previousroom == "village1") then
		local s = script:new()	
		s.actions[1] = { type="walkto", actor="player", pos=centerPos }
	    monkey.play(s)
	else --if (variables._previousroom == "meleemap") then
		local s = script:new()	
		s.actions[1] = { type="walkto", actor="player", pos=centerPos }
	    monkey.play(s)
	end
	refreshInventory()
	storeKeeperChase(270, 62, "idle_right", false, {320, 75}, "village1")
end



