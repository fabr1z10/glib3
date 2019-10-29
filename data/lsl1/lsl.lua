action.lsl = {}
print ("SUPERCAZZIFFRAHGLI")

function makeItem (args)
	local r = 
	{
		tag = args.tag,
		pos=args.pos or {0,0,0},
		hotspot = {
			priority = args.prio or 1,
			shape = { type ="poly", outline=args.outline}
		},
		actions = {
			look = {
				{ type = action.lsl.showmessage, args = { msg = args.msg}}
			},
			use = args.use
		}
	}
	if (args.model ~= nil) then
		r.type="sprite"
		r.model = args.model
	end
	return r
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

function displayBox(msg)

	local xbox = 160
	local ybox = 100
	local text_color = {0, 0, 0, 255}
	local box_color = {235,235,134,255}
	local border_color = {0,0,0,255}
	local paddingOuter = {10, 6}
	local paddingInner = {6, 4}

    local parent = monkey.getEntity("main")
	print (msg)
    local msgid = monkey.addEntity ({
		--tag = "msg",
		children = {
			{
				tag ="msgtext",
				pos={xbox, ybox, 2},
				components = {
					{ 
						type = "text", 
						id=msg,
						align = "center",
						font="ui",
						size=8,
						maxwidth = 160,
						color = text_color
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

	monkey.addEntity ({
		pos={xbox - a.width * 0.5 - paddingOuter[1] + 1, ybox-a.height*0.5-paddingOuter[2]+1, 1.6},
		components = {
			{ 
				type="gfx",
		 		shape = {
	 				type ="rect",
	 				width = a.width + 2*paddingOuter[1] - 2,
	 				height = a.height + 2*paddingOuter[2] - 2,
	 			},
	 			draw = "solid",
	 			color = box_color
	 		}
	 	}
	}, m)
	monkey.addEntity ({
		pos={xbox - a.width * 0.5 - paddingOuter[1], ybox-a.height*0.5-paddingOuter[2], 1.5},
		components = {
			{ 
				type="gfx",
		 		shape = {
	 				type ="rect",
	 				width = a.width + 2*paddingOuter[1],
	 				height = a.height + 2*paddingOuter[2]
	 			},
	 			draw = "solid",
	 			color = border_color
	 		}
	 	}
	}, m)
	monkey.addEntity ({
		pos={xbox - a.width * 0.5 - paddingOuter[1] + 1, ybox-a.height*0.5-paddingOuter[2] -1 , 1.5},
		components = {
			{ 
				type="gfx",
		 		shape = {
	 				type ="rect",
	 				width = a.width + 2*paddingOuter[1],
	 				height = a.height + 2*paddingOuter[2]
	 			},
	 			draw = "solid",
	 			color = border_color
	 		}
	 	}
	}, m)

	-- monkey.addEntity ({
	-- 	pos={158 - a.width * 0.5 - paddingInner[1], 83-a.height*0.5-paddingInner[2], 1.7},
	-- 	components = {
	-- 		{
	-- 			type ="gfx",
	-- 			shape = {
	-- 				type ="rect",
	-- 				width = a.width + 2*paddingInner[1],
	-- 				height = a.height + 2*paddingInner[2]
	-- 			},
	-- 			draw = "solid",
	-- 			color = {255,255,255,255}
	-- 		}
	-- 	}
	-- }, m)
	-- monkey.addEntity ({
	--  	pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 1.6},
	--  	components = {
	--  		{
	--  			type = "gfx",
	--  			shape = {
	--  				type ="rect",
	--  				width = a.width + 2*paddingInner[1] + 4,
	--  				height = a.height + 2*paddingInner[2]+2,
	--  			},
	--  			draw = "solid",
	--  			color = {170,0,0,255}
	-- 	 	}
	-- 	 }
	-- }, m)
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

action.lsl.showmessage = function (args) 	
	glib.assert (args.msg, msg)
	return { type = "callfunc", func = function() displayBox(args.msg) end}
end