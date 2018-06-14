function curry(f, arg)
    return function()
       f(arg) 
    end 
end

function curry2(f, arg)
    return function(x)
       f(arg, x) 
    end 
end

function curry2_1(f, arg1, arg2)
    return function(x)
       f(arg1, arg2, x) 
    end 
end



function hoverOn (obj)
    print ("calling " .. obj.text)
    if (variables._actionInfo.obj1 == nil) then 
        variables._actionInfo.obj1 = obj
        print ("nil ok")
    else
        if (variables._actionInfo.verb.objects > 1 and variables._actionInfo.obj1 ~= obj) then
            variables._actionInfo.obj2 = obj
        end
    end
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())
end

function hoverOff ()
    if (variables._actionInfo.obj2 ~= nil) then
        variables._actionInfo.obj2 = nil
    else
        -- set obj1 to nil unless we are waiting for 2nd object
        if (variables._actionInfo.selectSecond == false) then
            variables._actionInfo.obj1 = nil
        end
    end
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())
end

function createWalkToAction (obj, script)
    table.insert (script.actions,
    {
        id = #script.actions,
		walkarea = "walkarea",
		actor = "player",
        type = "walkto",
		pos = obj.pos
	  })

    if (obj.dir ~= nil) then
        table.insert (script.actions,
        {
            id = #script.actions,
            actor = "player",
            type = "turn",
            face = obj.dir
        })
     end
end

function createWalkToPosition (position, script, f)
    table.insert (script.actions,
    {
        id = #script.actions,
		    walkarea = "walkarea",
		    actor = "player",
        type = "walkto",
		    pos = position
	  }

  )
end




function useActionHandler ()
    -- create an empty script
    script = {
        startid = 0,
        id = "_walk",
        actions = {}
    }
    
    -- do we have a function? use is symmetric so we can test both cases
    a = (variables._actionInfo.obj1["use"] and variables._actionInfo.obj1["use"][variables._actionInfo.obj2]) or 
        (variables._actionInfo.obj2["use"] and variables._actionInfo.obj2["use"][variables._actionInfo.obj1])
    if (a == nil) then
       -- not handled, so we can use default handler. This func populates the script with the actions
       -- related to the default use case (where no actions is )
       defaultActions["use"](script)
       return script
    end
    isObj1InInv = inventory[variables._actionInfo.obj1] ~= nil
    isObj2InInv = inventory[variables._actionInfo.obj2] ~= nil
    if (isObj1InInv and isObj2InInv) then
        -- the two objects are both in inventory, so I don't have to walk anywhere
        a(script)
        return script
    elseif (isObj1InInv and not(isObj2InInv)) then
        -- obj1 is in inventory, so I walkt o object 2
        createWalkToAction (variables._actionInfo.obj2, script)
        a(script)
    elseif (isObj1InInv and not(isObj2InInv)) then
        -- obj2 is in inventory, so I walkt o object 1
        createWalkToAction (variables._actionInfo.obj1, script)
        a(script)
    else
        -- both are outside of inventory
        pickupAction = variables._actionInfo.obj1["pickup"]
        if (pickupAction ~= nil) then
            createWalkToAction (variables._actionInfo.obj1, script)
            pickupAction (script)
            createWalkToAction (variables._actionInfo.obj2, script)
            a(script)
            
        else
            pickupAction = variables._actionInfo.obj1["pickup"]
            if (pickupAction ~= nil) then
                createWalkToAction (variables._actionInfo.obj2, script)
                pickupAction (script)
                createWalkToAction (variables._actionInfo.obj1, script)
                a(script)
            else
                -- no object is pickuppable, just call the script
                a(script)
            end
        end
                    
    end
    return script
    
end

-- the default behavior when you click on an object
function runAction ()
    script = { startid = 0, id = "_walk", actions = {}, edges = {} }
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
        print ("finding action " .. variables._actionInfo.verb.code .. " " .. variables._actionInfo.obj1.text)
        a = variables._actionInfo.obj1[variables._actionInfo.verb.code]
        if (a == nil) then
            
            if (variables._actionInfo.verb.code == "give" or variables._actionInfo.verb.code == "use") then
                -- wait for second object
                print ("POLLLL")
                variables._actionInfo.selectSecond = true
                a = monkey.getEntity("currentaction")
                a:settext(variables._actionInfo:toString())
                return
            else
               -- run default
               -- Here we generate a play script. The first action is always a walkto towards the provided
               -- object position. The following action depend on the default action, usually it just says something
               -- like "It doesn't seem to work" or the like.
               print ("run default")
               createWalkToAction (variables._actionInfo.obj1, script)
               defaultActions[variables._actionInfo.verb.code](script)
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
            
            createWalkToAction (variables._actionInfo.obj1, script)
            a(script)
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        a1 = variables._actionInfo.obj1[variables._actionInfo.verb.code]
        if (a1 == nil) then
            a1 = variables._actionInfo.obj2[variables._actionInfo.verb.code]
            if (a1 == nil) then
                defaultActions[variables._actionInfo.verb.code](script)
            else
                
            end
        end
            
        
        --script = twoObjectHandler[variables._actionInfo.verb.code]
    end
    for n = 1, #script.actions-1 do
        table.insert (script.edges, {script.actions[n].id, script.actions[n+1].id})
    end
        
    monkey.play(script)
    variables._actionInfo:reset()
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())    
end

