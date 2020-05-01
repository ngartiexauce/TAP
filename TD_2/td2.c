int first_flip(V,n,P){
	if(n<4){
		return 0;

	}
	double d_1,d_2;
	for(int i=0; i<n;i++){
		for(int j=2;j<n-1;j++){
			d_1 = distance(i,j+1,P,V);
			d_2 = dist(V[P[i]],V[P[j]],P,V)+distance(i+1,j,P,V)+dist(V[P[i+1]],V[P[j+1]],P,V);
			if(d_1 > d_2){
				reverse(P,i,j);
				reverse(V,i,j);
				return d_2-d_1;
			}
		}
	}
	return 0;
	/* On veut flip v_i-v_i+1 et v_j-v_j+1*/

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

double tsp_flip(point * V,int n,int *P){
	for(int i=0; i<n; i++){
		P[i] = i;
	}
	while(first_flip(V,n,P) !=0){
		/*  Yeah Yeah */
	}
	return value(V,n,P);
}
double tsp_greedy(point *V,int n,int * P){
	int *Q[n-1];
	for(int i=0; i<n-1;i++){
		Q[i]=i+1;
	}
	P[0] = 0;
	for( int i=0; i<n-1; i++){
		int i_min;
		double d_min = DBL_MAX;
		for(int j=0;j< n;j++ ){
			if(Q[j] >0){
				double d = dist(V[P[i]], V[Q[j]])				
				if(d<min){
					i_min =j;
					Q[j] = -1;
				}
			}
		}
		P[i+1] = i_min;
	}

}