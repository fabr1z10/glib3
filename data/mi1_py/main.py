import sys

import example
import lib_py.engine as engine
import lib_py.entity as entity

import lib_py.scumm.scumm as scumm
import lib_py.scumm.functions as func
import lib_py.scumm.scripts as sscripts
#import mi1_py.text.eng.text as text

engine.addShader (engine.ShaderType.unlit_textured)
engine.addShader (engine.ShaderType.unlit_color)
engine.addShader (engine.ShaderType.text)

engine.device_size = [320, 200]
engine.window_size = [640, 400]
engine.title = 'The secret of Monkey Island'
engine.room = 'lookout'

example.init(example.what)


engine.addFont (engine.assets.Font('ui', './fonts/monkeysmall.ttf'))
engine.addFont (engine.assets.Font('monkey', './fonts/MonkeyIsland-1990.ttf'))

# configure scumm related stuff
scumm.Config.ui_height = 56


engine.loadSprites()
engine.loadText ('eng')

t = engine.data['strings']

import mi1_py.items

# e.strings = text.strings

# # add verbs and verb sets
scumm.Config.addVerb (scumm.Verb (id = 'open', text = t['ui']['open'], items=1, callback=func.set_verb('open'), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][1]])))
scumm.Config.addVerb (scumm.Verb (id = 'close', text = t['ui']['close'], items=1, callback=func.set_verb('close'), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'push', text = t['ui']['push'], items=1, callback=func.set_verb('push' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][3]])))
scumm.Config.addVerb (scumm.Verb (id = 'pull', text = t['ui']['pull'], items=1, callback=func.set_verb('pull' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][3]])))
scumm.Config.addVerb (scumm.Verb (id = 'walkto', text = t['ui']['walkto'], items=1, callback=func.set_verb('walkto' ), handler = func.handler1))
scumm.Config.addVerb (scumm.Verb (id = 'pickup', text = t['ui']['pickup'], items=1, callback=func.set_verb('pickup' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][5]])))
scumm.Config.addVerb (scumm.Verb (id = 'talkto', text = t['ui']['talkto'], items=1, callback=func.set_verb('talkto' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'give', text = t['ui']['give'], items=1, callback=func.set_verb('give' ), handler = func.handler1))
scumm.Config.addVerb (scumm.Verb (id = 'use', text = t['ui']['use'], items=1, callback=func.set_verb('use' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'look', text = t['ui']['lookat'], items=1, callback=func.set_verb('look' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][4]])))
scumm.Config.addVerb (scumm.Verb (id = 'turnon', text = t['ui']['turnon'], items=1, callback=func.set_verb('turnon' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))
scumm.Config.addVerb (scumm.Verb (id = 'turnoff', text = t['ui']['turnoff'], items=1, callback=func.set_verb('turnoff' ), handler = func.handler1,
    default_action = sscripts.say( lines = [t['defaultactions'][2]])))



scumm.Config.verbSets.append (scumm.VerbSet(verbs= ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give', 'use', 'look', 'turnon', 'turnoff'],
    defaultVerb='walkto'))

# # add fonts

# # add spritemodels

# e.config['verbs'] = {
#     'open': scumm.Verb (text = e.strings['ui']['open'], items = 1),
#     'close': scumm.Verb (text = e.strings['ui']['close'], items = 1),
#     'push': scumm.Verb (text = e.*strings['ui']['push'], items = 1),
#     'pull': scumm.Verb (text = e.strings['ui']['pull'], items = 1),
#     'walkto': scumm.Verb (text = e.strings['ui']['walkto'], items = 1),
#     'pickup': scumm.Verb (text = e.strings['ui']['pickup'], items = 1),
#     'talkto': scumm.Verb (text = e.strings['ui']['talkto'], items = 1),
#     'give': scumm.Verb (text = e.strings['ui']['close'], items = 2),
# }

# e.config['verbset'] = [
#     [ ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give'], 'walkto' ]
# ]


# settings.monkey = e


# settings.monkey.title = 'The secret of Monkey Island'

# # load rooms
import mi1_py.rooms.lookout

