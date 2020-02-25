local ai = scumm.state.actionInfo

scumm.script.changecolor = function(color, entity)
    entity:setcolor(color[1], color[2], color[3], color[4])
end

scumm.script.say = function(l) 
    return { type = scumm.action.say, args = { tag = 'player', lines = l}}
end


scumm.script.changeroom = function (args)
    return {
        { type = action.callfunc, args = { func = function() 
            -- remove player from current room
            variables.dynamic_items[engine.state.room][variables.current_player] = nil
            if not variables.dynamic_items[args.room] then variables.dynamic_items[args.room] = {} end
            variables.dynamic_items[args.room][variables.current_player] = { wa = args.walkarea, pos = args.pos, dir = args.dir }
            variables.player_pos[variables.current_player] = args.room
        end}},
        { type = action.change_room, args = { room = args.room }}
    }
        
end

scumm.script.pickup = function(id, flag)
    return {
        { type = action.callfunc, args = { func = function()
            local e = monkey.getEntity(id)
            e:setactive(false)
            if flag then
                variables[flag] = true
            end end}
        },
        {
            type = scumm.action.add_to_inventory, args = {id=id}
        }

    }
        
end

scumm.script.walk = function(x, y) 
    scumm.script.check_pending_script()
	local actions = {
		{ type = scumm.action.walkto, args = {tag='player', pos = {x, y}}}
	}
	local s = script.make(actions)
	s.name="_walk"
	monkey.play(s)	
end

-- converts the action info to a string (SCUMM based games)
scumm.script.action_to_string = function(ai)
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





scumm.script.getCurrentVerb = function()
	return engine.config.verbs[ai.verb]
end

scumm.script.updateVerb = function()
    a = monkey.getEntity("currentaction")
    a:settext(scumm.script.action_to_string(scumm.state.actionInfo))
end

scumm.script.reset_verb = function()
    scumm.script.set_verb(engine.config.default_verb)
end



scumm.script.set_verb = function(verb)
    local v = engine.config.verbs[verb]
    if v.objects > 0 then
        ai.verb = verb
        ai.obj1 = nil
        ai.obj2 = nil
        ai.selectSecond = false
        scumm.script.updateVerb()
    else
        v.callback()

    end
end

scumm.script.hoverOn = function(obj)
	local actionInfo = scumm.state.actionInfo
    if (actionInfo.obj1 == nil) then
        actionInfo.obj1 = obj
    else
        local verb = scumm.script.getCurrentVerb()
        if (verb.objects > 1 and actionInfo.obj1 ~= obj) then
            actionInfo.obj2 = obj
        end
    end
    scumm.script.updateVerb()
end

scumm.script.hoverOff = function()
    local actionInfo = scumm.state.actionInfo

    if (actionInfo.obj2 ~= nil) then
        actionInfo.obj2 = nil
    else
        -- set obj1 to nil unless we are waiting for 2nd object
        if (actionInfo.selectSecond == false) then
            actionInfo.obj1 = nil
        end
    end
    scumm.script.updateVerb()
end

scumm.script.hover_on_inv_button = function(entity) 
    local color = engine.config.ui.inv_selected
    entity:setcolor(color[1], color[2], color[3], color[4])
    local info = entity:getinfo()
    scumm.script.hoverOn(info.obj)
end

scumm.script.hover_off_inv_button = function(entity) 
    local color = engine.config.ui.inv_unselected
    entity:setcolor(color[1], color[2], color[3], color[4])
    local info = entity:getinfo()
    scumm.script.hoverOff()
end

scumm.script.check_pending_script = function()
    -- check if the player has a pending action
    if variables.pending_action[variables.current_player] then
        local s = script.make(variables.pending_action[variables.current_player])        
        monkey.play(s)  
        variables.pending_action[variables.current_player] = nil
    end

end

scumm.script.run_action = function()
    -- mm, no target object here, just ignore the click


    if not ai.obj1 then
        return
    end

    scumm.script.check_pending_script()

    -- get the verb handler
    local f = engine.config.verbs[ai.verb].callback
    if not f then
        print ('no handler available for verb: ' .. ai.verb)
    else
        f(ai.verb)
    end 



end



-- handler for verbs taking two objects (i.e. use, and give)
scumm.script.d2_handler = function(verb)
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
            scumm.script.updateVerb()

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
    table.insert (actions, { type = action.callfunc, args = { func = function() scumm.script.reset_verb() end }})

    local s = script.make(actions)
    s.name="_walk"
    monkey.play(s)  

end


scumm.script.default_handler = function(verb)
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

    table.insert (actions, { type = action.callfunc, args = { func = function() scumm.script.reset_verb() end }})

    local s = script.make(actions)
    s.name="_walk"
    monkey.play(s)  

end



scumm.script.refresh_inventory = function()
    local c = monkey.getEntity('inventory')
    c:cleartext()
    for k, v in pairs(variables.inventory[variables.current_player]) do
        c:addtext ({id=k, qty = v})
    end
    --     if (v == 1) then
    --         c:addtext( {text = engine.items[k].hotspot.text, obj = k})
    --     else
    --         c:addtext( { text = tostring(v) .. " " .. engine.items[k].hotspot.text_plural, obj = k}) -- l, obj = k} )
    --     end
    -- end
end