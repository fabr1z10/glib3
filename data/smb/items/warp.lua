items.warp = {}

items.warp.create = function(args)
	local t = nextTag()	
	local s = {type="rect", width=args.width, height=args.height, offset = {-args.width/2, 0} }
	return {
		tag = t,
		pos = { args.pos[1], args.pos[2], 0},
		components = {
			{ type="collider", shape=s, flag=4, tag = warpTag },
			{ type="info", func = args.func }
		}
	}
end



function mario_warp_in(mario, warp) 
	local info = warp:getinfo()
	warpFunction = info.func
end

function mario_warp_out() 
	print ("No warp")
	warpFunction = nil
end

function pipeDown(args) 
	-- move mario down 
	
	local s = script:new()
	s.actions = {
		[1] = {type="changestate", actor="player", state="nophys"},
		[2] = { type="move", by={0, -32}, speed = 25, actor = "player", after={1}},		
		[3] = { type="setcambounds", cam ="maincam", xmin=args.xmin, xmax = args.xmax, ymin = args.ymin, ymax = args.ymax, after={2}},
		[4] = { type="move", to=Pos{args.x, args.y}, immediate=true, actor="player", after={3}},
		[5] = {type="changestate", actor="player", state="idle", after={4}},
	}
	monkey.play(s)
end