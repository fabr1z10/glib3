
print ("polne")
print(characters.guybrush.name)

defaultActions = {
   walk = empty,
   look = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[4]} }),
   open = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[1]} }),
   close = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[2]} }),
   push = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[3]} }),
   pull = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[3]} }),
   pick = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[5]} }),
   use = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[2]} }),
   talk = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[2]} }),
   turnon = curry (say, {character=characters.guybrush, lines = {strings.defaultactions[2]} }),
   turnoff = curry (say, {character= characters.guybrush, lines = {strings.defaultactions[2]} })
   
}

function changecolor (color, entity)
    entity:parent():setcolor(color[1], color[2], color[3], color[4])
end

function updateVerb() 
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())    
end

-- click on a verb
function setverb(verb)
    print ("CALLLL")
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    variables._actionInfo.selectSecond = false
    updateVerb()
    print ("verb = " .. verb.code)
end

function hoverOn (obj)
    print ("PIPPO")
    print ("calling " .. obj.text)
    if (variables._actionInfo.obj1 == nil) then 
        variables._actionInfo.obj1 = obj
        print ("nil ok")
    else
        if (variables._actionInfo.verb.objects > 1 and variables._actionInfo.obj1 ~= obj) then
            variables._actionInfo.obj2 = obj
        end
    end
    updateVerb()
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
    updateVerb()
end


-- function that handle use on two objects
function useActionHandler ()
    -- create an empty script
    s = Script:create("_walk")

    -- do we have a function? use is symmetric so we can test both cases
    a = (variables._actionInfo.obj1["use"] and variables._actionInfo.obj1["use"][variables._actionInfo.obj2]) or 
        (variables._actionInfo.obj2["use"] and variables._actionInfo.obj2["use"][variables._actionInfo.obj1])
    if (a == nil) then
       -- not handled, so we can use default handler. This func populates the script with the actions
       -- related to the default use case (where no actions is )
       s:add(defaultActions["use"])
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
    -- mm, no target object here, just ignore the click
    if (variables._actionInfo.obj1 == nil) then
        return
    end
    print ("Current verb " .. variables._actionInfo.verb.code)
    local s = Script.create("_walk")
    print("Number of actions = " .. #s.actions)
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
        print ("finding action " .. variables._actionInfo.verb.code .. " " .. variables._actionInfo.obj1.text)
        a = variables._actionInfo.obj1[variables._actionInfo.verb.code]
        if (a == nil) then
            if (variables._actionInfo.verb.code == "give" or variables._actionInfo.verb.code == "use") then
                variables._actionInfo.selectSecond = true
                updateVerb()
                return
            else
               -- run default
               -- Here we generate a play script. The first action is always a walkto towards the provided
               -- object position. The following action depend on the default action, usually it just says something
               -- like "It doesn't seem to work" or the like.
               print ("Run default")
               s:add (createWalkToAction(variables._actionInfo.obj1))
               s:add (defaultActions[variables._actionInfo.verb.code]())
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
            print ("found custom")
            s:add (createWalkToAction(variables._actionInfo.obj1))
            s:add (a())
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        if (variables._actionInfo.verb.code == "use") then
            s = useActionHandler()
        end
        -- a1 = variables._actionInfo.obj1[variables._actionInfo.verb.code]
        -- if (a1 == nil) then
        --     a1 = variables._actionInfo.obj2[variables._actionInfo.verb.code]
        --     if (a1 == nil) then
        --         defaultActions[variables._actionInfo.verb.code](script)
        --     else
                
        --     end
        -- end
            
        
        --script = twoObjectHandler[variables._actionInfo.verb.code]
    end
    s:setsequence()
    print("Number of actions = " .. #s.actions)
    monkey.play(s)
    variables._actionInfo:reset()
    updateVerb()
end