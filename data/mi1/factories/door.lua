factory.door = {}


factory.door.create =function(args)
	local tag = args.tag
	local pos = args.pos
	local size = args.size
	local offset = args.offset
	local walk_to = args.walk_to
	local face = args.face
	local model = args.model
	local nextroom = args.nextroom

	return {
		tag = tag, 
		text = strings.objects.door,
		pos = pos,
		size = size,
		offset = offset,
		walk_to = walk_to,
		face = face,
		model = model,
		anim = function() 
			if (args.door_ref == 0) then
				return "close"
			else
				return "open"
			end
		end,
		actions = {
			walk = function() 
				if (args.door_ref == 1) then
					return change_room( nextroom)
				else
					return nil
				end
			end,
			open = function()
				args.door_ref = 1
				local s = script:new()
				s.actions = {
					[1] = { type="animate", actor=tag, anim="open" }
				}
				return s
			end,
			close = function()
				args.door_ref = 0
				local s = script:new()
				s.actions = {
					[1] = { type="animate", actor=tag, anim="close" }
				}
				return s
			end,
		}
	}
end
