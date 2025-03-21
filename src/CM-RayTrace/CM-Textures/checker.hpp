// Sub-class: Checkered textures

#ifndef CHECKER_H
#define CHECKER_H

#include "texturebase.hpp"

namespace CMRT
{
	namespace Texture
	{
		class Checker : public TextureBase
		{
			public:

				Checker();

				virtual ~Checker() override;

				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;

				void SetColor(const qbVector<double> &inputColor1, const qbVector<double> &inputColor2);


			private:
				qbVector<double> m_color1	{ 4 };
				qbVector<double> m_color2	{ 4 };
		};
	}
}

#endif // !CHECKER_H
