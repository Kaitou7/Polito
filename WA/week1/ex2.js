"use strict"
let names=  "Luigi De Russis, Luca Mannella, Fulvio Corno, Juan Pablo Saenz Moreno, Enrico Masala, Antonio Servetti";
let vet_names = names.split(',');
for(let i=0;i<vet_names.length;i++){
    vet_names[i] = vet_names[i].trim();
}
let vet_acro = [];
let acro;
let k = 0;
for (const name of vet_names){
    let s = name.toUpperCase();
    let s2 = s.split(' ');
    acro = '';
    for (let j=0;j<s2.length;j++){
        acro += s2[j][0];
    }
    vet_acro.push(acro);
    k++;
}

vet_acro.sort();
vet_names.sort();
console.log(vet_names);
console.log(vet_acro);