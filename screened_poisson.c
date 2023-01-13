/*
 *
 * Copyright 2013 IPOL Image Processing On Line http://www.ipol.im/
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
 */




/**
 * @mainpage Screened Poisson equation for image enhancement
 *
 * README.txt:
 * @verbinclude README.txt
 */

/**
 * @file screened_poisson.c
 * @brief screened poisson equation
 *
 * Given an image  f the algorithm compute a new image u  
 * with minimize the functional
 *
 *  @f$ \int |\nabla u-\nabla f|^2+\lambda \int (u-\bar{f})^2  \f$
 *
 * @author Catalina Sbert <catalina.sbert@uib.es>
 * @author Ana Belén Petro <anabelen.petro@uib.es>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io_png.h"
#include "screened_lib.h"
#include "auxiliary_lib.h"

int main(int argc, char *const *argv)
{

	double L;    
	size_t nx, ny, nc,dim;
	float *in, *out;
	double *R, *G, *B;
	double *Rout, *Gout, *Bout;
	int l;
	float s;
	
	
    /* wrong number of parameters : simple help info */
	
    if ( argc < 5 )
    {
    
    fprintf(stderr, "usage: %s L in.png out_bb.png out_s.png s\n", argv[0]);
    fprintf(stderr, "L: [0, 2] tradeoff parameter\n");
    fprintf(stderr, "s: [0,100] simplest color balance (default 0.1)\n");
    return EXIT_FAILURE;
    }
     L = atof(argv[1]);
    if (0. > L || 2 < L)
    {
        fprintf(stderr, "the  parameter L must be [0, 2]\n");
        return EXIT_FAILURE;
    }
	
	if(argc > 5) s=atof(argv[5]);
	else s=0.1;

    /* read the PNG image into data */
    if (NULL == (in = io_png_read_f32(argv[2], &nx, &ny, &nc)))
    {
        fprintf(stderr, "the image could not be properly read\n");
        return EXIT_FAILURE;
    }
    
	
    dim=nx*ny;
	
	out = (float *) malloc(nc * nx * ny * sizeof(float));
	 
    /* allocate data_out  */
	
	Rout=(double*)malloc(dim*sizeof(double));
   
	if(3 <= nc){	
		
       Gout=(double*)malloc(dim*sizeof(double));
       Bout=(double*)malloc(dim*sizeof(double));
		/* transform input into a double array*/
	
		input_rgb(in, &R, &G, &B, dim);
	
		/* compute the simplest color balance of the input image 
         with a s% of saturation*/
	
		simplest_color_balance(Rout, R, dim, s);
		simplest_color_balance(Gout, G, dim, s);
		simplest_color_balance(Bout, B, dim, s);
	
	
		/* write the output of the simplest color balance result*/  
	
		rgb_output(Rout, Gout, Bout, out, dim);
		io_png_write_f32(argv[3], out, nx, ny, nc);
	
	
	
   /*solve the screened poisson equation for each channel*/
		screened_poisson(Rout, Rout, nx,ny, L);
		simplest_color_balance(Rout, Rout, dim, s);
		screened_poisson(Gout, Gout, nx,ny, L);
		simplest_color_balance(Gout, Gout, dim,s);
		screened_poisson(Bout, Bout, nx,ny, L);
		simplest_color_balance(Bout,Bout,dim,s);


		/* write the output*/  
	
		rgb_output(Rout, Gout, Bout, out, dim);
		io_png_write_f32(argv[4], out, nx, ny, nc);
		
		free(Rout); free(Gout); free(Bout); free(R);
        free(G); free(B);
	}
	 
	else{ /* for gray images*/
				
		
		R=(double*)malloc(dim*sizeof(double));
		
		for(l=0;l<(int)dim; l++) R[l]=(double) in[l];
		
		simplest_color_balance(Rout, R, dim, s);
		
		for(l=0;l<(int)dim; l++) out[l]=(float) (Rout[l]);
		
		io_png_write_f32(argv[3], out, nx, ny, nc);
		
		screened_poisson(Rout, Rout, nx,ny, L);
		simplest_color_balance(Rout, Rout,dim,s);
		for(l=0;l<(int)dim; l++) out[l]=(float) (Rout[l]);
		
		io_png_write_f32(argv[4], out, nx, ny, nc);
		free(R); free(Rout);
	}
	
	free(in); free(out);

	return EXIT_SUCCESS;

} 
