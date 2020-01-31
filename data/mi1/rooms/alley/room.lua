local items = engine.items

roomDefinition = {
	width = 344,
	height = 144,
	startTable = {
		village3 = { walkarea="alley.walkarea", pos = items["alley.exit"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "village3",
	walkareas = {"alley.walkarea"},
	font_size = 8,
	playerid = "guybrush",
	collide=true
}

room = scumm.factory.basic_room (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="alley.png" }}},
	{ pos = {0, 0, 0.92}, components = { { type="gfx", image="alley_2.png" }}},
})

local fester = function()
	if (variables.met_fester == false) then
		local a = {
		}
		local s = script.make(a)
		monkey.play(s)
	end
end


table.insert(room.initstuff, fester)

-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- 	if (variables.met_fester == false) then
-- 		local s = script:new()
-- 		local di = strings.dialogues.fester

-- 		s.actions = {
-- 			action.say {id=1, actor="guybrush", lines={di[1]}},
-- 			action.walkto {id=2, actor="guybrush", pos ={150, 10}},
-- 			action.say {id=3, actor="guybrush", lines={di[2]}},
-- 			action.walkto {id=4, actor="guybrush", pos ={200, 10}},
-- 			action.say {id=9, actor="guybrush", lines={di[3]}, after={4}},
-- 			action.create_object { id=5, after={4}, name="fester", anim="idle_right", pos={30, 20, 0}, applydepth=true},
-- 			action.walkto {id=6, actor="fester", pos={150,10}},
-- 			action.turn {id =7, actor="guybrush", dir="west", after={9}},
-- 			action.say {id=8, actor="fester", lines={di[4], di[5]}}
-- 		}
-- 		-- 	action.delay { id=1, sec=5},
-- 		-- 	action.show_message { id = 2, message = strings.village3[1], color = items["fester"].text_color, pos= {594,67,1}},
-- 		-- 	action.delay { id=3, sec=5},
-- 		-- 	action.show_message { id = 4, message = strings.village3[2], color = items["fester"].text_color, pos= {594,67,1}},
-- 		-- 	action.delay { id=5, sec=5},
-- 		-- 	action.show_message { id = 6, message = strings.village3[3], color = items["fester"].text_color, pos= {594,67,1}},
-- 		-- }
-- 		-- s.loop = 1
-- 		monkey.play(s)	
-- 	end
-- end


