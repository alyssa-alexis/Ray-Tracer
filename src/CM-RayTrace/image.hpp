// Image handling class

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL.h>

class Image
{

public:
	Image();

	~Image();

	void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

	void SetPixel(const int x, const int y, const double red, const double green, const double blue);

	void Display();

	int GetXSize();
	int GetYSize();


private:

	// Function that takes in RGB values and returns a single 8-bit per channel color space of 24-bit color space.
	// SDL2 will use this value.
	Uint32 ConvertColor(const double red, const double green, const double blue);

	void InitTexture();

	void ComputeMaxValues();

	
private:
	// Arrays to store image data
	std::vector<std::vector<double>> m_rChannel;

	std::vector<std::vector<double>> m_gChannel;

	std::vector<std::vector<double>> m_bChannel;


	int m_xSize;
	int m_ySize;

	double m_maxRed;
	double m_maxGreen;
	double m_maxBlue;
	double m_overallMax;

	SDL_Renderer *m_pRenderer;
	SDL_Texture *m_pTexture;

};


#endif // !IMAGE_H
