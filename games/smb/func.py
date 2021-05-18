# functions
import vars
import example
import entity
import monkey
import sys
import actions as act
import components as comp
import platformer.states
from script import Script
import math

def toggle_pause():
    if vars.paused:
        example.get('main').enableUpdate(True)
        example.removeByTag('shader')
    else:
        example.get('main').enableUpdate(False)
        a = entity.Entity(pos=(0, 0, 1), tag='shader')
        a.add_component()
        a.addComponent (compo.ShapeGfxColor(shape = sh.Rect(256, 256), fill = sh.SolidFill(r=0, g=0, b=0, a=64)))
        example.get('diag').add(a)
    vars.paused = not vars.paused


def goto_world(world_id: str, start_location: int):
    def f():
        vars.invincibility = False
        # Don't reset energy! This only should be done after player dies!
        # vars.energy = vars.init_energy

        # Important! Reset these or otherwise you will get runtime errors!
        vars.currentWarp = -1

        vars.start_pos = start_location

        s = Script()
        s.add_action(act.ChangeRoom(world_id))
        example.play(s)

    return f


def restart():
    vars.invincibility = False
    vars.currentWarp = -1
    example.restart()


# player hitting a brick sensor
def brick_response(player: example.Wrap1, brick: example.Wrap1, x, y):
    # get the actual brick
    b = brick.parent()
    brick_id = b.id
    player.vy=-abs(player.vy)
    if vars.state == 0:
        s = Script()
        ystop = b.y
        s.add_action(act.MoveAccelerated(v0=[0, 50], a=[0, 0.5 * vars.gravity], yStop=ystop, entity_id=brick_id))
        example.play(s)
    else:
        # supermario
        piece = b.getInfo()['piece']
        example.remove(brick_id)
        m = example.get('main')
        make_piece(pos=[b.x, b.y, 1], vx=60, vy=180, model=piece, parent=m)
        make_piece(pos=[b.x, b.y, 1], vx=-60, vy=180, model=piece, parent=m)
        make_piece(pos=[b.x, b.y, 1], vx=120, vy=120, model=piece, parent=m)
        make_piece(pos=[b.x, b.y, 1], vx=-120, vy=120, model=piece, parent=m)


def bonus_brick_response(player: example.Wrap1, brick: example.Wrap1, x, y):
    b = brick.parent()
    info = b.getInfo()
    hits_left = info['hitsLeft']
    brick_id = b.id
    if hits_left > 0:
        info['hitsLeft'] -= 1
        s = Script()
        ystop = b.y
        s.add_action(act.MoveAccelerated(v0=[0, 50], a=[0, 0.5 * vars.gravity], yStop=ystop, entity_id=brick_id))
        if hits_left == 1:
            s.add_action(act.Animate(anim='taken', entity_id=brick_id))

        # release the bonus
        def p():
            info['callback'](b.x / vars.tile_size + 0.5, b.y / vars.tile_size)
        s.add_action(act.CallFunc(p))
        example.play(s)


def make_piece(pos, vx, vy, model, parent: example.Wrap1):
    a = entity.Sprite(model=model, pos=pos)
    id = parent.add(a)
    s = Script()
    s.add_action(act.MoveAccelerated(entity_id=id, v0=[vx, vy], a=[0, 0.5*vars.gravity], yStop=0))
    s.add_action(act.RemoveEntity(entity_id=id))
    example.play(s)


def on_warp_enter(player: example.Wrap1, warp: example.Wrap1, x, y):
    print('entering warp')
    vars.currentWarp = warp.id


def on_warp_exit(player: example.Wrap1, warp: example.Wrap1, x, y):
    print('exiting warp')
    vars.currentWarp = -1


def mushroom_response(player: example.Wrap1, mushroom: example.Wrap1, x, y):
    example.remove(mushroom.id)
    upgrade_player()


def upgrade_player():
    vars.state += 1
    if vars.state >= len(vars.stateInfo):
        vars.state = len(vars.stateInfo)-1
    # update model
    pl = example.get('player')

    st = vars.states[vars.state]

    size = st['size']
    offset = st['offset']
    pl.setModel(st['model'])
    pl.setColliderBounds(size[0], size[1], size[2], offset[0], offset[1], offset[2])
    # update bounding rect



