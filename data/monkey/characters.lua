function makeArrowUp() 
local dt=0.1
return 
	{
		id = "arrowup",
		sheet ="gfx/anims.png",
		type="sprite",
		ppu=1,
	    animations = {
        {
       	    name = "unselected",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 485, y = 4, width = 12, height = 20, anchor = {0, 0}}}}             
			}
        },
		{
			name = "selected",
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 485, y = 25, width = 12, height = 20, anchor = {0, 0}}}}             
			}
		}
        }	
	}
end
function makeArrowDown()
local dt =0.1
return
	{
		id = "arrowdown",
		sheet ="gfx/anims.png",
		type="sprite",
		ppu=1,
	    animations = {
        {
       	    name = "unselected",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 472, y = 4, width = 12, height = 20, anchor = {0, 0}}}}             
			}
        },
		{
			name = "selected",
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 472, y = 25, width = 12, height = 20, anchor = {0, 0}}}}             
			}
		}
        }	
	}

end

function makeGuybrush()
    local pane = {6,-34}
    local dt = 0.1
return {
        id="guybrush",
        sheet="gfx/sprite1.png",
		type="sprite",
        ppu=1,
        animations = {
	    {
	        name = "idle_front",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 24, y = 51, width = 22, height = 47, anchor = {12, 0}}
					}
		    	}
			}
	    },
        {
           name="idle_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 2, y = 51, width = 19, height = 47, anchor = {10, 0}}
					}
		       }
		   }				
        },
        {
           name="idle_back",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 49, y = 51, width = 20, height = 47, anchor = {12, 0}}
					}
		       }
		   }				
        },
        {
           name="idle_front_look_left",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 125, y = 200, width = 22, height = 47, anchor = {12, 0}}
					}
		       }
		   }				
        },
        {
           name="idle_front_look_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 148, y = 200, width = 21, height = 47, anchor = {12, 0}}
					}
		       }
		   }				
        },
	    {
	        name = "walk_front",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 207, y = 51, width = 22, height = 47, anchor = {11, 0}}
					}
		    	},
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 231, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		    	},	
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 3, y = 101, width = 20, height = 47, anchor = {10, 0}}
					}
		    	},
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 25, y = 101, width = 22, height = 47, anchor = {12, 0}}
					}
		    	},	
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 49, y = 101, width = 21, height = 47, anchor = {11, 0}}
					}
		    	},						
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 72, y = 101, width = 20, height = 47, anchor = {11, 0}}
					}
		    	}					
			}
	    },			
        {
           name="walk_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 4, y = 1, width = 32, height = 47, anchor = {16, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 40, y = 1, width = 16, height = 47, anchor = {11, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 60, y = 1, width = 19, height = 47, anchor = {11, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 83, y = 1, width = 31, height = 47, anchor = {15, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 117, y = 1, width = 18, height = 47, anchor = {11, 0}}
					}
		       },		
			   {
					duration = dt,
                    quads = {
			    		{ x = 141, y = 1, width = 19, height = 47, anchor = {11, 0}}
					}
		       }					
		   }				
        },		
        {
           name="walk_back",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 72, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 95, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 118, y = 51, width = 19, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 139, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 163, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 186, y = 51, width = 19, height = 47, anchor = {9, 0}}
					}
		       }
					
					
					
					
					
		   }				
        },
        {
           name="talk_front",

           frames={ 
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 129, width = 11, height = 13, anchor = pane }
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 129, width = 11, height = 13, anchor = pane }
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 205, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 143, width = 11, height = 13, anchor =  pane}
                    }
               },               
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane }
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 143, width = 11, height = 13, anchor = pane}
                    }
               },  
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 205, y = 143, width = 11, height = 13, anchor = pane }
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 143, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 179, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 192, y = 129, width = 11, height = 13, anchor = pane}
                    }
               },      
               {
                    duration = dt,
                    quads = {
                        { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
                        { x = 205, y = 143, width = 11, height = 13, anchor =  pane}
                    }
               }
           }

        },
        {
           name = "talk_right",
           frames = { 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {7, -35}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               },               
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 115, width = 11, height = 12, anchor = {7,-35}}
                    }
               },    
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 115, width = 11, height = 12, anchor = {7,-35}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 115, width = 11, height = 12, anchor = {7,-35}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               },   
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 115, width = 11, height = 12, anchor = {7,-35}}
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 101, width = 11, height = 12, anchor = {7,-35}}
                    }
               }               
           }                
        },
        {
            name = "talk_back",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 220, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 233, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 220, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 233, y = 101, width = 11, height = 12, anchor = {12, 0}}
                    }
               },                    
               {
                    duration = dt,
                    quads = {
                        { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
                        { x = 220, y = 115, width = 11, height = 12, anchor = {12, 0}}
                    }
               }                       
           }
        },
        {
            name = "operate_right",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 2, y = 150, width = 28, height = 45, anchor = {10, 0}},
                    }
               },
           }
        },
        {
            name = "operate_back",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 33, y = 150, width = 19, height = 45, anchor = {12, 0}},
                    }
               },
           }
        },
        {
            name = "operate_front",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 125, y = 151, width = 18, height = 46, anchor = {12, 0}},
                    }
               },
           }
        },
        {
            name = "kneel_front",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 80, y = 163, width = 17, height = 33, anchor = {10, 0}},
                    }
               },
           }
        },
        {
            name = "kneel_back",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 100, y = 163, width = 19, height = 33, anchor = {10, 0}},
                    }
               },
           }
        },
        {
            name = "plank",
            frames =            { 
               {
                    duration = dt,
                    quads = {
                        { x = 57, y = 150, width = 21, height = 47, anchor = {10, 0}},
                    }
               },
           }
        },
        {
            name = "pot_out",
            frames = { 
               	{ duration = dt, quads = {{ x = 1, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 30, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 59, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
           	}
        },
        {
            name = "show_pot",
            frames = { 
				{ duration = dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
           	}
        },
        {
            name = "pot_in",
            frames = { 
				{ duration = dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 59, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 30, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
               	{ duration = dt, quads = {{ x = 1, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
           	}
        },
        {
            name = "get_in_cannon",
            frames = { 
               	{ duration = dt, quads = {{ x = 1, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 30, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 59, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = 3*dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 176, y = 193, width = 21, height = 54, anchor = {7, 2}}}},
				{ duration = dt, quads = {{ x = 200, y = 200, width = 18, height = 47, anchor = {7, 2}}}},
				{ duration = dt, quads = {{ x = 222, y = 198, width = 26, height = 49, anchor = {7, 2}}}},
				{ duration = dt, quads = {{ x = 2, y = 249, width = 26, height = 49, anchor = {7, 1}}}},
				{ duration = dt, quads = {{ x = 31, y = 248, width = 23, height = 50, anchor = {5, -6}}}},
				{ duration = dt, quads = {{ x = 57, y = 248, width = 19, height = 46, anchor = {5, -6}}}},
				{ duration = dt, quads = {{ x = 80, y = 249, width = 21, height = 41, anchor = {6, -5}}}},
				{ duration = dt, quads = {{ x = 104, y = 249, width = 15, height = 29, anchor = {0, -13}}}},
				{ duration = dt, quads = {{ x = 124, y = 249, width = 19, height = 20, anchor = {4, -16}}}},
				{ duration = dt, quads = {{ x = 147, y = 249, width = 23, height = 20, anchor = {4, -22}}}},
				{ duration = dt, quads = {{ x = 172, y = 252, width = 21, height = 13, anchor = {4, -22}}}},
           	}
        },

        }
    }    
end

function makeLookout()
    local pane = {6,-34}
    local dt = 0.1
    return {
        id="lookout",
        sheet="gfx/anims.png",
		    type="sprite",
        ppu=1,
        animations = {
        {
            name = "idle_front",             
            frames = { 
 	    	  	{
					      duration = dt,
                quads = {
			    		      { x = 215, y = 1, width = 23, height = 44, anchor = {12, 0}},
                    { x = 129, y = 1, width = 9, height = 14, anchor = {6, -29}}
					      }
            }}
		    },
			  {
            name = "idle_right",             
            frames = {
	    	  	{
					      duration = dt,
                quads = {
			    		      { x = 105, y = 1, width = 20, height = 37, anchor = {10, 0}},
                    { x = 126, y = 18, z= 0.001,width = 12, height = 13, anchor = {2, -30}}
					      }
            }}
		    },
        {
            name = "idle_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 190, y = 1, width = 22, height = 35, anchor = {11, 0}},
                    { x = 168, y = 10, z= 0.001,width = 9, height = 9, anchor = {0, -31}}
                }
            }}
        },
        {
            name = "talk_front",             
            frames = {
              { duration = dt, quads = {{ x = 215, y = 1, width = 23, height = 44, anchor = {12, 0}}, { x = 129, y = 1, z= 0.001,width = 9, height = 14, anchor = {6, -29}}}},
              { duration = dt, quads = {{ x = 215, y = 1, width = 23, height = 44, anchor = {12, 0}}, { x = 143, y = 1, z= 0.001,width = 9, height = 15, anchor = {6, -29}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
              { duration = dt, quads = {{ x = 105, y = 1, width = 20, height = 37, anchor = {10, 0}}, { x = 126, y = 18, z= 0.001,width = 12, height = 13, anchor = {2, -30}}}},
              { duration = dt, quads = {{ x = 105, y = 1, width = 20, height = 37, anchor = {10, 0}}, { x = 140, y = 18, z= 0.001,width = 12, height = 14, anchor = {2, -30}}}}
            }
        },                
        {
            name = "talk_back",             
            frames = {
              { duration = dt, quads = {{ x = 190, y = 1, width = 22, height = 35, anchor = {11, 0}}}}
            }
        }        
    }}

    
end


function makePurpleClown()
    local pane = {6,-34}
    local dt = 0.1
    return {
        id="purpleclown",
        sheet="gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
            name = "idle_front",             
            frames = { 
            {
                duration = dt,
                quads = {
                    { x = 286, y = 303, width = 27, height = 45, anchor = {14, 0}}
                }
            }}
        },
        {
            name = "idle_right",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}},
					{ x = 316, y = 409, width = 11, height = 12, anchor = {2, -34}},
                }
            }}
        },
        {
            name = "idle_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 331, y = 409, width = 28, height = 45, anchor = {15, 0}}
                }
            }}
        },
        {
            name = "walk_front",             
            frames = {
              { duration = dt, quads = {{ x = 315, y = 315, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 340, y = 314, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 366, y = 314, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 392, y = 315, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 417, y = 314, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 443, y = 315, width = 24, height = 45, anchor = {12, 0}}}}
            }
        }, 
        {
            name = "walk_right",             
            frames = {
              { duration = dt, quads = {{ x = 364, y = 411, width = 28, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 394, y = 412, width = 24, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 419, y = 409, width = 15, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 436, y = 411, width = 26, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 463, y = 412, width = 21, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 486, y = 409, width = 15, height = 45, anchor = {11, 0}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
            	{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 316, y = 409, width = 11, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 277, y = 397, width = 10, height = 13, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 411, width = 11, height = 12, anchor = {2, -34}}}},
				{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 277, y = 424, width = 9, height = 12, anchor = {2, -34}}}}                
            }
        },   
        {
            name = "talk_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 331, y = 409, width = 28, height = 45, anchor = {15, 0}}
                }
            }}
        },
    }}

    
