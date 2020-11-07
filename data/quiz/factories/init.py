from factories.rooms.default import defaultRoom
from lib_py.engine import data

def initFactories():
    
    data ['factories']['rooms'] = {
        'default': defaultRoom
    }

