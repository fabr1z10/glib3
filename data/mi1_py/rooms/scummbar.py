import lib_py.engine as engine
import lib_py.scumm.room as room
import lib_py.scumm.actions as act
import lib_py.actions as actions
import lib_py.scumm.entity as se
import lib_py.shape as sh
from lib_py.script import Script
from lib_py.scumm.scumm import State
import lib_py.scumm.scripts as scr
import mi1_py.variables as var
import example    



def animate():
    run_background_script('scummbar.mancomb', 1, 4, 0, 0)
    run_background_script('scummbar.pirate1', 1, 4, 1, 4)
    run_background_script('scummbar.pirate2', 1, 4, 1, 4)
    run_background_script("scummbar.pirate3", 1, 4, 0.5, 0.5)
    run_background_script("scummbar.pirate4", 1, 4, 0, 0)
    run_background_script("scummbar.pirate5", 1, 4, 1, 2)
    run_background_script("scummbar.pirate7", 1, 4, 1, 2)
    run_background_script("scummbar.pirate8", 1, 4, 0, 0)
    run_background_script("scummbar.pirate9", 1, 4, 0, 0)
    run_background_script("scummbar.estevan", 1, 4, 0, 0)
    run_background_script("scummbar.loom", 1, 4, 0, 0)

def run_background_script(actor, a, b, c, d):
    s = Script(loop = 0)
    s.addAction (actions.DelayRandom(min=a, max=b))
    s.addAction (actions.Animate(tag=actor, anim='idle_2', fwd = True, sync = True))
    s.addAction (actions.DelayRandom(min=c, max=d))
    s.addAction (actions.Animate(tag=actor, anim='idle_2', fwd = False, sync = True))
    s.addAction (actions.Animate(tag=actor, anim='idle_1', fwd = True, sync = True))
    example.play(s)

def makeCook(pos, dir):
    return se.Character (
        model = 'cook', 
        speed = 100, 
        dir = dir, 
        state='idle', 
        text_color = [85, 85, 255, 255], 
        text_offset = [0,60], 
        tag = 'cook',
        pos = pos)


def cook():
    def setCookInKitchen():
        var.cook_in_kitchen = True

	# if coming from kitchen, cook should be added to the scene!
    cook_pos = [125, 17]
    if engine.previous_room == 'kitchen':
        var.cook_in_kitchen = False
        s = Script()
        # make the cook
        cook = makeCook (cook_pos, 'n')
        s.addAction (actions.AddEntity (cook, 'walkarea'))
        s.addAction (actions.Delay (sec = 5))
        s.addAction (act.Walk (tag = 'cook', pos = var.scummbar_kitchen_door_pos))
        s.addAction (actions.RemoveEntity(tag = 'cook'))
        s.addAction (actions.CallFunc(f = setCookInKitchen))
        example.play(s)
    else:
        var.cook_in_kitchen = True
        cook = makeCook (var.scummbar_kitchen_door_pos, 'w')
        s = Script()
        s.addAction (action = actions.Delay (sec=10), id = 0)
        s.addAction (actions.RunScript (s = scr.openDoor(doorId='scummbar.door.kitchen', var='scummbar_kitchen')() ))
        s.addAction (actions.AddEntity (cook, 'walkarea'))
        s.addAction (act.Walk (tag = 'cook', pos = cook_pos))
        s.addAction (act.Turn (tag = 'cook', dir= 'n'))
        s.addAction (actions.Delay (sec=5))
        s.addAction (act.Walk (tag = 'cook', pos = var.scummbar_kitchen_door_pos))
        s.addAction (actions.RemoveEntity(tag = 'cook'))
        s.addAction (actions.RunScript (s = scr.closeDoor(doorId='scummbar.door.kitchen', var='scummbar_kitchen')() ))
        s.loop = 0
        example.play(s)
