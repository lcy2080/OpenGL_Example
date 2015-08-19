//
//  Flag.cpp
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 16..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#include "Flag.h"
#include "Wind.h"
#include <math.h>
#include <iostream>

CFlag* CFlag::m_pFlag = 0;

CFlag* CFlag::GetInstance()
{
    if (m_pFlag == 0)
    {
        m_pFlag = new CFlag;
        m_pFlag->init();
    }
    return m_pFlag;
}

void CFlag::Destroy()
{
    if (m_pFlag)
    {
        delete m_pFlag;
        m_pFlag = 0;
    }
}

#define gravity -10.0

void CFlag::init()
{
    for (int row = 0; row<7; row++)
    {
        for (int col = 0; col<9; col++)
        {
            points[row][col].velocity = {0.0, 0.0, 0.0};
            points[row][col].position = {-4.0+(double)col,3.0-(double)row,(((row+col)%2)-0.5)/5.0};
            points[row][col].prev = points[row][col].position;
            points[row][col].accel = {0.0,gravity,0.0};
            points[row][col].fixed = false;
        }
    }
    
    for (int n=0;n<7;n++)
    {
        //if (n==0 || n==6)
            points[n][0].fixed = true;
    }
    //points[6][8].position = {2,-2,0};
    
    wind_x = 0.0;
    wind_z = 0.0;
}

void CFlag::Render(const double &delta)
{
    //Position Update
    //PositionUpdate(delta);
    
    glColor3f(1, 0, 0);
    
    //horizontal line
    for (int row = 0; row<7; row++)
    {
        glBegin(GL_LINE_STRIP);
        for (int col=0; col<9; col++)
        {
            glVertex3d(points[row][col].position.x, points[row][col].position.y, points[row][col].position.z);
        }
        glEnd();
    }
    
    //vertical line
    for (int col = 0; col<9; col++)
    {
        glBegin(GL_LINE_STRIP);
        for (int row=0; row<7; row++)
        {
            glVertex3d(points[row][col].position.x, points[row][col].position.y, points[row][col].position.z);
        }
        glEnd();
    }
}

