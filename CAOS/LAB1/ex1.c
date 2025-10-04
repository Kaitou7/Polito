#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


uint8_t* memscan8(const void* buf, size_t len, uint8_t needle);
void memrev(void* buf, size_t len);
bool read_u32_le_aligned(const void* buf, size_t len, size_t offset, uint32_t* out);

uint8_t* memscan8(const void* buf, size_t len, uint8_t needle){
    size_t step = sizeof(*buf);
   for(size_t i = 0; i<len; i++)
   {
    uint8_t elemento = *(uint8_t*)(buf);
    if ( elemento == needle)
        return (uint8_t*)buf;
    buf +=step;
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
    if ( (uintptr_t)(buf+offset) % _Alignof(uint32_t) == 0.){
        *out = *(uint32_t*)(buf+offset);
        return true;
    }
    return false;
}


int main(){
    if(memscan8("hello",5,'o') != NULL){
        printf("no null");
    }else{
        printf("Null");
    }
    int array[5] = {0,1,2,3,4};
    memrev(array,5);
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d,",array[i]);
    }
    
    uint32_t bytes_4[4] = {0x87654321,0x87653020,0x80654321,0x75654321};
    uint32_t out;
    if( read_u32_le_aligned(bytes_4,4,9,&out))
        printf("\ntrue, 0x%08x",out);
    else
        printf("\falso.");
    return 0;
}