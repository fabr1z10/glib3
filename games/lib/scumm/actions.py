from script import Script
import engine
import example
import random

class Walk:
    def __init__(self, pos : list, id = None, tag = None):
        self.type = 'scumm.action.walk'
        self.id = id
        self.tag = tag
        self.pos = pos

class Turn:
    def __init__(self, dir : str, id = None, tag = None):
        self.type = 'scumm.action.turn'
        self.id = id
        self.tag = tag
        self.dir = dir


class Say:
    def __init__(self, lines: list, font: str, id = None, tag = None, animate = True):
        self.type = 'scumm.action.say'
        self.font = font
        self.id = id
        self.tag = tag
        self.lines = lines
        self.animate = animate

class SetWall:
    def __init__(self, walkarea: str, wall_id: int, enabled: bool):
        self.type = 'scumm.action.enable_block'
        self.walkarea = walkarea
        self.wall = wall_id
        self.active = enabled
