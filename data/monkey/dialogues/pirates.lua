-- lookout dialogue

dialoguesPirates = {}

local d = strings.dialogues.pirates.text


function dialoguesPirates.getlost(l) 
	s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[l] } },
		[2] = say { character="ilp1", lines = {d[5]}, animstart = "talk", animend="idle", after={1} },
		[3] = { type = "callfunc", func = resumePlay, after={2}}
	}
	return s
end

function dialoguesPirates.masteringSword() 
	dialogues.pirates[1].lines[4].active= false
	dialogues.pirates[1].lines[10].active= true
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[32] } },
		[2] = say { character="ilp1", lines = {d[42], d[43], d[44], d[45], d[46]}, animstart = "talk", animend="idle", after={1} },
		[3] = say { character="ilp3", lines = {d[47], d[48]}, animstart = "talk", animend="idle", after={2} },
    	[4] = say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle", after={3} },
    	[5] = say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle", after={3} },
    	[6] = say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle", after={3} },
		[7] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={4,5,6}}
	}
	return s
end

function dialoguesPirates.masteringSwordAgain() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[50] } },
		[2] = say { character="ilp1", lines = {d[42], d[43], d[44]}, animstart = "talk", animend="idle", after={1} },
		[3] = say { character="ilp3", lines = {d[51]}, animstart = "talk", animend="idle", after={2} },
		[4] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={3} }
	}
	return s
end

function dialoguesPirates.masteringThievery() 
	dialogues.pirates[1].lines[5].active= false
	dialogues.pirates[1].lines[11].active= true
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[33] }},
		[2] = say { character="ilp2", lines = {d[52]}, animstart = "talk", animend="idle", after={1} },
		[3] = say { character="ilp1", lines = {d[53]}, animstart = "talk", animend="idle", after={2} },
		[4] = say { character="ilp3", lines = {d[54]}, animstart = "talk", animend="idle", after={3} },
		[5] = say { character="ilp2", lines = {d[55]}, animstart = "talk", animend="idle", after={4} },
		[6] = say { character="ilp1", lines = {d[56]}, animstart = "talk", animend="idle", after={5} },
		[7] = say { character="ilp3", lines = {d[57]}, animstart = "talk", animend="idle", after={6} },
		[8] = say { character="ilp1", lines = {d[58], d[59]}, animstart = "talk", animend="idle", after={7}},
		[9] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={8}}
    }
	return s
end

function dialoguesPirates.masteringThieveryAgain() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[60] } },
		[2] = say { character = "ilp2", lines = {d[55]}, animstart = "talk", animend="idle", after={1} },
		[3] = say { character = "ilp1", lines = {d[56]}, animstart = "talk", animend="idle", after={2} },
		[4] = say { character = "ilp3", lines = {d[57]}, animstart = "talk", animend="idle", after={3} },
		[5] = say { character="ilp1", lines = {d[58], d[59]}, animstart = "talk", animend="idle", after={4}},
		[6] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={5}}
	}
	return s
end

function dialoguesPirates.treasureHunting()
	dialogues.pirates[1].lines[6].active= false
	dialogues.pirates[1].lines[12].active= true
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[34] } },
		[2] = say { character="ilp3", lines = {d[61]}, animstart = "talk", animend="idle", after={1}},
		[3] = say { character="ilp1", lines = {d[62]}, animstart = "talk", animend="idle", after={2}},
		[4] = say { character = "guybrush", lines = { d[63] }, after={3} },
		[5] = say { character="ilp1", lines = {d[64]}, animstart = "talk", animend="idle", after={4}},
		[6] = say { character="ilp2", lines = {d[65], d[66]}, animstart = "talk", animend="idle", after={5}},
    	[7] = say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle", after={6}},
    	[8] = say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle", after={6}},
    	[9] = say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle", after={6}},
		[10] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={7,8,9}}
	}
	return s
end


function dialoguesPirates.treasureHuntingAgain()
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[67] } },
		[2] = say { character="ilp1", lines = {d[62]}, animstart = "talk", animend="idle", after={1}},
		[3] = say { character="ilp2", lines = {d[65], d[66]}, animstart = "talk", animend="idle", after={2}},
    	[4] = say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle", after={3}},
    	[5] = say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle", after={3}},
    	[6] = say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle", after={3}},
		[7] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={4,5,6}}
	}
	return s
end

function dialoguesPirates.pigs() 
	local s = script:new("_dial")
	s.actions = {	
		[1] = say { character = "guybrush", lines = { d[35] } },
		[2] = say { character="ilp1", lines = {d[68]}, animstart = "talk", animend="idle", after={1}},
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={2}}
	}
	return s
end

