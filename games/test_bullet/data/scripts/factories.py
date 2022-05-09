import mopy.util as utils
from mopy.entity import Entity

def ramp(args):
    e = Entity()
    pos = args['pos']
    e.model = {
        'type': 'model.ramp3D_wireframe',
        'width': args['width'],
        'length': args['length'],
        'height': args['height']
    }
    e.components = [{
        'type': 'bullet.rigid_body',
        'pos': pos,
        'mass': 0,
        'shape': {
            'type': 'bullet.ramp',
            'width': args['width'],
            'length': args['length'],
            'height': args['height']

        }
    }]
    return e


def box(args):
    color = args['color']
    size = args['size']
    pos = args['pos']
    mass = args['mass']
    color = utils.hex_to_rgb(color)
    half_size = [size[0] * 0.5, size[1] * 0.5, size[2] * 0.5]
    e = Entity()
    e.auto_pos = True
    e.model = {
        'type': 'model.box3D_color',
        'color': [color[0], color[1], color[2], 1],
        'size': size,
        'offset': [-half_size[0], -half_size[1], -half_size[2]]
    }
    e.components = [{
        'type': 'bullet.rigid_body',
        'pos': pos,
        'mass': mass,
        'shape': {
            'type': 'bullet.box',
            'size': half_size
        }
    }]
    return e
