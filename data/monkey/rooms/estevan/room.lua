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
    makeArrowUp(),
    makeArrowDown(),
    {
        id = "pirate",
        sheet = "gfx/faces.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { {duration = dt, quads = { { x = 268, y = 79, width = 92, height = 94, anchor = {0, 0}}}}}},
        { name = "blink", frames = { 
			{duration = dt, quads = { { x = 174, y = 79, width = 92, height = 94, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 80, y = 174, width = 92, height = 94, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 174, y = 79, width = 92, height = 94, anchor = {0, 0}}}},
		}},
        { name = "scared", frames = { {duration = dt, quads = { { x = 80, y = 79, width = 92, height = 94, anchor = {0, 0}}}}}},
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
			bounds = {0, 0, 320, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
	        {
	          pos = {0, 0, -5},
	          gfx = { image="gfx/estevan/bg1.png" },
	        },
			{
			  tag="estevan",
			  pos = {176, 15, 0},	
			  gfx = { model = "pirate", anim = "idle"}
			},
			{
			  tag="player",
			  pos = {50,50,0}
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
		children = {

		}
	}
}
}
-- end room

function room.init()

end

function room.afterstartup() 
	local firstLine = variables.talkedToEstevan and 6 or 1
	variables.talkedToEstevan = true
	local s = Script.create("startup")
	s:add (say { character = "estevan", noanim = true, lines = { strings.dialogues.estevan.text[firstLine] } })
	s:add ({ 
		{ type="animate", actor="estevan", anim="blink", loop=1 }, 
		{ type="animate", actor="estevan", anim="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="estevan", nodeId=1, init = true })}
	})
	s:setsequence()
	monkey.play(s)
end




