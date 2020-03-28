import lib_py.entity as e
import lib_py.components as compo
import lib_py.room as room
import lib_py.engine as engine
import lib_py.entity as entity
import example

import settings
from types import SimpleNamespace

# scumm requires a list of verb. Each verb 

class Verb:
    def __init__(self, id : str, text: str, items: int):
        self.text = text
        self.id = id
        self.items = items


class ScummConfig:
    class Colors:
        current_action = [0, 170, 170, 255]
        verb_selected = [255, 255, 85, 255]
        verb_unselected = [0, 170, 0, 255]
    __verbs = {}
    @staticmethod
    def addVerb(v : Verb):
        ScummConfig.__verbs[v.id] = v
    @staticmethod
    def getVerb(id : str) -> Verb:
        return __verbs[id]
        


def print_msg(msg):
    def h(e : example.Wrap1):
        print(msg)
    return h

def change_color(color):
    def f(e : example.Wrap1):
        #a = example.Wrap1()
        e.setColor(color)
    return f    

def set_verb(verb):
    def f(e : example.Wrap1):
        a : example.Wrap1 = example.what.get('current_verb')
        print (a.x())
        a.setText(verb)
        print ('ok')
    return f

#    example.


# scumm.func.set_verb = function(verb)
#     local v = engine.config.verbs[verb]
#     if v.objects > 0 then
#         ai.verb = verb
#         ai.obj1 = nil
#         ai.obj2 = nil
#         ai.selectSecond = false
#         scumm.func.updateVerb()
#     else
#         v.callback()

#     end
# end
# entities
# button
class VerbButton(e.Text):
    def __init__(self, font: str, text: str, colorInactive, colorActive, align: e.TextAlignment = e.TextAlignment.topleft, tag=None, pos=[0,0,0]):
        super().__init__(font, text, colorInactive, align, tag, pos)          
        self.addComponent(compo.HotSpot(
            onenter = change_color(colorActive), 
            onleave = change_color(colorInactive),
            onclick = set_verb(text) )) 
            #onclick = print_msg('clicking')))


class RoomUI(room.Room):
    def __init__(self, width, height, collide = False):
        super().__init__(width, height, collide)
        uisize = settings.monkey.uiHeight
        print ('uisize is '+str(uisize))
        camWidth = settings.monkey.deviceSize[0]
        camHeight = settings.monkey.deviceSize[1] - uisize

        # get the verbset used in this room
        verbset = settings.monkey.config['verbset'][0]
        verbs = settings.monkey.config['verbs']
        # add the main node     
        main = e.Entity (tag='main')
        main.camera = e.cam.OrthoCamera(width, height, camWidth, camHeight, [0, uisize, camWidth, camHeight], tag='maincam')
        #main.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, pos = [camWidth/2, 16, 0]))

        # add the ui node
        ui = e.Entity (tag='ui')
        ui.camera = e.cam.OrthoCamera(camWidth, uisize, camWidth, uisize, [0, 0, camWidth, uisize], tag = 'uicam')
        ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = ScummConfig.Colors.current_action, align = e.TextAlignment.bottom, 
            tag = 'current_verb', pos = [camWidth/2, 48, 0]))

        row = 2
        count = 0
        for a in verbset[0]:
            col = 1 + count // 4
            x = 2 + (col - 1) * 46
            verb = ScummConfig.getVerb(a)
            ui.add (VerbButton(
                font = 'ui',
                text = verb.text,
                colorInactive = ScummConfig.Colors.verb_unselected,
                colorActive = ScummConfig.Colors.verb_selected,
                align = e.TextAlignment.bottomleft,
                pos = [x, uisize - row*8, 0]
            ))  
            count +=1
            row += 1
            if (row > 5):
                row = 2


		#ui.add (VerbButton (font='ui', text='Open', colorInactive = ScummConfig.Colors.verb_unselected, colorActive = ScummConfig.Colors.verb_selected, align = e.TextAlignment.bottomleft, pos = [0,0,0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.topleft, pos = [0, 56, 0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.bottomleft, pos = [0, 0, 0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.topright, pos = [320, 56, 0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.bottomright, pos = [320, 0, 0]))
		
        self.ref['main'] = main.children

        self.scene.append(main)
        self.scene.append(ui)

        # create a hotspot manager
        self.engines.append(engine.HotSpotManager())

class BackgroundItem(entity.Entity):
    def __init__(self, image = None, tag = None, pos = [0, 0, 0]):
        super().__init__(tag, pos)
        self.addComponent (compo.Gfx(image=image))

class Sprite(entity.Entity):
    def __init__(self, sprite : str, tag = None, pos = [0, 0, 0]):
        super().__init__(tag, pos)
        self.type = 'sprite'
        self.model = sprite
        #self.addComponent (compo.Gfx(image=image))

