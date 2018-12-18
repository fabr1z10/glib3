require("template/room1")

local roomInfo = {
	width = 368,
	height = 144,
	startTable = {
		clearing = { pos = items["circus.wayout"].walk_to, facing = "west"},
	},
	defaultroom = "clearing",
	enableScroll = false,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
    	{ pos = {0, 0}, size={368, 20}, type="constant", value = 1},
    	{ pos = {0, 20}, size={368, 14}, type="linear_y", values={20,1,34,0.57}}
		
	}}
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites["circus.greenclown"])
room:add_asset(sprites["circus.purpleclown"])


room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/circus1.png" }}},
    { pos = {259, 1, 0.99}, components = { {type="gfx", image="gfx/circus2.png" }}},
    { pos = {233, 1, 0.99}, components = { {type="gfx", image="gfx/circus3.png" }}},
	{
		pos = {0,0,0},
		components = {
 	  		{ 
				type ="walkarea",
	 			priority = 0,
      			target = "player",
	        	shape = { type = "poly", outline = {0,35,368,35,368,0,0,0}},
 	  		}
		}
	},
	factory.object.create { object = "circus.greenclown"},
	factory.object.create { object = "circus.purpleclown"}	
})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	local d = strings.dialogues.fettbros
	

	local s1 = script:new()
	s1.actions = {
		action.say {id=1, actor="circus.purpleclown", lines={d[10]}},
		action.say {id=2, actor="circus.greenclown", lines={d[11]}},
		action.say {id=3, actor="circus.purpleclown", lines={d[12]}},
		action.say {id=4, actor="circus.greenclown", lines={d[13]}},
		action.say {id=5, actor="circus.purpleclown", lines={d[14]}},
		action.say {id=6, actor="circus.greenclown", lines={d[15]}},
		action.say {id=7, actor="circus.purpleclown", lines={d[16]}},
		action.say {id=8, actor="circus.greenclown", lines={d[17]}},
		action.say {id=9, actor="circus.purpleclown", lines={d[18]}},
		action.say {id=10, actor="circus.greenclown", lines={d[19]}},
		action.say {id=11, actor="circus.purpleclown", lines={d[20]}},
		action.say {id=12, actor="circus.greenclown", lines={d[21]}},
		action.say {id=13, actor="circus.purpleclown", lines={d[22]}},
		action.say {id=14, actor="circus.greenclown", lines={d[23]}},
		action.say {id=15, actor="circus.purpleclown", lines={d[5]}},
		action.say {id=16, actor="circus.greenclown", lines={d[5]}},
		action.say {id=17, actor="circus.purpleclown", lines={d[24]}},
		action.say {id=18, actor="circus.greenclown", lines={d[25]}},
		action.say {id=19, actor="circus.purpleclown", lines={d[5]}},
		action.say {id=20, actor="circus.greenclown", lines={d[5]}},
		action.say {id=21, actor="circus.purpleclown", lines={d[26]}},
		action.say {id=22, actor="circus.greenclown", lines={d[27]}},
		action.say {id=23, actor="circus.purpleclown", lines={d[28]}},
		action.say {id=24, actor="circus.greenclown", lines={d[22], d[23]}},
		action.say {id=25, actor="circus.purpleclown", lines={d[5]}},
		action.say {id=26, actor="circus.greenclown", lines={d[5]}},
		action.say {id=27, actor="circus.purpleclown", lines={d[5]}},
		action.say {id=28, actor="circus.greenclown", lines={d[5]}}
	}
	s1.loop = 1
	
	if (variables.entered_circus == false) then
		variables.entered_circus = true
		local s = script:new("_fettuccini")
		s.actions = {
			action.disable_controls{id=1},
			action.walkto {id=2, actor="guybrush", pos={178, 9}},
			action.say {id=3, after={1}, actor="circus.purpleclown", lines={d[1]}},
			action.say {id=4, actor="circus.greenclown", lines={d[2]}},
			action.say {id=5, actor="circus.purpleclown", lines={d[3]}},
			action.say {id=6, actor="circus.greenclown", lines={d[4]}},
			action.say {id=7, actor="circus.purpleclown", lines={d[5]}},
			action.say {id=8, actor="circus.greenclown", lines={d[5]}},
			action.say {id=9, actor="circus.purpleclown", lines={d[6]}},
			action.say {id=10, actor="circus.greenclown", lines={d[7]}},
			action.say {id=11, actor="circus.purpleclown", lines={d[8]}},
			action.say {id=12, actor="circus.greenclown", lines={d[9]}},
			action.start_dialogue {id=13, dialogue="fettuccini"},
		}
		s:push { script = s1 }
		monkey.play(s)
	else
		local s = script:new("_fettuccini")
		s.actions = {
			action.disable_controls{id=1},
			action.walkto {id=2, actor="guybrush", pos={178, 9}},
			action.start_dialogue {id=3, dialogue="fettuccini"},
		}
		s:push { script = s1, at = "start" }
		monkey.play(s)
				
	end		
end


