#ifndef HEAP_KMEANS_UBARR_H
#define HEAP_KMEANS_UBARR_H

/* Authors: Greg Hamerly, Jonathan Drake and Petr Ryšavý
 * Feedback: hamerly@cs.baylor.edu
 * See: http://cs.baylor.edu/~hamerly/software/kmeans.php
 * Copyright 2015
 *
 * HeapKmeansUBarr extends HeapKmeansModified. This algorithm enhances the
 * heap algorithm by array with upper bound and also a heap for finding
 * maximum over this array. As a result this algorithm can take advantage
 * from tightening upper bound and other advantages that Hamerly's algorithm
 * have over the heap algorithm.
 */

#include "heap_kmeans_modified.h"
#include <vector>
#include <numeric>

typedef std::vector<std::pair<double, int> > Heap;

class HeapKmeansUBarr : public HeapKmeansModified {
public:

	HeapKmeansUBarr() : maxUBHeap(NULL), ubHeapBounds(NULL) {}

	virtual ~HeapKmeansUBarr() {
		free();
	}

	virtual void initialize(Dataset const *aX, unsigned short aK, unsigned short *initialAssignment, int aNumThreads);
	virtual void free();

	virtual std::string getName() const {
		return "heapubarr";
	}


protected:

	virtual int runThread(int threadId, int maxIterations);
	
	void update_bounds();

	virtual void calculate_max_upper_bound();

	// this will be set of k heaps, one for each centroid
	// each heap will store a pair of upper bound and point index
	// this allows us to find maximum over upper bound
	Heap *maxUBHeap;
	
	// this array relativizes the upper bound, similarly as the
	// heap key, so that we do not have to update all the n
	// upper bounds, but updating k is enough
	double *ubHeapBounds;
};

#endif