_nextTag = 0


function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function curry2(f, arg)
    return function(x)
       f(arg, x) 
    end 
end

function nextTag()
	_nextTag = _nextTag+1
	return "__auto" .. _nextTag
end


function assert(n, msg) 
	if (n == nil) then
		print (msg)
	end
end

function gr (n, msg)
	if (n == nil) then
		print (msg)
	end
	return n
end

function go (n, d, msg)
	if (n == nil) then
		return d
	end
	return n
end

function get(ref)
	if (type(ref)=="function") then
		print ("PLLLL")
		return ref()
	else
		print ("LMMMM")
		return ref
	end
end

-- load all files in a folder
function load_all(folder_name)
    print ("Loading all " .. folder_name .. " ...")
    --local s = "find " .. _path .. " -path " .. folder_name .. "/*.lua | cut -c" .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    s = "find " .. _path .. folder_name .. "/*.lua | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    --print (s)
    local p = io.popen(s)


    for line in p:lines() do
        print(" " .. line)
        require(line)
    end
end

function ms(args)
    return function()
        local s = script:new()
		print ("number of action = " .. tostring(#args))
		s.actions = {}
        for k, v in ipairs(args) do
            table.insert(s.actions, v[1](v[2]))
        end
        return s
    end
end

function msc(args)
    return function()
    	local s = script:new()
    	for _, ss in ipairs(args) do
        	local s1 = script:new()
			s1.actions = {}
        	for _, v in ipairs(ss) do
        		print("running act")
            	table.insert(s1.actions, v[1](v[2]))
        	end

    		s:push { script=s1 }
        end
		s:dump()
        return s
    end
end




-- basic say script
function say(args) 
	-- requires actor, lines
	local s = script:new()
	s.actions = {
		[1] = { type="say", actor=args.actor.tag, lines = args.lines, offset = args.actor.text_offset, color = args.actor.text_color }
	}
	return s
end

function say2(args)
	local animate = args.animate
    return { 
		type="say", 
		actor=	args.actor.tag, 
		lines = args.lines, 
		offset = args.actor.text_offset, 
		color = args.actor.text_color, 
		animstart = args.animstart,
		animend = args.animend,
		animate = animate,
		after = args.after 
	}
end

function make_dialogue(args)
    print ("POLLOOO")
    local s = script:new()
    s.actions = {}
    local i = 1
    for k,v in ipairs(args) do
        print (v[1].tag .. "saying " .. tostring(#v[2]) .. " lines")
        local a = {i-1}
        if (i ==1) then
            a=nil
        end
		local args = {actor=v[1], lines=v[2], after = a}
		if (#v == 3) then
			args.animstart = v[3].anim_begin
			args.animend = v[3].anim_end
			args.animate = v[3].animate
		end

        s.actions[i] = say2(args)
        print ("polsjduhfuhf")
        i =i+1
    end
    return s
end

function make_script(args) 
	local s = script:new()
    print ("number of actions = " .. tostring(#args.actions))
	s.actions = args.actions
	return s
end


function variables._actionInfo:toString ()
    local t = { self.verb.text }
	print (t)
    if (self.obj1 ~= nil) then
		--o1 = objects[self.obj1]
        t[2] = items[self.obj1].text
        if (self.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = items[self.obj2].text
        else
            if (self.selectSecond == true) then
               t[3] = self.verb.prep 
            end
        end 
    end
    return table.concat(t," ")
end

function variables._actionInfo:reset()
   self.verb = config.verbs.walk
   self.obj1 = nil
   self.obj2 = nil
   self.selectSecond = false
end

function changecolor (color, entity)
    entity:setcolor(color[1], color[2], color[3], color[4])
end

function hover_on_inv_button(entity) 
	local color = config.ui_inv_selected
	entity:setcolor(color[1], color[2], color[3], color[4])
	local info = entity:getinfo()
	print ("Hovering on " .. info.data.obj)
	hoverOn(info.data.obj)
end

function hover_off_inv_button(entity) 
	local color = config.ui_inv_unselected
	entity:setcolor(color[1], color[2], color[3], color[4])
	local info = entity:getinfo()
	hoverOff()
end


function setverb(verb)
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    variables._actionInfo.selectSecond = false
    updateVerb()
end

function updateVerb() 
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())    
end

function change_room(roomId) 
	variables._previousroom = variables._room
	local s = script:new()
	s.actions = {
		[1] = { type="gotoroom", room = roomId}
	}
	return s
end

function walk_player_to(args) 
	local s = script:new()
	s.actions = {
		[1] = { type="walk", actor="player", pos=args.pos }
}
	monkey.play(s)
end

function hoverOn (obj)
    if (variables._actionInfo.obj1 == nil) then 
        variables._actionInfo.obj1 = obj
    else
        if (variables._actionInfo.verb.objects > 1 and variables._actionInfo.obj1 ~= obj) then
            variables._actionInfo.obj2 = obj
        end
    end
    updateVerb()
end

function hoverOff ()
    if (variables._actionInfo.obj2 ~= nil) then
        variables._actionInfo.obj2 = nil
    else
        -- set obj1 to nil unless we are waiting for 2nd object
        if (variables._actionInfo.selectSecond == false) then
            variables._actionInfo.obj1 = nil
        end
    end
    updateVerb()
end

-- the default behavior when you click on an object
function runAction ()
    -- mm, no target object here, just ignore the click
    if (variables._actionInfo.obj1 == nil) then
        return nil
    end
	-- create a brand new script
    local s = script:new("_walk")
	--s.name="_walk"
	print ("RUNNNNO LAZZIONE")
	print (variables._actionInfo.obj1)
	local obj = items[variables._actionInfo.obj1]
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
		if (variables._actionInfo.verb.code == "give") then
        	variables._actionInfo.selectSecond = true
            updateVerb()
            return		
		end
        a = obj.actions[variables._actionInfo.verb.code]
        if (a == nil) then
            if (variables._actionInfo.verb.code == "use") then
                variables._actionInfo.selectSecond = true
                updateVerb()
                return
            else
                -- run default
                -- Here we generate a play script. The first action is always a walkto towards the provided
                -- object position. The following action depend on the default action, usually it just says something
                -- like "It doesn't seem to work" or the like.
				if (variables.inventory[variables._actionInfo.obj1] == nil) then		
					s.actions = {
						action.walkto { id=1, actor="guybrush", obj = obj },
						action.turn { id=2, actor="guybrush", dir = obj.face }
					}			
				end
				local b = script.defaultactions[variables._actionInfo.verb.code]
				if (b ~= nil) then		
					s:push { script = b(), at = "end" }
				end
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
			if (variables.inventory[variables._actionInfo.obj1] == nil) then		
				s.actions = {
					action.walkto { id=1, actor="guybrush", obj = obj },
					action.turn { id=2, actor="guybrush", dir = obj.face }
				}		
			end
			--s:push { script = createWalkToAction {objectId = variables._actionInfo.obj1}, at = "end" }
			s:push { script = a(), at = "end" }
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        if (variables._actionInfo.verb.code == "use") then
			local obj2 = items[variables._actionInfo.obj2]
			-- walk action
			-- 1. If both obejcts are in inventory, stay where you are
			-- 2. If one object is in inventory, walk to the other object
			-- 3. If both objects are not in inventory, then
			-- a. If obj1 has a pickup action, pick it up and go to obj2
			-- b. If obj2 has a pickup action, pick it up and go to obj1
			-- c. If no pickup action is there, walk to obj2
			local IhaveObj1 = variables.inventory[variables._actionInfo.obj1] ~= nil
			local IhaveObj2 = variables.inventory[variables._actionInfo.obj2] ~= nil
			print ("I HAVE 1 = " .. tostring(IhaveObj1) .. ", i have 2 = " .. tostring(IhaveObj2))
			if (IhaveObj1 and (not IhaveObj2)) then
				s:push { script = walk_to_object(obj2), at="end" }
			elseif (IhaveObj2 and (not IhaveObj1)) then
				s:push { script = walk_to_object(obj), at="end" }
			elseif ((not IhaveObj1) and (not IhaveObj2)) then
				local pu1 = obj.actions["pickup"]
				local pu2 = obj2.actions["pickup"]
				if (pu1 ~= nil) then
					-- go pick-up 1st object, walk to 2nd
					s:push { script = walk_to_object(obj), at="end" }
					s:push { script = pu1(), at="end" }
					s:push { script = walk_to_object(obj2), at="end" }
				elseif (pu2 ~= nil) then
					-- go pick-up 2nd object, walk to 2nd
					s:push { script = walk_to_object(obj2), at="end" }
					s:push { script = pu2(), at="end" }
					s:push { script = walk_to_object(obj), at="end" }					
				else 
					s:push { script = walk_to_object(obj2), at="end" }
				end
			end
			-- now, slap the actual use action
			local u1 = obj.actions["use"] and obj.actions["use"][variables._actionInfo.obj2]
			local u2 = obj2.actions["use"] and obj2.actions["use"][variables._actionInfo.obj1]
			if (u1 ~= nil) then
				s:push {script=u1(), at="end"}
			elseif (u2 ~= nil) then
				s:push {script=u2(), at="end"}
			else
				-- default use handler
				s:push { script = script.defaultactions["use"](), at="end" }
   			end
        elseif (variables._actionInfo.verb.code == "give") then
			--s = giveActionHandler()
			print ("QUI")
			local IhaveObj1 = variables.inventory[variables._actionInfo.obj1] ~= nil
			if (not IhaveObj1) then return nil end
			local obj2 = items[variables._actionInfo.obj2]
			s:push { script = walk_to_object(obj2), at="end" }
			local u1 = obj.actions["give"] and obj.actions["give"][variables._actionInfo.obj2]
			if (u1 ~= nil) then
				s:push {script=u1()}
			else 
				s:push {script = script.defaultactions["give"]()}
			end
		end

        -- a1 = variables._actionInfo.obj1[variables._actionInfo.verb.code]
        -- if (a1 == nil) then
        --     a1 = variables._actionInfo.obj2[variables._actionInfo.verb.code]
        --     if (a1 == nil) then
        --         defaultActions[variables._actionInfo.verb.code](script)
        --     else
                
        --     end
        -- end
            
        
        --script = twoObjectHandler[variables._actionInfo.verb.code]
    end
    monkey.play(s)
    variables._actionInfo:reset()
    updateVerb()
end

function start_dialogue(args)    
	print ("Starting dialogue " .. args.dialogue)
	local dialogue = dialogues[args.dialogue]
	if (dialogue == nil) then
		print ("Can't find dialogue " .. args.dialogue)
	end
    local root = args.root or dialogue.nodes[1]
    if (args.root == nil) then
        if (dialogue.init ~= nil) then
            dialogue.init()
        end
    end
	print ("Run script")
	local s = script:new()
	s.actions ={
		[1] = { type="callfunc", func = function()
			print ("FOTTETEVIs")
			local m = monkey.getEntity("mainui")
			local m1 = monkey.getEntity("main")
			local m2 = monkey.getEntity("dialogueui")
			if (m.isnil) then
				print ("no  main ui")
			else
				m:setactive(false)
			end
			if (m1.isnil) then
				print ("no main")
			else
				m1:enablecontrols(false)
			end
			m2:setactive(true)
			--local root = dialogue[1]
			local children = get(root.children)
			print ("Size of children = " .. tostring(#children))
			m2:cleartext()
			for k, v in ipairs(children) do
				print ("child = " .. tostring(v))
                local node = dialogue.nodes[v]
                print("ciao = " .. tostring(v))
                print ( "pollo === " .. tostring(get(node.active)))
                if (get(node.active) == true) then
				    m2:addtext { text=node.text, dialogue_node = node, dialogue = args.dialogue }
			    end
            end
		end
		}
	}

	return s
end





function handleDialogueButton(entity)
	local m2 = monkey.getEntity("dialogueui")				
	m2:cleartext()
	print ("calling handleDialogueButton ...")
    local info = entity:getinfo()  
    local dialogueNode = info.data.node
    local dialogue = dialogues[info.data.dialogue]
    
    if (dialogueNode.deact ~= nil) then
        for k, v in ipairs(dialogueNode.deact) do
            dialogue.nodes[v].active = false
        end
    end
    if (dialogueNode.act ~= nil) then
        for k, v in ipairs(dialogueNode.act) do
            dialogue.nodes[v].active = true
        end
    end




	local s = nil

	
	if (dialogueNode.script ~= nil) then
        print ("calling button")
		s = dialogueNode.script()
	else
        print ("button has no script attached.")
    end

    local s1 = script:new()
	if (dialogueNode.children == nil) then
	 	-- return to game
	 	s1.actions = {
			action.end_dialogue { id = 1, dialogue = info.data.dialogue }
		}
	else
		atLeastOneActiveChild = false
		for k, v in ipairs(dialogueNode.children) do
            if (dialogue.nodes[v].active == true) then
				atLeastOneActiveChild = true
				break
			end
        end
		if (atLeastOneActiveChild) then
			s1.actions = {
				action.start_dialogue { id=1, dialogue = info.data.dialogue, root = dialogueNode }
			}
		else
	 		s1.actions = {
				action.end_dialogue { id = 1, dialogue = info.data.dialogue }
			}
		end
 --        s1 = start_dialogue {dialogue = info.data.dialogue, root = dialogueNode } 
 --        -- s1.actions = {
 --        --     [1] = { type="callfunc", func = function ()
 --        --         -- body
 --        --         local m2 = monkey.getEntity("dialogueui")
 --        --         for k, v in ipairs(dialogueNode.children) do
 --        --             m2:addtext { text=dialogue[v].text, dialogue_node = dialogue[v], dialogue = dialogue }
 --        --         end
 --        --     end}s
 --        -- }
	end
    if (s == nil) then
 		s = s1
 	else
		s:push { script = s1 }
 	end
	
	monkey.play(s)
end

refresh_inventory = function()
	local c = monkey.getEntity("inventory")
	c:cleartext()
	for k, v in pairs(variables.inventory) do
		if (v == 1) then
			c:addtext( {text = items[k].text, obj = k})
		else
			c:addtext( { text = tostring(v) .. " " .. items[k].text_plural, obj = k} )
		end
	end

end

walk_to_object = function(obj) 
	local s = script:new() 
	s.actions = {
		action.walkto { id=1, actor="guybrush", obj = obj },
		action.turn { id=2, actor="guybrush", dir = obj.face }
	}
	return s	
end

pick_up_item = function(name, act)
	return function()
		if (variables.inventory[name] == nil) then
			local s = script:new()
			local obj = items[name]
			s.actions = {
				action.animate { id=1, actor="guybrush", anim = act },
				action.delay { id=2, sec=0.5 },
				action.turn { id=3, actor="guybrush", dir = obj.face },
				--action.remove_object{ id=4, name = name },
				action.activate {id=4, name=name, value=false},
				action.add_to_inventory{id = 5, name= name, qty = 1}
			}
			--s:dump()
			return s
		else
			return nil
		end
	end
end

checkFunds = function(n)
	local p8 = variables.inventory["pieces_of_eight"]
	if (p8 == nil) then return false end
	return (p8 >= n)
end
