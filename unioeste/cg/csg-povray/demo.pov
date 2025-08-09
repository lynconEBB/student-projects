#version 3.7
#include "colors.inc"  
#include "shapes3.inc"  
#include "shapes3.inc"
#include "Round_Box_Y.inc"
#include "textures.inc" 
#include "skies.inc"
#include "stones.inc"

#declare Camera_0 = camera {perspective angle 90               // front view
                            location  <-10.0 , 10.0 ,-10.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 0.0 , 0.0>}
#declare Camera_1 = camera {/*ultra_wide_angle*/ angle 90   // diagonal view
                            location  <-0 ,20 ,0.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 0.0 , 0.0>}
#declare Camera_2 = camera {/*ultra_wide_angle*/ angle 90   // diagonal view
                            location  <-0 ,20 ,-20.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 0.0 , 0.0>}
#declare Camera_3 = camera {/*ultra_wide_angle*/ angle 90        // top view
                            location  <-10.0 , 10.0 ,10.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 0.0 , 0.0>}

#declare Camera_4 = camera {/*ultra_wide_angle*/ angle 90        // top view
                            location  <10 , 8.0 ,-5>
                            right     x*image_width/image_height
                            look_at   <-5.0 , -5.0 , 10.0>}

#declare Camera_7 = camera {/*ultra_wide_angle*/ angle 90   // diagonal view
                            location  <-0 ,10 ,-30.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 0.0 , 0.0>}
camera {
    Camera_0
}

light_source{<500,2500,-500> color White}

sky_sphere { 
    S_Cloud2
} 


#declare BombGrayColor = <0.1,0.1,0.1> ;
   

// ============================= Bomb ========================================

#declare BombBody = merge {
    object{//Round_Cone( point A, radius A, point B, radius B, rounding radius, merge on) 
        Round_Cone( <0,0,0>, 1, <0,0.7,0>, 0.8 , 0.1, 0)  
        texture{ 
            pigment{ 
                color BombGrayColor
            }         
        } 
        scale<1,1,1>  
        rotate<0,0,0> 
        translate<0,1.6,0>
    }  

    sphere {
        <0,0,0> 2
        pigment { color BombGrayColor }
        finish {
            ambient 0.2
        } 
        translate <0,0,0>
    }

  translate <0,-2,0> 
  finish { phong 0.5 }
} 
   
#declare BombWick = difference {
    sphere_sweep {
        b_spline
        4,
        <0,-10,0>, 1
        <0,-2,0>, 1
        <2,2,0>, 1
        <20,2,0>, 1
        texture { 
            T_Grnt4 
            normal { agate 0.15 scale 0.15}
        }
        finish {
            ambient 0.3
        }
    }

    box { 
        <-1.00, 0.00, -1.00>, < 1.00, 2.00, 1.00>
        scale <1.2,1.5,1.5> 
        rotate<0,0,15> 
        translate<5,0,0> 
    }
}

#declare Bomb = union {
    object { BombBody }
    object { 
        BombWick
        scale <1,1,1> * 0.3
        translate <-0.1,1,0>
    }  
    translate <10,9,0>
} 


// ======================== Character ================================
declare HeadRoundBox = object{ 
    Round_Box_Y ( <-1, -1, -1>, <1, 1, 1>, // <x, y, z> near lower left corner, <x, y, z> far upper right corner
                0.60, // Border_Radius_Big,  // big radius of vertical borders
                0.050, // Border_Radius_Small,// small radíus of horizontal borders
                1, 0 // Merge___On 
    ) 
    texture {
            pigment{ color White } 
    }
    scale<4,3,2.5>  rotate<90,0,0> translate<0,9,0>
}

#declare Chest = object{ 
    Egg_Shape( 0.2, 0.7  )
    scale <1,3.5,1>
    rotate <0,0,0>
    translate< 0, 0, 0>
}

#declare Belt = intersection {
    object { Chest }
    box { 
        <-1.00, 0.00, -1.00>, < 1.00, 2.00, 1.00>
        scale <3,0.5,3> 
        rotate<0,0,0> 
        translate<0,1.8,0>     
        
    } 

    pigment {
        color White
    }
    scale <1.05,1,1.05>
}
                                                                                                                                                                       
