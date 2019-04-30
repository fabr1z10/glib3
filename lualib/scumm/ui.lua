scumm.ui = {}


-- converts the action info to a string (SCUMM based games)
function engine.state.scumm.actionInfo:toString ()
	print(self.verb)
	local verb = engine.config.verbs[self.verb]
    local t = { verb.text }	
    if (self.obj1 ~= nil) then
        --o1 = objects[self.obj1]
        t[2] = items[self.obj1].hotspot.text
        if (self.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = items[self.obj2].hotspot.text
        else
            if (self.selectSecond == true) then
               t[3] = self.verb.prep 
            end
        end 
    end
    return table.concat(t, " ")
end

function engine.state.scumm.actionInfo:reset()
   self.verb = engine.config.default_verb
   self.obj1 = nil
   self.obj2 = nil
   self.selectSecond = false
end


function scumm.ui.updateVerb() 	
    a = monkey.getEntity("currentaction")
    a:settext(engine.state.scumm.actionInfo:toString())    
end

function scumm.ui.setverb(verb)
    engine.state.scumm.actionInfo.verb = verb
    engine.state.scumm.actionInfo.obj1 = nil
    engine.state.scumm.actionInfo.obj2 = nil
    engine.state.scumm.actionInfo.selectSecond = false
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
	local obj = items[variables._actionInfo.obj1]
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
						{ type = scumm.action.walkto, args = { tag="player", obj = variables._actionInfo.obj1 }},
						{ type = scumm.action.turn, args = { tag="player", dir = obj.hotspot.dir }}
					}			
				end
				local b = config.defaultactions[variables._actionInfo.verb.code]
				if (b ~= nil) then		
					table.insert (actions, b)
				end
				s = script.make (actions)
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
			print ("Running script (" .. variables._actionInfo.verb.text .. ", " .. variables._actionInfo.obj1 .. ") ...")
			local actions = {}
			if (variables.inventory[variables._actionInfo.obj1] == nil) then		
				actions = {
					{ type = scumm.action.walkto, args = { tag="player", obj = variables._actionInfo.obj1 }},
					{ type = scumm.action.turn, args = {tag="player", dir = obj.hotspot.dir }}
				}		
			end
			table.insert (actions, glib.get(a))
			print ("no. actions = " .. tostring(#actions))
			s = script.make (actions)
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        if (variables._actionInfo.verb.code == "use") then
			local obj2 = items[variables._actionInfo.obj2]
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
				table.insert (actions, action.combo.walk_to_object("player", variables._actionInfo.obj2))
			elseif (IhaveObj2 and (not IhaveObj1)) then
				table.insert (actions, action.combo.walk_to_object("player", variables._actionInfo.obj1))
			elseif ((not IhaveObj1) and (not IhaveObj2)) then
				local pu1 = obj.actions["pickup"]
				local pu2 = obj2.actions["pickup"]
				if (pu1 ~= nil) then
					-- go pick-up 1st object, walk to 2nd
					table.insert (actions, scumm.action.walk_to_object("player", variables._actionInfo.obj1))
					table.insert (actions, glib.get(pu1))
					table.insert (actions, scumm.action.walk_to_object("player", variables._actionInfo.obj2))
				elseif (pu2 ~= nil) then
					-- go pick-up 2nd object, walk to 2nd
					table.insert (actions, scumm.action.walk_to_object("player", variables._actionInfo.obj2))
					table.insert (actions, glib.get(pu2))
					table.insert (actions, scumm.action.walk_to_object("player", variables._actionInfo.obj1))
				else 
					table.insert (actions, scumm.action.walk_to_object("player", variables._actionInfo.obj2))
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
				local def = config.defaultactions["use"]
				table.insert (actions, get(def))
   			end
			s = script.make(actions)
        elseif (variables._actionInfo.verb.code == "give") then
			--s = giveActionHandler()
			local IhaveObj1 = variables.inventory[variables._actionInfo.obj1] ~= nil
			print ("I have " .. variables._actionInfo.obj1 .. " = " .. tostring(IhaveObj1))
			if (not IhaveObj1) then return nil end
			local obj2 = items[variables._actionInfo.obj2]
			local actions = {}
			table.insert (actions, scumm.action.walk_to_object("player", variables._actionInfo.obj2))
			local u1 = obj.actions["give"] and obj.actions["give"][variables._actionInfo.obj2]
			if (u1 ~= nil) then
				table.insert (actions, glib.get(u1))		
			else 
				local def = config.defaultactions["give"]
				table.insert (actions, glib.get(def))
			end
			s = script.make(actions)
		end
    end
	s.name= "_walk"
    monkey.play(s)
    variables._actionInfo:reset()
    scumm.ui.updateVerb()
end


function scumm.ui.hoverOn (obj)
	
    if (variables._actionInfo.obj1 == nil) then 
		print ("setting to " .. obj)
        variables._actionInfo.obj1 = obj
		print ("setting to " .. variables._actionInfo.obj1)
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

function scumm.ui.hover_on_inv_button(entity) 
	local color = config.ui.inv_selected
	entity:setcolor(color[1], color[2], color[3], color[4])
	local info = entity:getinfo()
	scumm.ui.hoverOn(info.data.obj)
end

function scumm.ui.hover_off_inv_button(entity) 
	local color = config.ui.inv_unselected
	entity:setcolor(color[1], color[2], color[3], color[4])
	local info = entity:getinfo()
	scumm.ui.hoverOff()
end

function scumm.ui.refresh_inventory()
	local c = monkey.getEntity("inventory")
	c:cleartext()
	for k, v in pairs(variables.inventory) do
		if (v == 1) then
			c:addtext( {text = items[k].hotspot.text, obj = k})
		else
			c:addtext( { text = tostring(v) .. " " .. items[k].hotspot.text_plural, obj = k}) -- l, obj = k} )
		end
	end

