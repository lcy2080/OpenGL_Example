//
//  Flag.h
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 16..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#ifndef __Template_OpenGL__Flag__
#define __Template_OpenGL__Flag__

#include <GLUT/GLUT.h>

#include "Vector3.h"

struct MassPoint
{
    bool fixed;
    Vec3 prev;
    Vec3 position;
    Vec3 velocity;
    Vec3 accel;
};

class CFlag
{   //Singleton Pattern
private:
    static CFlag* m_pFlag;
    void init();
    MassPoint points[7][9];
    
public:
    static CFlag* GetInstance();
    static void Destroy();
    void Render(const double &delta);
    void PositionUpdate(const double &delta);
    
    double wind_x;
    double wind_z;
};

#define g_Flag CFlag::GetInstance()

#endif /* defined(__Template_OpenGL__Flag__) */
