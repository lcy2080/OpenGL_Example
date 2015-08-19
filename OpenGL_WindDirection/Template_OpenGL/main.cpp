//
//  main.cpp
//  Template_OpenGL
//
//  Created by 이창영 on 2015. 8. 12..
//  Copyright (c) 2015년 이창영. All rights reserved.
//

#include <iostream>

using namespace std;

/*glut for Windows*/
//#include <GL/glut.h>

/*glut for Mac*/
//#include <OpenGL/OpenGL.h>
//#include <OpenGL/gl.h>
//#include <GL/glew.h>

//#include <OpenGL/gl3.h>


#include <GLUT/GLUT.h>

#include "Camera.h"

#include <time.h>

#include <math.h>

#include "Flag.h"

#include "Wind.h"

clock_t update_time;

clock_t physics_time;

int prev_time_physics;
int current_time_physics;
int prev_time_draw;
int current_time_draw;

/*GLUT display callback function*/
void display(void);

/*GLUT window reshape callback function*/
void reshape(int, int);

/*GLUT Idle function*/
void idle();

struct Point3D
{
    double x,y,z;
};


struct CamPos3D
{
    GLdouble x,y,z;
};

GLfloat Rotx = 0.0f;
GLfloat Roty = 0.0f;
GLfloat Rotz = 0.0f;

CamPos3D _CamPos;

CCamera Camera;

void KeyDown(unsigned char key, int x, int y)
{
    //std::cout << "keyboard input" << std::endl;
    switch (key)
    {
        case 'q':
            Rotx += 2.0f;
            //Camera.RotAngleXinc();
            break;
        case 'a':
            Rotx -= 2.0f;
            //Camera.RotAngleXdec();
            break;
        case 'w':
            Roty += 2.0f;
            //Camera.RotAngleYinc();
            break;
        case 's':
            Roty -= 2.0f;
            //Camera.RotAngleYdec();
            break;
        case 'e':
            Rotz += 2.0f;
            //Camera.RotAngleZinc();
            break;
        case 'd':
            Rotz -= 2.0f;
            //Camera.RotAngleZdec();
            break;
        case 'z':
            Rotx = 0.0f;
            Roty = 0.0f;
            Rotz = 0.0f;
            break;
        case 'r':
            g_Wind->WindInc();
            //g_Flag->wind_x += 1000;
            break;
        case 'f':
            g_Wind->WindDec();
            //g_Flag->wind_x -= 1000;
            break;
        case 't':
            //g_Flag->wind_z += 1000;
            break;
        case 'g':
            //g_Flag->wind_z -= 1000;
            break;
    }
}

int main(int argc, char * argv[])
{
    //init
    glutInit(&argc, argv);
    
    //initiallize time
    current_time_physics = glutGet(GLUT_ELAPSED_TIME);
    current_time_draw = current_time_physics;
    prev_time_physics = current_time_physics;
    prev_time_draw = current_time_physics;
    
    update_time = clock();
    physics_time = update_time;
    
    _CamPos.x = 0.0f;
    _CamPos.y = 0.0f;
    _CamPos.z = 25.0f;
    

    
    //set the window size 512*512
    glutInitWindowSize(512, 512);
    
    /*
     Set the display color to Red,Green,Blue and Alpha
     Allocate a depth buffer
     enable double buffering
     */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    //set the window position
    glutInitWindowPosition(0, 0);
    
    //Create the window and Call it "OpenGL_Template"
    glutCreateWindow("OpenGL_Template");
    
    /*
     Set the glut display callback function
     this is the function GLUT will call every time
     the window needs to be drawn
     */
    glutDisplayFunc(display);
    
    /*
     Set the glut reshape callback function
     this is the function GLUT will call whenever
     the window is resized, including when it is first created
     */
    glutReshapeFunc(reshape);
    
    /*Set the glut Keyboard input callback function*/
    glutKeyboardFunc(KeyDown);
    
    glutIdleFunc(idle);
    /*set the default background color to black*/
    glClearColor(0, 0, 0, 1);
    
    /*
     enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
    
    return 0;
}


void display()
{
    clock_t now_time = clock();
    
    
//    std::cout << "now_time : " << now_time << std::endl;
//    std::cout << "update_time : " << update_time << std::endl;
//    std::cout << now_time - update_time << std::endl;
    
    //redraw time
    //std::cout << (double)(now_time - update_time) / (double)CLOCKS_PER_SEC << std::endl;
    
    //fps
    //std::cout << (float) CLOCKS_PER_SEC / (float) (now_time - update_time) << std::endl;
    
    
    //std::cout << "display" << std::endl;
    
    //Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLdouble ratio = 512.0/512.0;
    
    gluPerspective(60.0, ratio, 10.0, 100.0);
    
    Camera.Render();
    
    //set the current drawing color to red
    glColor3f(1, 0, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(_CamPos.x, _CamPos.y, _CamPos.z,    // eye x,y,z
              0., 0., 0.,       // center x,y,z
              0., 1., 0.);      // Up direction
    
    //std::cout << Rotx << std::endl;
    
    glRotatef(Rotx, 1.0, 0.0, 0.0);
    glRotatef(Roty, 0.0, 1.0, 0.0);
    glRotatef(Rotz, 0.0, 0.0, 1.0);
    
    //start drawing triangles, each triangles takes 3 vertices
    //cout << "input delta : " << (double)(now_time - update_time) / (double)CLOCKS_PER_SEC << endl;
    //cout << "draw fps : " <<  (double)CLOCKS_PER_SEC / (double)(now_time - update_time)<< endl;
    
    //current_time_physics = glutGet(GLUT_ELAPSED_TIME);
    current_time_draw = glutGet(GLUT_ELAPSED_TIME);
    
    bool updated = false;
    while ((current_time_draw - prev_time_draw) < 15 || !updated)
    {
        current_time_physics = glutGet(GLUT_ELAPSED_TIME);
        current_time_draw = current_time_physics;
        
        if (current_time_physics - prev_time_physics > 7)
        {
            std::cout << "physics fps : " << 1000.0f/(float) (current_time_physics-prev_time_physics)<< std::endl;
            g_Flag->PositionUpdate((double)(current_time_physics-prev_time_physics) / 1000.0);
            prev_time_physics = current_time_physics;
            updated = true;
        }
    }
    std::cout << "draw fps : " << 1000.0f/(float) (current_time_draw-prev_time_draw)<< std::endl;
    g_Wind->Render();
    g_Flag->Render((float) (current_time_draw-prev_time_draw) / 1000.0);
    
    prev_time_draw = current_time_draw;
    
    glFlush();
    //swap the back and front buffers so we can see what we just drew
    glutSwapBuffers();
    
}

void reshape(int width, int height)
{
    /*
     tell OpenGL we want to display in a rectangle
     that is the same size as the window
     */
    glViewport(0, 0, width, height);
    
    //switch to the projection martix
    glMatrixMode(GL_PROJECTION);
    
    //clear the projection matrix
    glLoadIdentity();
    
    //set the camera view, orthographic projection in 2D
    gluOrtho2D(0, width, 0, height);
    
    //switch back to the model view matrix
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    display();
}