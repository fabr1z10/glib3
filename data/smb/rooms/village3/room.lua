--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
--require ("actions")

local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
	{
        id = "door_shop",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=78, y=150, width=20, height=31, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=101, y=150, width=20, height=31, anchor = {0, 0}}}}             
		    }
        },
		
		}		
	},


},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 800, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
            {
              tag = "mainbg",
              pos = {0, 0, -5},
              gfx = { image="gfx/village3/bg1.png" }
            },
            {
              tag = "mainbg",
              pos = {166, 0, 2},
              gfx = { image="gfx/village3/bg2.png" }
            },
	        {
	          walkarea = { 
	            tag = "walkarea",
	            priority = 0,
	            target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {406,49,425,49,436,63,494,63,494,42,594,42,594,71,600,71,638,23,745,23,752,17,770,17,770,10,762,10,775,0,374,0,396,22}
	            },
	            scaling = {
	                depth = { 
	                    { rect = {0, 800, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 800, 0, 144}, dir = "y", bounds = {0.5, 0.5} } 
	                }
	            }
	          }
	        },
			make_hotspot { 
				x=754,
				y=10,
				width=30, 
				height=60, 
				offset={0,0},
				priority = 1, 
				object = "village3_archway"				
			},
	        make_hotspot { 
	            x = 659, 
	            y = 17,
	            width = 20, 
	            height = 31, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "door_village_shop",
	            gfx = { model="door_shop", anim = ((objects.door_village_shop.isopen() == true) and "open" or "close")  }
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
		children = {

		}
	}
}
}
-- end room

function room.init()
	variables._actionInfo:reset()
	local fromData = {
        village2 = { playerpos = {750, 16, 0}, anim = "idle_right", flip = true },
		--voodoolady = { playerpos = {231, 52, 0}, anim = "idle_right", flip = true }
    }
    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["village2"]
	end

    table.insert (room.scene[1].children, {
        tag = objects.guybrush.tag,
        pos = d.playerpos,
        gfx = { model = "guybrush", anim = d.anim, flip = d.flip },
        follow = { cam="maincam" },
        scaling = {}
    })

end

function room.afterstartup() 
refreshInventory()
end




