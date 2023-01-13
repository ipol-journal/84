/*
 *  auxiliary_lib.h
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

#ifdef __cplusplus
extern "C" {
#endif

	void input_rgb(float *input, double **RR, double **GG,
                   double **BB, size_t size);
	
	float *rgb_output(double *R, double *G, double *B,
                      float *output, size_t size);
	
	double *int_double(double *data, unsigned char *data_in,
                       size_t dim, int channel);
	
	unsigned char *double_int(unsigned char *data, double *data_in,
                              size_t dim, int channel);
	
	double *gray_intensity(double *gray, double *data_in, size_t dim);
	
	double *color(double *data_out, double *data, double *gray,
                  double *gray1, size_t dim);
	
	double *simplest_color_balance(double *data_out, double *data,
                                   size_t dim, float s);
	
	float *simplest_color_balance_f(float *data_out, float *data,
                                    size_t dim, float s);
	
	float mean_f(float *data, int dim);


#ifdef __cplusplus
}
#endif