#include "metis.h"
#include <stdio.h>


// Install metis from:
// http://glaros.dtc.umn.edu/gkhome/fetch/sw/metis/metis-5.1.0.tar.gz

// Build with
// g++ metis.cc -lmetis

int main(){

    const idx_t nVertices = 6;
    idx_t nEdges    = 7;
    idx_t nWeights  = 1;
    idx_t nParts    = 2;

    idx_t objval;
    idx_t part[nVertices];


    // Indexes of starting points in adjacent array
    idx_t xadj[7] = {0,2,5,7,9,12,14};

    // Adjacent vertices in consecutive index order
    idx_t adjncy[14] = {1,3,0,4,2,1,5,0,4,3,1,5,4,2};

    // Weights of vertices
    // if all weights are equal then can be set to NULL
    idx_t vwgt[nVertices * nWeights];


    // int ret = METIS_PartGraphRecursive(&nVertices,& nWeights, xadj, adjncy,
    // 				       NULL, NULL, NULL, &nParts, NULL,
    // 				       NULL, NULL, &objval, part);

    int ret = METIS_PartGraphKway(&nVertices,& nWeights, xadj, adjncy,
				       NULL, NULL, NULL, &nParts, NULL,
				       NULL, NULL, &objval, part);

    printf("%d", ret);

    unsigned part_i;
    for(part_i = 0; part_i < nVertices; part_i++){
	     printf( "%d:\t %ld\n" , part_i,  part[part_i]);
    }


    return 0;
}
