#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"
#include "vector.h"

float **WARN_UNUSED   Mat_init(size_t size);
void                  Mat_free(float **matrix);
void                  Mat_print(float **matrix);
float_t WARN_UNUSED   Mat_det(float_t **matrix);
float_t **WARN_UNUSED Mat_adjugate(float_t **matrix);
float_t **WARN_UNUSED Mat_inverse(float_t **matrix);

//
// =============== { Operator Overloading }
//
Vector3 WARN_UNUSED Mat3_vect_mult(float **matrix, Vector3 vect);

#define Mat4_mult(matrix, k)                \
   _Generic(k,                              \
      Vector4: Mat4_mult_vect,              \
      float_t * *: Mat4_mult_mat,           \
      default: Mat4_mult_scalar)(matrix, k)
float **WARN_UNUSED   Mat4_mult_scalar(float **matrix, float_t k);
float_t **WARN_UNUSED Mat4_mult_mat(float_t **matrix, float_t **other);
Vector4 WARN_UNUSED   Mat4_mult_vect(float_t **matrix, Vector4 vector);

float_t **WARN_UNUSED Mat_get_model(Vector3  translation,
                                    double_t rx,
                                    double_t ry,
                                    double_t rz);
float_t **WARN_UNUSED Mat_get_projection(float_t l,
                                         float_t r,
                                         float_t t,
                                         float_t b,
                                         float_t n,
                                         float_t f);
float_t **WARN_UNUSED Mat_get_viewport(float_t sx,
                                       float_t sy,
                                       float_t ws,
                                       float_t hs,
                                       float_t ns,
                                       float_t fs);

#endif
