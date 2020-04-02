


class Walk:
    def __init__(self, pos : list, id = None, tag = None):
        self.type = 'scumm.action.walk'
        self.id = id
        self.tag = tag
        self.pos = pos