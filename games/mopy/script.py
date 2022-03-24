# a script is a graph whose nodes are actions

import mopy


class ScriptDesc:
    def __init__(self, id):
        self.nodes = dict()
        self.arcs = dict()
        self.id = id
        self.loop = None

    def add_node(self, id: int, args: list):
        self.nodes[id] = args

    def add_arc(self, id0, id1):
        if id0 not in self.arcs:
            self.arcs[id0] = list()
        self.arcs[id0].append(id1)

    def make(self, script_args= []):
        # creates an actual script
        s = Script(loop=self.loop)
        import mopy.scumm.scriptmake as sm
        current = 0
        ia = dict()
        for node, args in self.nodes.items():
            opcode = args[0].lower()
            factory = sm.script_factories.get(opcode)
            if not factory:
                print('mmh cannot find opcode: ' + str(opcode))
                exit(1)
            pargs = sm.proc_args(args[1:], script_args)
            print('processed args: ' + str(pargs))
            e = factory(pargs, s, current, script_args)
            ia[node] = (current, e)
            current = e+1

        print(ia)
        print(self.arcs)
        for tail, heads in self.arcs.items():
            for a1 in heads:
                s.add_edge(ia[tail][1], ia[a1][0])
        return s


class ScriptBuilder:
    def __init__(self, id):
        self.desc = []
        self.id = id

    def make(self, script_args=[]):
        # seect which desc to use
        index = 0
        if len(self.desc) > 1:
            f = getattr(mopy.monkey.engine.data.game, '_select_'+ self.id)
            if f:
                index = f(script_args)
        return self.desc[index].make(script_args)

class IndirectScriptBuilder:
    def __init__(self, builder, args):
        self.sb = builder
        self.args = args

    def make(self, script_args=[]):
        print('ciao '  + str(self.sb))
        print ('args = ' + str(script_args))
        if self.args:
            script_args.extend(self.args)
        print('sticane = ' + str(script_args))
        return self.sb.make(script_args)




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
        print('after = ' + str(after))
        iid = len(self.actions)
        print('after = ' + str(after))
        if id is not None:
            self.map[id] = iid
        if id and self.loop == id:
            self.loop = iid
        self.actions.append(action)
        if after is not None:
            if isinstance(after, int):
                after = [after]
            print('ok ' + str(after))
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


