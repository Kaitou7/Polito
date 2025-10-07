"use strict";

const set_string =['it','i','cat','spring','asfagagafgwhi'];
let new_set = [];
for (const s of set_string){
    new_set = set_string.map((a) => {
        const l = a.length;
        if(l >=2){
            return a[0] + a[1] + a[l-2]+a[l-1];
        } else
            return '';
    })
}
for (const s of new_set){
    console.log(s);
}