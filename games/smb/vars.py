tile_size = 16
jump_height = 160
time_to_jump_apex = 0.5
gravity = -(2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
jump_velocity = abs(gravity) * time_to_jump_apex
paused = False
invincibility = False
currentWarp = -1
score = 0
coins = 0
time = 300
start_pos = 0
state = 0                           # 0 = Mario, 1 = SuperMario, 2 = Fiery Mario

states = [
    {
        'model': 'sprites/01/mario',
        'size': (14, 15, 0),
        'offset': (0, 7.5, 0),
        'speed': 200
    },
    {
        'model': 'sprites/01/supermario',
        'size': (14, 30, 0),
        'offset': (0, 15, 0),
        'speed': 200
    },
    {
        'model': 'sprites/01/fierymario',
        'size': (14, 32, 0),
        'offset': (0, 16, 0),
        'speed': 200
    },
]



stateInfo = ['sprites/01/mario', 'sprites/01/supermario', 'sprites/01/fierymario']
tile_data = {}

class flags:
    player = 1
    platform = 2
    foe = 4
    player_attack = 8
    foe_attack = 16
    platform_passthrough = 32


class tags:
    player = 1
    mushroom = 11
    goomba = 12
    koopa = 13
    moving_platform =14
    coin = 15
    spawn = 16
    mushroom1up = 17
    starman = 18
    warp = 19
    brick_sensor = 20
    bonus_brick_sensor = 21
    hotspot = 22
    flower = 23
    fire = 24
    plant = 25
    key = 26
    player_fire = 27

foes = {
    'goomba': {
        'model': 'sprites/01/goomba',
        'size': (14, 16),
        'tag': tags.goomba,
        'flip_h': False,
        'flip_when_platform_ends': False,
        'speed': 10
    },
    'goomba2': {
        'model': 'sprites/01/goomba2',
        'size': (14, 16),
        'tag': tags.goomba,
        'flip_h': False,
        'flip_when_platform_ends': False,
        'speed': 10
    },
    'koopa': {
        'model': 'sprites/01/koopa',
        'size': (14, 24),
        'tag': tags.koopa,
        'flip_h': True,
        'flip_when_platform_ends': True,
        'speed': 10,
        'fast_speed': 300
    },
    'koopa2': {
        'model': 'sprites/01/koopa2',
        'size': (14, 24),
        'tag': tags.koopa,
        'flip_h': True,
        'flip_when_platform_ends': True,
        'speed': 10,
        'fast_speed': 300
    },
}