function dialoguesPirates.grog() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[36] } },
		[2] = say { character="ilp2", lines = {d[69]}, animstart = "talk", animend="idle", after={1}},
		[3] = say { character="ilp1", lines = {d[70]}, animstart = "talk", animend="idle", after={2}},
		[4] = say { character="ilp2", lines = {d[71]}, animstart = "talk", animend="idle", after={3}},
		[5] = say { character="ilp3", lines = {d[72]}, animstart = "talk", animend="idle", after={4}},
		[6] = say { character="ilp1", lines = {d[73]}, animstart = "talk", animend="idle", after={5}},
		[7] = say { character="ilp2", lines = {d[74]}, animstart = "talk", animend="idle", after={6}},
		[8] = say { character="ilp3", lines = {d[75]}, animstart = "talk", animend="idle", after={7}},
		[9] = say { character="ilp1", lines = {d[76]}, animstart = "talk", animend="idle", after={8}},
		[10] = say { character="ilp2", lines = {d[77]}, animstart = "talk", animend="idle", after={9}},
		[11] = say { character="ilp3", lines = {d[78]}, animstart = "talk", animend="idle", after={10}},
		[12] = say { character="ilp1", lines = {d[79]}, animstart = "talk", animend="idle", after={11}},
		[13] = say { character="ilp2", lines = {d[80], d[81]}, animstart = "talk", animend="idle", after={12}},
		[14] = say { character="ilp1", lines = {d[82]}, animstart = "talk", animend="idle", after={13}},
    	[15] = say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle", after={14}},
    	[16] = say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle", after={14}},
    	[17] = say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle", after={14}},
		[18] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={15,16,17}}
	}
	return s
end


function dialoguesPirates.leave() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[37] } },
		[2] = say { character="ilp1", lines = {d[38]}, animstart = "talk", animend="idle", after={1}},
		[3] = say { character="ilp2", lines = {d[39]}, animstart = "talk", animend="idle", after={2}},
		[4] = { type = "callfunc", func = resumePlay, after={3}}
	}
	return s
end

function dialoguesPirates.iwanttobeapirate()
	variables.talkedToPirates = true
	dialogues.pirates[1].lines[1].active= false
	dialogues.pirates[1].lines[2].active= false
	dialogues.pirates[1].lines[3].active= false
	dialogues.pirates[1].lines[4].active= true
	dialogues.pirates[1].lines[5].active= true
	dialogues.pirates[1].lines[6].active= true
	dialogues.pirates[1].lines[7].active= true
	dialogues.pirates[1].lines[8].active= true
	dialogues.pirates[1].lines[9].active= true

	s = script:new("_dial")
	
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[3] } },
	 	[2] = say { character="ilp1", lines = {d[6]}, animstart = "talk", animend="idle", after={1} },
	 	[3] = say { character="ilp2", lines = {d[7]}, animstart = "talk", animend="idle", after={2} },
    	[4] = say { character="ilp3", lines = {d[8]}, animstart = "talk", animend="idle", after={3} }, 
     	[5] = say { character="ilp1", lines = {d[9]}, animstart = "talk", animend="idle", after={4} },
     	[6] = say { character="ilp3", lines = {d[10]}, animstart = "talk", animend="idle", after={5} },
     	[7] = say { character="ilp1", lines = {d[11]}, animstart = "talk", animend="idle", after={6} },
     	[8] = say { character="ilp1", lines = {d[12]}, animstart = "talk", animend="idle", after={7} },
	 	[9] = say { character = "guybrush", lines = { d[13] }, after={8} },
     	[10] = say { character="ilp1", lines = {d[14]}, animstart = "talk", animend="idle", after={9}},
     	[11] = say { character="ilp1", lines = {d[15]}, animstart = "talk", animend="idle", after={10} },
     	[12] = say { character="ilp3", lines = {d[16]}, animstart = "talk", animend="idle", after={11} },
     	[13] = say { character="ilp1", lines = {d[17]}, animstart = "talk", animend="idle", after={12} },
     	[14] = say { character="ilp2", lines = {d[17]}, animstart = "talk", animend="idle", after={12} },
     	[15] = say { character="ilp3", lines = {d[17]}, animstart = "talk", animend="idle", after={12} },
	 	[16] = say { character = "guybrush", lines = { d[18], d[19] }, after = {13,14,15} },
     	[17] = say { character="ilp2", lines = {d[20]}, animstart = "talk", animend="idle", after= {16}}, 
     	[18] = say { character="ilp1", lines = {d[21]}, animstart = "talk", animend="idle", after={17}},
     	[19] = say { character="ilp2", lines = {d[22]}, animstart = "talk", animend="idle", after={18}},
     	[20] = say { character="ilp3", lines = {d[23]}, animstart = "talk", animend="idle", after={19}},
     	[21] = say { character="ilp2", lines = {d[24]}, animstart = "talk", animend="idle", after={20}},
     	[22] = say { character="ilp3", lines = {d[25]}, animstart = "talk", animend="idle", after={21}},
     	[23] = say { character="ilp2", lines = {d[26]}, animstart = "talk", animend="idle", after={22}},
     	[24] = say { character="ilp2", lines = {d[27]}, animstart = "talk", animend="idle", after={23}},
     	[25] = say { character="ilp2", lines = {d[28]}, animstart = "talk", animend="idle", after={24}},
     	[26] = say { character="ilp2", lines = {d[29]}, animstart = "talk", animend="idle", after={25}},
     	[27] = say { character="ilp1", lines = {d[30]}, animstart = "talk", animend="idle", after={26}},
     	[28] = say { character="ilp1", lines = {d[31]}, animstart = "talk", animend="idle", after={27}},
		[29] = say { character="ilp2", lines = {d[31]}, animstart = "talk", animend="idle", after={27}},
     	[30] = say { character="ilp3", lines = {d[31]}, animstart = "talk", animend="idle", after={27}},
		[31] = { type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 }), after={28,29,30}}
	}
    return s

end