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

-- basic say script
function say(args) 
	-- requires actor, lines
	local s = script:new()
	s.actions = {
		[1] = { type="say", actor=args.actor.tag, lines = args.lines, offset = args.actor.text_offset, color = args.actor.text_color }
	}
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
	print ("ASSO")	
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
				s.actions = {
					[1] = { type="walk", actor="player", pos = obj.walk_to},
					[2] = { type="turn", actor="player", dir = obj.face, after={1}}
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
				[1] = { type="walk", actor="player", pos = obj.walk_to },
				[2] = { type="turn", actor="player", dir = obj.face, after={1}}
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

function start_dialogue(dialogueId)
	local s = script:new()
	s.actions ={
		[1] = { type="callfunc", func = function()
			local m = monkey.getEntity("mainui")
			local m1 = monkey.getEntity("main")
			local m2 = monkey.getEntity("dialogueui")
			m:setactive(false)
			m1:enablecontrols(false)
			m2:setactive(true)
			local dialogue = dialogues[dialogueId]
			local root = dialogue[1]
			print ("Size of children = " .. tostring(#root.children))
			m2:cleartext()
			for k, v in ipairs(root.children) do
				m2:addtext { text=dialogue[v].text, dialogue_node = dialogue[v] }
			end
		end
		}
	}
	return s
end

function handleDialogueButton(entity)
	print ("VAFFFA " ..  tostring(entity.x))
	local m2 = monkey.getEntity("dialogueui")				
	m2:cleartext()
	
	local info = entity:getinfo()  
	local dialogueNode = info.data.node
	local s = nil
	if (dialogueNode.script ~= nil) then
		s = dialogueNode.script()
	end

	if (dialogueNode.children == nil) then
		-- return to game
		local s1 = script:new()
		s1.actions = {
			[1] = { type="callfunc", func= function() 
				local m = monkey.getEntity("mainui")
				local m1 = monkey.getEntity("main")
				local m2 = monkey.getEntity("dialogueui")
				m2:cleartext()
				m2:setactive(false)
				m:setactive(true)
				m1:enablecontrols(true)			
			end}
		}
		if (s == nil) then
			s = s1
		else
			s:push { script = s1, at = "end" }
		end
	else
	end
	monkey.play(s)
end
