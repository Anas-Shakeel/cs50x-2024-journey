-- Get the accomplice of the thief
SELECT
    *
FROM
    people
WHERE
    phone_number = (
        -- Get the phone number of the receiver of the call that bruce made
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            month = 7
            AND day = 28
            AND duration < 60
            AND caller = (
                -- Get the phone number of bruce (thief)
                SELECT
                    phone_number
                FROM
                    people
                WHERE
                    name = 'Bruce'
            )
    );