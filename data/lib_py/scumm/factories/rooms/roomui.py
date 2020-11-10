import lib_py.engine as engine
import lib_py.scumm as scumm

from lib_py.entity import Entity
from lib_py.camera import OrthoCamera

def makeRoomUI(room):

    
    r = RoomUI()

# this is a room with UI verbs below and the main scene above
class RoomUI(room.Room):
    def __init__(self, id: str, width, height, collide = False, addui: bool = True, verbSetId : int = 0):
        super().__init__(id, width, height)
        self.collide = collide
        scumm.State.collision_enabled = collide
        uisize = scumm.Config.ui_height
        camWidth = engine.device_size[0]
        camHeight = engine.device_size[1] - uisize

        # get the verbset used in this room
        verbset : scumm.VerbSet = scumm.Config.verbSets[verbSetId]
        defv : scumm.Verb = scumm.Config.getVerb (verbset.defaultVerb)
        scumm.Config.verb = verbset.defaultVerb
        #verbs = settings.monkey.config['verbs']
        default_verb = scumm.Config.getVerb
                
        # add the main node     
        main = Entity (tag='main')
        main.camera = OrthoCamera(width, height, camWidth, camHeight, [0, uisize, camWidth, camHeight], tag='maincam')

        # add the ui node
        if addui:
            main.addComponent (compo.HotSpotManager(lmbclick=func.walkto))
            
            ui = entity.Entity (tag='ui')
            ui.camera = cam.OrthoCamera(camWidth, uisize, camWidth, uisize, [0, 0, camWidth, uisize], tag = 'uicam')
            ui.add (entity.Text(font='ui', text = defv.text, color = scumm.Config.Colors.current_action, 
                align = entity.TextAlignment.bottom, tag = 'current_verb', pos = [camWidth/2, 48, 0]))
            ui.addComponent (compo.HotSpotManager())
            inventory_node = entity.TextView (factory=makeInventoryButton, pos=(160,0),  size=(140,48), fontSize=8, lines=6, deltax=26, tag='inventory')
            inventory_node.addComponent(compo.HotSpotManager())

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
            self.scene.append(ui)
            self.scene.append(inventory_node)

            scumm.Config.resetVerb()
                    

        # add the dialogue node
        dialogue_node = entity.TextView(factory=makeDialogueButton, size=[320,56], fontSize=8, lines=6, deltax=26, tag='dialogue')
        dialogue_node.addComponent(compo.HotSpotManager())

		#ui.add (VerbButton (font='ui', text='Open', colorInactive = ScummConfig.Colors.verb_unselected, colorActive = ScummConfig.Colors.verb_selected, align = e.TextAlignment.bottomleft, pos = [0,0,0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.topleft, pos = [0, 56, 0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.bottomleft, pos = [0, 0, 0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.topright, pos = [320, 56, 0]))
		# ui.add (e.Text(font='ui', text=verbs[verbset[1]].text, color = [255, 255, 255, 255], align = e.TextAlignment.bottomright, pos = [320, 0, 0]))
		
        self.ref['main'] = main.children

        self.scene.append(main)
        self.scene.append(dialogue_node)

        
        
        # create a hotspot manager
        #self.engines.append(runner.HotSpotManager(lmbclick=func.walkto))
        self.engines.append(runner.Scheduler())
        if collide:
            #self.engines.append (runner.CollisionEngine(128, 128))
            ce = runner.CollisionEngine(128, 128)
            ce.addResponse(0, 1, runner.CollisionResponse(onenter=ciao))
            self.engines.append (ce)
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

