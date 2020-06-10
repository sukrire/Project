/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef SIMULATION_H
#define SIMULATION_H

struct simulation
{
	// All the parameters necessary to estimate decoding failure rates for a range of physical noise rates.
	/*
		number of non-open vertices in the tiling and its dual
		nOV : array of 2 int
			(0) -- primal
			(1) -- dual
	*/
	int *nOV;
	
	/*
		number of connected components with no closed edges in the tiling and its dual
		comps : array of 2 int
			comps[0] -- connected componentes in the primal tiling
			comps[1] -- connected componens in the dual tiling
	*/
	int *comps;
	
	/*
		ordering of edges in the tiling, dual and dual-of-dual tiling.
		edgeOrderings : array of 3 int pointers
			edgeOrderings[0) -- ordering of edges in the dual graph with respect to the ordering in the primal graph (EToDE)
			edgeOrderings[2] -- ordering of edges in the primal graph with respect to the ordering in the dual graph (DEToE)
			edgeOrderings[3] -- ordering of edges in the dual-dual graph with respect to the ordering in the dual graph (DDEToDE)
	*/
	int **edgeOrderings;

	// minimum relative error bar that can be tolerated
	float accuracy;
	
	// number of Montecarlo trials to estimate a logical failure rate
	long stats;
	
	// minimum number of Montecarlo trials required for any estimation
	int minfails;
	
	/*
		type of error for which correctability must be tested for.
		type (int)
			 = 0 for both X and Z
			 = 1 for only X
			 = 2 for only Z
	*/
	int type;

	/*
		weight of the erasure as well as the indicator vector of erased edges on the graph and its dual.
		erasure -- array of 3 int pointers
				erasure[0] = array of 2 int
					erasure[0][0] -- weight of erasure on primal tiling
					erasure[0][1] -- weight of erasure on dual tiling
				erasure[1] -- array of e int where e is the total number of edges in the primal tiling.
					erasure[1][j] -- 1 if j-th edge in the primal graph is erased, 0 otherwise
				erasure[2] -- array of e int where e is the total number of edges in the dual tiling.
					erasure[2][j] -- 1 if j-th edge in the dual graph is erased, 0 otherwise
	*/
	int **erasure;

	// local time at which the simulation was carried out.
	char *timestamp;

	// total simulation runtime
	double runtime;

	// total number of decoding trials done in a simulation, for all noise rates.
	long totaltrials;
};

// Compute the error bar for a dataset describing decoding failures over decoding trials
extern double ErrorBar(double pfail, long nSamps);

// Count the number of non-open vertices of a Tiling.
extern int NonOpenVertices(struct tiling* pG);

// Preprocessing for the round of Montecarlo simulations to estimate decoding failure probability
extern void InitializeSimulation(struct simulation* pSim, struct tiling **pGs, int nRates, long nStats);

// Free memory allocated for simulation
extern void FreeSimulation(struct simulation* pSim, int nRates);

#endif /* SIMULATION_H */
