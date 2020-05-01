//
//  TSP - HEURISTIQUES
//
#include <math.h>

double dist(point A, point B) {
  double x = (A.x - B.x);
  double y = (A.y - B.y);
  return hypot(x,y);
}

static double value(point *V, int n, int *P) {
  static double **D=NULL;
  if(D==NULL){
      D=malloc(n*sizeof(double*));
      for(int i=0; i<n; i++){
        D[i] = malloc(n*sizeof(double));
        for( int j =0; j<n;j++){
          D[i][j] = -1;
        }
      }
  }
void reverse(int *T, int p, int q) {
  // renverse la partie T[p]...T[q] du tableau T avec p<q
  // si T={0,1,2,3,4,5,6} et p=2 et q=5, alors le nouveau
  // tableau sera {0,1, 5,4,3,2, 6}
  for(int i=0;i<(q-p+1)/2;i++){
    int tmp = T[i+p];
    T[i+p] = T[q-i];
    T[q-i] = tmp;
  }
  return;
}
double distance(int a, int b,int *P,point *V){
  double d;
  if( a < b){
    for(int i=a; i<b;i++){
      d+=dist(V[P[i]],V[P[i+1]]);
    }
  }
  return d;
}

double first_flip(point *V, int n, int *P) {
  // renvoie le gain>0 du premier flip réalisable, tout en réalisant
  // le flip, et 0 s'il n'y en a pas.
  if(n<4){
    return 0;

  }
  double d_1,d_2;
  for(int i=0; i<n;i++){
    for(int j=2;j<n-1;j++){
      d_1 = distance(i,j+1,P,V);
      d_2 = dist(V[P[i]],V[P[j]])+distance(i+1,j,P,V)+dist(V[P[i+1]],V[P[j+1]]);
      if(d_1 > d_2){
        reverse(P,i,j);
        return d_2-d_1;
      }
    }
  }
  return 0;
  /* On veut flip v_i-v_i+1 et v_j-v_j+1*/

}






double tsp_flip(point *V, int n, int *P) {
  // la fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i. Pensez aussi faire
  // drawTour() pour visualiser chaque flip.
  for(int i=0; i<n; i++){
    P[i] = i;
  }
  while(first_flip(V,n,P) !=0){
    drawTour(V,n,P);
    /*  Yeah Yeah */
  }
  return value(V,n,P);
}


double tsp_greedy(point *V, int n, int *P) {
  // la fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i.
  int Q[n-1];
  for(int i=0; i<n-1;i++){
    Q[i]=i+1;
  }
  P[0] = 0;
  for( int i=0; i<n-1; i++){
    int i_min;
    double d_min = DBL_MAX;
    for(int j=0;j< n;j++ ){
      if(Q[j] >0){
        double d = dist(V[P[i]], V[Q[j]])   ;    
        if(d<d_min){
          i_min =j;
          d_min = d;
          Q[j] = -1;
        }
      }
    }
    P[i+1] = i_min;
  }
}
