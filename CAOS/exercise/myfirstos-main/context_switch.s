.syntax unified
.cpu cortex=m4
.thumb
//just an implementation of a function so dont need of .data
.text
.thumb_func
.global os_switch
// defined in os.c and os.h, this symbol will be global.
os_switch:

ldr r2,[r0] 
// first parameter pointer copied
cbz r2,1f
// if r2 equal to 0 jump to 1 label
stmdb sp!, {r4-r11, lr}
// take all registers listed in {}, store them in the adx starting with the sp
mov r3,sp
str r4,[r2]
// saved sp in another register, cause sp can be modified everytime by other tasks

1:

ldr r3,[r1]  //r3=next->sp, switching the stack pointer of the next program
mov sp,r3
ldmia sp!, {r4-r11, lr}
// load group of set of registers from memory sp and load it into registers r4-r11, lr; remember order same of previous inst.
bx lr
//return from function
