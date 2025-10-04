#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>


void vswap(void* a, void* b, size_t size);
void vcopy_n(void* dst, const void* src, size_t count, size_t elem_size);
bool vminmax(const void* base, size_t count, size_t elem_size,
             int (*comparator)(const void*, const void*),
             const void** out_min, const void** out_max);
int cmp_int32(const void* a, const void* b);
int cmp_double(const void* a, const void* b);

void vswap(void* a, void* b, size_t size){
    uint8_t tmp;
    for(size_t i=0 ; i<size;i++){
        tmp = *(uint8_t*)(a+i);
        *(uint8_t*)(a+i) = *(uint8_t*)(b+i);
        *(uint8_t*)(b+i) = tmp;
    }
}

void vcopy_n(void* dst, const void* src, size_t count, size_t elem_size){
    uint8_t tmp;
    for(size_t i = 0; i<count;i++){
        for(size_t j = 0; j<elem_size; j++){
            *(uint8_t*)dst = *(uint8_t*)(src+j);
            dst++;
        }
    }
}
bool vminmax(const void* base, size_t count, size_t elem_size,
             int (*comparator)(const void*, const void*),
             const void** out_min, const void** out_max){
    void *min = base;
    void *max = base;
    base +=elem_size;
    for(size_t i = 1; i<count;i++){    
        int done_min=0,done_max=0;
        printf("\nbase: %f, min:%f, max:%f ",*(double*)(min),*(double*)(max),*(double*)(base));
            if(comparator((base),(max))>0)
                max=base;

            if(comparator((base),(min))<0)
                min=base;
            
        base +=elem_size;
    }
    printf("\nbase: %f, min:%f, max:%f ",*(double*)(min),*(double*)(max),*(double*)(base));
    *out_max=max;
    *out_min=min;
}

int cmp_int32(const void* a, const void* b){
    int n = sizeof(int32_t);
    for(size_t i = n-1; i>=0; i--){
        if(*(uint8_t*) (a+i) == *(uint8_t*) (b+i))
            continue;
        else
            return *(uint8_t*) (a+i) - *(uint8_t*) (b+i);
    }
    return 0;
}

int cmp_double(const void* a, const void* b){
    int n = sizeof(double);
    for(size_t i = n-1; i>=0; i--){
        if(*(uint8_t*) (a+i) == *(uint8_t*) (b+i))
            continue;
        else
            return *(uint8_t*) (a+i) - *(uint8_t*) (b+i);
    }
    return 0;
}

int main(){
    double a=22,b=11111111;
    vswap(&a,&b,sizeof(a));
    printf("%f %f\n",a,b);

    int32_t vet_int[4] = {0,0,0,0};
    int64_t t = 16;
    vcopy_n(vet_int,&t,3,sizeof(t));
    for(int i=0;i<4;i++)
        printf("%"PRId32",",vet_int[i]);
    /*
    int32_t *min,*max;
    int32_t vet2[4] = {45,5,50,1};
    vminmax(vet2,4,sizeof(int32_t),cmp_int32,&min,&max);
    printf("\nmin:%d max:%d",*min,*max);
    */
    double *min,*max;
    double vet2[4] = {452,5,50,11};
    printf("\nSize: %d\n",sizeof(double));
    vminmax(vet2,4,sizeof(double),cmp_double,&min,&max);
    printf("\nmin:%f max:%f",*min,*max);
    return 0;
}