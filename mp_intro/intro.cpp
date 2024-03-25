#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
	PNG pic(inputFile);
	unsigned int width = pic.width();
	unsigned int height = pic.height();

	// create rotatedPic with the same dimensions as the original pic
	PNG rotatedPic(width, height);

	// go over pixels
	for (unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {
			// coordinates in the rotated image
			unsigned int newX = width - x - 1;
			unsigned int newY = height - y - 1;

			RGBAPixel* originalPixel = pic(x, y);

			*rotatedPic(newX, newY) = *originalPixel;
		}
	}

	rotatedPic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here
	return png;
}
