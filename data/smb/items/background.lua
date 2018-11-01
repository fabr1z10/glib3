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

items.backgroundelement.castle = function(args) 
	return items.backgroundelement.create { pos = args.pos, z=-1, width=5, height=5, tiledata ={
		15, 1, 15, 1, 13, 4, 15, 1, 15, 1,
		15, 1, 15, 1, 15, 2, 15, 1, 15, 1,
		14, 3, 15, 3, 15, 3, 15, 3, 14, 3,
		-1   , 12, 3, 15 ,1, 13, 3, -1   ,
		-1   , 14, 3, 14, 3, 14, 3, -1   		
	}}
end

items.backgroundelement.pipe2ways = function(args) 
	local z = args.z or 1
	return items.backgroundelement.create { pos = args.pos, z=z, width=4, height=4, tiledata ={
		2, 5, 3, 5, 4, 5, 1, 4,
		2, 4, 3, 4, 4, 4, 1, 4,
		-1  , -1  , 0, 4, 1, 4,
		-1  , -1  , 0, 3, 1, 3
	}}
end