#ifndef _DEFINITIONS_H 
#define _DEFINITIONS_H
#include <windows.h>  // for MS Windows

#include <GL/glut.h>  // GLUT, include glu.h and gl.h

#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include<iostream>
using namespace std;

// gia tri cac mau
static GLfloat qaBlack[] = { 0,0,0,1.0 };
static GLfloat qaGreen[] = { 0,1.0,0,1.0 };
static GLfloat qaRed[] = { 1.0,0,0,1.0 };
static GLfloat qaBlue[] = { 0,0,1.0,1.0 };
static GLfloat qaWhite[] = { 1.0,1.0,1.0,1.0 };
static GLfloat qaYellow[] = { 1.0,1.0,0,1.0 };
static GLfloat qaGrey[] = { 0.5,0.5,0.5,0.5 };
static GLfloat qaLowAmbient[] = { 0.2,0.2,0.2,1.0 };
static GLfloat qaFullAmbient[] = { 1.0,1.0,1.0,1.0 };

#endif