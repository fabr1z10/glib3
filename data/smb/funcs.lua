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
        variables._actionInfo.obj1 = nil
    end
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())
end

function runAction ()
    print ("here")
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
        print ("finding action " .. variables._actionInfo.verb.code .. " " .. variables._actionInfo.obj1)
        a = actions[variables._actionInfo.obj1][variables._actionInfo.verb.code]
        if (a == nil) then
            print ("no action found")
        else
            print (a)
        end
    end 
    
end

-- click on a verb
function setverb(verb)
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())
    print ("verb = " .. verb.code)
end

function changecolor (color, entity)
    entity:parent():setcolor(color[1], color[2], color[3], color[4])
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