SELECT DISTINCT(name) FROM stars, movies, people
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND movies.title IN(SELECT title FROM stars, movies, people
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND name LIKE "Kevin Bacon")
AND name NOT LIKE "Kevin Bacon";
