#include <iostream>
#include <fstream>

// objects.cpp p189
#include "render.hpp"

//p189
Sphere::Sphere()
{
	type = SPHERE;
	nextobj = NULL;
	child = NULL;
	pattern = NULL;
	remove = NULL;
	name[0] = 0;
	xmult = 1;
	ymult = 1;
	upper = Vector();
	lower = Vector();
}

//p191
Quadratic::Quadratic()
{
	type = QUADRATIC;
	nextobj = NULL;
	child = NULL;
	pattern = NULL;
	remove = NULL;
	name[0] = 0;
	cterm = 0;
	yterm = 0;
	xmult = 1;
	ymult = 1;
	upper = Vector();
	lower = Vector();
}

//p202
int Object :: CollisionTest(Line * line, Scalar *t)
{
	return 0;
}

// p202
int Sphere :: CollisionTest(Line * line, Scalar *t)
{
	Scalar a,b,c,d,t1;
	Vector temp;
	temp = loc - line->loc;
	c = (temp % temp) - n1;
	b = -2*(line->dir % temp);
	a = line->dir % line->dir;
	d = b*b - 4.0*a*c;
	if (d<=0)
		return(FALSE);
	d=sqrt(d); *t=(-b+d)/(a+a);
	t1=(-b-d)/(a+a);
	if (*t<=SMALL && t1 <=SMALL)
		return(FALSE);
	if (t1 > *t)
	{
		if (*t < SMALL)
			*t = t1;
	}
	else
		if (t1 > SMALL)
			*t = t1;
	return(TRUE);
}

// p207
int Quadratic :: CollisionTest(Line * line, Scalar *t)
{
	Scalar a, b, c, d, t1;
	Vector location, loc1, tempdir;
	Line newline;

	newline.loc = line->loc - loc;
	if ((vect1.x == 0) && (vect1.y == 1) && (vect1.z == 0))
		newline.dir = line->dir;
	else
	{
		newline.dir = line->dir.Rotate(cos1, sin1, cos2, sin2);
		newline.loc = newline.loc.Rev_Rotate(cos1, sin1, cos2, sin2);
	}
	if (yterm == 0)
	{
		c = -(cterm) + vect2.x * newline.loc.x * newline.loc.x +
			vect2.y * newline.loc.y * newline.loc.y +
			vect2.z * newline.loc.z * newline.loc.z;
		b = 2*(vect2.x * newline.loc.x * newline.dir.x +
			vect2.y * newline.loc.y * newline.dir.y +
			vect2.z * newline.loc.z * newline.dir.z);
		a = vect2.x * newline.dir.x * newline.dir.x +
			vect2.y * newline.dir.y * newline.dir.y +
			vect2.z * newline.dir.z * newline.dir.z;
	}
	else
	{
		c = -(cterm) + vect2.x * newline.loc.x * newline.loc.x -
			yterm * newline.loc.y +
			vect2.z * newline.loc.z * newline.loc.z;
		b = 2*(vect2.x * newline.loc.x * newline.dir.x -
			yterm * newline.dir.y +
			vect2.z * newline.loc.z * newline.dir.z);
		a = vect2.x * newline.dir.x * newline.dir.x +
			vect2.z * newline.dir.z * newline.dir.z;
	}
	d = b * b - 4.0*a*c;
	if (d<0)
		return(FALSE);
	d = sqrt(d);
	*t = (-b+d)/(a+a);
	t1 = (-b-d)/(a+a);
	location = newline.loc + (newline.dir * *t);
	loc1 = newline.loc + (newline.dir * t1);
	if ((location.x < lower.x) ||
		(location.x > upper.x) ||
		(location.y < lower.y) ||
		(location.y > upper.y) ||
		(location.z < lower.z) ||
		(location.z > upper.z))
		*t = -1;
	if ((loc1.x < lower.x) ||
		(loc1.x > upper.x) ||
		(loc1.y < lower.y) ||
		(loc1.y > upper.y) ||
		(loc1.z < lower.z) ||
		(loc1.z > upper.z))
		t1 = -1;
	if (*t<=SMALL && t1 <=SMALL)
		return(FALSE);
	if (t1 > *t)
	{
		if (*t < SMALL)
			*t = t1;
	}
	else
		if (t1 > SMALL)
		*t = t1;
	return(TRUE);
}

