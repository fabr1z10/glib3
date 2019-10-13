-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
engine.items["guybrush"] = {
	tag = "player",
	model = "guybrush",
	character = {
		state = "idle",
		speed = 500
	},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 60},
	applydepth = true

}

engine.items["pieces_of_eight"] = {
	hotspot = {
		text = strings.objects.pieceofeight,
		text_plural = strings.objects.piecesofeight,
	},
	actions = {
		look = {
			{ type = scumm.action.say, args= { actor="guybrush", lines = {strings.pieces_of_eight}}}
		}

 -- function () 
	-- 		print ("123")		
	-- 		local s = script:new()
	-- 		s.actions = {
	-- 			action.say {id=1, actor="guybrush", lines = {strings.pieces_of_eight()}}
	-- 		}
	-- 		return s
	-- 	end

	}
}

engine.items["map"] = {
	hotspot = {
		text = strings.objects.map
	},
	actions = {
		look = function()
			local act = {
				{ type = action.animate, args = {tag="player", anim="open_map", sync=true}}
			}
			if (variables.map_looked == false) then 
				variables.map_looked = true
				table.insert (act, {type=action.delay, args = {sec=1}})
				table.insert (act, {
					type = scumm.action.say, args = {actor="guybrush", animstart="open_map_talk", animend="open_map_idle", lines = 
						{strings.village2[4], strings.village2[5], strings.village2[6], strings.village2[7]}}
				})
			else
				table.insert(act, {type=action.animate, args ={tag="player", anim="open_map_idle"}})
			end
				table.insert (act, {
					type = action.callfunc, args = { func = function() 
						local p = monkey.getEntity("main")
						local ui = monkey.getEntity("ui")
						local ot = monkey.getEntity("other")
						monkey.enablescriptengine(false)
   						p:setactive(false)
   						ui:setactive(false)
						local id = monkey.addEntity ({pos={0,0,0}, components = {
							{type="gfx", image="map.png"}
						}},ot)
						engine.state.scumm.lmboverride = function()
							ot:clear()
							p:setactive(true)
							ui:setactive(true)
							monkey.enablescriptengine(true) 
							local act2 = {
								{ type=action.animate, args = {tag="player", anim="open_map", sync=true, fwd=false}},
								{ type=action.animate, args = {tag="player", anim="idle_e"}}
							}
							local s = script.make(act2)
							engine.state.scumm.lmboverride=nil
							monkey.play(s)
						end
					end }
				})
			return act
		end
	}
}