#declare Shoe = difference {
    object{ 
        Egg_Shape( 0.2, 0.5  )
        scale <1,5,1> * 0.5
        rotate <-90,0,0>
        translate< 0, 0, 0>
        pigment {
            color <1,0,0.25>
        } 
    }

    box {
        <-1, -1, -1>, <1, 1, 1> // <x, y, z> near lower left corner, <x, y, z> far upper right corner
        translate <0,-1,0>
        scale <2,1,8>
    } 
}
                                                                                                                                                                       
#declare BeltDetail = difference {
    object { 
        HeadRoundBox
        pigment {
            color < 1.0, 0.65, 0.0>
        }
    }
    
    object {
        HeadRoundBox
        scale<0.6,0.6,2> 
        translate <0,3.5,0>
        pigment {
            color < 1.0, 0.65, 0.0>
        }
    }
    scale <0.25,0.25,0.1>
    translate <0,0.2,-2.3>
}


#declare Hood = difference {
    object {
        HeadRoundBox
    }
    object {
        HeadRoundBox
        scale<0.8,0.8,1>
        translate <0,1.7,-1>
    }
}

#declare Face = intersection {
    sphere { 
        <0,0,0>, 1.25  
        scale<1,0.5,0.5>
         
        texture { 
            pigment{ color < 1, 0.80, 0.55>}
        }
        rotate<90,0,0>  translate<0,0,0>  scale<1,1,1> * 5
    }  

    object{ Round_Box_Y ( <-1, -1, -1>, <1, 1, 1>, // <x, y, z> near lower left corner, <x, y, z> far upper right corner
                        0.60, // Border_Radius_Big,  // big radius of vertical borders
                        0.050, // Border_Radius_Small,// small radíus of horizontal borders
                        1, // Y_Filled___On,
                        0 // Merge___On 
                        ) //----------------------------------------
            texture {
                pigment{ color White } 
            } 
        scale<3.4,5,2.2>  rotate<90,0,0> translate<0,0,0>
    }
    pigment {
        color < 1, 0.80, 0.55>
    }

    translate <0,9.1,-0.2>
}

#declare BomberEye = sphere {
    <0, 0, 0>, 1 // <x, y, z>, radius
    pigment { color Black }
    scale <1,4.7,1> * 0.4
    translate <1.5,9,-3>
}

#declare Head = merge {
    object {
        Hood
    }

    object {
        Face
    }

    object {
        BomberEye
    }

    object {
        BomberEye
        translate <-3,0,0>
    }

    sphere_sweep {
        linear_spline
        2,
        <0,0,0>, 0.5 
        <0,1,2>, 0.5 
        pigment { 
            White
        }
        finish {
            ambient 0.3
        }
        translate <0,11.5,2.5>
    }

    sphere {
        <0, 12.5, 4.5>, 1 // <x, y, z>, radius
        pigment {
            color <1,0,0.25>
        }
    }      

    triangle {
        <0,0.5,0>, <0,2,0>, <-3,-1,0>
        pigment {
            color Black
        }
        translate <4,13.4,-5>
        scale <1,1,1> * 0.8
    }

    triangle {
        <0,0.5,0>, <0,2,0>, <-3,-1,0>
        pigment {
            color Black
        }
        translate <4,13.4,-5>
        scale <-1,1,1> * 0.8
    }
}

#declare Bomberman = merge {
    merge {
        object { 
            Chest 
            pigment{ color  rgb< 0.25, 0.25, 0.5> }
        } 
        object { Belt }
        object { BeltDetail }
    }
    // Arm
    sphere_sweep {
        b_spline
        4,
        <-5,0,0>, 0.5 
        <0,0,0>, 0.5 
        <7,4,0>, 0.5 
        <7,20,0>, 0.5 
        pigment { 
            White
        }
        finish {
            ambient 0.3
        }
        translate <0,4,0>
    }
    // Hand
    sphere {
        <0, 0, 0>, 1 // <x, y, z>, radius
        translate <6,10,0> 
        pigment {
            color <1,0,0.25>
        }
    }

    // Arm
    sphere_sweep {
        b_spline
        4,
        <0,0,0>, 0.5 
        <0,0,0>, 0.5 
        <-7,-4,0>, 0.5 
        <0,-5,0>, 0.5 
        pigment { 
            White
        }
        finish {
            ambient 0.3
        }
        translate <0,6,0>
    }
    // Hand
    sphere {
        <0, 0, 0>, 1 // <x, y, z>, radius
        translate <-5,2,0> 
        pigment {
            color <1,0,0.25>
        }
    }      
    //Leg
    sphere_sweep {
        linear_spline
        2,
        <-0.5,-2,0>, 0.5 
        <-2,-10,0>, 0.5 
        pigment { 
            White
        }
        finish {
            ambient 0.3
        }
        translate <0,5,0>
    }
    
    sphere_sweep {
        linear_spline
        2,
        <0.5,-2,0>, 0.5 
        <2,-10,0>, 0.5 
        pigment { 
            White
        }
        finish {
            ambient 0.3
        }
        translate <0,5,0>
    }
    object {
        Shoe
        translate <2,-6,1>
    }
    object {
        Shoe
        translate <-2,-6,1>
    }

    object {
        Head
    }

    translate <0,0,0>
} 

