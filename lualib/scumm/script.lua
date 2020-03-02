
scumm.script.say = function(l) 
    return { 
        type = scumm.action.say, args = { tag = 'player', lines = l}
    }
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

scumm.script.pickup = function(args)
    local actions = {}
    if args.anim_start then
        table.insert (actions, { type = action.animate, args = { tag='player', anim = args.anim_start}})
        table.insert (actions, { type = action.delay, args = { sec = 0.5 }})
    end
    table.insert (actions,
        { type = action.callfunc, args = { func = function()
            local e = monkey.getEntity(args.id)
            e:setactive(false)
            if flag then
                variables[flag] = true
            end end}
        })
    table.insert (actions, { type = scumm.action.add_to_inventory, args = {id = args.id} })
    if args.anim_end then 
        table.insert(actions, { type = action.animate, args = { tag='player', anim = args.anim_end} })
    end
    return actions
end




scumm.script.open_door = function(args)
    return {
        { type = action.animate, args = { tag = args.door, anim = 'open' }},
        { type = action.callfunc, args = { func = function() print ('ok') end }}
    }
    
end
