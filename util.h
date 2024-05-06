/*
 * util.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "CImg.h"
#include <vector>

using namespace std;

#define FPS 80 // frame per seconds

#define KEY_ESC 27 // ASCII for Escape key
enum ColorNames {
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PINK
};

static float colors[][3] = {
	{1, 1, 1},      // WHITE
	{0, 0, 0},      // BLACK
	{1, 0, 0},      // RED
	{0, 1, 0},      // GREEN
	{0, 0, 1},      // BLUE
	{1, 1, 0},      // YELLOW
	{1, 0.752941176470588, 0.796078431372549}  // PINK
};

float* white = colors[WHITE];
float* black = colors[BLACK];
float* red = colors[RED];
float* green = colors[GREEN];
float* blue = colors[BLUE];
float* yellow = colors[YELLOW];
float* pink = colors[PINK];

//defining some MACROS
#define M_PI 3.141519
#define MAX(A,B) ((A) > (B) ? (A):(B)) // finds max of two numbers
#define MIN(A,B) ((A) < (B) ? (A):(B)) // find min of two numbers
#define ABS(A) ((A) < (0) ? -(A):(A))  // find ABS of a given number

// define some constants

float Deg2Rad(float degree);
float Rad2Deg(float angle);

// function reads the image and give the pixels in
// column major order, every pixel is placed linearly
// in Reg, Green, Blue format and then columnwise same as opengl...
// uses CImg
void ReadImage(string imgname, vector<unsigned char> &imgArray);

// Function draws a circle of given radius and color at the
// given point sx and sy.
void DrawCircle(float sx, float sy, float radius, float*color);
void DrawSquare(int sx, int sy, int size,float* color);
// Function draws a circular curve of given
void Torus2d(int x /*Starting position x*/, int y /*Starting position Y*/,
		float angle, // starting angle in degrees
		float length,           // length of arc in degrees, >0
		float radius,           // inner radius, >0
		float width,            // width of torus, >0
		unsigned int samples,    // number of circle samples, >=3
		float *color = NULL);

// Function draws a line between point P1(x1,y1) and P2(x2,y2)
// of given width and colour
void DrawLine(int x1, int y1, int x2, int y2, int lwidth = 3, float *color =
		NULL);
// Function draws a rectangle with rounded corners at given x,y coordinates
void DrawRoundRect(float x, float y, float width, float height,
		float* color = 0, float radius = 0.0);
// Function draws a string at given x,y coordinates
void DrawString(int x, int y, int width, int height, const string& str,
		float * color = NULL);
void DrawString(float x, float y, const string& str, float * color = NULL);

// seed the random numbers generator by current time (see the documentation of srand for further help)...
void InitRandomizer();

//This function returns a random value within the specified range of [rmin, rmax] ...
long GetRandInRange(const long &rmin, const long &rmax);

/*To draw a triangle we need three vertices with each vertex having 2-coordinates [x, y] and a color for the triangle.
 * This function takes 4 arguments first three arguments (3 vertices + 1 color) to
 * draw the triangle with the given color.
 * */
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float *color);
// Draws a rectangle of the specified color
void DrawRectangle(int sx, int sy, int width, int height, float *color);

// Convert a Number to String...

string Num2Str(int t);
#endif /* UTIL_H_ */