// ======================= Roller item ==================

#declare ItemBase = difference {
    box {
        <-1, -1, -1>, <1, 1, 1>
        pigment {
            color Red
        }
        scale <5,0.5,5>
    }
    box {
        <-1, -1, -1>, <1, 1, 1>
        pigment {
            color Green
        }
        scale <4.5,1,4.5>
        translate <0, 1,0>
    }
}



#declare Wheel = difference {
    cylinder {
        <0, 0, 0>, <0, 0, 1>, 1// center of one end, center of other end, radius
        pigment {
            color Yellow
        }
    }
    cylinder {
        <0, 0, 0>, <0, 0, 1>, 0.5// center of one end, center of other end, radius
        pigment {
            color BombGrayColor
        }
        translate <0,0,-0.5>
    }
}


#declare Strap = difference {
    intersection {
        cylinder {
            <0, 0, 0>, <0, 1, 0>, 4
            pigment {
                color Orange
            }
            scale <1.2,10,1.2>
            translate <4,3,0>
        }

        box {
            <-1, -1, -1>, <1, 1, 1> // <x, y, z> near lower left corner, <x, y, z> far upper right corner
            scale <10,0.5,10> 
            translate <0,10,0>
        }
    }


    box {
        <-1, -1, -1>, <1, 1, 1>
        scale <1,1,1> * 5
        translate <9,10,0>
    }
}

#declare RollerBody = merge {
    difference {
        sphere_sweep {
            linear_spline
            2,
            <-5,0,0>, 5
            <5,0,0>, 5 
            pigment { 
                color <0.0, 0.5, 1.0>
            }
            finish {
                ambient 0.2
            }
            scale <1,1.2,1>
        }
        box {
            <-1, -1, -1>, <1, 1, 1> 
            scale <15,5,5>
            translate <0,-5,0>
        }
    }
    cylinder {
        <0, 0, 0>, <0, 1, 0>, 4
        pigment {
            color <0.0, 0.5, 1.0>
        }
        scale <1,10,1>
        translate <4,3,0>
    }
}

#declare Roller = union {
    object {
        RollerBody
    }

    object {
        Strap
    }

    object {
        Strap
        translate <0,-2,0>
    }

    object {
        Wheel
        scale <1,1,1> * 3
        translate <4, 0, -7>
    }

    object {
        Wheel
        scale <1,1,1> * 3
        translate <-3.5,0,-7>
    }

    object {
        Wheel
        scale <1,1,1> * 3
        translate <4, 0, 4>
    }

    object {
        Wheel
        scale <1,1,1> * 3
        translate <-3.5,0,4>
    }
}

#declare RollerItem = union {
    object {
        Roller
        scale <1,1,1> * 0.35
        translate <0,2,-10>
    }
    object {
        ItemBase
        translate <0,0,-10>
    }
}

// ================== Skull ===========================

