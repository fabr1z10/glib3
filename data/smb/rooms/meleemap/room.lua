--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")


local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush()
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 200},
			bounds = {0, 0, 320, 200},
			viewport = {0, 0, 320, 200}
		},
		children = {
        	{
              tag = "mainbg",
              pos = {0, 0, -5},
              gfx = { image="gfx/meleemap/bg1.png" }
            },
            {
              walkarea = { 
                  tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {76, 80}, {78, 81}, {71,90}, {64, 96}, {48,99}, {49, 114}, {73, 113}, {88, 114},{118,114}, {135,113}, {83,109},
					{101, 107}, {112, 97}, {157, 78}, {172, 64}, {196, 54}, {217,54}, {232,49}, {245,48}, {254,50}, {275, 95}, {54,131},{57,140}, {60,151},
					{67,161}, {82, 174}, {113, 177}, {146, 168}, {169,168}, {180, 174}, {196,174}, {227,180} }, edges = { 
					{0,1}, {1,2}, {2,3},{3,4}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}, {6,10}, {10,11}, {11,12}, {12,13}, {13,14}, {14,15}, {15,16},{16,17},{17,18},
					{18,19}, {19,20}, {5,21}, {21,22}, {22,23}, {23,24}, {24,25}, {25,26}, {26,27}, {27, 28}, {28,29}, {29,30}, {30,31}  }},
                  scaling = {
                    depth = { 
                        { rect = {0, 320, 0, 200}, dir = "y", bounds = {1, 1} } 
                    },
                    scale = {
                        { rect = {0, 320, 0, 200}, dir = "y", bounds = {0.1, 0.1} } 
                    }
                }
              }
            },
			createMapItem (72, 76, strings.objects.lookoutpoint, 1, {75, 80}, "lookout"),
			createMapItem (62, 68, strings.objects.village, 1, {69, 74}, "village1"),
			--createMapItem (71, 110, strings.objects.fork, 1),
			createMapItem (132, 110, strings.objects.clearing, 1, {135, 113}, "clearing"),	
			--createMapItem (132, 110, strings.objects.fork, 1),	
			--createMapItem (167, 64, strings.objects.bridge, 1),	
			--createMapItem (201, 52, strings.objects.lights, 1),	
			--createMapItem (272, 93, strings.objects.house, 1),	
			--createMapItem (231, 180, strings.objects.island, 1),	
			
			-- {
			--     pos = {62, 68, 0},
			--     hotspot = {
			--         priority = 1,
			--         shape = { type = "rect", width=10, height=10 },
			--         onenter = curry (mapLocationEnter, "village"),
			-- 		onleave = curry (mapLocationExit)
			--     }
			-- },a
        }
	},
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
			-- {
			--     pos = {0, 0, 0},
			--     hotspot = {
			--         priority = 1,
			--         shape = { type = "rect", width=320, height=200 },
			--         onmove = function(x,y) print(x .. " " .. y) end
			--     }
			-- },
			{ 
								    
		    	tag = "cursor",
		    	pos={0,0,0},
		    	text = { id = "prova", font="monkey", align = "bottom", color = config.ui_currentaction_color},
				cursor = {}
			}
		}
	}
}
}
-- end room

function room.init()
    variables._actionInfo:reset()
    -- previous room was lookout
	local fromData = {
        lookout = { playerpos = {76, 78, 0}, anim = "idle_back" },
		clearing = { playerpos = {135, 113, 0}, anim = "idle_right", flip=true },
    }
	
	f = fromData[variables._previousroom]
	if (f == nil) then
		variables._previousroom = "lookout"
		f = fromData[variables._previousroom]
	end

    -- add player
    table.insert (room.scene[1].children, {
        tag = "player",
        pos = f.playerpos,
        gfx = { model = "guybrush", anim = f.anim, flip=f.flip},
        follow = { cam="maincam" },
        layer = 1,
        scaling = {}
    })

end

function room.afterstartup() 
--refreshInventory()
end