-- click on a verb
function setverb(verb)
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    variables._actionInfo.selectSecond = false
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())
    print ("verb = " .. verb.code)
end

function changecolor (color, entity)
  print ("QUI")
    entity:parent():setcolor(color[1], color[2], color[3], color[4])
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
    layer = 1
} 
end

function makeUI () 
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
    text = {
        id = strings.ui.walkto, font="ui", align = "bottom", color = config.ui_currentaction_color
    },
    layer=2
    
}
--{
--    pos = {200, 40, 0},
--    outlinetext = {
--        id = "ciao", font="monkey", align="bottom", fontcolor={255,0,0,255}, outlinecolor = {255,255,255,255}, size = 8
--    },
--    layer = 2
--    
--}
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

function say (character, lines, script)
    table.insert (script.actions,
    {
        id = #script.actions,
        type = "say",
        actor = character.name,
        color = character.color,
        message = lines
    })
end

function makeGuybrush()
    local pane = {6,-34}
    local dt = 0.1
return {
        id="guybrush",
        sheet="gfx/sprite1.png",
		type="sprite",
        ppu=1,
        animations = {
	    {
	        name = "idle_front",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 24, y = 51, width = 22, height = 47, anchor = {12, 0}}
					}
		    	}
			}
	    },
        {
           name="idle_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 2, y = 51, width = 19, height = 47, anchor = {10, 0}}
					}
		       }
		   }				
        },
        {
           name="idle_back",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 49, y = 51, width = 20, height = 47, anchor = {12, 0}}
					}
		       }
		   }				
        },
	    {
	        name = "walk_front",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 207, y = 51, width = 22, height = 47, anchor = {11, 0}}
					}
		    	},
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 231, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		    	},	
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 3, y = 101, width = 20, height = 47, anchor = {10, 0}}
					}
		    	},
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 25, y = 101, width = 22, height = 47, anchor = {12, 0}}
					}
		    	},	
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 49, y = 101, width = 21, height = 47, anchor = {11, 0}}
					}
		    	},						
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 72, y = 101, width = 20, height = 47, anchor = {11, 0}}
					}
		    	}					
			}
	    },			
        {
           name="walk_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 4, y = 1, width = 32, height = 47, anchor = {16, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 40, y = 1, width = 16, height = 47, anchor = {11, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 60, y = 1, width = 19, height = 47, anchor = {11, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 83, y = 1, width = 31, height = 47, anchor = {15, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 117, y = 1, width = 18, height = 47, anchor = {11, 0}}
					}
		       },		
			   {
					duration = dt,
                    quads = {
			    		{ x = 141, y = 1, width = 19, height = 47, anchor = {11, 0}}
					}
		       }					
		   }				
        },		
        {
           name="walk_back",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 72, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 95, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 118, y = 51, width = 19, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 139, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 163, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 186, y = 51, width = 19, height = 47, anchor = {9, 0}}
					}
		       }
					
					
					
					
					
		   }				
        },
        {
           name="talk_front",

           frames={ 
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 129, width = 11, height = 13, anchor = pane }
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 129, width = 11, height = 13, anchor = pane }
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 205, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 143, width = 11, height = 13, anchor =  pane}
                    }
               },               
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane }
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 143, width = 11, height = 13, anchor = pane}
                    }
               },  
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 205, y = 143, width = 11, height = 13, anchor = pane }
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 143, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },      
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 205, y = 143, width = 11, height = 13, anchor =  pane}
                    }
               }
           }

        },
        {
           name = "talk_right",
           frames = { 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },               
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               },    
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },   
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               }               
           }                
        },
        {
            name = "talk_back",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 220, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 233, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 220, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 233, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },                    
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 220, y = 115, width = 11, height = 12, anchor = {12, 0}}
                    }
               }                       
                    
                    
                    
           }
        }
        }
    }    
end

