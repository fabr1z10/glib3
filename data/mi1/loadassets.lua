folder_name ="sprites2"  
spritesheets = {}
models={}
models2={}
print ("package path =  " .. package.path)  
print ("Loading all " .. folder_name .. " ...")
-- read sheets
s = "find " .. _path .. folder_name .. "/*s.lua | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
local p = io.popen(s)
for line in p:lines() do
	print(" " .. line)
    require(line)
end
s = "find " .. _path .. folder_name .. "/*d.lua | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
local p = io.popen(s)
for line in p:lines() do
	print(" " .. line)
    require(line)
end
