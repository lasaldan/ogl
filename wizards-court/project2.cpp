//
//  main.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/12/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <vector>
#include "project2.h"
using namespace std;

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    createWindow();
    glutDisplayFunc(display);
    initializeSettings();
    importModels();
    
    glutMainLoop();
    
    glutDestroyWindow(viewport);
    exit(0);
    return 0;		
}

void importModels() {
    crayonBox = Item();
    crayon1 = Item();
    
    ObjParser parser("/Users/Daniel/workspace/wizards-court/wizards-court/CrayonBox.obj", &crayonBox);
}

void drawScene() {
    /*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    
    /*  draw white polygon (rectangle) with corners at
     *  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
     */
    glColor3f (1.0, 1.0, 1.0);
    //glBegin(GL_POLYGON);
    glBegin(GL_QUADS);
    
    for(int i=0; i<crayonBox.vertices.size(); i++) {
        glVertex3f(crayonBox.vertices[i].x, crayonBox.vertices[i].y, crayonBox.vertices[i].z);
    }
    /*
    glVertex3f (0.25, 0.25, 0.0);
    glVertex3f (0.75, 0.25, 0.0);
    glVertex3f (0.75, 0.75, 0.0);
    glVertex3f (0.25, 0.75, 0.0);
     */
    glEnd();
    
    cout << crayonBox.GetVertices().size() << endl;
    cout << crayonBox.GetTextureCoordinates().size() << endl;
    cout << crayonBox.GetFaces().size() << endl;
    
    /*  don't wait!
     *  start processing buffered OpenGL routines
     */
    glFlush ();
}

void setCamera() {
    glTranslatef(0.0f,-0.75f, -12.0f);
    glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    glPopMatrix();
    
    setCamera();
    
    drawScene();
    
    glutSwapBuffers();
}

void createWindow()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (512, 512);
    viewport = glutCreateWindow ("Crayons");
}

void initializeSettings()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
