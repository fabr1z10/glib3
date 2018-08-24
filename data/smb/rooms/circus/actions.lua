local d = strings.dialogues.fettbros.text
function showPot() 
	local s = script:new()	
	s.actions = {
		[1] = { type="callfunc", func=startScript },
    	[2] = { type="animate", actor="player", anim="pot_out", loop=1, after={1} },
		[3] = { type="animate", actor="player", anim="show_pot", after={2} },
		[4] = say {character ="green_clown", lines ={d[82]}, after={3}},
		[5] = { type="animate", actor="player", anim="pot_in", loop=1, after={4} },
		[6] = { type="animate", actor="player", anim="idle_front", after={5} },
		[7] = say {character ="purple_clown", lines ={d[83]}, after={6}},
		[8] = { type="animate", actor="player", anim="idle_front_look_right", after={7} },
		[9] = say {character ="green_clown", lines ={d[84]}, after={8}},
		[10] = { type= "scroll", cam ="maincam", by = {48, 0}, speed = 50, after={9} },
		[11] = { type="walkto", actor="purpleclown", pos={333, 1},after={9}},
		[12] = { type="walkto", actor="greenclown", pos={296, 24},after={9}},
		[13] = { type="walkto", actor="player", pos={250, 24},after={9}},
		[14] = { type="turn", actor="player", face="south", after={13}},			
		[15] = { type="turn", actor="purpleclown", face="north", after={11}},			
		[16] = { type="turn", actor="greenclown", face="west", after={12}},			

		[17] = say {character ="purple_clown", lines ={d[85]}, after={14,15,16}},
		[18] = say {character ="green_clown", lines ={d[86]}, after={17}},
		[19] = say {character ="purple_clown", lines ={d[87]}, after={18}},
		[20] = { type="walkto", actor="player", pos={264, 23},after={19}},
		[21] = { type="turn", actor="player", face="east", after={20}},			
		[22] = say {character ="guybrush", lines ={d[88]}, after={21}},
		[23] = { type="walkto", actor="player", pos={250, 24},after={22}},
		[24] = { type="turn", actor="player", face="south", after={23}},		
		[25] = { type="animate", actor="player", anim="get_in_cannon", loop=1, after={24} },
		[26] = { type= "callfunc", func = curry (setActive, {id = "player", active=false }), after = {25} },
		[27] = { type= "callfunc", after={26}, func = curry (createObject, { 
				pos = {0, 0, 0},
				tag = "explosion",
				gfx = { model = "explosion", anim = "default" }})},
		[28] = { type= "callfunc", after={26}, func = curry (createObject, { 
				pos = {0, 0, 0},
				tag = "flyingguybrush",
				gfx = { model = "flyingguy", anim = "default" }})},
		[29] = { type="animate", actor="explosion", anim="default", loop=1, after={27} },
		[30] = { type="animate", actor="flyingguybrush", anim="default", loop=1, after={28} },
		[31] = { type= "callfunc", func = curry (setActive, {id = "explosion", active=false }), after = {29} },
		[32] = { type="animate", actor="flyingguybrush", anim="end", after={30} },
		[33] = say {character ="purple_clown", lines ={d[89]}, after={32}},
		[34] = say {character ="green_clown", lines ={d[90]}, after={33}},
		[35] = { type="walkto", actor="purpleclown", pos={87, 29},after={34}},
		[36] = { type="walkto", actor="greenclown", pos={126,29},after={34}},
		[37] = { type="turn", actor="purpleclown", face="east", after={35}},			
		[38] = { type="turn", actor="greenclown", face="west", after={36}},			
		[39] = say {character ="purple_clown", lines ={d[91]}, after={37,38}},
		[40] = say {character ="green_clown", lines ={d[92]}, after={39}},
		[41] = { type= "callfunc", func = curry(startDialogue, { dialogueId="fettbros", nodeId=5}), after = {40} }


	}
	return s
end
