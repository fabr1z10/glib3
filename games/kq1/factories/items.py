import vars
import entity
import components as compo
import scumm.components
import shapes

def bg(**kwargs):
    def f(*args):
        e = entity.Entity(pos=(args[0], args[1], args[2]))
        e.add_component(compo.Gfx(image = kwargs['image']))
        return e
    return f

def walkarea(**kwargs):
    def f(*args):
        e = entity.Entity(pos=(args[0], args[1], args[2]))
        e.tag = kwargs.get('id')
        shape = shapes.Poly(kwargs.get('outline'))
        if 'holes' in kwargs:
            for hole in kwargs['holes']:
                shape.holes.append(hole)
        walkarea = scumm.components.Walkarea(shape=shape)
        walkarea.depth= kwargs.get('depth', None)
        walls = kwargs.get('walls', None)
        if walls:
            for w in walls:
                walkarea.add_wall([w[0], w[1]], [w[2], w[3]], True)
        e.add_component(walkarea)
        return e
    return f

def character(**kwargs):
    def f(*args):
        key = args[0]
        is_player = key == vars.current_player
        desc = args[1]
        model = desc.get('model', None)
        text_color = desc.get('text_color', [255, 255, 255, 255])
        text_offset = desc.get('text_offset', [0, 60])
        pos = desc.get('pos')
        tag = desc.get('tag', key)
        s = None
        dir = desc.get('dir', 's')
        if model:
            s = entity.Sprite(model=model, pos=pos, tag='player' if is_player else tag)
            #s.add_component(compo.Collider(debug=True, flag=vars.Collision.Flags.player, mask=vars.Collision.Flags.other,
            #                           tag=vars.Collision.Tags.player, shape=shapes.Rect(width=8, height=2, offset=[-4, 0])))
            if is_player:
                s.add_component(compo.Follow())
        else:
            s = entity.Entity(pos=pos, tag='player' if is_player else tag)
        s.add_component(scumm.components.CharacterController(dir=dir, speed=100, text_color=text_color, text_offset=text_offset))
        return s
    return f