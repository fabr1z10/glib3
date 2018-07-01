require ("funcs")
require ("text")
require ("dialogues")
require ("actions")
require ("dialogues/lookout")

local dt = 0.1

room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
    makeLookout()
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
		}
	},
	makescummui1()
},
hotkeys = {
	{ key = 32, func = provaciccio }
}
}
-- end room

function room.init()

end

function room.afterstartup() 

end




