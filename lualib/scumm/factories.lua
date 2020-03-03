-- Basic room 

require ('scumm/factories/room')
require ('scumm/factories/room_ui')
require ('scumm/factories/room_map')
require ('scumm/factories/room_dialogue')

--require ('scumm/factories/room_base')
--require ('scumm/factories/room_mp')



function scumm.func.toggle_pause () 
	scumm.state.game_paused = not scumm.state.game_paused;
	print ("toggling pause, now " .. tostring(scumm.state.game_paused))
	-- local p = monkey.getEntity("main")
	-- local ui = monkey.getEntity("ui")
	-- monkey.enablescriptengine(not engine.state.scumm.game_paused)

	-- p:enableupdate(not engine.state.scumm.game_paused)
	-- ui:enableupdate(not engine.state.scumm.game_paused)
 --   	--p:setactive(not engine.state.scumm.game_paused)
 --   	--ui:setactive(not engine.state.scumm.game_paused)
 --   	engine.state.scumm.game_paused = not engine.state.scumm.game_paused
end

-- this func gets the id of the template


function scumm.factory.object (args)
	if scumm.utils.has_player(args.id) then
		return {}
	end

	glib.assert(args.id, 'required item <id>')
	print ('    adding item: ' .. args.id)
	local item = engine.items[args.id]

	if not item then error("Hey! Don't know item: " .. args.id, 1) end

	local f = scumm.ifac.fmap[item.type]
	if not f then error("Unknown factory func for item: " .. args.id,1) end

	--local tag = nil
	--i-f item.tag then 
	--	tag = args.id
	--end

	-- 1. if args.params.tag is specified nothing to do
	-- 2. if not specified, and item 
	local params = args.params or {}
	if not params.tag and item.tag then
		params.tag = type(item.tag) == 'string' and item.tag or args.id
	end

	params._id = args.id
	return f { item = item, args = params }


end

function scumm.factory.basic_room (args) 
	
	local p = scumm.factory.room_base(args)

	local start_pos = nil
	if args.startTable then		
		local proom = (engine.state.previousRoom == '') and args.defaultroom or engine.state.previousRoom
		start_pos = args.startTable[proom]
		if not start_pos then error ("Unable to find start position for " .. proom, 1) end
	end

	if start_pos then
		print ("adding player to " .. start_pos.walkarea)
		p:add(start_pos.walkarea, {
			scumm.factory.object {
				id = args.playerid,
				params = {
					tag = 'player',
					pos = start_pos.pos,
					dir = start_pos.dir,
					follow = true
				}
			}
		})
	end

	return p
end

require ('scumm/factories/buttons')