factory.warp = {}

factory.warp.create = function(args)
	assert(args.width, "width")
	assert(args.height, "height")
	assert(args.pos, "pos")
	assert(args.func, "pos")

	local s = {type="rect", width=args.width, height=args.height, offset = {-args.width/2, 0} }
	return {
		pos = { args.pos[1]*engine.tilesize, args.pos[2]*engine.tilesize, 0},
		components = {
			{ type="collider", shape=s, flag=variables.collision.flags.foe, mask = variables.collision.flags.player, tag = variables.collision.tags.warp },
			{ type="info", func = args.func }
		}
	}
end

factory.warp.response = function (mario, warp, sx, sy) 
	print ("entering")
	local warp_info = warp:getinfo()
	variables.warpfunc = warp_info.func
end

factory.warp.onexit = function (mario, warp, sx, sy) 
	print ("leaving")
	variables.warpfunc = nil
end

-- function mario_warptouch(mario, warp) 
-- 	local info = warp:getinfo()
-- 	info.func(info.args)
-- end

-- function mario_warp_in(mario, warp) 
-- 	local info = warp:getinfo()
-- 	warpFunction = info.func
-- end

-- function mario_warp_out() 
-- 	print ("No warp")
-- 	warpFunction = nil
-- end

-- function pipeDown(args) 
-- 	-- move mario down 
-- 	local s = script:new()
-- 	s.actions = {
-- 		[1] = {type="changestate", actor="player", state="nophys"},
-- 		[2] = { type="move", by={0, -32}, speed = 25, actor = "player", after={1}},		
-- 		[3] = { type="setcambounds", cam ="maincam", xmin=args.xmin, xmax = args.xmax, ymin = args.ymin, ymax = args.ymax, after={2}},
-- 		[4] = { type="move", to=Pos{args.x, args.y}, immediate=true, actor="player", after={3}},
-- 		[5] = {type="changestate", actor="player", state="idle", after={4}},
-- 	}
-- 	monkey.play(s)
-- end

-- function pipeRight(args) 
-- 	-- move mario down 
-- 	local s = script:new()
-- 	s.actions = {
-- 		[1] = { type="changestate", actor="player", state="nophys"},
-- 		[2] = { type="animate", actor ="player", anim="walk", flipx = false, after={1}},
-- 		[3] = { type="move", by={32, 0}, speed = 25, actor = "player", after={2}},		
-- 		[4] = { type="setcambounds", cam ="maincam", xmin=args.xmin, xmax = args.xmax, ymin = args.ymin, ymax = args.ymax, after={3}},
-- 		[5] = { type="move", to=Pos{args.x, args.y}, immediate=true, actor="player", after={4}},
-- 		[6] = { type="animate", actor ="player", anim="idle", flipx = false, after={5}},
-- 		[7] = { type="move", by={0, 32}, speed = 25, actor = "player", after={6}},		
-- 		[8] = { type="changestate", actor="player", state="idle", after={7}},
-- 	}
-- 	monkey.play(s)
-- end

