#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdalign.h>


uint8_t* memscan8(const void* buf, size_t len, uint8_t needle);
void memrev(void* buf, size_t len);
bool read_u32_le_aligned(const void* buf, size_t len, size_t offset, uint32_t* out);

uint8_t* memscan8(const void* buf, size_t len, uint8_t needle){
   for(size_t i = 0; i<len; i++)
   {
    if ( *(uint8_t*)(buf+i) == needle)
        return (uint8_t*)buf;
   }
   return NULL;
}

void memrev(void* buf, size_t len){
     size_t step = sizeof(int);
    int tmp;
    printf("start\n");
    for (size_t i = 0; i < len/2; i++)
    {   
       tmp = *(int*)(buf+i*step);
       *(int*)(buf+i*step)=*(int*)(buf+(len-i-1)*step);
       *(int*)(buf+(len-i-1)*step)=tmp;
    }
    
    
}
bool read_u32_le_aligned(const void* buf, size_t len, size_t offset, uint32_t* out){
    if(len*4-offset<4)
        return false;
    const uint8_t* p = (const uint8_t*)buf + offset;
    if ( (uintptr_t)(p) % _Alignof(uint32_t) == 0){
        *out = *(uint32_t*)(buf+offset);
        uint32_t v = (uint32_t)p[0]
               | ((uint32_t)p[1] << 8)
               | ((uint32_t)p[2] << 16)
               | ((uint32_t)p[3] << 24);
        *out = v;
        return true;
    }
    return false;
}


int main(){
    if(memscan8("hello",5,'c') != NULL){
        printf("no null.\n");
    }else{
        printf("Null\n");
    }
    int array[5] = {0,1,2,3,4};
    memrev(array,5);
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d,",array[i]);
    }
    
    alignas(4) uint8_t buf[16] = {0x78,0x56,0x34,0x12};
    uint32_t out;
    if( read_u32_le_aligned(buf,4,9,&out))
        printf("\ntrue, 0x%08x",out);
    else
        printf("\false.");
    return 0;
}