//
//  Utility.c
//  c-ray-tracer
//
//  Created by Harshdeep Kahlon on 4/15/21.
//

#include "Utility.h"
#include <math.h>

float3 addFloat3(float3 a, float3 b) {
    float3 result = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
    return result;
}


float3 subFloat3(float3 a, float3 b) {
    float3 result = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
    return result;
}

float dotFloat3(float3 a, float3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float3 crossFloat3(float3 a, float3 b) {
    float3 result = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x
    };
    return result;
}

float3 multFloat3(float3 a, float c) {
    float3 result = {
        .x = a.x * c,
        .y = a.y * c,
        .z = a.z * c
    };
    return result;

}

float3 normalizeFloat3(float3 a) {
    float w = magnitudeFloat3(a);
    float3 result = {
        .x = a.x / w,
        .y = a.y / w,
        .z = a.z / w
    };
    return result;
}

float magnitudeFloat3(float3 a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

float normFloat3(float3 a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}
