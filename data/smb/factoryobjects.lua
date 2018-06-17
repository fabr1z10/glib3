function makeUI () 
	print ( "ollo = " .. config.ui_currentaction_color[2])
	return {
		makeButton(2, 40, variables._verbs.open),
		makeButton(2, 32, variables._verbs.close),
		makeButton(2, 24, variables._verbs.push),
		makeButton(2, 16, variables._verbs.pull),
		makeButton(48, 40, variables._verbs.walk),
		makeButton(48, 32, variables._verbs.pick),
		makeButton(48, 24, variables._verbs.talk),
		makeButton(48, 16, variables._verbs.give),
		makeButton(100, 40, variables._verbs.use),
		makeButton(100, 32, variables._verbs.look),
		makeButton(100, 24, variables._verbs.turnon),
		makeButton(100, 16, variables._verbs.turnoff),
		{
    		tag = "currentaction",
    		pos={160,48,0},
    		text = { id = "ddd", font="ui", align = "bottom", color = config.ui_currentaction_color},
    		layer=2
    	},
    	layer=2    
	}
end

function makeButton (x, y, verb)
    return {
        pos = { x, y, 0 },
        button = { id = verb.text, font="ui", align="bottomleft", group = 2, priority =1, layer=2, color = config.ui_unselected_color,
                   onenter = curry2(changecolor, config.ui_selected_color ),
                   onleave = curry2(changecolor, config.ui_unselected_color),
                   onclick = curry(setverb, verb ) },
        layer = 2
    }
end


function make_hotspot(input)
return {
    pos = {input.x, input.y, 0},
    gfx = input.gfx,
    hotspot = {
        group = 1,
        priority = input.priority, 
        shape = { type = "rect", width=input.width, height=input.height, offset= input.offset},
        onenter = curry(hoverOn, input.object),
        onleave = hoverOff,
        onclick = runAction
    },
    layer = 1,
	scaling = input.scaling,
    tag = input.object.tag
} 
end
