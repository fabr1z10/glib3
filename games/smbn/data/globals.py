import mopy.util as utils
import data.scripts


tiled_pos = True
tile_size = 16, 16
jump_height = 80
time_to_jump_apex = 0.5
a = utils.compute_gravity(jump_height, time_to_jump_apex)
gravity = a[0]
jump_velocity = a[1]
show_boxes = True
player_modes = [
    {'model': 'sprites.mario', 'size': (0.8, 1)},
    {'model': 'sprites.supermario', 'size': (0.8, 2)},
    {'model': 'sprites.fierymario', 'size': (0.8, 2)},
]
start_position = 0
player_mode = 0
score = 0
time = 0
display_name = ''
active_warp = None
invincible = False
invincible_time = 5

class Keys:
    down = 264

class CollisionFlags:
    player = 1
    platform = 2
    foe = 4
    controller = 8
    platform_passthrough = 32


class CollisionTags:
    player = 1
    goomba = 2
    bonus_brick_sensor = 3
    basic_brick_sensor = 4
    mushroom = 5
    flower = 6
    hidden_brick_sensor = 7
    warp = 8
    pickup_coin = 9
    warp_right = 10
    end_level = 11
    flag_pole = 12
    hotspot = 13


class colors:
    sky = [92/255.0, 148/255.0, 252/255.0, 1.0]
    sky2 = utils.rgb(36, 60, 98)

collision_engine = {
    'type': 'runner.collisionengine',
    'response': [
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.goomba,
        'on_enter': data.scripts.mario.foe_hits_mario
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.hotspot,
        'on_enter': data.scripts.mario.player_hits_hotspot
    },



    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.mushroom,
        'on_enter': data.scripts.mario.player_gets_mushroom
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.warp,
        'on_enter': data.scripts.mario.set_warp,
        'on_leave': data.scripts.mario.clear_warp
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.pickup_coin,
        'on_enter': data.scripts.mario.remove_item
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.warp_right,
        'on_enter': data.scripts.mario.on_warp_right
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.end_level,
        'on_enter': data.scripts.mario.end_level
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.flower,
        'on_enter': data.scripts.mario.player_gets_flower
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.bonus_brick_sensor,
        'on_enter': data.scripts.mario.hit_brick_sensor
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.basic_brick_sensor,
        'on_enter': data.scripts.mario.hit_basic_brick_sensor
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.hidden_brick_sensor,
        'on_enter': data.scripts.mario.hit_hidden_brick_sensor
    },
    {
        'tag1': CollisionTags.player,
        'tag2': CollisionTags.flag_pole,
        'on_enter': data.scripts.mario.play_flag_scene
    }
    ],
    'size': [80, 80]
}




    # size: [80, 80]