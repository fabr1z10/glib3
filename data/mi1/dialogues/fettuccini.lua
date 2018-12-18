local d = strings.dialogues.fettbros

local s1 = {
 	{ action.noop, { id = 1}},
	{ action.walkto, {id=2, actor="circus.purpleclown", pos ={148, 7}}},
	{ action.walkto, {id=3, after={1}, actor="circus.greenclown", pos ={218, 7}}},
	{ action.turn, {id=4, after={2}, actor="circus.purpleclown", dir="east"}},
	{ action.turn, {id=5, after={3}, actor="circus.greenclown", dir="west"}},
	{ action.turn, {id=6, after={4,5}, actor="guybrush", dir="south"}},
	{ action.say, {id=7, actor="circus.purpleclown", lines={d[34]}}},
	{ action.say, {id=8, actor="circus.greenclown", lines={d[35]}}},
	{ action.say, {id=9, actor="circus.purpleclown", lines={d[36]}}},
	{ action.say, {id=10, actor="circus.greenclown", lines={d[37]}}},
	{ action.say, {id=11, actor="circus.purpleclown", lines={d[38]}}},
	{ action.say, {id=12, actor="circus.greenclown", lines={d[39]}}},
	{ action.say, {id=13, actor="circus.purpleclown", lines={d[40]}}},
	{ action.say, {id=14, actor="circus.greenclown", lines={d[41]}}},
	{ action.say, {id=15, actor="circus.purpleclown", lines={d[42]}}},
	{ action.say, {id=16, actor="circus.greenclown", lines={d[43]}}},
	{ action.say, {id=17, actor="circus.purpleclown", lines={d[44]}}},
	{ action.say, {id=18, actor="circus.greenclown", lines={d[45]}}},
	{ action.say, {id=19, actor="circus.purpleclown", lines={d[46]}}},
	{ action.say, {id=20, actor="circus.greenclown", lines={d[47]}}},
	{ action.say, {id=21, actor="circus.purpleclown", lines={d[48]}}},
	{ action.say, {id=22, actor="circus.greenclown", lines={d[49]}}},
	{ action.say, {id=23, actor="circus.purpleclown", lines={d[50]}}},
	{ action.say, {id=24, actor="circus.greenclown", lines={d[51]}}},
	{ action.say, {id=25, actor="circus.purpleclown", lines={d[52]}}},
	{ action.say, {id=26, actor="circus.greenclown", lines={d[53]}}},
	{ action.say, {id=27, actor="circus.purpleclown", lines={d[54], d[55]}}},
	{ action.say, {id=28, actor="circus.greenclown", lines={d[56]}}},
	{ action.say, {id=29, actor="circus.purpleclown", lines={d[57]}}},
	{ action.say, {id=30, actor="circus.greenclown", lines={d[58]}}},
	{ action.say, {id=31, actor="circus.purpleclown", lines={d[59]}}},
	{ action.say, {id=32, actor="circus.greenclown", lines={d[60]}}},
	{ action.set_variable, {id=33, var="circus_knows_trick", value=true}}
}


local s2 = {
 	{ action.noop, { id = 1}},
	{ action.walkto, {id=2, actor="circus.purpleclown", pos ={148, 7}}},
	{ action.walkto, {id=3, after={1}, actor="circus.greenclown", pos ={218, 7}}},
	{ action.turn, {id=4, after={2}, actor="circus.purpleclown", dir="east"}},
	{ action.turn, {id=5, after={3}, actor="circus.greenclown", dir="west"}},
	{ action.turn, {id=6, after={4,5}, actor="guybrush", dir="south"}},
	{ action.say, {id=7, actor="circus.purpleclown", lines={d[67]}}},
	{ action.say, {id=8, actor="circus.greenclown", lines={d[68]}}},
}

local a1 = function(n) 
	return { text = d[n], active=true, children= function() if (variables.circus_knows_helmet == true) then return {10,11} else return {7,8,9} end end, 
		script = function()
			local s = script:new()
			s.actions = {
				action.kill_script {id = 1, script="_fettuccini"},
				action.say {id=2, actor="guybrush", lines={d[n]}}
			}

			if (variables.circus_knows_trick == false) then
				s:push { script = ms(s1)() }
			elseif (variables.circus_knows_helmet == false) then
				s:push { script = ms(s2)() }
			else
				s:push { script = ms(s2)() }
				local s2 = script:new()
				s2.actions = {
					action.say {id=1, actor="circus.purpleclown", lines={d[70]}}
				}
				s:push {script=s2}
			end
			return s
		end
	}
end


dialogues.fettuccini = {
	close = function()
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 5, 6}},
		[2] = a1(29),
		[3] = a1(30),
		[4] = a1(31),
		[5] = a1(32),
		[6] = a1(33),
		[7] = { text = d[61], active=true, children={10,11}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[61]}}},
			{ action.say, {id=2, actor="circus.purpleclown", lines={d[69], d[70]}}}
		} },
		[8] = { text = d[62], active=true, children ={13,14}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[61]}}},
			{ action.say, {id=2, actor="circus.purpleclown", lines={d[64]}}}
		} },
		[9] = { text = d[63], active=true, script = ms{
			{ action.say, {id=1, actor="guybrush", lines={d[63]}}},
			{ action.change_room, {id=2, room="clearing"}}		
		} },
		[10] = { text = d[71], active=true, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[71]}}},
			{ action.say, {id=2, actor="circus.greenclown", lines={d[73]}}},
			{ action.say, {id=3, actor="circus.purpleclown", lines={d[74]}}},
			{ action.say, {id=4, actor="circus.greenclown", lines={d[75]}}},
			{ action.say, {id=5, actor="circus.purpleclown", lines={d[76]}}},
			{ action.say, {id=6, actor="circus.greenclown", lines={d[77]}}},
			{ action.set_variable, {id=7, var="circus_knows_helmet", value=true}},
			{ action.change_room, {id=8, room="clearing"}}
		}},
		[11] = { text = d[72], active=true},
		[12] = { text = d[29], active=true, children={10, 11}, script = msc {
			{
				{ action.kill_script, {id = 1, script="_fettuccini"}},
				{ action.say, {id=2, actor="guybrush", lines={d[29]}}}
			}, 
			s2
		}}, 
		[13] = { text = d[65], active=true, children={10,11}, script = ms {
			{ action.say, {id=1, actor="guybrush", lines={d[65]}}},
			{ action.say, {id=2, actor="circus.purpleclown", lines={d[70]}}},
			{ action.set_variable, {id=3, var="circus_knows_helmet", value=true}},
		} }
		[14] = { text = d[66], active=true, script = ms{
			{ action.say, {id=1, actor="guybrush", lines={d[66]}}},
			{ action.change_room, {id=2, room="clearing"}}		
		} }
	}
}