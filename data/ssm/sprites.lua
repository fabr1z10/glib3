local dt = 0.1
sprites = {
	-- start graham
	beast = {
		id = "beast",
		sheet = "gfx/ab.png",
		type = "sprite",
		ppu = 2,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 6, y = 11, width = 43, height = 71, anchor = {19, 0}}}}
				}
		    },
	        {
	           name="walk",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 55, y = 10, width = 24, height = 72, anchor = {20, 0}}}},
				   { duration = dt, quads = { { x = 84, y = 11, width = 48, height = 71, anchor = {30, 0}}}},
		           { duration = dt, quads = { { x = 55, y = 10, width = 24, height = 72, anchor = {20, 0}}}},
				   { duration = dt, quads = { { x = 136, y = 11, width = 49, height = 71, anchor = {30, 0}}}}
			   }				
	        },		
		    {
		        name = "jump", frames = 
				{ 
					{ duration = dt, quads = { { x = 194, y = 87, width = 42, height = 59, anchor = {19, 0}}}}
				}
		    },
	        {
	           name="punch",
	           frames=
	           { 
		           { duration = dt, quads = { { x = 187, y = 11, width = 62, height = 71, anchor = {33, 0}}}},
				   { duration = dt, quads = { { x = 253, y = 11, width = 40, height = 71, anchor = {23, 0}}}},
				   { duration = dt, quads = { { x = 298, y = 12, width = 64, height = 70, anchor = {24, 0}}}}
			   }				
	        },		
	        {
	           name="kick",
	           frames=
	           { 
		            { duration = dt, quads = { { x = 3, y = 87, width = 61, height = 69, anchor = {41, 0}}}},
				    { duration = dt, quads = { { x = 68, y = 87, width = 43, height = 69, anchor = {19, 0}}}},
				    { duration = dt, quads = { { x = 114, y = 88, width = 76, height = 68, anchor = {25, 0}}}},
			   }				
	        },	
	        {
	           name="cr",
	           frames=
	           { 
		            { duration = 2*dt, quads = { { x = 28, y = 162, width = 42, height = 74, anchor = {21, 0}}}},
				   { duration = 3*dt, quads = { { x = 84, y = 11, width = 48, height = 71, anchor = {18, 0}}}},
			   }				
	        },	
		
		}
	},
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
	           name="slide",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 176, y = 64, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },
	        {
	           name="slidebig",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 192, y = 64, width = 16, height = 32, anchor = {8, 0}}}},
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
		    },
		    {
		        name = "taken", frames = 
				{ 
					{ duration = dt, quads = { { x = 224, y = 0, width = 16, height = 16, anchor = {0, 0}}}}
				}
		    }				
		}
	},
	basicbrickdark = {
		id = "basicbrickdark",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 160, y = 48, width = 16, height = 16, anchor = {0, 0}}}}
				}
		    },
		    {
		        name = "taken", frames = 
				{ 
					{ duration = dt, quads = { { x = 240, y = 96, width = 16, height = 16, anchor = {0, 0}}}}
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
	brickcoin = {
		id = "brickcoin",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 160, y = 16, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 176, y = 16, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 192, y = 16, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 208, y = 16, width = 16, height = 16, anchor = {8, 0}}}},
				}
		    }		
		}
	},
	pickupcoin = {
		id = "pickupcoin",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 128, y = 64, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 144, y = 64, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 160, y = 64, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 144, y = 64, width = 16, height = 16, anchor = {0, 0}}}},
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
	plant = {
		id = "plant",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 128, y = 96, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 144, y = 96, width = 16, height = 32, anchor = {8, 0}}}},

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
	score100 = {
		id = "score100",
		sheet = "gfx/smb1.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 0, y = 80, width = 16, height = 16, anchor = {8, 0}}}}
				}
		    }		
		}
	},

}
