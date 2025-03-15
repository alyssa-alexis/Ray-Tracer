// Texture base class construction.


#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <memory>
#include "../qbLinAlg-main/qbMatrix.h"
#include "../qbLinAlg-main/qbVector.h"
#include "../ray.hpp"


namespace CMRT
{
	namespace Texture
	{
		class TextureBase
		{
			public:

				TextureBase();

				virtual ~TextureBase();

				// note: color is returned as a 4D vector (RGBA).
				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords);

				// note: plane texture rotation is 2D, so only one angle for rotation.
				void SetTransform(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale);

				// Blend RGBA colors to return a 3D vector (RGB)
				static qbVector<double> BlendColors(const std::vector<qbVector<double>> &inputColorList);
				
				qbVector<double> ApplyTransform(const qbVector<double> &inputVector);

			private:
				// functions (later)

			private:
				// Identity matrix
				// 2D vectors here, so 3x3 transform matrix
				qbMatrix2<double> m_transformMatrix{ 3, 3, std::vector<double>{	1.0, 0.0, 0.0, 0.0,
																				1.0, 0.0, 0.0, 0.0,
																				1.0} };
		};
	}
}
#endif // !TEXTUREBASE_H
