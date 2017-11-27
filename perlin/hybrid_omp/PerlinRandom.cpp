#include <iostream>
#include <cmath>
#include <mpi.h>
#include <omp.h>
#include "ppm.h"
#include "PerlinNoise.h"

int main(int argc, char **argv) {
	/**
	 * Define the size of the image
	 */
	unsigned int width = 1920, height = 1080;

	int numtasks, rank;
	
	MPI_Status stat;

	/**
	 * MPI Initialization
	 */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	

	unsigned int arr_size = width * height * sizeof(unsigned char);

	unsigned char *r = (unsigned char *) malloc(arr_size);
    unsigned char *g = (unsigned char *) malloc(arr_size);
    unsigned char *b = (unsigned char *) malloc(arr_size);

    unsigned char *local_r = (unsigned char *) malloc(arr_size / numtasks);
    unsigned char *local_g = (unsigned char *) malloc(arr_size / numtasks);
    unsigned char *local_b = (unsigned char *) malloc(arr_size / numtasks);

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
	#pragma omp parallel for collapse(2) shared(pn)
	for(unsigned int i = rank * height / numtasks; i < height * (rank + 1) / numtasks; ++i) {     // y
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
			local_r[i * width + j - rank * arr_size / numtasks] = floor(255 - 255 * n);
			local_g[i * width + j - rank * arr_size / numtasks] = floor(255 - 127 * n);
			local_b[i * width + j - rank * arr_size / numtasks] = floor(255);
		}
	}

	MPI_Gather(local_r, arr_size / numtasks, MPI_UNSIGNED_CHAR, r, arr_size / numtasks, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	MPI_Gather(local_g, arr_size / numtasks, MPI_UNSIGNED_CHAR, g, arr_size / numtasks, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	MPI_Gather(local_b, arr_size / numtasks, MPI_UNSIGNED_CHAR, b, arr_size / numtasks, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		
		/**
		 * insert into image
		 */
		#pragma omp parallel for
		for (int i = 0; i < arr_size; ++i) {
			image.r[i] = r[i];
			image.g[i] = g[i];
			image.b[i] = b[i];
		}
		
		/**
		 * Save the image in a binary PPM file
		 */
		image.write("sky.ppm");
	}
	MPI_Finalize();

	return 0;
}
