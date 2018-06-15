
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

