local dt = 0.1
sprites = {
	-- start graham
	banzai_bill = {
		id = "banzai_bill",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 48, y = 32, width = 64, height = 64, anchor = {0, 0}}}}	
				}
			}
		}
	},
	rex = {
		id = "rex",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="walk",
				frames = {
					{ duration = dt, quads = { { x = 112, y = 32, width = 32, height = 32, anchor = {16, 0}}}},
					{ duration = dt, quads = { { x = 144, y = 32, width = 32, height = 32, anchor = {16, 0}}}}	
				}
			},
			{
				name="walk_small",
				frames = {
					{ duration = dt, quads = { { x = 176, y = 48, width = 16, height = 16, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 192, y = 48, width = 16, height = 16, anchor = {8, 0}}}}	
				}
			},
			{
				name="dead",
				frames = {
					{ duration = dt, quads = { { x = 208, y = 48, width = 16, height = 16, anchor = {8, 0}}}},
				}
			},
		}
	},
	mario = {
		id = "mario",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
		    {
		        name = "idle", frames = 
				{ 
					{ duration = dt, quads = { { x = 96, y = 0, width = 16, height = 32, anchor = {8, 0}}}}
				}
		    },
		  --   {
		  --       name = "idlebig", frames = 
				-- { 
				-- 	{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}}
				-- }
		  --   },
		  --   {
		  --       name = "idlebigfire", frames = 
				-- { 
				-- 	{ duration = dt, quads = { { x = 0, y = 112, width = 16, height = 32, anchor = {8, 0}}}}
				-- }
		  --   },
	        {
	           name="walk",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 96, y = 0, width = 16, height = 32, anchor = {8, 0}}}},
					{ duration = dt, quads = { { x = 112, y = 0, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },		
	    --     {
	    --        name="walkbig",
	    --        frames=
	    --        { 
					-- { duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					-- { duration = dt, quads = { { x = 96, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
					-- { duration = dt, quads = { { x = 112, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			  --  }				
	    --     },		
	    --     {
	    --        name="walkbigfire",
	    --        frames=
	    --        { 
					-- { duration = dt, quads = { { x = 16, y = 112, width = 16, height = 32, anchor = {8, 0}}}},
					-- { duration = dt, quads = { { x = 32, y = 112, width = 16, height = 32, anchor = {8, 0}}}},
					-- { duration = dt, quads = { { x = 48, y = 112, width = 16, height = 32, anchor = {8, 0}}}},
			  --  }				
	    --     },		
	        {
	           name="jump",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 176, y = 0, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },	
	        {
	           name="jump_down",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 192, y = 0, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },	
			
	    --     {
	    --        name="jumpbig",
	    --        frames=
	    --        { 
					-- { duration = dt, quads = { { x = 128, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			  --  }				
	    --     },
	    --     {
	    --        name="jumpbigfire",
	    --        frames=
	    --        { 
					-- { duration = dt, quads = { { x = 64, y = 128, width = 16, height = 32, anchor = {8, 0}}}},
			  --  }				
	    --     },
	        {
	           name="dead",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 128, y = 0, width = 16, height = 32, anchor = {8, 0}}}},
			   }				
	        },
	        {
	           name="duck",
	           frames=
	           { 
					{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 16, anchor = {8, 0}}}},
			   }				
	        },		
	  --       {
	  --          name="slide",
	  --          frames=
	  --          { 
			-- 		{ duration = dt, quads = { { x = 176, y = 64, width = 16, height = 16, anchor = {8, 0}}}},
			--    }				
	  --       },
	  --       {
	  --          name="slidebig",
	  --          frames=
	  --          { 
			-- 		{ duration = dt, quads = { { x = 192, y = 64, width = 16, height = 32, anchor = {8, 0}}}},
			--    }				
	  --       },

			-- {	
			--     name="smalltobig",
		 --        frames = 
			-- 	{ 
			-- 		{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			-- 		{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			-- 		{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			-- 		{ duration = 2*dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			-- 		{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			-- 		{ duration = 4*dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			-- 	}
			-- },
			-- {	
			--     name="bigtosmall",
		 --        frames = 
			-- 	{ 
			-- 		{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			-- 		{ duration = dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			-- 		{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 32, anchor = {8, 0}}}},
			-- 		{ duration = 2*dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			-- 		{ duration = dt, quads = { { x = 80, y = 16, width = 16, height = 31, anchor = {8, 0}}}},
			-- 		{ duration = 4*dt, quads = { { x = 0, y = 0, width = 16, height = 16, anchor = {8, 0}}}},
			-- 	}
			-- }				

		}
	},
	brick = {
		id = "brick",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 192, y = 96, width = 16, height = 16, anchor = {0, 0}}}}	
				}
			},
			{
				name="rotate",
				frames = {
					{ duration = dt, quads = { { x = 192, y = 96, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 176, y = 128, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 192, y = 128, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 208, y = 128, width = 16, height = 16, anchor = {0, 0}}}},
				}
			},

		}
	},
	bonusbrick = {
		id = "bonusbrick",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 208, y = 96, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 224, y = 128, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 240, y = 128, width = 16, height = 16, anchor = {0, 0}}}},
					{ duration = dt, quads = { { x = 256, y = 128, width = 16, height = 16, anchor = {0, 0}}}},
				}
			},
			{
				name="taken",
				frames = {
					{ duration = dt, quads = { { x = 272, y = 128, width = 16, height = 16, anchor = {0, 0}}}},
				}
			},

		}
	},
	brickpiece = {
		id = "brickpiece",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 192, y = 112, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 208, y = 112, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 224, y = 112, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 240, y = 112, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 256, y = 112, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 272, y = 112, width = 16, height = 16, anchor = {0, 0}}}}	
				}
			}
		}
	},
	midway_gate = {
		id = "midway_gate",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 272, y = 0, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 288, y = 0, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 304, y = 0, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 320, y = 0, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},
	midway_gate_top = {
		id = "midway_gate_top",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 272, y = 16, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 288, y = 16, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 304, y = 16, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 320, y = 16, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},
	midway_gate_back = {
		id = "midway_gate_back",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 272, y = 32, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 288, y = 32, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 304, y = 32, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 320, y = 32, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},
	midway_gate_back_top = {
		id = "midway_gate_back_top",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 272, y = 64, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 288, y = 64, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 304, y = 64, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 320, y = 64, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},
	midway_gate_back_flag = {
		id = "midway_gate_back_flag",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 272, y = 48, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 288, y = 48, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 304, y = 48, width = 16, height = 16, anchor = {0, 0}}}},	
					{ duration = dt, quads = { { x = 320, y = 48, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},
	midway_flag = {
		id = "midway_flag",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 240, y = 32, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},
	infobrick = {
		id = "infobrick",
		sheet = "gfx/sprites.png",
		type = "sprite",
		ppu = 1,
		animations = {
			{
				name="idle",
				frames = {
					{ duration = dt, quads = { { x = 176, y = 112, width = 16, height = 16, anchor = {0, 0}}}},	
				}
			}
		}		
	},  
}
