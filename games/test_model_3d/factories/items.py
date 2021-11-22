from mopy.entity import Entity
import mopy.monkey as monkey


def brick(ciao):
    e = Entity()
    tile_size = monkey.engine.room_vars.get('tile_size', [1, 1])
    e.components.append({
        'type': 'components.collider',
        'shape': {
            'type': 'rect',
            'width': tile_size[0],
            'height': tile_size[1],
        },
        'tag': 0,
        'flag': 2,
        'mask': 0,
        'debug': True
    })
    return e