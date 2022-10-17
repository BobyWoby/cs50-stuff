--SELECT movies.title, ratings.rating FROM movies JOIN ratings ON ratings.rating = rating WHERE year = 2010;
SELECT ratings.rating, movies.title FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2010
ORDER BY rating DESC, title;