import mopy.util as utils

tile_size = 16, 16
jump_height = 64
time_to_jump_apex = 0.5
a = utils.compute_gravity(jump_height, time_to_jump_apex)
gravity = a[0]
jump_velocity = a[1]


class CollisionFlags:
    player = 1
    platform = 2
    foe = 4
    platform_passthrough = 32


class CollisionTags:
    player = 1
    goomba = 2
    brick_sensor = 3

