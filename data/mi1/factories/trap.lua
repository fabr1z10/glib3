factory.trap = {}

factory.trap.create = function(args) 
	return {
		pos = args.pos,
		tag= args.tag,
		components = {
			{ type="collider", shape={type="rect", width=args.width, height=args.height}, tag=2, flag=2, mask=1 },
			{ type="info", onenter = args.onenter }
		}
	}

end