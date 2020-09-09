/* San Angeles Observation OpenGL ES version example
 * Copyright 2004-2005 Jetro Lauha
 * All rights reserved.
 * Web: http://iki.fi/jetro/
 *
 * This source is free software; you can redistribute it and/or
 * modify it under the terms of EITHER:
 *   (1) The GNU Lesser General Public License as published by the Free
 *       Software Foundation; either version 2.1 of the License, or (at
 *       your option) any later version. The text of the GNU Lesser
 *       General Public License is included with this source in the
 *       file LICENSE-LGPL.txt.
 *   (2) The BSD-style license that is included with this source in
 *       the file LICENSE-BSD.txt.
 *
 * This source is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files
 * LICENSE-LGPL.txt and LICENSE-BSD.txt for more details.
 *
 * $Id: app.h,v 1.14 2005/02/06 21:13:54 tonic Exp $
 * $Revision: 1.14 $
 */

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif


#define WINDOW_DEFAULT_WIDTH    640
#define WINDOW_DEFAULT_HEIGHT   480

#define WINDOW_BPP              16

typedef struct {
    GLfixed *vertexArray;
    GLubyte *colorArray;
    GLfixed *normalArray;
    GLint vertexComponents;
    GLsizei count;
} GLOBJECT;

typedef struct {
    float x, y, z;
} VECTOR3;

// The simple framework expects the application code to define these functions.
extern void appInit();
extern void appDeinit();
extern void appRender(long tick, int width, int height);

static GLOBJECT * newGLObject(long vertices, int vertexComponents, int useNormalArray);
static GLOBJECT * createSuperShape(const float *params);
static void freeGLObject(GLOBJECT *object);
static unsigned long randomUInt();
static GLOBJECT * createGroundPlane();
static void vector3Sub(VECTOR3 *dest, VECTOR3 *v1, VECTOR3 *v2);
static float ssFunc(const float t, const float *p);
static void superShapeMap(VECTOR3 *point, float r1, float r2, float t, float p);
static void seedRandom(unsigned long seed);
static void prepareFrame(int width, int height);
static void gluPerspective(GLfloat fovy, GLfloat aspect,
                           GLfloat zNear, GLfloat zFar);
static void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
                      GLfloat centerx, GLfloat centery, GLfloat centerz,
                      GLfloat upx, GLfloat upy, GLfloat upz);
static void camTrack();
static void configureLightAndMaterial();
static void drawModels(float zScale);
static void drawGLObject(GLOBJECT *object);
static void drawGroundPlane();
static void drawFadeQuad();


/* Value is non-zero when application is alive, and 0 when it is closing.
 * Defined by the application framework.
 */
extern int gAppAlive;


#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED
