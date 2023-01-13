/*
 *
 * Copyright 2012 IPOL Image Processing On Line http://www.ipol.im/
 *
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
 *
 *
 * @file screened_lib.c
 * @brief laplacian, DFT and Poisson routines
 *
 * @author Catalina Sbert <catalina.sbert@uib.es>
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>


#include <fftw3.h>

#include "screened_lib.h"

/* M_PI is a POSIX definition */
#ifndef M_PI2
/** macro definition for Pi² */
#define M_PI2 9.86960440109
#endif                          /* !M_PI */





				

/**
 * @brief perform a screned  Poisson PDE in the Fourier DCT space
 *
 * @f$ (PI² i²/nx²+ PI²j²/ny²+ lambda)u(i, j) = 
 *    =(PI² i²/nx²+ PI²j²/ny²) g(i,j) @f$
 *
 * @param data  input array dct of the input image of size nx x ny
 * @param nx data array size
 * @param ny data array size
 * @param L the constant of the screened equation
 *
 * @return the data array, update
 */

double *screened_poisson_dct(double *data, size_t nx,
                             size_t ny, double L)
{
	
	double normx, normy, coeff, coeff1;
	int i,j,l;
	
	
	
	normx=M_PI2/(double)(nx*nx);
	normy=M_PI2/(double)(ny*ny);
	
	if(L > 0.){
		for(j=0;j< (int) ny; j++){
			l=j*(int)nx;
			for(i=0; i< (int) nx; i++){
				if(i==0 && j==0) data[0]=0.;
				else{
					coeff=normx*i*i+normy*j*j;
					coeff1=coeff/(coeff+L);
					data[i+l]*=coeff1;
				}
			
			}
		}
	}
	
	return data;
}   

/**
 * @brief Solve the screened Poisson equation
 *
 *  The input array is processed as follow:
 *
 * @li compute the FFT of the input array
 * @li solve the  screened Poisson equation in Fourier domain
 * @li compute the inverse FFT
 *
 *
 *
 * @param data  input array dct of the input image of size nx x ny
 * @param nx data array size
 * @param ny data array size
 * @param L the constant of the screened equation
 *
 * @return data_out  the solution
 */

double *screened_poisson(double *data_out, double *data, size_t nx,
                         size_t ny, double L)
{

	double *data_fft;
	int l;
	int dim, dim4;
	fftw_plan p;
         

	dim=(int) nx* (int) ny;
	dim4=4*dim;
        

     /*allocate memory for the Fourier transform*/

	data_fft=(double*)fftw_malloc(sizeof(double)*dim);
	
		
     /* compute the Fourier transform of the input array*/

    p=fftw_plan_r2r_2d((int)ny,(int)nx, data, data_fft, FFTW_REDFT10,
                       FFTW_REDFT10,FFTW_ESTIMATE);
	fftw_execute(p); 
    fftw_destroy_plan(p);    

	/*solve poisson equation in the Fourier domain*/
	
	screened_poisson_dct(data_fft, nx, ny, L);

	/*compute the inverse Fourier transform*/

	p=fftw_plan_r2r_2d((int)ny, (int)nx, data_fft, data_out,
                       FFTW_REDFT01,FFTW_REDFT01, FFTW_ESTIMATE);
	fftw_execute(p); 
     
	for(l=0;l< dim;l++) data_out[l]/=dim4;
	
	fftw_destroy_plan(p);
	fftw_free(data_fft); 

	return data_out;


}

	
