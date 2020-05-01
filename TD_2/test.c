#include <stdio.h>
#include "tools.h"
#define SWAP(x, y, z)  (z) = (x), (x) = (y), (y) = (z)
void MaxPermutation(int *P, int n, int k) {
  for(int i = 0; i <(n-k)/2 ; i++){
    int tmp = P[i+k];
    P[i+k] = P[n-i-1];
    P[n-i-1] = tmp;
  }
  return;
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


bool NextPermutation(int *P, int n) {
  /*
    Génère la prochaine permutation P de taille n dans l'ordre
    lexicographique. On renvoie true si la prochaine permutation a pu
    être déterminée et false si P était la dernière permutation (et
    alors P n'est pas modifiée). Il n'est pas nécessaire que les
    valeurs de P soit dans [0,n[.

    On se base sur l'algorithme classique qui est:

    1. Trouver le plus grand index i tel que P[i] < P[i+1].
       S'il n'existe pas, la dernière permutation est atteinte.
    2. Trouver le plus grand indice j tel que P[i] < P[j].
    3. Echanger P[i] avec P[j].
    4. Renverser la suite de P[i+1] jusqu'au dernier élément.

  */
  int i=-1, j, m=n-1, t;

  /* étape 1: cherche i le plus grand tq P[i]<P[i+1] */
  for (j = 0; j < m; j++)
    if (P[j] < P[j + 1]) i = j; /* on a trouvé un i tq P[i]<P[i+1] */
  if (i < 0) return false; /* le plus grand i tq P[i]<[i+1] n'existe pas */

  /* étape 2: cherche j le plus grand tq P[i]<P[j] */
  for (j = i+1; (j<n) && (P[i]<P[j]) ; j++);
  j--;

  /* étape 3: échange P[i] et P[j] */
  SWAP(P[i], P[j], t);

  /* étape 4: renverse P[i+1]...P[n-1] */
  for (++i; i < m; i++, m--)
    SWAP(P[i], P[m], t);

  return true;
}
 int main()
 {
 	int  P[10] = {0,1,2,3,4,5,6,7,8,9};
    for(unsigned int i = 0; i<10;i++){
    printf("%d ",P[i] );  
  }
 	printf("\nreverse:\n");
 	reverse(P, 2,5 );
 	for(unsigned int i = 0; i<10;i++){
 		printf("%d ",P[i] );	
 	}
 	/*printf("\n");
 	for(int i =1 ; i<3; i++){
	 	printf("NextPermutation %d:\n",i);
	 	bool t = NextPermutation(Q,6);
	  	for(unsigned int j = 0; j<6;j++){
	 		printf("%d ",Q[j] );	
	 	}
	 	printf("\n");

 	}*/

 	return 0;
 }

