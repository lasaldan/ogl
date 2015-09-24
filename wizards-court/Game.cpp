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
    Vertex car_location = Vertex(0,.05,0);
    scene.Get("car").GetMatrix().SetTranslation(car_location);
    
    Vertex tire_1_loc = Vertex(-.38,.155,-.55);
    scene.Get("tire_front_driver").GetMatrix().SetTranslation(tire_1_loc);
    scene.Get("tire_front_driver").GetMatrix().SetScale(-.25);
    
    Vertex tire_2_loc = Vertex(-.38,.155,.49);
    scene.Get("tire_rear_driver").GetMatrix().SetTranslation(tire_2_loc);
    scene.Get("tire_rear_driver").GetMatrix().SetScale(-.25);
    
    Vertex tire_3_loc = Vertex(.38,.155,-.55);
    scene.Get("tire_front_passenger").GetMatrix().SetTranslation(tire_3_loc);
    scene.Get("tire_front_passenger").GetMatrix().SetScale(.25);
    
    Vertex tire_4_loc = Vertex(.38,.155,.49);
    scene.Get("tire_rear_passenger").GetMatrix().SetTranslation(tire_4_loc);
    scene.Get("tire_rear_passenger").GetMatrix().SetScale(.25);

    

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
    if (e.type == SDL_QUIT) {
        Running =  false;
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
    ManifestParser assets = ManifestParser(RESOURCE_ROOT + "manifest/objects.manifest");
    ObjParser parser = ObjParser();

    map<string, GLuint> textures;

    
    //for (map<string,string>::iterator it=assets.GetTextures().begin(); it!=assets.GetTextures().end(); ++it) {
    for (auto& it: assets.GetTextures()) {
        GLuint tex = SOIL_load_OGL_texture((RESOURCE_ROOT + it.second).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        pair<string, GLuint> p = pair<string, GLuint>(it.first, tex);
        textures.insert( p );
    }
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);                                    // Return Success
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    //for(map<string,string>::iterator it=assets.GetModels().begin(); it!=assets.GetModels().end(); ++it) {
    for (auto& it: assets.GetModels()) {
        Item temp = Item();
        parser.parseFile((RESOURCE_ROOT + it.second), &temp);
        temp.SetTexture(textures.at(it.first));
        scene.AddItem(it.first, temp);
    }
}