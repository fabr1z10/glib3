from lib_py.entity import Entity, Sprite
from lib_py.components import Gfx, Collider, TiledGfx, Info, SmartCollider, Controller2D, Dynamics2D, StateMachine, SimpleState
from lib_py.platformer.components import FoeWalk
from lib_py.script import Script
from lib_py.actions import Move, MoveAccelerated, RemoveEntity, CallFunc, SetState
import lib_py.shape as sh
import smb_py.vars as vars
import smb_py.tiles as tiles
import example

def m1(x: float, y: float):
    a = mushroom(x, y)
    main = example.get('main')
    id = main.add(a)
    s = Script()
    s.addAction(Move(id =id, speed=10, by=[0, 16]))
    s.addAction(SetState (id = id, state='walk'))
    example.play(s) 

def mushroom(x: float, y: float):
    a = Sprite(model='mushroom', pos = [x*vars.tileSize, y*vars.tileSize, -0.1])
    a.addComponent (SmartCollider(
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.mushroom))
    a.addComponent (Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    a.addComponent (Dynamics2D(gravity= vars.gravity))
    stateMachine = StateMachine (initialState='idle')
    stateMachine.states.append (SimpleState (id='idle', anim = 'walk'))
    stateMachine.states.append (FoeWalk(id='walk', anim='walk', speed=30, acceleration=0, flipHorizontal=False, flipWhenPlatformEnds=False, left=1))
    a.addComponent (stateMachine)
    return a

def m2(x: float, y: float):
    print ('x='+ str(x))
    def score():
        m3(x, y+1)
    a = Sprite ('flyingcoin', pos=[x * vars.tileSize, (y+1)*vars.tileSize, 0])
    main = example.get('main')
    id = main.add(a)
    s = Script()
    s.addAction(MoveAccelerated(v0 = [0, 100], a = [0, -100], yStop = (y*vars.tileSize) +16, id = id))
    s.addAction(RemoveEntity(id=id))
    s.addAction(CallFunc(f = score))
    example.play(s) 

def m3(x: float, y: float):
    a = Sprite ('score100', pos=[x * vars.tileSize, (y+1)*vars.tileSize, 0])
    main = example.get('main')
    id = main.add(a)
    s = Script()
    s.addAction(Move(speed=100, by=[0, 64], id = id))
    s.addAction(RemoveEntity(id=id))
    example.play(s)

# creates a rectangular platform
def platform (props):
    def f(args):
        x = args[0]
        y = args[1]
        w = args[2]
        h = args[3]
        a = Entity()
        #print ('image = ' + props[1])
        a.addComponent (Gfx(image = props[1], repeat = [w, h]))
        a.addComponent (Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, 
            shape = sh.Rect(width = w * vars.tileSize, height = h * vars.tileSize)))
        a.pos = (x * vars.tileSize, y * vars.tileSize, 0)
        return a
    return f

def brick(props):
    def f(args):
        model = props[0]
        x = args[0]
        y = args[1]
        a = Sprite(model = model)
        a.addComponent (Collider (flag = vars.flags.platform, mask = 0, tag = 0, shape = sh.Rect(width=vars.tileSize, height=vars.tileSize)))
        a.pos = [x * vars.tileSize, y * vars.tileSize, 0]
        b = Entity()
        b.pos = [2, -0.5, 0]
        b.addComponent (Collider (
            flag=vars.flags.foe,
            mask=vars.flags.player,
            tag = vars.tags.brick_sensor,
            shape = sh.Rect(width = vars.tileSize-4, height = 1.0)
        ))
        a.add(b)
        return a    
    return f

def tilemap (props):
    def f(args):
        shape = None                
        tm = getattr(tiles, props[1])
        x = args[0]
        y = args[1]
        z = args[2] if len(args)>2 else 0
        width = tm[0]
        height = tm[1]
        collision = tm[2]
        data = tm[3]
        if collision:
            shape = sh.Rect(width = width * vars.tileSize, height = height * vars.tileSize) 
        e = Entity(pos = [x*vars.tileSize, y*vars.tileSize, z])
        e.addComponent (TiledGfx(
            tilesheet = 'gfx/smb1.png', 
            sheetSize = [16, 16],
            tileData = data, 
            width = width, 
            height = height,
            size = vars.tileSize))
        if collision:
            e.addComponent (Collider (
                flag=vars.flags.platform,
                mask = 1,
                tag = 1,
                shape = shape
            ))
        return e
    return f     


def _brick(x, y, model, hits, callback):
    a = Sprite(model = model, pos= [x * vars.tileSize, y * vars.tileSize, 0])
    a.addComponent (Collider (flag = vars.flags.platform, mask = 0, tag = 0, 
        shape = sh.Rect(width=vars.tileSize, height=vars.tileSize)))
    a.addComponent (Info ( 
        hitsLeft = hits,
        callback = callback))
    b = Entity()
    b.pos = [2, -0.5, 0]
    b.addComponent (Collider (
        flag = vars.flags.foe,
        mask = vars.flags.player,
        tag = vars.tags.bonus_brick_sensor,
        shape = sh.Rect(width = vars.tileSize - 4, height = 1.0)
    ))
    a.add(b)
    return a

def mushroombrick(props):
    def f(args):
        return _brick(args[0], args[1], 'bonusbrick', 1, m1)
    return f

def coinbrick(props):
    def f(args):
        return _brick(args[0], args[1], 'bonusbrick', 1, m2)
    return f