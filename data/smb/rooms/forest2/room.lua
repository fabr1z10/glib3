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
	makeStorekeeper()
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
	          gfx = { image="gfx/forest2/bg1.png" },
	        },
			{
              walkarea = { 
                  tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {257, 70}, {257, 32}, {320, 32}, {0,32}, {276,32}, {276,13} }, edges = { 
					{0,1}, {1,4}, {1,3},{4,2},{4,5}}},
                  scaling = {
                    depth = { 
                        { rect = {0, 320, 0, 200}, dir = "y", bounds = {1, 1} } 
                    },
                    scale = {
                        { rect = {0, 320, 0, 200}, dir = "y", bounds = {1, 1} } 
                    }
                }
              }
			},
	        make_hotspot { 
                x=300,
				y=0,
				width=20, 
				height=144, 
				priority = 1, 
				object = "forest2_1"
			},
	        make_hotspot { 
                x=239, 
				y=70, 
				width=20, 
				height=50, 
				priority = 1, 
				object = "forest2_4"
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
        forest1 = { playerpos = {310, 32, 0}, anim = "idle_right", flip=true },
        forest4 = { playerpos = objects.forest2_4.pos, anim = "idle_front", flip=true },
    }
    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["forest1"]
	end

    table.insert (room.scene[1].children, {
        tag = objects.guybrush.tag,
        pos = {d.playerpos[1], d.playerpos[2], 0},
        gfx = { model = "guybrush", anim = d.anim, flip = d.flip },
        follow = { cam="maincam" },
        scaling = {}
    })

end

function room.afterstartup() 
	refreshInventory()

end