end

function scumm.ui.handleDialogueButton(entity)
    local m2 = monkey.getEntity("dialogueui")               
    m2:cleartext()
    --print ("calling handleDialogueButton ...")
    local info = entity:getinfo()  
    local dialogueNode = info.data.node
    local dialogue = dialogues[info.data.dialogue]
    if (dialogueNode.deact ~= nil) then
        for k, v in ipairs(dialogueNode.deact) do
            dialogue.nodes[v].active = false
        end
    end
    if (dialogueNode.act ~= nil) then
        for k, v in ipairs(dialogueNode.act) do
            dialogue.nodes[v].active = true
        end
    end
    local actions = nil
    if (dialogueNode.script ~= nil) then
        print ("Running script ...")
        actions = glib.get(dialogueNode.script)
    else
        print ("button has no script attached.")
    end


    local s1 = { type = scumm.action.resume_dialogue, args = { dialogue = info.data.dialogue, node = dialogueNode }}
     if (actions ~= nil) then
     	table.insert (actions, s1)
     else
        actions = s1
     end
     local s = script.make(actions)

     monkey.play(s)
end

function scumm.ui.pause_script (value) 
    return {
        { type=action.callfunc, args = { func = function() 
            local a =monkey.getEntity("main")
            a:enableupdate(not value)
            a:enablecontrols(not value)
        end}},
        { type=action.suspend_all_scripts, args = {value = value}},
    }
end

function scumm.ui.walk (args)
	if (variables._actionInfo.verb.code == "walk") then

		-- check if the current action is 
		-- is player on this walkarea?
		local player = monkey.getEntity("player")
		local playerWalkarea = player:parent().tag
		if (args.walkarea == nil or args.walkarea == playerWalkarea) then
			-- assume same walk area
print("sifjroifj")
			local actions = {
				{ type = scumm.action.walkto, args = {tag="player", pos = args.pos}}
			}
			return actions
		end
		-- if we get here, we want the player to move to a differnet walk area
		-- first we need to check whether the two are connected
		-- and then we see if there's a connecting script
		print ("Trying to move to apnother walkarea: " .. args.walkarea)
		local a = roomDefinition.walkareas[playerWalkarea]
	 	if (a ~= nil) then
			local b = a[args.walkarea]
			if (b ~= nil) then
				print ("Script found.")
				local actions = {
					b,
					{ type = scumm.action.walkto, args = {tag="player", pos = args.pos}}
				}
				return actions
			end
		end
		print ("not found.")
		return nil
	end
end


function scumm.ui.runSciAction (x, y, objId)
    -- enter paused mode
    -- get current action
    local currentVerb = variables._actionInfo.verb.code
    print ("current verb: " .. currentVerb)
		
 --    --p  rint ("Click pos = " .. tostring(x) .. "," .. tostring(y) .. " obj id = " .. objId)
 --  print (tostring(items[objId].pos[1]))
	-- -- if (currentVerb == "walk") then
	-- -- 	-- forward the click to a walk-area
	-- -- 	if (items[objId].walkarea ~= nil) then
	-- -- 		local wa = monkey.getEntity(items[objId].walkarea)
	-- -- 		wa:forceclick(x, y)
	-- -- 	end
	-- -- 	-- local actions = {
	-- -- 	-- 	{ type = scumm.action.walkto, args = {tag="player", pos = {x,y}}}
	-- -- 	-- }
	-- --  --    local s = script.make(actions)
	-- -- 	-- s.name="_walk"
	-- --  --    monkey.play(s)
	-- -- else 
 --    	if (items[objId].actions == nil or items[objId].actions[currentVerb] == nil) then
 --        	print ("no action <" .. currentVerb .. "> defined for: " .. objId)
 --        	return
 --    	end
	local p = items[objId].actions[currentVerb]
	if (p == nil) then
		print ("... mm no action")
		return
	end
	local s = nil
	if (type(p)=="function") then
		s = p(x, y)
print ("number actions " .. tostring(#s))
	else
		s = p
	end
		
	local actions = {s}
	--         --scumm.ui.pause_script (true),
	--         s,
	--         --scumm.ui.pause_script (false)
	--     }
	local a = script.make(actions)
	a.name="_walk"
	monkey.play(a)
	




end


