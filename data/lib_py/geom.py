

class vec2:
    def __init__(self, x=0, y=0, l=None):
        if l is not None:
            self.x = l[0]
            self.y = l[1]
        else:
            self.x = x
            self.y = y

    def __add__(self, o):
        return vec2(self.x + o.x, self.y + o.y)
    def __sub__(self, o):
        return vec2(self.x - o.x, self.y - o.y)
    def __iadd__(self, o):
        self.x += o.x
        self.y += o.y
        return self

    def __str__(self):
        return str((self.x, self.y))

class vec3:
    def __init__(self, x=0, y=0, z=0,l=None):
        if l is not None:
            self.x = l[0]
            self.y = l[1]
            self.z = l[2]
        else:
            self.x = x
            self.y = y
            self.z = z

    def __add__(self, o):
        return vec3(self.x + o.x, self.y + o.y, self.z+o.z)
    
    def __sub__(self, o):
        return vec3(self.x - o.x, self.y - o.y, self.z-o.z)

    def __iadd__(self, o):
        self.x += o.x
        self.y += o.y
        self.z +=o.z
        return self

    def __str__(self):
        return str((self.x, self.y, self.z))