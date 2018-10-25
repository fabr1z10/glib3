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
	s.actions = {
		[1] = { type="move", actor=tag, to ={arg.pos2[1]*16, arg.pos2[2]*16}, speed=arg.speed},
		[2] = { type="move", actor=tag, to ={arg.pos[1]*16, arg.pos[2]*16}, speed=arg.speed, after={1}},
	}
	s.loop = 1
	table.insert(arg.initscripts, s)
	

	print ("SOZZO")
	return
	{
		tag = tag,
		pos = {arg.pos[1]*16, arg.pos[2]*16, -1},
		components = {
			{ type="gfx", img="gfx/smb1.png", width=arg.width, height=1, size=16, tiledata=tiledata, sheetsize={16, 16}},
			{ type="collider", 
				shape = {type="line", A = {0,8}, B = {16*arg.width, 8}},
				--shape={type="rect", width=16*arg.width, height = 8}, 
				tag=10, flag = 32 },
			{ type="platform"}
		},
		children = {
			{
				pos = { 0, 8, 0},
				components = {
					{ type="collider", shape = sh, tag = movingPlatformTag, flag = 4 },
					{ type="gfx", shape = sh, color = {255,0,0,255}},
				}
			}
		}
	}
end