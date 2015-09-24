//
//  Camera.cpp
//  wizards-court
//
//  Created by Daniel Fuller on 9/22/15.
//  Copyright (c) 2015 Daniel Fuller. All rights reserved.
//

#include "Camera.h"

Camera::Camera() {
    angle=0;
}

void Camera::AdjustCamera() {
    glTranslatef(0.0f, -1.0f, -2.0f); // Local: +l/-r , -u/+d , +f/-b
    glRotatef(angle--, 0.0f, 1.0f, 0.0f);
}