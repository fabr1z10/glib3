function makeUI () 
	print ( "ollo = " .. config.ui_currentaction_color[2])

	return {
    {
        tag = "ui",
        children = {
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
            }
    	},
    	layer=2    
    }
	}
end

function refreshInventory()
	inv = monkey.getEntity("inventory")
	inv:cleartext()
	for k, v in pairs(inventory) do
		inv:addbutton({ text = objects[k].text, priority = 1, onenter = curry2(hoverOnInventory, {obj = k, color = config.ui_inv_selected}),
        onleave = curry2(hoverOffInventory, {color = config.ui_inv_unselected}),
        onclick = runAction })
	end
end

function makescummui1() 
	return 
	{
		tag="ui",
	 	camera = {
			type="ortho",
	 		size = {320, 56},
	 		bounds = {0, 0, 320, 56},
	 		viewport = {0, 0, 320, 56}
	 	},	
		children = {
			{
				tag = "uiplay",
				children = {
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
					{
						tag="inventory",
						textview = {
							width = 170.0,
							height = 48.0,
		                    viewport = {150, 0, 170, 48},
							color = config.ui_inv_unselected,
		                    font = "ui",
		                    size = 8,
							deltax = 26,
							arrowup = "arrowup",
		                    arrowdown = "arrowdown"
						}
					}
				}
			},
			{
				tag="dialogue",
				textview = {
					width = 320.0,
					height = 56.0,
                    viewport = {0, 0, 320, 56},
					color = config.ui_unselected_color,
                    font = "ui",
                    size = 8,
					deltax = 0,
					arrowup = "arrowup",
                    arrowdown = "arrowdown"
				}			
			}
		}
	}
	-- add all inventory items
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

function makeDialogueButton (x, y, button) 
    return {
        pos = {x, y, 0},
        button = { id = button.text, font="ui", align="bottomleft", group = 2, priority = 1, layer = 2, maxwidth = 320, color = config.ui_unselected_color,
            onenter = curry2(changecolor, config.ui_selected_color),
            onleave = curry2(changecolor, config.ui_unselected_color),
            onclick = curry(pippo, button)
        },
        layer = 2
    }   
end


function make_hotspot(input)
if (inventory[input.object]~=nil) then
	return nil
end
obj = objects[input.object]
local z = input.z
if (z == nil) then
	z = 0
end
return {
    pos = {input.x, input.y, z},
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
    tag = obj.tag
} 
end
