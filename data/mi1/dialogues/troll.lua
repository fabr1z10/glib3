local d = strings.dialogues.troll

local fguy = function(lines) 
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = action.say, args = {actor = "guybrush", lines = l }}
end

local ftro = function(lines)
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = action.say, args = {actor = "bridge.troll", lines = l, animstart = "talk", animend= "idle"}}
end

dialogues.troll = {
	close = function()
		local actions = {
			{ type = action.resume_script, args = {script="_troll"}}
		}
		local s = ms2(actions)
		monkey.play(s)
	end,
	nodes = {
		[1] = { children = {2, 3, 4, 19, 5, 6} },
		[2] = { text = d[4], deact={2}, active=true, children = {7,8,9,10}, script = { fguy({4}), ftro({9, 10, 11})}},
		[3] = { text = d[5], deact={3}, active=true, script = { fguy({5}), ftro({19,20})}},
		[4] = { text = d[6], deact={4}, act={19}, active=true, children = {11,12,13}, script = { fguy({6}),ftro({21})}},
		[5] = { text = d[7], active=true, deact={7}, script = { fguy({7}), ftro({34,35})}},
		[6] = { text = d[8], active=true, script = { fguy({8}), ftro({39})}},
		[7] = { text = d[12], active=true, script = { fguy({12}), ftro({16, 17})}},
		[8] = { text = d[13], active=true, script = { fguy({13}), ftro({40, 41})}},
		[9] = { text = d[14], active=true, script = { fguy({14}), ftro({42,43,44,45,46})}},
		[10] = { text = d[15], active=true, script = { fguy({15}), ftro({47})}},
		[11] = { text = d[22], deact={2}, active=true, children = {7,8,9,10}, script = { fguy({4}), ftro({9,10,11})}},
		[12] = { text = d[23], active=true, children = {14,15,16,17,18}, script = { fguy({23}), ftro({25})}},
		[13] = { text = d[24], active=true, script = { fguy({24}), ftro({36,37})}},
		[14] = { text = d[26], deact={14,15,16,17,18}, active=true, script = { fguy({26}), ftro({31,32,33})}},
		[15] = { text = d[27], deact={14,15,16,17,18}, active=true, script = { fguy({27}), ftro({31,32,33})}},
		[16] = { text = d[28], deact={14,15,16,17,18}, active=true, script = { fguy({28}), ftro({31,32,33})}},
		[17] = { text = d[29], deact={14,15,16,17,18}, active=true, script = { fguy({29}), ftro({31,32,33})}},
		[18] = { text = d[30], deact={14,15,16,17,18}, active=true, script = { fguy({30}), ftro({31,32,33})}},
		[19] = {text=d[38], active=false, children = {14,15,16,17,18}, script = { fguy({38}), ftro({25})}}
	}
}