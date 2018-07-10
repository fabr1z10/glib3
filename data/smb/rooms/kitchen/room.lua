--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
require ("dialogues/lookout")

local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
    {
        id = "door_to_bar",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 222, y = 280, width = 37, height = 53, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 183, y = 280, width = 37, height = 53, anchor = {0, 0}}}}}}
        }
    },
    {
        id = "door_to_pier",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 399, y = 280, width = 32, height = 60, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 365, y = 280, width = 32, height = 60, anchor = {0, 0}}}}}}
        }
    },
	{
		id = "kitchen_table",
		sheet = "gfx/anims.png",
		type="sprite",
		ppu = 1,
		animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 126, y = 208, width = 33, height = 26, anchor = {0, 0}}}}}}
		}
	},
	{
		id ="potostew",
		sheet ="gfx/anims.png",
		type="sprite",
		ppu=1,
		animations = {
		{ 
            name="default", 
            frames = { 
                { duration = dt, quads = { { x = 254, y = 220, width = 29, height = 17, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 254, y = 239, width = 29, height = 17, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 254, y = 258, width = 29, height = 17, anchor = {0, 0}}}},
			}
		}}
	},
	{
		id = "meat",
		sheet = "gfx/anims.png",
		type="sprite",
		ppu = 1,
		animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 49, y = 37, width = 24, height = 6, anchor = {0, 0}}}}}}
		}
	},
	{
		id = "pot",
		sheet = "gfx/anims.png",
		type="sprite",
		ppu = 1,
		animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 75, y = 36, width = 15, height = 7, anchor = {0, 0}}}}}}
		}
	},
	{
		id = "fish",
		sheet = "gfx/anims.png",
		type="sprite",
		ppu = 1,
		animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 33, y = 36, width = 12, height = 7, anchor = {0, 0}}}}}}
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
	          gfx = { image="gfx/kitchen/bg1.png" },
	        },
			{
			  pos = {204, 0, 3},
			  gfx = { image="gfx/kitchen/bg2.png" },
			},
	        {
	          pos = {115, 0, 3},
	          gfx = { model = "kitchen_table", anim = "default" },
	        },
	        {
	          pos = {153, 39, -3},
	          gfx = { model = "potostew", anim = "default" },
	        },
	        {
	            walkarea = { 
	        	tag = "walkarea",
	        	group = 1,
	        	priority = 0,
	        	target = "player",
	        	shape = { type = "poly", outline = {40,16,59,21,155,21,180,18,192,18,294,18,307,12,199,9,207,0,160,0,149,11,112,11,100,0,40,0}},
				blockedlines = {
					{ A = {194, 0}, B = {194, 144}, active =true },
					{ A = {206, 0}, B = {206, 144}, active =true },
				},
	            scaling = {
	                depth = { 
	                    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 1} } 
	                }
	            }
	            }
			},
	        make_hotspot { 
	            x = 19,
	            y = 18, 
	            width = 38, 
	            height = 53, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "door_kitchen_bar",
	            gfx = { model="door_to_bar", anim = ((objects.door_kitchen_bar.isopen() == true) and "open" or "close") }
	        },
	        make_hotspot { 
	            x = 192,
	            y = 9, 
	            width = 40, 
	            height = 64, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "door_kitchen_pier",
	            gfx = { model="door_to_pier", anim = ((objects.door_kitchen_pier.isopen() == true) and "open" or "close") }
	        },
			make_hotspot {
				x = 79,
				y = 40,
				width = 20,
				height = 20,
				offset = {0, 0},
				priority = 1,
				object = "meat",
				gfx = { model="meat", anim="default" }
			},
			make_hotspot {
				x = 104,
				y = 24,
				width = 15,
				height = 7,
				offset = {0, 0},
				priority = 1,
				object = "pot",
				gfx = { model="pot", anim="default" }
			},
			make_hotspot {
				x = 234,
				y = 9,
				width = 12,
				height = 7,
				offset = {0, 0},
				priority = 1,
				object = "fish",
				gfx = { model="fish", anim="default" }
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
        scummbar = { playerpos = {45, 14, 0}, anim = "idle_right" }
    }

    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["scummbar"]
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




