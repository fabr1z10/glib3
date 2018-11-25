items.warp = {}


items.warp.create = function(args)
	local pos = args.pos
	local width = args.width
	local height = args.height
	local ctag = args.ctag
	local func = args.func

	local t = args.tag or nextTag()	
	local s = {type="rect", width = width, height = height, offset = {-width/2, 0} }
	return {
		tag = t,
		pos = { pos[1], pos[2], 0},
		components = {
			{ type="collider", shape=s, flag=collisionFlags.enemy, mask = collisionFlags.player, tag = ctag },
			{ type="info", func = func }
		}
	}
end

-- function mario_warptouch(mario, warp) 
-- 	local info = warp:getinfo()
-- 	info.func(info.args)
-- end

function mario_warp_in(mario, warp) 	
	print ("Setting warp function")
	local info = warp:getinfo()
	warpFunction = info.func
end

function mario_warp_out() 
	print ("No warp")
	warpFunction = nil
end


function pipeDown(args) 
 	-- move mario down 
print ("MOVINGF DOWN")
 	local s = script:new()
 	s.actions = {
 		[1] = {type="changestate", actor="player", state="nophys"},
 		[2] = { type="move", by={0, -32}, speed = 25, actor = "player", after={1}},	
		[3] = { type="callfunc", func = curry(switchToArea, (args.area)), after={2}},
 		--[3] = { type="setcambounds", cam ="maincam", xmin=args.xmin, xmax = args.xmax, ymin = args.ymin, ymax = args.ymax, after={2}},
 		--[4] = { type="move", to=Pos{args.x, args.y}, immediate=true, actor="player", after={3}},
 		[4] = {type="changestate", actor="player", state="idle", after={3}},
 	}
 	monkey.play(s)
end

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
