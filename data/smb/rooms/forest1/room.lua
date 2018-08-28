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
	          gfx = { image="gfx/forest1/bg1.png" },
	        },
			{
              walkarea = { 
                  tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {237, 70}, {237, 32}, {320, 32}, {101,32}, {154,32}, {154,70} }, edges = { 
					{0,1}, {1,2}, {1,4}, {4,3},{4,5}}},
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
                x=223,
				y=59,
				width=20, 
				height=40, 
				priority = 1, 
				object = "forest1_2"
			},
	        make_hotspot { 
                x=140, 
				y=59, 
				width=20, 
				height=40, 
				priority = 1, 
				object = "forest1_3"
			},
	        make_hotspot { 
                x=310, 
				y=0, 
				width=10, 
				height=144, 
				priority = 1, 
				object = "forest_exit"
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
        meleemap = { playerpos = objects.forest_exit.pos, anim = "idle_right", flip=true },
		forest2 = { playerpos = objects.forest1_2.pos, anim = "idle_front", flip=false },
    }
	if (variables._previousroom ~= "meleemap" and variables.chase == 1) then
		variables.chase = 0
	end	
    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["meleemap"]
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
	if (variables.chase == 1) then
		local s = script:new("_chase")
		s.actions = {
			[1] = { type = "callfunc", func = curry (createObject, { 
				pos = {153, 50, 0},
				gfx = { model = "storekeeper", anim = "idle_right", flip=true },
				scaling = {},
				tag = "storekeeper"
			})},
			[2] = { type = "walkto", actor = "storekeeper", pos = {153, 70}, after={1} },
			[3] = { type="callfunc", func = curry(setActive, {id="storekeeper", active=false}), after={2} },
			[4] = {type="delay", sec=8, after={3}},
			[5] = {type="callfunc", func = function() variables.chase=0 end, after={4}},
		}
		monkey.play(s)
	end
end




