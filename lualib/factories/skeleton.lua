factory.skeleton = {}

local helper1 = function(c, part)
print (part)
	assert (c[part], part)
	local p = engine.assets.bones[c[part]]
	if (p == nil) then 
		error ("Unknown bone: " .. part)
	end
	return p
end

factory.skeleton.create = function (args)

	glib.assert (args.character, "character")
	glib.assert (args.pos, "pos")
	glib.assert (args.speed, "speed")
	-- ensure character is existing

	local c = engine.assets.characters[args.character]
	if (c == nil) then error ("Unknown character: " .. args.character) end
	local l_offset_y = c.l_offset_y or 0 
	local r_offset_y = c.r_offset_y or 0 

	assert (c.gfx, "character requires <gfx>")
	assert (c.animations, "character requires <animations>")
		
	local scale = args.scale or 1

	local torso = helper1 (c, "torso")
	local thigh = helper1 (c, "rthigh")
	local shin = helper1 (c, "rshin")
	local lthigh = c.lthigh and helper1(c, "lthigh") or thigh
	local lshin = c.lshin and helper1(c, "lshin") or shin
	local components = {
		{ 
			type="extstatemachine", 
			initialstate = "walk",
			states = {
				{ 
					id = "walk", 
					state = {
						type = "walk25", 
						speed = args.speed,
						acceleration = 0.1,
						fliph=true,
						dir = "e",
						keys = {
							{ id = 81, action = "changestate", state = "attack" },
						}
					}
				},
			}
		}
	}

	for _, state in ipairs(c.additional_states) do
		table.insert (components[1].states, state)
	end


	local torso_length = torso.quad[4]*scale
	local torso_width = torso.quad[3]*scale
	local rthigh_length = thigh.quad[4]*scale
	local rshin_length = shin.quad[4]*scale

	local total_height = torso_length + rthigh_length + rshin_length

	local c_flag = 0
	local c_mask = 0
	local c_tag = 0
	local c_attack_tag = 0 
	local c_attack_mask = 0
	if (args.player) then
		c_flag = variables.collision.flags.player
		c_mask = 0
		c_tag = variables.collision.tags.player
		c_attack_tag = variables.collision.tags.player_attack
		c_attack_mask = variables.collision.flags.foe
	else 
		c_flag = variables.collision.flags.foe
		c_mask = 0
		c_tag = variables.collision.tags.foe
		c_attack_tag = variables.collision.tags.foe_attack
		c_attack_mask = variables.collision.flags.player
	end


	-- prepare the skeletal collider
	if (args.collider ~= nil) then
		local collider = {
			type = "skeletalcollider",
			tag = c_tag,
			flag = c_flag,
			mask = c_mask,
			bounds = {},
			attack = {}			
		}

    	for i,v in ipairs(c.animations) do 
     		table.insert (collider.bounds, { anim = v[1], x = -0.5*torso_width, y = 0, width = torso_width, height = torso_length })
    	end	
    	for i,v in ipairs(c.attack) do
    		table.insert (collider.attack, { 
    			anim = v.anim, 
    			t = v.t,                -- attack time
    			tag = c_attack_tag, 
    			mask = c_attack_mask, 
    			x = v.x, 
    			y= v.y, 
    			width = v.width, 
    		    height = v.height 
    		})
    	end
		table.insert (components, collider)
	end

	if (args.player == true) then
		table.insert (components, { type ="keyinput" })
	end

	if (args.info) then 
		table.insert (components, args.info)
	end


	local bones = {
		{ 
			name = "torso", 
			length = torso.quad[4]*scale, 
			desc = {
		  		pos = {0, 0, 0},							
		  		components = {
					{ type ="gfx", image=c.gfx, height=torso_length, offset = {-torso.origin[1]*scale,-torso.origin[2]*scale, 0}, quad = torso.quad}
				}
			}
		},					
		-- right leg
		{ 
			name = "rthigh", 
			length = math.abs(thigh.shinpos[2]-thigh.origin[2])*scale, 
			parent="torso", desc = {
				pos = {(torso.rleg[1]-torso.origin[1])*scale, (torso.rleg[2]-torso.origin[2])*scale, 0.001},
				components = {
					{ type ="gfx", image=c.gfx, height=rthigh_length, offset = {-thigh.origin[1]*scale,-thigh.origin[2]*scale, 0}, quad = thigh.quad }
				}
			}
		},
		{ 
			name = "rshin", 
			length = shin.quad[4]*scale, 
			parent="rthigh", 
			desc = {
				pos = {(thigh.shinpos[1]-thigh.origin[1])*scale, (thigh.shinpos[2]-thigh.origin[2])*scale, 0},							
				components = {
					{ type ="gfx", image=c.gfx, height=rshin_length, offset = {-shin.origin[1]*scale,-shin.origin[2]*scale}, quad = shin.quad}
				}
			}
		},
		-- left leg
		{ 
			name = "lthigh", 
			length = math.abs(lthigh.shinpos[2]-lthigh.origin[2])*scale, 
			parent="torso", desc = {
				pos = {(torso.lleg[1]-torso.origin[1])*scale, (torso.lleg[2]-torso.origin[2])*scale, -0.001},
				components = {
					{ type ="gfx", image=c.gfx, height=lthigh.quad[4]*scale, offset = {-lthigh.origin[1]*scale,-lthigh.origin[2]*scale, 0}, quad = lthigh.quad }
				}
			}
		},
		{ 
			name = "lshin", 
			length = lshin.quad[4]*scale, 
			parent="lthigh", 
			desc = {
				pos = {(lthigh.shinpos[1]-lthigh.origin[1])*scale, (lthigh.shinpos[2]-lthigh.origin[2])*scale, 0},							
				components = {
					{ type ="gfx", image=c.gfx, height=lshin.quad[4]*scale, offset = {-lshin.origin[1]*scale,-lshin.origin[2]*scale}, quad = lshin.quad}
				}
			}
		},
	}

	if (c.head ~= nil) then
		local head = helper1 (c, "head")

		table.insert (bones, { 
			name = "head", 
			length = head.quad[4]*scale, 
			parent="torso", desc = 
			{
				pos = {(torso.headpos[1]-torso.origin[1])*scale, (torso.headpos[2]-torso.origin[2])*scale, 0},
				components = {
					{ type ="gfx", image=c.gfx, height=head.quad[4]*scale, offset = {-head.origin[1]*scale,-head.origin[2]*scale,0 }, quad = head.quad }
				}
			}
		})
	end

	if (c.rupperarm ~= nil) then
		local r_upper_arm = engine.assets.bones[c.rupperarm]
		if (r_upper_arm == nil) then
			error("Unknown bone: " .. c.rupperarm)
		end
		
		assert(c.rforearm, "forearm")
		local r_forearm = engine.assets.bones[c.rforearm]
		if (r_forearm == nil) then
			error("Unknown bone: " .. c.rforearm)
		end

		local l_upper_arm = engine.assets.bones[c.lupperarm]
		if (l_upper_arm == nil) then
			error("Unknown bone: " .. c.lupperarm)
		end		
		
		local l_forearm = engine.assets.bones[c.lforearm]
		if (l_forearm == nil) then
			error("Unknown bone: " .. c.lforearm)
		end

		table.insert(bones, {
			name = "rarmup", 
			length = math.abs(r_upper_arm.forearmpos[2])*scale, 
			parent="torso", 
			desc = {
				pos = {(torso.rarmpos[1]-torso.origin[1])*scale,(torso.rarmpos[2]-torso.origin[2])*scale,2*0.001},
				components = {
					{ type ="gfx", image=c.gfx, height=r_upper_arm.quad[4]*scale, offset = {-r_upper_arm.origin[1]*scale,-r_upper_arm.origin[2]*scale}, quad = r_upper_arm.quad}	
				}
			}
		})
		
		table.insert(bones, { 
			name = "rarmfore", 
			length = r_forearm.quad[4]*scale, 
			parent="rarmup", 
			desc = {
				pos = {(r_upper_arm.forearmpos[1]-r_upper_arm.origin[1])*scale, (r_upper_arm.forearmpos[2]-r_upper_arm.origin[2])*scale, 0},
				components = {
					{ type ="gfx", image=c.gfx, height=r_forearm.quad[4]*scale, offset = {-r_forearm.origin[1]*scale, -r_forearm.origin[2]*scale, 0}, quad = r_forearm.quad}
				}
			}
		})
		table.insert(bones, { 
			name = "larmup", 
			length = math.abs(l_upper_arm.forearmpos[2])*scale, 
			parent="torso", 
			desc = {
				pos = {(torso.larmpos[1] - torso.origin[1])*scale,(torso.larmpos[2]-torso.origin[2])*scale,-2*0.001},
				components = {
					{ type ="gfx", image=c.gfx, height=l_upper_arm.quad[4]*scale, offset = {-l_upper_arm.origin[1]*scale,-l_upper_arm.origin[2]*scale}, quad = l_upper_arm.quad}	
				}
			}
		})
		table.insert(bones, { 
			name = "larmfore", 
			length = l_forearm.quad[4]*scale, 
			parent="larmup", 
			desc = {
				pos = {(l_upper_arm.forearmpos[1]-l_upper_arm.origin[1])*scale, (l_upper_arm.forearmpos[2]-l_upper_arm.origin[2])*scale, 0},
				components = {
					{ type ="gfx", image=c.gfx, height=l_forearm.quad[4]*scale, offset = {-l_forearm.origin[1]*scale, -l_forearm.origin[2]*scale, 0}, quad = l_forearm.quad}
				}
			}
		})
	end

	local a = {}
    for i,v in ipairs(c.animations) do 
     	print ("adding animation " .. v[1])
     	table.insert (a, { v[1], v[2] })
    end

	return {	
		tag = args.tag,
		type = "skeleton",		
		l_offset_y = l_offset_y*scale,
		r_offset_y = r_offset_y*scale,
		pos = {args.pos[1], args.pos[2], 0},
		animations = a,
		components = components,					
		bones = bones,
		children = {
			{ 
				pos = {0,0,0}, 
				components = { 
					{ type = "gfx", color = {0,0,0,128},shape = {type="ellipse", 
						semiaxes = {torso_width, 0.1*torso_width},
						--width = torso_width, height = torso_width*0.5, 
						offset ={0,-0.05*torso_width}},
						draw="solid"
					}
				}
			}
		}
	}
end