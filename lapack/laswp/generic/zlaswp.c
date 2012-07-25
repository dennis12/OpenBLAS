#include "common.h"

int CNAME(BLASLONG n, BLASLONG k1, BLASLONG k2, FLOAT dummy1, FLOAT dummy4,
          FLOAT *a, BLASLONG lda, FLOAT *dummy2, BLASLONG dumy3, blasint *ipiv, 
	  BLASLONG incx)
{
  BLASLONG i, ip, j, k, ix, ix0, i1, i2, inc, nb, n0;
  nb = 16;
  n0 = (n / nb) * nb; 

  if (incx > 0){
    ix0 = k1 - 1;
    i1 = k1 - 1;
    i2 = k2 - 1;
    inc = +1;
  }
  else if (incx < 0){
    ix0 = (k2-1)*(-incx);
    i1 = k2 - 1;
    i2 = k1 - 1;
    inc = -1;
  }
  else return 0;


  if (n0 != 0){
    for(j=0; j<n0; j+=nb){

      for(i=i1, ix=ix0; (incx>0)? i<=i2: i>=i2; i+=inc, ix+=incx){
        ip = ipiv[ix] - 1;

        if (ip != i){
          for(k=j; k<j+nb; k++){
            FLOAT tmp0 = a[2*i+0 + 2*lda*k];
            FLOAT tmp1 = a[2*i+1 + 2*lda*k];
            FLOAT tmp2 = a[2*ip+0 + 2*lda*k];
            FLOAT tmp3 = a[2*ip+1 + 2*lda*k];
            a[2*i+0 + 2*lda*k] = tmp2;
            a[2*i+1 + 2*lda*k] = tmp3;
            a[2*ip+0 + 2*lda*k] = tmp0;
            a[2*ip+1 + 2*lda*k] = tmp1;
          }
        }
      }
    }
  }

  if (n0 != n){
    for(i=i1, ix=ix0; (incx>0)? i<=i2: i>=i2; i+=inc, ix+=incx){
      ip = ipiv[ix] - 1;

      if (ip != i){
        for(k=n0; k<n; k++){
          FLOAT tmp0 = a[2*i+0 + 2*lda*k];
          FLOAT tmp1 = a[2*i+1 + 2*lda*k];
          FLOAT tmp2 = a[2*ip+0 + 2*lda*k];
          FLOAT tmp3 = a[2*ip+1 + 2*lda*k];
          a[2*i+0 + 2*lda*k] = tmp2;
          a[2*i+1 + 2*lda*k] = tmp3;
          a[2*ip+0 + 2*lda*k] = tmp0;
          a[2*ip+1 + 2*lda*k] = tmp1;
        }
      }
    }
  }

  return 0;
}
