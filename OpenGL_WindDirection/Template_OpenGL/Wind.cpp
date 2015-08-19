//
//  Wind.cpp
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 17..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#include "Wind.h"

#include <math.h>
#include <iostream>

CWind* CWind::m_pWind = 0;

CWind* CWind::GetInstance()
{
    if (!m_pWind)
    {
        m_pWind = new CWind;
        m_pWind->init();
    }
    
    return m_pWind;
}

void CWind::init()
{
    WindPower = 0.0;
    WindDir = {1, 0, 1};
    
    double length = sqrt(WindDir.x*WindDir.x + WindDir.y*WindDir.y + WindDir.z*WindDir.z);
    
    if (length==0.0)
    {
        WindDir = {0.0,0.0,0.0};
    }
    else
    {
        WindDir = {WindDir.x/length,WindDir.y/length,WindDir.z/length};
    }
}

void CWind::Destroy()
{
    if (m_pWind)
    {
        delete m_pWind;
        m_pWind = 0;
    }
}

void CWind::Render()
{
    //std::cout << "CWind Render" << std::endl;
    //std::cout << "Wind Dir : " << WindDir.x << "," << WindDir.y << "," << WindDir.z << std::endl;
    //std::cout << "Wind Power : " << WindPower << std::endl;
    glColor3f(0, 1, 0);
    for (int x = -20; x<=20; x++)
    {
        for (int y = -20; y<=20; y++)
        {
            glBegin(GL_LINES);
            
            glVertex3d((double)x, (double)y, 0);
            glVertex3d((double)x + WindDir.x, (double)y + WindDir.y, (double)0 + WindDir.z);
            
            glEnd();
        }
    }
}

Vec3 CWind::GetWind(const Vec3 &position)
{
    Vec3 result;
    
    result = {
        WindDir.x * WindPower,
        WindDir.y * WindPower,
        WindDir.z * WindPower
    };
    
    return result;
}

void CWind::WindInc()
{
    WindPower += 10.0;
}

void CWind::WindDec()
{
    WindPower -= 10.0;
}
