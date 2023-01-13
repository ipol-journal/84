

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










/** screened_poisson_lib.h
 *
 * @author Catalina Sbert Juan
 
 */

void input_rgb(float *input, double **RR, double **GG,
               double **BB, size_t size) ;

float *rgb_output(double *R, double *G, double *B,
                  float *output, size_t size) ;

double *screened_poisson(double *data_out, double *data,
                         size_t nx, size_t ny, double L);

double *normalize(double *data_out, double *data, size_t dim, float s);