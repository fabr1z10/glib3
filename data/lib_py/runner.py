class KeyListener:
    def __init__(self):
        self.type = 'runner.keylistener'
        self.keys = []
    
    def addKey (self, key : int, func : Callable):
        self.keys.append ({ 'key': key, 'func': func })

def pippo(x, y):
    print ('clicked at ' + str(x) + ', ' + str(y))

class HotSpotManager:
    def __init__(self):
        self.type = 'runner.hotspotmanager'
        self.lmbclick = pippo