#include <stdio.h>
#include <string.h>

#include "render.hpp"

int main()
{
	Line line;
	Vector up, lookat;
	Scalar flength;
	int w, h, nobjs;
	Object *objs = 0;

	Scene scene;
	scene.load( "scene.ray");
    scene.dump( std::cout);
// convert scene to local vars	
	w = scene.width; h = scene.height; objs = scene.objlist; flength = scene.flength; line.loc = scene.loc; lookat = scene.lookat; up = scene.up; objs = scene.objlist; nobjs = scene.nobjs();

	line.dir = lookat - line.loc;
	line.dir = line.dir / sqrt(line.dir % line.dir);;

	Scalar zoom = flength;
	Scalar vw = 1.0 / zoom;
	Scalar vh = 1.0 * h / w / zoom;

	Vector right = line.dir ^ up;
	up = right ^ line.dir;
	Vector s0, s1, s2;
	s0 = line.loc + line.dir;
	s1 = s0 + up;
	s2 = s0 + right;

	int i, j;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			Scalar t;
			int n;
			Scalar u, v; 			// compute a point s in camera screen plane based on {u,v}
//			v = -vw/2 + vw * (Scalar)i / ((Scalar)w - 1);	// XXX it seems like this doesn't work with examples from book : they are meant to be drawn right to left ?
			v = -vw/2 + vw * (Scalar)(w - i - 1) / ((Scalar)w - 1) / flength;
			u = -vh/2 + vh * (Scalar)(h - j - 1) / ((Scalar)h - 1) / flength;
			Vector s; 				// p=p0+(p1-p0)u+(p2-p0)v
			s = s0 + (s1 - s0) * u + (s2 - s0) * v;
			Line l = line; 			// compute final camera=> pixel vector _v
			l.dir = s - line.loc;

			t = 100000;
			n = 0;
			int nn;
			Object *obj = objs;
			for (nn = 0; nn < nobjs; nn++)
			{
				Scalar _t;
				int ret = obj->CollisionTest( &l, &_t);
				if (ret)
				{
					if (_t < t)
					{
						n = ret;
						t = _t;
					}
				}
				obj = obj->nextobj;
			}
			double val = 0;
			if (n)
				val = t;
			val = val;
			if (n)
			{
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
