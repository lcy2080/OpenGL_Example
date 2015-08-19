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

#include </usr/include/GL/glew.h>
#include <GLUT/GLUT.h>

GLuint VBO;

/*GLUT display callback function*/
void display(void);

/*GLUT window reshape callback function*/
void reshape(int, int);

/*GLUT Idle function*/
void idle();


static void InitializeGlutCallbacks()
{
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
    //glutReshapeFunc(reshape);
    
    //glutIdleFunc(idle);

}

struct Vector3f
{
    GLfloat x,y,z;
    Vector3f(){}
    Vector3f(GLfloat _x,GLfloat _y, GLfloat _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(0.0f, 1.0f, 0.0f);
    Vertices[1] = Vector3f(-1.0f, -1.0f,0.0f);
    Vertices[2] = Vector3f(1.0f, -1.0f,0.0f);
    /*
     glGenBuffers를 이용하여 1개의 Buffer를 할당받아 GLuint 타입의 VBO로 그래픽 메모리의 주소를 반환한다.
     */
    glGenBuffers(1, &VBO);
    /*
     The target GL_ARRAY_BUFFER means that the buffer will contain an array of vertices.
     Another useful target is GL_ELEMENT_ARRAY_BUFFER which means that the buffer contains the indices of the vertices in another buffer.
     */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
     Binding 후 Binding 한 주소로 데이터를 채워넣는 작업
     GL_STATIC_DRAW 을 이용하면 Buffer의 내용을 바꾸지 못한다.
     The opposite will be GL_DYNAMIC_DRAW.
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


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
    
    InitializeGlutCallbacks();
    
    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    
    /*set the default background color to black*/
    glClearColor(0, 0, 0, 1);
    
    CreateVertexBuffer();
    
    /*
     enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
    
    return 0;
}


void display()
{
    //Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    /*
     for Draw call, re Bind the buffer.
     vertex가 하나이기 때문에 매 프레임마다 Bind해도 상관 없으나 커지면 다른 방식을 사용해야 한다.
     */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
     이 부분은 Buffer안의 데이터를 어찌 처리 할지에 대해 언급하는 부분.
     첫 parameter는 attribute의 index를 특정하는 부분
     두번째는 component의 개수 : 현재는 x,y,z 3개 이므로 3,
     세번째는 component의 type,
     네번째는 attribute를 사용하기 전에 normalize 할 것인가 여부,
     다섯번째는 stride : the number of bytes between two instances of that attribute in the buffer.
     in hear, there is only one attribute. vertex position.
     if we have two attribute, position and normal 6component * 4bytes -> 24.
     last is offset of attribute, if we have position and normal, position's offset is 0, normal's offset is 12.
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    /*
     make the call to draw the geometry. GPU start to work from this point.
     first : what GPU draw
     second : start
     third : end
     */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    /*
     사용하지 않는 vertex를 즉각적으로 disable 해준다. 남겨두는 것은 쉐이더 적용시 문제를 유발 할 수 있다.
     */
    glDisableVertexAttribArray(0);
    
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