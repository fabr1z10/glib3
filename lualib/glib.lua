glib = {}

engine.state = {
    room = engine.start_room,
    previousRoom = "",
}

function glib.assert(a, b, c)
	if (a == nil) then 
		error("Required argument: " ..b, c or 2) 
	end
end

function glib.assert_both (a, b, c) 
	if (a == nil or b == nil) then
		error ("Required both argument: " .. c, 2)
	end
end

function glib.assert_either (a, b, c) 
    if (a == nil and b == nil) then
		error ("Required both argument: " .. c, 2)
	end
end

-- checks whether the object is an array
function glib.isarray(t) 
    return (type(t)=="table" and t[1] ~= nil)
end

-- load all lua filesi in the given folder
function glib.load_folder(folder_name)
   -- print ("Loading all files in " .. folder_name .. " ...")
    --local s = "find " .. _path .. " -path " .. folder_name .. "/*.lua | cut -c" .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    s = "find " .. _path .. folder_name .. "/*.lua | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    print (s)
    local p = io.popen(s)
    for line in p:lines() do
        --print(" " .. line)
        require(line)
    end
end

function glib.load_all(name)
    io.write ("loading " .. name .. " ...")
   -- print ("Loading all files in " .. folder_name .. " ...")
    --local s = "find " .. _path .. " -path " .. folder_name .. "/*.lua | cut -c" .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    s = "find " .. _path .. "rooms/ -name \"" .. name .. ".lua\" | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
    --print (s)
    local p = io.popen(s)
    for line in p:lines() do
        print("LOOOAD " .. line)
        require(line)
    end
    io.write ("done! \n")

end


-- if ref is a function, call the funtion otherwise gets the value
function glib.get(ref)
	if (type(ref)=="function") then
		return ref()
	else
		return ref
	end
end

function glib.curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function glib.curry2(f, arg)
    return function(x)
       f(arg, x) 
    end 
end

function glib.depth(d1, z1, d2, z2, z)
    local a = (d1-d2)/(z1-z2)
    local b = d1-a*z1
    return a*z+b
end

function glib.tablelength(T)
  local count = 0
  for _ in pairs(T) do count = count + 1 end
  return count
end

function glib.basic_model(sheet, anim)
    return {
        sheet = sheet,
        type = "sprite",
        ppu=1,
        animations = {
            { name = "default", frames = { { duration = engine.dt, quads = {{ id = anim }}}}},
        }
    }


end
