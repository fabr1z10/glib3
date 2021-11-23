import glm

def tiles_to_world(tile_pos, tile_size):
    if len(tile_pos) == 2:
        return tile_pos[0] * tile_size[0], tile_pos[1] * tile_size[1]
    else:
        return tile_pos[0] * tile_size[0], tile_pos[1] * tile_size[1], tile_pos[2]


def mat_to_list(m):
    return [ m[0][0], m[0][1], m[0][2], m[0][3],
             m[1][0], m[1][1], m[1][2], m[1][3],
             m[2][0], m[2][1], m[2][2], m[2][3],
             m[3][0], m[3][1], m[3][2], m[3][3]]


# compute gravity and initial jump vel from jump height
# and time to jump apex
def compute_gravity(jump_height, time_to_jump_apex):
    gravity = (2.0 * jump_height) / (time_to_jump_apex * time_to_jump_apex)
    jump_speed = abs(gravity) * time_to_jump_apex
    return gravity, jump_speed