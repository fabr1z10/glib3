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

function assert(a, b)
	if (a == nil) then 
		error("Required argument: " ..b, 2) 
	end
end

function get(ref)
	if (type(ref)=="function") then
		return ref()
	else
		return ref
	end
end

function isarray(t) 
    return (type(t)=="table" and t[1] ~= nil)
end

-- takes an input array and flattens it
-- e.g {1, 2,{3, {5, 7}, 4}, 10} --> {1, 2, 3, 5, 7, 4, 10}
function flatten(a) 
    local out = {}
    for _, v in ipairs(a) do
        if (isarray(v)) then
            print (tostring(v) .. " is an array")
            tmp = flatten(v)
            for _, j in ipairs(tmp) do
               table.insert(out, j)
            end
        else
            print (tostring(v) .. " is not an array")
            table.insert(out, v)
        end
    end
    return out
end

function flatten_script(a, offset) 
    local out = {}
	local ref_id = {}
	local id = offset
    for _, v in ipairs(a) do
        if (isarray(v)) then
            --print (tostring(v) .. " is an array")
            tmp = flatten_script(v, id)
			-- copy all ref id 
			for k, v in pairs(tmp[2]) do
				ref_id[k] = v
			end
            for _, j in ipairs(tmp[1]) do
               table.insert(out, j)
            end
			id = tmp[1][#tmp[1]].id
        else
            --print (tostring(v) .. " is not an array")
			if (v.type ~= nil) then
				id = id + 1
				local node = { id = id, action = v.type(v.args) }
				if (v.ref ~= nil) then
					ref_id[v.ref] = id
				end
				if (v.after ~= nil) then 
					node.after = {}
					for _, ref in ipairs(v.after) do
						table.insert (node.after, ref_id[ref])
					end
				else
					if (id > 0) then
						node.after = { id-1 } 
					end
				end
	            table.insert(out, node)
			end
        end
    end
    return {out, ref_id}
end


function defaultHelper(line) 
	s = script:new()
	s.actions[1] = say {character="guybrush", lines = {strings.defaultactions[line]}}
	return s
end


-- load all files in a folder
function load_all(folder_name)
    print ("Loading all files in " .. folder_name .. " ...")
    --local s = "find " .. _path .. " -path " .. folder_name .. "/*.lua | cut -c" .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    s = "find " .. _path .. folder_name .. "/*.lua | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    --print (s)
    local p = io.popen(s)
    for line in p:lines() do
        --print(" " .. line)
        require(line)
    end
end

function ms(args)
    return function()
        local s = script:new()
		--print ("number of action = " .. tostring(#args))
		s.actions = {}
        for k, v in ipairs(args) do
            table.insert(s.actions, v[1](v[2]))
        end
        return s
    end	
end

function ms2(args, loop)

    local s = script:new()
	local data = flatten_script (args, 0) 
	s.actions = data[1]
	if (loop ~= nil) then
		s.loop = data[2][loop]
		print ("script has loop at ref = " .. tostring(loop) .. " which corresponds to id = " .. tostring(s.loop))
	end
		
	-- just for debug. print action
	for _,v in pairs(s.actions) do 
		local sa = ""
		if (v.after == nil) then
			sa = (v.id == 1) and "-" or "{" .. tostring(v.id-1) .. "}"
		else
			sa = tostring(#(v.after)) .. "{"
			for _, after in ipairs(v.after) do
				sa = sa .. tostring(after) .. ", "
			end
			sa = sa .. "}"
		end
		--print ("id = " .. tostring(v.id) .. ", after = " .. sa .. ", type = " .. v.action.type)	
	end
    return s
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

function changecolor (color, entity)
    entity:setcolor(color[1], color[2], color[3], color[4])
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

function variables._actionInfo:toString ()
    local t = { self.verb.text }

    if (self.obj1 ~= nil) then
        --o1 = objects[self.obj1]
        t[2] = items2[self.obj1].hotspot.text
        if (self.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = items2[self.obj2].hotspot.text
        else
            if (self.selectSecond == true) then
               t[3] = self.verb.prep 
            end
        end 
    end
    return table.concat(t, " ")
end


function variables._actionInfo:reset()
   self.verb = config.verbs.walk
   self.obj1 = nil
   self.obj2 = nil
   self.selectSecond = false
end


function hoverOn (obj)
	print ("CIAO! " .. obj)
    if (variables._actionInfo.obj1 == nil) then 
		print ("Set")
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
    --local s = script:new("_walk")
	--s.name="_walk"
	local obj = items2[variables._actionInfo.obj1]
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
				print ("Running default script (" .. variables._actionInfo.verb.text .. ", " .. variables._actionInfo.obj1 .. ") ...")
				local actions = {}
				if (variables.inventory[variables._actionInfo.obj1] == nil) then		
					actions = {
						{ type = action.walkto, args = { actor="guybrush", obj = variables._actionInfo.obj1 }},
						{ type = action.turn, args = { actor="guybrush", dir = obj.hotspot.dir }}
					}			
				end
				local b = script.defaultactions[variables._actionInfo.verb.code]
				if (b ~= nil) then		
					table.insert (actions, b)
				end
				s = ms2 (actions)
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
			print ("Running script (" .. variables._actionInfo.verb.text .. ", " .. variables._actionInfo.obj1 .. ") ...")
			local actions = {}
			if (variables.inventory[variables._actionInfo.obj1] == nil) then		
				actions = {
					{ type = action.walkto, args = { id=1, actor="guybrush", obj = variables._actionInfo.obj1 }},
					{ type = action.turn, args = { id=2, actor="guybrush", dir = obj.hotspot.dir }}
				}		
			end
			table.insert (actions, get(a))
			s = ms2 (actions)
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        if (variables._actionInfo.verb.code == "use") then
			local obj2 = items2f[variables._actionInfo.obj2]
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
			local IhaveObj1 = variables.inventory[variables._actionInfo.obj1] ~= nil
			if (not IhaveObj1) then return nil end
			local obj2 = items2[variables._actionInfo.obj2]
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
	s.name= "_walk"
    monkey.play(s)
    variables._actionInfo:reset()
    updateVerb()
end

function handleDialogueButton(entity)
    local m2 = monkey.getEntity("dialogueui")               
    m2:cleartext()
    --print ("calling handleDialogueButton ...")
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
    local actions = nil
    if (dialogueNode.script ~= nil) then
        print ("Running script ...")
        actions = get (dialogueNode.script)
    else
        print ("button has no script attached.")
    end


	local s1 = { type = action.resume_dialogue, args = { dialogue = info.data.dialogue, node = dialogueNode }}
    if (actions ~= nil) then
    	table.insert (actions, s1)
    else
        actions = s1
    end
    local s = ms2 (actions)

    monkey.play(s)
end

refresh_inventory = function()
	local c = monkey.getEntity("inventory")
	c:cleartext()
	for k, v in pairs(variables.inventory) do
		if (v == 1) then
			c:addtext( {text = items[k].hotspot.text, obj = k})
		else
			c:addtext( { text = tostring(v) .. " " .. items2[k].hotspot.text_plural, obj = k}) -- l, obj = k} )
		end
	end

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

function hover_on_inv_button(entity) 
	local color = config.ui_inv_selected
	entity:setcolor(color[1], color[2], color[3], color[4])
	local info = entity:getinfo()
	hoverOn(info.data.obj)
end

function hover_off_inv_button(entity) 
	local color = config.ui_inv_unselected
	entity:setcolor(color[1], color[2], color[3], color[4])
	local info = entity:getinfo()
	hoverOff()
end
