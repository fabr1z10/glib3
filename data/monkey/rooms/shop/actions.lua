function talkToStorekeeper() 
	s = script:new("_storekeeper2")
	if (inventory["sword"] == nil and inventory["shovel"] == nil) then
		s.actions = {
			[1] = { type="suspendscript", script ="_storekeeper" },
			[2] = say { character = "storekeeper", lines = { strings.dialogues.storekeeper.text[1]}, after={1} },
			[3] = say { character = "guybrush", lines = { strings.dialogues.storekeeper.text[2]}, after={2} },
			[4] = say { character = "storekeeper", lines = { strings.dialogues.storekeeper.text[3]}, after={3} },
			[5] = { type= "resumescript", script ="_storekeeper", after={4} }
		}
	else
		-- If i have either the sword or the shovel, then I start the dialogue
		s.actions = {
			[1] = { type="suspendscript", script ="_storekeeper" },
			[2] = say { character = "storekeeper", lines = { strings.dialogues.storekeeper.text[1]}, after={1} },
			[3] = { type= "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=1, init = true }), after={2} }
		}		
	end
	monkey.play(s)
end

function walkToShopDoor() 
	-- check if we have an unpaid item
	unpaidItem = (inventory["sword"] ~= nil and variables.swordPaid == false) or (inventory["shovel"] ~= nil and variables.shovelPaid == false)
	if (unpaidItem) then
		local s = script:new()
		s.actions = {
			[1] = { type="suspendscript", script ="_storekeeper" },
			[2] = say { character = "storekeeper", lines = { strings.dialogues.storekeeper.text[30]} , after={1}}
		}
		local d1 = createWalkToAction {objectId = "storekeeper"}
		local s1 = script:new()
		s1.actions = {
			[1] = { type = "callfunc", func = curry(startDialogue, { dialogueId="storekeeper", nodeId=1 }) }
		}
		s:push {script=d1, at="end"}
		s:push {script=s1, at="end"}
		return s
	else
		return walkToDoor{ obj = "door_shop_village", roomId = "village3"}
	end

end

