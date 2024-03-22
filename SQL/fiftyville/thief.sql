-- Get the Thief
SELECT * FROM people
WHERE passport_number IN (
-- Get the passport_number list
select people.passport_number from people JOIN passengers ON people.passport_number=passengers.passport_number WHERE flight_id IN (select id FROM flights WHERE year=2023 AND month=7 AND day=29 ORDER BY hour limit 1)

)
AND license_plate IN (
-- Get the license_plate list
select bsl.license_plate from people JOIN bakery_security_logs AS bsl on people.license_plate=bsl.license_plate WHERE activity='exit' AND year=2023 AND month=7 AND day=28 AND hour=10 AND minute BETWEEN 15 AND 25

)
AND phone_number IN (
-- Get the phone_number list
select caller from people JOIN phone_calls ON people.phone_number=phone_calls.caller WHERE year=2023 AND month=7 AND day=28 AND duration < 60

)
AND id IN (
-- Get the person_id list
select bank_accounts.person_id from bank_accounts JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number WHERE year=2023 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street'

);
