//
//  Camera.cpp
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 15..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#include "Camera.h"

CCamera::CCamera()
{
    RotX = 0;
    RotY = 0;
    RotZ = 0;
}

void CCamera::Render()
{
    glRotatef(RotX, 1.0f, 0.0f, 0.0f);
    glRotatef(RotY, 0.0f, 1.0f, 0.0f);
    glRotatef(RotZ, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);
}

void CCamera::RotAngleXinc()
{
    RotX+=15.0f;
}
void CCamera::RotAngleYinc()
{
    RotY+=15.0f;
}
void CCamera::RotAngleZinc()
{
    RotZ+=15.0f;
}
void CCamera::RotAngleXdec()
{
    RotX-=15.0f;
}
void CCamera::RotAngleYdec()
{
    RotY-=15.0f;
}
void CCamera::RotAngleZdec()
{
    RotZ-=15.0f;
}