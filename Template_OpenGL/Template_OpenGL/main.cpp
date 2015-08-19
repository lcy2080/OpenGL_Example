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
#include <GLUT/GLUT.h>

/*GLUT display callback function*/
void display(void);

/*GLUT window reshape callback function*/
void reshape(int, int);

int main(int argc, char * argv[])
{
    //init
    glutInit(&argc, argv);
    
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
    
    /*set the default background color to black*/
    glClearColor(0, 0, 0, 1);
    
    /*
     enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
    //glutInit(&argc, argv);
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


void display()
{
    //Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    //set the current drawing color to red
    glColor3f(1, 0, 0);
    
    //start drawing triangles, each triangles takes 3 vertices
    glBegin(GL_TRIANGLES);
    
    glVertex2f(10, 10);
    glVertex2f(250, 400);
    glVertex2f(400, 10);
    
    //tell OpenGL we're done drawing triangles
    glEnd();
    
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