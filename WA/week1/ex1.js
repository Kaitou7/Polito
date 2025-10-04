"use strict";
const marks = [-12, -3, 18, 10, 4, -1, 0, 16];
const marks2 = [...marks];
marks2.sort((a,b)=> b-a);

let i = marks2.findIndex((e) => e<0);
let NN = marks.length-i;
let marks3 = marks2.slice(0,i-2);
console.log(marks2);
console.log(marks3);
let avg = 0;
for (const val of marks3){
    avg +=val;
}
avg =Math.round( avg / marks3.length);
console.log(avg);

const addedArray = Array(NN+2).fill(avg);

marks3.splice(marks3.length,0,...addedArray);
console.log(marks3);