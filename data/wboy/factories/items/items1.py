from lib_py.entity import Entity, Sprite
from lib_py.components import Gfx, TexAnim, ShapeGfxColor, Parallax, Collider, ScriptPlayer, Follow, KeyInput, StateCallback, TiledGfx, Info, SmartCollider, Controller2D, Dynamics2D, StateMachine, SimpleState, PolygonalMover, Platform, Fader, Attack, JumpAttack
from lib_py.platformer.components import FoeWalk, Jump, WalkSide
from lib_py.script import Script
from lib_py.actions import Move, MoveAccelerated, RemoveEntity, CallFunc, SetState
import lib_py.shape as sh
import smb_py.vars as vars
import smb_py.tiles as tiles
import smb_py.scripts as scripts
import example

def makePlayer(model: str, x: float, y: float):
    player = Sprite(model = model, pos = [x * vars.tileSize, y*vars.tileSize], tag='player')
    player.addComponent (SmartCollider(
        flag = vars.flags.player,
        mask = vars.flags.foe | vars.flags.foe_attack,
        tag = vars.tags.player))
    player.addComponent (Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    speed = 75
    player.addComponent (Dynamics2D(gravity= vars.gravity))
    stateMachine = StateMachine(initialState='walk')
    stateMachine.states.append (SimpleState (id='dead', anim='dead'))
    stateMachine.states.append (WalkSide(
        id = 'walk', 
        speed = 200, 
        acceleration = 0.05, 
        jumpSpeed = vars.jump_velocity, 
        keys = [
            [90, StateCallback(f=scripts.fire)],
            [264, StateCallback(f=scripts.enterPipe)],
        ],        
        flipHorizontal=True))
    stateMachine.states.append (Jump(id='jump', speed=200, acceleration=0.10, 
        keys = [
            [90, StateCallback(f=scripts.firej)],
        ], 
        flipHorizontal=True, animUp='jump', animDown='jump'))
    stateMachine.states.append (Attack(id='attack1', anim= 'fire'))
    stateMachine.states.append (JumpAttack(id='attack2', anim= 'fire', speed = 200, acceleration = 0.10, flipHorizontal = True))        
    stateMachine.states.append (FoeWalk(id='demo', anim='walk', speed = 75, 
        acceleration=0.05, flipHorizontal=True, flipWhenPlatformEnds = False, left=1))
    stateMachine.states.append (SimpleState (id='pipe', anim='idle'))
    stateMachine.states.append (SimpleState (id='slide', anim='slide'))
    player.addComponent (stateMachine)
    player.addComponent (KeyInput())    
    player.addComponent (Follow(relpos=[0,32,5]))
    return player

def m1(x: float, y: float):
    a = None
    if vars.state == 0:
        a = mushroom(x, y)
    else:
        a = flower (x, y)
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

def flower(x: float, y: float):
    a = Sprite(model='flower', pos = [x*vars.tileSize, y*vars.tileSize, -0.1])
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
    stateMachine.states.append (FoeWalk(id='walk', anim='walk', speed=0, acceleration=0, flipHorizontal=False, flipWhenPlatformEnds=False, left=1))
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

def line(props):
    def f(args):
        print ('xxx')
        x = args[0] * vars.tileSize
        y = args[1] * vars.tileSize
        Ax = args[2] * vars.tileSize
        Ay = args[3] * vars.tileSize
        Bx = args[4] * vars.tileSize
        By = args[5] * vars.tileSize
        minx = min(Ax, Bx)
        maxx = max(Ax, Bx)
        miny = min(Ay, By)
        maxy = max(Ay, By)
        a = Entity()
        print ('xxx')
        a.addComponent (Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, 
            shape = sh.Line(A=[Ax,Ay,0], B=[Bx,By,0])))
        a.addComponent (Info (bounds = [minx,miny,maxx,maxy]))
        a.pos = (x,y,0)
        return a
    return f



# creates a rectangular platform
def platform (props):
    def f(args):
        x = args[0]
        y = args[1]
        w = args[2]
        h = args[3]
        rx = args[4]
        ry = args[5]
        a = Entity()
        #print ('image = ' + props[1])
        if len(props) > 1:
            a.addComponent (Gfx(image = props[1], repeat = [rx, ry]))
        a.addComponent (Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, 
            shape = sh.Rect(width = w * vars.tileSize, height = h * vars.tileSize)))
        a.pos = (x * vars.tileSize, y * vars.tileSize, 0)
        return a
    return f

def sprite (props):
    def f(args):
        x = args[0]
        y = args[1]
        z = args[2] if len(args)>2 else 0
        a = Sprite(model=props[1], pos = [x * vars.tileSize, y * vars.tileSize, z])
        return a
    return f

