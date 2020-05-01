import lib_py.scumm.scumm as s
import lib_py.entity as entity
import lib_py.components as compo
import lib_py.scumm.components as sc
import lib_py.shape as sh
import lib_py.scumm.functions as sf


#import lib_py.scumm.scumm as scumm


import example

def change_color(color):
    def f(e : example.Wrap1):
        e.setColor(color)
    return f    

def set_verb(verbId):
    def f(x, y, e : example.Wrap1):
        s.Config.verb = verbId
        s.Config.item1 = ''
        s.Config.item2 = ''
        update_current_action()
    return f

def update_current_action():
    a : example.Wrap1 = example.get('current_verb')
    verb = s.Config.getVerb(s.Config.verb)
    text = verb.text
    if s.Config.item1:
        item = s.State.items[s.Config.item1]
        text += ' ' + item.text
    a.setText (text)

def hoverOn(obj):
    def f(item):
    	#local actionfo = scumm.state.actionInfo
        if not s.Config.item1:
            s.Config.item1 = obj
        else:
            print ('suca')
            #local verb = scumm.func.getCurrentVerb()
            #if (verb.objects > 1 and actionInfo.obj1 ~= obj) then
            #    actionInfo.obj2 = obj
            #end
        update_current_action()
    return f

def hoverOff(obj):
    if s.Config.item2:
        s.Config.item2 = ''
    else:
        # set obj1 to nil unless we are waiting for 2nd object
        #if (actionInfo.selectSecond == false) then
        s.Config.item1 = ''
    update_current_action()

class BackgroundItem(entity.Entity):
    def __init__(self, image = None, tag = None, pos = [0, 0, 0]):
        super().__init__(tag, pos)
        self.addComponent (compo.Gfx(image=image))

class VerbButton(entity.Text):
    def __init__(self, font: str, verbId: str, colorInactive, colorActive, align: entity.TextAlignment = entity.TextAlignment.topleft, tag=None, pos=[0,0,0]):
        verb = s.Config.getVerb(verbId)
        super().__init__(font, verb.text, colorInactive, align, tag, pos)          
        self.addComponent(compo.HotSpot(
            shape = None,
            onenter = change_color(colorActive), 
            onleave = change_color(colorInactive),
            onclick = verb.callback )) 

class DialogueButton(entity.Text):
    def __init__(self, font: str, text: str, colorInactive, colorActive, align: entity.TextAlignment = entity.TextAlignment.bottomleft, 
        script: callable = None, tag=None, pos=[0,0,0]):
        super().__init__(font, text, colorInactive, align, tag, pos)          
        self.addComponent(compo.HotSpot(
            shape = None,
            onenter = change_color(colorActive), 
            onleave = change_color(colorInactive),
            onclick = script )) 

class WalkArea(entity.Entity):
    def __init__(self, shape, depth = None, scale = None, priority : int = 0, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        self.addComponent(sc.Walkarea(shape = shape, depth=depth, scale = scale))
        #self.shape = shape
        #self.depth = depth
        #self.priority = priority

class Sprite(entity.Entity):
    def __init__(self, model: str = None, anim : str = None, item : str = None, tag = None, pos = [0,0,0]):
        super().__init__(tag, pos)
        if not tag:
            self.tag = item
        if model is not None:
            self.type = 'sprite'
        self.model = model
        self.anim = anim
        if item:
            it : scumm.Item = s.State.items[item]
            self.addComponent(compo.HotSpot(
                shape = sh.Rect(width=it.width, height=it.height, offset = it.offset),
                priority=it.priority,
                onenter = hoverOn(item), 
                onleave = hoverOff,
                onclick = sf.run_action))

class Character(Sprite):
    def __init__(self, model: str, speed:float, dir:str, state:str, text_color : list, text_offset : list = [0, 60], item: str=None, anim: str = None, tag = None, pos = [0,0,0]):
        super().__init__(model = model, item=item,anim= anim, tag=tag, pos=pos)
        self.__charcomp = sc.Character(speed=speed,dir=dir,state=state)
        self.addComponent (self.__charcomp)
        self.addComponent (compo.Info(text_color = text_color, text_offset = text_offset))
    def __setattr__(self, name, value):
        if name == 'state':
            self.__charcomp.state = value
        elif name == 'dir':
            self.__charcomp.dir = value
        else:
            super().__setattr__(name, value)

# -- create a character
# scumm.ifac.char = function(args) 
# 	glib.assert(args.item, 'item!')

# 	local item = args.item

# 	glib.assert(item.model, 'character requires a model!')
# 	glib.assert(item.speed, 'character requires a speed!')

# 	local entity = Entity:new(args)

# 	entity.type = 'sprite'
# 	print ('ciao ' .. item.model)
# 	entity.model = item.model

# 	-- direction character is facing
# 	local dir = args.args.dir and (args.args.dir) or (item.dir)
# 	local state = args.args.state and (args.args.state) or (item.state or 'idle')

# 	table.insert (entity.components, { type="character", speed = item.speed, dir = dir, state = state })
# 	table.insert (entity.components, { type="info", info = { 
# 		color = item.text_color,
# 		offset = item.text_offset	
# 		--id = args.args._id 
# 	}})

# 	if args.args.follow then
# 		table.insert(entity.components, { type='follow', cam='maincam', relativepos = {0, 0, 5}, up = {0, 1, 0} })
# 	end	

# 	if item.collide and roomDefinition.collide then
# 		table.insert(entity.components, { 
# 			type='collider', 
# 			shape = { type='rect', width = item.collide.size[1], height=item.collide.size[2], offset = item.collide.offset },
# 			tag = item.collide.tag,
# 			flag = item.collide.flag,
# 			mask=item.collide.mask
# 		})
# 	end

# 	if item.hotspot then
# 		glib.assert(item.hotspot.text, 'entity with hotspot requires text!')
# 		glib.assert_either(item.hotspot.size, item.hotspot.shape, 'entity with hotspot requires size!')
# 		glib.assert(item.hotspot.walk_to, 'entity with hotspot requires walkto!')
# 		glib.assert(item.hotspot.dir, 'entity with hotspot requires dir!')

# 		local priority = item.hotspot.priority or 1
# 		local shape = item.hotspot.shape or { type="rect", width = item.hotspot.size[1], height = item.hotspot.size[2], offset = item.hotspot.offset }

# 		table.insert(entity.components, { 
# 			type = "hotspot", priority = priority,
# 			shape = shape,
# 			onenter = glib.curry (scumm.func.hoverOn, args.args._id),
# 			onleave = scumm.func.hoverOff,
# 			onclick = scumm.func.run_action,
# 		})
# 	end	

# 	return entity
# end
        
# class Sprite(entity.Entity):
#     def __init__(self, sprite : str, tag = None, pos = [0, 0, 0]):
#         super().__init__(tag, pos)
#         self.type = 'sprite'
#         self.model = sprite
#         #self.addComponent (compo.Gfx(image=image))