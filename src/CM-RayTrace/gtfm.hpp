// Class for geometric transformations

#ifndef GTFM_H
#define GTFM_H

#include "\qbLinAlg-main\qbVector.h"
#include "\qbLinAlg-main\qbMatrix.h"
#include "./ray.hpp"

namespace CMRT
{
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;

	class GTform
	{
	public:

		GTform();

		~GTform();

		GTform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale);

		// matrix pairs: forward and backward transforms
		GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);

		void SetTransform(	const qbVector<double> &translation, 
							const qbVector<double> &rotation, 
							const qbVector<double> &scale);

		qbMatrix2<double> GetForward();
		qbMatrix2<double> GetBackward();

		CMRT::Ray Apply(const CMRT::Ray &inputRay, bool dirFlag);
		qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);

		friend GTform operator* (const CMRT::GTform &lhs, const CMRT::GTform &rhs);

		GTform operator= (const GTform &rhs);


		// functions to help debugging (later)

		void PrintMatrix(bool dirFlag);

		static void PrintVector(const qbVector<double> &vector);

		
	private:
		void Print(const qbMatrix2<double> &matrix);
	
	private:
		// 4x4 matrices due to homogenous coordinates
		qbMatrix2<double> m_fwdtfm{ 4,4 };
		qbMatrix2<double> m_bcktfm{ 4,4 };
	};

}


#endif //!GTFM_H