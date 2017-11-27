#include <cmath>
#include <omp.h>
#include "ppm.h"
#include "PerlinNoise.h"

int main() {
	
	/**
	 * Define the size of the image
	 */
	unsigned int width = 1920, height = 1080;

	/**
	 * Create an empty PPM image
	 */
	ppm image(width, height);

	/**
	 * Create a PerlinNoise object with a random permutation vector generated with seed
	 */
	unsigned int seed = 237;
	PerlinNoise pn(time(NULL));

	/**
	 * Visit every pixel of the image and assign a color generated with Perlin noise
	 */
	# pragma omp parallel for collapse(2) shared(pn)
	for(unsigned int i = 0; i < height; ++i) {     // y
		for(unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j/((double)width);
			double y = (double)i/((double)height);

			/**
			 * Typical Perlin noise
			 */
			double n = pn.noise(10 * x, 10 * y, 0.8);

			/** 
			 * Map the values to the [0, 255] interval
			 */
			image.r[i * width + j] = floor(255 - 255 * n);
			image.g[i * width + j] = floor(255 - 127 * n);
			image.b[i * width + j] = floor(255 - 0 * n);
		}
	}

	/**
	 * Save the image in a binary PPM file
	 */
	image.write("sky.ppm");

	return 0;
}
