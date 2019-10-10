factory.sprite = {}

factory.sprite.create = function(args)

	glib.assert (args.model, "model")
	glib.assert (args.pos, "pos")
	local pos = args.pos 
	return {	
		tag = args.tag,
		type="sprite",
		model=args.model,
		anim=args.anim,
		flipx = args.flipx,
		scale =args.scale or 1,
		pos = {pos[1], pos[2], 0},
	}
end