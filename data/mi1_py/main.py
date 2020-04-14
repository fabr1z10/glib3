import example
import lib_py.engine as engine
import lib_py.scumm.scumm as scumm
import lib_py.scumm.functions as func
import lib_py.scumm.helper as helper
import lib_py.scumm.scripts as sscripts


engine.startUp()

engine.device_size = [320, 200]
engine.window_size = [640, 400]
engine.title = 'The secret of Monkey Island'
engine.room = 'lookout'

engine.addFont (engine.assets.Font('ui', './fonts/monkeysmall.ttf'))
#engine.addFont (engine.assets.Font('monkey', './fonts/MonkeyIsland-1990.ttf'))//
engine.addFont (engine.assets.Font('monkey', './fonts/arial.ttf'))

# configure scumm related stuff
scumm.Config.ui_height = 56
scumm.State.player = 'guybrush'

engine.loadSprites()
engine.loadText ('eng')

t = engine.data['strings']


# # add verbs and verb sets
scumm.Config.addVerb (scumm.Verb (id = 'open', text = t['ui']['open'], items=1, callback=helper.set_verb('open'), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][1]])))
scumm.Config.addVerb (scumm.Verb (id = 'close', text = t['ui']['close'], items=1, callback=helper.set_verb('close'), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'push', text = t['ui']['push'], items=1, callback=helper.set_verb('push' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][3]])))
scumm.Config.addVerb (scumm.Verb (id = 'pull', text = t['ui']['pull'], items=1, callback=helper.set_verb('pull' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][3]])))
scumm.Config.addVerb (scumm.Verb (id = 'walkto', text = t['ui']['walkto'], items=1, callback=helper.set_verb('walkto' ), handler = func.handler1))
scumm.Config.addVerb (scumm.Verb (id = 'pickup', text = t['ui']['pickup'], items=1, callback=helper.set_verb('pickup' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][5]])))
scumm.Config.addVerb (scumm.Verb (id = 'talkto', text = t['ui']['talkto'], items=1, callback=helper.set_verb('talkto' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'give', text = t['ui']['give'], items=1, callback=helper.set_verb('give' ), handler = func.handler1))
scumm.Config.addVerb (scumm.Verb (id = 'use', text = t['ui']['use'], items=1, callback=helper.set_verb('use' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'look', text = t['ui']['lookat'], items=1, callback=helper.set_verb('look' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][4]])))
scumm.Config.addVerb (scumm.Verb (id = 'turnon', text = t['ui']['turnon'], items=1, callback=helper.set_verb('turnon' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'turnoff', text = t['ui']['turnoff'], items=1, callback=helper.set_verb('turnoff' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))



scumm.Config.verbSets.append (scumm.VerbSet(verbs= ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give', 'use', 'look', 'turnon', 'turnoff'],
    defaultVerb='walkto'))

# sets door to closed
scumm.State.variables['door.village.scummbar'] = 'closed'

import mi1_py.data.items
import mi1_py.rooms.lookout
import mi1_py.rooms.village1
import mi1_py.rooms.scummbar