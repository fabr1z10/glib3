from enum import Enum

class NodeStatus(Enum):
    ACTIVE = 1
    OPEN = 2
    CLOSED = 3

class Line:
    def __init__(self, text: str, script: callable, order: int=1):
        self.node = None
        self.order =order
        self.text = text
        self.script = script

# a dialogue line contains:
class DialogueNode:
    # next_group: the next group of lines to show. -1 to exit dialogue
    def __init__(self, id: str, lines, status: NodeStatus, nextStatus : NodeStatus, resume: bool, active = True, closeNodes = []):
        self.id = id
        self.dialogue = None
        self.status = status
        self.nextStatus = nextStatus
        self.lines = lines
        self.resume = resume
        self.active = active
        self.closeNodes = closeNodes
        for line in self.lines:
            line.node = self

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
    def __init__(self, id: str):
        self.id = id
        self.nodes = {}
        self.edges = {}
        self.onStart = None
        self.onEnd = None
        self.frontier = []

    def reset(self):
        self.frontier = ['init']

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
        print ('frontier is = ' + str(self.frontier))
        l = self.frontier
        self.frontier = []
        lines = []
        while l:
            p = l.pop(0)
            node : DialogueNode = self.nodes[p]
            if node.status == NodeStatus.ACTIVE and node.isActive():
                for line in node.lines:
                    lines.append(line)
                self.frontier.append(p)
            elif node.status == NodeStatus.OPEN:
                if p in self.edges:
                    for nn in self.edges[p]:
                        l.append(nn)
        print ('new     frontier is = ' + str(self.frontier))
        lines.sort(key=lambda x: x.order)
        for l in lines:
            print (l.order)
        return lines

    def addNode (self, node : DialogueNode):
        node.dialogue = self
        self.nodes[node.id] = node

    def addEdge (self, tail: str, head: str):
        if tail not in self.edges:
            self.edges[tail] = []
        self.edges[tail].append(head)