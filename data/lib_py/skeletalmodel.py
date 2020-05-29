
class Bone:
    def __init__(self, gfx: str, id: str, quad):
        self.quad = quad
        self.gfx = gfx
        self.origin = origin
        self.pos = {}



class SkeletalModel:
    def __init__(self, a, data):
        self.type = 'asset.skeleton'
        #self.gfx = a['gfx']
        print ('ciaociao')
        self.bones = []
        self.animations = {}
        mp = {}
        bones = data['assets']['skeletalmodels']['bones']
        anims = data['assets']['skeletalmodels']['anims']
        print ('ciao ciao ' + str(a))
        if 'boxes' in a:
            self.boxes = a['boxes']
        for key, value in a['anims'].items():
            animId = value['id']
            print (animId + ' poooo')
            anim = anims[animId]
            cast = value.get('cast', [-1, 0])
            self.animations[key] = {
                'anim': anim,
                'box': value.get('box',-1),
                'cast': cast[0],
                'cast_time': cast[1]
            } 
        for key, value in a['bones'].items():
            bone = bones[value['id']]
            mp[key] = value['id']
            b = {
                'id': key,
                'quad': bone.get('quad'),
                'gfx': bone.get('gfx'),
                'origin': bone.get('origin'),                
                'z': value.get('z', 0)
            }
            #print (b)
            if 'parent' in value:                
                parentId = value['parent'][0]
                parentPos = value['parent'][1]
                b['parent'] = parentId
                # get parent node
                parentBone : Bone = bones[mp[parentId]] 
                b['pos'] = parentBone['pos'][parentPos]
            self.bones.append(b)
        
        

    
