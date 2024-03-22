-- Get the city the thief escaped to
SELECT
    *
FROM
    airports
WHERE
    id IN (
        -- Get the destination airport
        SELECT
            destination_airport_id
        FROM
            flights
        WHERE
            year = 2023
            AND month = 7
            AND day = 29
        ORDER BY
            hour,
            minute ASC
        LIMIT
            1
    );