# a dialogue line contains:
class DialogueLine:
    # next_group: the next group of lines to show. -1 to exit dialogue
    def __init__(self, text: str, script:callable, deact_after_use: bool, next_group: int, act_lines :list=[], active: bool = True):
        self.dialid = ''
        self.text = text
        self.script = script
        self.active = active
        self.next_group = next_group
        self.deact_after_use = deact_after_use
        self.act_lines = act_lines

class Dialogue:
    def __init__(self, id: str):
        self.id = id
        self.lines = {}
        self.choice = {}

    def getActiveLines (self, choice : int):
        lines = []
        for line in self.choice[choice]:
            if self.lines[line].active:
                lines.append(self.lines[line])
        return lines

    def addLine (self, id: int, choice: int, dl : DialogueLine):
        if choice not in self.choice:
            self.choice[choice] = []
        self.choice[choice].append(id)
        dl.dialid = self.id
        self.lines[id] = dl
