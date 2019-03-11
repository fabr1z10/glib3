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
			c:addtext( {text = items2[k].hotspot.text, obj = k})
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
