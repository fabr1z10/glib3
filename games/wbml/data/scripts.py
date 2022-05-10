import data
from mopy.script import Script
import mopy.actions as act
from mopy.entity import Text, TextAlignment, Entity
import example
import mopy

def init():
    engine = mopy.monkey.engine
    engine.add_item_factory('player', data.factories.player)
    engine.add_item_factory('rect', data.factories.rect)
    engine.add_item_factory('bg', data.factories.bg)
    engine.add_item_factory('trunk', data.factories.trunk)
    engine.add_item_factory('mp', data.factories.moving_platform)
    engine.add_item_factory('foe', data.factories.foe)


def preload(desc):
    data.globals.start_positions = desc['start_positions']


def setup():
    print('merfda')


def setup2():
    #pass
    from wbml.data.actions import WBM

    s = Script()
    s.seq([WBM('$msg/1'),# WBM('$msg/2'), WBM('$msg/3'), WBM('$msg/4'),
           act.SetVariable('globals.player_mode', 1),
           act.SetVariable('globals.start_position', 1),
           act.SetVariable('globals.doors.0.open', 0),
           act.SetVariable('globals.room0', 1),
           act.ChangeRoom('citywl')])

    example.play(s)
    #pane()

def setup_bar():
    ra = mopy.monkey.engine.room_args
    gl = mopy.monkey.engine.data.globals
    bonus_left = Entity()
    bonus_left.model = gl.bonus_list[ra[0]]['gfx']
    bonus_left.pos = (2.5*16, 10.2*16, 0.11)
    example.get('main').add(bonus_left)
    bonus_right = Entity()
    bonus_right.model = gl.bonus_list[ra[2]]['gfx']
    bonus_right.pos = (9.5*16, 10.2*16, 0.11)
    example.get('main').add(bonus_right)




    from wbml.data.actions import WBM

    # check if player has enough gold to buy items
    min_cost = min(int(ra[1]), int(ra[3]))
    if gl.gold < min_cost:
        s = Script()
        s.seq([WBM('$msg/8'), act.ChangeRoom('citywl')])
        example.play(s)
    else:
        mopy.monkey.engine.data.globals.pos = [(2, 7.625, 0.1), (5.25, 7.625, 0.1), (9.5, 7.625, 0.1)]
        mopy.monkey.engine.data.globals.cpos = 1
        s = Script()
        s.seq([WBM('$msg/5')])
        example.play(s)
    #pane()


def hand_left():
    mopy.monkey.engine.data.globals.cpos = max(0,mopy.monkey.engine.data.globals.cpos-1)
    p = mopy.monkey.engine.data.globals.pos[mopy.monkey.engine.data.globals.cpos]
    example.get('hand').setPosition(p[0] * 16, p[1] * 16, p[2] * 16)


def hand_right():
    mopy.monkey.engine.data.globals.cpos = min(2,mopy.monkey.engine.data.globals.cpos+1)
    p = mopy.monkey.engine.data.globals.pos[mopy.monkey.engine.data.globals.cpos]
    example.get('hand').setPosition(p[0] * 16, p[1] * 16, p[2] * 16)

def hand_select():
    from wbml.data.actions import WBM
    gl = mopy.monkey.engine.data.globals
    selected = mopy.monkey.engine.data.globals.cpos
    s = Script()
    if selected == 1:
        s.seq([act.SetActive(tag='hand', value=False),
            WBM('$msg/6'), act.SetVariable('globals.start_position', 2), act.ChangeRoom('citywl')])
    else:
        bonus_picked = None
        cost = 0
        msg = None
        if selected == 0:
            bonus_picked = mopy.monkey.engine.room_args[0]
            cost = int(mopy.monkey.engine.room_args[1])
            msg = mopy.monkey.engine.room_args[4]
        else:
            bonus_picked = mopy.monkey.engine.room_args[2]
            cost = int(mopy.monkey.engine.room_args[3])
            msg = mopy.monkey.engine.room_args[5]
        if mopy.monkey.engine.data.globals.gold >= cost:
            mopy.monkey.engine.data.globals.gold -= cost
            bonus =gl.bonus_list[bonus_picked]
            bonus['callback']()
            s.seq([
                act.SetActive(tag='hand', value=False),
                WBM(msg),
                act.SetVariable('globals.start_position', 2),
                act.ChangeRoom('citywl')])
    example.play(s)


