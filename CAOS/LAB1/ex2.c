#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>


void vswap(void* a, void* b, size_t size);
void vcopy_n(void* dst, const void* src, size_t count, size_t elem_size);
bool vminmax(const void* base, size_t count, size_t elem_size,
             int (*comparator)(const void*, const void*),
             const void** out_min, const void** out_max);
int cmp_int32(const void* a, const void* b);
int cmp_double(const void* a, const void* b);

void vswap(void* a, void* b, size_t size){
    if (a == b || size == 0) return;
    unsigned char* pa = (unsigned char*)a;
    unsigned char* pb = (unsigned char*)b;
    // Use malloc to avoid huge VLAs; handles overlap too.
    unsigned char* tmp = (unsigned char*)malloc(size);
    if (!tmp) return; // silently ignore on OOM for this utility
    memcpy(tmp, pa, size);
    memcpy(pa, pb, size);
    memcpy(pb, tmp, size);
    free(tmp);

}

void vcopy_n(void* dst, const void* src, size_t count, size_t elem_size){
    if (!dst || !src || elem_size == 0 || count == 0) return;
    size_t nbytes = count * elem_size;
    const unsigned char* s = (const unsigned char*)src;
    unsigned char* d = (unsigned char*)dst;

    if (d == s || nbytes == 0) return;

    if (d < s || d >= s + nbytes) {
        // forward copy
        for (size_t i = 0; i < nbytes; ++i) d[i] = s[i];
    } else {
        // backward copy (overlap)
        for (size_t i = nbytes; i-- > 0; ) d[i] = s[i];
    }


}
bool vminmax(const void* base, size_t count, size_t elem_size,
             int (*comparator)(const void*, const void*),
             const void** out_min, const void** out_max){
    if (!base || !comparator || !out_min || !out_max || elem_size == 0) return false;
    if (count == 0) { *out_min = *out_max = NULL; return false; }
    const unsigned char* p = (const unsigned char*)base;
    const unsigned char* min= base;
    const unsigned char* max = base;
    for(size_t i = 1; i<count;i++){
            const unsigned char* cur = p + i * elem_size;    
            if(comparator((cur),(max))>0)
                max=cur;

            if(comparator((cur),(min))<0)
                min=cur;
            
    }
    *out_max=(const void*)max;
    *out_min=(const void*)min;
    return true;
}

int cmp_int32(const void* a, const void* b){
    const int32_t aa = *(const int32_t*)a;
    const int32_t bb = *(const int32_t*)b;
    return (aa > bb) - (aa < bb);

}

int cmp_double(const void* a, const void* b){
    const double aa = *(const double*)a;
    const double bb = *(const double*)b;
    return (aa > bb) - (aa < bb);

}

int main(){
    double a=22,b=11111111;
    vswap(&a,&b,sizeof(a));
    printf("%f %f\n",a,b);

   int32_t arr[] = {1,2,3,4,5};
    vcopy_n(&arr[1], &arr[0], 0, sizeof arr[0]); // overlap move right by 1
    printf("vcopy_n: ");
    for (size_t i=0;i<5;i++) printf("%d ", arr[i]); puts("");

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