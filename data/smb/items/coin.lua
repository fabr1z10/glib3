items.coin = {}

items.coin.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=16, height=16 }
	local z = args.z or 1
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], z },
		components = {
			{ type="gfx", model = "pickupcoin", anim="idle" },
			{ type="collider", tag=coinTag, flag=collisionFlags.enemy, mask = collisionFlags.player, shape = s },
		},
	}
end

function mario_coin(mario, coin) 
	coin:remove()
end