folder_name ="sprites"  
sprites = {}
models={}
print ("package path =  " .. package.path)  
print ("Loading all " .. folder_name .. " ...")
s = "find " .. _path .. folder_name .. "/*.lua | cut -c " .. tostring(string.len(_path)+1) .. "- | sed 's/.\\{4\\}$//'"
local p = io.popen(s)
for line in p:lines() do
	print(" " .. line)
    require(line)
end