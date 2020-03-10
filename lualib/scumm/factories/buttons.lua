scumm.factory.button = function(args)
	glib.assert(args.pos, "pos")
	glib.assert(args.font, "font")
	glib.assert(args.text, "text")
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
	glib.assert(args.id, "id")
	local qty = args.qty or 1

	local item = engine.items[args.id]
	-- create label
	local label =''
	if not args.qty or args.qty == 1 then
		label = item.hotspot.text
	else
	    print ("ciao " .. tostring(args.qty) .. " " .. args.id)
		label = tostring(args.qty) .. ' ' .. item.hotspot.text_plural
	end

    if not item then error("Hey, I don't know item: " .. args.id,1) end
	local button = scumm.factory.button {
		pos = {0,0},
		font = engine.config.ui.font,
        text = label,
        align="bottomleft", 
        color = engine.config.ui.inv_unselected, 
		maxwidth = 170,
        size = 8, 
        priority = 1,
		onenter = scumm.func.hover_on_inv_button,
        onleave = scumm.func.hover_off_inv_button,
		onclick = scumm.func.run_action 
	}
	table.insert (button.components, { type='info', info = { obj = args.id }})
	return button
end

scumm.factory.dialoguebutton = function (args) 
	local button = scumm.factory.button {
		pos = {0,0},
		font = engine.config.ui.font,
        text = args.text,
		maxwidth = args.maxwidth,
        align = "bottomleft", 
        color = engine.config.ui.verb_unselected_color,
        size = 8, 
        priority = 1,
		--info = { node = args.dialogue_node, dialogue = args.dialogue }, 
		onenter = glib.curry2(scumm.func.changecolor, engine.config.ui.verb_selected_color),
        onleave = glib.curry2(scumm.func.changecolor, engine.config.ui.verb_unselected_color),
		onclick = scumm.func.handleDialogueButton	
	}
	table.insert (button.components, { type='info', info = { node = args.dialogue_node, dialogue = args.dialogue }})
	return button

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
		onenter = glib.curry2(scumm.func.changecolor, engine.config.ui.verb_selected_color), 
        onleave = glib.curry2(scumm.func.changecolor, engine.config.ui.verb_unselected_color),
		onclick = glib.curry(scumm.func.set_verb, args.verb)
	}
end