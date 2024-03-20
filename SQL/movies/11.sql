-- list the titles of the five highest rated movies (in order)
-- that Chadwick Boseman starred in, starting with the highest rated.
SELECT
    title
FROM
    movies
    -- Join stars and ratings tables with movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN ratings ON movies.id = ratings.movie_id
WHERE
    -- Get the person ID of Chadwick Boseman
    stars.person_id = (
        SELECT
            id
        FROM
            people
        WHERE
            name = "Chadwick Boseman"
    )
    -- Sort by rating in Descending order
ORDER BY
    ratings.rating DESC
LIMIT
    5;
