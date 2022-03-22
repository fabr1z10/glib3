# a script is a graph whose nodes are actions

class ScriptDesc:


    def __init__(self, action, item):
        self.nodes = dict()
        self.arcs = dict()
        self.action = action
        self.item = item

    def id(self):
        return self.action + '_' + self.item

    def add_node(self, id: int, args: list):
        self.nodes[id] = args

    def add_arc(self, id0, id1):
        if id0 not in self.arcs:
            self.arcs[id0] = list()
        self.arcs[id0].append(id1)

    def make(self):
        # creates an actual script
        s = Script()
        import mopy.scumm.scriptmake as sm
        current = 0
        ia = dict()
        for node, args in self.nodes.items():
            opcode = args[0].lower()
            factory = sm.script_factories.get(opcode)
            if not factory:
                print('mmh cannot find opcode: ' + str(opcode))
                exit(1)
            e = factory(self.item, args, s, current)
            ia[node] = (current, e)
            current = e+1

        print(ia)
        print(self.arcs)
        for tail, heads in self.arcs.items():
            for a1 in heads:
                s.add_edge(ia[tail][1], ia[a1][0])
        return s







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
        if id and self.loop == id:
            self.loop = iid
        self.actions.append(action)
        if after:
            for aid in after:
                self.edges.append([aid, iid])
        # else:
        #     # if after is not provided, we assum it goes after the last added action
        #     if iid > 0:
        #         self.edges.append([iid - 1, iid])
        return iid

    def add_edge(self, id0, id1):
        print('adding edge from ' + str(id0) + ' to ' + str(id1))
        self.edges.append([id0, id1])

    add = add_action


