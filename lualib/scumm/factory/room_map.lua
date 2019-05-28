-- Basic room 
function scumm.factory.map_room (args) 
	-- validation phase
	glib.assert(args.width, "width")
	glib.assert(args.height, "width")
	--glib.assert(args.font_size, "font_size")

	local room_width = args.width
	local room_height = args.height
	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2]

	-- start y
	--local font_size = args.font_size

	local startPos = nil
	if (args.startTable ~= nil) then
		startPos = args.startTable[engine.state.previousRoom]
		if (startPos == nil) then
			startPos = args.startTable[args.defaultroom]
		end	
	end
	local enableScroll = args.enableScroll
	if (enableScroll == nil) then enableScroll = true end
	

	local p =  {
		afterstartup = function()
			for k, v in ipairs(room.initstuff) do
				v()
			end
			--if (variables.troll_fed==false) then troll() end
		end,
		items = {},
		dialogues = {},
		scripts = {},
		startPos = startPos,
		initstuff = {
			[1] = function() 
				--engine.state.scumm.actionInfo.verb = engine.config.default_verb
				--scumm.ui.updateVerb() 
				--scumm.ui.refresh_inventory()
			end
		},
		engines = {
			{ 
                type = "hotspotmanager", 
			    keys = {
				    { key = 299, func = function() monkey.endroom() end }
			    },
				lmbclick = function(x, y)
				    print (tostring(x) .. "," .. tostring(y))

					if (engine.state.scumm.actionInfo.verb == "walk") then
						local actions = scumm.ui.walk { pos = {x,y} }
						local s = script.make(actions)
						s.name="_walk"
						monkey.play(s)
					end
				end,	 
			},
			{ type = "scheduler" }
		},
		-- assets = {
		-- 	"arrow_up",
		-- 	"arrow_down",
		-- 	"guybrush", -- set this as input param
		-- },
		scene = {
			{
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {camWidth, camHeight},
					bounds = {0, 0, room_width, room_height},
					viewport = {0, 0, camWidth, camHeight}
				},
				children = {}
			},
			{
					tag = "diag",
					camera = {
						tag = "maincam",
						type="ortho",
						size = {320, 200},
						bounds = {0, 0, 320, 200},
						viewport = {0, 0, 320, 200}
					},
					children = {
						-- {
						--     pos = {0, 0, 0},
						--     hotspot = {
						--         priority = 1,
						--         shape = { type = "rect", width=320, height=200 },
						--         onmove = function(x,y) print(x .. " " .. y) end
						--     }
						-- },
						{ 
					    	tag = "cursor",
					    	pos={0,0,0},
							components = {
					    		{ type="text", id = "prova", font="monkey", align = "bottom", color = engine.config.ui_currentaction_color},
								{ type="cursor"}
							}
						}
					}
			}

		}
	}

	if (args.collide == true) then
		table.insert (p.engines, 
			{ 
				type = "collision", 
				size = {128, 128}, 
				response = {
					{ tag = {1, 2}, onenter=function(e,f) 

							local info = f:getinfo()
							if (info.onenter ~= nil) then
								info.onenter()
							end
					 end}
				}
			}
		)
	end

	-- get the inventory
	--table.insert(p.initstuff, function()
		--setverb (config.verbs.walk)
		--refresh_inventory()
		-- c:addtext ( { text="ciao" })
		-- c:addtext ( { text="come" })
		-- c:addtext( { text ="stai" })
		-- c:addtext({ text="alleelelel"})
		-- c:addtext({ text="stronzo" })
		-- c:addtext( { text="duro"})
		-- c:addtext( {text="anvedi"})
	--end)
	local refs = {
		main = p.scene[1].children,
		--ui = p.scene[2].children[1].children[1].children
	}



	-- add the walkarea(s)
	if (args.walkareas) then
		for _, wa in ipairs(args.walkareas) do
			local tmp = scumm.factory.object { id = wa }
			table.insert (refs.main, tmp)
			refs[wa] =  tmp.children
		end

		-- adding player
		print("ciao = "..tostring(startPos.pos[1]))
		print("ciao = "..tostring(startPos.pos[2]))
		local w1 = refs[startPos.walkarea]
		table.insert(w1,  
			scumm.factory.object { 
				id="guybrush",
				pos={startPos.pos[1], startPos.pos[2], 0}, 
				tag="player", 
				dir = startPos.dir,
				follow = (room_width > 320 and enableScroll),
				collide = args.collide
			}
		)

			--scumm.factory.object { 
		-- 	id="guybrush",
		-- 	
		-- 	tag="player", 
		-- 	dir = startPos.dir,
		-- 	--collide = args.collide


		-- } })

	end

	--table.insert (refs.ui,scumm.factory.verbbutton {pos={2, 40}, verb = "open"} )

	if (p.startPos.func ~= nil) then

	 	table.insert(p.initstuff, p.startPos.func)
	end
	

	function p:add(to, items) 
		for k,v in ipairs(items) do
			print ("ciaociao")
			print (refs[to].tag)
			table.insert(refs[to], v)
		end
	end

	engine.state.scumm.actionInfo.verb = engine.config.default_verb
	p.depth = args.depth
	p.scale = args.scale
	return p
end
