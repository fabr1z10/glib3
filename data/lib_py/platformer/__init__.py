import lib_py.components as compo

class WalkSide(compo.State):
    def __init__(self, id: str, speed : float, acceleration : float, flipHorizontal: bool, jumpSpeed : float):
        super().__init__(id)
        self.type = 'state.walkside'
        self.speed = speed
        self.jumpSpeed = jumpSpeed
        self.acceleration = acceleration
        self.flipH = flipHorizontal

					# 	id = "walk", 
					# 	state = {
					# 		type = "walkside", 
					# 		speed = 75, 
					# 		acceleration = 0.05, 
					# 		fliph = true, 
					# 		jumpspeed = variables.jump_velocity,
					# 		keys = {
					# 			{ id = 341, action="callback", func= function() 
					# 				if (variables.can_fire) then
					# 					print ("fire!")
					# 					factory.mario.fire()
					# 				end 
					# 				end 
					# 			},
					# 			{ id = 264, action="callback", func= function() if (variables.warpfunc ~= nil) then variables.warpfunc() end end },
					# 		}
					# 	}
					# },