#declare Skull = difference {
    ovus {
        1, 1 // base_radius, top_radius (top_radius < base_radius)
        pigment {
            color White
        }
        rotate <0,0,90>
        scale <1,1.8,1.5> * 3
        finish {ambient 0.4}
    }
    box {
        <-1, -1, -1>, <1, 1, 1> // <x, y, z> near lower left corner, <x, y, z> far upper right corner
        scale <2,1.5,2> * 3 
        translate <0,-5,3>
        pigment {
            color White
        }
    }
    box {
        <-1, -1, -1>, <1, 1, 1> // <x, y, z> near lower left corner, <x, y, z> far upper right corner
        scale <4,2,2>  
        translate <-1,-4.2,-3>
        pigment {
            color White
        }
    }
    object{ // Round_Box(A, B, WireRadius, UseMerge)
        Round_Box(<-1,-1,-1>,<1,1,1>, 0.5 , 0)  
         
        scale<1.5,3,3>  
        rotate<0, 0,0> 
        translate<2.5,-3.5,-2.5>
        pigment {
            color White
        }
      } 
    object{ // Round_Box(A, B, WireRadius, UseMerge)
        Round_Box(<-1,-1,-1>,<1,1,1>, 0.5 , 0)  
         
        scale<1.5,3,3>  
        rotate<0, 0,0> 
        translate<-5,-3.5,-2.5>
        pigment {
            color White
        }
      } 
    object{//Round_Cone( point A, radius A, point B, radius B, rounding radius, merge on) 
         Round_Cone( <0,0,0>, 0.50    , <0,1.20,0>, 0.20 , 0.15, 0)  
         
         scale<0.3,2,4>  * 2
         rotate<0,0,0> 
         translate<0,-5.2,-3.5>
       } 

    object{//Round_Cone( point A, radius A, point B, radius B, rounding radius, merge on) 
         Round_Cone( <0,0,0>, 0.50    , <0,1.20,0>, 0.20 , 0.15, 0)  
         
         scale<0.3,2,4>  * 2
         rotate<0,0,0> 
         translate<-1.2,-5.2,-3.5>
       } 

    object{//Round_Cone( point A, radius A, point B, radius B, rounding radius, merge on) 
         Round_Cone( <0,0,0>, 0.50    , <0,1.20,0>, 0.20 , 0.15, 0)  
         
         scale<0.3,2,4>  * 2
         rotate<0,0,0> 
         translate<-2.4,-5.2,-3.5>
       } 

    ovus {
        1, 1
        translate < 0,1.5,-3> 
        scale <1,1,1.2> *1.2 
        rotate <0,0,0>
        pigment { 
            color Black
        }
    }
    ovus {
        1, 1
        translate < -3,1.5,-3> 
        scale <1,1,1.2> *1.2 
        rotate <0,0,0>
        pigment { 
            color Black
        }
    }
    sphere {
        <0, 0, 0>, 0.4 
        scale <1,1,5>
        translate <-1.8,1,-4.6> 
    }
}

#declare DebuffBase = difference {
    box {
        <-1, -1, -1>, <1, 1, 1>
        pigment {
            color Red
        }
        scale <5,0.5,5>
    }
    box {
        <-1, -1, -1>, <1, 1, 1>
        pigment {
            color Orange
        }
        scale <4.5,1,4.5>
        translate <0, 1,0>
    }
}

#declare DebuffItem = union {
    object {
        Skull
        scale <1,1,1> * 0.8
        translate <1,3,0>
    }
    sphere {
        <0, 0, 0>, 0.2 // <x, y, z>, radius
        translate <1,5,-2.5> 
        pigment {
            color Red
        }
        finish {ambient 4}
    } 
    sphere {
        <0, 0, 0>, 0.2 // <x, y, z>, radius
        translate <-1.5,5,-2.5> 
        pigment {
            color Red
        }
        finish {ambient 4}
    } 
    object {
        DebuffBase
    }
}

// ==================================== Mount ============================================

#declare Smile = difference {
    box {
        <-1, -1, -1>, <1, 1, 1> // <x, y, z> near lower left corner, <x, y, z> far upper right corner
        rotate <0,0,45> 
        pigment {
            color Black
        }
        scale <3,3.5,3>
    }

    cylinder {
        <0, 0, 5>, <0, 0, -4>, 4.8
        scale <1.1,1,1>
        translate <0,3.5,0>
        pigment {
            color Black
        }
    }
}
#declare MountBody = difference {
    object {//Round_Cone3( point A, radius A, point B, radius B, merge on) 
        Round_Cone3( <0,0,0>, 0.30, <0,0.8,0>, 0.80 , 0 )  
        pigment{ color Cyan } 
        scale<1,1,1> * 5  
        rotate<0,0,0> 
        translate<0,0.0,0>
    }
    object {
        Smile
        scale <0.9,0.8,1> * 0.6
        translate <0,5,-3>
    }
}

#declare Eye = merge {
    sphere {
        <0, 0, 0>, 1 // <x, y, z>, radius
        pigment { color < 0.5, 0.0, 1.0> } 
        scale <1.2,0.5,1>
    }

    sphere {
        <0, 0, 0>, 1 // <x, y, z>, radius
        pigment { color < 0.5, 0.0, 1.0> } 
        scale <1.2,0.5,1>
        rotate <0,0,90>
    }
}

