// Sub-class: Flat textures

#ifndef FLAT_H
#define FLAT_H

#include "texturebase.hpp"

namespace CMRT
{
	namespace Texture 
	{
		class Flat : public TextureBase
		{
			public:

				Flat();

				virtual ~Flat() override;

				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;

				/* note: this was not defined in base class because some textures can have many colors */
				void SetColor(const qbVector<double> &inputColor);


			private:
				qbVector<double> m_color { 4 };		// RGBA
		};
	}
}
#endif // !FLAT_H