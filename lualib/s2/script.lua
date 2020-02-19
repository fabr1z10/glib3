local ai = scumm.state.actionInfo

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

scumm.utils.mm2 = function(id, sheet, anim, frames)
    local m = {
        sheet = sheet, 
        type = 'sprite.model',
        ppu = 1
    }
    local dt = 0.1
    local anims = {}
    for i, a in ipairs(anim) do
        local fs = {}
        for _, f in ipairs(frames[i]) do
            table.insert(fs, { duration = dt, quads = { {id = f }}})
        end
        local p = { name = a, frames = fs }
        table.insert(anims, p)
    end
    m.animations = anims

    engine.assets.models[id] = m
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
    ai.verb = verb
    ai.obj1 = nil
    ai.obj2 = nil
    ai.selectSecond = false
    scumm.script.updateVerb()
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

scumm.script.run_action = function()
    -- mm, no target object here, just ignore the click
    if not ai.obj1 then
        return
    end

    -- get the verb handler
    local f = engine.config.verbs[ai.verb].callback
    if not f then
        print ('no handler available for verb: ' .. ai.verb)
    else
        f(ai.verb)
    end 



end

scumm.script.default_handler = function(verb)
    --print ('default handler! verb = ' .. verb)

    local item = engine.items[ai.obj1]
    if not item then
        print ("unknown item: " .. ai.obj1)
        return
    end

    -- check if item has a walkto
    local hs = item.hotspot
    print ("eccoci " .. tostring(hs.walk_to[1]))
    local actions = {
        { type = scumm.action.walkto, args = {tag='player', pos = hs.walk_to }},
        -- turn towards item
        { type = scumm.action.turn, args = { tag = 'player', dir = hs.dir }},
    }

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