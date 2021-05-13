//
//  cube.h
//  c-ray-tracer
//
//  Created by Harshdeep Kahlon on 3/25/21.
//

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include "Utility.h"

typedef struct {
    float3 p1;
    float3 p2;
    float3 p3;
    float3 normal;
} Triangle;

typedef struct {
    float3 center;
    float radius;
} Sphere;


extern Triangle allTriangles[14];

static const float3 eye = { .x = 0.5, .y = 0.5, .z = -1.0 };

static Sphere lightSphere = {
    { 0.5, 0.5, 1.5 },
    0.1
};

static const Triangle floorTriangle1 = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 }
};

static const Triangle floorTriangle2 = {
    { 1.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 }
};

static const GLfloat cubePoints[8][3] = {
    {0.1, 0.25, 0.7},
    {0.1, 0.05, 0.7},
    {0.3, 0.25, 0.7},
    {0.3, 0.05, 0.7},
    {0.3, 0.25, 0.5},
    {0.3, 0.05, 0.5},
    {0.1, 0.05, 0.5},
    {0.1, 0.25, 0.5},
};

static const GLint cubeTriangles[12][3] = {
    {1, 3, 6},
    {5, 3, 6},
    {1, 0, 6},
    {7, 0, 6},
    {5, 4, 6},
    {7, 4, 6}, // 5
    {0, 2, 7},
    {4, 2, 7}, // 7
    {0, 1, 2},
    {3, 1, 2},
    {3, 2, 5}, // 10
    {4, 2, 5}
};

Triangle initTriangle(float3 a, float3 b, float3 c);

int compareTriangle(Triangle t1, Triangle t2);

Triangle convertToTriangle(const int nums[3]);

float intersectTriangle(Ray ray, int triangleIndex, int isSecondary);

float intersectSphere(Ray ray, Sphere sphere);
