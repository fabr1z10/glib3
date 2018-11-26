factory.button = {}
factory.verbbutton = {}
factory.inventorybutton = {}
factory.dialoguebutton = {}

-- a button is simply some text with a hotspot
factory.button.create = function(args)
	local pos = args.pos
	local font = args.font 
	local size = args.size or 8
	local align = args.align or "topleft"
	local onenter = args.onenter
	local onleave = args.onleave
	local onclick = args.onclick	
	local priority = args.priority
	local text = args.text
	local color = args.color or {255,255,255,255}
	local maxwidth = args.maxwidth
	local components = {
		{ type="text", id=text, font = font, size = size, color = color, align = align, maxwidth = maxwidth },
		{ type="hotspot", onenter = onenter, onleave = onleave, onclick = onclick, priority = priority }
	}
	if (args.info ~= nil) then
		table.insert(components, { type="info", data = args.info})
	end

    return {
        pos = { pos[1], pos[2], 0 },
		components = components
    }

end

factory.inventorybutton.create = function (args) 
	
	return factory.button.create {
		pos = {0,0},
		font="ui", 
        text= args.text,
		maxwidth = args.maxwidth,
        align="bottomleft", 
        color = config.ui_inv_unselected, 
        size = 8, 
        priority = 1,
		onenter = curry2(changecolor, config.ui_inv_selected), 
        onleave = curry2(changecolor, config.ui_inv_unselected),
		onclick = curry(setverb, verb)
	}

end

factory.dialoguebutton.create = function (args) 
	return factory.button.create {
		pos = {0,0},
		font="ui", 
        text= args.text,
		maxwidth = args.maxwidth,
        align="bottomleft", 
        color = config.ui_unselected_color, 
        size = 8, 
        priority = 1,
		info = { node = args.dialogue_node, dialogue = args.dialogue }, 
		onenter = curry2(changecolor, config.ui_selected_color), 
        onleave = curry2(changecolor, config.ui_unselected_color),
		onclick = handleDialogueButton
	}

end


factory.verbbutton.create = function(args) 
	local pos = args.pos
	local verb = args.verb
	return factory.button.create {
		pos = pos,
		font="ui", 
        text= verb.text,
        align="bottomleft", 
        color = config.ui_unselected_color, 
		maxwidth = 170,
        size = 8, 
        priority = 1,
		onenter = curry2(changecolor, config.ui_selected_color), 
        onleave = curry2(changecolor, config.ui_unselected_color),
		onclick = curry(setverb, verb)
	}
end