end

function makeGreenClown()
    local pane = {6,-34}
    local dt = 0.1
    return {
        id="greenclown",
        sheet="gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
            name = "idle_front",             
            frames = { 
            {
                duration = dt,
                quads = {
                    { x = 286, y = 350, width = 27, height = 45, anchor = {14, 0}}
                }
            }}
        },
        {
            name = "idle_right",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}},
					{ x = 316, y = 423, width = 10, height = 12, anchor = {2, -34}},
                }
            }}
        },
        -- {
        --     name = "idle_back",             
        --     frames = {
        --     {
        --         duration = dt,
        --         quads = {
        --             { x = 331, y = 409, width = 28, height = 45, anchor = {15, 0}}
        --         }
        --     }}
        -- },
        {
            name = "walk_front",             
            frames = {
              { duration = dt, quads = {{ x = 315, y = 362, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 340, y = 361, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 366, y = 361, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 392, y = 362, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 417, y = 362, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 443, y = 362, width = 24, height = 45, anchor = {12, 0}}}}
            }
        }, 
        {
            name = "walk_right",             
            frames = {
              { duration = dt, quads = {{ x = 364, y = 458, width = 28, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 394, y = 459, width = 24, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 419, y = 456, width = 15, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 436, y = 458, width = 26, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 463, y = 459, width = 21, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 486, y = 456, width = 15, height = 45, anchor = {11, 0}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 316, y = 423, width = 10, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 443, width = 10, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 456, width = 10, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 469, width = 10, height = 12, anchor = {2, -34}}}},
            }
        },   
    }}

    
