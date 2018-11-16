items.button = {}
items.verbbutton = {}
items.inventorybutton = {}

-- a button is simply some text with a hotspot
items.button.create = function(args)
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

    return {
        pos = { pos[1], pos[2], 0 },
		components = {
			{ type="text", id=text, font = font, size = size, color = color, align = align, maxwidth = maxwidth },
			{ type="hotspot", onenter = onenter, onleave = onleave, onclick = onclick, priority = priority }
		}
    }

end

items.inventorybutton.create = function (text, maxwidth) 
	return items.button.create {
		pos = {0,0},
		font="ui", 
        text= text,
		maxwidth = maxwidth,
        align="bottomleft", 
        color = config.ui_inv_unselected, 
        size = 8, 
        priority = 1,
		onenter = curry2(changecolor, config.ui_inv_selected), 
        onleave = curry2(changecolor, config.ui_inv_unselected),
		onclick = curry(setverb, verb)
	}

end

items.verbbutton.create = function(args) 
	local pos = args.pos
	local verb = args.verb
	return items.button.create {
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