// custom
Scene::~Scene()
{
	Object *obj = objlist;
//	asm volatile("int $3");
	while (obj)
	{
		Object *next = obj->nextobj;
		delete obj;
		obj = next;
	}
}
void Scene::dump( std::ostream& os)
{
	os 	<< " version=" << version << std::endl
    	<< " loc=" << loc.x << ":" << loc.y << ":" << loc.z << std::endl
    	<< " lookat=" << lookat.x << ":" << lookat.y << ":" << lookat.z << std::endl
    	<< " up=" << up.x << ":" << up.y << ":" << up.z << std::endl
		<< " width=" << width << std::endl
		<< " height=" << height << std::endl
		<< " flength=" << flength << std::endl
	;
	Object *obj = objlist;
	int nobjs = 0;
	while (obj)
	{
//		os << " type=" << (int)obj->type << std::endl;
		obj = obj->nextobj;
		nobjs++;
	}
	os	<< "found " << nobjs << " objs" << std::endl;
}

void Scene::load( const char *filename)
{
	std::ifstream myfile;
    myfile.open( "scene.ray");
    myfile >> *this;
    myfile.close();
}

std::ostream& operator<<( std::ostream& os, Scene& rvalue)
{
	os	<< rvalue.version << " " << rvalue.loc << " " << rvalue.lookat << " " << rvalue.up << " " << rvalue.width << " " << rvalue.height
		<< " " << rvalue.flength << std::endl;
	Object *obj = rvalue.objlist;
	while (obj)
	{
		os << *obj << std::endl;
		obj = obj->nextobj;
	}
	
	return os;
}

std::istream& operator>>( std::istream& is, Scene& rvalue)
{
	is >> rvalue.version;
	if (rvalue.version > Scene::SCENE_VERSION)
	{
		std::cout << "scene version unsupported (mine is " << Scene::SCENE_VERSION << " scene is " << rvalue.version << ")" << std::endl;
		exit( 1);
	}
	is >> rvalue.loc >> rvalue.lookat >> rvalue.up >> rvalue.width >> rvalue.height >> rvalue.flength;
	Object **pobj = &rvalue.objlist;
	int nobjs = 0;
	while (!is.eof())
	{
		*pobj = Object::load0( is);
		if (!*pobj)
			break;
		pobj = &((*pobj)->nextobj);
		nobjs++;
	}
	return is;
}

int Scene::nobjs()
{
	int nobjs = 0;
    Object *obj = objlist;
    while (obj)
    {
        obj = obj->nextobj;
        nobjs++;
    }
    return nobjs;
}

void Quadratic::dump( std::ostream& os)
{
	os 	<< " " << loc << " " << vect1 << " " << vect2 << " " << cterm << " " << yterm << " " << lower << " " << upper << std::endl;
}

void Quadratic::load( std::istream& is)
{
	is >> loc >> vect1 >> vect2 >> cterm >> yterm >> lower >> upper;
}

std::ostream& operator<<( std::ostream& os, Object& rvalue)
{
	os << " " << (int)rvalue.type;
	rvalue.dump( os);
	return os;
}

Object* Object::load0( std::istream& is)
{
	Object* result = 0;
	int ty;
	is >> ty;
	if (!is.eof())
	{
	switch (ty)
	{
		case SPHERE: result = new Sphere; break;
		case QUADRATIC: result = new Quadratic; break;
	}
	if (result)
		result->load( is);
	}

	return result;
}

void Sphere::dump( std::ostream& os)
{
	os << " " << loc << " " << vect1 << std::endl;
}

void Sphere::load( std::istream& is)
{
	is	>> loc 	>> vect1;
}