end

function makeStorekeeper()
	local dt = 0.1
	return {
        id = "storekeeper",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}}
		    }
        },
        {
        	name="walk_right",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=380, y=105, width=30, height=45, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=412, y=107, width=26, height=44, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=440, y=105, width=27, height=46, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=469, y=106, width=28, height=45, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=380, y=154, width=26, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=407, y=152, width=38, height=45, anchor = {12, 0}}}},
		    }        	
    	},
    	{
        	name="walk_front",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=310, y=225, width=34, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=346, y=225, width=29, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=378, y=246, width=28, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=408, y=246, width=29, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=439, y=246, width=30, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=472, y=247, width=31, height=41, anchor = {12, 0}}}},
		    }        	
    	},
    	{
        	name="walk_back",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=448, y=155, width=34, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=483, y=155, width=28, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=378, y=201, width=28, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=408, y=200, width=28, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=438, y=201, width=32, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=472, y=200, width=32, height=42, anchor = {12, 0}}}},
		    }        	
    	},
        {
       	    name = "talk_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=168, y=3, width=10, height=14, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=180, y=4, width=10, height=13, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=192, y=4, width=12, height=12, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=207, y=2, width=11, height=15, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=220, y=2, width=11, height=15, anchor = {-2,-32}}}},
		    }
        },
		}
	}
