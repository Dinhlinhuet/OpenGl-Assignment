// koch.cpp
// by Glenn G. Chappell
// March 2004
//
// For CS 481/681
// Turtle Fractal Demo - draws Koch snowflake

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::string;
#include <sstream>
#include <stdlib.h>
using std::exit;
#include <GL/glut.h> // GLUT stuff - includes OpenGL headers
#include <gl/gl.h>
#include <gl/glu.h>
#include <Windows.h>
#include "Turtle.h"  // class Turtle: turtle-graphics


// Global variables
// Window/viewport
const int startwinsize = 400; // Starting window width & height, in pixels

// Keyboard
const int ESCKEY = 27;        // ASCII value of escape character

// For turtle graphics
Turtle t;                     // The turtle
int fraclevel = 3;            // "Level" for the fractal
const int minfraclevel = 0;   // Min & max for above
const int maxfraclevel = 10;


// tostring
// Convert argument to string class using operator<<
// Must include <sstream>
template<typename T>
std::string tostring(const T & input)
{
   std::ostringstream os;
   os << input;
   return os.str();
}


// printbitmap
// Prints the given string at the given raster position
//  using GLUT bitmap fonts.
// You probably don't want any rotations in the model/view
//  transformation when calling this function.
void printbitmap(const string msg, double x, double y)
{
   glRasterPos2d(x, y);
   for (string::const_iterator ii = msg.begin();
        ii != msg.end();
        ++ii)
   {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
   }
}


// drawkoch_recurse
// Draws a Koch curve at the given level, with the given length,
// using the turtle.
// If level is 0, draws a line segment. Otherwise, recursively
// draws the curve.
void drawkoch_recurse(int level, double length)
{
   if (level <= 0)
   {
      t.forward(length);
   }
   else
   {
      drawkoch_recurse(level-1, length/3.0);
      t.left(60);
      drawkoch_recurse(level-1, length/3.0);
      t.right(120);
      drawkoch_recurse(level-1, length/3.0);
      t.left(60);
      drawkoch_recurse(level-1, length/3.0);
   }
}


// drawsnowflake
// Draws a Koch snowflake, using drawkoch_recurse.
void drawsnowflake()
{
   const double fracsize = 1.0;

   t.reset();
   t.setpos(-0.5, 0.3);  // Positioned at (-0.5, 0.3)
   t.setdir(0.0);        // Facing east

   // Draw three Koch curve segments:
   // level = fraclevel, length = fracsize
   drawkoch_recurse(fraclevel, fracsize);
//   t.right(120);
//   drawkoch_recurse(fraclevel, fracsize);
//   t.right(120);
//   drawkoch_recurse(fraclevel, fracsize);
}


// display
// The GLUT display function
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);

   // Draw fractal
   glLineWidth(2.0);
   glColor3d(0.5, 0.0, 0.9);
   drawsnowflake();

   // Draw instructions
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
      glColor3d(0.5, 0.5, 0.0);
      printbitmap("Koch Snowflake", -0.9, 0.7);
      printbitmap("<- ->   Change level [" + tostring(fraclevel) + "]", -0.9, 0.8);
      printbitmap("Esc     Quit", -0.9, 0.7);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);

   glFlush();  // Single-buffered!
}


// keyboard
// The GLUT keyboard function
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case ESCKEY:  // ESC: Quit
      exit(0);
      break;
   }
}


// special
// The GLUT special function
void special(int key, int x, int y)
{
   switch (key)
   {
   case GLUT_KEY_RIGHT:  // ->: Increment level
      if (fraclevel < maxfraclevel)
      {
         ++fraclevel;
         glutPostRedisplay();
      }
      break;
   case GLUT_KEY_LEFT:   // ->: Decrement level
      if (fraclevel > minfraclevel)
      {
         --fraclevel;
         glutPostRedisplay();
      }
      break;
   }
}


// reshape
// The GLUT reshape function
void reshape(int w, int h)
{
   const double c = 0.7;  // Viewport contains at least -c to +c in both x & y
   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // We want a non-distorted coordinate system:
   // the smallest possible rectangle containing
   // -c to +c in both x & y coordinates.
   if (w > h)
      gluOrtho2D(-c*w/h,c*w/h, -c,c);
   else // h >= w
      gluOrtho2D(-c,c, -c*h/w,c*h/w);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


// idle
// The GLUT idle function
void idle()
{
   // Print OpenGL errors, if there are any (for debugging)
   if (GLenum err = glGetError())
   {
      cerr << "OpenGL ERROR: " << gluErrorString(err) << endl;
   }
}


// init
// Initializes GL states
// Called by main
void init()
{
   glClearColor(1.0, 1.0, 1.0, 0.0);  // white background
}


int main(int argc, char ** argv)
{
   // Initialize OpenGL/GLUT
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

   // Make a window
   glutInitWindowSize(1366, 768);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Koch Snowflake");

   // Initialize GL states & register callbacks
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutIdleFunc(idle);

   // Do something
   glutMainLoop();

   return 0;
}
