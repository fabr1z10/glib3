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
    makeCook(),
    {
        id = "door_out",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 2, y = 243, width = 38, height = 47, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 2, y = 195, width = 38, height = 47, anchor = {0, 0}}}}}}
        }
    },
    {
        id = "door_kitchen",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 44, y = 199, width = 35, height = 69, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 44, y = 270, width = 35, height = 69, anchor = {0, 0}}}}}}
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
			bounds = {0, 0, 640, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
			{
		    	pos = {0, 0, -5},
          		gfx = { image="gfx/scummbar/bg1.png", width=640, height=144 },
          		layer = 1
        	},
	        {
	          walkarea = { 
	            tag = "walkarea",
	            group = 1,
	            priority = 0,
	            layer = 1,
	            target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {32,16,70,24,128,19,251,18,311,10,321,10,345,32,467,41,492,50,514,40,565,40,580,35,629,6,626,0,256,0,200,16,149,0,90,0,85,10},
	                 holes = {
	               
	                    {374,6,505,6,505,28,374,28}
	                }
	            },
	            scaling = {
	                depth = { 
	                    { rect = {0, 640, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 640, 0, 144}, dir = "y", bounds = {1, 1} } 
	                }
	            }
	          }
	        },
	        make_hotspot { 
	            x = 32, 
	            y = 25, 
	            width = 38, 
	            height = 47, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "scummbar_door_out",
	            gfx = { model="door_out", anim = ((objects.scummbar_door_out.isopen() == true) and "open" or "close") }
	        },
	        make_hotspot { 
	            x = 591, 
	            y = 9, 
	            width = 35, 
	            height = 69, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "door_bar_kitchen",
	            gfx = { model="door_kitchen", anim = ((objects.door_bar_kitchen.isopen() == true) and "open" or "close") }
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
    -- put your initialization code here
    variables._actionInfo:reset()

	local fromData = {
        village1 = { playerpos = {66, 19, 0}, anim = "idle_right" },
		kitchen = { playerpos = {601, 16, 0}, anim = "idle_right", flip = true},
    }

    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["village1"]
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

function room.start() 
    --cook script
 	s = Script.create("_cook")
	local n = 1
	if (variables._previousroom == "kitchen") then
	    s:add ({
	        { type = "callfunc", func = curry (createObject, { 
	            pos = {100, 20, 0},
	            gfx = { model = "cook", anim = "idle_back" },
	            scaling = {},
	            tag = "cook"
	        })},
	        { type = "delay", sec = 3.0 },
	        {
	            type = "walkto",
	            walkarea = "walkarea",
	            actor = "cook",
	            pos = {607, 20}
	        },
	        { type = "delay", sec = 0.5 },
			{ type = "animate", actor ="door_bar_kitchen", anim="close" },
			{ type = "callfunc", func = function() objects.door_bar_kitchen.setopen(false) end },
	        { type = "callfunc", func = curry(removeObject, "cook") }
	    })
		n = 7
	end
    s:add ({
        { type = "delay", sec = 5.0 },
		{ type = "animate", actor ="door_bar_kitchen", anim="open" },
		{ type = "callfunc", func = function() objects.door_bar_kitchen.setopen(true) end },
        { type = "callfunc", func = curry (createObject, { 
            pos = {607, 20, 0},
            gfx = { model = "cook", anim = "idle_back" },
            layer = 1,
            scaling = {},
            tag = "cook"
        })},
        {
            type = "walkto",
            walkarea = "walkarea",
            actor = "cook",
            pos = {100, 20}
        },
        { type ="turn", actor="cook", face="north"},
        { type = "delay", sec = 3.0 },
        {
            type = "walkto",
            walkarea = "walkarea",
            actor = "cook",
            pos = {607, 20}
        },
        { type = "delay", sec = 0.5 },
		{ type = "animate", actor ="door_bar_kitchen", anim="close" },
		{ type = "callfunc", func = function() objects.door_bar_kitchen.setopen(false) end },
        { type = "callfunc", func = curry(removeObject, "cook") }
    })
	s:setsequence()
	s.loop = n
	monkey.play(s)
end


