factory.hotspot = {}

factory.hotspot.create = function(args) 
	return 	{
		pos = args.pos,
		components = {
			{ type="hotspot", priority = 1,
				shape = {type="rect", width = args.width, height = args.height },
				onclick = args.onclick }
		}
	}

end