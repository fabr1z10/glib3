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
        follow = { cam="maincam" },
        scaling = {}
    })

end

function room.afterstartup() 
refreshInventory()
end




