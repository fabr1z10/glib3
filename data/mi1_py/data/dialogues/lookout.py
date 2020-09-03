# from lib_py.scumm.dialogue import Dialogue, DialogueNode
# from lib_py.script import Script
# from lib_py.scumm.scumm import State
# from lib_py.scumm.functions import dialogueHelper2
# import lib_py.engine as engine
# import mi1_py.variables as var
# import lib_py.scumm.actions as sa
# import example
# import random
#
# # define the string array
# sl = engine.data['strings']['dialogues']['lookout']
#
# # create the dialogue
# d = Dialogue('lookout', sl)
#
# def g(n):
#     def f():
#         s = Script()
#         l = None
#         if var.talked_to_lookout>0:
#             names = [sl[53],sl[54]]
#             l = [sl[5], sl[43] + random.choice(names)]
#         else:
#             l = [sl[5], sl[6], sl[7], sl[8], sl[9]]
#         var.talked_to_lookout +=1
#         s.addAction (sa.Say(lines = [sl[n]], tag='player'))
#         s.addAction (sa.Turn(tag='lookout', dir='s'))
#         s.addAction (sa.Say(tag='lookout', lines = l))
#         return s
#     return f
#
# def lookoutTurn(n):
#     def f():
#         s = Script()
#         s.addAction(sa.Say(tag="player", lines = [sl[n]]))
#         s.addAction(sa.Turn(tag='lookout', dir='e'))
#         s.addAction(sa.Say(tag="lookout", lines = [sl[15], sl[16]]))
#         return s
#     return f
#
# def squinky():
#     if d.nodes['imguy'].status == NodeStatus.CLOSED:
#         return dialogueHelper2(sl, ['player', 11], ['lookout', 27], ['player',28], ['lookout', 29])()
#     else:
#         return dialogueHelper2(sl, ['player', 11], ['lookout', 41])()
#
# def start(self):
#     d.nodes[12].active = True
#     if (not d.nodes[10].active or not d.nodes[13].active):
#         d.nodes[47].active = True
#     return
#
# def end(self):
#     s = Script()
#     s.addAction(sa.Turn(tag='lookout', dir='w'))
#     example.play(s)
#
# d.addStartScript (start)
# d.addEndScript (end)
#
# # nodes
# d.add (1, g(1), 1, True)
# d.add (2, g(2), 1, True)
# d.add (3, g(3), 1, True)
# d.add (4, g(4), 1, True)
#
# d.add (10, dialogueHelper2 (sl, ['player', 10, 17], ['lookout', 18, 19, 20, 21]), 1, lambda: 1 if var.talked_to_lookout == 1 else 3, [10], [22], parent=[1])
# d.add (22, dialogueHelper2(sl, ['player', 22], ['lookout', 23,24,25,26]), 1, False, parent=[1])
# d.add (11, squinky, 1, lambda: 1 if var.talked_to_lookout == 1 else 3, parent=[1])
# d.add (47, dialogueHelper2(sl, ['player', 47], ['lookout', 49]), 1, False, [47], parent=[1])
#
# d.add (12, lookoutTurn(12), 1, True, closeNodes=[12], parent=[1])
# d.add (13, dialogueHelper2 (sl, ['player', 13], ['lookout', 30, 31, 32]), 1, True, [13,10,11], [34,38,47], parent=[1])
# d.add (14, dialogueHelper2 (sl, ['player', 14], ['lookout', 42]), -1, True, parent=[1],order=10)
#
# d.add (34, dialogueHelper2(sl, ['player', 34], ['lookout', 35, 36, 37]), 1, False, [34], parent=[1])
# d.add (38, dialogueHelper2(sl, ['player', 38], ['lookout', 39, 40]), 1, False, [38], parent=[1])
#
# State.addDialogue (d)
