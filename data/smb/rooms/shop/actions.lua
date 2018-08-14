function talkToStorekeeper() 
	s = script:new("_storekeeper2")
	s.actions = {
		[1] = { type="suspendscript", script ="_storekeeper" },
		[2] = say { character = "storekeeper", lines = { strings.dialogues.storekeeper.text[1]}, after={1} },
		[3] = say { character = "guybrush", lines = { strings.dialogues.storekeeper.text[2]}, after={2} },
		[4] = say { character = "storekeeper", lines = { strings.dialogues.storekeeper.text[3]}, after={3} },
		[5] = { type= "resumescript", script ="_storekeeper", after={4} }
	}
	monkey.play(s)
end


