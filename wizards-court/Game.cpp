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
    tireRotation = 0;
}

int Game::Run() {
    if(Init() == false) {
        return -1;
    }
    
    LoadAssets();
    InitializeScene();
    
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

void Game::InitializeScene() {
    scene.Get("car").Translate(0, .05, 0);
    
    scene.Get("tire_front_driver").Translate(-.38,.155,-.55).Scale(-.25).RotateY(tireRotation);
    
    scene.Get("tire_rear_driver").Translate(-.38, .155, .49).Scale(-.25);
    
    scene.Get("tire_front_passenger").Translate(.38,.155,-.55).Scale(.25).RotateY(tireRotation);
    
    scene.Get("tire_rear_passenger").Translate(.38, .155, .49).Scale(.25);

    scene.Get("parking_lot").RotateY(60).Translate(-5.2,0,6);
    
}

bool Game::Init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((viewport = SDL_CreateWindow("Parking Lot", SCREEN_LOCATION_X, SCREEN_LOCATION_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0 | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL) {
        return false;
    }
    SDL_SetWindowFullscreen(viewport, 0);
    
    context = SDL_GL_CreateContext(viewport);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // the first parameters adjust location of viewport in window
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    //gluPerspective(90.0, 1.0, 0.1, 100);
    //glTranslatef(1.0f, -1.0f, -1.0f); // Local: +l/-r , -u/+d , +f/-b
    //glRotatef(0, 20.0f, 30.0f, 50.0f);
    

    glMatrixMode(GL_MODELVIEW);
    
    
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    //glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    //glDepthFunc( GL_EQUAL );
    
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    camera = Camera();
    
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);
    joystick1 = SDL_JoystickOpen(1);
    
    return true;
}

void Game::HandleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN){
        Running = false;
    }
    else if (e.type == SDL_QUIT) {
        Running =  false;
    }
    else if(e.type == SDL_JOYBUTTONDOWN) {
        cout << "Pressing Button: [" << e.jbutton.button << "]" << endl;
    }
    else if(e.type == SDL_JOYAXISMOTION) {
        if(e.jaxis.axis == LEFT_JOY_X)
            cameraDX = e.jaxis.value;
        if(e.jaxis.axis == LEFT_JOY_Y)
            cameraDY = e.jaxis.value;
        if(e.jaxis.axis == RIGHT_JOY_X)
            cameraRY = e.jaxis.value;
        if(e.jaxis.axis == RIGHT_JOY_Y)
            cameraRZ = e.jaxis.value;
    }
    else if(e.type == SDL_JOYHATMOTION) {

        if(e.jhat.value & SDL_HAT_LEFT) {
            inputs = (0 | DPAD_LEFT);
        }
        
        if(e.jhat.value & SDL_HAT_RIGHT) {
            inputs = (0 | DPAD_RIGHT);
        }
        
        if(e.jhat.value == 0) {
            inputs = 0;
        }
    }
}

void Game::Update() {
    if(inputs & DPAD_LEFT && tireRotation > -30) {
        tireRotation -= 3;
        scene.Get("tire_front_driver").RotateY(tireRotation);
        scene.Get("tire_front_passenger").RotateY(tireRotation);
    }
    else if(inputs & DPAD_RIGHT && tireRotation < 30) {
        tireRotation += 3;
        scene.Get("tire_front_driver").RotateY(tireRotation);
        scene.Get("tire_front_passenger").RotateY(tireRotation);
    }
    if(cameraDX > 256 || cameraDX < -256)
        camera.moveHorizontal(cameraDX/-100000);
    
    if(cameraDY > 256 || cameraDY < -256)
        camera.moveForward(cameraDY/100000);
    
    if(cameraRY > 256 || cameraRY < -256)
        camera.lookHorizontal(cameraRY/100000);
}

void Game::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    
    // Handle camera inputs
    //camera.AdjustCamera();
    
    scene.DrawScene(camera);
    
    SDL_GL_SwapWindow(viewport);
}

void Game::Cleanup() {
    //SDL_GL_DeleteContext(viewport);
    SDL_Quit();
}

void Game::LoadAssets() {
    ManifestParser assets = ManifestParser(RESOURCE_ROOT + "manifest/objects.manifest");
    ObjParser parser = ObjParser();

    map<string, GLuint> textures;

    for (auto& it: assets.GetTextures()) {
        GLuint tex = SOIL_load_OGL_texture((RESOURCE_ROOT + it.second).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        pair<string, GLuint> p = pair<string, GLuint>(it.first, tex);
        textures.insert( p );
    }
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    for (auto& it: assets.GetModels()) {
        Item temp = Item();
        parser.parseFile((RESOURCE_ROOT + it.second), &temp);
        temp.SetTexture(textures.at(it.first));
        scene.AddItem(it.first, temp);
    }
}