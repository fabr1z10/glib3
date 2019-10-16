factory.model = {}

factory.model.create_simple = function(args)
	engine.assets.models[args.id] = {
    	sheet = args.sheet,
    	type = "sprite",
    	ppu=1,
		animations = {
			{ name = "idle", frames = { { duration = 1, quads = {{ id = args.frame }}}}},
		}
	}
end