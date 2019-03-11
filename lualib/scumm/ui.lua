scumm.ui = {}

function variables._actionInfo:toString ()
    local t = { self.verb.text }

    if (self.obj1 ~= nil) then
        --o1 = objects[self.obj1]
        t[2] = items2[self.obj1].hotspot.text
        if (self.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = items2[self.obj2].hotspot.text
        else
            if (self.selectSecond == true) then
               t[3] = self.verb.prep 
            end
        end 
    end
    return table.concat(t, " ")
end

function scumm.ui.updateVerb() 
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())    
end

function scumm.ui.setverb(verb)
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    variables._actionInfo.selectSecond = false
    scumm.ui.updateVerb()
end

function scumm.ui.changecolor (color, entity)
    entity:setcolor(color[1], color[2], color[3], color[4])
end

function scumm.ui.hoverOn (obj)
    if (variables._actionInfo.obj1 == nil) then 
		print ("Set")
        variables._actionInfo.obj1 = obj
    else
        if (variables._actionInfo.verb.objects > 1 and variables._actionInfo.obj1 ~= obj) then
            variables._actionInfo.obj2 = obj
        end
    end
    scumm.ui.updateVerb()
end

function scumm.ui.hoverOff ()
    if (variables._actionInfo.obj2 ~= nil) then
        variables._actionInfo.obj2 = nil
    else
        -- set obj1 to nil unless we are waiting for 2nd object
        if (variables._actionInfo.selectSecond == false) then
            variables._actionInfo.obj1 = nil
        end
    end
    scumm.ui.updateVerb()
end

-- the default behavior when you click on an object
function scumm.ui.runAction ()
    -- mm, no target object here, just ignore the click
    if (variables._actionInfo.obj1 == nil) then
        return nil
    end
	-- create a brand new script
    --local s = script:new("_walk")
	--s.name="_walk"
	local obj = items2[variables._actionInfo.obj1]
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
		if (variables._actionInfo.verb.code == "give") then
        	variables._actionInfo.selectSecond = true
            scumm.ui.updateVerb()
            return		
		end
        a = obj.actions[variables._actionInfo.verb.code]
        if (a == nil) then
            if (variables._actionInfo.verb.code == "use") then
                variables._actionInfo.selectSecond = true
                scumm.ui.updateVerb()
                return
            else
                -- run default
                -- Here we generate a play script. The first action is always a walkto towards the provided
                -- object position. The following action depend on the default action, usually it just says something
                -- like "It doesn't seem to work" or the like.
				print ("Running default script (" .. variables._actionInfo.verb.text .. ", " .. variables._actionInfo.obj1 .. ") ...")
				local actions = {}
				if (variables.inventory[variables._actionInfo.obj1] == nil) then		
					actions = {
						{ type = action.walkto, args = { actor="guybrush", obj = variables._actionInfo.obj1 }},
						{ type = action.turn, args = { actor="guybrush", dir = obj.hotspot.dir }}
					}			
				end
				local b = script.defaultactions[variables._actionInfo.verb.code]
				if (b ~= nil) then		
					table.insert (actions, b)
				end
				s = ms2 (actions)
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
			print ("Running script (" .. variables._actionInfo.verb.text .. ", " .. variables._actionInfo.obj1 .. ") ...")
			local actions = {}
			if (variables.inventory[variables._actionInfo.obj1] == nil) then		
				actions = {
					{ type = action.walkto, args = { id=1, actor="guybrush", obj = variables._actionInfo.obj1 }},
					{ type = action.turn, args = { id=2, actor="guybrush", dir = obj.hotspot.dir }}
				}		
			end
			table.insert (actions, get(a))
			s = ms2 (actions)
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        if (variables._actionInfo.verb.code == "use") then
			local obj2 = items2[variables._actionInfo.obj2]
			-- walk action
			-- 1. If both obejcts are in inventory, stay where you are
			-- 2. If one object is in inventory, walk to the other object
			-- 3. If both objects are not in inventory, then
			-- a. If obj1 has a pickup action, pick it up and go to obj2
			-- b. If obj2 has a pickup action, pick it up and go to obj1
			-- c. If no pickup action is there, walk to obj2
			local actions = {}
			local IhaveObj1 = variables.inventory[variables._actionInfo.obj1] ~= nil
			local IhaveObj2 = variables.inventory[variables._actionInfo.obj2] ~= nil
			if (IhaveObj1 and (not IhaveObj2)) then
				table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj2))
			elseif (IhaveObj2 and (not IhaveObj1)) then
				table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj1))
			elseif ((not IhaveObj1) and (not IhaveObj2)) then
				local pu1 = obj.actions["pickup"]
				local pu2 = obj2.actions["pickup"]
				if (pu1 ~= nil) then
					-- go pick-up 1st object, walk to 2nd
					table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj1))
					table.insert (actions, get(pu1))
					table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj2))
				elseif (pu2 ~= nil) then
					-- go pick-up 2nd object, walk to 2nd
					table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj2))
					table.insert (actions, get(pu2))
					table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj1))
				else 
					table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj2))
				end
			end
			-- now, slap the actual use action
			local u1 = obj.actions["use"] and obj.actions["use"][variables._actionInfo.obj2]
			local u2 = obj2.actions["use"] and obj2.actions["use"][variables._actionInfo.obj1]
			if (u1 ~= nil) then
				table.insert (actions, get(u1))
			elseif (u2 ~= nil) then
				table.insert (actions, get(u2))
			else
				local def = script.defaultactions["use"]
				table.insert (actions, get(def))
   			end
			s = ms2(actions)
        elseif (variables._actionInfo.verb.code == "give") then
			--s = giveActionHandler()
			local IhaveObj1 = variables.inventory[variables._actionInfo.obj1] ~= nil
			if (not IhaveObj1) then return nil end
			local obj2 = items2[variables._actionInfo.obj2]
			local actions = {}
			table.insert (actions, action.combo.walk_to_object("guybrush", variables._actionInfo.obj2))
			local u1 = obj.actions["give"] and obj.actions["give"][variables._actionInfo.obj2]
			if (u1 ~= nil) then
				table.insert (actions, get(u1))		
			else 
				local def = script.defaultactions["give"]
				table.insert (actions, get(def))
			end
			s = ms2(actions)
		end
    end
	s.name= "_walk"
    monkey.play(s)
    variables._actionInfo:reset()
    updateVerb()
end
