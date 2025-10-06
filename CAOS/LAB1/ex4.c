#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

int strsplit(const char* s, char delim, char*** out_tokens, size_t* out_count);

int strsplit(const char* s, char delim, char*** out_tokens, size_t* out_count){
    if ( *s == NULL)
        return -1;
    size_t j;
    size_t *i = malloc(sizeof(size_t)*10); 
    for(j= 0; *(s+j) != '\0'; j++){
        if(*(s+j) == delim){
            *(i+*(out_count)*sizeof(size_t)) = j;
            *(out_count)=*(out_count)+1;
        }
    }
    *out_tokens = malloc(*out_count);
    int start = 0, space;
    for(size_t N=0;N<*out_count;N++){
        space = *(i+N*sizeof(int)) - start;
        *(out_tokens+N) = malloc((space));
        memcpy(*(out_tokens),(s+start),space);
        *out_tokens += space+1;
        start = *(i+N)+1;
    }
    free(i);
    return 0;
}

int main(){
    char **out_tokens;
    size_t out_count = 0;
    if(strsplit("::a::",':',&out_tokens,&out_count) == 0 ){
        printf("%zu",out_count);
        for(int i=0;i<out_count;i++){
            printf("\n%s\n",*(out_tokens+i));
            free(*(out_tokens+i));
        }
        free(out_tokens);
    }
    else
        printf("failure.");
}