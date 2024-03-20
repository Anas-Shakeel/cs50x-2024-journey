-- List of names of directors who directed a movie which got a rating of at 9.0
-- If a director directed more than one movie which got 9.0 rating, they should only appear in results once (or the name their of)

SELECT name FROM people WHERE people.id IN (SELECT person_id FROM directors JOIN ratings ON directors.movie_id=ratings.movie_id WHERE ratings.rating >=9.0);
