"use strict";
const dayjs = require ('dayjs');

function Film(id, title, favorite, date, rating){
    this.id = id
    this.title = title;
    this.favorite = favorite?true:false;
    this.date = date?dayjs(date):'<not defined>';
    this.rating = rating? rating: -1;
    //this.date = date?dayjs(date).format('MMM DD, YYYY'):'<not defined>';
    this.printFilm = () =>{
        console.log('Id: ',this.id,', Title: ',this.title,', Favorite: ',this.favorite,', Watch date:',this.date == '<not defined>'?'<not defined>':this.date.format('MMM DD, YYYY').toString()
            ,', Score: ',this.rating>=0?this.rating:'<not defined>');
    }
}

function FilmLibrary(){
    this.list_films= [];

    this.addNewFilm = (film) => this.list_films.push(film);
    this.printLib = () => {
        for (const f of this.list_films)
            f.printFilm();
    }
    this.sortByDate = () =>[...this.list_films].sort((a,b) =>{ 
        a = a.date =='<not defined>'?dayjs('9999/12/30'):a.date;
        b = b.date =='<not defined>'?dayjs('9999/12/30'):b.date;
        console.log(b);
        console.log(a);
        return a.diff(b);
    });

    this.deleteFilm = (id) => {this.list_films = [...this.list_films].filter((a)=> a.id !=id);};

    this.resetWatchedFilms = ()=>{
        this.list_films = [...this.list_films].map((a) => {a.date = '<not defined>' ; return a;});
    }

    this.getRated = ()=> this.list_films.filter((a) => a.rating >=0).sort((a,b) => a-b);
}

const film_array = [
    [1,'Pulp Fiction',true,'March 10, 2023',5],
    [2,'21 Grams',true,'March 17, 2023',4],
    [3,'Star Wars',,,],
    [4,'Matrix',,,],
    [5,'Shrek',,'March 21, 2023',3]
];
const library = new FilmLibrary();

for (let i =0; i<film_array.length;i++)
    library.addNewFilm(new Film(film_array[i][0],film_array[i][1],film_array[i][2],film_array[i][3],film_array[i][4]))
//library.printLib()
console.log('Sort by date');
for (let b of library.sortByDate()){
    b.printFilm();
}
library.deleteFilm(1);
console.log('prova');
library.resetWatchedFilms();
for (let b of library.getRated()){
    b.printFilm();
}