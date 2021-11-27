from mopy.script import Script
import mopy.actions as act
import example
import data
import mopy.util as utils

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





