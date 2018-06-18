
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
    print ("SAY!" .. args.lines[1])
    actions = {
    {
        type= "say",
        actor = args.character.name,
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
        actor = args.character.name,
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

function walkToDoor(args) 
    if (args.obj.isopen == true) then
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
            { type="callfunc", func = function() args.obj.isopen = args.open end }
        }
    end 
end

function startDialogue(args)
    print ("CALLING START DIALOGUE!")
    ui = monkey.getEntity("ui")
    ui:setactive(false)
        print ("2")
    parent = monkey.getEntity("dialogue")
    print ("3")
    node = dialogues[args.dialogueId][args.nodeId]
    print ("lines = " .. #node.lines)
    j = 0
    for _, line in ipairs(node.lines) do
        monkey.addEntity(makeDialogueButton(0, 48-8*j, line), parent)
        j = j +1
    end
    


end


