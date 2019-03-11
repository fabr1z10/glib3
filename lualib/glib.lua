print ("Loading <glib> lib")

glib = {}

function glib.assert(a, b, c)
	if (a == nil) then 
		error("Required argument: " ..b, c or 2) 
	end
end

function glib.assert_both (a, b, c) 
	if (a == nil and b == nil) then
		error ("Required both argument: " .. c, 2)
	end
end

function glib.assert_either (a, b, c) 
	if (a == nil or b == nil) then
		error ("Required both argument: " .. c, 2)
	end
end

-- checks whether the object is an array
function glib.isarray(t) 
    return (type(t)=="table" and t[1] ~= nil)
end

-- load all lua filesi in the given folder
function glib.load_folder(folder_name)
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