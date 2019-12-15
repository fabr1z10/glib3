function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function makeItem (args)
	local x  = args.x or 0
	local y = args.y or 0
	local z = args.z or 0 
	local shape = nil
	if (args.outline) then
		shape = { type="poly", outline = args.outline }
	else 
		shape = { type="rect", width = args.width, height = args.height, offset = args.offset }
	end
	return {
		tag = args.tag,
		pos={x,y,z},
		hotspot = {
			priority = args.priority or 1,
			shape = shape
		},
		actions = {
			look = args.look or  {
				{ type = action.kq.showmessage, args = { msg=args.msg}}
			},
			talk = args.talk,
			use = args.use
		},
		gfx = args.gfx,
		hole = args.hole,
		model = args.model
	}
end

function makeRoomChange (args) 
	return 
	{ 
		pos = {args.x,args.y,0},
		components = {
			{ type = "collider", flag = 32, mask = 1, tag=10, 
 					shape = { type="rect", width = args.width, height = args.height }
 			},
 			{ type = "info", func = function() 
 				local actions = {
					{ type = action.change_room, args = {room = args.room}}
				}
 				local s = script.make(actions)
 				monkey.play(s)
 				end 
			}
 		}
 	}
end


function makeShape (arg)
	return {
		pos = arg.pos,
		angle = arg.angle,
		gfx = {shape=arg.shape, color={255,255,255,255} },
		collider= {shape=arg.shape, tag=arg.tag, flag = arg.flag},
		info = arg.info
	}
end

function changeRoom(o1, o2)
	local a = o2:getinfo()
	print (a.roomto)
	local s = script:new("_cr")

	s.actions = {
		[1] = {type="gotoroom", room=a.roomto }
	}
	monkey.play(s)

end

function exitpause() 
	if (engine.config.pause == true) then
		print ("Exit pause mode")
	    local parent = monkey.getEntity("main")
		--local ui = monkey.getEntity("ui")
		if (engine.config.msgid ~= -1) then
			monkey.removeFromId(engine.config.msgid)
			engine.config.msgid = -1
		end
		--if (variables.callbackAfterPause ~= nil) then
	--		variables.callbackAfterPause()
	--	end
		parent:enableupdate(true)
		--ui:enableupdate(true)
		monkey.enablescriptengine(true) 
		engine.config.pause = false
	end

end

function waitForRestart()
	local b = monkey.getEntity("graham")
	local c = monkey.getEntity("ui")
	b:setactive(false)
	c:setactive(false)
	variables.callbackAfterPause = nil
end

function endSequence()
 	local s = script:new("_endseq")
	variables.callbackAfterPause = waitForRestart
	s.actions = {
		[1] = { type="delay", sec = 2},
		[2] = { type="callfunc", func = curry(displayBox, strings.global[1]), after={1} }
	}
	
	monkey.play(s)

end

function enterWater() 
	-- play enter water script
	if (variables.status == 0) then
	 	local s = script:new("_enterwater")
		-- disbale walking graham
		local a = monkey.getEntity("graham")
		a:changestate("drown")
		variables.status = 1
	    s.actions = {
			[1] = { type = "delay", sec = 2},
			[2] = {type="callfunc", func = function() print("Drown!") end, after={1} }
		}
		monkey.play(s)
	end
end

function enterWaterDie() 
	print ("IFFF")
	-- play enter water script
	if (variables.status == 0) then
		-- disbale walking graham
		local a = monkey.getEntity("graham")
		a:changestate("drown")
		variables.callbackAfterPause = endSequence
		displayBox(strings.room001[3])
		variables.status = 4
	end
end


function exitWater() 
	if (variables.status == 2) then
		-- disbale swimming graham
		local a = monkey.getEntity("swimming_graham")
		a:setactive(false)
		local b = monkey.getEntity("graham")
		b:setactive(true)
		b:setposition(a.x,a.y, a.z)
		variables.status = 0
	end

end

function startSwimming() 
	if (variables.status == 1) then
	print ("EIEIEIEIE")
		local s = script:new("_startswim")
	    s.actions = {
			[1] = { type = "killscript", script="_enterwater" }
		}
		monkey.play(s)
