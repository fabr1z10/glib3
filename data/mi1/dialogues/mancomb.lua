local d = strings.dialogues.mancomb

dialogues.mancomb = {
	close = function()
		local s = change_room("scummbar")
		monkey.play(s)
	end,
	-- root
	nodes = {
		[1] = { children = {2, 24, 3, 4, 5} },
		[2] = { text = d[3], active=true, children = {6,7,8,9}, script = curry(make_dialogue, {
			{ items.guybrush, {d[3]}, { animate=false } },
			{ items.mancomb.mancomb, { d[9] }, {animate=false} },
			{ items.mancomb.mancomb, { d[10], d[11] }, { anim_begin="smile" } },
		}) },
		[3] = { text = d[4], active=true, deact={3}, children = {2, 14, 5}, script = curry(make_dialogue, {
			{ items.guybrush, {d[4]}, { animate=false } },
			{ items.mancomb.mancomb, { d[29], d[30], d[24], d[25], d[26] }, {anim_begin="idle"} },
		}) },
		[4] = { text = d[5], active=true, deact={5}, children = {21,22,23}, script = curry(make_dialogue, {
			{ items.guybrush, {d[5]}, { animate=false } },
			{ items.mancomb.mancomb, { d[40], d[41] }, {anim_begin="idle"} },
		}) },
		[5] = { text = d[6], active=true, script = curry(make_dialogue, {
			{ items.guybrush, {d[6]}, {animate=false}},
			{ items.mancomb.mancomb, { d[6], d[7] }, { anim_begin="idle" } },			
		}) },
		[6] = { text = d[12], active=true, deact={6}, children={7,8,9}, script = curry(make_dialogue, {
			{ items.guybrush, {d[12]}, { animate=false } },
			{ items.mancomb.mancomb, { d[16] }, { anim_begin="idle" } },
		}) },
		[7] = { text = d[13], active=true, children = {10,11,12,13},deact={6,7}, script = curry(make_dialogue, {
			{ items.guybrush, {d[13]}, { animate=false } },
			{ items.mancomb.mancomb, { d[17], d[18] }, { anim_begin="idle" } },
		}) },
		[8] = { text = d[14], active=true, deact={8}, children = {14, 5}, script = curry(make_dialogue, {
			{ items.guybrush, {d[14]}, { animate=false } },
			{ items.mancomb.mancomb, { d[45], d[46] }, { anim_begin="idle" } },
		}) },
		[9] = { text = d[15], active=true, script = curry(make_dialogue, {
			{ items.guybrush, {d[15]}, { animate=false } },
			{ items.mancomb.mancomb, { d[47], d[48] }, { anim_begin="idle" } },
		}) },
		[10] = { text = d[19], active= true, children={14,5}, script = curry(make_dialogue, {
			{ items.guybrush, {d[19]}, {animate=false}},
			{ items.mancomb.mancomb, { d[23], d[24], d[25], d[26] }, { anim_begin="idle" } },

		}) },
		[11] = { text = d[20], active= true, },
		[12] = { text = d[21] },
		[13] = { text = d[22], active=true, script = curry(make_dialogue, {
			{ items.guybrush, {d[22]}, {animate=false}},
			{ items.mancomb.mancomb, { d[57] }, { anim_begin="idle" } },		
		}) },
		[14] = { text = d[27], active=true, children={15,16,17}, script = curry(make_dialogue, {
			{ items.guybrush, {d[27]}, {animate=false}},
			{ items.mancomb.mancomb, { d[31], d[32], d[33] }, { anim_begin="idle" } },			
		}) },
		[15] = { text = d[34], active = true, children = {18,19,20}, script = curry(make_dialogue, {
			{ items.guybrush, {d[34]}, {animate=false}},
			{ items.mancomb.mancomb, { d[52], d[53] }, { anim_begin="idle" } },			
		}) },
		[16] = { text = d[35], active = true, script = curry(make_dialogue, {
			{ items.guybrush, {d[35]}, {animate=false}},
			{ items.mancomb.mancomb, { d[64], d[65] }, { anim_begin="idle" } },		
			{ items.mancomb.mancomb, { d[66], d[6], d[7] }, { anim_begin="idle" } },				
		}) },
		[17] = { text = d[36] },
		[18] = { text = d[54], active = true, script = curry(make_dialogue, {
			{ items.guybrush, {d[54]}, {animate=false}},
			{ items.mancomb.mancomb, { d[59], d[60], d[61], d[62] }, { anim_begin="idle" } },			
			{ items.mancomb.mancomb, { d[63] }, { anim_begin="smile" } },			
			{ items.mancomb.mancomb, { d[66], d[6], d[7] }, { anim_begin="idle" } },			
		}) },
		[19] = { text = d[55], active = true, script = curry(make_dialogue, {
			{ items.guybrush, {d[55]}, {animate=false}},
			{ items.mancomb.mancomb, { d[58], d[59], d[60], d[61], d[62] }, { anim_begin="idle" } },			
			{ items.mancomb.mancomb, { d[63] }, { anim_begin="smile" } },			
			{ items.mancomb.mancomb, { d[66], d[6], d[7] }, { anim_begin="idle" } },			
		}) },
		[20] = { text = d[56] },
		[21] = { text = d[42] },
		[22] = { text = d[43] },
		[23] = { text = d[44], curry(make_dialogue, {
			{ items.guybrush, {d[44]}, {animate=false}},
			{ items.mancomb.mancomb, { d[6], d[7] }, { anim_begin="idle" } },			
		}) },
		[24] = { text = d[49], active = false, children = {10,11,12,13}, curry(make_dialogue, {
			{ items.guybrush, {d[49]}, {animate=false}},
			{ items.mancomb.mancomb, { d[46], d[18] }, { anim_begin="idle" } },			
		})}


	}
}