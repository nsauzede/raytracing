#include <stdio.h>
#include <string.h>

#include "render.hpp"

int main()
{
	Scalar t = 3.14;
	int n = 0;

	Line line;
#if 1
	Vector up( 0, 1, 0);
	line.loc = Vector( -20, 70, -80);
	Vector lookat = Vector( 200, 50, -15);
//	line.loc = Vector( 50, 70, 115);
//	Vector lookat = Vector( 200, -50, 15);

	line.dir = lookat - line.loc;
//	line.dir = lookat;
	line.dir = line.dir / sqrt(line.dir % line.dir);;

#else
	Vector up( 0, 1, 0);
	line.loc = Vector( 1, 1, 1);
	line.dir = Vector( -1, -1, -1);
#endif
	int w = 4*32;
	int h = 2*20;
	Scalar zoom = 1.0;
	Scalar vw = 1.0 / zoom;
	Scalar vh = 1.0 * h / w / zoom;

	Vector right = line.dir ^ up;
	up = right ^ line.dir;
	Vector s0, s1, s2;
	s0 = line.loc + line.dir;
	s1 = s0 + up;
	s2 = s0 + right;

#define MAX 10
	Object *objs[MAX];
	memset( objs, 0, MAX * sizeof(void *));
	int nobjs = 0;

#define R 0.5
#define LIM 1.4
#ifdef QUAD
	Quadratic *quad2;
	// elliptic cone cyan 1
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 230, 60, -100);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( 2500, -625, 2500);		// vect2 : a b c
	quad2->cterm = 0;					// cterm : d
	quad2->yterm = 0;						// yterm : e
	quad2->lower = Vector( -25, -50, -25);
	quad2->upper = Vector( 25, 50, 25);
	// cylinder green 2
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 300, 0, -55);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( 1, 0, 1);		// vect2 : a b c
	quad2->cterm = 300;					// cterm : d
	quad2->yterm = 0;						// yterm : e
	quad2->lower = Vector( -18, 0, -18);
	quad2->upper = Vector( 18, 60, 18);
	// elliptic paraboloid purple 3
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 220, 60, 25);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( 60, 0, 60);		// vect2 : a b c
	quad2->cterm = 0;					// cterm : d
	quad2->yterm = -60;						// yterm : e
	quad2->lower = Vector( -20, -40, -20);
	quad2->upper = Vector( 20, 60, 20);
	// hyperbolic paraboloid blue 4
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 160, 30, -35);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( 2, 0, -2);		// vect2 : a b c
	quad2->cterm = 0;					// cterm : d
	quad2->yterm = -100;						// yterm : e
	quad2->lower = Vector( -15, -25, -15);
	quad2->upper = Vector( 15, 40, 15);
	// hyperboloid of one sheet orange 5
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 230, 60, 90);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( 1, -1, 1);		// vect2 : a b c
	quad2->cterm = 300;					// cterm : d
	quad2->yterm = 0;						// yterm : e
	quad2->lower = Vector( -25, -60, -25);
	quad2->upper = Vector( 25, 60, 25);
	// hyperboloid of two sheets red 6
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 500, 60, 30);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( -5, -7, 3);		// vect2 : a b c
	quad2->cterm = 700;					// cterm : d
	quad2->yterm = 0;						// yterm : e
	quad2->lower = Vector( -22, -60, -22);
	quad2->upper = Vector( 22, 60, 22);
	// ellipsoid white 7
	objs[nobjs++] = quad2 = new Quadratic;
	quad2->loc = Vector( 130, 30, 35);
	quad2->vect1 = Vector( 0, 1, 0);		// vect1 : dir
	quad2->vect2 = Vector( 8, 4, 1);		// vect2 : a b c
	quad2->cterm = 500;					// cterm : d
	quad2->yterm = 0;						// yterm : e
	quad2->lower = Vector( -25, -40, -25);
	quad2->upper = Vector( 25, 60, 25);
#else
	Sphere sphere;
	objs[nobjs++] = &sphere;
	sphere.loc = Vector( 0, 0, 0);
	sphere.vect1 = Vector( R, 0, 0);	// vect1 : radius 0 0
	sphere.n1 = sphere.vect1.x * sphere.vect1.x;	// precompute n1=radius^2
#endif
	
	int i, j;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			Scalar u, v; 			// compute a point s in camera screen plane based on {u,v}
//			v = -vw/2 + vw * (Scalar)i / ((Scalar)w - 1);	// XXX it seems like this doesn't work with examples from book : they are meant to be drawn right to left ?
			Scalar flength = 5 * 65 * 0 + 1;
			v = -vw/2 + vw * (Scalar)(w - i - 1) / ((Scalar)w - 1) / flength;
			u = -vh/2 + vh * (Scalar)(h - j - 1) / ((Scalar)h - 1) / flength;
			Vector s; 				// p=p0+(p1-p0)u+(p2-p0)v
			s = s0 + (s1 - s0) * u + (s2 - s0) * v;
			Line l = line; 			// compute final camera=> pixel vector _v
			l.dir = s - line.loc;

			t = 100000;
			n = 0;
			int nn;
			for (nn = 0; nn < nobjs; nn++)
			{
				Scalar _t;
				int ret = objs[nn]->CollisionTest( &l, &_t);
				if (ret)
				{
					if (_t < t)
					{
						n = ret;
						t = _t;
					}
				}
			}
			double val = 0;
			if (n)
				val = t;
			val = val;
			//printf( "%c", n ? 'G' : '.');
			if (n)
			{
				//printf( "%1.0f", val * 10);
				int v = val * 10;
				printf( "%d", v % 10);
			}
			else
				printf( ".");
		}
		printf( "\n");
	}

	return 0;
}
