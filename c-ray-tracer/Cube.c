//
//  Cube.c
//  c-ray-tracer
//
//  Created by Harshdeep Kahlon on 4/29/21.
//

#include "Cube.h"
#include <math.h>

Triangle allTriangles[14];

Triangle initTriangle(float3 a, float3 b, float3 c) {
    Triangle triangle = { .p1 = a, .p2 = b, .p3 = c };
    float3 ca = subFloat3(c, a);
    float3 ba = subFloat3(b, a);
    float3 normal = normalizeFloat3(crossFloat3(ca, ba));
    triangle.normal = normal;
    return triangle;
}

Triangle convertToTriangle(const int nums[3]) {
    float3 p1 = { .x = cubePoints[nums[0]][0], .y = cubePoints[nums[0]][1], .z = cubePoints[nums[0]][2] };
    float3 p2 = { .x = cubePoints[nums[1]][0], .y = cubePoints[nums[1]][1], .z = cubePoints[nums[1]][2] };
    float3 p3 = { .x = cubePoints[nums[2]][0], .y = cubePoints[nums[2]][1], .z = cubePoints[nums[2]][2] };
    Triangle triangle = initTriangle(p1, p2, p3);
    return triangle;
}

int compareTriangle(Triangle t1, Triangle t2) {
    float3 d1 = subFloat3(t1.p1, t2.p1);
    float3 d2 = subFloat3(t1.p2, t2.p2);
    float3 d3 = subFloat3(t1.p3, t2.p3);
    
    return d1.x == 0 && d2.x == 0 && d3.x == 0 &&
    d1.y == 0 && d2.y == 0 && d3.y == 0 &&
    d1.z == 0 && d2.z == 0 && d3.z == 0;
}


float intersectTriangle(Ray ray, int triangleIndex, int isSecondary) {
    Triangle triangle = allTriangles[triangleIndex];
    float3 t1 = triangle.p1;
    float3 t2 = triangle.p2;
    float3 t3 = triangle.p3;
    
    float3 n = triangle.normal;
    
    float u = dotFloat3(n, subFloat3(t3, ray.origin)) / dotFloat3(n, subFloat3(ray.direction, ray.origin));
    
    if (u < 0)
        return -1.0;

    float3 i = addFloat3(ray.origin, multFloat3(subFloat3(ray.direction, ray.origin), u));
    
    float3 v1 = subFloat3(t1, i);
    float3 v2 = subFloat3(t2, i);
    float3 v3 = subFloat3(t3, i);
    
    float3 c1 = crossFloat3(v1, v2);
    float3 c2 = crossFloat3(v2, v3);
    float3 c3 = crossFloat3(v3, v1);
    
    float d1 = dotFloat3(c1, c2);
    float d2 = dotFloat3(c2, c3);
    float d3 = dotFloat3(c3, c1);
    
    if (!(d1 > 0 && d2 > 0 && d3 > 0))
        return -1.0;
    
    return u;
}

float intersectSphere(Ray ray, Sphere sphere) {
    double u = dotFloat3(subFloat3(sphere.center, ray.origin), subFloat3(ray.direction, ray.origin));
    
    float3 sub = subFloat3(ray.direction, ray.origin);
    float bot = magnitudeFloat3(sub);
    
    u /= (bot * bot);
    
    if (u < 0)
        return -1.0;

    float3 p = addFloat3(ray.origin, multFloat3(sub, u));
    
    float res = magnitudeFloat3(subFloat3(p, sphere.center));
        
    if (res <= sphere.radius) {
        return u;
    }
    
    return -1.0;
}


float intersectSphere1(Ray ray, Sphere sphere) {
    float3 rd = normalizeFloat3(ray.direction);
    float a = dotFloat3(rd, rd);
    float3 s0_r0 = subFloat3(ray.origin, sphere.center);
    float b = 2.0 * dotFloat3(rd, s0_r0);
    float c = dotFloat3(s0_r0, s0_r0) - (sphere.radius * sphere.radius);
    if (b*b - 4.0*a*c < 0.0) {
        return -1.0;
    }
    return (-b - sqrt((b*b) - 4.0*a*c))/(2.0*a);
}
