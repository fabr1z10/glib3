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


objects.village1_door.walk = curry(walkToDoor, {obj = objects.village1_door, roomId = "lookout"} )
objects.village1_door.open = curry(operateDoor, {obj = objects.village1_door, open = true} )
objects.village1_door.close = curry(operateDoor, {obj = objects.village1_door, open = false} )



actions = {
    
    path = {
        open = pippo
        
        
    }
    
 
    
    
    
}

