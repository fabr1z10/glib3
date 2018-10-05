-- voodoo lady dialogue

dialoguesStorekeeper = {}

local d = strings.dialogues.storekeeper.text

function getRandomLines() 
	local a = {
		{d[3]}, 
		{d[6]},
		{d[7], d[8]}
	}
	return a[math.random(1, #a)]
end

-- if Guybrush doesn't have sword nor shovel, just go with an exit line otherwise start dialogue properly
function startDialogueHelper()
	
	if (inventory["sword"] == nil and inventory["shovel"] == nil) then
		local s = dialoguesStorekeeper.leave()
		monkey.play(s)
	else
		local s = script:new()
		s.actions = {
			[1] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=1 }) }
		}
		monkey.play(s)
	end
end

function dialoguesStorekeeper.leave()
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[2] } },
		[2] = say { character="storekeeper", lines = getRandomLines(), after={1} },
		[3] = { type= "resumescript", script ="_storekeeper", after={2} },
		[4] = { type = "callfunc", func = resumePlay, after={3}}
	}
	return s
end

function dialoguesStorekeeper.sword() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[4] } },
		[2] = say { character="storekeeper", lines = {d[12]}, after={1} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=2 }), after={2}}
	}
	return s
end

function dialoguesStorekeeper.swordmaster()
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[34] } },
		[2] = say { character="storekeeper", lines = {d[36], d[37], d[38], d[39], d[40], d[41], d[42], d[43]}, after={1} },
		[3] = { type="activatewall", wall=0, active = false, after={2}},
	    [4] = { type="walkto", actor="storekeeper", pos={85, 15}, after={3}},
	    [5] = { type="animate", actor="door_shop", anim="open", after={4}},
	    [6] = { type="turn", actor="storekeeper", face="east", after={5}},
		[7] = say { character="storekeeper", lines = {d[45]}, after={6} },
	    [8] = { type="animate", actor="door_shop", anim="close", after={7}},
		[9] = { type="activatewall", wall=0, active = true, after={8}},
		[10] = { type="callfunc", func = function() variables.doors.shop = false end, after={9}},
		[11] = { type="callfunc", func = curry(setActive, {id="storekeeper", active=false}), after={10} },
		[12] = { type = "callfunc", func = resumePlay, after={11}},
		[18] = {type="callfunc", func = function() variables.chase=1 end, after={12}},
		[19] = {type="delay", sec=8, after={18}},
		[20] = {type="callfunc", func = function() variables.chase=0 end, after={19}},
		[16] = {type="callfunc", func = curry(setActive, {id="sign", active =true}), after={3}},
		[17] = {type="callfunc", func = curry(setActive, {id="bell", active =true}), after={3}},

	}
	return s

end


function dialoguesStorekeeper.shovel() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[5] } },
		[2] = say { character="storekeeper", lines = {d[12]}, after={1} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=4 }), after={2}}
	}
	return s
end


function dialoguesStorekeeper.iwantsword(n) 
	local s = script:new("_dial")
	if (inventory["pieceofeight"] ~= nil and inventory["pieceofeight"].qty >= 100) then
		s.actions = {
			[1] = say { character = "guybrush", lines = { d[n] } },
			[2] = say { character="storekeeper", lines = {d[31], d[32], d[33]}, after={1} },
			[3] = { type="callfunc", func = curry (pickupItemQty, { name="pieceofeight", qty=-100}), after={2}},
			[4] = { type= "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=1 }), after={3}}
		}
		variables.swordPaid = true
   
	else
		s.actions = {
			[1] = say { character = "guybrush", lines = { d[n] } },
			[2] = say { character="storekeeper", lines = (variables.knowsSwordPrice == false and {d[16], d[17]} or {d[21], d[22]}), after={1} },
			[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=3 }), after={2}}
		}
	end
	variables.knowsSwordPrice = true
	return s

end

function dialoguesStorekeeper.iwantshovel() 
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[13] } },
		[2] = say { character="storekeeper", lines = (variables.knowsShovelPrice == false and {d[23], d[24]} or {d[28], d[29]}), after={1} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=5 }), after={2}}
	}
	variables.knowsShovelPrice = true
	return s

end

function dialoguesStorekeeper.nomoney(n)
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[n] } },
		[2] = say { character = "storekeeper", lines = {d[19]}, after={1} }
	}
	local d1 = createWalkToAction {objectId = "sword", goanyway =true}
	local d2 = drop {obj = "sword"}
	local d3 = createWalkToAction {objectId = "storekeeper"}
	s:push {script =d1, at="end"}
	s:push {script =d2, at="end"}
	s:push {script =d3, at="end"}
	local s1 = script:new()
	s1.actions = {
		[1] = say { character = "storekeeper", lines = {d[20]} },
		[2] = { type ="callfunc", func = startDialogueHelper, after={1} }
	}
	s:push {script =s1, at="end"}
	--s:push {script = startDialogueHelper(), at="end" }
	return s
end

function dialoguesStorekeeper.nomoneyshovel(n)
	local s = script:new("_dial")
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[n] } },
		[2] = say { character = "storekeeper", lines = {d[26]}, after={1} }
	}
	local d1 = createWalkToAction {objectId = "shovel", goanyway =true}
	local d2 = drop {obj = "shovel"}
	local d3 = createWalkToAction {objectId = "storekeeper"}
	s:push {script =d1, at="end"}
	s:push {script =d2, at="end"}
	s:push {script =d3, at="end"}
	local s1 = script:new()
	s1.actions = {
		[1] = say { character = "storekeeper", lines = {d[27]} },
		[2] = { type ="callfunc", func = startDialogueHelper, after={1} }
	}
	s:push {script =s1, at="end"}
	--s:push {script = startDialogueHelper(), at="end" }
	return s
end
