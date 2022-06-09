#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//define camera class
class camera {

public:
    //variables for opengl
    vec3 eye; //center position
    vec3 at; //point where this camera is pointing out
    vec3 up; // up direction (normalized)

    //other variables
    vec3 forward; //vector pointing forward direction
    float distance = 1; //distance from eye to at
    vec3 right; //vector indicating right direction from the point of camera
    
    void InitCamera(vec3 _center, vec3 _at, vec3 _up)
    {
        //set three variables and update others
        eye = _center;
        at = _at;
        up = _up;
        UpdateCamera();
    }

    void MoveCamera(vec3 move)
    {
        eye += move;
        at += move;
    }

    void RotateCamera(vec3 axis, float angle)
    {
        //rotate direc and up vector
        vec4 tempForward = vec4(forward, 0);
        vec4 tempUp = vec4(up, 0);
        mat4 rot = rotate(mat4(1), radians(angle), axis);
        forward = rot * tempForward;
        up = rot * tempUp;

        //update at vector accordingly
        at = eye + forward * distance;

        UpdateCamera();
    }

    //update variables accordingly
    void UpdateCamera()
    {
        up = normalize(up);
        distance = length(at - eye);
        forward = normalize(at - eye);
        right = normalize(cross(forward, up));
    }
};