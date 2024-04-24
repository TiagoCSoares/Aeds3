#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    
    srand((unsigned)time(NULL));

    for(int i = 0; i < 100000; i++) {
        int numVertices = (rand() % 50)+25;
        //printf("%d\n", numVertices);
        if(numVertices < 25 || numVertices > 75)
            printf("errou\n");
    }
}