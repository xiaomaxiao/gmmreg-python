#define SQR(X) ((X) * (X))

#include <math.h>

/* PLEASE READ THIS HEADER, IMPORTANT INFORMATION INSIDE */
#include "memory_layout_note.h"

#ifdef WIN32
__declspec(dllexport)
#endif
    double GaussTransform(const double* A, const double* B, int m, int n,
                          int dim, double scale, double* grad) {
  int i, j, d;
  int id, jd;
  double dist_ij, cross_term = 0;
  double cost_ij;
  for (i = 0; i < m * dim; ++i) grad[i] = 0;
  for (i = 0; i < m; ++i) {
    for (j = 0; j < n; ++j) {
      dist_ij = 0;
      for (d = 0; d < dim; ++d) {
        id = i * dim + d;
        jd = j * dim + d;
        dist_ij = dist_ij + SQR(A[id] - B[jd]);
      }
      cost_ij = exp(-dist_ij / SQR(scale));
      for (d = 0; d < dim; ++d) {
        id = i * dim + d;
        jd = j * dim + d;
        grad[id] += -cost_ij * 2 * (A[id] - B[jd]);
      }
      cross_term += cost_ij;
    }
  }
  for (i = 0; i < m * dim; ++i) {
    grad[i] /= (m * n * SQR(scale));
  }
  return cross_term / (m * n);
}
