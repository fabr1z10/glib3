from lib_py.scumm.scumm import State
from lib_py.scumm.scumm import Item
from lib_py.scumm.dialogue import Dialogue, NodeStatus
from lib_py.scumm.dialogue import Line, DialogueNode
from lib_py.script import Script
import lib_py.scumm.actions as sa
import lib_py.scumm.scripts as ssc
import lib_py.engine as engine
import mi1_py.variables as var
import example

st = engine.data['strings']
sl = st['lines']

# engine.items['scummbar.door.out'] = make_door {
# 	tag = 'scummbar.door.out',
# 	model = 'door_scummbar_village',
# 	pos = {32, 24, -1},
# 	size = {38, 47},
# 	walk_to = mi.rooms.scummbar.door_out,
# 	dir = 'w',
# 	var = 'door_village_scummbar',
# 	go_to = {
# 		room = 'village1',
# 		pos = mi.rooms.village1.door,
# 		dir = 's'
# 	}
# }

# door leading out
State.addItem(
    id = 'scummbar.door.out',
    item = Item(
        text = st['objects']['door'],
        width = 38,
        height = 47,
        walkto = var.scummbar_door_pos,
        dir = 'w',
        actions = {
            'open': ssc.openDoor (doorId='scummbar.door.out', var = 'village_scummbar'),
            'close': ssc.closeDoor (doorId='scummbar.door.out', var = 'village_scummbar'),
            'walkto': ssc.walkDoor (var = 'village_scummbar', room='village1', pos=var.village1_door_pos, dir='s')
        }
    )
)

State.addItem(
    id = 'scummbar.door.kitchen',
    item = Item(
        text = st['objects']['door'],
        width = 35,
        height = 69,
        walkto = var.scummbar_kitchen_door_pos,
        dir = 'e',
#        actions = {
#            'open': ssc.openDoor (doorId='scummbar.door.out', var = 'door.village.scummbar'),
#            'close': ssc.closeDoor (doorId='scummbar.door.out', var = 'door.village.scummbar'),
#            'walkto': ssc.walkDoor (var = 'door.village.scummbar', room='village1', pos=var.village1_door_pos, dir='s')
#        }
    )
)

 	# walk = function() 
 	# 	if not variables.cook_in_kitchen then
 	# 		local m = monkey.getEntity('scummbar.cook')
 	# 		if (m.x > 320) then
 	# 			return {
	#  				{ type = scumm.action.toggle_controls, args =  { active = false, ui = false }},
 	# 				{ type = action.suspend_script, args = {script = "_cook"}},
 	# 				{ type = scumm.action.turn, args = { tag = "scummbar.cook", dir="east"}},
 	# 				{ type = scumm.action.say, args = { tag = "scummbar.cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }}},
 	# 				{ type = scumm.action.turn, args = { tag = "scummbar.cook", dir="west"}},
 	# 				{ type = action.set_state, args = {tag = "scummbar.cook", state="walk"}},
 	# 				{ type = action.resume_script, args = {script = "_cook"}},
	#  				{ type = scumm.action.toggle_controls, args =  { active = true, ui = false }},

 	# 			}
 	# 		else
 	# 			-- sneak into kitchen
 	# 			return scumm.script.changeroom { room = 'kitchen', pos = mi.rooms.kitchen.door, dir='e' }
 	# 		end
 	# 	else
 	# 		return nil
 	# 	end
 	# end,
 	# open = function() 
 	# 	if variables.cook_in_kitchen then
 	# 		return {
 	# 			{ type = scumm.action.toggle_controls, args =  { active = false, ui = false }},
 	# 			{ type = action.suspend_script, args = {script = "_cook"}},
 	# 			{ type = action.animate, args = {tag ="scummbar.door.kitchen", anim="open" }},
 	# 			{ type = action.show_message, args = { 
 	# 				message = strings.dialogues.cook[3], 
 	# 				color = mi.data.cook_text_color, 
 	# 				pos= {591, 100,1},
 	# 				font = 'monkey'
 	# 			}},
 	# 			{ type = action.animate, args = {tag="scummbar.door.kitchen", anim="close" }},
 	# 			{ type = action.resume_script, args = {script = "_cook"}},
 	# 			{ type = scumm.action.toggle_controls, args =  { active = true, ui = false }},
 	# 		}
 	# 	else
 	# 		return { type = action.open_door, args = {door="scummbar.door.kitchen"}}
 	# 	end
 	# end



State.addItem(
    id = 'scummbar.fireplace',
    item = Item(

        text = st['objects']['fireplace'],
        width = 29, height = 18,
        walkto = [512, 40],
        dir = 'e',
        actions = {
            'look':ssc.say (lines=[sl[3]])
        }))



State.addItem(
    id = 'scummbar.mancomb',
    item = Item (
        text = st['objects']['pirate'],
        width = 30, height = 30,
        walkto = [125, 17],
        dir = 'n'
    )
)

State.addItem(
    id = 'scummbar.estevan',
    item = Item (
        text = st['objects']['pirate'],
        width = 30, height = 20,
        walkto = [195, 11],
        dir = 's'
        #actions = {
		#look =  scumm.script.changeroom { room = 'estevan' },
		#talk =  scumm.script.changeroom { room = 'estevan' },
        #}
    ))

State.addItem(
    id = 'scummbar.loom',
    item = Item (
        text = st['objects']['pirate'],
        width = 26, height = 17,
        walkto = [250, 16],
        dir = 'n'
        #actions = {
		#look =  scumm.script.changeroom { room = 'estevan' },
		#talk =  scumm.script.changeroom { room = 'estevan' },
        #}
    ))


State.addItem( 
    id = 'scummbar.pirate1',
    item = Item (
        text = st['objects']['pirate'],
        width=30,height=30,
        walkto = [140,20],
        dir = 'n',
        actions = {
            'look': ssc.say (lines = [ sl[5] ]),
            'talkto': ssc.say (lines = [ sl[5] ])
        }
    )
)

State.addItem( 
    id = 'scummbar.pirate4',
    item = Item(
        text = st['objects']['pirates'],
        width=70,height=20,
        walkto = [50,10],
        dir = 's',
        actions = {
            'look': ssc.say (lines = [ sl[6] ]),
            'talkto': ssc.say (lines = [ sl[6] ])
        }
    )
)

State.addItem( 
    id = 'scummbar.important_looking_pirates',
    item = Item(
        text = st['objects']['ilp'],
        width=110,height=25,
        walkto=[460, 2],
        dir = 'w'
    ))

# engine.items["scummbar.important_looking_pirates"] = {
# 	type = 'object',
# 	pos = {370,30,0},
# 	hotspot = {
# 		text = strings.objects.ilp,
# 		walk_to = {460, 2},
# 		size = {110,25},
# 		dir = 'w',
# 	},
# 	actions = {
#  		talk = function() 
#  			local dp = strings.dialogues.pirates
#  			local actions = {
# 				{ type = scumm.action.toggle_controls, args = { active=false, ui=true } },
# 				{ type = scumm.action.say, args = { tag='scummbar.ilp1', lines = { dp[1] }}},
# 				{ type = scumm.action.start_dialogue, args = { dialogue = "importantpirates" }}
# 			}
#  			return actions
#  		end
#  	}
# }


#	pos = {89, 24, -1},
#	actions = {
#		look = scumm.script.changeroom { room = 'mancomb' },
#		talk = scumm.script.changeroom { room = 'mancomb' },
#	}
#}#