end

function makeCook()
    local pane = {6,-34}
    local dt = 0.1
    return {
        id="cook",
        sheet="gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
            name = "idle_front",             
            frames = { 
            {
                duration = dt,
                quads = {
                    { x = 316, y = 213, width = 31, height = 48, anchor = {15, 0}}
                }
            }}
        },
        {
            name = "idle_right",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 438, y = 115, width = 28, height = 48, anchor = {14, 0}}
                }
            }}
        },
        {
            name = "idle_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 462, y = 165, width = 36, height = 48, anchor = {18, 0}}
                }
            }}
        },
        {
            name = "walk_right",             
            frames = {
              { duration = dt, quads = {{ x = 349, y = 216, width = 25, height = 48, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 376, y = 216, width = 31, height = 48, anchor = {15, 0}}}},
              { duration = dt, quads = {{ x = 409, y = 215, width = 20, height = 49, anchor = {10, 0}}}},
              { duration = dt, quads = {{ x = 431, y = 215, width = 28, height = 49, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 460, y = 216, width = 27, height = 48, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 489, y = 216, width = 22, height = 48, anchor = {11, 0}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
              { duration = dt, quads = {{ x = 349, y = 116, width = 28, height = 47, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 379, y = 115, width = 28, height = 48, anchor = {14, 0}}}}, 
              { duration = dt, quads = {{ x = 408, y = 115, width = 28, height = 48, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 438, y = 115, width = 28, height = 48, anchor = {14, 0}}}},
              { duration = dt, quads = {{ x = 467, y = 115, width = 29, height = 48, anchor = {14, 0}}}}
            }
        },   
    }}

    
end