# # to be populated via the characters.yaml file
# #characters = dict()
#
jump_height = 40.0
time_to_jump_apex = 0.5
gravity = -(2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
jump_velocity = abs(gravity) * time_to_jump_apex
# scale = 1
# player = 'larry'
# height = 0
# cm_per_unit = 40
# # player variables - might change at game time
player_scale = 1
player_speed = 100
player_model = 'cody/sprite/main'
# player_dead = False
# energy = 599
# energy_start = 10
# enemy_count = 0
# max_enemies = 1
# foe_desc_id = None
# prob_new_enemy = 0.4
# enemies_to_kill = 10
# enemy_killed = 0
# next_room=None
# room_length = 0
# invincibility = False
# z = 0
# closest_foe = None
# dynamic_foes = dict()
# current_foes = dict()
# size_small = 1.2
# scale_factor = 1.0
# default_scale = 1.0
# room_3d = False
#
# # player status
# pl_model = 'g11'
# skin = 'f'
# size = 's'
# futa = '0'
# shoez = 'bare'
#
# model_id = 0
# #model_prefix = 'gal11'
# model_prefix = 'gal14'
# player_portrait = 'gfx/portraits/melissa.jpg'
# player_name = 'MELISSA'
# shoez_id = 'bare'
# cock_id = None
# cock_size = 1
# # variation on the models
# modelz = [
#     'light',
#     'dark',
#     'big',
#     'dark_big',
#     'massive',
# ]
#
# def get_height_str(height):
#     return str(round(height)) + 'cm'
#
# def get_model():
#     return model_prefix + '_' + modelz[model_id] + '_' +shoez_id
#
# def get_model_noshoe():
#     return model_prefix + '_' + modelz[model_id]
#
#
#
# # keys
# class keys:
#     hit1 = 90
#     hit2 = 88
#     fire = 65
#     stomp = 83
#
# statix = {
#     '0': {'img': 'gfx/static/0018.png', 'scale': 0.01, 'shadow_pos': [0,20,0], 'shear': -0.05},
#     '1': {'img': 'gfx/static/0020.png', 'scale': 0.008, 'shear':0.07},
#     '2': {'img': 'gfx/static/0021.png', 'scale': 0.008, 'shear': 0.12}
# }
#
# bonus = [
#     ['sprites/01/mushroom', 'grow', 0.1],
#     ['sprites/01/shrink_mushroom', 'shrink', 0.1],
#     ['sprites/01/dumbbell', 'update_model', 0.1, 2],
#     ['sprites/01/dumbbell', 'update_model', 0.1, 3],
#     ['sprites/01/tanlotion', 'update_model', 0.1, 1],
#     ['sprites/01/tanlotion', 'update_model', 0.1, 3],
#     ['sprites/01/potion', 'update_model', 0.1, 4],
#     ['sprites/01/filadisr', 'put_on_shoez', 0.02, 'filadisr'],
#     ['sprites/01/combatbo', 'put_on_shoez', 0.02, 'combat1'],
#     ['sprites/01/yrudreaw', 'put_on_shoez', 0.02, 'shoe1'],
#     ['sprites/01/potion', 'get_futa', 0.1, 'cock', 1],
#     ['sprites/01/dumbbell', 'get_futa', 0.1, 'cock', 2],
#     #['sprites/01/yrudreaw', 'put_on_shoez', 0.02, 'yrudreaw'],
#     #['sprites/01/cork1', 'put_on_shoez', 0.02, 'a4'],
#     #['sprites/01/demstackblk', 'put_on_shoez', 0.02, 'a6'],
# ]
#
# bonuses = {
#     'gal11': [
#         [0, 1, 2, 4, 7, 8, 9],
#         [0, 1, 3, 7, 8, 9],
#         [0, 1, 5, 7, 8, 9],
#         [0, 1, 6, 7, 8, 9],
#         [0, 1, 7, 8, 9]],
#     'melissa': [[0, 1, 7, 8, 10, 11]],
#     'gal14': [[0, 1, 7, 8]],
#     #'melissa': [[11]]
# }
#
# blood_fx = [
#     ['gfx/fx/44479.png', (331, 174), 0.01],
#     ['gfx/fx/12.png', (470, 476), 0.01]
# ]
#
# foes = []
#
#
# textures = {
#     '1': ['gfx/tex/pitted.jpg', 10, 10],
#     '2': ['gfx/tex/w1.jpg', 10, 10],
#     '3': ['gfx/tex/crate1.jpg', 2, 2],
#     '4': ['gfx/tex/floor1.png', 2, 2],
#     'asph': ['gfx/tex/asphalt0.jpg', 8, 8],
#     'hbone1': ['gfx/tex/herrbon1.png', 8, 8],
#     'curb': ['gfx/tex/curb.jpg', 10, 1]
#
# }
#
#
class flags:
    player = 1
    platform = 2
    foe = 4
    player_attack = 8
    foe_attack = 16
    platform_passthrough = 32
    gib = 64


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
    foe_attack = 28
    player_attack = 29
    foe=30
    bonus_container=31
    bonus=32
    gonext = 33
    crusher = 34
    gib = 35
    platform = 36
    platform_destructible = 37

