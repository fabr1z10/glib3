function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function curryg(f, arg) 
	return function(name) 
		arg.scriptname = name
		return f(arg)
	end
end

function curry2(f, arg)
    return function(x)
       f(arg, x) 
    end 
end

require ("script")
require ("factoryactions")
-- require ("rooms/scummbar/actions")
-- require ("rooms/kitchen/actions")
-- require ("rooms/voodoolady/actions")
-- require ("rooms/village2/actions")
-- require ("rooms/shop/actions")
-- require ("rooms/meleemap/actions")
-- require ("rooms/circus/actions")
print ("The path is : " .. _path)
print ("Loading items ...")
local p = io.popen("find " .. _path .. " -path */items.lua | cut -c" .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"):lines()
for line in p do
	print("loading " .. line)
	require(line)
end
print ("Loading actions ...")

local p = io.popen("find " .. _path .. " -path */actions.lua | cut -c" .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"):lines()
for line in p do
	print("loading " .. line)
	require(line)
end
--require ("items")
require ("factoryobjects")
require ("uifuncs")
require("dialogues")


function curry2_1(f, arg1, arg2)
    return function(x)
       f(arg1, arg2, x) 
    end 
end




function createWalkToPosition (position, script, f)
    table.insert (script.actions,
    {
        id = #script.actions,
		    walkarea = "walkarea",
		    actor = "player",
        type = "walkto",
		    pos = position
	  }

  )
end

require ("characters")



