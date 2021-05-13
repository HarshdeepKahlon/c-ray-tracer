//
//  Utility.h
//  c-ray-tracer
//
//  Created by Harshdeep Kahlon on 4/15/21.
//

#ifndef Utility_h
#define Utility_h

#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} float3;

typedef struct {
    float3 origin;
    float3 direction;
} Ray;

typedef struct {
    int hitObject;
    float distance;
    float3 point;
} IntersectionInfo;

typedef struct {
    float xStart;
    float xEnd;
    float yStart;
    float yEnd;
    int threadId;
} RayTraceThreadInfo;



float3 addFloat3(float3 a, float3 b);

float3 subFloat3(float3 a, float3 b);

float dotFloat3(float3 a, float3 b);

float3 crossFloat3(float3 a, float3 b);

float3 multFloat3(float3 a, float c);

float3 normalizeFloat3(float3 a);

float magnitudeFloat3(float3 a);

float normFloat3(float3 a);

#endif /* Utility_h */
