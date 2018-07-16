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