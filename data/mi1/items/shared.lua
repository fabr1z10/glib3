-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
engine.items["guybrush"] = {
	tag = "player",
	model = "guybrush",
	character = {
		state = "idle",
		speed = 50
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