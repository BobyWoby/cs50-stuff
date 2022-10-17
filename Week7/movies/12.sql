SELECT title FROM movies, people, stars
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND people.name LIKE "Johnny Depp" AND
title IN (SELECT title FROM movies, people, stars
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND people.name LIKE "Helena Bonham Carter");


--IN ("Johnny Depp","Helena Bonhaam Carter");
