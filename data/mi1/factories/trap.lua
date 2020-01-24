scumm.factory.trap = function(args) 
	return {
		pos = args.pos,
		tag= args.tag,
		components = {
			{ type="collider", shape=args.shape, tag=2, flag=2, mask=1 },
			{ type="info", onenter = args.onenter }
		}
	}
end