import sys

import lib_py.engine as engine
import lib_py.scumm.scumm as scumm
import mi1_py.text.eng.text as text

engine.addShader (engine.ShaderType.unlit_textured)
engine.addShader (engine.ShaderType.unlit_color)
engine.addShader (engine.ShaderType.text)

engine.device_size = [320, 200]
engine.window_size = [640, 400]
engine.title = 'The secret of Monkey Island'
engine.room = 'lookout'

engine.addFont (engine.assets.Font('ui', './fonts/monkeysmall.ttf'))
# configure scumm related stuff
scumm.Config.ui_height = 56

# sys.path.append('../data')

# import lib_py.scumm as scumm
# import lib_py.engine as engine

# import settings
# import text.eng.text as text
# import example

# example.what.prova()

# e = engine.Engine(deviceSize=[320,200], windowSize=[640,400], uiHeight = 56, startRoom='lookout')


engine.data['strings'] = text.strings
# e.strings = text.strings

# # add verbs and verb sets
scumm.Config.addVerb (scumm.Verb (id = 'open', text = text.strings['ui']['open'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'close', text = text.strings['ui']['close'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'push', text = text.strings['ui']['push'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'pull', text = text.strings['ui']['pull'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'walkto', text = text.strings['ui']['walkto'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'pickup', text = text.strings['ui']['pickup'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'talkto', text = text.strings['ui']['talkto'], items=1))
scumm.Config.addVerb (scumm.Verb (id = 'give', text = text.strings['ui']['give'], items=1))


scumm.Config.verbSets.append (scumm.VerbSet(verbs= ['open', 'close', 'push', 'pull', 'walkto', 'pickup'],
    defaultVerb='walkto'))

# # add fonts

# # add spritemodels

# e.config['verbs'] = {
#     'open': scumm.Verb (text = e.strings['ui']['open'], items = 1),
#     'close': scumm.Verb (text = e.strings['ui']['close'], items = 1),
#     'push': scumm.Verb (text = e.strings['ui']['push'], items = 1),
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

