from mopy.actions import CallFunc, Sequence
from mopy.entity import Text, Entity, TextAlignment
import mopy
import mopy.actions as act
import example
import math


def initialize_message(msg_id):
    def f():
        aa = mopy.monkey.engine.read(msg_id)
        id = example.get('main').add(Text(font='sprites.mario_font', size=8, text=aa, color=[0, 0, 0, 0], maxwidth=160,align=TextAlignment.center, pos=[96, 132,1.01 ]))
        text_size = example.getById(id).getTextSize()
        tw = (text_size[2] - text_size[0])
        th = (text_size[3] - text_size[1])
        width = math.ceil(tw / 8.0)
        height = math.ceil(th / 8.0)
        data = [22, 8]
        data.extend([23, 8] * width)
        data.extend([24, 8])
        md = [22, 7]
        md.extend([23, 7] * width)
        md.extend([24, 7])
        data.extend(md * height)
        data.extend([22, 6])
        data.extend([23, 6] * width)
        data.extend([24, 6])
        e = Entity(tag='msg_wrap')
        e.model = {
            'type': 'model.tiled',
            'tex': 'gfx/wbml.png',
            'img_tile_size': [8, 8],
            'tile_size': [8, 8],
            'size': [width + 2, height + 2],
            'data': data}
        e.pos=[96 - 0.5 * tw - 8, 132 - 0.5*th - 8, 1]
        example.get('main').add(e)
        #s = Script()
        #acts=[]
        #print('positioned ' + str(text_size))
        id1 = example.get('main').add(Text(tag='ciaone', font='sprites.mario_font', size=8, text=aa,
                                          color=[255,255,255,255], maxwidth=160,align=TextAlignment.top_left, pos=[96-0.5*tw, 132+0.5*th, 1.02]))
    return f

    # for n in range(1, len(aa)+1):
    #     acts.append(act.SetText(tag='ciaone', text=aa[0:n]))
    #     acts.append(act.Delay(0.05))
    # s.seq(acts)
    # example.play(s)


class WonderBoyMsg(CallFunc):
    def __init__(self, msg_id):
        super().__init__(f=initialize_message(msg_id))


class WBM(Sequence):
    def __init__(self, msg_id):
        super().__init__()
        self.activities.append(WonderBoyMsg(msg_id))
        aa = mopy.monkey.engine.read(msg_id)
        for n in range(1, len(aa) + 1):
            self.activities.append(act.SetText(tag='ciaone', text=aa[0:n]))
            self.activities.append(act.Delay(0.05))
        self.activities.append(act.WaitForKey())
        self.activities.append(act.RemoveEntity(tag='ciaone'))
        self.activities.append(act.RemoveEntity(tag='msg_wrap'))

