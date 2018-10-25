function getProperty(a)
	return (type(a) == "function" and a() or a)
end

-- Create a script where the player walks to an object and turns toward its direction
function createWalkToAction(args)
	s = script:new()
	-- if the object is in the inventory, nothing to be done
	if (inventory[args.objectId] ~= nil and args.goanyway == nil) then
		return nil
	end
	
    obj = objects[args.objectId]
	if (obj.posfunc == nil) then
		walkPos = obj.pos
	else
		walkPos = obj.posfunc()
	end
	
	s.actions[1] = { type="walkto", walkarea = "walkarea", actor = "player", pos = walkPos }

	dir = nil
	if (obj.dirfunc ~= nil) then
		dir = obj.dirfunc()
	else
		dir = obj.dir
	end

    if (dir ~= nil) then
		s.actions[2] = { type="turn", actor = "player", face = dir, after = {1} }
    end
	return s
end

function say (args)
	--local actions = {}
	c = objects[args.character]
	local action = {
	    type= "say",
    	actor = c.tag,
        color = c.color,
        message = args.lines,
		offset = c.offset,
		animstart = args.animstart,
		animend = args.animend,
		noanim = args.noanim,
		after = args.after
    }    
    return action
end


function createObject (obj) 
    --print ("CREATE OBJ" .. obj.tag)
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
	local a = inventory[obj.name]
	if (a == nil) then
		inventory[obj.name] = { qty = obj.qty }
	else
		a.qty = a.qty + obj.qty
	end
	refreshInventory()
end

function dropItem(obj)
	inventory[obj] = nil
	refreshInventory()
end

function removeItemFromInventory(obj) 
	print ("removing " .. obj)
	inventory[obj] = nil
	refreshInventory()
end

function pickup (args) 
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
	local s = script:new()
	s.actions =  {
        [1] = {type = "animate", actor="player", anim=pickupAnim },
        [2] = {type = "delay", sec="0.5", after={1} },
        [3] = {type = "animate", actor="player", anim=("idle_" .. face), after={2} },
		[4] = {type = "callfunc", func = curry(pickupItem, args.obj), after={3} },
		--[5] = {type = "callfunc", func = curry(removeObject, o.tag), after = {4}}
		[5] = {type="callfunc", func=curry(setActive, {id=args.obj, active=false}), after={4}}
	}
	return s
end

function drop (args) 
	-- first check if obj is in inventory
	if (inventory[args.obj] == nil) then
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
	local s = script:new()
	s.actions =  {
        [1] = {type = "animate", actor="player", anim=pickupAnim },
        [2] = {type = "delay", sec="0.5", after={1} },
        [3] = {type = "animate", actor="player", anim=("idle_" .. face), after={2} },
		[4] = {type = "callfunc", func = curry(dropItem, args.obj), after={3} },
		[5] = {type = "callfunc", func=curry(setActive, {id=args.obj, active=true}), after={4}}
	}
	return s
end





function changeRoom(roomId)
	local s = script:new()
    s.actions = {
        [1] = { type = "gotoroom", room = roomId }
    }
	return s
end

function talk(args)
	local s = script:new()
    s.actions = {
        [1] = { type = "callfunc", func = curry(startDialogue, { dialogueId=args.character, nodeId=args.node, init = true }) }
    }
	return s
end

function lookPiecesOfEight() 
	local s = script:new()	
	s.actions = {
		[1] = say { character ="guybrush", lines = { strings.piecesofeightmsg() } }
	}
	return s

end


function walkToDoor(args) 
	local o = objects[args.obj]
    if (o.isopen() == true) then
    	s = script:new()
		s.actions[1] = { type = "gotoroom", room = args.roomId } 
		return s
    else
    	return nil
    end
end

-- checks if a door is open
function isOpen (doorName)
	return variables.doors[doorName]
end

function setOpen (doorName, value)
	variables.doors[doorName] = value
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
        s = script:new()
        s.actions = { 
			--{ type="turn", actor="player", face = direction},
        	[1] = { type="animate", actor="player", anim=("operate_" .. face), flipx = (direction == "west")},
            [2] = { type="delay", sec="0.5", after={1} },
    		[3] = { type="animate", actor = o.tag, anim = (args.open and "open" or "close"), after={2} },
            [4] = { type="animate", actor="player", anim=("idle_" .. face), flipx = (direction == "west"), after={3} },
        	[5] = { type="callfunc", func = function() o.setopen(args.open) end, args={4} }
        }
        return s
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
    	if (getProperty(node.lines[k].active) == true) then
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
		 	onclick = curry(onDialogueButtonClick, node.lines[k])
		})
    end

end

function _say(args) 
	s = script:new()
	s.actions[1] = say(args) 
	return s
end

function storeKeeperChase(x, y, anim, flip, walkto, prevroom)
	if (variables.chase == 1 and (variables._previousroom == prevroom)) then
		local s = script:new("_chase")
		s.actions = {
			[1] = { type = "callfunc", func = curry (createObject, { 
				pos = {x, y, 0},
				gfx = { model = "storekeeper", anim = anim, flip=flip },
				scaling = {},
				tag = "storekeeper"
			})},
			[2] = { type = "walkto", actor = "storekeeper", pos = walkto, after={1} },
			[3] = { type="callfunc", func = curry(setActive, {id="storekeeper", active=false}), after={2} },
			[4] = {type="delay", sec=8, after={3}},
			[5] = {type="callfunc", func = function() variables.chase=0 end, after={4}},
		}
		monkey.play(s)
	else 
		variables.chase = 0
	end
end
