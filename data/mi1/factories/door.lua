factory.door = {}


factory.door.create =function(args)
	local tag = args.name
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
			
			if (variables[args.door_ref] == 0) then
				return "close"
			else
				return "open"
			end
		end,
		actions = {
			walk = function() 
				if (variables[args.door_ref] == 1) then
					local s = script:new()
					s.actions = { action.change_room { id=1, room = nextroom }}
					return s
					--return change_room( nextroom)
				else
					return nil
				end
			end,
			open = function()
				variables[args.door_ref] = 1
				print ("OPEN!!! " .. tag)
				local s = script:new()
				s.actions = {
					action.animate {id = 1, actor=tag, anim="open" }
				}
				print "OPEN!!!"
				return s
			end,
			close = function()
				variables[args.door_ref] = 0
				local s = script:new()
				s.actions = {
					action.animate {id = 1, actor=tag, anim="close" }
				}
				return s
			end,
		}
	}
end
