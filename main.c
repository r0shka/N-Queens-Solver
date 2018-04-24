#include "tree.h"

int main(int argc, char **argv){
	
	/**USAGE**/
	if(argc!=3){
		puts("USAGE: ./ai S N");
		puts("S: 1 - Eight queens puzzle FC, 2 - Eight queens puzzle BJ");
		puts("N : number of variables");
		puts("Example : ./ai 1 8");
		return 0;
	}

	int sizeVar = 1 + strtol(argv[2], NULL, 10);	//add 1 as we start at 1, not 0
	if(sizeVar < 4){			
		puts("No solutions for less than 4 queens");
		return 0;
	}

	clock_t end;
	clock_t begin;
	
	int q, r;
		int i, j, m, n, k;
	int var[sizeVar];
	int val[sizeVar];
	int dom[sizeVar][sizeVar];
	int superPosition[sizeVar];
	int * con[sizeVar][sizeVar];
	for(i=1; i < sizeVar; i++)
		for(j=1; j < sizeVar; j++){
			dom[i][j]=1;
			con[i][j] = (int *)malloc(sizeVar * sizeVar * sizeof(int) );
	}

		
	/**init array**/
	for(i = 1; i < sizeVar-1; i++)
		for(j = i+1; j < sizeVar; j++)
			for(m = 1; m < sizeVar; m++)
				for(n = 1; n < sizeVar; n++)
					*(con[i][j]+m*sizeVar+n) = 1;

	/**generate con (Toepliz Matrix with step k) **/
	for(i = 1; i < sizeVar-1; i++){
		k=0;
		for(j = i+1; j < sizeVar; j++){
			k++;
			for(m = 1; m < sizeVar; m++){
				for(n = 1; n < sizeVar; n++){
					if(m==n){
						*(con[i][j]+m*sizeVar+n) = 0;
						if(n + k < sizeVar)
							*(con[i][j]+m*sizeVar+(n + k )) = 0;
						if(n - k > 0)
							*(con[i][j]+m*sizeVar+(n - k )) = 0;
					}		
				}
			}
		}
	}
	/**end generate con**/


	/**init var,  val & superposition**/
	for(i=1; i < sizeVar; i++){
		var[i]=0;
		val[i]=i;
		superPosition[i]=1;
	}

	/**N queens puzzle FC**/
	if(strtol(argv[1], NULL, 10) == 1){
		int nbNodes=0;
		q=1;
		r=1;	//row
		var[q]=val[r];
		Liste *tree = create(var[q++], val[r], 0);
		puts("Calculating...");

		begin = clock();			// start timing algorithm

		/** FORWARD CHECKING **/

		while(1){
			/**If a solution is found**/
			if(q>=sizeVar){
				printf("A solution is found!\n");
				end = clock();			// stop timing algorithm
				double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;				
				printf("Time: %f s\n", time_spent);
				printf("Nodes: %d\n", nbNodes);
				showSolution(tree, sizeVar);
				return 0;
			}
			
			/**create superposition**/
			for(i = 1; i < q; i++){			// C = Numero tetraedrique de sizeVar * sizeVar; Pour 8 = 120*8 = 960
					for(n = 1; n < sizeVar; n++){
						if(  *(con[i][q]+ var[i] *sizeVar+n) == 1 && superPosition[n]  == 1 )
							superPosition[n] = 1;
						else
							superPosition[n] = 0;
					}
			}
			/**end create superposition**/
			
			/**placing queens in all possible locations**/
			for(i=1; i< sizeVar; i++){
				if(superPosition[i]==1){
					var[q]=val[i];
					addElem(tree, q, val[i], 0);
					nbNodes++;
				}
			}

			/**entering the last created node**/
			tree->premier->visited = 1;

			/**if no available nodes, Q hasn't changed, then another value for Q**/
			if(tree->premier->var == q-1){
				while(tree->premier->visited==1){
					var[--q]=0;
					removeElem(tree);
					if(tree->premier->var == q ){
						var[q] = tree->premier->val;
					}
				}
			}
			tree->premier->visited = 1;

			/**If we returned all the way to the first node Q1**/
			if(tree->premier->var == 1){
				r++;
				q=1;
				removeElem(tree);
				addElem(tree, 1, r, 0);
				var[q]=r;
			}

			q++;	//moving to the next queen

		/**reset superposition**/
		for(n = 1; n < sizeVar; n++)
			superPosition[n]=1;
		/**end reset super position**/

		}
		free(tree);
		/** END OF FORWARD CHECKING **/

		/**FREE MEMORY**/
		for(i=1; i < sizeVar; i++)
			for(j=1; j < sizeVar; j++)
				free(con[i][j]);

	}
	
	/**N queens puzzle BJ**/

	if(strtol(argv[1], NULL, 10) == 2){
		int nbNodes=0;
		q=1;
		r=1;	//row
		var[q]=val[r];
		Liste *tree = create(var[q++], val[r], 0);
		puts("Calculating...");

		begin = clock();			// start timing algorithm

		/** BACK JUMPING **/

		while(1){
			/**If a solution is found**/
			if(q>=sizeVar){
				printf("A solution is found!\n");
				end = clock();			// stop timing algorithm
				double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;				
				printf("Time: %f s\n", time_spent);
				printf("Nodes: %d\n", nbNodes);
				showSolution(tree, sizeVar);
				return 0;
			}
			
			/**create superposition**/
			for(i = 1; i < q; i++){			// C = Numero tetraedrique de sizeVar * sizeVar; Pour 8 = 120*8 = 960
					for(n = 1; n < sizeVar; n++){
						if(  *(con[i][q]+ var[i] *sizeVar+n) == 1 && superPosition[n]  == 1 )
							superPosition[n] = 1;
						else
							superPosition[n] = 0;
					}
			}
			/**end create superposition**/
			
			/**placing queens in all possible locations**/
			for(i=1; i< sizeVar; i++){
				addElem(tree, q, val[i], 0);
				nbNodes++;
				if(superPosition[i]==0){
					removeElem(tree);
				}
				else
					var[q]=val[i];
			}

			/**entering the last created node**/
			tree->premier->visited = 1;

			/**if no available nodes, Q hasn't changed, then another value for Q**/
			if(tree->premier->var == q-1){
				while(tree->premier->visited==1){
					var[--q]=0;
					removeElem(tree);
					if(tree->premier->var == q ){
						var[q] = tree->premier->val;
					}
				}
			}
			tree->premier->visited = 1;

			/**If we returned all the way to the first node Q1**/
			if(tree->premier->var == 1){
				r++;
				q=1;
				removeElem(tree);
				addElem(tree, 1, r, 0);
				var[q]=r;
			}

			q++;	//moving to the next queen

		/**reset superposition**/
		for(n = 1; n < sizeVar; n++)
			superPosition[n]=1;
		/**end reset super position**/

		}
		free(tree);

		/**FREE MEMORY**/
		for(i=1; i < sizeVar; i++)
			for(j=1; j < sizeVar; j++)
				free(con[i][j]);
	}

	

	else{
		puts("USAGE: ./ai S N");
		puts("S: 1 - Eight queens puzzle FC, 2 - Eight queens puzzle BJ");
		puts("N : number of variables");
		puts("Example : ./ai 1 8");
		return 0;
	}
}
