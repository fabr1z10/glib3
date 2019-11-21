factory.blocks = {}
factory.npc = {}
factory.bg = {}

factory.blocks.platform = function(gfx) 
	return 
		function(p)
			return factory.rect { pos = {p[1], p[2]}, z=1, img = gfx, width=p[3], height=p[4] }
		end	
end

factory.blocks.basicbrick = function(p) 
	return factory.basic_brick.create { pos = p, sprite="basicbrick", piece="brickpiece" } 
end

factory.blocks.basicbrick_dark = function(p) 
	return factory.basic_brick.create { pos = p, sprite="basicbrick_dark", piece="brickpiece_dark" } 
end

factory.blocks.brickcoin = function(p) 
	return factory.bonus_brick.create { pos= p, sprite="bonusbrick", factory = factory.flyingcoin, args = { sprite="flying_coin" } } 
end

factory.blocks.brickcoinmulti = function(p) 
	return factory.bonus_brick.create { pos= p, sprite="bonusbrick2", hitsleft=5, factory = factory.flyingcoin, args = { sprite="flying_coin" } } 
end

factory.blocks.brickcoinmulti_dark = function(p) 
	return factory.bonus_brick.create { pos= p, sprite="bonusbrick2_dark", hitsleft=5, factory = factory.flyingcoin, args = { sprite="flying_coin" } } 
end

factory.blocks.brickmushroom = function(p)
	return factory.bonus_brick.create { 
		pos= p, 
		sprite="bonusbrick", 
		factory = function()
			local mario = monkey.getEntity("player")
			local state = mario:getinfo().state
			if (state == 1) then
				return factory.mushroom
			else
				return factory.flower
			end
		end,
		args = function() 
			local mario = monkey.getEntity("player")
			local state = mario:getinfo().state
			if (state == 1) then
				return { sprite = "mushroom" }
			else
				return { sprite = "flower" }
			end
		end
	}	  
end

factory.blocks.brickmushroom_dark = function(p)
	return factory.bonus_brick.create { 
		pos= p, 
		sprite="bonusbrick2_dark", 
		factory = function()
			local mario = monkey.getEntity("player")
			local state = mario:getinfo().state
			if (state == 1) then
				return factory.mushroom
			else
				return factory.flower
			end
		end,
		args = function() 
			local mario = monkey.getEntity("player")
			local state = mario:getinfo().state
			if (state == 1) then
				return { sprite = "mushroom" }
			else
				return { sprite = "flower" }
			end
		end
	}	  
end


factory.blocks.brickstarman = function(p) 
	return factory.bonus_brick.create { pos= p, sprite="bonusbrick2", factory = factory.starman, args = { sprite="starman" } } 
end
factory.blocks.brickstarman_dark = function(p) 
	return factory.bonus_brick.create { pos= p, sprite="bonusbrick2_dark", factory = factory.starman, args = { sprite="starman" } } 
end
factory.blocks.brickoneuphidden = function(p) 
	return factory.bonus_brick.create { pos= p, sprite="hiddenbrick", factory = factory.mushroom, args = { sprite="mushroom1up", oneup=true } } 
end

factory.blocks.pipe_2_green = function(p) 
	return factory.tiled.create { pos = p, z=1, width=2, height=2, collide=true, tiledata = {0,4,1,4,0,3,1,3}, img = "smb1.png"} 
end

factory.blocks.pipe_3_green = function(p) 
	return factory.tiled.create { pos = p, width=2, height=3, collide=true, tiledata = {0,4,1,4,0,4,1,4,0,3,1,3}, img = "smb1.png"} 
end

factory.blocks.pipe_4_green = function(p) 
	return factory.tiled.create { pos = p, width=2, height=4, collide=true, tiledata = {0,4,1,4,0,4,1,4,0,4,1,4,0,3,1,3}, img = "smb1.png"} 
end

factory.blocks.pickupcoin = function(p) 
	return factory.coin.create { model="pickup_coin", pos = p}
end

factory.blocks.platform1 = function(p) 
	local td = {1,15}
	for i = 1, p[3]-2 do 
		table.insert(td, 2) 
		table.insert(td, 15)
	end     -- count from 1 to 3
	table.insert(td, 3)
	table.insert(td, 15)
	return factory.tiled.create { pos = {p[1],p[2]}, width = p[3], height=1, tiledata = td, img="smb1.png", collide=true }
end


factory.blocks.spawn = function(f)
	return function(p) 
		return factory.spawn.create { 
			width=1, 
			height=256, 
			use_once=true, 
			pos= {p[1],p[2]}, 
			func = f, 
			itempos = {p[3],p[4]}
		}
	end
end


factory.npc.goomba = function(p) 
	return factory.goomba.create {
		pos = p, 
		sprite="goomba",
		flip = true, 
	}
end
factory.npc.koopa = function(p) 
	return factory.koopa.create {
		pos = p, 
		sprite="koopa",
		flip = true, 
	}
end

factory.npc.plant = function(p)
	return factory.plant.create {pos=p, sprite="plant"}
end

