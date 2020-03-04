engine.items["pieces_of_eight"] = {
	hotspot = {
		text = strings.objects.pieceofeight,
		text_plural = strings.objects.piecesofeight,
	},
	actions = {
		look = function() return { type = scumm.action.say, args = { tag = "player", lines = { strings.pieces_of_eight() } } } end
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
