scumm.ui = {}
local actionInfo = engine.state.scumm.actionInfo
local inventory = engine.state.scumm.inventory

-- converts the action info to a string (SCUMM based games)
function engine.state.scumm.actionInfo:toString ()
	print(self.verb)
	local verb = engine.config.verbs[self.verb]
    local t = { verb.text }	
    if (self.obj1 ~= nil) then
        --o1 = objects[self.obj1]
        print ("sticazi " .. self.obj1)
        t[2] = engine.items[self.obj1].hotspot.text
        if (self.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = engine.items[self.obj2].hotspot.text
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





-- the default behavior when you click on an object
function scumm.ui.runAction ()
    -- mm, no target object here, just ignore the click
    if (actionInfo.obj1 == nil) then
        return nil
    end
	-- create a brand new script
    --local s = script:new("_walk")
	--s.name="_walk"
	local obj = engine.items[actionInfo.obj1]
    if (actionInfo.obj2 == nil) then
        -- try to run a single object action
		if (actionInfo.verb == "give") then
        	actionInfo.selectSecond = true
            scumm.ui.updateVerb()
            return		
		end
        a = obj.actions[actionInfo.verb]
        if (a == nil) then
            if (actionInfo.verb == "use") then
                actionInfo.selectSecond = true
                scumm.ui.updateVerb()
                return
            else
                -- run default
                -- Here we generate a play script. The first action is always a walkto towards the provided
                -- object position. The following action depend on the default action, usually it just says something
                -- like "It doesn't seem to work" or the like.
				print ("Running default script (" .. actionInfo.verb .. ", " .. actionInfo.obj1 .. ") ...")
				local actions = {}
				if (inventory[actionInfo.obj1] == nil) then		
					actions = {
						{ type = scumm.action.walkto, args = { tag="player", obj = actionInfo.obj1 }},
						{ type = scumm.action.turn, args = { tag="player", dir = obj.hotspot.dir }}
					}			
				end
				local b = engine.config.defaultactions[actionInfo.verb]
				if (b ~= nil) then		
					table.insert (actions, b)
				end
				s = script.make (actions)
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
			print ("Running script (" .. actionInfo.verb .. ", " .. actionInfo.obj1 .. ") ...")
			local actions = {}
			if (inventory[actionInfo.obj1] == nil) then
				actions = {
					{ type = scumm.action.walkto, args = { tag="player", obj = actionInfo.obj1 }},
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
        if (actionInfo.verb.code == "use") then
			local obj2 = engine.items[actionInfo.obj2]
			-- walk action
			-- 1. If both obejcts are in inventory, stay where you are
			-- 2. If one object is in inventory, walk to the other object
			-- 3. If both objects are not in inventory, then
			-- a. If obj1 has a pickup action, pick it up and go to obj2
			-- b. If obj2 has a pickup action, pick it up and go to obj1
			-- c. If no pickup action is there, walk to obj2
			local actions = {}
			local IhaveObj1 = inventory[actionInfo.obj1] ~= nil
			local IhaveObj2 = inventory[actionInfo.obj2] ~= nil
			if (IhaveObj1 and (not IhaveObj2)) then
				table.insert (actions, action.combo.walk_to_object("player", actionInfo.obj2))
			elseif (IhaveObj2 and (not IhaveObj1)) then
				table.insert (actions, action.combo.walk_to_object("player", actionInfo.obj1))
			elseif ((not IhaveObj1) and (not IhaveObj2)) then
				local pu1 = obj.actions["pickup"]
				local pu2 = obj2.actions["pickup"]
				if (pu1 ~= nil) then
					-- go pick-up 1st object, walk to 2nd
					table.insert (actions, scumm.action.walk_to_object("player", actionInfo.obj1))
					table.insert (actions, glib.get(pu1))
					table.insert (actions, scumm.action.walk_to_object("player", actionInfo.obj2))
				elseif (pu2 ~= nil) then
					-- go pick-up 2nd object, walk to 2nd
					table.insert (actions, scumm.action.walk_to_object("player", actionInfo.obj2))
					table.insert (actions, glib.get(pu2))
					table.insert (actions, scumm.action.walk_to_object("player", actionInfo.obj1))
				else 
					table.insert (actions, scumm.action.walk_to_object("player", actionInfo.obj2))
				end
			end
			-- now, slap the actual use action
			local u1 = obj.actions["use"] and obj.actions["use"][actionInfo.obj2]
			local u2 = obj2.actions["use"] and obj2.actions["use"][actionInfo.obj1]
			if (u1 ~= nil) then
				table.insert (actions, get(u1))
			elseif (u2 ~= nil) then
				table.insert (actions, get(u2))
			else
				local def = config.defaultactions["use"]
				table.insert (actions, get(def))
   			end
			s = script.make(actions)
        elseif (actionInfo.verb == "give") then
			--s = giveActionHandler()
			local IhaveObj1 = inventory[actionInfo.obj1] ~= nil
			print ("I have " .. actionInfo.obj1 .. " = " .. tostring(IhaveObj1))
			if (not IhaveObj1) then return nil end
			local obj2 = items[actionInfo.obj2]
			local actions = {}
			table.insert (actions, scumm.action.walk_to_object("player", actionInfo.obj2))
			local u1 = obj.actions["give"] and obj.actions["give"][actionInfo.obj2]
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
    actionInfo:reset()
    scumm.ui.updateVerb()
end


function scumm.ui.hoverOn (obj)
	local actionInfo = engine.state.scumm.actionInfo
    if (actionInfo.obj1 == nil) then
        -- print ("setting to " .. obj)
        actionInfo.obj1 = obj
		--print ("setting to " .. variables._actionInfo.obj1)
    else
        local verb = scumm.ui.getCurrentVerb()
        if (verb.objects > 1 and actionInfo.obj1 ~= obj) then
            actionInfo.obj2 = obj
        end
    end
    scumm.ui.updateVerb()
end

function scumm.ui.hoverOff ()
	local actionInfo = engine.state.scumm.actionInfo

    if (actionInfo.obj2 ~= nil) then
        actionInfo.obj2 = nil
    else
        -- set obj1 to nil unless we are waiting for 2nd object
        if (actionInfo.selectSecond == false) then
            actionInfo.obj1 = nil
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
	for k, v in pairs(inventory) do
		if (v == 1) then
			c:addtext( {text = items[k].hotspot.text, obj = k})
		else
			c:addtext( { text = tostring(v) .. " " .. items[k].hotspot.text_plural, obj = k}) -- l, obj = k} )
		end
	end

end

function scumm.ui.handleDialogueButton(x,y,entity)
    local m2 = monkey.getEntity("dialogueui")               
    m2:cleartext()
    --print ("calling handleDialogueButton ...")
    local info = entity:getinfo()  
    local dialogueNode = info.data.node
    local dialogue = engine.dialogues[info.data.dialogue]
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
	if (engine.state.scumm.actionInfo.verb == "walk") then
		-- check if the current action is 
		-- is player on this walkarea?
		local player = monkey.getEntity("player")
		local playerWalkarea = player:parent().tag
		if (args.walkarea == nil or args.walkarea == playerWalkarea) then
			-- assume same walk area
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

function scumm.ui.getCurrentVerb() 
	return engine.config.verbs[engine.state.scumm.actionInfo.verb]
end

function scumm.ui.runSciAction (x, y, objId)
    -- enter paused mode
    -- get current action
    local currentVerb = engine.state.scumm.actionInfo.verb
    print ("current verb: " .. currentVerb)
	local p = engine.items[objId].actions[currentVerb]
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


