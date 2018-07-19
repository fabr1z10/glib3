-- lookout dialogue

dialoguesPirates = {}

local d = strings.dialogues.pirates.text


function dialoguesPirates.getlost(l) 

	 s = Script.create("_dial")
	 s:add (say { character = "guybrush", lines = { d[l] } })
	 s:add (say { character="ilp1", lines = {d[5]}, animstart = "talk", animend="idle" })
	 s:add ({{ type = "callfunc", func = resumePlay }})
	 s:setsequence()
	 return s
end

function dialoguesPirates.masteringSword() 
	dialogues.pirates[1].lines[4].active= false
	dialogues.pirates[1].lines[10].active= true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[32] } })
	s:add (say { character="ilp1", lines = {d[42], d[43], d[44], d[45], d[46]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp3", lines = {d[47], d[48]}, animstart = "talk", animend="idle" })
    s:add (say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle" }) 
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
	table.insert(s.edges, {0,1})
	table.insert(s.edges, {1,2})
	table.insert(s.edges, {2,3})
	table.insert(s.edges, {2,4})
	table.insert(s.edges, {2,5})	
	table.insert(s.edges, {3,6})
	table.insert(s.edges, {4,6})
	table.insert(s.edges, {5,6})
	return s
end

function dialoguesPirates.masteringSwordAgain() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[50] } })
	s:add (say { character="ilp1", lines = {d[42], d[43], d[44]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp3", lines = {d[51]}, animstart = "talk", animend="idle" })
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
    s:setsequence()
	return s
end

function dialoguesPirates.masteringThievery() 
	dialogues.pirates[1].lines[5].active= false
	dialogues.pirates[1].lines[11].active= true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[33] } })
	s:add (say { character="ilp2", lines = {d[52]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp1", lines = {d[53]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp3", lines = {d[54]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp2", lines = {d[55]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp1", lines = {d[56]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp3", lines = {d[57]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp1", lines = {d[58], d[59]}, animstart = "talk", animend="idle" })
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
    s:setsequence()
	return s
end

function dialoguesPirates.masteringThieveryAgain() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[60] } })
	s:add (say { character="ilp2", lines = {d[55]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp1", lines = {d[56]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp3", lines = {d[57]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp1", lines = {d[58], d[59]}, animstart = "talk", animend="idle" })
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
    s:setsequence()
	return s
end

function dialoguesPirates.treasureHunting()
	dialogues.pirates[1].lines[6].active= false
	dialogues.pirates[1].lines[12].active= true
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[34] } })
	s:add (say { character="ilp3", lines = {d[61]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp1", lines = {d[62]}, animstart = "talk", animend="idle" })
	s:add (say { character = "guybrush", lines = { d[63] } })
	s:add (say { character="ilp1", lines = {d[64]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp2", lines = {d[65], d[66]}, animstart = "talk", animend="idle" })
    s:add (say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle" }) 
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
	table.insert(s.edges, {0,1})
	table.insert(s.edges, {1,2})
	table.insert(s.edges, {2,3})
	table.insert(s.edges, {3,4})
	table.insert(s.edges, {4,5})	
	table.insert(s.edges, {5,6})
	table.insert(s.edges, {5,7})
	table.insert(s.edges, {5,8})
	table.insert(s.edges, {6,9})
	table.insert(s.edges, {7,9})
	table.insert(s.edges, {8,9})
	return s
end


function dialoguesPirates.treasureHuntingAgain()
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[67] } })
	s:add (say { character="ilp1", lines = {d[62]}, animstart = "talk", animend="idle" })
	s:add (say { character="ilp2", lines = {d[65], d[66]}, animstart = "talk", animend="idle" })
    s:add (say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle" }) 
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
	table.insert(s.edges, {0,1})
	table.insert(s.edges, {1,2})
	table.insert(s.edges, {2,3})
	table.insert(s.edges, {2,4})
	table.insert(s.edges, {2,5})	
	table.insert(s.edges, {3,6})
	table.insert(s.edges, {4,6})
	table.insert(s.edges, {5,6})	
	return s
end

function dialoguesPirates.pigs() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[35] } })
	s:add (say { character="ilp1", lines = {d[68]}, animstart = "talk", animend="idle" }) 
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
    s:setsequence()
	return s
end

function dialoguesPirates.grog() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[36] } })
	s:add (say { character="ilp2", lines = {d[69]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp1", lines = {d[70]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp2", lines = {d[71]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp3", lines = {d[72]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp1", lines = {d[73]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp2", lines = {d[74]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp3", lines = {d[75]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp1", lines = {d[76]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp2", lines = {d[77]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp3", lines = {d[78]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp1", lines = {d[79]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp2", lines = {d[80], d[81]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp1", lines = {d[82]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp1", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp2", lines = {d[49]}, animstart = "talk", animend="idle" }) 
    s:add (say { character="ilp3", lines = {d[49]}, animstart = "talk", animend="idle" }) 
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
	table.insert(s.edges, {0,1})
	table.insert(s.edges, {1,2})
	table.insert(s.edges, {2,3})
	table.insert(s.edges, {3,4})
	table.insert(s.edges, {4,5})	
	table.insert(s.edges, {5,6})	
	table.insert(s.edges, {6,7})	
	table.insert(s.edges, {7,8})
	table.insert(s.edges, {8,9})
	table.insert(s.edges, {9,10})
	table.insert(s.edges, {10,11})
	table.insert(s.edges, {11,12})
	table.insert(s.edges, {12,13})
	table.insert(s.edges, {13,14})
	table.insert(s.edges, {13,15})
	table.insert(s.edges, {13,16})
	table.insert(s.edges, {14,17})
	table.insert(s.edges, {15,17})
	table.insert(s.edges, {16,17})
	return s
end


function dialoguesPirates.leave() 
	s = Script.create("_dial")
	s:add (say { character = "guybrush", lines = { d[37] } })
	s:add (say { character="ilp1", lines = {d[38]}, animstart = "talk", animend="idle" }) 
	s:add (say { character="ilp2", lines = {d[39]}, animstart = "talk", animend="idle" }) 
	s:add ({{ type = "callfunc", func = resumePlay }})
	s:setsequence()
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

	 s = Script.create("_dial")
	 s:add (say { character = "guybrush", lines = { d[3] } })
	 s:add (say { character="ilp1", lines = {d[6]}, animstart = "talk", animend="idle" })
	 s:add (say { character="ilp2", lines = {d[7]}, animstart = "talk", animend="idle" })
     s:add (say { character="ilp3", lines = {d[8]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[9]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp3", lines = {d[10]}, animstart = "talk", animend="idle" })
     s:add (say { character="ilp1", lines = {d[11]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[12]}, animstart = "talk", animend="idle" }) 
	 s:add (say { character = "guybrush", lines = { d[13] } })
     s:add (say { character="ilp1", lines = {d[14]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[15]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp3", lines = {d[16]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[17]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp2", lines = {d[17]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp3", lines = {d[17]}, animstart = "talk", animend="idle" }) 
	 s:add (say { character = "guybrush", lines = { d[18], d[19] } })
     s:add (say { character="ilp2", lines = {d[20]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[21]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp2", lines = {d[22]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp3", lines = {d[23]}, animstart = "talk", animend="idle" })
     s:add (say { character="ilp2", lines = {d[24]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp3", lines = {d[25]}, animstart = "talk", animend="idle" })
     s:add (say { character="ilp2", lines = {d[26]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp2", lines = {d[27]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp2", lines = {d[28]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp2", lines = {d[29]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[30]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp1", lines = {d[31]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp2", lines = {d[31]}, animstart = "talk", animend="idle" }) 
     s:add (say { character="ilp3", lines = {d[31]}, animstart = "talk", animend="idle" }) 
	-- s:add ({{ type = "callfunc", func = resumePlay }})
	s:add ({{ type = "callfunc", func = curry(startDialogue, { dialogueId="pirates", nodeId=1 })}})
	table.insert(s.edges, {0,1})
	table.insert(s.edges, {1,2})
	table.insert(s.edges, {2,3})
	table.insert(s.edges, {3,4})
	table.insert(s.edges, {4,5})	
	table.insert(s.edges, {5,6})	
	table.insert(s.edges, {6,7})	
	table.insert(s.edges, {7,8})
	table.insert(s.edges, {8,9})
	table.insert(s.edges, {9,10})
	table.insert(s.edges, {10,11})
	table.insert(s.edges, {11,12})
	table.insert(s.edges, {11,13})
	table.insert(s.edges, {11,14})
	table.insert(s.edges, {12,15})
	table.insert(s.edges, {13,15})
	table.insert(s.edges, {14,15})
	table.insert(s.edges, {15,16})
	table.insert(s.edges, {16,17})
	table.insert(s.edges, {17,18})
	table.insert(s.edges, {18,19})
	table.insert(s.edges, {19,20})
	table.insert(s.edges, {20,21})
	table.insert(s.edges, {21,22})
	table.insert(s.edges, {22,23})
	table.insert(s.edges, {23,24})
	table.insert(s.edges, {24,25})
	table.insert(s.edges, {25,26})
	table.insert(s.edges, {26,27})
	table.insert(s.edges, {26,28})
	table.insert(s.edges, {26,29})
	table.insert(s.edges, {27,30})
	table.insert(s.edges, {28,30})
	table.insert(s.edges, {29,30})

	 --s:setsequence()
	 return s

end