void CFlag::PositionUpdate(const double &delta)
{
    
    for (int row = 0; row<7; row++)
    {
        for (int col = 0; col<9; col++)
        {
            //accel init
            Vec3 Wind = g_Wind->GetWind(points[row][col].position);
            
            double Rwind_x = rand()%10*400 + Wind.x;
            double Rwind_z = rand()%10*400 + Wind.z;
            
            if (Wind.x==0.0) Rwind_x = 0.0;
            if (Wind.z==0.0) Rwind_z = 0.0;
            //std::cout << "wind_x : " << Rwind_x << std::endl;
            //std::cout << "wind_z : " << Rwind_z << std::endl;
            
            points[row][col].accel = {Rwind_x,-1000.0,Rwind_z};
            
            double k_factor1 = 10000.0;
            double k_factor2 = 1000.0;
            double k_factor3 = 500.0;
            double Dist1 = 1.0;
            double Dist2 = 2.0;
            double Dist3 = sqrt(2.0);
            
            //accel horizontal
            //col-1
            if (col-1>=0)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row][col-1].position.x,
                    points[row][col].position.y - points[row][col-1].position.y,
                    points[row][col].position.z - points[row][col-1].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor1*(length-Dist1);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //col+1
            if (col+1<9)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row][col+1].position.x,
                    points[row][col].position.y - points[row][col+1].position.y,
                    points[row][col].position.z - points[row][col+1].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor1*(length-Dist1);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            
            //accel horizontal2
            //col-2
            if (col-2>=0)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row][col-2].position.x,
                    points[row][col].position.y - points[row][col-2].position.y,
                    points[row][col].position.z - points[row][col-2].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor2*(length-Dist2);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //col+2
            if (col+2<9)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row][col+2].position.x,
                    points[row][col].position.y - points[row][col+2].position.y,
                    points[row][col].position.z - points[row][col+2].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor2*(length-Dist2);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }

            
            //accel vertical
            //row-1
            if (row-1>=0)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row-1][col].position.x,
                    points[row][col].position.y - points[row-1][col].position.y,
                    points[row][col].position.z - points[row-1][col].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor1*(length-Dist1);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //row+1
            if (row+1<7)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row+1][col].position.x,
                    points[row][col].position.y - points[row+1][col].position.y,
                    points[row][col].position.z - points[row+1][col].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor1*(length-Dist1);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            
            //accel vertical2
            //row-2
            if (row-2>=0)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row-2][col].position.x,
                    points[row][col].position.y - points[row-2][col].position.y,
                    points[row][col].position.z - points[row-2][col].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor2*(length-Dist2);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //row+2
            if (row+2<7)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row+2][col].position.x,
                    points[row][col].position.y - points[row+2][col].position.y,
                    points[row][col].position.z - points[row+2][col].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor2*(length-Dist2);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            
            //accel 대각선 1
            //row-1 col-1
            if (row-1>=0 && col-1>=0)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row-1][col-1].position.x,
                    points[row][col].position.y - points[row-1][col-1].position.y,
                    points[row][col].position.z - points[row-1][col-1].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor3*(length-Dist3);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //row-1 col+1
            if (row-1>=0 && col+1<9)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row-1][col+1].position.x,
                    points[row][col].position.y - points[row-1][col+1].position.y,
                    points[row][col].position.z - points[row-1][col+1].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor3*(length-Dist3);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //row+1 col-1
            if (row+1<7 && col-1>=0)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row+1][col-1].position.x,
                    points[row][col].position.y - points[row+1][col-1].position.y,
                    points[row][col].position.z - points[row+1][col-1].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor3*(length-Dist3);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }
            //row+1 col+1
            if (row+1<7 && col+1<9)
            {
                Vec3 Dir = {
                    points[row][col].position.x - points[row+1][col+1].position.x,
                    points[row][col].position.y - points[row+1][col+1].position.y,
                    points[row][col].position.z - points[row+1][col+1].position.z
                };
                
                double length = sqrt(Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
                
                Vec3 Norm = {Dir.x/length, Dir.y/length, Dir.z/length};
                
                double Accel = - k_factor3*(length-Dist3);
                
                points[row][col].accel = {
                    points[row][col].accel.x + Accel*Norm.x,
                    points[row][col].accel.y + Accel*Norm.y,
                    points[row][col].accel.z + Accel*Norm.z
                };
            }


            
            if (row==6 && col==8)
            {
//                std::cout << "delta : " << delta <<std::endl;
//            std::cout << "Velocity : " <<
//            points[row][col].velocity.x << "," <<
//            points[row][col].velocity.y << "," <<
//            points[row][col].velocity.z << std::endl;
            }
            
            //velocity
            points[row][col].velocity = {
                points[row][col].velocity.x*0.95 + delta * points[row][col].accel.x,
                points[row][col].velocity.y*0.95 + delta * points[row][col].accel.y,
                points[row][col].velocity.z*0.95 + delta * points[row][col].accel.z
            };
            
            if (row==6 && col==8)
            {
//                std::cout << "Accel : " <<
//                points[row][col].accel.x << "," <<
//                points[row][col].accel.y << "," <<
//                points[row][col].accel.z << std::endl;
            }
        }
    }
    
    for (int row = 0 ; row<7 ; row++)
    {
        for (int col = 0; col<9 ; col++)
        {
            //position
            if (!points[row][col].fixed)
            {
//                Vec3 Pos = {
//                    2 * points[row][col].position.x - points[row][col].prev.x + delta * delta * points[row][col].accel.x,
//                    2 * points[row][col].position.y - points[row][col].prev.y + delta * delta * points[row][col].accel.y,
//                    2 * points[row][col].position.z - points[row][col].prev.z + delta * delta * points[row][col].accel.z
//                };
//                
//                points[row][col].prev = points[row][col].position;
//                
//                points[row][col].position = Pos;
//                
                points[row][col].position = {
                    points[row][col].position.x + delta*points[row][col].velocity.x,
                    points[row][col].position.y + delta*points[row][col].velocity.y,
                    points[row][col].position.z + delta*points[row][col].velocity.z,
                };
            }
        }
    }
}