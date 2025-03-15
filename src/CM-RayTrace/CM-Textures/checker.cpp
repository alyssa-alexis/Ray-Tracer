// Sub-class methods: checkered texture (4 total)

#include "checker.hpp"

CMRT::Texture::Checker::Checker()
{
	m_color1 = qbVector<double>{ std::vector<double> { 1.0, 1.0, 1.0, 1.0 } };		// white
	m_color2 = qbVector<double>{ std::vector<double> { 0.2, 0.2, 0.2, 1.0 } };		// dark gray
}

CMRT::Texture::Checker::~Checker() {}

qbVector<double> CMRT::Texture::Checker::GetColor(const qbVector<double> &uvCoords)
{
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);

	qbVector<double> localColor	{ 4 };
	int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));

	if ((check % 2) == 0)
	{
		localColor = m_color1;
	}
	else
	{
		localColor = m_color2;
	}

	return localColor;
}

void CMRT::Texture::Checker::SetColor(const qbVector<double> &inputColor1, const qbVector<double> &inputColor2)
{
	m_color1 = inputColor1;
	m_color2 = inputColor2;
}