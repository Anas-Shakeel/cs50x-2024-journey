-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Find the description (crime scene report)
SELECT
    description
FROM
    crime_scene_reports
WHERE
    month = 7
    AND day = 28
    AND street = 'Humphrey Street';

-- Get the interviews of three witnesses (aka transcipts)
SELECT
    name,
    transcript
FROM
    interviews
WHERE
    month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';

-- Check bakery-security-logs for cars that left between 10:15 to 10:25
SELECT
    id,
    license_plate,
    hour,
    minute
FROM
    bakery_security_logs
WHERE
    month = 7
    AND day = 28
    AND activity = 'exit'
    AND hour = 10
    AND minute BETWEEN 15 AND 25
ORDER BY
    minute;

-- Get the list of people who have withdrawn money from the ATM at Leggett Street
select
    *
from
    people
WHERE
    id in (
        select
            person_id
        from
            bank_accounts AS b_a
            JOIN atm_transactions AS atm_t ON b_a.account_number = atm_t.account_number
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND transaction_type = 'withdraw'
            AND atm_location = 'Leggett Street'
    );

-- Get the list of phone calls of July 28, (with a duration of less than a minute [60secs])
select
    caller,
    receiver,
    duration
from
    phone_calls
where
    year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60;

--Get the earliest flight's info of JULY 29 (next day of theft)
SELECT
    id,
    origin_airport_id,
    destination_airport_id,
    hour,
    minute
FROM
    flights
WHERE
    year = 2023
    AND month = 7
    AND day = 29
ORDER BY
    hour
LIMIT
    1;

-- Get the city in which the thief escaped to
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

-- Get the passengers list that are boarding the earliest flight
select
    name,
    phone_number,
    people.passport_number
from
    people
    JOIN passengers ON people.passport_number = passengers.passport_number
WHERE
    flight_id IN (
        select
            id
        FROM
            flights
        WHERE
            year = 2023
            AND month = 7
            AND day = 29
        ORDER BY
            hour
        limit
            1
    );

-- Get the Thief
-- Find someone (in people) who has the passport_number from the passsengers list
-- and who has license_plate number from the parking lot leavers list
-- and who has phone_number from the call logs list of july 28 (within 10 minutes of 10:15)
-- and who has an id from the list of peoples who withdrawn the money
SELECT
    *
FROM
    people
WHERE
    passport_number IN (
        -- Get the passport_number list
        select
            people.passport_number
        from
            people
            JOIN passengers ON people.passport_number = passengers.passport_number
        WHERE
            flight_id IN (
                select
                    id
                FROM
                    flights
                WHERE
                    year = 2023
                    AND month = 7
                    AND day = 29
                ORDER BY
                    hour
                limit
                    1
            )
    )
    AND license_plate IN (
        -- Get the license_plate list
        select
            bsl.license_plate
        from
            people
            JOIN bakery_security_logs AS bsl on people.license_plate = bsl.license_plate
        WHERE
            activity = 'exit'
            AND year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 25
    )
    AND phone_number IN (
        -- Get the phone_number list
        select
            caller
        from
            people
            JOIN phone_calls ON people.phone_number = phone_calls.caller
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND duration < 60
    )
    AND id IN (
        -- Get the person_id list
        select
            bank_accounts.person_id
        from
            bank_accounts
            JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
        WHERE
            year = 2023
            AND month = 7
            AND day = 28
            AND transaction_type = 'withdraw'
            AND atm_location = 'Leggett Street'
    );

-- Get the accomplice of the thief
-- Once the thief is found, finding the accomplice is a piece of cake!
-- As we know that the thief called someone (his accomplice) shortly after the theft and talked for less than a minute
-- Find the number of the person on the other end of the call and check who's number it is.
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
                    -- Bruce is the name of the thief
                    name = 'Bruce'
            )
    );