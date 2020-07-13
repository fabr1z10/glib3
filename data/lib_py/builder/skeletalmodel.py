from PIL import Image
import example
from lib_py.geom import vec2,vec3
from itertools import zip_longest

def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)
    
def ms1(x):
    from lib_py.engine import data

    print ('-------- generating skeletal model -----------')
    im = Image.open(example.dir+'/'+x['texture'])
    tex_height = im.size[1]
    print ('image height = ' + str(tex_height))     
    joint_data = {}
    root = ''
    out = {
        'type': 'asset.skeletalmodel',
        'texture': x['texture'],
        'joints': [],
        'polygons': [],
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

    keypoints = {}

    for k in x['joints']:
        jointId = k['id']
        keypoints[jointId] = {}
        isRoot = k.get('root', False)
        pos = k['pos']
        poly = k['poly'] 
        polyId = poly[0]
        parent = k.get('parent', None)
        joint_data [jointId] = {
            'root': isRoot,
            'pos': pos,
            'poly': polyId,
            'parent': parent,
            'children': []
        }
        if parent:
            joint_data[parent]['children'].append(jointId)
        print ('    root: ' + str(isRoot))
        print ('    pos: ' + str(pos))
        print ('    poly: ' + str(polyId))
        print ('    parent: ' + str(joint_data[jointId]['parent']))
        if isRoot:
            root = jointId
            root_joint_pos = vec3(pos[0], pos[1])
        joint_pos = vec3(pos[0], pos[1], pos[2])
        # generate polygon for this joint
        print ('reading mesh: ' + polyId)
        p = data['assets']['mesh'][polyId]
        po = {
            'id': jointId,
            'points': []
        }
        mesh_origin = vec2(p['origin'][0], p['origin'][1])
        indices = [0, 0, 0]
        for j in range(1, len(poly)):
            indices[j-1] = jmap[poly[j]]
        for vertex in grouper(p['points'], 5, 0):
            tex_coords = vec2(vertex[0], vertex[1])
            po['points'].extend( [
                joint_pos.x - root_joint_pos.x + (tex_coords.x - mesh_origin.x),
                -(joint_pos.y - root_joint_pos.y + (tex_coords.y - mesh_origin.y)),
                joint_pos.z - root_joint_pos.z,
                tex_coords.x,
                tex_coords.y,
                indices[0],
                indices[1],
                indices[2],
                vertex[2],
                vertex[3],
                vertex[4]])
        if 'keypoints' in p:
            for name, value in p['keypoints'].items():
                xk = joint_pos.x - root_joint_pos.x + (value[0] - mesh_origin.x)
                yk = -(joint_pos.y - root_joint_pos.y + (value[1] - mesh_origin.y))
                keypoints[jointId][name] = [xk, yk]

        out['polygons'].append(po)

    print ('keypoints:')

    if 'offset' in x:
        for k in x['offset']:
            joint = k['joint']
            id = k['keypoint']
            kp = keypoints[joint][id]
            out['offset'].append([joint, kp[0], kp[1]])

    l = [root]
    while l:
        currentJoint = l.pop(0)
        joint = joint_data[currentJoint]
        # get joint absolute position
        pos = vec3(l=joint['pos'])
        pos.y = tex_height - pos.y
        ppos = None
        if joint['parent'] is not None:
            ppos = vec3(l=joint_data[joint['parent']]['pos'])
            ppos.y = tex_height - ppos.y
        else:
            ppos = pos
        joint_data[currentJoint]['relpos'] = (pos - ppos)
        for child in joint['children']:
            l.append(child)

    for key, value in joint_data.items():
        print ('*** joint: ' + str(key) + ' ***')
        print ('pos: ' + str(value['pos']))
        print ('relative pos: ' + str(value['relpos']))
        print ('parent: ' + str(value['parent']))
        print ('mesh: ' + str(value['poly']))
        p = value['relpos']
        j = {
            'id': key,
            'pos': [p.x,p.y,p.z],
            'root': value['root']
        }
        if value['parent'] is not None:
            j['parent'] = value['parent']
        out['joints'].append(j)

    print(out)
    return out