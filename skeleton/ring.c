/************************************************
 *              CSCI 3410, HW 0
 *             Ring Buffers & FIR
 *************************************************/

#include <stdlib.h>
#include "ring.h"

struct ring * ring_create(int size) {
        /* TODO: implement this function */
	
//checks for input size being less than or equal to 0
	if(size<=0)
		return NULL;

//allocates memory for ring object
	struct ring* r = malloc(sizeof(struct ring));
//sets ring variables
	r->size = size+1;
	r->read = 0;
	r->write = 0;
//creates pointer and allocates memory for the ring's data
	short* d = (short*)malloc(sizeof(short)*(size+1));
	r->data = d;
//returns the created ring
	return r;
}

int ring_size(struct ring *ring) {
        /* TODO: implement this function */
//checks for null cases and returns -1 on null parameter
	int s = 0;
	if(ring!=NULL){
//compares location of write and read vars to find the number of items in ring
		s = ((ring->write) - (ring->read));
		if(s<0)
			s = ring->size + s;
		return s;
	}
        return -1;
}

int ring_enqueue(struct ring *ring, short data) {
        /* TODO: implement this function */
//null case for the ring parameter
	if(ring!=NULL){
//checks if the ring buffer is full
		if((((ring->write)+1)%(ring->size))==(ring->read))
			return -1;
//if not full, writes the given data to the ring at the write location and moves
//write forward one index
		else
		{
			ring->data[ring->write] = data;
			ring->write = ((ring->write)+1)%(ring->size);
			return 0;
		}
	}
	return -1;
}

int ring_dequeue(struct ring *ring, short *datap) {
        /* TODO: implement this function */
	
//checks if either of the inputs are null
	if(ring!=NULL && datap!=NULL)
	{
//checks for if the ring is empty
		if(ring->write==ring->read)
		return -1;
		else
		{
//else, set the data at the 'read' location to the value of the datap pointer
//increment read variable by one
		*datap = ring->data[ring->read];
		ring->read = (ring->read+1)%(ring->size);
		return 0;
		}
	}
	
        return -1;
}

double ring_apply_fir(struct ring *ring, double *weights) {
        /* TODO: implement this function */
	
//checks for if the ring is null
	double w = 0.0;
	if(ring!=NULL){
//checks if the ring is not full
	if((((ring->write)+1)%(ring->size))!=(ring->read))
	{
	return 0;
	}
	else{
//for loop to multiply each index starting at the read value by each index
//of the given "weights"
		int r = ring->read;
		for(int x=0; x<(ring->size-1); x++)
		{
			w+=(ring->data[r])*weights[x];
			r = ((r+1) % (ring->size));
		}
//returns the summation
	return w;
	}
	}
        return 0;
}

void ring_free(struct ring *ring) {
        /* TODO: implement this function */
	
//frees the data of the ring and the ring itself if they exist
	if(ring!=NULL){
	if(ring->data!=NULL)
		free(ring->data);
	free(ring);
	}
	
}
