// Sub-class methods: flat texture (4 total)

#include "flat.hpp"

CMRT::Texture::Flat::Flat()
{
	m_color = qbVector<double>{ std::vector<double> { 0.0, 0.0, 0.0, 1.0} };
}

CMRT::Texture::Flat::~Flat() {}

qbVector<double> CMRT::Texture::Flat::GetColor(const qbVector<double> &uvCoords)
{
	return m_color;
}

void CMRT::Texture::Flat::SetColor(const qbVector<double> &inputColor)
{
	m_color = inputColor;
}