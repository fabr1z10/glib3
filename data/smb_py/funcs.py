from lib_py.entity import Entity, Sprite
import lib_py.components as compo
import lib_py.shape as sh
import lib_py.actions as act
from lib_py.script import Script
import smb_py.vars as vars
import example

def upgradePlayer():
    vars.state += 1
    if vars.state >= len(vars.stateInfo):
        vars.state = 0
    # update model
    pl = example.get('player')
    pl.setModel(vars.stateInfo[vars.state], 'idle')


def makePiece(pos, vx, vy, model, parent : example.Wrap1):
    a = Sprite(model = model, pos = pos)
    id = parent.add(a)
    s = Script()
    s.addAction (act.MoveAccelerated (id = id, v0 = [vx, vy], a = [0, 0.5*vars.gravity], yStop=0))
    s.addAction (act.RemoveEntity (id = id))
    #		type = action.remove_object, args = { id = id1}
    example.play(s)

def brickResponse (player : example.Wrap1, brick : example.Wrap1, x, y):
    b = brick.parent()
    brick_id = b.id()
    if vars.state == 0:
        s = Script()
        ystop = b.y()
        s.addAction (act.MoveAccelerated (v0 = [0, 50], a = [0, 0.5 * vars.gravity], yStop = ystop, id = brick_id))
        example.play(s)
    else:
        print ('removing ' + str(brick_id))
        example.remove(brick_id)
        m = example.get('main')
        makePiece(pos = [b.x(), b.y(), 1], vx = 60, vy = 180, model ='brickpiece', parent=m)
        makePiece(pos = [b.x(), b.y(), 1], vx = -60, vy = 180, model ='brickpiece', parent=m)
        makePiece(pos = [b.x(), b.y(), 1], vx = 120, vy = 120, model ='brickpiece', parent=m)
        makePiece(pos = [b.x(), b.y(), 1], vx = -120, vy = 120, model ='brickpiece', parent=m)

def bonusBrickResponse (player: example.Wrap1, brick: example.Wrap1, x, y):
    b = brick.parent()
    info = b.getInfo()
    hitsLeft = info['hitsLeft']
    brick_id = b.id()
    if hitsLeft > 0:
        info['hitsLeft'] -= 1
        s = Script()
        ystop = b.y()
        s.addAction (act.MoveAccelerated (v0 = [0, 50], a = [0, 0.5 * vars.gravity], yStop = ystop, id = brick_id))
        if hitsLeft == 1:
           s.addAction (act.Animate (anim='taken', id=brick_id)) 
        # release the bonus
        def p():
            info['callback'](b.x()/ vars.tileSize + 0.5, b.y() / vars.tileSize)
        s.addAction (act.CallFunc (f = p))
        example.play(s)

def mushroomResponse (player: example.Wrap1, mushroom: example.Wrap1, x, y):
    example.remove(mushroom.id())
    upgradePlayer()

# factory.bonus_brick.response = function(p1, p2)

# 	local brick = p2:parent()
# 	local brick_info = brick:getinfo()
# 	if brick_info.hitsleft > 0 then
# 		brick_info.hitsleft = brick_info.hitsleft - 1
# 		local actions = {
# 			{ 
# 				type = action.moveaccel, 
# 				args = { 
# 					id = brick.id, 
# 					initial_velocity = {0, 50}, 
# 					acceleration = {0, 0.5*variables.gravity}, 
# 					ystop = brick_info.y
# 				}
# 			}
# 		}
# 		if (brick_info.hitsleft == 0) then
# 			table.insert (actions, {
# 				type = action.animate,
# 				args = { id = brick.id, anim = "taken" }
# 			})
# 		end
		

# 		table.insert (actions, {
# 			type = action.callfunc,
# 			args = {
# 				func = function()
# 					local pos = {brick.x+0.5*engine.tilesize, brick.y, 1}
# 					local factory = glib.get(brick_info.factory)
# 					local args = glib.get(brick_info.args)

# 					local o = factory.create(args, pos)
# 					print("Mio cuggggg")
# 					local m1 = monkey.getEntity("main")
# 					local id = monkey.addEntity (o, m1)

# 					-- hey, do I have to perform a script on this?
# 					if (factory.script ~= nil) then
# 						print ("FATTTTONE")
# 						local actions = factory.script(id, pos)
# 						local s = script.make(actions)
# 						monkey.play(s)
# 					end


# 				end
				
# 			}
# 		})

# 		-- release the bonus
# 		local s = script.make(actions)
# 		monkey.play(s)
# 	end	
# end
