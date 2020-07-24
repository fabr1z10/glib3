import copy
import lib_py.room as room
import lib_py.engine as engine
import lib_py.components as compo
import lib_py.entity as entity
import lib_py.runner as runner
import lib_py.camera as cam
import lib_py.scumm.scumm as scumm
import lib_py.scumm.entity as se
import lib_py.scumm.functions as func
from lib_py.scumm.helper import refresh_inventory
import lib_py.actions as act
import lib_py.scumm.actions as scact
from lib_py.script import Script
from lib_py.actions import RunScript
from lib_py.scumm.helper import addCustomScript
import example



def runDialogueScript(s):
    def f(x, y, obj = None):
        dial = example.get('dialogue')
        dial.clearText()
        # check if there's any script to run
        a = Script()
        node = s
        for cn in node.closeNodes:
            s.dialogue.nodes[cn].active = False
        for an in node.activateNodes:
            s.dialogue.nodes[an].active = True
        for id, d in s.dialogue.nodes.items():
            print (str(d.id) + ' ' + str(d.active))

        #if s.node.nextStatus != NodeStatus.SAME:
        #   s.node.status = s.node.nextStatus
        #s.node.dialogue.openNode(s.node)
        # check if I have a script associated to this line
        func = s.dialogue.id + '_'+node.id
        print ('check if ' + func)
        addCustomScript (engine.scripts.dialogues, func, a)
        #ds = s.script()
        #if ds:
        #    a.addAction(act.RunScript(s = ds))
        if s.nextId == None:
            print ('ending')
            a.addAction(scact.EndDialogue(s.dialogue.id))
        else:
            print ('next is ' + s.nextId)
            s.dialogue.current = s.nextId
            a.addAction(scact.ResumeDialogue(s.dialogue.id))
        example.play(a)
    return f

def makeInventoryButton(item):
    return se.InventoryButton(
        font='ui', 
        itemId=item[0], 
        qty=item[1],
        colorInactive = scumm.Config.Colors.inv_unselected, 
        colorActive= scumm.Config.Colors.inv_selected)

def makeDialogueButton(dialogueline):
    return se.DialogueButton(
        font = 'ui', 
        text = dialogueline.text, 
        script = runDialogueScript(dialogueline),
        colorInactive = scumm.Config.Colors.verb_unselected,
        colorActive = scumm.Config.Colors.verb_selected)

class RoomDialogue(room.Room):
    def __init__(self, id: str):
        width = engine.device_size[0]
        uisize = scumm.Config.ui_height
        height = engine.device_size[1] - uisize
        super().__init__(id, width, height)
        self.collide = False

        # add the main node     
        main = entity.Entity (tag='main')
        main.camera = cam.OrthoCamera(width, height, width, height, [0, uisize, width, height], tag='maincam')

        # add the dialogue node
        dialogue_node = entity.TextView(factory=makeDialogueButton, size=[320,56], fontSize=8, lines=6, deltax=26, tag='dialogue')
        dialogue_node.addComponent(compo.HotSpotManager())
        self.ref['main'] = main.children

        self.scene.append(main)
        self.scene.append(dialogue_node)
        self.engines.append(runner.Scheduler())
    def addItem(self, id: str, parent: str = 'main', **kwargs):
        entity = scumm.State.items[id].create(**kwargs)
        self.add (e = entity, ref =parent)


def startupRoomFullscreen(id: str):
    def f():
        if hasattr(engine.scripts.rooms, 'onstart_' + id):
            a = getattr(engine.scripts.rooms, 'onstart_' + id)()
            if a:
                example.play(a)
    return f

def startupRoomUI(id: str):
    def f():
        print ('starting up inventory')
        refresh_inventory()
        # check if room has a onstart script
        if hasattr(engine.scripts.rooms, 'onstart_' + id):
            a = getattr(engine.scripts.rooms, 'onstart_' + id)()
            if a:
                example.play(a)
    return f

class RoomFullscreen(room.Room):
    def __init__(self, id: str, width, height, collide = False):
        super().__init__(id, width, height)
        self.collide = collide
        camWidth = engine.device_size[0]
        camHeight = engine.device_size[1]
        main = entity.Entity (tag='main')
        main.camera = cam.OrthoCamera(width, height, camWidth, camHeight, [0, 0, camWidth, camHeight], tag='maincam')
        main.addComponent (compo.HotSpotManager(lmbclick=func.walkto))

        self.ref['main'] = main.children
        self.scene.append(main)
        
        # create a hotspot manager
        self.engines.append(runner.Scheduler())
        self.init.append(startupRoomFullscreen(id))


