


scumm.factory.button = function(args)
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
		--{ type="text", id=text, font = font, size = size, color = color, align = align, maxwidth = maxwidth },
		{ type="hotspot", onenter = onenter, onleave = onleave, onclick = onclick, priority = priority }
	}
	if (args.info ~= nil) then
		table.insert(components, { type="info", data = args.info})
	end

    return {
    	type = "text",
    	text = text, 
    	font = font, 
    	size = size,
    	color = color,
    	align = align,
    	maxwidth = maxwidth,
        pos = { pos[1], pos[2], 0 },
		components = components
    }

end

scumm.factory.inventorybutton = function (args) 
	return scumm.factory.button {
		pos = {0,0},
		font = engine.config.ui.font,
        text= args.text,
		maxwidth = args.maxwidth,
        align="bottomleft", 
        color = engine.config.ui.inv_unselected,
        size = 8, 
        priority = 1,
		info = { obj = args.obj},
		onenter = scumm.ui.hover_on_inv_button, --scurry2(changecolor, config.ui_inv_selected), 
        onleave = scumm.ui.hover_off_inv_button, --(changecolor, config.ui_inv_unselected),
		onclick = scumm.ui.runAction
	}

end

scumm.factory.inventorybutton_sci = function (args)
	return scumm.factory.button {
		pos = {0,0},
		font = "ui",
        text= args.text,
		maxwidth = args.maxwidth,
        align="bottomleft",
        color = {255,0,0,255},
        size = 8,
        priority = 1,
		--info = { obj = args.obj},
		--onenter = scumm.ui.hover_on_inv_button, --scurry2(changecolor, config.ui_inv_selected),
        --onleave = scumm.ui.hover_off_inv_button, --(changecolor, config.ui_inv_unselected),
		--onclick = scumm.ui.runAction
	}

end

scumm.factory.dialoguebutton = function (args) 
	return scumm.factory.button {
		pos = {0,0},
		font = engine.config.ui.font,
        text= args.text,
		maxwidth = args.maxwidth,
        align="bottomleft", 
        color = engine.config.ui.verb_unselected_color,
        size = 8, 
        priority = 1,
		info = { node = args.dialogue_node, dialogue = args.dialogue }, 
		onenter = glib.curry2(scumm.ui.changecolor, engine.config.ui.verb_selected_color),
        onleave = glib.curry2(scumm.ui.changecolor, engine.config.ui.verb_unselected_color),
		onclick = scumm.ui.handleDialogueButton
	}

end


scumm.factory.verbbutton = function(args) 
	local pos = args.pos
	local verb = engine.config.verbs[args.verb]
	return scumm.factory.button {
		pos = pos,
		font = engine.config.ui.font,
        text= verb.text,
        align="bottomleft", 
        color = engine.config.ui.verb_unselected_color, 
		maxwidth = 170,
        size = 8, 
        priority = 1,
		onenter = glib.curry2(scumm.ui.changecolor, engine.config.ui.verb_selected_color), 
        onleave = glib.curry2(scumm.ui.changecolor, engine.config.ui.verb_unselected_color),
		onclick = glib.curry(scumm.ui.setverb, args.verb)
	}
end