/************************************************
 *              CSCI 3410, HW 0
 *             Ring Buffers & FIR
 *************************************************/

#include <stdlib.h>
#include "ring.h"

struct ring * ring_create(int size) {
        /* TODO: implement this function */
	
	if(size<=0)
		return NULL;

	struct ring* r = malloc(sizeof(struct ring));
	r->size = size+1;
	r->read = 0;
	r->write = 0;
	short* d = (short*)malloc(sizeof(short)*(size+1));
	r->data = d;
	return r;
}

int ring_size(struct ring *ring) {
        /* TODO: implement this function */
	int s = 0;
	if(ring!=NULL){
		s = ((ring->write) - (ring->read));
		if(s<0)
			s = ring->size + s;
		return s;
	}
        return -1;
}

int ring_enqueue(struct ring *ring, short data) {
        /* TODO: implement this function */
	if(ring!=NULL){
		if((((ring->write)+1)%(ring->size))==(ring->read))
			return -1;
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
	
	if(ring!=NULL && datap!=NULL)
	{
		if(ring->write==ring->read)
		return -1;
		else
		{
		*datap = ring->data[ring->read];
		ring->read = (ring->read+1)%(ring->size);
		return 0;
		}
	}
	
        return -1;
}

double ring_apply_fir(struct ring *ring, double *weights) {
        /* TODO: implement this function */
	
	double w = 0.0;
	if(ring!=NULL){
	if((((ring->write)+1)%(ring->size))!=(ring->read))
	{
	return 0;
	}
	else{
		int r = ring->read;
		for(int x=0; x<(ring->size-1); x++)
		{
			w+=(ring->data[r])*weights[x];
			r = ((r+1) % (ring->size));
		}
	return w;
	}
	}
        return 0;
}

void ring_free(struct ring *ring) {
        /* TODO: implement this function */
	
	if(ring!=NULL){
	if(ring->data!=NULL)
		free(ring->data);
	free(ring);
	}
	
}