print ("DIFDDIDD")
		variables.drown = false
		local a = monkey.getEntity("drowning_graham")
		a:setactive(false)
		local b = monkey.getEntity("swimming_graham")
		b:setactive(true)
		b:setposition(a.x,a.y, a.z)
		variables.status = 2
	end
end

function processText(command) 
	words = {}
	for word in command:gmatch("%w+") do table.insert(words, word) end
	
	local t = actions
	for _,w in ipairs(words) do
		t = t[w]	
		if (t == nil) then
			print ("don't know " .. w)
			break
		else
			
		end
		
	end
	--print (type(t))
	if (type(t) == "function") then
		t()
	end

end

function enterPause() 
	print ("QUI")
	local main = monkey.getEntity("main")
	--local ui = monkey.getEntity("ui")
	print ("QUI2")
	main:enableupdate(false)
	engine.config.pause = true
--	ui:enableupdate(false)
	--variables.pause = true
	monkey.enablescriptengine(false)
end

function displayInventory ()
    local parent = monkey.getEntity("diag")
	local paddingOuter = {10, 6}
	local paddingInner = {6, 4}
	local width = 128
	local height = 80
	local mainItem = {
		pos={160 - width * 0.5 - paddingOuter[1], 100- height*0.5-paddingOuter[2], 1.5},
		components = {
			{ 
				type="gfx",
		 		shape = {
	 				type ="rect",
	 				width = width + 2*paddingOuter[1],
	 				height = height + 2*paddingOuter[2]
	 			},
	 			draw = "solid",
	 			color = {128,128,128,255}
	 		}
	 	},
	 	children = {}
	}


	count = 0
	for k, v in pairs(engine.state.scumm.inventory) do
		print ("CIAO " .. k)
		local p = engine.state.scumm.items[k]
		if (p == nil) then
			print ("Unknown item " .. k)
		else
			table.insert (mainItem.children, {
				pos = {paddingInner[1], height-7*count, 1},
				components = {
					{ type = "text", id=p.text, font="ui", align = "bottomleft", size=7, color ={0,0,0,255}},
					{ 
						type="hotspot", 
						priority = 2, 
						onenter = function() print ("ciao ello") end,
						onclick = function() 
							engine.config.verbs.item.code = p.code
							engine.config.verbs.item.anim = p.anim
							exitpause() 
						end

					}
				}
			})
		end
	end

	local msgid =monkey.addEntity (mainItem, parent)

	local m = monkey.getEntityFromId(msgid)
	monkey.addEntity ({
	 	pos={2,1,0.2},
	 	components = {
	 		{
	 			type = "gfx",
	 			shape = {
	 				type ="rect",
	 				width = width+2*paddingOuter[1]-4,
	 				height = height+2*paddingOuter[2]-2,
	 			},
	 			draw = "solid",
	 			color = {170,0,0,255}
		 	}
		 }
	}, m)	
	monkey.addEntity ({
	 	pos={4,2,0.3},
	 	components = {
	 		{
	 			type = "gfx",
	 			shape = {
	 				type ="rect",
	 				width = width+2*paddingOuter[1]-8,
	 				height = height+2*paddingOuter[2]-4,
	 			},
	 			draw = "solid",
	 			color = {128,128,128,255}
		 	}
		 }
	}, m)	

	engine.config.msgid = msgid
	enterPause()
end

