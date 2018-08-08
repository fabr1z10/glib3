defaultActions = {
   walk = empty,
   look = curryg (say, {character="guybrush", lines = {strings.defaultactions[4]} }),
   open = curryg (say, {character="guybrush", lines = {strings.defaultactions[1]} }),
   close = curryg (say, {character="guybrush", lines = {strings.defaultactions[2]} }),
   push = curryg (say, {character="guybrush", lines = {strings.defaultactions[3]} }),
   pull = curryg (say, {character="guybrush", lines = {strings.defaultactions[3]} }),
   pick = curryg (say, {character="guybrush", lines = {strings.defaultactions[5]} }),
   use = curryg (say, {character="guybrush", lines = {strings.defaultactions[2]} }),
   talk = curryg (say, {character="guybrush", lines = {strings.defaultactions[2]} }),
   turnon = curryg (say, {character="guybrush", lines = {strings.defaultactions[2]} }),
   turnoff = curryg (say, {character="guybrush", lines = {strings.defaultactions[2]} })
   
}

function changecolor (color, entity)
    entity:setcolor(color[1], color[2], color[3], color[4])
end

function updateVerb() 
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())    
end

-- click on a verb
function setverb(verb)
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    variables._actionInfo.selectSecond = false
    updateVerb()
end

function hoverOn (obj)
	print (obj)
    if (variables._actionInfo.obj1 == nil) then 
        variables._actionInfo.obj1 = obj
    else
        if (variables._actionInfo.verb.objects > 1 and variables._actionInfo.obj1 ~= obj) then
            variables._actionInfo.obj2 = obj
        end
    end
    updateVerb()
end

function hoverOnInventory (args, entity)
	changecolor (args.color, entity) 
	hoverOn(args.obj)
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

function hoverOffInventory(args, entity) 
	changecolor(args.color, entity)
	hoverOff()
end

-- function that handle use on two objects
function useActionHandler ()
	
    -- create an empty script
    local s = Script.create("_walk")
	print ("Using " .. variables._actionInfo.obj1 .. " with " .. variables._actionInfo.obj2)
	local obj1 = objects[variables._actionInfo.obj1]
	local obj2 = objects[variables._actionInfo.obj2]
	local a = nil	

	if (obj1["use"] ~= nil) then
		a = obj1["use"][variables._actionInfo.obj2]
	else 
		if (obj2["use"] ~= nil) then
			a = obj2["use"][variables._actionInfo.obj1]
		end 
	end
	-- do we have a function? use is symmetric so we can test both cases
    if (a == nil) then
		print ("custom use not found")
       -- not handled, so we can use default handler. This func populates the script with the actions
       -- related to the default use case (where no actions is )
       s:add(defaultActions["use"]())
       return s
    end
    isObj1InInv = inventory[variables._actionInfo.obj1] ~= nil
    isObj2InInv = inventory[variables._actionInfo.obj2] ~= nil
    if (isObj1InInv and isObj2InInv) then
        -- the two objects are both in inventory, so I don't have to walk anywhere
        s:add(a())
        return s
    elseif (isObj1InInv and not(isObj2InInv)) then
        -- obj1 is in inventory, so I walkt o object 2
		s:add(createWalkToAction(variables._actionInfo.obj2))
        s:add(a())
		return s
    elseif (isObj1InInv and not(isObj2InInv)) then
        -- obj2 is in inventory, so I walkt o object 1
		s:add(createWalkToAction(variables._actionInfo.obj1))
        s:add(a())
		return s
    else
        -- both are outside of inventory
        pickupAction = obj1["pick"]
        if (pickupAction ~= nil) then
            s:add(createWalkToAction(variables._actionInfo.obj1))
            s:add(pickupAction())
            s:add(createWalkToAction(variables._actionInfo.obj2))
	        s:add(a())
            return s
        else
            pickupAction = obj2["pick"]
            if (pickupAction ~= nil) then
	            s:add(createWalkToAction(variables._actionInfo.obj2))
    	        s:add(pickupAction())
        	    s:add(createWalkToAction(variables._actionInfo.obj1))
	        	s:add(a())
            	return s
            else
                -- no object is pickuppable, just call the script
				s:add(a())
                return s
            end
        end
                    
    end
    
    
end


-- the default behavior when you click on an object
function runAction ()
    -- mm, no target object here, just ignore the click
    if (variables._actionInfo.obj1 == nil) then
        return nil
    end
    print ("Current verb " .. variables._actionInfo.verb.code)
	-- create a brand new script
    local s = Script:new()
	print("NOW IS")
	s:dump()
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
        print ("finding action " .. variables._actionInfo.verb.code .. " " .. variables._actionInfo.obj1)
		local obj = objects[variables._actionInfo.obj1]
        a = obj[variables._actionInfo.verb.code]
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
				s:push { actions = createWalkToAction {objectId = variables._actionInfo.obj1}, name ="walk" }
				--s:push { actions = defaultActions[variables._actionInfo.verb.code] ("action"), after = "walk" }
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
	s:dump()
    monkey.play(s)
    variables._actionInfo:reset()
    updateVerb()
end