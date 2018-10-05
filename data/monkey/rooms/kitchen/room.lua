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
	},
	{
		id = "plank",
		sheet = "gfx/anims3.png",
		type="sprite",
		ppu = 1,
		animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 2, y = 194, width = 67, height = 24, anchor = {0, 0}}}}}},
		{ name="pushed", frames = { {duration = dt, quads = { { x = 2, y = 169, width = 61, height = 24, anchor = {0, 0}}}}}}
		}
	},
	{
		id = "seagull",
		sheet = "gfx/anims3.png",
		type ="sprite",
		ppu = 1,
		animations = {
			{
				name = "flying",
				frames = {	
					{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-307,-37}}}},
					{duration = dt, quads = {{x=39, y = 49, width=25, height=12, anchor = {-295,-35}}}},
					{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-292,-33}}}},
					{duration = dt, quads = {{x=39, y = 63, width=19, height=25, anchor = {-285,-29}}}},
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-277,-32}}}},
					{duration = dt, quads = {{x=39, y = 63, width=19, height=25, anchor = {-269,-22}}}},
					{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-260,-25}}}},
					{duration = dt, quads = {{x=39, y = 49, width=25, height=12, anchor = {-247,-23}}}},
					{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-244,-21}}}},
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-245,-23}}}},
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-250,-17}}}},
					{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-248,-14}}}},
					{duration = dt, quads = {{x=39, y = 128, width=25, height=11, anchor = {-246,-13}}}},
					{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-243,-12}}}},
					{duration = dt, quads = {{x=39, y = 141, width=19, height=9, anchor = {-243,-10}}}}
				}
			},
			{
				name = "eating",
				frames = {	
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=61, y = 36, width=18, height=11, anchor = {-242,-10}}}},
					{duration = dt, quads = {{x=66, y = 51, width=17, height=10, anchor = {-243,-10}}}},
					{duration = dt, quads = {{x=60, y = 63, width=19, height=9, anchor = {-242,-10}}}},
					{duration = dt, quads = {{x=60, y = 74, width=19, height=10, anchor = {-242,-10}}}},
					{duration = dt, quads = {{x=60, y = 63, width=19, height=9, anchor = {-242,-10}}}},	
					{duration = dt, quads = {{x=60, y = 74, width=19, height=10, anchor = {-242,-10}}}},
					{duration = dt, quads = {{x=60, y = 86, width=17, height=10, anchor = {-243,-10}}}},
					{duration = dt, quads = {{x=60, y = 86, width=17, height=10, anchor = {-243,-10}}}},
					{duration = dt, quads = {{x=60, y = 86, width=17, height=10, anchor = {-243,-10}}}},
					{duration = dt, quads = {{x=60, y = 98, width=18, height=11, anchor = {-242,-10}}}},
					{duration = dt, quads = {{x=64, y = 111, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=66, y = 125, width=11, height=17, anchor = {-249,-10}}}},
					{duration = dt, quads = {{x=60, y = 144, width=12, height=17, anchor = {-248,-10}}}},
					{duration = dt, quads = {{x=85, y = 37, width=12, height=17, anchor = {-248,-10}}}},
				}
			},
			{
				name = "jump1",
				frames = {	
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-40}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-64}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-94}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-100}}}},
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-82}}}},	
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-64}}}},	
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-40}}}},	
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-10}}}}
				}
			},
			{
				name = "jump2",
				frames = {	
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-40}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-64}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-82}}}},			
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-94}}}},			
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-100}}}},		
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-249,-98}}}},			
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-255,-94}}}},			
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-261,-86}}}},			
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-267,-74}}}},			
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-273,-58}}}},			
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-279,-38}}}},			
					{duration = dt, quads = {{x=3, y = 221, width=23, height=7, anchor = {-268,-34}}}},			
					{duration = dt, quads = {{x=39, y = 63, width=19, height=25, anchor = {-259,-27}}}},			
					{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-254,-23}}}},			
					{duration = dt, quads = {{x=39, y = 49, width=25, height=12, anchor = {-245,-15}}}},			
					{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-250,-17}}}},			
					{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-248,-14}}}},			
					{duration = dt, quads = {{x=39, y = 128, width=25, height=11, anchor = {-246,-13}}}},			
					{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-244,-12}}}},			
					{duration = dt, quads = {{x=39, y = 141, width=19, height=9, anchor = {-243,-11}}}}		
				}
			},
			{
				name = "nofish",
				frames = {	
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=88, y = 57, width=7, height=13, anchor = {-250,-10}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=82, y = 72, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=84, y = 87, width=7, height=13, anchor = {-250,-10}}}},
					{duration = dt, quads = {{x=82, y = 72, width=15, height=13, anchor = {-245,-10}}}},
					{duration = dt, quads = {{x=28, y = 220, width=21, height=17, anchor = {-243,-10}}}},
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-247,-11}}}},
					{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-248,-10}}}},
					{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-250,-14}}}},
					{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-260,-20}}}},
					{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-264,-23}}}},
					{duration = dt, quads = {{x=24, y = 244, width=25, height=12, anchor = {-268,-24}}}},
					{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-272,-25}}}},
					{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-276,-25}}}},
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-280,-31}}}},
					{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-284,-27}}}},
					{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-288,-30}}}},
					{duration = dt, quads = {{x=24, y = 244, width=25, height=12, anchor = {-292,-32}}}},
					{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-296,-33}}}},
					{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-300,-32}}}},
					{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-304,-38}}}},
					{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-308,-34}}}},
					{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-312,-39}}}}
				}
			},	
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
			make_hotspot {
				x = 153,
				y = 39,
				width = 32,
				height = 19,
				offset = {0, 0},
				priority = 1,
				object = "potostew"
			},
			make_hotspot {
				x = 9,
				y = 0,
				width = 28,
				height = 28,
				offset = {0, 0},
				priority = 2,
				object = "barrel"
			},
			make_hotspot {
				x = 114,
				y = 0,
				width = 35,
				height = 22,
				offset = {0, 0},
				priority = 2,
				object = "kitchen_table"
			},
			{
				-- plank
				pos = {248, 0, 1},
				tag = "plank",
				gfx = { model="plank", anim="default"},
			},
			{
			    pos = {287, 7, 0},
			    hotspot = {
			        priority = 1,
			        shape = { type = "rect", width=21, height=8 },
			        onclick = hitPlank
			    }
			},
			{
				walktrigger = {
				
					shape = { type = "rect", width=20, height=100, offset = {80,0}},
					target = "player",
					onenter = startSeagull,
					onleave = function() end,
					onstay = function() end,
				}
			}
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




