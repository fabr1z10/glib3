factory.player = {}

local face_map = {
	east = { sprite="idle_right", flip=false},
	west = { sprite="idle_right", flip=true},
	north = { sprite="idle_back", flip=false},
	south = { sprite="idle_front", flip=false}
}

factory.player.create = function(args)
	local pos = args.pos
	local model = args.model
	local facing = args.facing
	local f = face_map[facing]
	
	local components = {
		{ type="gfx", model = model, anim = f.sprite, flip = f.flip }
	}
	print("ADDING SCROLLING?")
	if (args.scroll) then 
		print ("YES")
		table.insert(components, { type="follow", cam ="maincam", relativepos = {0,0,5}, up={0,1,0}})
	else
		print ("NO")
	end
	if (args.depth ~= nil or args.scale ~= nil) then
		table.insert(components, { type="depth", depth = args.depth, scale = args.scale })
	end


	return
	{
		tag = "player",
		pos = {pos[1], pos[2], 0},
		components = components
	}
end