factory.npc.rotatingfire = function(p)
	return factory.rotatingfire.create { pos = {p[1],p[2]}, n=p[3], model="enemy_fire"}
end

factory.bg.tiled = function(temp,z) 
	return function(p) return factory.tiled.create_from { pos = p, z=z or -1.0,template = temp } end 
end

factory.bg.tiled_one = function(args, p)
	return function(p) return factory.tiled.create { pos = {p[1],p[2]}, z=args.z or -1.0,width =p[3], height=p[4], tiledata = args.tile, img = args.img, collide=args.collide, sheetsize ={engine.tilesize,engine.tilesize} } end 
end


factory.blocks.warp_down = function(args) 
	return function(p)
		return factory.warp.create { 
			pos = p, 
			width = 14, 
			height = 2, 
			func = function() 
				local mario = monkey.getEntity("player")
				mario.state = "warp"
				variables.warpfunc = nil
				local actions = {
					{ type = action.move, args = {tag="player", by = {0, -32}, speed = 50}},
					{ type = action.move, args = {tag="player", to = {args.to[1]*engine.tilesize,args.to[2]*engine.tilesize}, imm = true}},
					{ type = action.set_state, args = {tag="player", state="jump"}},
					{ type = action.activate, args = {tag ="bg", active=false}},
					{ type = action.change_cam_bounds, args = {cam="maincam", x= args.x_bounds, y = args.y_bounds}}
				}
				local s = script.make(actions)
				monkey.play(s)	
			end
		}
	end
end


factory.blocks.warp_up = function(args) 
	return function(p)
		return factory.hotspot.create { 
			pos = p, 
			width = 14, 
			height = 2, 
			func = function() 
				local actions = {
					{ type = action.set_state, args = {tag = "player", state = "walk"}},
					{ type = action.set_demo_mode, args = { tag="player", value=true, sync = true, length = 1, events = {
						{ t=0, key = 262, event ="down"}
					}}},
					{ type = action.set_state, args = {tag="player", state="warp"}},
					{ type = action.move, args = {tag="player", to = {args.to[1]*engine.tilesize,args.to[2]*engine.tilesize}, imm = true}},
					{ type = action.activate, args = {tag ="bg", active=true}},
					{ type = action.change_cam_bounds, args = {cam="maincam", x= args.x_bounds, y = args.y_bounds}},
					{ type = action.move, args = {tag="player", by = {0, 64}, speed = 50}},
					{ type = action.set_state, args = {tag = "player", state = "walk"}},
				}
				local s = script.make(actions)
print ("CAZZO DURO")
				monkey.play(s)				
			end
		}
	end
end
 
factory.blocks.end_level_pole = function(p) 
	return factory.hotspot.create { 
		pos = p, 
		width = 2, 
		height = 256, 
		func = function(mario, hotspot)
			local mario = monkey.getEntity("player")
			hotspot:remove()
			mario.state = "slide"
			local delta = math.abs(mario.y - 48, 0)
			local actions = {
				{ type = action.noop, ref = 1},
				{ type = action.move, ref = 2, after={1}, args = {tag="player", by = {0, -delta}, speed = 50}},
				{ type = action.move, after={1}, args = {tag="flag", by = {0, -128}, speed = 50}},
				{ type = action.set_state, after= {2}, args = {tag = "player", state = "walk"}},
				{ type = action.set_demo_mode, args = { tag="player", value=true, sync = true, length = 10, events = {
					{ t=0, key = 262, event ="down"}
				}}},
			}
			local s = script.make(actions)
			monkey.play(s)		
		end
	}
end

factory.blocks.touchdown = function(p)
	return factory.hotspot.create { 
		pos = p, 
		width = 2, 
		height = 2, 
		func = function(mario, hotspot)
			mario:setactive(false)
			local actions = {
				{ type = action.create_object, args = { factory = factory.simplesprite.create,
					args = { tag="end_level", model = "castle_flag", pos ={204, 5},z =-1.0 }}},
				{ type = action.move, args = {tag="end_level", by = {0, 32}, speed = 20}},
			 	{ type = action.delay, args = { sec = 2}},
			 	{ type = action.change_room, args = {room=room.next}}
			}
			local s = script.make(actions)
			monkey.play(s)	
		end
	}
end


factory.blocks.moving_platform = function(p) 
	return factory.movingplatform.create { 
		pos = {p[1], p[2]},
		width=3, 
		tile = {15,5},
		--speed=20, 
		img="smb1.png", 
		loop_type = 1,
		start_index = p[3],
		pct = p[4],
		movements = {
			{ delta = {0, p[5]}, speed = 50 }
		},
		callback = function(platform) 
			platform:dropcharacters()
		end
	}
end

factory.blocks.moving_platform_2 = function(p) 
	return factory.movingplatform.create { 
		pos = {p[1], p[2]},
		width=3, 
		tile = {15,5},
		--speed=20, 
		img="smb1.png", 
		loop_type = 0,
		start_index = p[3],
		pct = p[4],
		movements = {
			{ delta = {p[5], p[6]}, speed = 50 }
		},
		callback = function(platform) 
			platform:dropcharacters()
		end
	}
end