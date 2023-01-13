/*
 *  auxiliary_lib.c
 *  
 *
 *  Created by Catalina Sbert Juan on 13/11/12.
 *  Copyright 2012 Universitat de les Illes Balears. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/**
 *@brief Transform an unsigned char array into three double arrays
 *
 * @param data_in input unsigned char array
 * @return R, G, B  double array
 */

void input_rgb(float *input, double **RR, double **GG,
               double **BB, size_t size)
{
    
    int n, dim;
	double *R, *G, *B;
	
	
    R= (double*) malloc(size*sizeof(double));
    G= (double*) malloc(size*sizeof(double));
    B= (double*) malloc(size*sizeof(double));
	dim=(int) size;
	
    for (n=0; n < dim; n++) {
        R[n]=(double)input[n];
        G[n]=(double)input[dim+n];
        B[n]=(double)input[2*dim+n];
    }
	
	*RR=R; *GG=G; *BB=B;
	
    
}
/**
 *@brief Transform  three double arrays into an unsigned char array 
 *
 * 
 * @param R, G, B  double array
 * @return output  unsigned char array
 */

float *rgb_output(double *R, double *G, double *B, float *output,
                  size_t size)
{
    int n, dim;
	
	dim=(int) size;
	
    for (n=0; n < dim; n++) {
        output[n]=(float)(R[n]);
        output[dim+n]=(float)(G[n]);
        output[2*dim+n]=(float)(B[n]);
    }
	
	return output;
}


/**
 *
 *@brief Sort a double array
 *
 * x and y are pointers to doubles.
 * Returns  -1 if x < y
 * 0 if x == y
 * +1 if x > y
*/

int myComparisonFunction(const void *x, const void *y) {
	
    	
    double dx, dy;
	
    dx = *(double *)x;
    dy = *(double *)y;
	
    if (dx < dy) {
        return -1;
    } else if (dx > dy) {
        return +1;
    }
    return 0;
}

/**
 * @brief Simplest color balance
 *
 * Sort the pixels values.
 * Compute the minimium as the sorted array at position dim x s1/100
 * Compute the maximum as the sorted array at position N(1-s2/100)-1.
 * Saturate the pixels according to the computed minimum and maximum.
 * Affine transformation between [minimum, maximum] and [0,255]
 *
 * @param data input array
 * @param s1 the percentage of saturated pixels 
 * @param dim size of the array
 *
 * @return data_out the scaled array.
 */
double *simplest_color_balance(double *data_out, double *data,
                               size_t dim,float s)
{
	
	
	int per;
	int l;
	double min,max, scale;
	double *sortdata;
	
	sortdata= (double*) malloc(dim*sizeof(double));
	
	memcpy(sortdata, data, dim*sizeof(double));
	
	qsort(sortdata, dim, sizeof sortdata[0], &myComparisonFunction);
	
	per = (int) (s*dim/100);
	min=sortdata[per];
	max= sortdata[dim-1-per];
	
	
	
	if(max  <= min)  for(l=0;l< (int) dim; l++) data_out[l]=max;
	else{
		scale=255./(max-min);
		for(l=0;l< (int)dim; l++){
			if(data[l] < min) data_out[l]=0.;
			else if(data[l]> max) data_out[l]=255.;
			else data_out[l]=scale*(data[l]-min);
		}
	}
    
    free(sortdata);
	
	return data_out;
	
	
	
}
