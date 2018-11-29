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
	s.actions = args
	return s
end


function variables._actionInfo:toString ()
    local t = { self.verb.text }
	print (t)
    if (self.obj1 ~= nil) then
		--o1 = objects[self.obj1]
        t[2] = self.obj1.text
        if (self.obj2 ~= nil) then
            --o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = self.obj2.text
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
    if (variables._actionInfo.obj2 == nil) then
        -- try to run a single object action
		local obj = variables._actionInfo.obj1
        a = obj.actions[variables._actionInfo.verb.code]
        if (a == nil) then
            if (variables._actionInfo.verb.code == "give" or variables._actionInfo.verb.code == "use") then
                variables._actionInfo.selectSecond = true
                updateVerb()
                return
            else
                -- run default
                -- Here we generate a play script. The first action is always a walkto towards the provided
                -- object position. The following action depend on the default action, usually it just says something
                -- like "It doesn't seem to work" or the like.
				print ("CIAOCIAO")
				s.actions = {
					action.walkto { id=1, actor="player", obj = obj },
					action.turn { id=2, actor="player", dir = obj.face }
					--[1] = { type="walk", actor="player", pos = obj.walk_to},
					--[2] = { type="turn", actor="player", dir = obj.face, after={1}}
				}			
				local b = defaultActions[variables._actionInfo.verb.code]
				if (b ~= nil) then		
					s:push { script = b(), at = "end" }
				end
				--s:dump()
            end
        else
            -- run specific action
            -- see if obj1 has an action with obj2
            print ("found custom")
			s.actions = {
				action.walkto { id=1, actor="player", obj = obj },
				action.turn { id=2, actor="player", dir = obj.face }
			}		
			--s:push { script = createWalkToAction {objectId = variables._actionInfo.obj1}, at = "end" }
			s:push { script = a(), at = "end" }
        end
    else
        -- action with two objects
        -- see if there are any two object actions like verb obj1 ...
        --if (variables._actionInfo.verb.code == "use") then
        --    s = useActionHandler()
        --elseif (variables._actionInfo.verb.code == "give") then
		--	s = giveActionHandler()
		--end
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
	--s:dump()
	print ("CIAONE")
    monkey.play(s)
	print ("CIAO")
    variables._actionInfo:reset()
	print ("CIOCOCO")
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
			print ("Size of children = " .. tostring(#root.children))
			m2:cleartext()
			for k, v in ipairs(root.children) do
                local node = dialogue.nodes[v]
                if (node.active == true) then
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
			[1] = { type="callfunc", func= function() 
				local m = monkey.getEntity("mainui")
				local m1 = monkey.getEntity("main")
				local m2 = monkey.getEntity("dialogueui")
				m2:cleartext()
				
				m2:setactive(false)
				if (not m.isnil) then
					m:setactive(true)	
				end
				if (not m1.isnil) then
					m1:enablecontrols(true)			
				end
				if (dialogue.close ~= nil) then
					dialogue.close()
				end

			end},
		}

	else
        --local dialogue = info.data.dialogue

        s1 = start_dialogue {dialogue = info.data.dialogue, root = dialogueNode } 
        -- s1.actions = {
        --     [1] = { type="callfunc", func = function ()
        --         -- body
        --         local m2 = monkey.getEntity("dialogueui")
        --         for k, v in ipairs(dialogueNode.children) do
        --             m2:addtext { text=dialogue[v].text, dialogue_node = dialogue[v], dialogue = dialogue }
        --         end
        --     end}s
        -- }
	end
    if (s == nil) then
        s = s1
    else
        s:push { script = s1, at = "end" }
    end
	
	monkey.play(s)
end







