#ifndef RAY_H
#define RAY_H

#include "\qbLinAlg-main\qbVector.h"

namespace CMRT
{
	class Ray 
	{
	public:
		Ray();

		Ray(const qbVector<double>& point1, const qbVector<double>& point2);

		qbVector<double> GetPoint1() const;
		qbVector<double> GetPoint2() const;

	public:
		qbVector<double> m_point1	{ 3 };
		qbVector<double> m_point2	{ 3 };
		qbVector<double> m_lab		{ 3 };
	};
}

#endif // !RAY_H
