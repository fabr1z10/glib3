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
import lib_py.actions as act
import lib_py.scumm.actions as scact

from lib_py.script import Script
import example

def runDialogueScript(s):
    def f(x, y, obj = None):
        dial = example.get('dialogue')
        dial.clearText()
        # check if there's any script to run
        a = Script()
        ds = s.script()
        if ds:
            a.addAction(act.RunScript(s = ds))
        if s.next_group == -1:
            a.addAction(scact.EndDialogue())
        else:
            a.addAction(scact.StartDialogue(s.dialid, group=s.next_group))
        example.play(a)
    return f

def makeDialogueButton(dialogueline):
    return se.DialogueButton(
        font = 'ui', 
        text = dialogueline.text, 
        script = runDialogueScript(dialogueline),
        colorInactive = scumm.Config.Colors.verb_unselected,
        colorActive = scumm.Config.Colors.verb_selected)



class RoomUI(room.Room):
    def __init__(self, id: str, width, height, collide = False):
        super().__init__(id, width, height, collide)
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

        # create a hotspot manager
        #self.engines.append(runner.HotSpotManager(lmbclick=func.walkto))
        self.engines.append(runner.Scheduler())
    def addDynamicItems(self):
        roomId = self.id
        for key, value in scumm.State.room_items[roomId].items():
            print ('creating dynamic item = ' + key)
            # get a shallow copy of item
            item = engine.data['entities'][key]
            # apply ajustments
            for pk, pv in value.params.items():
                setattr(item, pk, pv)
            self.add(e=item, ref = value.parent)
            print('adding item ' + key)

