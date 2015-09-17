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
#include "SOIL.h"

using namespace std;

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    createWindow();
    glutDisplayFunc(display);
    initializeSettings();
    importModels();
    loadTextures();
    
    glutMainLoop();
    
    glutDestroyWindow(viewport);
    exit(0);
    return 0;		
}

void loadTextures() {
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/box.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[1] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/blue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[2] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/green.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[3] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/purple.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    if(texture[0] == 0)
        cout << "Failed to load texture." << endl;
    else
        cout << "Loaded" << endl;


    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);                                    // Return Success
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);}

void importModels() {
    crayonBox = Item();
    crayon1 = Item();
    
    ObjParser parser = ObjParser();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/CrayonBox_simple.obj", &crayonBox);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/Crayon.obj", &crayon1);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/Crayon.obj", &crayon2);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/Crayon.obj", &crayon3);
}


void drawScene() {
    glClear (GL_COLOR_BUFFER_BIT);
    
    for(int i=0; i<crayonBox.faces.size(); i++) {
        glBegin(GL_POLYGON);
        for(int j=0; j<crayonBox.faces[i].vertices.size(); j++) {
            glTexCoord2f(crayonBox.faces[i].textureCoordinates[j].x, crayonBox.faces[i].textureCoordinates[j].y);
            glVertex3f(crayonBox.faces[i].vertices[j].x-2, crayonBox.faces[i].vertices[j].y, crayonBox.faces[i].vertices[j].z+1);
        }
        glEnd();
    }
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    
    for(int i=0; i<crayon1.faces.size(); i++) {
        glBegin(GL_POLYGON);
        for(int j=0; j<crayon1.faces[i].vertices.size(); j++) {
            glTexCoord2f(crayon1.faces[i].textureCoordinates[j].x, crayon1.faces[i].textureCoordinates[j].y);
            glVertex3f(crayon1.faces[i].vertices[j].x+1, crayon1.faces[i].vertices[j].y, crayon1.faces[i].vertices[j].z - .2);
        }
        glEnd();
    }
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    
    for(int i=0; i<crayon2.faces.size(); i++) {
        glBegin(GL_POLYGON);
        for(int j=0; j<crayon2.faces[i].vertices.size(); j++) {
            glTexCoord2f(crayon2.faces[i].textureCoordinates[j].x, crayon2.faces[i].textureCoordinates[j].y);
            glVertex3f(crayon2.faces[i].vertices[j].x+3, crayon2.faces[i].vertices[j].y, crayon2.faces[i].vertices[j].z - .2);
        }
        glEnd();
    }
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    
    for(int i=0; i<crayon3.faces.size(); i++) {
        glBegin(GL_POLYGON);
        for(int j=0; j<crayon3.faces[i].vertices.size(); j++) {
            glTexCoord2f(crayon3.faces[i].textureCoordinates[j].x, crayon3.faces[i].textureCoordinates[j].y);
            glVertex3f(crayon3.faces[i].vertices[j].x+5, crayon3.faces[i].vertices[j].y, crayon3.faces[i].vertices[j].z - .2);
        }
        glEnd();
    }
    
    glFlush ();
}

void setCamera() {
    glTranslatef(0.0f, 0.0f, -10.0f); // Local: +l/-r , -u/+d , +f/-b
    glRotatef(160.0f, 0.0f, 1.0f, 0.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    
//    glPushMatrix();
//    glTranslatef(0.0f, 0.0f, 0.0f);
//    glPopMatrix();
    
    setCamera();
    
    drawScene();
    
    glutSwapBuffers();
}

void createWindow()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);
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
