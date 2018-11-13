items.finalgate = {}

-- args:
-- mandatory:s
-- x, y     initial position
-- dir      walking direction (1 = right, -1 = left)
items.finalgate.create = function(args)
	local pos = args.pos
	local t = nextTag()	
	--local s = {type="rect", width=16, height=16, offset={0,0}}
	return {
		tag = t,
		pos = {pos[1], pos[2], 0 },
		children = {
			{ pos = {32, 0, 0.1}, components = { { type="gfx", img="gfx/sprites.png", width=1, height=9, size=16, tiledata={21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,0}, sheetsize={32, 32}}  }},
			{ pos = {0, 0, -0.1}, components = { { type="gfx", img="gfx/sprites.png", width=1, height=9, size=16, tiledata={21,4,21,4,21,4,21,4,21,4,21,4,21,4,21,3,21,2}, sheetsize={32, 32}}  }}
		}
	}
end

