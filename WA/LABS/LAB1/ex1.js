"use strict";
const dayjs = require ('dayjs');
dayjs().format('MMM D, YYYY');
function Film(id, title, favorite, date, rating){
    this.id = id
    this.title = title;
    this.favorite = favorite?true:false;
    this.date = date?dayjs(date).format('MMM DD, YYYY'):'<not defined>';
    this.rating = rating? rating:'<not assigned>';
    
    this.printFilm = () =>{
        console.log('Id: ',this.id,', Title: ',this.title,', Favorite: ',this.favorite,', Watch date:',this.date.toString(),', Score: ',this.rating);
    }
}

function FilmLibrary(){
    this.list_films= [];

    this.addNewFilm = (film) => this.list_films.push(film);
    this.printLib = () => {
        for (const f of this.list_films)
            f.printFilm();
    }
    this.sortByDate = () =>[...this.list_films].sort((a,b) => b.date.diff(a.date));

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
library.printLib()
library.