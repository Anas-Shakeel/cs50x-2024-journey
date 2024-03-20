-- List the names of all people who starred in a movie released in 2004, Ordered by birth year.
-- Persons who have appeared in more movies than one, should appear only once in result

SELECT people.name from people JOIN stars ON people.id=stars.person_id WHERE stars.movie_id in (SELECT id from movies WHERE year = 2004) ORDER BY people.birth;
