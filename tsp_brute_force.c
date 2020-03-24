//
//  TSP - BRUTE-FORCE
//
// -> la structure "point" est définie dans tools.h
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

  double l = 0;
  double v;

  for(int i = 0; i<n-1; i++){
    if(D[P[i]][P[i+1]] > 0){
      v =D[P[i]][P[i+1]];
    }else{
      v= dist(V[P[i]], V[P[i+1]]);
      D[P[i]][P[i+1]] = v;
      D[P[i+1]][P[i]] = v;
    }
    l += v;
  }
  return l+dist(V[P[n-1]], V[P[0]]);
}

double tsp_brute_force(point *V, int n, int *Q) {
  double w = DBL_MAX;
  int P[n];
  for(int i = 0; i<n ; i++){
	   P[i] = i;
  }
  double s;
  do{

	   s = value(V,n,P);
	   if(w>s){
         w = s ;
		     for(int i = 0; i<n ; i++){
			        Q[i] = P[i];
  	     }
  drawTour(V, n, Q);
	}
  }while(NextPermutation(P,n) && running);
  return w;
}

void MaxPermutation(int *P, int n, int k) {
  for(int i = 0; i <(n-k)/2 ; i++){
    int tmp = P[i+k];
    P[i+k] = P[n-i-1];
    P[n-i-1] = tmp;
  }
  return;
}




static double value_opt(point *V, int n, int *P, double w) {
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

  double l = 0;
  double v;

  for(int i = 0; i<n-1; i++){
    if(D[P[i]][P[i+1]] > 0){
      v =D[P[i]][P[i+1]];
    }else{
      v= dist(V[P[i]], V[P[i+1]]);
      D[P[i]][P[i+1]] = v;
      D[P[i+1]][P[i]] = v;
    }

    l += v;
    if(l+dist(V[P[i+1]], V[P[0]]) > w){
      return -(i+2);
    }
  }
  return l+dist(V[P[n-1]], V[P[0]]);
}








double tsp_brute_force_opt(point *V, int n, int *Q) {
  double w = DBL_MAX;
  int P[n];
  for(int i = 0; i<n ; i++){
     P[i] = i;
  }
  double s;
  do{
     s = value_opt(V,n,P,w);
     if(s < 0){
         MaxPermutation(P,n-1,-s);
     }else if(w>s){
           w = s ;
           for(int i = 0; i<n ; i++){
                Q[i] = P[i];
           }
     }
  }
  while(NextPermutation(P,n-1) && running); 
  return w;
}
