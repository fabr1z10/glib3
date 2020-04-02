# a script is a graph whose nodes are actions

class Script:
    def __init__(self):
        self.actions = []
        self.edges = []
        self.map = {}        
    # add an action
    def addAction (self, action, id = None, after = None):
        iid = len(self.actions)
        if id:
            self.map[id] = iid
        self.actions.append(action)
        if after:
            for aid in after:
                self.edges.append([self.map[aid], iid])
                
    

