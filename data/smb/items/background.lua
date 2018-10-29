items.backgroundelement = {}

items.backgroundelement.create = function(args)
	local z =args.z or 1
	return {
		tag = args.tag,
		pos = {args.pos[1], args.pos[2], z},
		components = {
			{ type="gfx", img="gfx/smb1.png", width=args.width, height=args.height, size=16, tiledata=args.tiledata, sheetsize={16, 16}}
		}
	}
end