#     local a2 = {
# 		{ ref = 1, type = action.delay, args = {sec = 10} },
# 	 	mi.script.open_door { door='scummbar.door.kitchen', value=true },
# 	 	{ type = action.set_variable, args = { var = 'cook_in_kitchen', value = false }},
# 		{ type = action.create_object, args = { 
# 			factory = scumm.factory.object, 
# 			args = { id="scummbar.cook", params = { pos = mi.rooms.scummbar.door_kitchen, dir='w' } }, 
# 			parent = "scummbar.walkarea", 				
# 		}},
# 		{ type = scumm.action.walkto, args = { tag = 'scummbar.cook', obj = "scummbar.mancomb" }}, --obj = items["scummbar.mancomb"]},		
# 		{ type = scumm.action.turn, args = { tag = 'scummbar.cook', dir='north'}},
# 	 	{ type = action.delay, args = {sec = 5 } },
# 	 	{ type = scumm.action.walkto, args = { tag ="scummbar.cook", obj = 'scummbar.door.kitchen'}},
# 	 	{ type = action.remove_object, args = { tag = 'scummbar.cook'}},
# 	 	mi.script.open_door { door='scummbar.door.kitchen', value=false },
# 		{ type = action.set_variable, args = {var = 'cook_in_kitchen', value = true }},
# 	 }


# 	 	a1 = {
# 	 		{ type = action.create_object, args = { 
# 	 			factory = scumm.factory.object, 
# 	 			args = { id = 'scummbar.cook', params = { pos = {mancombPos[1], mancombPos[2], 0}, dir='n' }},
# 	 			parent = 'scummbar.walkarea'
# 	 		}},
# 	 		{ type = action.delay, args = {sec = 5 }},
# 	 		{ type = scumm.action.walkto, args = { tag ='scummbar.cook', obj = 'scummbar.door.kitchen'}},
# 	 		{ type = action.remove_object, args = { tag ="scummbar.cook" }},
# 	 		mi.script.open_door { door='scummbar.door.kitchen', value = false },
# 	 		{ type = action.set_variable, args = {var = 'cook_in_kitchen', value = true }}
# 	 	}
# 	else
# 		variables.cook_in_kitchen = true
# 	end
# 	-- 	variables[items["scummbar.door_kitchen"].variable] = 0
# 	-- end
#     local a2 = {
# 		{ ref = 1, type = action.delay, args = {sec = 10} },
# 	 	mi.script.open_door { door='scummbar.door.kitchen', value=true },
# 	 	{ type = action.set_variable, args = { var = 'cook_in_kitchen', value = false }},
# 		{ type = action.create_object, args = { 
# 			factory = scumm.factory.object, 
# 			args = { id="scummbar.cook", params = { pos = mi.rooms.scummbar.door_kitchen, dir='w' } }, 
# 			parent = "scummbar.walkarea", 				
# 		}},
# 		{ type = scumm.action.walkto, args = { tag = 'scummbar.cook', obj = "scummbar.mancomb" }}, --obj = items["scummbar.mancomb"]},		
# 		{ type = scumm.action.turn, args = { tag = 'scummbar.cook', dir='north'}},
# 	 	{ type = action.delay, args = {sec = 5 } },
# 	 	{ type = scumm.action.walkto, args = { tag ="scummbar.cook", obj = 'scummbar.door.kitchen'}},
# 	 	{ type = action.remove_object, args = { tag = 'scummbar.cook'}},
# 	 	mi.script.open_door { door='scummbar.door.kitchen', value=false },
# 		{ type = action.set_variable, args = {var = 'cook_in_kitchen', value = true }},
# 	 }
	
# 	local actions = {}
# 	table.insert(actions, a1)
# 	table.insert(actions, a2)
# 	--local s = ms2(actions, 1)

# 	local s = script.make(actions, 1)
# 	s.name = "_cook"
# 	monkey.play(s)
# end

