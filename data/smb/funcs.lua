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



function hoverOn (msg)
    if (variables._actionInfo.obj1 == nil) then
        variables._actionInfo.obj1 = msg
    else
        if (variables._actionInfo.verb.objects > 1) then
            variables._actionInfo.obj2 = msg
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

-- the default behavior when you click on an object
function runAction ()
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
        print ("finding action " .. variables._actionInfo.verb.code .. " " .. variables._actionInfo.obj1)
        a = actions[variables._actionInfo.obj1][variables._actionInfo.verb.code]
        if (a == nil) then
            if (variables._actionInfo.verb.code == "give" or variables._actionInfo.verb.code == "use") then
                -- wait for second object
                variables._actionInfo.selectSecond = true
            else
               -- run default
               -- Here we generate a play script. The first action is always a walkto towards the provided
               -- object position. The following action depend on the default action, usually it just says something
               -- like "It doesn't seem to work" or the like.
               print ("Run default action for " .. variables._actionInfo.verb.code)
               variables._actionInfo:reset()
            end
        else
            -- run specific action
            print (a)
			a()
            variables._actionInfo:reset()
        end
    end
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
    entity:parent():setcolor(color[1], color[2], color[3], color[4])
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

function makeGuybrush()
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
        }
        }
    }    
end
