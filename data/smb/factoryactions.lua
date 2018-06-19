
-- script object
Script = {}
Script.__index = Script

function Script.create(id)
    local self = setmetatable({}, Script)
    self.id = id
    self.startid = 0
    self.actions = {}
    self.edges={}
    return self
end

-- add actions to the script
function Script:add(actions)
    if (actions ~= nil) then
        for _, action in ipairs(actions) do
            action.id = #self.actions
            print("adding " .. action.type)
            table.insert (self.actions, action)
        end
    else
        print("NIL")
    end
end

function Script:setsequence()
    for n = 1, #self.actions-1 do
        table.insert (self.edges, {self.actions[n].id, self.actions[n+1].id})
    end
end

function Script:setloop()
    self:setsequence()
    table.insert (self.edges, {self.actions[#self.actions].id, self.actions[1].id})
end

function createObject (obj) 
    print ("CREATE OBJ" .. obj.tag)
    parent = monkey.getEntity("main")

    monkey.addEntity (obj, parent)
end


function removeObject (tag) 
    monkey.removeEntity(tag)
end

function createWalkToAction (obj)

    actions = {
        {
            type = "walkto",
            walkarea = "walkarea",
            actor = "player",
            pos = obj.pos
        }
    }

    if (obj.dir ~= nil) then
        table.insert (actions,
        {
            actor = "player",
            type = "turn",
            face = obj.dir
        })
     end

     return actions
end

function empty() 
    return nil
end

function say (args)
    actions = {
    {
        type= "say",
        actor = args.character.tag,
        color = args.character.color,
        message = args.lines
    }
    }
    return actions
end

function turn (args)
    actions = {
    {
        type= "turn",
        actor = args.character.tag,
        face = args.face
    }
    }
    return actions
end

function changeRoom(roomId)
    return {
        { type = "gotoroom", room = roomId }
    }
end

function talk(args)
    return {
        { type = "callfunc", func = curry(startDialogue, { dialogueId=args.character, nodeId=args.node, init = true }) }
    }
end


function walkToDoor(args) 
    if (args.obj.isopen() == true) then
        return {
            { type = "gotoroom", room = args.roomId }
        }
    end 
end

function operateDoor(args)
    -- if args.open == true then I need to something when it's closed
    -- and viceversa, so ...
    if (args.obj.isopen ~= args.open) then
        face = dirHelper[args.obj.dir]
        return { 
            { type="animate", actor="player", anim=("operate" .. face) },
            { type="delay", sec="0.5" },
            { type="animate", actor = args.obj.tag, anim = (args.open and "open" or "close") },
            { type="animate", actor="player", anim=("idle" .. face) },
            { type="callfunc", func = function() args.obj.setopen(args.open) end }
        }
    end 
end

function resumePlay()
    ui = monkey.getEntity("ui")
    ui:setactive(true)
    monkey.enableGroup(1)
end

function startDialogue(args)
    ui = monkey.getEntity("ui")
    monkey.disableGroup(1)
    ui:setactive(false)
    parent = monkey.getEntity("dialogue")

    dial = dialogues[args.dialogueId]
    node = dial[args.nodeId]
    if (args.init == true and dial.init ~= nil) then
        dialogues[args.dialogueId].init()
    end
    
    local tkeys = {}
    for k in pairs(node.lines) do
        if (node.lines[k].active == true) then
            table.insert(tkeys, k )
        end 
    end
    table.sort(tkeys) 
    j = 0
    for _, k in ipairs(tkeys) do
        entity = monkey.addEntity(makeDialogueButton(0, 0, node.lines[k]), parent)
        j = j + entity.lines
        entity:setposition(0, 56 - 8*j, 0)
        
    end

end




