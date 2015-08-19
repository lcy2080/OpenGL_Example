//
//  Camera.h
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 15..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#ifndef __Template_OpenGL__Camera__
#define __Template_OpenGL__Camera__

#include <GLUT/GLUT.h>

class CCamera
{
public:
    CCamera();
    void Render();
    
    void RotAngleXinc();
    void RotAngleYinc();
    void RotAngleZinc();
    void RotAngleXdec();
    void RotAngleYdec();
    void RotAngleZdec();
private:
    GLfloat RotX,RotY,RotZ;
};

#endif /* defined(__Template_OpenGL__Camera__) */
