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
	s.actions = {
		[1] = say { character = "guybrush", lines = { d[n] } },
		[2] = say { character="storekeeper", lines = (variables.knowsSwordPrice == false and {d[16], d[17]} or {d[21], d[22]}), after={1} },
		[3] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=3 }), after={2}}
	}
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
