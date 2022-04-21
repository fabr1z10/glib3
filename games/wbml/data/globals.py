import mopy.util as utils
import data.scripts as scripts

tiled_pos = True
tile_size = [16, 16]
jump_height = 96
time_to_jump_apex = 0.5
a = utils.compute_gravity(jump_height, time_to_jump_apex)
gravity = a[0]
jump_velocity = a[1]
player_modes = [
    {'model': 'sprites.wboy0', 'size': (0.8, 1)},
    {'model': 'sprites.wboy1', 'size': (0.8, 1)},
]
player_mode = 1
start_position = 0
active_warp = None
invincible = False
invincible_time = 5

class Keys:
    up = 264
    attack = 81

class CollisionFlags:
    player = 1
    platform = 2
    foe = 4
    controller = 8
    platform_passthrough = 32


class CollisionTags:
    player = 1
    door = 2
    foe = 3
    player_attack = 4
    coin = 5

collision_engine = {
    'type': 'runner.collisionengine',
    'response': [
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.door,
        'on_enter': scripts.set_warp,
        'on_leave': scripts.clear_warp
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.foe,
        'on_enter': scripts.ciaone
    },
    {
        'tag1': CollisionTags.player_attack,
        'tag2': CollisionTags.foe,
        'on_enter': scripts.ciaone2
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.coin,
        'on_enter': scripts.pick_up_coin
    }],
    'size': [80, 80]
}

doors = {
    0: {'open': 1, 'anim': 'closed', 'room': 'pippo'},
    1: {'open': 1, 'anim': 'bar', 'room': 'bar'}
}

room0 = 0