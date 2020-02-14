local ai = scumm.state.actionInfo


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


scumm.script.getCurrentVerb = function()
	return engine.config.verbs[state.scumm.actionInfo.verb]
end

scumm.script.updateVerb = function()
    a = monkey.getEntity("currentaction")
    a:settext(scumm.script.action_to_string(scumm.state.actionInfo))
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
        local verb = scumm.ui.getCurrentVerb()
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
    print ('default handler! verb = ' .. verb)

    local item = engine.items[ai.obj1]
    if not item then
        print ("unknown item: " .. ai.obj1)
        return
    end

    -- check if item has a walkto
    local hs = item.hotspot

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

    local s = script.make(actions)
    s.name="_walk"
    monkey.play(s)  

end