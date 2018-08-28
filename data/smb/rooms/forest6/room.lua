local dt = 0.1

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
			bounds = {0, 0, 320, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
	        {
	          pos = {0, 0, -5},
	          gfx = { image="gfx/forest6/bg1.png" },
	        },
			{
              walkarea = { 
                  tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {0,32}, {239, 32}, {320, 32},{239,70}}, edges = { 
					{0,1}, {1,2},{1,3}}},
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
                x=0,
				y=0,
				width=20, 
				height=144, 
				priority = 1, 
				object = "forest6_7"
			},
	        make_hotspot { 
                x=300, 
				y=0, 
				width=20, 
				height=144, 
				priority = 1, 
				object = "forest6_8"
			},
	        make_hotspot { 
                x=227,
				y=70,
				width=30, 
				height=70, 
				priority = 1, 
				object = "forest6_5"
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
        forest5 = { playerpos = objects.forest6_5.pos, anim = "idle_front", flip=false },
        forest7 = { playerpos = objects.forest6_7.pos, anim = "idle_right", flip=false },
        forest8 = { playerpos = objects.forest6_8.pos, anim = "idle_right", flip=true },

    }
    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["forest5"]
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




