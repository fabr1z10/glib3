local d = strings.dialogues.mancomb

local fguy = function(lines) 
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = scumm.action.say, args = {tag = 'player', lines = l, animate=false }}
end

local fman = function(lines,anim)
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = scumm.action.say, args = {tag = 'mancomb.mancomb', lines = l, animstart = anim or "idle", animend= anim or "idle"}}
end

engine.dialogues.mancomb = {
	close = function()
		-- on close, return to scummbar
		local actions = scumm.script.changeroom { 
			room = 'scummbar', 
			pos = engine.items['scummbar.mancomb'].hotspot.walk_to, 
			dir='n'
		}
		local s = script.make(actions)
		monkey.play(s)
	end,
	-- root
	nodes = {
		[1] = { children = {2, 24, 3, 4, 5}},
		[2] = { text = d[3], deact={2}, active=true, children = {6,7,8,9}, script = { fguy({3}), fman({9}), fman({10, 11}, "smile") }},
		[3] = { text = d[4], deact={3}, active=true, deact={3}, children = {2, 14, 5}, script = { fguy({4}), fman({29, 30, 24, 25, 26}) }},
		[4] = { text = d[5], deact={4}, active=true, deact={5}, children = {21,22,23}, script = { fguy({5}), fman({40, 41})}},
		[5] = { text = d[6], active=true, script = { fguy({6}), fman({6, 7})}},
		[6] = { text = d[12], active=true, deact={6}, children={7,8,9}, script = { fguy({12}), fman({16})}},
		[7] = { text = d[13], active=true, children = {10,11,12,13}, deact={6,7}, script = { fguy({13}), fman({17, 18})}},
		[8] = { text = d[14], active=true, deact={8}, children = {14, 5}, script = { fguy({14}), fman({45, 46})}},
		[9] = { text = d[15], active=true, script = { fguy({15}), fman({47, 48})}},
		[10] = { text = d[19], active= true, children={14,5}, script = { fguy({19}), fman({23,24,25,26})}},
		[11] = { text = d[20], active= true, children={14,5}, script = {fguy({20}), fman({28, 24, 25, 26})}},
		[12] = { text = d[21], active= true, children={14,5}, script = { fguy({21}), fman({50, 51, 24, 25, 26})}},
		[13] = { text = d[22], active=true, script = { fguy({22}), fman({57})}},
		[14] = { text = d[27], active=true, children={15,16,17}, script = {fguy({27}), fman({31,32, 33})}},
		[15] = { text = d[34], active = true, children = {18,19,20}, script = { fguy({34}), fman({52, 53})}},
		[16] = { text = d[35], active = true, script = { fguy({35}), fman({64, 65, 66, 6, 7})}},
		[17] = { text = d[36], active = true, script = { fguy({36}), fman({65, 6, 7})}},
		[18] = { text = d[54], active = true, script = { fguy({54}), fman({59, 60, 61, 62}), fman({63}, "smile"), fman({66,6,7})}},
		[19] = { text = d[55], active = true, script = { fguy({55}), fman({58, 59, 60, 61, 62}), fman({63}, "smile"), fman({66,6,7})}},
		[20] = { text = d[56], active = true, script = { fguy({56}), fman({6, 7})} },
		[21] = { text = d[42], active = true, children={14, 5}, script = { fguy({42}), fman ({24, 25, 26})}},
		[22] = { text = d[43], active = true, children={15,16,17}, script = { fguy({43}), fman({31, 32, 33})} },
		[23] = { text = d[44], active = true, script = { fguy({44}), fman({6, 7})}},
		[24] = { text = d[49], active = false, children = {10,11,12,13}, script = { fguy({49}), fman({46, 18})}}
	}
}