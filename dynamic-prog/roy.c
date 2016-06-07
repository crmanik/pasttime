#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define min(x,y) ((x > y) ? y : x)

int main() {
    
    long long int num_cops, cost, i = 0, j = 0, final = 0, var1 = 0, var2 = 0, tmp = 0;
    long long int *loc, *prev_final, opt = 0;
    
     
    scanf("%lld", &num_cops);
    scanf("%lld", &cost);
    
    //printf("\nNumber of Cops/Thieves: %d\n", num_cops);
    //printf("Cost for Cops         : %d\n", cost);
    
    loc = malloc(sizeof(long long int) * num_cops);
    
    if (loc == NULL) {
            printf("Mem alloc failed\n");
            return 0;
    }
    
    prev_final = malloc(sizeof(long long int) * num_cops);
    
    if (loc == NULL) {
            printf("Mem alloc failed\n");
            return 0;
    }
    
    
    //printf("Location:");
    for(i = 0; i < num_cops; i++) {
        scanf("%lld", &loc[i]);
        //printf(" %d ", loc[i]);
        
    }
    
    //printf("\n");
    
    for(i = 0; i < num_cops; i++) {
        for(j = 0; j < num_cops; j++) {
            tmp = loc[j]- loc[i];
            var2 =  tmp * tmp + (i+1) * cost;
            if (i == 0 || i > j){
		if (j > i) {
                  final = var2;
		} else {
		  final = (i+1) * cost;
		}
            }
            else {
                var1 = prev_final[j-1] + cost;
                final = min(var1, var2);
		
                
            }
            prev_final[j] = final;
	   printf(" %lld ", final);
                                             
        }
	if (!opt || opt > final) {
		opt = final;
	}
	printf("\n");
                    
    }
    
    printf("%lld", opt);
     
    
    return 0;
}

