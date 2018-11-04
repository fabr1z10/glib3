-- voodoo lady dialogue

dialoguesFettBros = {}

local d = strings.dialogues.fettbros.text

function dialoguesFettBros.howmuch() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say {character ="guybrush", lines ={d[62]}},
		[2] = say {character ="purple_clown", lines ={d[64]}, after={1}},
		[3] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=3 }), after = {2}}
	}
	return s
end

function dialoguesFettBros.noway(n) 
	local s = script:new("_dial")
	s.actions = {
		[1] = say {character ="guybrush", lines ={d[n]}},
		[2] = { type= "gotoroom", room="clearing", after={1} }
	}
	return s
end

function dialoguesFettBros.closing(n)
	local s = script:new("_dial")
	variables.cannondone = true
	s.actions = {
		[1] = { type="showmessage", color = objects.guybrush.color, message = d[n], pos = {104,90,0} },
		[2] = say {character ="purple_clown", lines ={d[95]}, after={1}},
		[3] = say {character ="green_clown", lines ={d[96]}, after={2}},
		[4] = say {character ="purple_clown", lines ={d[97]}, after={3}},
		[5] = say {character ="green_clown", lines ={d[98], d[99]}, after={4}},
		[6] = say {character ="purple_clown", lines ={d[100]}, after={5}},
		[7] = say {character ="green_clown", lines ={d[101]}, after={6}},
		[8] = say {character ="purple_clown", lines ={d[102]}, after={7}},
		[9] = say {character ="green_clown", lines ={d[103]}, after={8}},
		[10] = say {character ="purple_clown", lines ={d[6]}, after={9}},
		[11] = say {character ="green_clown", lines ={d[7]}, after={10}},
		[12] = say {character ="purple_clown", lines ={d[8]}, after={11}},
		[13] = say {character ="green_clown", lines ={d[9]}, after={12}},
		[14] = { type="callfunc", func = curry(pickupItemQty, {name = "pieceofeight", qty = 478}), after={13}},
		[15] = { type="callfunc", func = curry(dropItem, "pot"), after={14}},
		[16] = { type= "gotoroom", room="clearing", after={15} }
	}
	return s
end

function dialoguesFettBros.doit() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say {character ="guybrush", lines ={d[61]}},
		[2] = say {character ="purple_clown", lines ={d[69], d[70]}, after={1}},
		[3] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=4 }), after = {2}}
	}
	variables.talkedAboutHelmet = true
	return s
end

function dialoguesFettBros.nohelmet() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say {character ="guybrush", lines ={d[71]}},
		[2] = say {character ="green_clown", lines ={d[73]}, after={1}},
		[3] = say {character ="purple_clown", lines ={d[74]}, after={2}},
		[4] = say {character ="green_clown", lines ={d[75]}, after={3}},
		[5] = say {character ="purple_clown", lines ={d[76]}, after={4}},
		[6] = say {character ="green_clown", lines ={d[77]}, after={5}},
		[7] = { type= "gotoroom", room="clearing", after={6} }	
	}
	return s
end

function dialoguesFettBros.ihavehelmet() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say {character ="guybrush", lines ={d[72]}},
		[2] = say {character ="green_clown", lines ={d[78]}, after={1}},
		[3] = say {character ="purple_clown", lines ={d[79]}, after={2}},
		[4] = say {character ="green_clown", lines ={d[80]}, after={3}},
		[5] = say {character ="purple_clown", lines ={d[81]}, after={4}},
		[6] = say {character ="green_clown", lines ={d[75]}, after={5}},
		[7] = { type= "callfunc", func = resumePlay, after={6}}
	}
	return s
end


