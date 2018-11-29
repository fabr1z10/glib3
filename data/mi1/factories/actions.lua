
action.random_delay = function(args)
	local id = gr(args.id, "Required id in action.random_delay")
	local after= go(args.after, nil)
	local min = gr(args.min, "Required min in action.random_delay")
	local max = gr(args.max, "Required min in action.random_delay")
	
	return { id = id, after = after, type="delay_dynamic", func = function() return (min + math.random() * (max-min)) end }
end

action.animate = function(args)
	local id = gr(args.id, "Required id in action.animate")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required id in action.animate")
	local item = items[actor]
	local anim = gr(args.anim, "Required id in action.animate")
	return { id = id, after = after, type="animate", actor=item.tag, anim=anim }
end

action.animate_once = function(args)
	local id = gr(args.id, "Required id in action.animate")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required id in action.animate")
	local item = items[actor]
	local anim = gr(args.anim, "Required id in action.animate")
	return { id = id, after = after, type="animate", actor=item.tag, loop=1, anim=anim }
end

action.walkto = function (args) 
print ("canebello")
	local id = gr(args.id, "Required id in action.walkto")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required id in action.walkto")
	local item = items[actor]
	local pos = nil
	if (args.obj == nil) then
		pos = gr(args.pos, "Required object or position in action.walkto")
	else
		local item2 = items[args.obj]
		pos = item2.walk_to
		if (pos == nil) then
			print ("ERROR! Target object needs a <walk_to> field!")
		end
	end
	print ("id... = " .. tostring(id))
	return { id=id, after=after, type="walk", actor=item.tag, pos = pos }

end

action.turn = function (args) 
	local id = gr(args.id, "Required id in action.turn")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required actor in action.turn")
	local dir = gr(args.dir, "Required dir in action.turn")
	return { id=id, after=after, type="turn", actor=actor, dir = dir }

end

action.say = function(args) 
	local id = gr(args.id, "Required id in action.say")
	local after= go(args.after, nil)
	local actor = gr(args.actor, "Required actor in action.say")
	local lines = gr(args.lines, "Required lines to say in action.say")
	local item = items[actor]
	return { id = id, after = after,  type="say", actor= item.tag, lines = lines, offset = item.text_offset, color = item.text_color }
end