class Asset:
    def __init__(self, id : str):
        self.id = id


class Font(Asset):
    def __init__(self, id : str, file: str):
        super().__init__(id)
        self.type = 'font'
        self.file = file

class SpriteModel(Asset):
    def __init__(self, id : str):
        super().__init__(id)

