local items = engine.items

roomDefinition = {
	width = 368,
	height = 144,
	startTable = {
		clearing = { walkarea="circus.walkarea", pos = items["circus.wayout"].hotspot.walk_to, dir = "west"},
	},
	font_size=8,
	playerid="guybrush",
	walkareas = { "circus.walkarea"},
	collide=true,
	defaultroom = "clearing",
	enableScroll = false,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
    	{ pos = {0, 0}, size={368, 20}, type="constant", value = 1},
    	{ pos = {0, 20}, size={368, 14}, type="linear_y", values={20,1,34,0.57}}
		
	}}
}

room = scumm.factory.basic_room(roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="circus1.png" }}},
    { pos = {259, 1, 0.99}, components = { {type="gfx", image="circus2.png" }}},
    { pos = {233, 1, 0.99}, components = { {type="gfx", image="circus3.png" }}},
   	{ pos = {247, 17, 0.99}, components = { {type="gfx", image="circus4.png"}}},
 --   	scumm.factory.walkarea {
 --       	shape = { type = "poly", outline = {0,35,368,35,368,0,0,0}},
	-- },
	scumm.factory.object { id="circus.wayout"},

	-- factory.object.create { object = "circus.wayout"},
	-- factory.object.create { object = "circus.greenclown"},
	-- factory.object.create { object = "circus.purpleclown"}	
})


room:add("circus.walkarea", {
	scumm.factory.object { id="circus.purpleclown"},
	scumm.factory.object { id="circus.greenclown"},
})

local init = function()
	local d = strings.dialogues.fettbros

 	local s1 = {
 		{ ref=10, type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[10]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[11]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[12]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[13]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[14]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[15]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[16]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[17]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[18]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[19]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[20]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[21]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[22]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[23]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[24]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[25]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[26]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[27]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[28]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[22], d[23]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.purpleclown", lines={d[5]}}},
 		{ type = scumm.action.say, args= { actor="circus.greenclown", lines={d[5]}}}
 	}
 	local actions = {}
 	if (variables.entered_circus == false) then
 		variables.entered_circus = true
 		--local s = script:new("_fettuccini")
 		actions = {
 			{ ref=1, type=scumm.action.disable_controls },
 			{ type=scumm.action.walkto , args = {tag="player", pos={178, 9}}},
 			{ type=scumm.action.say, after={1}, args = {actor="circus.purpleclown", lines={d[1]}}},
 			{ type=scumm.action.say, args={ actor="circus.greenclown", lines={d[2]}}},
 			{ type=scumm.action.say, args={ actor="circus.purpleclown", lines={d[3]}}},
 			{ type=scumm.action.say, args={ actor="circus.greenclown", lines={d[4]}}},
 			{ type=scumm.action.say, args={ actor="circus.purpleclown", lines={d[5]}}},
 			{ type=scumm.action.say, args={ actor="circus.greenclown", lines={d[5]}}},
 			{ type=scumm.action.say, args={ actor="circus.purpleclown", lines={d[6]}}},
 			{ type=scumm.action.say, args={ actor="circus.greenclown", lines={d[7]}}},
 			{ type=scumm.action.say, args={ actor="circus.purpleclown", lines={d[8]}}},
 			{ type=scumm.action.say, args={ actor="circus.greenclown", lines={d[9]}}},
			{ type=scumm.action.start_dialogue, args= { dialogue="fettuccini"}}
 		}
 	else
		actions = {
 			{ type=scumm.action.disable_controls },
 			{ type=scumm.action.walkto , args = {tag="player", pos={178, 9}}},
			{ type=scumm.action.start_dialogue, args= { dialogue="fettuccini"}}
 		}
 	end		

	table.insert(actions, s1)
	local s = script.make(actions, 10)
	s.name = "_fettuccini"
	monkey.play(s)

end

table.insert(room.initstuff, init)


-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- 	local d = strings.dialogues.fettbros
	

	
-- 	if (variables.entered_circus == false) then
-- 		variables.entered_circus = true
-- 		local s = script:new("_fettuccini")
-- 		s.actions = {
-- 			action.disable_controls{id=1},
-- 			action.walkto {id=2, actor="guybrush", pos={178, 9}},
-- 			action.say {id=3, after={1}, actor="circus.purpleclown", lines={d[1]}},
-- 			action.say {id=4, actor="circus.greenclown", lines={d[2]}},
-- 			action.say {id=5, actor="circus.purpleclown", lines={d[3]}},
-- 			action.say {id=6, actor="circus.greenclown", lines={d[4]}},
-- 			action.say {id=7, actor="circus.purpleclown", lines={d[5]}},
-- 			action.say {id=8, actor="circus.greenclown", lines={d[5]}},
-- 			action.say {id=9, actor="circus.purpleclown", lines={d[6]}},
-- 			action.say {id=10, actor="circus.greenclown", lines={d[7]}},
-- 			action.say {id=11, actor="circus.purpleclown", lines={d[8]}},
-- 			action.say {id=12, actor="circus.greenclown", lines={d[9]}},
-- 			action.start_dialogue {id=13, dialogue="fettuccini"},
-- 		}
-- 		s:push { script = s1 }
-- 		monkey.play(s)
-- 	else
-- 		local s = script:new("_fettuccini")
-- 		s.actions = {
-- 			action.disable_controls{id=1},
-- 			action.walkto {id=2, actor="guybrush", pos={178, 9}},
-- 			action.start_dialogue {id=3, dialogue="fettuccini"},
-- 		}
-- 		s:push { script = s1, at = "start" }
-- 		monkey.play(s)
				
-- 	end		
-- end


