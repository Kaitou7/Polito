#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>


typedef bool (*stage_fn)(int32_t* x, void* user);
bool add(int32_t* x, void* user);
bool run_pipeline(int32_t* x, stage_fn const* stages, void* const* users, size_t n_stages);

bool add(int32_t* x, void* user){
    *x += *(int32_t*)user;
    return true;
}
bool isEven(int32_t* x, void* user){
    if(*x%2 == 0){
        *x = *x/2;
        return true;
    }
    return false;
}
bool clamp(int32_t* x, void* user){
    size_t step = sizeof(int32_t);
    int32_t ol = *(int32_t*)(user+step);
    int32_t hi = *(int32_t*)(user+2*step);
    if (*x >ol && *x < hi)
        return false;
    if (*x <ol)
        *x = ol;
    if (*x >hi)
        *x = hi;
    return true;
}
bool substract(int32_t* x, void* user){
    size_t step = sizeof(int32_t);
    *x -=*(int32_t*)(user+step*3);
    return true; 
}

bool run_pipeline(int32_t* x, stage_fn const* stages, void* const* users, size_t n_stages){
    for(size_t i = 0;i<n_stages; i++){
        if(!stages[i](x,users))
            return false;
        
    }
    return true;
}


int main(){
    int32_t x = 0;
    int32_t values [5] = {5,10,20,15,2};
    int32_t users[5]={6,10,20,15,2};
    stage_fn func[5]={add,isEven,clamp,substract,add};
    if(!run_pipeline(&x,func,users,5))
        printf("Pipeline stopped, error in pipeline!");
    else
        printf("Pipeline done, x:%d",x);
    return 0;
}