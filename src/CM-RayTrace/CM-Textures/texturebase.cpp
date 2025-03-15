// Base Texture methods (6 total)

#include "texturebase.hpp"
#include <cmath>

CMRT::Texture::TextureBase::TextureBase(){}

CMRT::Texture::TextureBase::~TextureBase(){}

qbVector<double> CMRT::Texture::TextureBase::GetColor(const qbVector<double> &uvCoords)
{
	qbVector<double> outputColor	{ 4 };

	return outputColor;
}

void CMRT::Texture::TextureBase::SetTransform(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale)
{
	qbMatrix2<double> rotationMatrix = { 3, 3, std::vector<double>{	cos(rotation), -sin(rotation), 0.0,
																	sin(rotation), cos(rotation), 0.0,
																	0.0, 0.0, 1.0} };

	qbMatrix2<double> scaleMatrix = { 3, 3, std::vector<double>{	scale.GetElement(0), 0.0, 0.0,
																	0.0, scale.GetElement(1), 0.0,
																	0.0, 0.0, 1.0} };

	qbMatrix2<double> translationMatrix = { 3, 3, std::vector<double> {	1.0, 0.0, translation.GetElement(0),
																		0.0, 1.0, translation.GetElement(1),
																		0.0, 0.0, 1.0} };

	m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

qbVector<double> CMRT::Texture::TextureBase::BlendColors(const std::vector<qbVector<double>> &inputColorList)
{
	qbVector<double> outputColor	{ 3 };

	return outputColor;
}

qbVector<double> CMRT::Texture::TextureBase::ApplyTransform(const qbVector<double> &inputVector)
{
	qbVector<double> newInput  { 3 };
	newInput.SetElement(0, inputVector.GetElement(0));
	newInput.SetElement(1, inputVector.GetElement(1));

	qbVector<double> result = m_transformMatrix * newInput;

	qbVector<double> output		{ 2 };
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));

	return output;
}