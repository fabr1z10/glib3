# a script is a graph whose nodes are actions

class Script:
    def __init__(self, uid: str = None, loop: int = None):
        self.id = uid
        self.actions = []
        self.edges = []
        self.map = {}
        self.loop = loop

    # add an action
    def add_action(self, action, id=None, after=None):
        iid = len(self.actions)
        if id is not None:
            self.map[id] = iid
        self.actions.append(action)
        if after:
            for aid in after:
                self.edges.append([self.map[aid], iid])
        else:
            # if after is not provided, we assum it goes after the last added action
            if iid > 0:
                self.edges.append([iid - 1, iid])


