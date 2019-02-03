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

-- load all files in a folder
function load_all(folder_name)
    print ("Loading all files in " .. folder_name .. " ...")
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