def builder():
    r =  room.RoomUI(id='scummbar', width = 640, height = 144)
    r.add (se.BackgroundItem(image='gfx/scummbar_1.png', pos = [0, 0, -3]), 'main')
    r.add (se.BackgroundItem(image='gfx/scummbar_2.png', pos = [374, 20, 0.95]), 'main')
    r.add (se.BackgroundItem(image='gfx/scummbar_3.png', pos = [157, 0, 0.99]), 'main')
    r.add (se.BackgroundItem(image='gfx/scummbar_4.png', pos = [20, 0, 0.99]), 'main')

    r.add (se.WalkArea (tag='walkarea', shape = sh.Polygon(
        outline = [32, 16, 70, 24, 128, 19, 251, 18, 311, 10, 321, 10, 345, 32, 467, 41,
 			492, 50, 514, 40, 565, 40, 580, 35, 629, 6, 626, 0, 256, 0, 200, 16, 149, 0, 90, 0, 85, 10],
        holes = [ [374, 28, 505, 28, 505, 6, 374, 6]]),
        depth = sh.LinY(y0=0,z0=1,y1=144,z1=0)), 'main')
    
    # doors
    r.add (se.Sprite (item='scummbar.door.out', anim = var.doors.village_scummbar, model='door_scummbar_village', pos = [32, 24, 0]), 'main')	
    r.add (se.Sprite (item='scummbar.door.kitchen', anim = var.doors.scummbar_kitchen, model='door_scummbar_kitchen', pos = [591, 9, 0]), 'main')	
    
    # other
    r.add (se.Sprite (model = 'scummbar.fireplace', item = 'scummbar.fireplace', pos = [509, 44,1]), 'walkarea')


    # pirates
    r.add (se.Sprite (item = 'scummbar.mancomb', model = 'scummbar.mancomb', pos = [89, 24, -1]), 'main')
    r.add (se.Sprite (item = 'scummbar.estevan', model = 'scummbar.estevan', pos = [164, 21, 1]), 'main')
    r.add (se.Sprite (item = 'scummbar.loom', model = 'scummbar.loom', pos = [260, 17, 1]), 'walkarea')
    r.add (se.Sprite (item = 'scummbar.pirate1', model = 'scummbar.pirate1', pos = [138, 38, -1]), 'main')
    r.add (se.Sprite (model = 'scummbar.pirate2', pos = [124,20,-1], tag = 'scummbar.pirate2'), 'main')
    r.add (se.Sprite (model = 'scummbar.pirate3', pos = [30,0,-1], tag = 'scummbar.pirate3'), 'walkarea')
    r.add (se.Sprite (item = 'scummbar.pirate4', model = 'scummbar.pirate4', pos = [0, 0, -1]), 'walkarea')
    r.add (se.Sprite (model = 'scummbar.pirate5', pos = [200,18,1], tag = 'scummbar.pirate5'), 'main')
    r.add (se.Sprite (model = 'scummbar.pirate6', pos = [160,0,1], tag = 'scummbar.pirate6'), 'main')
    r.add (se.Sprite (model = 'scummbar.pirate7', pos = [255,38,1], tag = 'scummbar.pirate7'), 'walkarea')
    r.add (se.Sprite (model = 'scummbar.pirate8', pos = [215,44,1], tag = 'scummbar.pirate8'), 'walkarea')
    r.add (se.Sprite (model = 'scummbar.pirate9', pos = [278,40,1], tag = 'scummbar.pirate9'), 'walkarea')
    r.add (se.Character (model='ilp1', speed = 100, dir = 'e', 
        state='idle', text_color=[85, 85, 255, 255], text_offset=[0,60], pos = [376, 11, 0.95]), 'walkarea')
    r.add (se.Character (model='ilp2', speed = 100, dir = 'e', 
        state='idle', text_color=[255, 255, 85, 255], text_offset=[0,60], pos = [413,11,0.95]), 'walkarea')
    r.add (se.Character (model='ilp3', speed = 100, dir = 'e', 
        state='idle', text_color=[255, 85, 255, 255], text_offset=[0,60], pos = [444,18,0.95]), 'walkarea')
    r.add (se.Sprite (item = 'scummbar.important_looking_pirates', pos=[370,30,0]), 'main')

    r.init.append (animate)
    r.init.append (cook)
    r.addDynamicItems()
    return r

engine.addRoom (id = 'scummbar', f=builder)
