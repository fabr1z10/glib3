
-- initialize game characters and dynamic items
-- args must be an array of tables, where each table should specify:
-- key    req/opt  type         desc
-- ###########################################
-- id     required string       the item id
-- player optional bool    	    whether the item is a player (default = false)
-- room   required string       the room where the player is
-- pos    required vec2         the initial position (x, y)
-- dir    optional char         the direction (only for characters, can be n, s, e, w)
scumm.utils.init = function(args) 
    variables.players = {}
    variables.player_pos = {}
    variables.inventory = {}
    variables.dynamic_items = {}
    variables.pending_action = {}
    for _, i in ipairs(args) do
        print ('adding ' .. i.id)
        if i.type == 'player' then
            table.insert(variables.players, i.id)
            variables.inventory[i.id] = {}
            variables.player_pos[i.id] = i.room
        end
        if not variables.dynamic_items[i.room] then variables.dynamic_items[i.room] = {} end
        variables.dynamic_items[i.room][i.id] = { pos = i.pos, dir = i.dir }
    end

    variables.current_player = variables.players[1]
    print ('the current player is ' .. variables.current_player)
end


-- returns whether current player has a particular item
scumm.utils.has_player = function(id)
    return variables.inventory[variables.current_player][id] ~= nil
end

-- helper function to buils prite models!
scumm.utils.mm2 = function(id, sheet, anim, frames, frametime)
    local m = {
        sheet = sheet, 
        type = 'sprite.model',
        ppu = 1
    }
    local dt = frametime or 0.1
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

scumm.utils.add_walk_to = function(actions, item)
    
    local hs = item.hotspot
    if hs then 
        table.insert (actions, { type = scumm.action.walkto, args = {tag='player', pos = hs.walk_to }})
        table.insert (actions, { type = scumm.action.turn, args = { tag = 'player', dir = hs.dir }})
    end
end