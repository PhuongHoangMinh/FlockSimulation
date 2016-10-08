#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <limits>
#include "utils.h"

struct Vector3D
{
public:
	double x;
	double y;
	double z;

	Vector3D():x(0.0), y(0.0), z(0.0){}
	Vector3D(double xval, double yval, double zval): x(xval), y(yval), z(zval)
	{}

	
	//set x, y and z to zero
	void Zero() {x = 0.0; y = 0.0; z= 0.0;}

	//return true if 
	//returns true if both x and y are zero
	bool isZero()const{return (x*x + y*y + z*z) < MinDouble;}

	//inline double  
	
	//returns the length of the vector
	inline double    Length()const;

	//returns the squared length of the vector (thereby avoiding the sqrt)
	inline double    LengthSq()const;

	inline void      Normalize();

	inline double    Dot(const Vector3D& v2)const;

	////returns positive if v2 is clockwise of this vector,
	////negative if anticlockwise (assuming the Y axis is pointing down,
	////X axis to right like a Window app)
	//inline int       Sign(const Vector2D& v2)const;

	// //returns the vector that is perpendicular to this one.
	//inline Vector2D  Perp()const;

	
	//adjusts x and y so that the length of the vector does not exceed max
	inline void Truncate(double max);

	inline double Distance(const Vector3D &v2)const;

	inline double DistanceSq(const Vector3D &v2)const;

	//inline void      Reflect(const Vector2D& norm);

	////returns the vector that is the reverse of this vector
	//inline Vector2D  GetReverse()const;

	
	//some overloaded operators
	const Vector3D& operator+=(const Vector3D &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	const Vector3D& operator-=(const Vector3D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
		
	}

	const Vector3D&	operator*=(const double& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
		
	}

	const Vector3D& operator/=(const double &rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;

		return *this;
	
	}

	bool operator==(const Vector3D& rhs)const
	{
		return (isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z));
	}

	bool operator!=(const Vector3D& rhs)const
	{
		return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
	}

};


//-----------------------------------------------------------------------some more operator overloads
inline Vector3D operator*(const Vector3D &lhs, double rhs);
inline Vector3D operator*(double lhs, const Vector3D &rhs);
inline Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs);
inline Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs);
inline Vector3D operator/(const Vector3D &lhs, double val);
//std::ostream& operator<<(std::ostream& os, const Vector2D& rhs);
//std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs);


inline double Vector3D::Length() const
{

	return sqrt(x*x + y*y + z*z);
}

inline double Vector3D::LengthSq() const
{
	return (x*x + y*y + z*z);
}

//------------------------- Vec2DDot -------------------------------------
//
//  calculates the dot product
//------------------------------------------------------------------------
inline double Vector3D::Dot(const Vector3D& v2)const
{

	return x*v2.x + y*v2.y + z*v2.z;
}

//------------------------------ Distance --------------------------------
//
//  calculates the euclidean distance between two vectors
//------------------------------------------------------------------------
inline double Vector3D::Distance(const Vector3D &v2) const
{
	double xDistance = v2.x - x;
	double yDistance = v2.y - y;
	double zDistance = v2.z - z;

	return sqrt(xDistance*xDistance + yDistance*yDistance + zDistance*zDistance );
}

//------------------------------ DistanceSq ------------------------------
//
//  calculates the euclidean distance squared between two vectors 
//------------------------------------------------------------------------
inline double Vector3D::DistanceSq(const Vector3D &v2) const
{
	double xDistance = v2.x - x;
	double yDistance = v2.y - y;
	double zDistance = v2.z - z;
	

	return xDistance*xDistance + yDistance*yDistance + zDistance*zDistance;
}

//----------------------------- Truncate ---------------------------------
//
//  truncates a vector so that its length does not exceed max
//------------------------------------------------------------------------
inline void Vector3D::Truncate(double max)
{
	if(this->Length() > max)
	{
		this->Normalize();

		*this *= max;
	}

}

//------------------------- Normalize ------------------------------------
//
//  normalizes a 2D Vector
//------------------------------------------------------------------------
inline void Vector3D::Normalize()
{
	double vector_length = this->Length();

	if(vector_length > std::numeric_limits<double>::epsilon())
	{
		this->x /= vector_length;
		this->y /= vector_length;
		this->z /= vector_length;
	}

}

//------------------------------------------------------------------------non member functions

inline Vector3D Vec3DNormalize(const Vector3D &v)
{
	Vector3D vec = v;

	double vector_length = vec.Length();

	if (vector_length > std::numeric_limits<double>::epsilon())
	{
		vec.x /= vector_length;
		vec.y /= vector_length;
		vec.z /= vector_length;
	}

	return vec;

}


inline double Vec3DDistance(const Vector3D &v1, const Vector3D &v2)
{
	double xDistance = v2.x - v1.x;
	double yDistance = v2.y - v1.y;
	double zDistance = v2.z - v1.z;

	return sqrt(xDistance*xDistance + yDistance*yDistance +zDistance*zDistance);

}


inline double Vec3DDistanceSq(const Vector3D &v1, const Vector3D &v2)
{
	double xDistance = v2.x - v1.x;
	double yDistance = v2.y - v1.y;
	double zDistance = v2.z - v1.z;

	return xDistance*xDistance + yDistance*yDistance +zDistance*zDistance;


}

inline double Vec3DLength(const Vector3D& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}


inline double Vec3DLengthSq(const Vector3D& v)
{

	return (v.x*v.x + v.y*v.y + v.z*v.z);
}

//------------------------------------------------------------------------operator overloads
inline Vector3D operator*(double lhs, const Vector3D &rhs)
{
	Vector3D result(rhs);

	result.x *= lhs;
	result.y *= lhs;
	result.z *= lhs;
	//result *= lhs;
	
	return result;
}

inline Vector3D operator*(const Vector3D &lhs, double rhs)
{
	Vector3D result(lhs);
	result.x *= rhs;
	result.y *= rhs;
	result.z *= rhs;
	//result *= rhs;
	return result;
}

inline Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs)
{
	Vector3D result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;
	result.z -= rhs.z;

	return result;
}

inline Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
{
	Vector3D result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;
	result.z += rhs.z;

	return result;
}

inline Vector3D operator/(const Vector3D &lhs, double val)
{
	Vector3D result(lhs);
	result.x /= val;
	result.y /= val;
	result.z /= val;

	return result;
}

#endif