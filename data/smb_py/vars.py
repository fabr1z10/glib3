tileSize = 16
jump_height = 160
time_to_jump_apex = 0.5
gravity = -(2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
jump_velocity = abs(gravity) * time_to_jump_apex
warp_func = None
state = 2
invincibility = False
player = 'mario'
score = 0
coins = 0
time = 0
start_pos = 0
currentWarp = -1
paused = False

stateInfo = [
    'mario',
    'supermario',
    'fierymario'
]

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
