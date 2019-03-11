print ("exec <scumm/action> script")

scumm.action = {}

scumm.action.walkto = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	local pos = args.pos
	if (pos == nil) then
		assert (args.obj, "pos or obj")
		local obj = items[args.obj]
		pos = obj.hotspot.walk_to
	end	
	return { type="walk", tag = args.tag, id = args.id, pos = pos }
end

scumm.action.turn = function (args) 
	glib.assert_either (args.tag, args.id, "id or tag")
	assert (args.dir, "dir")
	return { type="turn", tag = args.tag, id = args.id, dir = args.dir }

end

scumm.action.pickup = function(id, anim1, anim2) 
	return { 
		{ ref = 1, type = action.animate, args ={actor="guybrush", anim=anim1, sync=true}},
		{ type = action.remove_object, args ={name=id }},
		{ type = action.animate, after={1}, args ={actor="guybrush", anim=anim2 }},
		{ type = action.add_to_inventory, args = {id=id}}
	}
end

scumm.action.walk_to_object= function(actor, id) 
	return { 
		{ type = action.walkto, args ={actor=actor, obj=id}},
		{ type = action.turn, args = {actor=actor, dir = items2[id].hotspot.dir}}
	}
end