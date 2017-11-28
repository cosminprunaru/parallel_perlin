# parallel_perlin
Perlin noise generator for 2D procedural image creation.

Took a perlin serial implementation and parallelized it in 4 ways:

	- openMP
	- MPI
	- pthreads
	- hybrid (MPI + openMP)
	- TODO --> MPI + pthreads

Original repo: https://github.com/sol-prog/Perlin_Noise
