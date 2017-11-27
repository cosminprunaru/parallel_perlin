#include <iostream>
#include <unistd.h>
#include <cmath>
#include <stdint.h>
#include <pthread.h>
#include "ppm.h"
#include "PerlinNoise.h"

#define NUM_THREADS 4

/**
 * Define size of image
 */
unsigned int width = 1920, height = 1080;

/**
 * Create empty image ppm
 */
ppm image(width, height);

/**
 * Create a PerlinNoise object with a random permutation vector
 */
PerlinNoise pn;

void *perlin(void *arg) {
	int start = (intptr_t) arg;
	int chunk = height / NUM_THREADS;
	int end = start + chunk;

	/**
	 * Visit every pixel of the image and assign a color generated with Perlin noise
	 */
	for(unsigned int i = start; i < end; ++i) {     // y
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
}

int main(int argc, char **argv) {
	
	/**
	 * Creare array to hold threads
	 */
	pthread_t tids[NUM_THREADS];
	
	/** 
	 * Create and start the threads
	 */
	for (int i = 0; i < NUM_THREADS; ++i) {
		pthread_create(&tids[i], NULL, perlin, (void *)(intptr_t)(i * height / NUM_THREADS));
	}
	
	/**
 	 * Wait for every thread to finish
	 */
	for (int i = 0; i < NUM_THREADS; ++i) {
		pthread_join(tids[i], NULL);
	}

	/**
	 * Save the image in a binary PPM file
	 */
	image.write("wood.ppm");

	return 0;
}
