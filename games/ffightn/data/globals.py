default_size = (2, 2, 2)
default_speed = 50
default_time_acc = 0.1
default_jump_height = 50
default_time_to_jump_apex = 0.5
attack_keys = [
    81, # Q
    87, # W
    69  # E
]
class CollisionFlags:
    player = 1
    platform = 2
    foe = 4
    player_attack = 8
    foe_attack = 16
    platform_passthrough = 32


class CollisionTags:
    player = 1
    goomba = 2
    brick_sensor = 3
    player_attack = 4
    crate = 5
    foe = 6
    foe_attack =7
    platform = 8