local d = strings.dialogues.estevan


local fguy = function(lines) 
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = scumm.action.say, args = {tag = "player", lines = l, animate=false }}
end

local fman = function(lines,anim)
	local l = {}
	for _, n in ipairs(lines) do
		table.insert(l, d[n])
	end
	return { type = scumm.action.say, args = {tag = "estevan.estevan", lines = l, animstart = anim or "idle", animend= anim or "idle"}}
end

engine.dialogues.estevan = {
	close = function()
		-- on close, return to scummbar
		local actions = scumm.script.changeroom { 
			room = 'scummbar', 
			pos = engine.items['scummbar.estevan'].hotspot.walk_to, 
			dir='s'
		}
		local s = script.make(actions)
		monkey.play(s)
	end,
	-- root
	nodes = {
		[1] = { children = {2, 3, 4, 5, 6}},
		[2] = { text = d[2], deact={2}, children = {2,3,4,5,6}, active=true, script = { fguy({2}), fman({8}) }},
		[3] = { text = d[3], deact={3}, act={6}, children = {2,3,4,5,6}, active=true, script = { fguy({3}), fman({10,11,12,13}) } },
		[4] = { text = d[4], deact={4}, children = {2,3,4,5,6}, active=true, script = { fguy({4}), fman({14,15,16,17,18}) } },
		[5] = { text = d[5], active=true, script = { fguy({5}), fman({7}) } },
		[6] = { text = d[9], deact={6}, active=false, children = {2,3,4,5,6}, script = {fguy({9}), fman({19,20,21})}}
	}
}