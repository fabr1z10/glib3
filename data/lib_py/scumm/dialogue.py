from enum import Enum

import types

# class NodeStatus(Enum):
#     ACTIVE = 1
#     OPEN = 2
#     CLOSED = 3
#     SAME = 4

# class Line:
#     def __init__(self, text: str, script: callable, order: int=1):
#         self.node = None
#         self.order =order
#         self.text = text
#         self.script = script

# a dialogue line contains:
class DialogueNode:
    # next_group: the next group of lines to show. -1 to exit dialogue
    def __init__(self, id: int, text: str = '', script: callable = None, active = True, nextId = 0, closeNodes = [], activateNodes = [], order=1):
        self.id = id
        self.text = text
        self.script = script
        self.dialogue = None
        self.active = active
        self.nextId = nextId
        self.closeNodes = closeNodes
        self.order = order
        self.activateNodes = activateNodes

    def isActive(self):
        if callable(self.active):
            return self.active()
        return self.active


# A dialogue is a graph-like structure.
# every node has one or more lines. 
# when we start a dialogue, we start exploring the graph until we get to nodes in state: ACTIVE
# an active node means we need to add LINES into the UI.
# a node may be also OPEN, this means that this node has already been explored and we need to go further down
# a node may be CLOSED; in this case we stop the depth -a analysis 
class Dialogue:
    def __init__(self, id: str, strings: list):
        self.id = id
        self.nodes = {}
        self.edges = {}
        self.onStart = None
        self.onEnd = None
        self.current = 0
        self.strings = strings
        self.addNode(DialogueNode(0))

    def reset(self):
        self.current = 0

    def addStartScript(self, script):
        self.onStart = types.MethodType(script, self)

    def addEndScript(self, script):
        self.onEnd = types.MethodType(script, self)

    def openNode(self, node : DialogueNode):
        # remove node id from frontier
        self.frontier.remove(node.id)
        print ('removed ' + str(node.id))
        print(str(self.frontier))
        if node.id in self.edges:
            for nn in self.edges[node.id]:
                self.frontier.append(nn)
        print ('opened node ' + str(node.id) + ', now frontier is ' + str(self.frontier))

    def getLines(self):
        print ('** current node: ' + str(self.current))
        lines = []
        if self.current not in self.edges:
            return lines
        outEdges = self.edges[self.current]
        for outEdge in outEdges:
            head : DialogueNode = self.nodes[outEdge]
            active = head.isActive()
            print (str(outEdge) + ' is active ' + str(active))
            if active:
                lines.append(head)
        lines.sort(key=lambda x: x.order)
        return lines

    def addNode (self, node : DialogueNode):
        node.dialogue = self
        self.nodes[node.id] = node



    def add(self, id: int, script, nextId, active, closeNodes = [], actNodes = [], parent = [0], order=1):
        self.addNode(DialogueNode(
            id = id, 
            text = self.strings[id], 
            script = script, 
            active = active, 
            nextId = nextId, 
            closeNodes = closeNodes, 
            activateNodes= actNodes,
            order = order))
        for p in parent:
            if p not in self.edges:
                self.edges[p] = []
            self.edges[p].append(id)

