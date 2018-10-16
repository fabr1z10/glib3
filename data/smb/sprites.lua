local dt = 0.1
sprites = {
	-- start graham
	mario = {
		id = "mario",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    },
		    {
		        name = "idlebig", frames = 
				{ 
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}}
				}
		    },
		    {
		        name = "idlebigfire", frames = 
				{ 
					{ duration = dt, quads = { { x = 0, y = 112, width = 16, height = 32, anchor = {8, 0}}}}
				}
		    },
	        {
	           name="walk",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 16, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 32, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 48, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },		
	        {
	           name="walkbig",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 96, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 112, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },		
	        {
	           name="walkbigfire",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 16, y = 112, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 32, y = 112, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 48, y = 112, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },		
	        {
	           name="jump",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 80, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },				
	        {
	           name="jumpbig",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 128, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },
	        {
	           name="jumpbigfire",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 64, y = 128, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },
	        {
	           name="dead",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 96, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },
	        {
	           name="duck",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 96, y = 128, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },		
			{	
			    name="smalltobig",
		        frames = 
				{ 
					{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = 2*dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = 4*dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
				}
			},
			{	
			    name="bigtosmall",
		        frames = 
				{ 
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = 2*dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 31, anchor = {8, 0}}}},
					{ duration = 4*dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
				}
			}				

		}
	},
	goomba = {
		id = "goomba",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "walk", frames = 
				{ 
					{ duration = dt, quads = { { x = 112, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 128, y = 0, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    },
		    {
		        name = "dead", frames = 
				{ 
					{ duration = dt, quads = { { x = 144, y = 0, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    }			
		}
	},
	koopa = {
		id = "koopa",
		sheet ="gfx/smb1.png",
		type = "sprite",
		ppu=1,
		animations = {
			{
				name = "walk", frames =
				{ 
					{ duration = dt, quads = { { x = 0, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 16, y = 16, width = 16, height = 32, anchor = {8, 0}}}}
				}
			},
			{
				name = "shell", frames =
				{ 
					{ duration = dt, quads = { { x = 32, y = 32, width = 16, height = 16, anchor = {8, 0}}}}
				}
			},			
			{
				name = "blink", frames =
				{ 
					{ duration = dt, quads = { { x = 32, y = 32, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 32, y = 16, width = 16, height = 16, anchor = {8, 0}}}},
				}
			},			

		}
	},
	basicbrick = {
		id = "basicbrick",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 240, y = 0, width = 16, height = 16, anchor = {0, 0}}}}
				}
		    }		
		}
	},
	mushroom = {
		id = "mushroom",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 48, y = 16, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    }		
		}
	},
	mushroom1up = {
		id = "mushroom1up",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 144, y = 48, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    }		
		}
	},
	flower = {
		id = "flower",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 176, y = 96, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 192, y = 96, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 208, y = 96, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 224, y = 96, width = 16, height = 16, anchor = {8, 0}}}},
				}
		    }		
		}
	},
	star = {
		id = "star",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 128, y = 48, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    }		
		}
	},
	bonusbrick = {
		id = "bonusbrick",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 160, y = 0, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 176, y = 0, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 192, y = 0, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 176, y = 0, width = 16, height = 16, anchor = {0, 0}}}},
				}
		    },
		    {
		        name = "taken", frames = 
				{ 
					{ duration = dt, quads = { { x = 224, y = 0, width = 16, height = 16, anchor = {0, 0}}}}
				}
		    }			
		}
	},
	invbrick = {
		id = "invbrick",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "nottaken", frames = 
				{ 
					{ duration = dt, quads = { { x = 176, y = 80, width = 16, height = 16, anchor = {0, 0}}}},
				}
		    },
		    {
		        name = "taken", frames = 
				{ 
					{ duration = dt, quads = { { x = 224, y = 0, width = 16, height = 16, anchor = {0, 0}}}}
				}
		    }			
		}
	},	

}
