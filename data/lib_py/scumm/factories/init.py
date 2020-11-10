import lib_py.engine as engine

from lib_py.scumm.factories.rooms import makeRoomUI

def init():
    engine.addRoomFactory ('ui', makeRoomUI)
    
    print ('ciao')