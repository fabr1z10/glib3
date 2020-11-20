tile_size = 16
jump_height = 160
time_to_jump_apex = 0.5
gravity = -(2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
jump_velocity = abs(gravity) * time_to_jump_apex
paused = False
invincibility = False
currentWarp = -1
score = 0
time = 300
start_pos = 0
state = 0                           # 0 = Mario, 1 = SuperMario, 2 = Fiery Mario
stateInfo = ['mario', 'supermario', 'fierymario']

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