# functions
import vars
import example
import entity
import actions as act
from script import Script

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


def restart():
    vars.invincibility = False
    vars.currentWarp = -1
    example.restart()


# player hitting a brick sensor
def brick_response(player: example.Wrap1, brick: example.Wrap1, x, y):
    # get the actual brick
    b = brick.parent()
    brick_id = b.id
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
        s.add_action(act.MoveAccelerated(v0=[0, 50], a=[0, 0.5 * vars.gravity], yStop=ystop, id=brick_id))
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
    pl.setModel(vars.stateInfo[vars.state])


def coin_response(player: example.Wrap1, coin: example.Wrap1, x, y):
    example.remove(coin.id)
