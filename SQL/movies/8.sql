-- List of names of all people who starred in Toy Story.

SELECT people.name from people JOIN stars ON people.id=stars.person_id WHERE stars.movie_id = (SELECT id from movies WHERE title="Toy Story");
