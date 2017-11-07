#include <Sprite.h>
#include <Matrix.h>
// Sprite Animation
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates the use of the Matrix & Sprite libraries
// Displays animated waveform graphic on screen

// Created 29 March 2006

/* create a new Matrix instance
   pin 0: data  (din)
   pin 1: load  (load)
   pin 2: clock (clk)
*/
Matrix myMatrix = Matrix(0, 2, 1);

/* create a new Sprite instance
   8 pixels wide, 4 pixels tall
*/



Sprite one = Sprite(
  4, 4,
  B0110,
  B0010,
  B0010,
  B0111
);
Sprite two = Sprite(
  4, 4,
  B1111,
  B0011,
  B1100,
  B1111
);

Sprite three

= Sprite(
  4, 4,
  B1111,
  B0111,
  B0001,
  B1111
);

Sprite four = Sprite(
  4, 4,
  B1000,
  B1010,
  B1111,
  B0010
);


Sprite five = Sprite(
  4, 4,
  B1111,
  B1100,
  B0011,
  B1111
);

Sprite six = Sprite(
  4, 4,
  B1111,
  B1000,
  B1111,
  B1111
);

Sprite seven = Sprite(
  4, 4,
  B0111,
  B0001,
  B0010,
  B0010
);

Sprite eight = Sprite(
  4, 4,
  B1111,
  B1111,
  B1001,
  B1111
);

Sprite nine = Sprite(
  4, 4,
  B1111,
  B1111,
  B0001,
  B1111
);

Sprite ten = Sprite(
  4, 4,
  B1011,
  B1011,
  B1011,
  B1011
);

Sprite eleven = Sprite(
  4, 4,
  B1001,
  B1001,
  B1001,
  B1001
);

Sprite twelve = Sprite(
  4, 4,
  B1011,
  B1011,
  B1011,
  B0000
);


int x = 3;
void setup()
{ 
    myMatrix.write(5, 0, HIGH);
    myMatrix.write(6, 0, HIGH);
    myMatrix.write(7, 0, HIGH);
    myMatrix.write(0, 0, HIGH);
    myMatrix.write(0, 1, HIGH);
    myMatrix.write(0, 2, HIGH);
    myMatrix.write(0, 3, HIGH);
    myMatrix.write(x, 2, ten); 
}


void loop()
{
      // place sprite on screen
                   // advance x coordinate to the right
}