function dialoguesFettBros.ahem(n) 


	local s = script:new("_dial")
	if (variables.talkedToFettuccini == false) then 
		variables.talkedToFettuccini = true
		s.actions = {
			[1] = { type= "suspendscript", script ="_circus" },
			[2] = say {character ="guybrush", lines ={d[n]}, after = {1}},
			[3] = {type = "animate", actor="purpleclown", anim="idle_front", after={1}},
			[4] = {type = "animate", actor="greenclown", anim="idle_front", after={1}},
			[5] = {type="walkto", actor="purpleclown", pos={148,7},after={2}},
			[6] = {type="walkto", actor="greenclown", pos={218,7},after={2}},
			[7] = {type="turn", actor="purpleclown", face="east", after={5}},
			[8] = {type="turn", actor="greenclown", face="west", after={6}},
			[9] = {type="turn", actor="player", face="south", after={7,8}},
				[10] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=2 }), after = {9}},
			-- [10] = say {character ="purple_clown", lines ={d[34]}, after = {9}},
			-- [11] = {type = "animate", actor="player", anim="idle_front_look_left", after={9}},
			-- [12] = say {character ="green_clown", lines ={d[35]}, after = {10}},
			-- [13] = {type = "animate", actor="player", anim="idle_front_look_right", after={10}},
			-- [14] = say {character ="purple_clown", lines ={d[36]}, after = {12}},
			-- [15] = {type = "animate", actor="player", anim="idle_front_look_left", after={12}},
			-- [16] = say {character ="green_clown", lines ={d[37]}, after = {14}},
			-- [17] = {type = "animate", actor="player", anim="idle_front_look_right", after={14}},	
			-- [18] = say {character ="purple_clown", lines ={d[38]}, after = {16}},
			-- [19] = {type = "animate", actor="player", anim="idle_front_look_left", after={16}},
			-- [20] = say {character ="green_clown", lines ={d[39]}, after = {18}},
			-- [21] = {type = "animate", actor="player", anim="idle_front_look_right", after={18}},	
			-- [22] = say {character ="purple_clown", lines ={d[40]}, after = {20}},
			-- [23] = {type = "animate", actor="player", anim="idle_front_look_left", after={20}},
			-- [24] = say {character ="green_clown", lines ={d[41]}, after = {22}},
			-- [25] = {type = "animate", actor="player", anim="idle_front_look_right", after={22}},	
			-- [26] = say {character ="purple_clown", lines ={d[42]}, after = {24}},
			-- [27] = {type = "animate", actor="player", anim="idle_front_look_left", after={24}},
			-- [28] = say {character ="green_clown", lines ={d[43]}, after = {26}},
			-- [29] = {type = "animate", actor="player", anim="idle_front_look_right", after={26}},	
			-- [30] = say {character ="purple_clown", lines ={d[44]}, after = {28}},
			-- [31] = {type = "animate", actor="player", anim="idle_front_look_left", after={28}},
			-- [32] = say {character ="green_clown", lines ={d[45]}, after = {30}},
			-- [33] = {type = "animate", actor="player", anim="idle_front_look_right", after={30}},	
			-- [34] = say {character ="purple_clown", lines ={d[46]}, after = {32}},
			-- [35] = {type = "animate", actor="player", anim="idle_front_look_left", after={32}},
			-- [36] = say {character ="green_clown", lines ={d[47]}, after = {34}},
			-- [37] = {type = "animate", actor="player", anim="idle_front_look_right", after={34}},
			-- [38] = say {character ="purple_clown", lines ={d[48]}, after = {36}},
			-- [39] = {type = "animate", actor="player", anim="idle_front_look_left", after={36}},
			-- [40] = say {character ="green_clown", lines ={d[49]}, after = {38}},
			-- [41] = {type = "animate", actor="player", anim="idle_front_look_right", after={38}},
			-- [42] = say {character ="purple_clown", lines ={d[50]}, after = {40}},
			-- [43] = {type = "animate", actor="player", anim="idle_front_look_left", after={40}},
			-- [44] = say {character ="green_clown", lines ={d[51]}, after = {42}},
			-- [45] = {type = "animate", actor="player", anim="idle_front_look_right", after={42}},
			-- [46] = say {character ="purple_clown", lines ={d[52]}, after = {44}},
			-- [47] = {type = "animate", actor="player", anim="idle_front_look_left", after={44}},
			-- [48] = say {character ="green_clown", lines ={d[53]}, after = {46}},
			-- [49] = {type = "animate", actor="player", anim="idle_front_look_right", after={46}},
			-- [50] = say {character ="purple_clown", lines ={d[54]}, after = {48}},
			-- [51] = {type = "animate", actor="player", anim="idle_front_look_left", after={48}},
			-- [52] = {type = "animate", actor="player", anim="idle_front_look_right", after={50}},
			-- [53] = {type="delay", sec=1, after={50}},
			-- [54] = say {character ="purple_clown", lines ={d[55]}, after = {53}},
			-- [55] = {type = "animate", actor="player", anim="idle_front_look_left", after={53}},
			-- [56] = say {character ="green_clown", lines ={d[56]}, after = {54}},
			-- [57] = {type = "animate", actor="player", anim="idle_front_look_right", after={54}},
			-- [58] = say {character ="purple_clown", lines ={d[57]}, after = {56}},
			-- [59] = {type = "animate", actor="player", anim="idle_front_look_left", after={56}},
			-- [60] = say {character ="green_clown", lines ={d[58]}, after = {58}},
			-- [61] = {type = "animate", actor="player", anim="idle_front_look_right", after={58}},
			-- [62] = say {character ="purple_clown", lines ={d[59]}, after = {60}},
			-- [63] = {type = "animate", actor="player", anim="idle_front_look_left", after={60}},
			-- [64] = say {character ="green_clown", lines ={d[60]}, after = {62}},
			-- [65] = {type = "animate", actor="player", anim="idle_front_look_right", after={62}},
			-- [65] = {type = "animate", actor="player", anim="idle_front", after={64}},
			-- [66] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=2 }), after = {64}},
		}
	else
		if (variables.talkedAboutHelmet == false) then
			s.actions = {
				[1] = { type= "suspendscript", script ="_circus" },
				[2] = say {character ="guybrush", lines ={d[n]}, after = {1}},
				[3] = {type = "animate", actor="purpleclown", anim="idle_front", after={1}},
				[4] = {type = "animate", actor="greenclown", anim="idle_front", after={1}},
				[5] = {type="walkto", actor="purpleclown", pos={148,7},after={2}},
				[6] = {type="walkto", actor="greenclown", pos={218,7},after={2}},
				[7] = {type="turn", actor="purpleclown", face="east", after={5}},
				[8] = {type="turn", actor="greenclown", face="west", after={6}},
				[9] = {type="turn", actor="player", face="south", after={7,8}},
				[10] = say {character ="purple_clown", lines ={d[67]}, after = {9}},
				[11] = say {character ="green_clown", lines ={d[68]}, after = {10}},
				[12] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=2 }), after = {11}},
			}
		else
			s.actions = {
				[1] = { type= "suspendscript", script ="_circus" },
				[2] = say {character ="guybrush", lines ={d[n]}, after = {1}},
				[3] = {type = "animate", actor="purpleclown", anim="idle_front", after={1}},
				[4] = {type = "animate", actor="greenclown", anim="idle_front", after={1}},
				[5] = {type="walkto", actor="purpleclown", pos={148,7},after={2}},
				[6] = {type="walkto", actor="greenclown", pos={218,7},after={2}},
				[7] = {type="turn", actor="purpleclown", face="east", after={5}},
				[8] = {type="turn", actor="greenclown", face="west", after={6}},
				[9] = {type="turn", actor="player", face="south", after={7,8}},
				[10] = say {character ="purple_clown", lines ={d[67]}, after = {9}},
				[11] = say {character ="green_clown", lines ={d[68]}, after = {10}},
				[12] = say {character ="purple_clown", lines ={d[70]}, after = {11}},
				[13] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=4 }), after = {12}},
			}
		end
	end
	return s
end