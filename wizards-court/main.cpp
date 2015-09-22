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
#include "main.h"
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
    controller = Controller();
    
    glutMainLoop();
    
    glutDestroyWindow(viewport);
    exit(0);
    return 0;		
}

void loadTextures() {
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/parking_lot.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[1] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/tire.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[2] = SOIL_load_OGL_texture("/Users/Daniel/workspace/wizards-court/wizards-court/textures/car.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
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
    parking_lot = Item();
    car = Item();
    tire1 = Item();
    tire2 = Item();
    tire3 = Item();
    tire4 = Item();
    
    ObjParser parser = ObjParser();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/ParkingLot.obj", &parking_lot);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/car.obj", &car);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire1);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire2);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire3);
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire4);
}

void drawItem(Item item, GLuint textureId) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    for(int i=0; i<item.faces.size(); i++) {
        glBegin(GL_POLYGON);
        for(int j=0; j<item.faces[i].vertices.size(); j++) {
            glTexCoord2f(item.faces[i].textureCoordinates[j].x, item.faces[i].textureCoordinates[j].y);
            glVertex3f(item.faces[i].vertices[j].x, item.faces[i].vertices[j].y, item.faces[i].vertices[j].z);
        }
        glEnd();
    }
}


void drawScene() {
    glClear (GL_COLOR_BUFFER_BIT);
    
    drawItem( parking_lot, texture[0]);
    drawItem( car, texture[2]);
    drawItem( tire1, texture[1]);
    drawItem( tire2, texture[1]);
    drawItem( tire3, texture[1]);
    drawItem( tire4, texture[1]);
    
    glFlush ();
}

void setCamera() {
    glTranslatef(0.0f, -2.0f, -2.0f); // Local: +l/-r , -u/+d , +f/-b
    glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
}

void handleEvents() {
    while (SDL_PollEvent(&controller.sdlEvent)){
        //If user presses any key
        if (controller.sdlEvent.type == SDL_KEYDOWN){
            cout << "Key" << endl;
        }
        //If user clicks the mouse
        if (controller.sdlEvent.type == SDL_MOUSEBUTTONDOWN){
            cout << "mouse" << endl;
        }
    }

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    handleEvents();
    
    setCamera();
    drawScene();
    
    glutSwapBuffers();
}


int   x_axis  = 0;
int   y_axis  = 0;
int   z_axis  = 0;
int   button1 = 0;
int   button2 = 0;
int   button3 = 0;
int   button4 = 0;
int   button5 = 0;
void updateFlags(unsigned int buttonmask, int x, int y, int z)
{
    x_axis  = x;
    y_axis  = y;
    z_axis  = z;
    
    if (buttonmask & 0x01)  button1 = 1;
    else  button1 = 0;
    if (buttonmask & 0x02)  button2 = 1;
    else  button2 = 0;
    if (buttonmask & 0x04)  button3 = 1;
    else  button3 = 0;
    if (buttonmask & 0x08)  button4 = 1;
    else  button4 = 0;
    if (buttonmask & 0x10)  button5 = 1;
    else  button5 = 0;
    
    if(button1)
        cout << "button 1 down" << endl;
    if(button2)
        cout << "button 2 down" << endl;
    if(button3)
        cout << "button 3 down" << endl;
    if(button4)
        cout << "button 4 down" << endl;
    if(button5)
        cout << "button 5 down" << endl;
    
    if (x != 3 || y != -3) {
        cout << "x: " << x << "y: " << y << "z: " << z << endl;
    }
}


void createWindow()
{

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (900, 900);
    viewport = glutCreateWindow ("Parking Lot");
}

void initializeSettings()
{
    printf(" joystick %i - buttons %i - axes %i \n", glutDeviceGet(GLUT_HAS_JOYSTICK), glutDeviceGet(GLUT_JOYSTICK_BUTTONS), glutDeviceGet(GLUT_JOYSTICK_AXES));

    glutJoystickFunc(updateFlags, 25);
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
