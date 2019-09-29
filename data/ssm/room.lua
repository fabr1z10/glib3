local roomInfo = {
	worldWidth = 224,
	worldHeight = 16,
	startPos = {0, 0},
	collisionSize = 80,
	g = -10
}

local initscripts = {}

room = getBaseRoom(roomInfo)
local mainScene = room.scene[1].children[3].children

