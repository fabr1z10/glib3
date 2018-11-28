local d = strings.dialogues.estevan

dialogues.estevan = {
	close = function()
		local s = change_room("scummbar")
		monkey.play(s)
	end,
	-- root
	nodes = {
		[1] = { children = {2,3,4,5} },
		[2] = { text = d[2], active=true, deact={2}, script = curry(make_dialogue, {
			{ items.guybrush, {d[2]}, { animate=false } },
			{ items.estevan.estevan, { d[8] }, {animate=false} }
		})},
		[3] = { text = d[3], active=true},
		[4] = { text = d[4], active=true},
		[5] = { text = d[5], active=true, script = curry(make_dialogue, {
			{ items.guybrush, {d[5]}, { animate=false } },
			{ items.estevan.estevan, { d[7] }, {animate=false} }
		})}
	}
}