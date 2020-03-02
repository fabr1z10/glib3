local d = strings.dialogues.loom_pirate

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
	return { type = scumm.action.say, args = {tag = 'loompirate.loompirate', lines = l, animstart = anim or "idle", animend= anim or "idle"}}
end

engine.dialogues.loompirate = {
	close = function()
		-- on close, return to scummbar
		local actions = scumm.script.changeroom { 
			room = 'scummbar', 
			pos = engine.items['scummbar.loompirate'].hotspot.walk_to, 
			dir='n'
		}
		local s = script.make(actions)
		monkey.play(s)
	end,
	-- root
	nodes = {
		[1] = { children = {2, 3, 4, 5}},
		[2] = { text = d[2], deact={2}, active=true, children={2,3,4,5}, script = { fguy({2}), fman({1}) }},
		[3] = { text = d[3], deact={3}, children={2,3,4,5}, active=true, script = { fguy({3}), fman({1}) } },
		[4] = { text = d[4], deact={4}, children={2,3,4,5}, active=true, script = { fguy({4}), fman({6,7,8,9,10,11,12,13}, "smile"), fguy({14}), fman({15}, "idle") } },
		[5] = { text = d[5], active=true, script = { fguy({5}), fman({2}) } },
	}
}