def set_warp(player, warp, x, y):
    info = warp.getInfo()
    mopy.monkey.engine.data.globals.active_warp = info['door_id']
    print('setting warp: ' + str(info['door_id']))


def ciaone(player, foe, x, y):
    gl = mopy.monkey.engine.data.globals
    if not gl.invincible:
        player.setState('hit', {'direction': 1 if player.flipx else -1})
        player.vy = 300
        player.vx = -100 if player.vx > 0 else 100


def coinland(e):
    e.setAnim('fall')


def pick_up_coin(player, coin, x, y):
    example.remove(coin.id)


def ciaone2(player_attack, foe, x, y):
    foe.setState('dead', {})
    s = Script()
    s.seq([
        act.Delay(sec=1),
        act.RemoveEntity(entity_id=foe.id),
        act.AddEntity(entity_id='entities.flying_coin', pos=[foe.x / 16, foe.y / 16, 1])
    ])
    example.play(s)


    #example.remove(foe.id)

def clear_warp(player, warp, x, y):
    mopy.monkey.engine.data.globals.active_warp = None
    print('clearing warp')


def pane():
    aa = mopy.monkey.engine.read('$msg/1')
    print(aa)
    id = example.get('main').add(Text(font='sprites.mario_font', size=8, text=aa, color=[0,0,0,0], maxwidth=160,align=TextAlignment.center, pos=[96, 132,1.01 ]))
    text_size = example.getById(id).getTextSize()
    # s.add_action(Msg(
    #     font=gl.msg_font,
    #     color=(127, 83, 30, 255),
    #     align=TextAlignment.center,
    #     text=mopy.monkey.engine.read(text),
    #     pos=(gl.sci_viewport[2] * 0.5, gl.sci_viewport[3] * 0.5, 1),
    #     inner_texture=gl.msg_inner_texture,
    #     border_texture=gl.msg_border_texture,
    #     eoc=True,
    #     timeout=1000,
    #     box=True,
    #     padding=(4, 5)))
    # s.add_action(sierra_enable_controls(True))
    # return s
    #s = Script()
    #
    #
    # print ('fottimilcazzzzo!!!!')
    #s.seq([
    #    act.AddEntity(entity_id='entities.textbg', pos=[0.5, 7, 1])
    #])
    import math
    tw = (text_size[2] - text_size[0])
    th = (text_size[3] - text_size[1])
    width = math.ceil(tw / 8.0)
    height = math.ceil(th / 8.0)
    data = [22, 8]
    data.extend([23, 8] * width)
    data.extend([24, 8])
    md = [22, 7]
    md.extend([23, 7] * width)
    md.extend([24, 7])
    data.extend(md * height)
    data.extend([22, 6])
    data.extend([23, 6] * width)
    data.extend([24, 6])
    e = Entity()
    e.model = {
            'type': 'model.tiled',
            'tex': 'gfx/wbml.png',
            'img_tile_size': [8, 8],
            'tile_size': [8, 8],
            'size': [width + 2, height + 2],
            'data': data}
    e.pos=[96 - 0.5 * tw - 8, 132 - 0.5*th - 8, 1]
    example.get('main').add(e)
    s = Script()
    acts=[]
    print('positioned ' + str(text_size))
    id1 = example.get('main').add(Text(tag='ciaone', font='sprites.mario_font', size=8, text=aa,
                                      color=[255,255,255,255], maxwidth=160,align=TextAlignment.top_left, pos=[96-0.5*tw, 132+0.5*th, 1.02]))
    for n in range(1, len(aa)+1):
        acts.append(act.SetText(tag='ciaone', text=aa[0:n]))
        acts.append(act.Delay(0.05))
    s.seq(acts)
    example.play(s)


def enter_door(x):
    if mopy.monkey.engine.data.globals.active_warp is not None:
        warp_id =mopy.monkey.engine.data.globals.active_warp
        mopy.monkey.engine.data.globals.active_warp = None
        door_info = mopy.monkey.engine.data.globals.doors[warp_id]
        s = Script()
        args = door_info.get('args',None)
        print('args=' +str(args))
        s.seq([
            act.SetState(tag='player', state='knock'),
            act.Delay(sec=0.1),
            act.Animate(tag='door_' + str(warp_id), anim='open'),
            act.ChangeRoom(room=door_info['room'], args=args)
        ])
        example.play(s)

def panepippo():
    print('ciao')