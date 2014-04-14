// vmath.cpp p50
#include "vmath.hpp"

using namespace std;

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector( Scalar x1, Scalar y1, Scalar z1)
{
	x = x1;
	y = y1;
	z = z1;
}

Vector::Vector( const Vector& rvalue)
{
	x = rvalue.x;
	y = rvalue.y;
	z = rvalue.z;
}

Vector Vector::operator+( const Vector& arg)
{
	Vector result;
	result.x = x + arg.x;
	result.y = y + arg.y;
	result.z = z + arg.z;
	return result;
}

Vector Vector::operator-( const Vector& arg)
{
	Vector result;
	result.x = x - arg.x;
	result.y = y - arg.y;
	result.z = z - arg.z;
	return result;
}

Vector Vector::operator*( Scalar arg)
{
	Vector result;
	result.x = x * arg;
	result.y = y * arg;
	result.z = z * arg;
	return result;
}

Vector Vector::operator/(Scalar arg)
{
	Vector result;
	result.x = x / arg;
	result.y = y / arg;
	result.z = z / arg;
	return result;
}

Vector Vector::operator=( const Vector& rvalue)
{
	x = rvalue.x;
	y = rvalue.y;
	z = rvalue.z;
	return *this;
}

Vector Vector::operator~()
{
	Vector result;
	Scalar l;
	
	l = *this % *this;
	l = sqrt( l);
	result = result / l;
	return result;
}

Scalar Vector::operator%( const Vector& arg)
{
	Scalar result;
	result = x*arg.x + y*arg.y + z*arg.z;
	return result;
}

Vector Vector::operator^( const Vector& arg)
{
	Vector result;

	result.x = y * arg.z - z * arg.y;
	result.y = z * arg.x - x * arg.z;
	result.z = x * arg.y - y * arg.x;

	return result;
}

Vector Vector::Rotate(Scalar cos1, Scalar sin1, Scalar cos2, Scalar sin2)
{
	Vector temp, result;
	result.x = x * cos1 + z * -sin1;
	temp.y = y;
	result.z = x * sin1 + z * cos1;
	result.y = temp.y * -cos2 + temp.z * sin2;
	result.z = temp.y * -sin2 + temp.z * -cos2;
	return result;
}

Vector Vector::Rev_Rotate(Scalar cos1, Scalar sin1, Scalar cos2, Scalar sin2)
{
	Vector temp, result;
	temp.x = x;
	result.y = y * cos2 + z * -sin2;
	temp.z = y * sin2 + z * cos2;
	result.x = temp.x * -cos1 + temp.z * sin1;
	result.z = temp.x * -sin1 + temp.z * -cos1;
	return result;
}

ostream& operator<<( ostream& os, Vector& rvalue)
{
	return os << "(" << rvalue.x << ";" << rvalue.y << ";" << rvalue.z << ")";
}
