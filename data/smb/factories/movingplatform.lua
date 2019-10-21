factory.movingplatform = {}

factory.movingplatform.create = function(arg)
	
	local tag = glib.next_tag()
	local sh = {type="rect", width=16*arg.width, height = 0.5}
	local tiledata = {}
	for i = 1,arg.width do
		table.insert(tiledata, arg.tx)
		table.insert(tiledata, arg.ty)
	end
	local pos = arg.path[1].pos
	table.insert(arg.initscripts, function() 
		print ("START!!!") 

		local actions = {}
		local id=1
		for _, v in ipairs(arg.path) do
			print ("moving to " .. tostring(v.pos[1]))
			table.insert(actions, { type = action.move, ref=id, args = { tag = tag, speed =v.speed or arg.speed, to = {v.pos[1], v.pos[2]}}})
			id= id+1
		end
		local s = script.make(actions)
		s.loop = 1
		monkey.play(s)	
	end)

	-- local s = script:new()
	-- local i = 1
	-- for k, v in ipairs(arg.path) do
	-- 	local immediate = nil
	-- 	if (v.speed == nil) then
	-- 		immediate = true
	-- 	end
	-- 	local speed = v.speed
	--  	local after = nil
	-- 	if (i > 1) then
	-- 		after = {i-1}
	-- 	end
	-- 	if (immediate == true) then
	-- 		table.insert (s.actions, {type="dropcharacters", actor=tag, pos = {v.pos[1], v.pos[2]}, after=after})
	-- 	else
	-- 		table.insert (s.actions, {type="dropcharacters", actor=tag, pos = {v.pos[1], v.pos[2]}, after=after})
	-- 	end
	-- 	i=i+1
	-- end
	-- s.loop = 1
	-- table.insert(arg.initscripts, s)
	
	return
	{
		tag = tag,
		pos = {pos[1], pos[2], -1},
		components = {
			{ type="gfx", img=arg.img, width=arg.width, height=1, size=16, tiledata=tiledata, sheetsize={16, 16}},
			{ type="collider", 
				shape = {type="line", A = {0,8}, B = {16*arg.width, 8}},
				--shape={type="rect", width=16*arg.width, height = 8}, 
				tag=10, flag = 32, mask = 0 },
			{ type="platform"}
		},
		children = {
			{
				pos = { 0, 8, 0},
				components = {
					{ type="collider", shape = sh, tag = variables.collision.tags.moving_platform, flag =variables.collision.flags.foe, mask = variables.collision.flags.foe| variables.collision.flags.player },
					{ type="gfx", shape = sh, color = {255,0,0,255}},
				}
			}
		}
	}
end