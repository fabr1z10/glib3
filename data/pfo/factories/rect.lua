factory.rect = function(args)
	assert(args.width, "width")
	assert(args.height, "height")
	assert(args.img, "img")
	assert(args.pos, "pos")	
	local z = args.z or 0
	local width = engine.tilesize * args.width
	local height = engine.tilesize * args.height
	local flag = args.flag or 2
	local tag = args.tag or 1
	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, z },
		components = {
			{ type = "gfx", image = args.img, width = width, height = height, rep = {args.width, args.height}},
			{ type = "collider", flag = flag, mask = 1, tag=tag, shape = { type="rect", width = width, height = height }}
		}
	}
end

-- factory.tiledrect = function (args) 
-- 	assert(args.width, "width")
-- 	assert(args.height, "height")
-- 	assert(args.img, "img")
-- 	assert(args.pos, "pos")	
-- 	local z = args.z or 0
-- 	local width = engine.tilesize * args.width
-- 	local height = engine.tilesize * args.height
-- 	return {
-- 		pos = { args.pos[1] * engine.tilesize, args.pos[2] * tilesize, z },
-- 		components = {
-- 			{ type = "gfx", img = args.img, width = width, height = height, sheetsize = {16, 16}, tiledata = args.tiledata
-- 			{ type = "collider", flag = 2, mask = 1, tag=1, shape = { type="rect", width = width, height = height }}
-- 		}
-- 	}


-- end



-- function makeRect(arg)
-- 	local width = 16 * arg.width
-- 	local height = 16 * arg.height
-- 	local s = { type = "rect", width = width, height = height }
-- 	local gfxComponent = nil
-- 	if (arg.gfx ~= nil) then
-- 		gfxComponent = { type ="gfx", image=("gfx/" .. arg.gfx .. ".png"), width = width, height = height, rep={arg.width, arg.height} }
-- 	else
-- 		gfxComponent = { type ="gfx", img="gfx/smb1.png", width=arg.width, height=arg.height, size=16, tiledata=arg.tiledata, sheetsize={16, 16} }
-- 	end
-- 	local z = arg.z or 0
-- 	return {
-- 		pos = {arg.pos[1], arg.pos[2], z},
-- 		components = {
-- 			gfxComponent,	
-- 			{ type ="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0 }
-- 		}
-- 	}
-- end