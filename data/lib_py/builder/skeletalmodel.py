from PIL import Image
import example
from lib_py.geom import vec2,vec3
from itertools import zip_longest
import math
def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)
    

class Joint:
    def __init__(self, id, poly: str, z = 0, posId = None, parent = None):
        self.id = id
        self.parent = parent
        self.root = (parent is None)
        self.posId = posId
        self.relpos = None
        self.modelpos = None
        self.children = []
        self.z = z
        self.scale = 1
        self.poly = poly

    def __str__(self):
        return ('\npoly = ' + self.poly + '\nparent = ' + str(self.parent) + '\nrelpos = ' + str(self.relpos) + '\nmodelpos = ' + str(self.modelpos) +']\n')
    def __repr__(self):
        return str(self)

def getValue (a, args):
    if isinstance(a, str) and a[0] == '@':
        if a[1:] not in args:
            raise BaseException ('template requires: ' + a[1:])
        return args[a[1:]]
    return a


# create a skeletal model   
def ms1(x, args = {}):
    from lib_py.engine import data

    #print ('-------- generating skeletal model -----------')
    # I have no longer one tex per model
    # but I want to have possibly more than one texture (one tex per poly)! more flexible
    #im = Image.open(example.dir+'/'+x['texture'])
    #tex_height = im.size[1]
    #print ('image height = ' + str(tex_height))     
    joint_data = {}
    root = ''
    out = {
        'type': 'asset.skeletalmodel',
        #'texture': x['texture'],
        'joints': [],
        'polygons': [],
        #'boxes': x['boxes'],
        'animations': x['animations'],
        'offset': []
    }
    root_joint_pos = vec3()
    # 1st joint must be root joint!!!
    # create a map that associates bone name with its index
    jmap = {}
    jc = 0
    for k in x['joints']:
        jmap[k['id']] = jc
        jc += 1

    #print (jmap)

    keypoints = {}

    # store here left, right, bottom, top for each bone
    metrics = {}
    xmin = math.inf
    xmax = -math.inf
    ymin = math.inf
    ymax = -math.inf
    
    # first of all you need for each joint to compute:
    # 1. its position relative to parent
    # 2. its position in model coordinates (origin in root)
    for k in x['joints']:
        jointId = k['id']
        keypoints[jointId] = {}
        isRoot = k.get('root', False)
        if isRoot:
            root = jointId
        pos = k['pos']
        poly = k['poly'] 
        polyId = getValue(poly[0], args)
        parent = k.get('parent', None)
        z = k.get('z', 0)
        #print ('zzz = ' + jointId + str(z))
        j = Joint(jointId, polyId, parent = parent, posId = pos, z = z)
        j.scale = getValue(k.get('scale', 1), args)
        joint_data [jointId] = j        
        if parent is not None:
            joint_data[parent].children.append(jointId)
        p = data['assets']['mesh'][polyId]
        mesh_origin = vec2(p['origin'][0], p['origin'][1])
        keypoints[jointId]['origin'] = mesh_origin
        if 'keypoints' in p:
            for name, value in p['keypoints'].items():
                xk = value[0]
                yk = value[1]
                keypoints[jointId][name] = vec2(xk, yk)

    l = [root]
    while l:
        currentJoint = l.pop(0)
        joint : Joint = joint_data[currentJoint]
        # compute position relative to parent
        if joint.parent is None:
            joint.relpos = vec3 (0, 0, 0)
            joint.modelpos = vec3 (0, 0, 0)
        else:
            parent = joint.parent
            pos = joint.posId
            p = keypoints[parent][pos]
            o = keypoints[parent]['origin']
            #print ('this joint ' + joint.id)
            #print ('pos id = ' + str(p))
            #print ('parent origin = ' + str(o))
            relpos = p - o
            # flip y as these are still tex coords
            joint.relpos = vec3(relpos.x, -relpos.y, 0)
            joint.modelpos = joint_data[parent].modelpos + joint.relpos
            joint.modelpos.z= 0
        for child in joint.children:
            l.append(child)
    #joint_data['modelpos'] = 
    #     pos = vec3(l=joint['pos'])
    #     pos.y = tex_height - pos.y
    #     ppos = None
    #     if joint['parent'] is not None:
    #         ppos = vec3(l=joint_data[joint['parent']]['pos'])
    #         ppos.y = tex_height - ppos.y
    #     else:
    #         ppos = pos
    #     joint_data[currentJoint]['relpos'] = (pos - ppos)
    #     for child in joint['children']:
    #         l.append(child)


    for k in x['joints']:
        jointId = k['id']
        joint : Joint = joint_data[jointId]
        joint_pos = joint_data[jointId].modelpos
        #print ('z of ' + jointId +' is ' + str(joint_pos.z))
        bone_xmin = math.inf
        bone_xmax = -math.inf
        bone_ymin = math.inf
        bone_ymax = -math.inf        

        # generate polygon for this joint
        #print ('reading mesh: ' + joint.poly)
        p = data['assets']['mesh'][joint.poly]
        po = {
            'id': jointId,
            'points': [],
            # add one tex per polygon!
            'texture': p['texture']
        }
        mesh_origin = vec2(p['origin'][0], p['origin'][1])
        indices = [0, 0, 0]
        poly = k['poly'] 
        #print ('scale for ' + jointId + ' is ' + str(scale))
        for j in range(1, len(poly)):
            indices[j-1] = jmap[poly[j]]
        #print ('indices to ' + jointId + ' : ' + str(indices))
        for vertex in grouper(p['points'], 5, 0):
            tex_coords = vec2(vertex[0], vertex[1])
            vx = joint_pos.x + joint.scale*(tex_coords.x - mesh_origin.x) 
            vy = joint_pos.y - joint.scale*(tex_coords.y - mesh_origin.y)
            #vx = joint_pos.x - root_joint_pos.x + (tex_coords.x - mesh_origin.x) 
            #vy = -(joint_pos.y - root_joint_pos.y + (tex_coords.y - mesh_origin.y))
            xmin = min(vx,xmin)
            xmax = max(vx,xmax)
            ymin = min(vy,ymin)
            ymax = max(vy,ymax)
            bone_xmin = min(vx,bone_xmin)
            bone_xmax = max(vx,bone_xmax)
            bone_ymin = min(vy,bone_ymin)
            bone_ymax = max(vy,bone_ymax)
            po['points'].extend( [
                vx,
                vy,
                joint.z,
                tex_coords.x,
                tex_coords.y,
                indices[0],
                indices[1],
                indices[2],
                vertex[2],
                vertex[3],
                vertex[4]])
        #keypoints[jointId]['origin'] = [mesh_origin.x, mesh_origin.y]
        #if 'keypoints' in p:
        #    for name, value in p['keypoints'].items():
        #        xk = joint_pos.x - root_joint_pos.x + (value[0] - mesh_origin.x)
        #        yk = -(joint_pos.y - root_joint_pos.y + (value[1] - mesh_origin.y))
        #        keypoints[jointId][name] = [xk, yk]
        metrics[jointId+'_xmin'] = bone_xmin
        metrics[jointId+'_xmax'] = bone_xmin
        metrics[jointId+'_ymin'] = bone_ymin
        metrics[jointId+'_ymax'] = bone_ymax
        metrics[jointId+'_width'] = bone_xmax-bone_xmin
        metrics[jointId+'_height'] = bone_ymax-bone_ymin
        out['polygons'].append(po)

    #print (metrics)
    if 'offset' in x:
        for k in x['offset']:
            jointId = k['joint']
            id = k['keypoint']
            kp = keypoints[jointId][id]
            kpo = keypoints[jointId]['origin']
            joint = joint_data[jointId]
            #scale = joint_data['scale']
            #print ('michia ' + jointId + ' ' + str(scale))
            #print (str(kp.x) + '..' + str(kpo.x))
            #print (str(kp.y) + '..' + str(kpo.y))
            #print (joint.modelpos.x)
            #print (joint.modelpos.y)
            xx = joint.modelpos.x + joint.scale* (kp.x - kpo.x)
            yx = joint.modelpos.y - joint.scale*(kp.y - kpo.y)
            #print ('cazzo pene = ' + str(xx))
            #print ('cazzo pene = ' + str(yx))
            out['offset'].append([jointId, xx, yx])

    for k in x['joints']:
        # maintain the same order!!!
        jointId = k['id']
        joint = joint_data[jointId]
        p = joint.relpos
        j = {
            'id': jointId,
            'pos': [p.x, p.y, p.z],
            'root': joint.root
        }
        if joint.parent is not None:
            j['parent'] = joint.parent
        out['joints'].append(j)
 
    # for key, value in joint_data.items():
    #     p = value.relpos
    #     j = {
    #         'id': key,
    #         'pos': [p.x, p.y, p.z],
    #         'root': value.root
    #     }
    #     if value.parent is not None:
    #         j['parent'] = value.parent
    #     out['joints'].append(j)

    metrics['xmin'] = xmin
    metrics['xmax'] = xmax
    metrics['ymin'] = ymin
    metrics['ymax'] = ymax
    metrics['width'] = xmax-xmin
    metrics['height'] = ymax -ymin
    #print('metrics:')
    #print(metrics)

    # set the boxes
    bx = {
        'anim': {},
        'attack': []
    }
    if 'boxes' in x:
        if 'anim' in x['boxes']:
            for key, value in x['boxes']['anim'].items():
                bx['anim'][key] = [eval(value[0]), eval(value[1])]
        if 'attack' in x['boxes']:
            for value in x['boxes']['attack']:
                bx['attack'].append({
                    'anim': value['anim'],
                    't': value['t'],
                    'box': [
                        eval(value['box'][0]),
                        eval(value['box'][1]),
                        eval(value['box'][2]),
                        eval(value['box'][3])]
                })
    #print ('ciacwrvpojreoigje')                
    #print(bx)        
    out['boxes'] = bx
    out['metrics'] = metrics
    #print(out)
    return out