class RoomUI(room.Room):
    def __init__(self, id: str, width, height, collide = False):
        super().__init__(id, width, height)
        self.collide = collide
        uisize = scumm.Config.ui_height
        print ('uisize is '+str(uisize))
        camWidth = engine.device_size[0]
        camHeight = engine.device_size[1] - uisize

        # get the verbset used in this room
        verbset : scumm.VerbSet = scumm.Config.verbSets[0]
        defv : scumm.Verb = scumm.Config.getVerb (verbset.defaultVerb)
        scumm.Config.verb = verbset.defaultVerb
        #verbs = settings.monkey.config['verbs']
        default_verb = scumm.Config.getVerb
        # add the main node     
        main = entity.Entity (tag='main')
        main.camera = cam.OrthoCamera(width, height, camWidth, camHeight, [0, uisize, camWidth, camHeight], tag='maincam')
        main.addComponent (compo.HotSpotManager(lmbclick=func.walkto))
        #main.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, pos = [camWidth/2, 16, 0]))

        # add the ui node
        ui = entity.Entity (tag='ui')
        ui.camera = cam.OrthoCamera(camWidth, uisize, camWidth, uisize, [0, 0, camWidth, uisize], tag = 'uicam')
        ui.add (entity.Text(font='ui', text = defv.text, color = scumm.Config.Colors.current_action, 
            align = entity.TextAlignment.bottom, tag = 'current_verb', pos = [camWidth/2, 48, 0]))
        ui.addComponent (compo.HotSpotManager())
        inventory_node = entity.TextView (factory=makeInventoryButton, pos=(160,0),  size=(140,48), fontSize=8, lines=6, deltax=26, tag='inventory')
        inventory_node.addComponent(compo.HotSpotManager())

        # add the dialogue node
        dialogue_node = entity.TextView(factory=makeDialogueButton, size=[320,56], fontSize=8, lines=6, deltax=26, tag='dialogue')
        dialogue_node.addComponent(compo.HotSpotManager())

        row = 2
        count = 0
        for a in verbset.verbs:
            col = 1 + count // 4
            x = 2 + (col - 1) * 46
            verb : scumm.Verb = scumm.Config.getVerb(a)
            print ('here ' + a + ' ' + verb.text)
            ui.add (se.VerbButton(
                font = 'ui',
                verbId = a,
                colorInactive = scumm.Config.Colors.verb_unselected,
                colorActive = scumm.Config.Colors.verb_selected,
                align = entity.TextAlignment.bottomleft,
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
        self.scene.append(dialogue_node)
        self.scene.append(inventory_node)

        scumm.Config.resetVerb()
        
        # create a hotspot manager
        #self.engines.append(runner.HotSpotManager(lmbclick=func.walkto))
        self.engines.append(runner.Scheduler())
        self.init.append(startupRoomUI(id))


    def addItem(self, id: str, parent: str = 'main', **kwargs):
        inv = scumm.State.getCurrentInventory()
        if id in inv:
            return
        entity = scumm.State.items[id].create(**kwargs)
        self.add (e = entity, ref =parent)

    def addDynamicItems(self):
        roomId = self.id
        if roomId in scumm.State.room_items:
            for key, value in scumm.State.room_items[roomId].items():
                print ('creating dynamic item = ' + key)
                # get the item
                print(value)
                entity = scumm.State.items[key].create(**value)
                print ('focami ' + str(entity.pos[0]))
                self.add (e = entity, ref = value['parent'])
                #if key in engine.data['factories']:
                #    print ('found fac')
                #    print(value)
                #    entity = engine.data['factories'][key](**value)
                #    self.add (e=entity, ref=value['parent'])
                #else:
                #    print ('factory not found')
                # # get a shallow copy of item
                # item = engine.data['entities'][key]
                # # apply ajustments
                # for pk, pv in value.params.items():
                #     setattr(item, pk, pv)
                # self.add(e=item, ref = value.parent)
                # print('adding item ' + key)

