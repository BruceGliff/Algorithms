#include <stdio.h>
#include <math.h>

typedef struct Point {
 float x;
 float y;
} Point;

typedef Point Vector;

typedef struct Triangle {
  Point points[3];
} Triangle;


void printPoint(Point const *P) {
  printf("x: %f; y:%f\n", P->x, P->y);
}

void printTriangle(Triangle const *T) {

  printf("Triangle:\n");
  for (int i = 0; i != 3; ++i) {
    printf("  ");
    printPoint(&T->points[i]);
  }
}

float cross(Vector const *V0, Vector const *V1) {
  return V0->x * V1->y - V0->y * V1->x;
}

float dot(Vector const *V0, Vector const *V1) {
  return V0->x * V1->x + V0->y * V1->y;
}

float len(Vector const *V0) {
  return sqrtf(dot(V0, V0));
}

int resolvePoint(Triangle const *T, Point const *P) {

  Vector const V0 = { T->points[1].x - T->points[0].x, T->points[1].y - T->points[0].y };
  Vector const V1 = { T->points[2].x - T->points[0].x, T->points[2].y - T->points[0].y };

  Vector const V2 = { P->x - T->points[0].x, P->y - T->points[0].y };

  float const det = cross(&V0, &V1);

  float const det1 = cross(&V0, &V2);
  float const det2 = cross(&V2, &V1);

  float const det3 = det - det1 - det2;

  return (det2 > 0 && det1 > 0 && det3 > 0) || (det2 < 0 && det1 < 0 && det3 < 0);
}

int main() {

  Triangle T;
  for (int i = 0; i != 3; ++i)
    scanf("%f %f", &T.points[i].x, &T.points[i].y);

  int N;
  scanf("%d", &N);

  Point P;
  for (int i = 0; i != N; ++i) {
    scanf("%f %f", &P.x, &P.y);
    if(resolvePoint(&T, &P))
      printf("%d\n", i+1);
  }

  return 0;
}