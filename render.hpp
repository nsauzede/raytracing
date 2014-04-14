// render.hpp p60
/*
Header File for Ray Tracing Program
    By Roger T. Stevens - 3/1/90
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vmath.hpp"
/*
Object Definitions
*/
#define PATT_HEADER		0
#define LINE			1
#define SPHERE			2
#define PARALLELOGRAM	3
#define TRIANGLE		4
#define LAMP			5
#define OBSERVER		6
#define GROUND			7
#define SKY				8
#define BBOX			9
#define RING			10
#define QUADRATIC		11
#define BEGIN_BBOX		12
#define END_BBOX           13
#define BEGIN_INSTANCES    14
#define END_INSTANCES      15
#define AMB                16
#define DIFF               17
#define MIRROR             18
#define TRANS              19
#define DENSITY            20
#define INDEX              21
#define DITHER             22
#define SREFLECT           23
#define REFLECT            24
#define LOC                25
#define RADIUS             26
#define PAttern			27 
#define REMOVE 28 
#define XMULT 29 
#define YMULT 30 
#define NAME 31 
#define DIST 32 
#define LOOKAT 33 
#define V1 34
#define V2 35
#define ZENITH 36 
#define HORIZ 37 
#define RAD_1 38 
#define RAD_2 39 
#define A 40 
#define B 41 
#define C 42 
#define D 43 
#define E 44 
#define XMAX 45 
#define YMAX 46 
#define ZMAX 47 
#define XMIN 48 
#define YMIN 49 
#define ZMIN 50 
#define DIR 51 
#define FOC_LENGTH 52 
#define FIRST_SCAN 53 
#define DEFAULT 54 
#define FILE_NAME 55 
#define LAST_SCAN 56 
#define XRES 57 
#define YRES 58 
#define X_SIZE 59 
#define Y_SIZE 60 
#define START_X 61 
#define START_Y 62 
#define END_X 63 
#define END_Y 64 
#define PAREN 65 
#define NO_SHADOW 66 
#define NO_LAMP 67 
#define THRESHOLD		68
#define UP				69
#define INSTANCE_OF		70
#define SCALE			71
#define RECTANGLE		72
#define CIRCLE			73
#define POLYGON			74
#define COLOR			75
#define POINT			76
#define CONE			77
#define HEIGHT			78
#define FRACTAL			79
#define DIMENSION		80
#define SCALAR			81
#define NUll			82
#define last_no			83

/*
Useful Constants
*/
#define TRUE  1
#define FALSE 0
#define SMALL         0.001
#define ASPECT        1.0  // aspect ratio
#define CNUM         63    // number of shades of solor minus one
#define MAX_IX        4    // maximum x interpolation
#define MAX_IY        4    // maximum y interpolation
#define max_pixel   800    // max of RGB array size (dots per row)
extern int XSIZE;
extern int YSIZE;
extern int CENTERX;
extern int CENTERY;
extern int XSIZE4;            
/*
Color Data Definitions
*/
class color_data
{
      public:
      Vector    amb,           // ambient lighting
                diff,          // diffuse lighting
                mirror,        // % light reflected
                trans,         // % light transmitted
                density;       // density
      Scalar     reflect,       // percent specu9arly reflected
                index;         // index if refraction
      short     sreflect,      // specular refl coefficient
                dither;        // color dithering
      color_data operator=(color_data&);
 };
/*
Class definition for Line
*/
class Line
{
      public:
      Vector loc,dir;
      int flag;   
 };
/*
Class definition for Lamp
*/
class Lamp
{
      public:
      Vector loc;
      Scalar radius, distance;
      Lamp * next_lamp;
 };
/*
Class definition for a Pattern
*/
class Pattern
{
	public:
	short		type;      // type of pattern
	Scalar		xsize,      // pattern size in x direction
				ysize,      // pattern size in y direction
				startx,     // x coordinate starting position
				starty,     // y coordinate starting position
				endx,       // x coordinate ending position
				endy,       // y coordinate ending position
				radius;     // radius of circle pattern
	color_data  col_data;   // color information
	char        name[32];   // name of pattern
	Pattern     *child,
				*sibling,
				*link;
};

//p64
/*
 Class Definitions for Object
*/
class Object
{
	public:
	unsigned char	type, // object type
					flag;
	char name[16];	// object name
	Vector	loc,	// object location
			vect1,	// three vectors
			vect2,
			vect3,
			lower,	// iower bound
			upper,	// upper bound
			norm;
	Scalar	cterm,yterm,	// used for quadratic
					// surfaces only
			xmult,	// x multiplier for
					// patterns
			ymult,	// y multiplier for
					// pattern
			n1, // precomputed values
			len1,
			len2,
			cos1,
			sin1,
			cos2,
			sin2;
	color_data	*col_data; // color information
	Object	*nextobj,	// addr of next object in list
			*child;		// address of child for
						// bounding boxes
	Pattern	*pattern,	// addr of pattern structure
			*remove;	// address of struct to remove
						// obj section
	Object operator=(Object &);
//	virtual void FindNorm(Vector * normal, Vector * position);
//	virtual void Position (Scalar * pos1, Scalar *pos2, Vector
//							*location);
	virtual int CollisionTest(Line * line, Scalar *t);
//	virtual void FindBbox(Vector * v1, Vector * v2);
//	virtual void Scale_Instance(Vector *mult, int fflag);
};

class Sphere: public Object
{
	public:
	Sphere();
	void FindNorm(Vector * normal, Vector * position);
	void Position (Scalar * pos1, Scalar *pos2, Vector *location);
	int CollisionTest(Line * line, Scalar *t);
	void FindBbox(Vector * v1, Vector * v2);
	void Scale_Instance(Vector *mult, int fflag);
};

#if 0
Triangle: public Object
public:
Triangle():
void FindNorm(Vector * normal, Vector * position);
void Position (Scalar * posl, Scalar *pos2, Vector *location)
int CollisionTest(Line * line, Scalar *t);
void FindBbox(Vector * v1, Vector * v2);
void Scale_Instance(Vector *mult, int fflag);
l;
class Parallelogram: public Object
(
public:
Parallelogram();
void FindNorm(Vector * normal, Vector * position)i
void Position (Scalar * posl, Scalar *pos2, Vector *location)
int CollisionTest(Line * line, Scalar *t):
- void FindBbox(Vector * vl, Vector * v2);
void Scale_Instance(Vector *mult, int fflag);
l:
class Ring: public Object
(
public:
Ring();
void FindNorm(Vector * normal, Vector *_position):
void Position (Scalar * posl, Scalar *pos2, Vector *location)
int CollisionTest(Line * line, Scalar *t):
< void FindBbox(Vector * vl, Vector * v2);
void Scale_Instance(Vector *mult, int fflag);
l: ~
#endif
class Quadratic: public Object
{
	public:
	Quadratic();
	void FindNorm(Vector * normal, Vector * position);
	void Position (Scalar * pos1, Scalar *pos2, Vector *location);
	int CollisionTest(Line * line, Scalar *t);
	void FindBbox(Vector * v1, Vector * v2);
	void Scale_Instance(Vector *mult, int fflag);
};
#if 0
class BBox: public Object
I
int CollisionTest(Line * line, Scalar *t);
void FindBbox(Vect0r * v1, Vector * v2);
1:
#endif
