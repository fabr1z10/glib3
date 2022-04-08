from mopy.script import Script
import mopy.actions as act
import example
import data
import mopy
import mopy.util as utils
import data.factories as f


def init():
    engine = mopy.monkey.engine
    engine.add_item_factory('brick', f.brick)
    engine.add_item_factory('goomba', f.goomba)
    engine.add_item_factory('mario', f.mario)
    engine.add_item_factory('rect', f.rect)
    engine.add_item_factory('bg', f.bg)
    engine.add_item_factory('coin', f.coin)
    engine.add_item_factory('scoreboard', f.scoreboard)


def set_player_mode(n):
    player = example.get('player')
    tile_size = data.globals.tile_size
    data.globals.player_mode = n
    mode = data.globals.player_modes[n]
    player.setModel(mode['model'])
    size = mode['size']
    player.setColliderBounds(size[0] * tile_size[0], size[1] * tile_size[1], 0, 0, 0.5*size[1] * tile_size[1], 0)


def player_gets_mushroom(player, mushroom, x, y):
    if data.globals.player_mode == 0:
        set_player_mode(1)
    example.remove(mushroom.id)

def player_gets_flower(player, flower, x, y):
    if data.globals.player_mode < 2:
        set_player_mode(2)
    example.remove(flower.id)

def foe_hits_mario(player, foe, x, y):
    if player.getState() == 'jump' and player.vy < 0:
        s = Script()
        player.vy = data.globals.jump_velocity * 0.5
        s.add_action(act.SetState(state='dead', entity_id=foe.id))
        s.add_action(act.Delay(211))
        s.add_action(act.RemoveEntity(foe.id))
        example.play(s)
    else:
        pass
        #player_hit_by_enemy(player)

def hit_hidden_brick_sensor(player, sensor, x, y):
    if player.vy < 0:
        return
    player.vy = 0
    brick = sensor.parent()
    brick.collisionFlag = 2
    hit_brick_sensor(player, sensor, x, y)

def hit_brick_sensor(player, sensor : example.Wrap1, x, y):
    brick = sensor.parent()
    info = brick.getInfo()
    if info['hits_left'] > 0:
        print('hits:' + str(info['hits_left']))
        info['hits_left'] -= 1
        sensor.parent().vy = 100
        # release item if any
        bonus = info.get('item', None)
        print(bonus)
        if bonus:
            utils.create_entity(bonus, (brick.x + data.globals.tile_size[0] * 0.5, brick.y, -0.1), use_tile=False)
        if info['hits_left'] == 0:
            brick.setAnim('taken')


def hit_basic_brick_sensor(player, sensor : example.Wrap1, x, y):
    brick = sensor.parent()
    if data.globals.player_mode == 0:
        brick.vy = 100
    else:
        player.vy = 0
        utils.create_entity("scripts.factories.brick_piece", (brick.x, brick.y, 1), use_tile=False, args={'model': 'brickpiece', 'vx': 60, 'vy': 180})
        utils.create_entity("scripts.factories.brick_piece", (brick.x, brick.y, 1), use_tile=False, args={'model': 'brickpiece', 'vx': -60, 'vy': 180})
        utils.create_entity("scripts.factories.brick_piece", (brick.x, brick.y, 1), use_tile=False, args={'model': 'brickpiece', 'vx': 120, 'vy': 120})
        utils.create_entity("scripts.factories.brick_piece", (brick.x, brick.y, 1), use_tile=False, args={'model': 'brickpiece', 'vx': -120, 'vy': 120})
        example.remove(brick.id)

def set_warp(player, warp, x, y):
    data.globals.active_warp = warp.getInfo()['warp_to']
    print('setting warp')


def clear_warp(player, warp, x, y):
    data.globals.active_warp = None
    print('clearing warp')


def remove_item(player, item, x, y):
    example.remove(item.id)

def warp_down(a):
    print ('checking warp... ' + str(data.globals.active_warp))
    if data.globals.active_warp:
        s = Script()
        s.add_action(act.SetState(tag='player', state='warp'))
        s.add_action(act.Move(speed=50, by=(0, -64), tag='player'))
        s.add_action(act.ChangeRoom(data.globals.active_warp))
        example.play(s)


def on_warp_right(player, warp, x, y):
    player.setState('npcwalk', { 'direction': 1})


def end_level(player, warp, x, y):
    player.setActive(False)
    info = warp.getInfo()
    s = Script()
    s.add_action(act.Delay(sec=1))
    s.add_action(act.SetVariable('globals.start_position', info['start_position']))
    s.add_action(act.ChangeRoom(room=info['warp_to']))
    example.play(s)


def rise():
    player = example.get('player')
    player.setState('warp', {})
    s = Script()
    s.add_action(act.Move(speed=50, by=(0, 64), tag='player'))
    s.add_action(act.SetState(tag='player', state='walk'))
    example.play(s)

def play_flag_scene(player, obj, x, y):
    player.vy = 0
    s = Script()
    s.add_action(act.SetState(tag='player', state='slide'))
    s.add_action(act.Move(tag='player', by=(0, obj.y - player.y), speed=50))
    s.add_action(act.SetState(tag='player', state='npcwalk', args={'direction': 1}))
    example.play(s)