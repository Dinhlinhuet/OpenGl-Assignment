// turtle.h
// by Glenn G. Chappell
// March 2004
//
// For CS 481/681
// Simple turtle graphics class
#include <GL/glut.h>
#include <GL/glu.h>
#include <gl/gl.h>
#include <math.h>  // <sigh> broken compilers ...
                   // Change this to <cmath> if you want
#ifndef M_PI
#define M_PI (3.1415926535897932384626433832795)
#endif


// ****************************************************
// class Turtle
// ****************************************************

// This is a simple logo-style drawing "turtle". It has a position
// (x & y) and a direction (in degrees ccw [counterclockwise] from
// east). It drags a pen, which is either down (drawing - the default)
// or up (not drawing). It can turn right or left and move forward
// or back. If the pen is down when it moves, a line is drawn. Lines
// are drawn using the OpenGL primitive GL_LINES. The initial state
// is position (0,0), direction 0 (east), pen down. The reset()
// function returns the turtle to this state.

class Turtle
{
// ***** class Turtle: ctors, etc. *****
public:

   Turtle()                         // Default ctor
   { reset(); }

   // Compiler-generated dctor, copy ctor, copy op= are fine

// ***** class Turtle: Public Functions *****
public:

   void reset()                     // Restore initial state
   { x = 0.0; y = 0.0; dir = 0.0; draw = true; }

   void setpos(const double newx, const double newy)
   { x = newx; y = newy; }          // Set position x & y

   void setdir(const double newdir) // Set direction in degrees ccw from east
   { dir = newdir; }

   void left(const double angle)    // Turn - angle is in degrees
   { dir += angle; }

   void right(const double angle)   // Turn - angle is in degrees
   { left(-angle); }

   void pendown()                   // Lower pen; turn drawing on
   { draw = true; }

   void penup()                     // Raise pen; turn drawing off
   { draw = false; }

   void forward(const double dist)  // Move forward; draw if pen is down
   {
      double newx = x + dist * cos(M_PI * dir / 180.0);
      double newy = y + dist * sin(M_PI * dir / 180.0);
      if (draw)
      {
         glBegin(GL_LINES);
            glVertex2d(x, y);
            glColor3d(0.1,0.5,0.75);
            glVertex2d(newx, newy);
         glEnd();
      }
      x = newx;
      y = newy;
   }

   void back(const double dist)            // Move backward; draw if pen down
   { forward(-dist); }

// ***** class Turtle: Data members *****
private:

   double x;    // Current x coordinate
   double y;    // Current y coordinate
   double dir;  // Current direction in degrees ccw from east
   bool draw;   // true if currently drawing (pen down)

};  // End class Turtle
