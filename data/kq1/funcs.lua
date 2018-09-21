function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function changeRoom(o1, o2)
	local a = o2:getinfo()
	print (a.roomto)

end

function exitpause() 
	if (variables.pause == true) then
		print ("Exit pause mode")
	    local parent = monkey.getEntity("main")
		local ui = monkey.getEntity("ui")
		monkey.removeEntity("msg")
		if (variables.callbackAfterPause ~= nil) then
			variables.callbackAfterPause()
		end
		parent:enableupdate(true)
		ui:enableupdate(true)
		monkey.enablescriptengine(true) 
		variables.pause = false
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
	local main = monkey.getEntity("main")
	local ui = monkey.getEntity("ui")
	main:enableupdate(false)
	ui:enableupdate(false)
	variables.pause = true
	monkey.enablescriptengine(false)
end


function displayBox(msg)
    local parent = monkey.getEntity("main")
	print (msg)
    monkey.addEntity ({
		tag = "msg",
		children = {
			{
				tag ="msgtext",
				pos={158, 83, 1},
				text = {
					id=msg,
					align = "center",
					font="ui",
					size=7,
					maxwidth = 160,
					color = {0,0,0,255}
				}
			}
		}
	}, parent)
	local m  = monkey.getEntity("msg")
	local mm  = monkey.getEntity("msgtext")
    local a = mm:gettextinfo()
	print ("width = " .. a.width)
	print ("height = " .. a.height)
	local paddingOuter = {10, 6}
	local paddingInner = {6, 4}
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingOuter[1], 83-a.height*0.5-paddingOuter[2], 0.5},
		gfx = {
			shape = {
				type ="rect",
				width = a.width + 2*paddingOuter[1],
				height = a.height + 2*paddingOuter[2]
			},
			draw = "solid",
			color = {255,255,255,255}
		}
	}, m)
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingInner[1], 83-a.height*0.5-paddingInner[2], 0.7},
		gfx = {
			shape = {
				type ="rect",
				width = a.width + 2*paddingInner[1],
				height = a.height + 2*paddingInner[2]
			},
			draw = "solid",
			color = {255,255,255,255}
		}
	}, m)
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 0.7},
		gfx = {
			shape = {
				type ="rect",
				width = a.width + 2*paddingInner[1] + 4,
				height = a.height + 2*paddingInner[2]+2,
			},
			draw = "solid",
			color = {170,0,0,255}
		}
	}, m)
	-- monkey.addEntity ({
	-- 	pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 0.6},
	-- 	gfx = {
	-- 		shape = {
	-- 			type ="rect",
	-- 			width = a.width + 2*paddingInner[1]+4,
	-- 			height = a.height + 2*paddingInner[2]+2,
	-- 		},
	-- 		draw = "solid",
	-- 		color = {170,0,0,255}
	-- 	}
	-- }, m)
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