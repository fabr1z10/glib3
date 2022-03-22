# a script is a graph whose nodes are actions

class Script:
    def __init__(self, uid: str = None, loop: int = None):
        self.id = uid
        self.actions = []
        self.edges = []
        self.map = {}
        self.loop = loop
        self.on_kill = None

    def set_loop(self, id):
        self.loop = self.map[id]

    # add an action
    def add_action(self, action, id=None, after=None):
        iid = len(self.actions)
        if id is not None:
            self.map[id] = iid
        self.actions.append(action)
        if after:
            print('STOCANE' + str(after))
            for aid in after:
                print('STOCANE' + str(aid))
                self.edges.append([aid, iid])
        else:
            # if after is not provided, we assum it goes after the last added action
            if iid > 0:
                self.edges.append([iid - 1, iid])