def img(props):
    def f(args):
        x = args[0]
        y = args[1]
        z = args[2]        
        w = args[3]
        h = args[4]
        a=Entity()
        a.addComponent (Gfx(image = props[1], repeat = [w, h]))
        #f = Fader()
        ##f.addColor (0, [255,255,255,255])
        #f.addColor (1, [255,255,255,0])
        #f.addColor (2, [255,255,255,255])
        #a.addComponent (f)
        #a.addComponent (TexAnim (period=[0,-1]))
        a.pos = (x * vars.tileSize, y * vars.tileSize, z)
        return a
    return f

def brick(props):
    def f(args):
        model = props[1]
        x = args[0]
        y = args[1]
        a = Sprite(model = model)
        a.addComponent (Collider (flag = vars.flags.platform, mask = 0, tag = 0, shape = sh.Rect(width=vars.tileSize, height=vars.tileSize)))
        a.pos = [x * vars.tileSize, y * vars.tileSize, 0]
        a.addComponent (Info(piece = props[2]))
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

def multicoinbrick(props):
    def f(args):
        return _brick(args[0], args[1], props[1], args[2], m2)
    return f


def bg(props):
    def f(args):
        a = Entity(pos=[args[0],args[1],args[2]])
        a.addComponent (ShapeGfxColor(shape = sh.Rect(256, 256), fill = sh.SolidFill(r=props[1], g=props[2], b=props[3])))
        a.addComponent (Parallax(cam='maincam', factor=[1,1], campos0=[128,128], pos0=[0,0]))
        return a
    return f

def bgp(props):
    def f(args):
        p = props[1]
        print (p)
        a = Entity(pos=[args[0],args[1],args[2]])
        a.addComponent (Gfx(image=p['image'], repeat=p['repeat']))
        a.addComponent (Parallax(cam='maincam', factor=p['parallax'], campos0=[128,112], pos0=[0,64]))
        return a
    return f

def makeDoor (props):
    def f(args):
        a = Sprite(model='door', pos = [args[0]* vars.tileSize, args[1]* vars.tileSize, -1])
        a.addComponent (Collider (flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.door, shape=sh.Rect(vars.tileSize, vars.tileSize*2)))
        a.addComponent (Info (var = args[2], world = args[3], start=args[4]))
        return a
    return f

# spawns a foe when player hits it
def makeSpawn (prop):
    def f(args):
        spawn = Entity(pos = [args[0] * vars.tileSize, args[1] * vars.tileSize])
        spawn.addComponent (Collider(flag=vars.flags.foe,mask=vars.flags.player,tag=vars.tags.spawn, shape=sh.Rect(1,256)))
        spawn.addComponent (Info(factory=prop[1], info = prop[2], delta = [args[2], args[3]]))
        return spawn
    return f

def makePipeIn (prop):
    def f(args):
        ps = prop[1] if len(prop)>0 else {}
        pin = Entity(pos = [args[0] * vars.tileSize, args[1] * vars.tileSize], tag=ps.get('tag',None))
        pin.addComponent (Collider(flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.warp, shape = sh.Rect(4, 2)))
        pin.addComponent (Info (world=args[2], start=args[3]))
        return pin
    return f

def makeCollect(prop):
    def f(args):
        # the first argument is the callback function
        # the second, if present, is the model
        model = prop[1].get('model', None)
        func = prop[1].get('func')
        info = prop[1].get('info', None)
        pos = [args[0]*vars.tileSize,args[1]*vars.tileSize]
        if model is None:
            a = Entity(pos=pos)
            size = prop[1].get('size')
            a.addComponent (Collider (flag = vars.flags.foe, mask = vars.flags.player, tag= vars.tags.key, shape=sh.Rect(width=size[0],height=size[1])))
        else:
            a = Sprite(model=model, pos=pos)
            a.addComponent (SmartCollider(flag=vars.flags.foe, mask = vars.flags.player, tag = vars.tags.key))
        a.addComponent (Info (func = func, info = info))
        return a
    return f

def makeMovingPlatform(prop):
    def f (args):
        P = [args[0]*vars.tileSize, args[1]*vars.tileSize]
        e = Entity (pos = P)
        e.addComponent (TiledGfx (tilesheet='gfx/smb1.png', sheetSize=[16,16], tileData=[15,5], width = 1, height = 1, size=vars.tileSize,
            repx=args[2],repy=1))
        e.addComponent (Collider (flag = vars.flags.platform_passthrough, mask = vars.flags.player, tag = 0, 
            shape = sh.Line(A=[0,vars.tileSize,0],B=[args[2]*vars.tileSize,vars.tileSize,0])))
        e.addComponent (PolygonalMover (origin = P, loop = args[5], pct=args[3], moves = [ {'delta': [0,args[4]*vars.tileSize], 'speed': args[6], 'hold': 0} ]))
        e.addComponent (Platform())
        return e
    return f


