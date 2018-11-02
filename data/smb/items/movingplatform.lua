items.movingplatform = {}

items.movingplatform.create = function(arg)
	
	local tag = nextTag()
	local sh = {type="rect", width=16*arg.width, height = 0.5}
	local tiledata = {}
	for i = 1,arg.width do
		table.insert(tiledata, arg.tx)
		table.insert(tiledata, arg.ty)
	end

	local s = script:new()
	local i = 1
	for k, v in ipairs(arg.path) do
		local immediate = nil
		if (v.speed == nil) then
			immediate = true
		end
		local speed = v.speed
	 	local after = nil
		if (i > 1) then
			after = {i-1}
		end
		if (immediate == true) then
			table.insert (s.actions, {type="dropcharacters", actor=tag, pos = {v.pos[1], v.pos[2]}, after=after})
		else
			table.insert(s.actions, { type = "move", actor=tag, to = {v.pos[1], v.pos[2]}, speed = v.speed, immediate = immediate, after = after })
		end
		i=i+1
	end
	s.loop = 1
	table.insert(arg.initscripts, s)
	
	return
	{
		tag = tag,
		pos = {arg.pos[1], arg.pos[2], -1},
		components = {
			{ type="gfx", img="gfx/smb1.png", width=arg.width, height=1, size=16, tiledata=tiledata, sheetsize={16, 16}},
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
					{ type="collider", shape = sh, tag = movingPlatformTag, flag = collisionFlags.enemy, mask = collisionFlags.player | collisionFlags.enemy  },
					{ type="gfx", shape = sh, color = {255,0,0,255}},
				}
			}
		}
	}
end