def coin_response(player: example.Wrap1, coin: example.Wrap1, x, y):
    example.remove(coin.id)


def on_hotspot_enter(player: example.Wrap1, warp: example.Wrap1, x, y):
    info = warp.getInfo()
    if 'func' in info:
        info['func'](player, warp)


def goomba_response(player: example.Wrap1, goomba: example.Wrap1, x, y):
    if player.getState() == 'jump' and player.vy < 0:
        s = Script()
        player.vy = 300
        s.add_action(act.SetState(state='dead', entity_id=goomba.id ))
        s.add_action(act.Delay(2))
        s.add_action(act.RemoveEntity(goomba.id))
        example.play(s)
    else:
        player_hit_by_enemy(player)


def koopa_response(player: example.Wrap1, koopa: example.Wrap1, x, y):
    if koopa.getState() == 'hide':
        koopa.killScripts()
        if player.getState() == 'jump' and player.vy < 0:
            player.vy = 300
        #koopa.move(-10 * x, 0, 0)
        left = 0 if (player.x < koopa.x) else 1
        s = Script()
        s.add_action(act.SetState(state='walk2', entity_id=koopa.id, args={'left': left}))
        koopa.play(s)
    elif koopa.getState() == 'walk2':
        # hit player only if going towards player
        dx = player.x - koopa.x
        if (dx > 0 and not koopa.flipx) or (dx < 0 and koopa.flipx):
            player_hit_by_enemy(player)

    else:
        if player.getState() == "jump" and player.vy < 0:
            print ('fokkami')
            player.vy = 300
            s = Script()
            s.add_action(act.SetState(state='hide', entity_id=koopa.id))
            s.add_action(act.Delay(20))
            s.add_action(act.Blink(duration=2,blink_duration=0.2,entity_id=koopa.id))
            s.add_action(act.SetState(state='walk', entity_id = koopa.id))
            koopa.play(s)
        else:
            player_hit_by_enemy(player)


def player_hit_by_enemy(player: example.Wrap1):
    if vars.invincibility:
        return
    downgrade_player()


def downgrade_player():
    vars.state -= 1
    if vars.state < 0:
        player_dead()
    else:
        vars.invincibility = True
        pl = example.get('player')
        st = vars.states[vars.state]
        size = st['size']
        offset = st['offset']
        pl.setModel(st['model'])
        pl.setColliderBounds(size[0], size[1], size[2], offset[0], offset[1], offset[2])
        s = Script()
        s.add_action(act.Blink(duration=5, blink_duration=0.2, entity_id=pl.id))
        s.add_action(act.CallFunc(reset_invincible))
        example.play(s)


def reset_invincible():
    vars.invincibility = False


def restart():
    vars.invincibility = False
    vars.currentWarp = -1
    example.restart()


def player_dead():
    s = Script()
    vars.state = 0
    s.add_action(act.SetState(state='dead', tag='player'))
    s.add_action(act.Delay(1))
    s.add_action(act.MoveAccelerated(v0=[0, 200], a=[0, vars.gravity], yStop=0, tag='player'))
    s.add_action(act.RemoveEntity(tag='player'))
    s.add_action(act.CallFunc(restart))
    example.play(s)


def on_spawn(player: example.Wrap1, spawn: example.Wrap1, x, y):
    # get the detail
    info = spawn.getInfo()
    fct = info['factory']
    func = monkey.engine.get_item_factory(fct)
    props = info['info']
    delta = info['delta']
    px = spawn.x / vars.tile_size + delta[0]
    py = spawn.y / vars.tile_size + delta[1]
    spawned = func(props)(px, py)
    example.get('main').add(spawned)
    example.remove(spawn.id)


def on_collect_item(player: example.Wrap1, item: example.Wrap1, x, y):
    f = item.getInfo()['func']
    getattr(sys.modules[__name__], f)(player, item, x, y)


