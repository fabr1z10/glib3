print ("exec <scumm/action> script")
action.scumm = {}

action.scumm.pickup = function(id, anim1, anim2) 
	return { 
		{ ref = 1, type = action.animate, args ={actor="guybrush", anim=anim1, sync=true}},
		{ type = action.remove_object, args ={name=id }},
		{ type = action.animate, after={1}, args ={actor="guybrush", anim=anim2 }},
		{ type = action.add_to_inventory, args = {id=id}}
	}
end

action.scumm.walk_to_object= function(actor, id) 
	return { 
		{ type = action.walkto, args ={actor=actor, obj=id}},
		{ type = action.turn, args = {actor=actor, dir = items2[id].hotspot.dir}}
	}
end