def makeSimpleFoe(prop):
    def f(args): #model: str, x: float, y: float):
        props=prop[1]
        model = props['model']
        fliph = props['fliph']
        flipp = props['flipAtPlatformEnd']
        ctag = props['ctag']
        scale = props.get('scale', 1)
        speed = props.get('speed', 20)
        goomba = Sprite(model = model, pos = [args[0] * vars.tileSize, args[1] * vars.tileSize, 0.1])
        goomba.scale = scale
        goomba.addComponent (SmartCollider(
            flag = vars.flags.foe,
            mask = vars.flags.player,
            tag = getattr(vars.tags, ctag)))
        goomba.addComponent (Controller2D(
            maskUp = vars.flags.platform, 
            maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
            maxClimbAngle = 80, 
            maxDescendAngle = 80))
        goomba.addComponent (Dynamics2D(gravity= vars.gravity))
        stateMachine = StateMachine(initialState='walk')
        stateMachine.states.append (FoeWalk(
            id = 'walk', 
            anim = 'walk',  
            speed = speed, 
            acceleration = 0,
            flipHorizontal = fliph,
            flipWhenPlatformEnds= flipp,
            left = 1))
        stateMachine.states.append (FoeWalk(
            id = 'dead', 
            anim = 'dead',  
            speed = 0, 
            acceleration = 0,
            flipHorizontal = fliph,
            flipWhenPlatformEnds= flipp,
            left = 1))
        stateMachine.states.append (SimpleState(id='dead2', anim='idle'))
        goomba.addComponent (stateMachine)
        return goomba
    return f


def makeKoopa(prop):
    def f(args):
        props=prop[1]
        model = props['model']
        fliph = props['fliph']
        flipp = props['flipAtPlatformEnd']
        speed = props.get('speed', 20)
        goomba = Sprite(model = model, pos = [args[0] * vars.tileSize, args[1] * vars.tileSize, -0.1])
        goomba.addComponent (SmartCollider(
            flag = vars.flags.foe,
            mask = vars.flags.player,
            tag = vars.tags.koopa))
        goomba.addComponent (Controller2D(
            maskUp = vars.flags.platform, 
            maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
            maxClimbAngle = 80, 
            maxDescendAngle = 80))
        goomba.addComponent (Dynamics2D(gravity= vars.gravity))
        goomba.addComponent (ScriptPlayer())
        stateMachine = StateMachine(initialState='walk')
        stateMachine.states.append (FoeWalk(
            id = 'walk', 
            anim = 'walk',  
            speed = speed, 
            acceleration = 0,
            flipHorizontal = fliph,
            flipWhenPlatformEnds= flipp,
            left = 1))
        stateMachine.states.append (FoeWalk(
            id = 'walk2', 
            anim = 'hide',  
            speed = 200,
            acceleration = 0,
            flipHorizontal = fliph,
            flipWhenPlatformEnds= flipp,
            left = 1))
        stateMachine.states.append (FoeWalk(
            id = 'hide', 
            anim = 'hide',  
            speed = 0, 
            acceleration = 0,
            flipHorizontal = fliph,
            flipWhenPlatformEnds= flipp,
            left = 1))
        goomba.addComponent (stateMachine)
        return goomba
    return f


def makeFoe (id: str, x:float, y:float): #model: str, x: float, y: float, speed: float, scale: float = 1.0, energy=1):
    model, speed, scale, energy = vars.foes[id]
    

    collFlag = vars.flags.foe
    collMask = vars.flags.player | vars.flags.player_attack
    collTag = vars.tags.foe    
    castTag = vars.tags.foe_attack
    castMask = vars.tags.player
    
    entity = Sprite (model = model, pos = [x * vars.tileSize, y*vars.tileSize, 0])
    entity.addComponent (SmartCollider(
        flag = collFlag,
        mask = collMask,
        tag = collTag,
        castTag=castTag,
        castMask=castMask))
    entity.scale = scale
    entity.addComponent (Info (energy=energy))
    entity.addComponent (Controller2D(
        maskUp = vars.flags.platform, 
        maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
        maxClimbAngle = 80, 
        maxDescendAngle = 80))
    
    entity.addComponent (Dynamics2D(gravity= vars.gravity))
    
    stateMachine = StateMachine(initialState='walk')
    
    stateMachine.states.append (FoeChase(id='walk', walkanim='walk', idleanim='idle', speed = 20, acceleration=0, attacks=['attack3'], prob_attack= 0.1))
    stateMachine.states.append (Attack(id='attack1', anim= 'attack1'))
    stateMachine.states.append (Attack(id='attack2', anim= 'attack2'))
    stateMachine.states.append (JAttack (id='attack3', animup='jumpup', animdown = 'jumpdown', animland='ciao', height=80, timeDown=0.2))
    stateMachine.states.append (SimpleState(id='dead', anim='hit'))
    stateMachine.states.append (IsHit(id='ishit', acceleration=300, anim='hit', dist =32))
    stateMachine.states.append (FoeWalk(id='landed', anim='landed',speed=0,acceleration=0,flipHorizontal=True,flipWhenPlatformEnds=False, left=False))
    stateMachine.states.append (FoeWalk(id='idle', anim='idle',speed=0,acceleration=0,flipHorizontal=True,flipWhenPlatformEnds=False, left=False))
    entity.addComponent (stateMachine)
    return entity