function displayBox(msg)
    local parent = monkey.getEntity("main")
	print (msg)
    local msgid = monkey.addEntity ({
		--tag = "msg",
		children = {
			{
				tag ="msgtext",
				pos={158, 83, 2},
				components = {
					{ 
						type = "text", 
						id=msg,
						align = "center",
						font="ui",
						size=7,
						maxwidth = 160,
						color = {0,0,0,255}
					}
				}
			}
		}
	}, parent)
    engine.config.msgid = msgid
    print (msgid)
    local m = monkey.getEntityFromId(msgid)
	-- local m  = monkey.getEntity("msg")
	local mm  = monkey.getEntity("msgtext")
    local a = mm:gettextinfo()
	print ("width = " .. a.width)
	print ("height = " .. a.height)
	local paddingOuter = {10, 6}
	local paddingInner = {6, 4}
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingOuter[1], 83-a.height*0.5-paddingOuter[2], 1.5},
		components = {
			{ 
				type="gfx",
		 		shape = {
	 				type ="rect",
	 				width = a.width + 2*paddingOuter[1],
	 				height = a.height + 2*paddingOuter[2]
	 			},
	 			draw = "solid",
	 			color = {255,255,255,255}
	 		}
	 	}
	}, m)
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingInner[1], 83-a.height*0.5-paddingInner[2], 1.7},
		components = {
			{
				type ="gfx",
				shape = {
					type ="rect",
					width = a.width + 2*paddingInner[1],
					height = a.height + 2*paddingInner[2]
				},
				draw = "solid",
				color = {255,255,255,255}
			}
		}
	}, m)
	monkey.addEntity ({
	 	pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 1.6},
	 	components = {
	 		{
	 			type = "gfx",
	 			shape = {
	 				type ="rect",
	 				width = a.width + 2*paddingInner[1] + 4,
	 				height = a.height + 2*paddingInner[2]+2,
	 			},
	 			draw = "solid",
	 			color = {170,0,0,255}
		 	}
		 }
	}, m)
	-- -- monkey.addEntity ({
	-- -- 	pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 0.6},
	-- -- 	gfx = {
	-- -- 		shape = {
	-- -- 			type ="rect",
	-- -- 			width = a.width + 2*paddingInner[1]+4,
	-- -- 			height = a.height + 2*paddingInner[2]+2,
	-- -- 		},
	-- -- 		draw = "solid",
	-- -- 		color = {170,0,0,255}
	-- -- 	}
	-- -- }, m)
	enterPause()
end

function setGrahamState (s) 
end


function makeGraham(x, y, depth) 
	return
		{
			tag = "graham",
			switch = {
				states = { "walk", "drown", "swim" },
				initial = "walk"
			},
			children = {
				{
					-- walk
					gfx = { model="graham", anim="idle_right"},
					collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
					pos = {x,y,0},
					depth = depth,
					keyboardcontrollercollision = { 
						width = 1, 
		                height = 1, 
		                speed = 1, 
		                horizontal_rays = 2, 
		                vertical_rays = 2,
						anims = {
							{ id = "walk_right", anim = "walk_right" },
							{ id = "walk_front", anim = "walk_front" },
							{ id = "walk_back", anim = "walk_back" },
							{ id = "idle_right", anim = "idle_right" },
							{ id = "idle_front", anim = "idle_front"},
							{ id= "idle_back", anim = "idle_back"}
						} 
		            }

				},
				{
					-- drown
					gfx = { model="graham", anim="drown"},
					collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
					depth = depth,
			    }, 
				{
					-- swim
					gfx = { model="graham", anim="swim_right"},
					depth = depth,
					collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
					keyboardcontrollercollision = { 
						width = 1, 
		                height = 1, 
		                speed = 1, 
		                horizontal_rays = 2, 
		                vertical_rays = 2,
						anims = {
							{ id = "walk_right", anim = "swim_right" },
							{ id = "walk_front", anim = "swim_front" },
							{ id = "walk_back", anim = "swim_right" },
							{ id = "idle_right", anim = "swim_right" },
							{ id = "idle_front", anim = "swim_front"},
							{ id= "idle_back", anim = "swim_back"}
						} 

		            }
			    }
			}
	    }

 
end

function makeui()
	return {
		tag = "ui",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 24},
			bounds = {0, 0, 320, 24},
			viewport = {0, 0, 320, 24}
		},
		children = {
			{
				pos={0,16,0},
				text = {
					id="_",
					font="ui",
					size=8,
					align ="bottomleft"
				},
				keyinput = {
					maxlength = 10,
					func = processText
				}
				
			}
		}
	}
end
