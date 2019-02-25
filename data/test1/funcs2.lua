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




