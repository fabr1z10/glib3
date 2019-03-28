local d = strings.dialogues.fettbros

local actor_map = {
	[1] = "guybrush",
	[2] = "circus.purpleclown",
	[3] = "circus.greenclown"
}

local f = function(who, lines) 
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = scumm.action.say, args = {actor = actor_map[who], lines = l }}
end

local fettuccini_approach = {
	{ ref = 1, type = action.noop },
	{ ref = 2, type =scumm.action.walkto, after={1}, args={tag="circus.purpleclown", pos ={148, 7}}},
	{ ref = 3, type =scumm.action.walkto, after={1}, args={tag="circus.greenclown", pos = {218, 7}}},
	{ type =scumm.action.turn, after={2,3}, args={tag="circus.purpleclown", dir="east"}},
	{ type =scumm.action.turn, after={2,3}, args={tag="circus.greenclown", dir="west"}},
	{ type =scumm.action.turn, after={2,3}, args={tag="player", dir="south"}},
}

local s1 = { 
	--f(2,{34}), f(3,{35}), f(2,{36}), f(3,{37}), f(2,{38}), f(3,{39}), f(2,{40}), f(3,{41}), f(2,{42}), f(3,{43}), f(2,{44}), f(3,{45}), f(2,{46}), f(3,{47}), f(2,{48}), 
	--f(3,{49}), f(2,{50}), f(3,{51}), f(2,{52}), f(3,{53}), f(2, {54,55}), f(3,{56}), f(2,{57}), f(3,{58}), f(2,{59}), 
	f(3,{60}),
	{ type=action.set_variable, args={var="circus_knows_trick", value=true}} }

local s3 = { f(2, {95}), f(3, {96}), f(2, {97}), f(3, {98}), {type=action.delay, args={sec=0.5}},
	f(3, {99}), f(2, {100}), f(3, {101}), f(2, {102}), f(3, {103}), {type=action.change_room, args= {room="clearing"}}}

local a1 = function(n) 
	return { text = d[n], active=true, 
		children= function() if (variables.circus_knows_helmet == true) then return {10,11} else return {7,8,9} end end, 
		script = function()
			-- guybrush says the 1st sentence...
			local actions = { 
				{ type = action.kill_script, args = {script="_fettuccini" }}, 
				f(1,{n}),
				fettuccini_approach
			}

			if (variables.circus_knows_trick == false) then
				table.insert(actions, s1)
			elseif (variables.circus_knows_helmet == false) then
				table.insert(actions, { f(2, {67}), f(3, {68}) })
			else
				table.insert(actions, { f(2, {67}), f(3, {68}), f(2, {70}) })
			end
			return actions
		end
	}
end


dialogues.fettuccini = {
	close = function() end,
	nodes = {
		[1] = { children = {2, 3, 4, 5, 6}},
		[2] = a1(29),
		[3] = a1(30),
		[4] = a1(31),
		[5] = a1(32),
		[6] = a1(33),
		[7] = { text = d[61], active=true, children={10,11}, script = { f(1, {61}), f(2, {69, 70}) }},
		[8] = { text = d[62], active=true, children ={13,14}, script = { f(1, {61}), f(2, {64}) }},
		[9] = { text = d[63], active=true, script = { f(1, {63}), { type=action.change_room, args={room="clearing"}}}},
		[10] = { text = d[71], active=true, script = { f(1, {71}), f(3, {73}), f(2, {74}), f(3, {75}), f(2, {76}), f(3, {77}), 
			{ type = action.set_variable, args = {var="circus_knows_helmet", value=true}},
			{ type=action.change_room, args={room="clearing"}}}},
	    [11] = { text = d[72], active=true, script = { f(1, {72}), f(3, {78}), f(2, {79}), f(3, {80}), f(2, {81}), f(3, {76}),
			{ type = action.set_variable, args = {var="circus_knows_helmet", value=true}}}},
		[12] = { text = d[29], active=true, children={10, 11}, script = { { type = action.kill_script, args = {script="_fettuccini"}}, f(1, {29}), fettuccini_approach, f(2, {67}), f(3, {68})}},
		[13] = { text = d[65], active=true, children={10,11}, script = { f(1, {65}), f(2, {70}),
			{ type = action.set_variable, args = {var="circus_knows_helmet", value=true}}}},
		[14] = { text = d[66], active=true, script = { f(1, {66}), { type=action.change_room, args={room="clearing"}}}},
		[15] = { children = {16, 17}},
		[16] = { text = d[93], active=true, script = { {type=action.show_message, args = { message = d[93], color = items["guybrush"].text_color, pos = {93, 60, 5}}}, s3 }},
		[17] = { text = d[94], active=true, script = { {type=action.show_message, args = { message = d[94], color = items["guybrush"].text_color, pos = {93, 60, 5}}}, s3 }}
	}
	
}