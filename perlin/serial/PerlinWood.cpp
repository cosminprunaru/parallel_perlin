#include <iostream>
#include <cmath>
#include "ppm.h"
#include "PerlinNoise.h"

int main(int argc, char **argv) {	

	/**
	 * Full HD
	 */
	unsigned int width = 1920, height = 1080;	

	/**
	 * Create an empty PPM image
	 */
	ppm image(width, height);

	/**
	 * Create a PerlinNoise object with the reference permutation vector
	 */
	PerlinNoise pn;
	
	/**
	 * Visit every pixel of the image and assign a color generated with Perlin noise
	 */
	for(unsigned int i = 0; i < height; ++i) {     // y
		for(unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j/((double)width);
			double y = (double)i/((double)height);

			/**
			 * Wood like structure
			 */
			double n = 20 * pn.noise(x, y, 0.8);
			n = n - floor(n);
			
			/** 
			 * Map the values to the [0, 255] interval 
			 */
			image.r[i * width + j] = floor(133 * n);
			image.g[i * width + j] = floor(94 * n);
			image.b[i * width + j] = floor(66 * n);
		}
	}

	/**
	 * Save the image in a binary PPM file
	 */
	image.write("wood.ppm");
	
	return 0;
}
