local ai = scumm.state.actionInfo

scumm.func.changecolor = function(color, entity)
    entity:setcolor(color[1], color[2], color[3], color[4])
end

-- converts the action info to a string (SCUMM based games)
scumm.func.action_to_string = function(ai)
    --print(self.verb)
    local verb = engine.config.verbs[ai.verb]
    local t = { verb.text }
    if (ai.obj1 ~= nil) then
        --o1 = objects[self.obj1]
        -- print ("sticazi " .. self.obj1)
        t[2] = engine.items[ai.obj1].hotspot.text
        if (ai.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = verb.prep
            t[4] = engine.items[ai.obj2].hotspot.text
        else
            if (ai.selectSecond == true) then
                t[3] = verb.prep
            end
        end
    end
    return table.concat(t, " ")
end

scumm.func.updateVerb = function()
    a = monkey.getEntity("currentaction")
    a:settext(scumm.func.action_to_string(scumm.state.actionInfo))
end


scumm.func.getCurrentVerb = function()
	return engine.config.verbs[ai.verb]
end


scumm.func.reset_verb = function()
    scumm.func.set_verb(engine.config.default_verb)
end



scumm.func.set_verb = function(verb)
    local v = engine.config.verbs[verb]
    if v.objects > 0 then
        ai.verb = verb
        ai.obj1 = nil
        ai.obj2 = nil
        ai.selectSecond = false
        scumm.func.updateVerb()
    else
        v.callback()

    end
end

scumm.func.hoverOn = function(obj)
	local actionInfo = scumm.state.actionInfo
    if (actionInfo.obj1 == nil) then
        actionInfo.obj1 = obj
    else
        local verb = scumm.func.getCurrentVerb()
        if (verb.objects > 1 and actionInfo.obj1 ~= obj) then
            actionInfo.obj2 = obj
        end
    end
    scumm.func.updateVerb()
end

scumm.func.hoverOff = function()
    local actionInfo = scumm.state.actionInfo

    if (actionInfo.obj2 ~= nil) then
        actionInfo.obj2 = nil
    else
        -- set obj1 to nil unless we are waiting for 2nd object
        if (actionInfo.selectSecond == false) then
            actionInfo.obj1 = nil
        end
    end
    scumm.func.updateVerb()
end

scumm.func.hover_on_inv_button = function(entity) 
    local color = engine.config.ui.inv_selected
    entity:setcolor(color[1], color[2], color[3], color[4])
    local info = entity:getinfo()
    scumm.func.hoverOn(info.obj)
end

scumm.func.hover_off_inv_button = function(entity) 
    local color = engine.config.ui.inv_unselected
    entity:setcolor(color[1], color[2], color[3], color[4])
    local info = entity:getinfo()
    scumm.func.hoverOff()
end

scumm.func.check_pending_script = function()
    -- check if the player has a pending action
    if variables.pending_action[variables.current_player] then
        local s = script.make(variables.pending_action[variables.current_player])        
        monkey.play(s)  
        variables.pending_action[variables.current_player] = nil
    end

end

scumm.func.run_action = function()
    -- mm, no target object here, just ignore the click
    if not ai.obj1 then
        return
    end

    scumm.func.check_pending_script()

    -- get the verb handler
    local f = engine.config.verbs[ai.verb].callback
    if not f then
        print ('no handler available for verb: ' .. ai.verb)
    else
        f(ai.verb)
    end 



end

-- handler for verbs taking two objects (i.e. use, and give)
scumm.func.d2_handler = function(verb)
    --print ('verb is ' .. verb)

    -- clearly, if no object is selected, do nothing
    local item1 = engine.items[ai.obj1]
    if not item1 then
        return
    end

    local actions = {}

    -- if only one object is selected, check out if use is available for obj1
    if ai.obj1 and not ai.obj2 then
        -- check if item has a walkto. If so, walk the player to the object, unless player owns it
        if (item1.actions and item1.actions[verb] and not item1.actions[verb] == 'table') then
            if not scumm.utils.has_player(ai.obj1) then
                scumm.utils.add_walk_to (actions, ai.obj1)
            end            
            local add = glib.get(item.actions[verb])
            table.insert (actions, add)
        else
            -- add the preposition
            ai.selectSecond = true
            scumm.func.updateVerb()

        end


    end

    if ai.obj1 and ai.obj2 then
        local item2 = engine.items[ai.obj2]
        -- both objects specified. Here we need to make some distinctions

        -- easy. player has ONE of the items
        -- in this case we walk to 
        has_o1 = scumm.utils.has_player (ai.obj1)
        has_o2 = scumm.utils.has_player (ai.obj2)
        if (has_o1 ~= has_o2) or (has_o1 and has_o2) then
            if (has_o1 ~= has_o2) then
                external_item = has_o1 and item2 or item1            
                scumm.utils.add_walk_to (actions, external_item)
            end
            -- check if item1 has the action
            custom_action = nil
            i1a = item1.actions and item1.actions[verb] and item1.actions[verb][ai.obj2]

            if not i1a then
                i2a = item2.actions and item2.actions[verb] and item2.actions[verb][ai.obj1]
                if not i2a then 
                    -- default 
                    table.insert (actions, engine.config.verbs[verb].def())                    
                else
                    custom_action = item2.actions[verb][ai.obj1]
                end
            else
                custom_action = item1.actions[verb][ai.obj2]
            end
            if custom_action then
                local add = glib.get(custom_action)
                table.insert (actions, add)
            end
        else
            -- player doesn't have any of the items...
            print ('not supported yet.')
        end
    end

    if next(actions) == nil then
        return
    end
    table.insert (actions, { type = action.callfunc, args = { func = function() scumm.func.reset_verb() end }})

    local s = script.make(actions)
    s.name="_walk"
    monkey.play(s)  

end


scumm.func.default_handler = function(verb)
    --print ('default handler! verb = ' .. verb)

    local item = engine.items[ai.obj1]
    if not item then
        print ("unknown item: " .. ai.obj1)
        return
    end

    local actions = {}
    -- check if item has a walkto. If so, walk the player to the object, unless player owns it
    if not scumm.utils.has_player(ai.obj1) then
        local hs = item.hotspot
        table.insert (actions, { type = scumm.action.walkto, args = {tag='player', pos = hs.walk_to }})
        table.insert (actions, { type = scumm.action.turn, args = { tag = 'player', dir = hs.dir }})
    end

    if item.actions then
        if item.actions[verb] then
            local add = glib.get(item.actions[verb])
            table.insert (actions, add)
        else
            -- default action
            local default_action = engine.config.verbs[verb].def
            if default_action then
                table.insert (actions, default_action())
            end
        end
    end

    table.insert (actions, { type = action.callfunc, args = { func = function() scumm.func.reset_verb() end }})

    local s = script.make(actions)
    s.name="_walk"
    monkey.play(s)  

end



scumm.func.refresh_inventory = function()
    local c = monkey.getEntity('inventory')
    c:cleartext()
    for k, v in pairs(variables.inventory[variables.current_player]) do
        c:addtext ({id=k, qty = v})
    end
end

scumm.func.handleDialogueButton = function (x,y,entity)
    local m2 = monkey.getEntity("dialogueui")               
    m2:cleartext()
    --print ("calling handleDialogueButton ...")
    local info = entity:getinfo()  
    
    local dialogueNode = info.node
    local dialogue = engine.dialogues[info.dialogue]

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
        --print ("Running script ...")
        actions = glib.get(dialogueNode.script)
    else
        print ("button has no script attached.")
    end

    print ('ij')
    local s1 = { type = scumm.action.resume_dialogue, args = { dialogue = info.dialogue, node = dialogueNode }}
    if (actions ~= nil) then
        table.insert (actions, s1)
    else
        actions = s1
    end
    local s = script.make(actions)

    monkey.play(s)
end

scumm.func.closeDialogue = function(dialogue) 
    local m = monkey.getEntity('mainui')
    local m1 = monkey.getEntity('main')
    local m2 = monkey.getEntity('dialogueui')

    scumm.state.walk_enabled = true
    m2:cleartext()
    m2:setactive(false)
    if not m.isnil then
        m:setactive(true)  
    end
    if not m1.isnil then
        m1:enablecontrols(true)      
    end
    if dialogue.close then
        dialogue.close()
    end
end

scumm.func.walk = function(x, y) 
    scumm.func.check_pending_script()
	local actions = {
		{ type = scumm.action.walkto, args = {tag='player', pos = {x, y}}}
	}
	local s = script.make(actions)
	s.name="_walk"
	monkey.play(s)	
end
