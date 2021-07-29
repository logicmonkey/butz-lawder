#include <stdio.h>
#include <stdlib.h>
#include "butz-lawder.h"

#define VERTS 8*8*8

int main() {

  Point pt;
  Hcode v = {0};

  int i;

  printf("#define VERTS %d\n", VERTS);
  printf("double p[%d][3] = {\n", VERTS);

  for (i = 0; i < VERTS; i++) {
    v.hcode[0] = i;
    v.hcode[1] = 0;
    v.hcode[2] = 0;
    pt = H_decode(v);
    printf("{%f, %f, %f}", (float)pt.hcode[0], (float)pt.hcode[1], (float)pt.hcode[2]);
    if (i<VERTS-1) printf(",\n");
  }
  printf("};\n");

  return 0;
}
