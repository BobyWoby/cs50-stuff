SELECT DISTINCT name FROM people, directors, movies, ratings
WHERE people.id = directors.person_id
AND movies.id = directors.movie_id
AND ratings.movie_id = movies.id
AND rating >= 9.0;

--SELECT DISTINCT name FROM people, directors, movies, ratings WHERE people.id = directors.person_id AND movies.id = directors.movie_id AND ratings.movie_id = movies.id AND rating > 9.0;