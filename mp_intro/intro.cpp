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

    RGBAPixel color1(200, 60, 60);   // red
    RGBAPixel color2(60, 180, 60);   // green
    RGBAPixel color3(60, 60, 196);   // blue
	RGBAPixel color4(255, 255, 255); // white
	
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            // calculate the distance to the center of the image
            double distance = sqrt(pow(x - width / 2.0, 2) + pow(y - height / 2.0, 2));

            // color based on the distance
            if (distance < width / 3.9) {
                *png(x, y) = color1;
            } else if (distance < 1 * width / 3.0) {
                *png(x, y) = color2;
			} else if (distance < 1.5 * width / 3.0) {
				*png(x, y) = color3;
            } else {
                *png(x, y) = color4;
            }
        }
    }

	return png;
}
