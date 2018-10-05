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
        { name = "idle", frames = { {duration = dt, quads = { { x = 319, y = 1, width = 78, height = 70, anchor = {0, 0}}}}}},
        { name = "blink", frames = { 
			{duration = dt, quads = { { x = 399, y = 1, width = 78, height = 70, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 319, y = 1, width = 78, height = 70, anchor = {0, 0}}}}
		}},
        { name = "smile", frames = { {duration = dt, quads = { { x = 239, y = 1, width = 78, height = 70, anchor = {0, 0}}}}}},
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
	          gfx = { image="gfx/loom/bg1.png" },
	        },
			{
			  tag="loompirate",
			  pos = {212, 26, 0},	
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
	local s = Script.create("startup")
	s:add (say { character = "loom_pirate", noanim = true, lines = { strings.dialogues.loom_pirate.text[1] } })
	s:add ({ 
		{ type="animate", actor="loompirate", anim="blink", loop=1 }, 
		{ type="animate", actor="loompirate", anim="idle" },
		{ type= "callfunc", func = curry(startDialogue, { dialogueId="loom_pirate", nodeId=1, init = true })}
	})
	s:setsequence()
	monkey.play(s)
end




