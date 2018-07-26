#ifndef DILATED_CONVOLUTIONAL_LAYER_H
#define DILATED_CONVOLUTIONAL_LAYER_H

#include "cuda.h"
#include "image.h"
#include "activations.h"
#include "layer.h"
#include "network.h"

typedef layer dilated_convolutional_layer;

#ifdef GPU
void forward_convolutional_layer_gpu(dilated_convolutional_layer layer, network net);
void backward_convolutional_layer_gpu(dilated_convolutional_layer layer, network net);
void update_convolutional_layer_gpu(dilated_convolutional_layer layer, update_args a);

void push_convolutional_layer(dilated_convolutional_layer layer);
void pull_convolutional_layer(dilated_convolutional_layer layer);

void add_bias_gpu(float *output, float *biases, int batch, int n, int size);
void backward_bias_gpu(float *bias_updates, float *delta, int batch, int n, int size);
void adam_update_gpu(float *w, float *d, float *m, float *v, float B1, float B2, float eps, float decay, float rate, int n, int batch, int t);
#ifdef CUDNN
void cudnn_convolutional_setup(layer *l);
#endif
#endif

dilated_convolutional_layer make_dilated_conv_layer(int batch, int h, int w, int c, int n, int groups, int size, int stride, int padding, ACTIVATION activation, int batch_normalize, int binary, int xnor, int adam);
void resize_dilated_conv_layer(dilated_convolutional_layer *layer, int w, int h);
void forward_dilated_conv_layer(const dilated_convolutional_layer layer, network net);
void update_dilated_conv_layer(dilated_convolutional_layer layer, update_args a);
image *visualize_dilated_conv_layer(dilated_convolutional_layer layer, char *window, image *prev_weights);
void binarize_weights(float *weights, int n, int size, float *binary);
void swap_binary(dilated_convolutional_layer *l);
void binarize_weights2(float *weights, int n, int size, char *binary, float *scales);

void backward_dilated_conv_layer(dilated_convolutional_layer layer, network net);

void add_bias(float *output, float *biases, int batch, int n, int size);
void backward_bias(float *bias_updates, float *delta, int batch, int n, int size);

image get_dilated_conv_image(dilated_convolutional_layer *layer);
image get_dilated_conv_delta(dilated_convolutional_layer *layer);
image get_dilated_conv_weight(dilated_convolutional_layer *layer, int i);

int dilated_conv_out_height(dilated_convolutional_layer layer);
int dilated_conv_out_width(dilated_convolutional_layer layer);

#endif

