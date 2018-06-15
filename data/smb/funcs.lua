function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function curry2(f, arg)
    return function(x)
       f(arg, x) 
    end 
end

require ("factoryactions")
require ("items")
require ("factoryobjects")
require ("uifuncs")





function curry2_1(f, arg1, arg2)
    return function(x)
       f(arg1, arg2, x) 
    end 
end




function createWalkToPosition (position, script, f)
    table.insert (script.actions,
    {
        id = #script.actions,
		    walkarea = "walkarea",
		    actor = "player",
        type = "walkto",
		    pos = position
	  }

  )
end















--{
--    pos = {200, 40, 0},
--    outlinetext = {
--        id = "ciao", font="monkey", align="bottom", fontcolor={255,0,0,255}, outlinecolor = {255,255,255,255}, size = 8
--    },
--    layer = 2
--    
--}
		





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
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },               
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               },    
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },   
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 192, y = 115, width = 11, height = 12, anchor = {10, 0}}
                    }
               }, 
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 179, y = 101, width = 11, height = 12, anchor = {10, 0}}
                    }
               },
               {
                    duration = dt,
                    quads = {
                        { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
                        { x = 205, y = 101, width = 11, height = 12, anchor = {10, 0}}
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
        }



        }
    }    
end

