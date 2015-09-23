//
//  Game.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/21/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Game.h"
#include <iostream>


Game::Game() {
    viewport = NULL;
    Running = true;
}

int Game::Run() {
    if(Init() == false) {
        return -1;
    }
    
    LoadAssets();
    
    SDL_Event Event;
    
    while(Running) {
        while(SDL_PollEvent(&Event)) {
            HandleEvent(Event);
        }
        
        Update();
        Render();
    }
    
    Cleanup();
    
    return 0;
}

bool Game::Init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    
    //SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_GL_DOUBLEBUFFER | SDL_WINDOW_OPENG
    if((viewport = SDL_CreateWindow("Parking Lot", SCREEN_LOCATION_X, SCREEN_LOCATION_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0 | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL) {
        return false;
    }
    SDL_SetWindowFullscreen(viewport, 0);
    
    context = SDL_GL_CreateContext(viewport);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // the first parameters adjust location of viewport in window
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    return true;
}

void Game::HandleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN){
        Running = false;
    }
}

void Game::Update() {
    
}

void Game::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    camera.AdjustCamera();
    
    scene.DrawScene();
    
    SDL_GL_SwapWindow(viewport);
}

void Game::Cleanup() {
    //SDL_GL_DeleteContext(viewport);
    SDL_Quit();
}

void Game::LoadAssets() {
    
}

void Game::LoadTextures() {
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

void Game::ImportModels() {
    
    ObjParser parser = ObjParser();
    
    Item parking_lot = Item();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/ParkingLot.obj", &parking_lot);
    parking_lot.SetTexture(texture[0]);
    
    Item car = Item();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/car.obj", &car);
    car.SetTexture(texture[2]);
    
    Item tire1 = Item();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire1);
    tire1.SetTexture(texture[1]);
    
    Item tire2 = Item();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire2);
    tire2.SetTexture(texture[1]);
    
    Item tire3 = Item();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire3);
    tire3.SetTexture(texture[1]);
    
    Item tire4 = Item();
    parser.parseFile("/Users/Daniel/workspace/wizards-court/wizards-court/models/tire.obj", &tire4);
    tire4.SetTexture(texture[1]);
    
    scene.AddItem(parking_lot);
    scene.AddItem(car);
    scene.AddItem(tire1);
    scene.AddItem(tire2);
    scene.AddItem(tire3);
    scene.AddItem(tire4);
    
    // Translate Car
    Vertex v = Vertex(0.1,0,0);
    scene.GetPositionedItem(1).GetMatrix().SetTranslation(v);
}
