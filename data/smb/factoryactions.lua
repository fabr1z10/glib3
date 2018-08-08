-- Create a script where the player walks to an object and turns toward its direction
function createWalkToAction(args)

	-- if the object is in the inventory, nothing to be done
	if (inventory[args.objectId] ~= nil) then
		return nil
	end
	
    obj = objects[args.objectId]
	if (obj.posfunc == nil) then
		walkPos = obj.pos
	else
		walkPos = obj.posfunc()
	end
	
	local actions = {}
	actions[0] = { type="walkto", walkarea = "walkarea", actor = "player", pos = walkPos }

	dir = nil
	if (obj.dirfunc ~= nil) then
		dir = obj.dirfunc()
	else
		dir = obj.dir
	end

    if (dir ~= nil) then
		actions[1] = { type="turn", actor = "player", face = dir, after = {0} }
    end
	return actions
end

function say (args)
	local s = Script:new(args.scriptname)
	c = objects[args.character]
	s:push({
    	[0] = {
	        type= "say",
    	    actor = c.tag,
        	color = c.color,
        	message = args.lines,
			offset = c.offset,
			animstart = args.animstart,
			animend = args.animend,
			noanim = args.noanim
    	}
    })
    return s
end


function createObject (obj) 
    print ("CREATE OBJ" .. obj.tag)
    parent = monkey.getEntity("main")

    monkey.addEntity (obj, parent)
end


function removeObject (tag) 
    monkey.removeEntity(tag)
end



function empty() 
    return nil
end



function say2 (args)
	c = objects[args.character]
    action = 
    {
        type= "say",
        actor = c.tag,
        color = c.color,
        message = args.lines,
		offset = c.offset,
		animstart = args.animstart,
		animend = args.animend,
		noanim = args.noanim
    }

    return action
end


function turn (args)
    c = objects[args.character]
    actions = {
    {
        type= "turn",
        actor = c.tag,
        face = args.face
    }
    }
    return actions
end

function pickupItem(obj)
	inventory[obj] = { qty = 1 }
	refreshInventory()
end

function pickupItemQty(obj)
	inventory[obj.name] = { qty = obj.qty }
	refreshInventory()
end

function removeItemFromInventory(obj) 
	print ("removing " .. obj)
	inventory[obj] = nil
	refreshInventory()
end

function pickup (args) 
print("qwqwqw")
	-- first check if obj is in inventory
	if (inventory[args.obj] ~= nil) then
		-- I already have this
		return
	end
	local o = objects[args.obj]
	if (o.dirfunc ~= nil) then
		face = dirHelper[o.dirfunc()]
	else
        face = dirHelper[o.dir]
    end
	if (o.pickupAnim == nil) then
		pickupAnim = "operate_" .. face
	else
		pickupAnim = o.pickupAnim
	end
	return {
        {type = "animate", actor="player", anim=pickupAnim },
        {type = "delay", sec="0.5" },
        {type = "animate", actor="player", anim=("idle_" .. face) },
		{type = "callfunc", func = curry(pickupItem, args.obj)},
		{type = "callfunc", func = curry(removeObject, o.tag)}
	}
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

function lookPiecesOfEight() 
	return {
		say2 { character ="guybrush", lines = { strings.piecesofeightmsg() } }
	}

end


function walkToDoor(args) 
	local o = objects[args.obj]
    if (o.isopen() == true) then
        return {
            { type = "gotoroom", room = args.roomId }
        }
    end 
end

function isOpen (doorName)
	local o = objects[doorName]
	return o.openflag
end

function setOpen (doorName, value)
	local o = objects[doorName]
	o.openflag = value
end

function operateDoor(args)
    -- if args.open == true then I need to something when it's closed
    -- and viceversa, so ...
	local o = objects[args.obj]
    if (o.isopen() ~= args.open) then
		local direction =""
		if (o.dirfunc ~= nil) then
			direction = o.dirfunc()
			face = dirHelper[direction]
		else
			direction = o.dir
            face = dirHelper[direction]
        end
		return { 
			--{ type="turn", actor="player", face = direction},
            { type="animate", actor="player", anim=("operate_" .. face), flipx = (direction == "west")},
            { type="delay", sec="0.5" },
            { type="animate", actor = o.tag, anim = (args.open and "open" or "close") },
            { type="animate", actor="player", anim=("idle_" .. face), flipx = (direction == "west") },
            { type="callfunc", func = function() o.setopen(args.open) end }
        }
    end 
end

function pause()
	monkey.enablescriptengine(false)
end

function resumePlay()
print ("OFOFOFOF")
    local ui = monkey.getEntity("uiplay")
	--inv = monkey.getEntity("inventory")
	local d = monkey.getEntity("dialogue")
	local a = monkey.getEntity("main")
	d:setactive(false)
	ui:setactive(true)
    --inv:setactive(true)
	a:enablecontrols(true)
end

function startScript()
    ui = monkey.getEntity("uiplay")
	d = monkey.getEntity("dialogue")
	a = monkey.getEntity("main")
    --monkey.disableGroup(1)
    ui:setactive(false)
	d:setactive(true)
	a:enablecontrols(false)

end

function setActive (args) 
	a = monkey.getEntity(args.id)
	a:setactive(args.active)

end


function startDialogue(args)
    ui = monkey.getEntity("uiplay")
	d = monkey.getEntity("dialogue")
	a = monkey.getEntity("main")
    --monkey.disableGroup(1)
    ui:setactive(false)
	d:setactive(true)
	a:enablecontrols(false)

    -- parent = monkey.getEntity("dialogue")

    dial = dialogues[args.dialogueId]
    node = dial[args.nodeId]

--print(node.lines[1])
    -- if (args.init == true and dial.init ~= nil) then
    --     dialogues[args.dialogueId].init()
    -- end
    
    local tkeys = {}
    for k in pairs(node.lines) do
    	if (node.lines[k].active == true) then
    		table.insert(tkeys, k )
    	end 
    end
    table.sort(tkeys) 
    j = 0
    for _, k in ipairs(tkeys) do
		print ("LINEA = " .. node.lines[k].text)
		d:addbutton({ 
		 	text = node.lines[k].text,
			priority = 1, 
		 	onenter = curry2(changecolor, config.ui_selected_color),
		 	onleave = curry2(changecolor, config.ui_unselected_color), 
		 	onclick = curry(pippo, node.lines[k])
		})
    end

end




