//
//  Wind.h
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 17..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#ifndef __Template_OpenGL__Wind__
#define __Template_OpenGL__Wind__

#include <GLUT/GLUT.h>

#include "Vector3.h"

class CWind
{
private:
    static CWind* m_pWind;
    void init();
    
    Vec3 WindDir;
    double WindPower;
public:
    static CWind* GetInstance();
    static void Destroy();
    
    void Render();
    
    Vec3 GetWind(const Vec3 &position);
    
    void WindInc();
    void WindDec();
};

#define g_Wind CWind::GetInstance()

#endif /* defined(__Template_OpenGL__Wind__) */
