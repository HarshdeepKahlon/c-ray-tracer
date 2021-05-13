//
//  main.c
//  c-ray-tracer
//
//  Created by Harshdeep Kahlon on 5/13/21.
//

#include <stdlib.h>
#include <pthread.h>
#include <float.h>
#include <math.h>
#include "Utility.h"
#include "Cube.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#define THREAD_COUNT 16
#define MAX_DEPTH 3

static float buffer[1000][1000];

static pthread_t thread_id[THREAD_COUNT];

float castRay(Ray ray, int depth);

IntersectionInfo trace(Ray ray, int objectId) {
    IntersectionInfo intersection;
    intersection.distance = 100000;
    intersection.hitObject = -2;
    for(int x = 0; x < 14; x++) {
        if (x == objectId) continue;
        float i = intersectTriangle(ray, x, 0);
        if (i != -1.0 && i < intersection.distance) {
            intersection.hitObject = x;
            intersection.distance = i;
            intersection.point = addFloat3(ray.origin, multFloat3(subFloat3(ray.direction, ray.origin), i));
        }
    }
    
    float i = intersectSphere(ray, lightSphere);
    if (i != -1.0 && i < intersection.distance) {
        intersection.hitObject = -1;
        intersection.distance = i;
        if (objectId != -1) {
        }
    }
    
    return intersection;
}

float distance(float3 a, float3 b) {
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

float shadeDiffuse(IntersectionInfo intersection, int depth) {
    float ambient = 0.1;
    
    Ray secondaryRay = {
        intersection.point,
        lightSphere.center
    };
    IntersectionInfo secondaryIntersection = trace(secondaryRay, intersection.hitObject);
    
    if (secondaryIntersection.hitObject != -1) {
            if (depth == MAX_DEPTH)
                return ambient;
            return castRay(secondaryRay, depth + 1);
    }
    
    float diffuse = 1.0 / (2 * distance(intersection.point, lightSphere.center));
        
    return ambient + diffuse;
}


float castRay(Ray ray, int depth) {
    if (depth > MAX_DEPTH) return 0;
    IntersectionInfo intersection = trace(ray, -1);
    if (intersection.distance == 100000) { // hit nothing
        return 0.0;
    }
    if (intersection.hitObject == -1) { // hit light
        return 1.0;
    }
    return shadeDiffuse(intersection, depth);
}

void* rayTraceThread(void* ptr) {
    RayTraceThreadInfo* info = (RayTraceThreadInfo*)ptr;
    for(float i = info->xStart; i < info->xEnd; i += 0.0005) {
        for(float j = info->yStart; j < info->yEnd; j += 0.0005) {
            float3 screenLoc = { .x = i, .y = j, .z = 0 };
            Ray ray = {
                eye,
                screenLoc,
            };
            buffer[(int)(i*1000)][(int)(j*1000)] = castRay(ray, 0);
        }
    }
    return NULL;
}



void drawpixel(float x,float y,float r,float g,float b) // assume x,y 0-100
{
#define SZ  .02
    glBegin(GL_TRIANGLES);
    
    glColor3f(r,g,b);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y);
    glVertex2f(-1.0+.02*(float)x+ SZ, -1.0+.02*(float)y+ SZ);
    glVertex2f(-1.0+.02*(float)x,     -1.0+.02*(float)y+ SZ);
    glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    RayTraceThreadInfo* threadInfo[THREAD_COUNT];
    float increment = 1.0/THREAD_COUNT;
    for (int i = 0; i < THREAD_COUNT; i++) {
        RayTraceThreadInfo* info = (RayTraceThreadInfo*)malloc(sizeof(RayTraceThreadInfo));
        info->xStart = increment * i;
        info->xEnd = increment * i + increment;
        info->yStart = 0.0;
        info->yEnd = 1;
        info->threadId = i;
        threadInfo[i] = info;
        pthread_create(&thread_id[i], NULL, rayTraceThread, (void*)info);
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread_id[i], NULL);
    }
    for(float i = 0.0; i < 1.0; i += 0.001) {
        for(float j = 0.0; j < 1.0; j += 0.001) {
            float color = buffer[(int)(i*1000)][(int)(j*1000)];
            drawpixel(i * 100, j * 100, color, color, color);
        }
    }
    glFlush();
}


int main(int argc, char** argv)
{
    for(int i = 0; i < 12; i++) {
        Triangle triangle = convertToTriangle(cubeTriangles[i]);
        allTriangles[i] = triangle;
    }
    allTriangles[12] = initTriangle(floorTriangle1.p1, floorTriangle1.p2, floorTriangle1.p3);
    allTriangles[13] = initTriangle(floorTriangle2.p1, floorTriangle2.p2, floorTriangle2.p3);
    glutInit(&argc,argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMainLoop();
}