def fire_hits_foe(foe: example.Wrap1, fire: example.Wrap1, x, y):
    example.remove(fire.id)
    foe.setState('dead2', {})
    s = Script()
    s.add_action(act.MoveAccelerated(v0=[50 if fire.x < foe.x else -50, 150], a=[0, vars.gravity], yStop=-32, entity_id=foe.id))
    s.add_action(act.RemoveEntity(entity_id=foe.id))
    example.play(s)


def _fire(a: example.Wrap1, state: str):
    if vars.state >= 2:
        a.setState(state, {})
        b = entity.Sprite(model='fire', pos=(a.x + (-2 if a.flipx else 2), a.y+16, 0))
        b.flipx = a.flipx
        b.add_component(comp.Controller2D(
            mask_up=vars.flags.platform,
            mask_down=vars.flags.platform | vars.flags.platform_passthrough,
            max_climb_angle=80,
            max_descend_angle=80))
        b.add_component(comp.GarbageCollect(10))
        b.add_component(comp.Dynamics2D(gravity=vars.gravity))
        b.add_component(comp.SmartCollider(flag=vars.flags.player_attack, mask=vars.flags.foe | vars.flags.platform, tag=vars.tags.player_fire))
        sm = comp.StateMachine(initial_state='jmp')
        sm.states.append(platformer.states.Bounce(uid='jmp', speed=300, a=0, b=200))
        b.add_component(sm)
        example.get('main').add(b)


def fire(a: example.Wrap1):
    _fire(a, 'attack1')


def firej(a: example.Wrap1):
    _fire(a, 'attack2')


def enter_pipe(a: example.Wrap1):
    if not vars.paused and vars.currentWarp != -1:
        a.setState('pipe', {})
        info = example.getById(vars.currentWarp).getInfo()
        s = Script()
        s.add_action(act.Move(speed=100, by=[0, -64], tag='player'))
        s.add_action(act.CallFunc(goto_world(info['world'], info['start'])))
        example.play(s)


def dead(p: example.Wrap1, k, x, y):
    p.setModel(vars.stateInfo[0])
    vars.state = 0
    downgrade_player()


def win_slide(p: example.Wrap1, k, x, y):
    example.remove(k.id)
    p.setState('slide', {})
    s = Script()
    p.vy = 0
    s.add_action(act.Move(speed=50, to=[p.x, 48], tag='player'))
    s.add_action(act.SetState(tag='player', state='demo', args={'left': 0}))
    example.play(s)


def goto_stage(p: example.Wrap1, k: example.Wrap1, x, y):
    add_info = k.getInfo()['info']
    example.remove(k.id)
    p.setActive(False)
    s = Script()
    s.add_action(act.Delay(0.5))
    s.add_action(act.CallFunc(goto_world(add_info['world'], add_info['pos'])))
    example.play(s)


def pickup_coin(p, k, x, y):
    example.remove(k.id)
    vars.coins += 1
    example.get('coin_label').setText ('{:02d}'.format(vars.coins))

def spawn(p, k, x, y):
    info = k.getInfo()
    detail = info['info']
    factory = detail['factory']
    args = detail['args']
    print(args)
    func = monkey.engine.get_item_factory(factory)(**args)
    positions = info['args'][4:]
    example.remove(k.id)
    for i in range(0, len(positions)//2):
        ix = positions[i * 2]
        iy = positions[i * 2 + 1]
        foe = func(ix, iy)
        example.get('main').add(foe)


def pipe_out(p: example.Wrap1, k, x, y):
    p.setState('demo', {'left': 0})
    add_info = k.getInfo()['info']
    s = Script()
    s.add_action(act.Delay(0.5))
    s.add_action(act.CallFunc(goto_world(add_info['world'], add_info['pos'])))
    example.play(s)


def cippo():
    example.get('w1').setActive(False)
    s = Script()
    s.add_action(act.SetState(tag='player', state='pipe'))
    s.add_action(act.Move(tag='player', speed=50, by=[0, 64]))
    s.add_action(act.SetState(tag='player', state='walk'))
    example.play(s)
