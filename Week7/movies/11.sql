SELECT title FROM people, stars, movies, ratings
WHERE stars.movie_id = movies.id
AND ratings.movie_id = movies.id
AND people.id = stars.person_id
AND people.name LIKE "Chadwick Boseman"
ORDER BY rating DESC LIMIT 5;

--SELECT title FROM people, stars, movies, ratings WHERE people.id = stars.person_id AND movies.id = stars.movie_id AND people.name LIKE "Chadwick Boseman";