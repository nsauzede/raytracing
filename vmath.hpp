// vmath.hpp p48
#include <iostream>
#include <math.h>

#define USE_COPY_CTOR

#ifdef USE_FLOAT
typedef float Scalar;
#else
typedef double Scalar;
#endif

class Vector {
	public:
		Scalar x, y, z;
		Vector();
		Vector(Scalar x1, Scalar y1, Scalar z1);
		Vector( const Vector &);
		Vector operator=(const Vector &);
		Vector operator+(const Vector &);
		Vector operator-(const Vector &);
		Vector operator-();
		Vector operator*(Vector &);
		Vector operator*(Scalar );
		Vector operator/(Scalar );
		Scalar operator%(const Vector &);	// Dot product
		Vector operator^(const Vector &);	// Cross product
		Vector operator~();			// Normalize vector
		Vector min(Vector &);
		Vector max(Vector &);
		Vector Rotate(Scalar cos1, Scalar sin1, Scalar cos2, Scalar sin2);
		Vector Rev_Rotate(Scalar cos1, Scalar sin1, Scalar cos2, Scalar sin2);
		friend std::ostream& operator<<(std::ostream&,Vector&);
		friend std::istream& operator>>(std::istream&,Vector&);
		void get_vector();
};
