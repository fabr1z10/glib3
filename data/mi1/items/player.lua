items.player = {}

local face_map = {
	east = { sprite="idle_right", flip=true},
	west = { sprite="idle_right", flip=false},
	north = { sprite="idle_back", flip=false},
	south = { sprite="idle_front", flip=false}
}

items.player.create = function(args)
	local pos = args.pos
	local model = args.model
	local facing = args.facing
	local f = face_map[facing]
	
	return
	{
		tag = "player",
		pos = {pos[1], pos[2], 0},
		components = {
			{ type="gfx", model = model, anim = f.sprite, flip = f.flip }
		}
	}
end