#declare Mount = union {
    object {
        MountBody
    }
    object {
        Eye
        translate <1.5,7,-4>
    }
    object {
        Eye
        translate <-1.5,7,-4>
    }
    object{ // Round_Box(A, B, WireRadius, UseMerge)
        Round_Box(<-1,-1,-1>,<1,1,1>, 0.5 , 0)  
            
        scale<0.7,1.8,0.5>  
        rotate<-45,0,0> 
        translate<0,3,-2>
        pigment {
            color White
        }
    } 
    object{ // Round_Box(A, B, WireRadius, UseMerge)
        Round_Box(<-1,-1,-1>,<1,1,1>, 0.5 , 0)  
            
        scale<0.7,1.8,0.5>  
        rotate<-40,0,0> 
        translate<-1.55,4,-2>
        pigment {
            color White
        }
    } 
    object{ // Round_Box(A, B, WireRadius, UseMerge)
        Round_Box(<-1,-1,-1>,<1,1,1>, 0.5 , 0)  
            
        scale<0.7,1.8,0.5>  
        rotate<-40,0,0> 
        translate<1.55,4,-2>
        pigment {
            color White
        }
    } 
}

// ==================== Scene ==============================
#declare Scene = union {
    box {
        <-1, -1, -1>, <1, 1, 1> // <x, y, z> near lower left corner, <x, y, z> far upper right corner
        texture{ 
            pigment{ color rgb<0.35,0.65,0.0>*0.9 }
            normal { bumps 0.75 scale 0.015 }
            finish { phong 0.1 }
        } // end of texture
        translate < 0.1,0,0>
        scale <10.5,0.1,10> 
    }

    #declare Voxel = object {
        Round_Box(<-1,-1,-1>,<1,1,1>, 0.25 , 0)  
        scale<1,1,1>  rotate<0, 0,0> translate<0,1,0>
    }
    #declare WallTile = object {
        Voxel
        pigment {
            color <1,1,1> * 0.2
        }
    }

    union { 
        #local Nr = 0;     // start
        #local EndNr = 11; // end
        #while (Nr< EndNr) 

        object{ WallTile translate<Nr*2,0,0>} 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-9,0,-9>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 11; // end
        #while (Nr< EndNr) 

        object{ WallTile translate<Nr*2,0,0>} 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-9,0,9>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 8; // end
        #while (Nr< EndNr) 

        object{ WallTile translate <0,0,Nr*2> } 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-9,0,-7>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 8; // end
        #while (Nr< EndNr) 

        object{ WallTile translate <0,0,Nr*2> } 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<11,0,-7>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 4; // end
        #while (Nr< EndNr) 

        object{ WallTile translate<Nr*4,0,0>} 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-5,0,-2>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 4; // end
        #while (Nr< EndNr) 

        object{ WallTile translate<Nr*4,0,0>} 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-5,0,-6>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 4; // end
        #while (Nr< EndNr) 

        object{ WallTile translate<Nr*4,0,0>} 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-5,0,2>
    } 

    union { 
        #local Nr = 0;     // start
        #local EndNr = 4; // end
        #while (Nr< EndNr) 

        object{ WallTile translate<Nr*4,0,0>} 

        #local Nr = Nr + 1;  // next Nr
        #end // --------------- end of loop 

        rotate<0,0,0> 
        translate<-5,0,6>
    } 
    object {
        Bomb
        scale <1,1,1> * 0.5
        translate <-8,-2.2,0>
    }

    object {
        DebuffItem
        scale <0.9,1,0.9> * 0.22
        translate <5,0.1,4>
    }

    object {
        DebuffItem
        scale <0.9,1,0.9> * 0.22
        translate <-7,0.1,-4>
    }

    object {
        RollerItem
        scale <1,1,1> * 0.21
        translate <-7,0.1,2.2>
    }

    object {
        Mount
        scale <0.8,1,0.8> * 0.35
        rotate <0,90,0>
        translate <5,0.5,-3.5>
    }

    object {
        Bomberman
        scale <1,1,1> * 0.28
        translate <1,1.8,6>
    }

    object {
        Bomb
        scale <1,1,1> * 0.5
        translate <-2.2,2.2,6>
    }
}

object {
    Scene
} 
    