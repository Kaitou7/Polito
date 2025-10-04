"use strict";
const dayjs = require ('dayjs');

function Answer(text, resp, score, date ){
    this.response = text;
    this.respondent =resp;
    this.score=score;
    this.date=dayjs(date);

}

function Question(text, quest, date ){
    this.questione_text = text;
    this.questioner =quest;
    this.obj_date=dayjs(date);
    this.list_answer= [];

    this.add = (ans) => this.list_answer.push(ans);

    /*

    function myfilter(vett, callback){
        let list_ans2 = [];
        for(const a of vett){
            if(callback(a))
                list_ans2.push(a);
        }
        return list_ans2;
    }
    this.findAll = (name) => myfilter ( this.list_answer, (a)=>a.respondent===name); 
    
    custom filter function, for functional programming

    all callbacks are like these v.filter(( current value, index of the value, vector reference)) =>{}  
    
    .reduce  (callback(accumulator, currentvalue[,index[,array]]) , [,initialValue]), second parameter is optionale, if not given
    it take the first element of the array; it will be the initialization of accumulator; current value will be first element of array.
    */

    this.findAll = (name) => this.list_answer.filter((a) => a.respondent===name);

    this.afterDate = (d) => this.list_answer.filter( (a)=> a.date.isAfter(d))

    this.listByDate = () => [...this.list_answer].sort((a,b) => b.date.diff(a.date));

    this.listByScore = () => [...this.list_answer].sort((a,b)=> b.score-a.score);
}
const answers_array = [
    ["Hello word",'antonio','10','2023-08-30'],
    ["Hello gianni",'enrico','2','2025-08-03'],
    ["Hello cai",'antonio','1','2025-08-30']
];
const answers_obj = [];
for (let i = 0; i<answers_array.length;i++){
    answers_obj[i] = new Answer(answers_array[i][0],answers_array[i][1],answers_array[i][2],answers_array[i][3])
}
const q1 = new Question("How are you?",'Gianni','2018-02-10');
q1.add(answers_obj[0]);
q1.add(answers_obj[1]);
q1.add(answers_obj[2]);

console.log(q1.findAll('antonio'));

console.log('q1 answer text',q1.findAll('antonio').map((a)=>a.response));
console.log('dates: ');
console.log(q1.afterDate(dayjs().subtract(1,'year')));
console.log("sort date",q1.listByDate());
console.log("sort score",q1.listByScore());