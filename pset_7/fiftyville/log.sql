-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
SELECT transcript, name FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;

SELECT full_name FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE month = 7 AND day = 29 AND year = 2021);
SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 ORDER BY duration ASC; --returns caller number
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street';
SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND activity = 'exit';
SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021);
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street');
SELECT transaction_type, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 and atm_location = 'Leggett Street';
SELECT destination_airport_id FROM flights WHERE hour <= 8 AND month = 7 AND day = 29 AND year = 2021;
SELECT full_name FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE hour <= 8 AND month = 7 AND day = 29 AND year = 2021);
--above query outputs Fiftyville Regional Airport so (...) outputs earliest flight out of Fiftyville the day after robbery




-- suspects
SELECT name
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND activity = 'exit')
-- outputs Sofia, Taylor, Diana, Kelsey and Bruce


SELECT name
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND activity = 'exit')
AND id IN(SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street'));
--outputs Taylor, Diana and Bruce


SELECT name
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration <= 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND activity = 'exit')
AND id IN(SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street'));
--outputs Taylor, Diana and Bruce


SELECT name
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration <= 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND activity = 'exit')
AND id IN(SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
--outputs Taylor, Dana and Bruce


SELECT name
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration <= 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute >= 15 AND activity = 'exit')
AND id IN(SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
--outputs Taylor, Dana and Bruce


SELECT name
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration <= 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2021))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit')
AND id IN(SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
--Outputs Bruce and Diana


SELECT name
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND duration <= 60)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id
    IN (
        SELECT id
        FROM flights
        WHERE hour <= 8
        AND month = 7
        AND day = 29
        AND year = 2021))
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute >= 5
    AND minute <= 25
    AND activity = 'exit')
AND id IN (
    SELECT person_id FROM bank_accounts WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND year = 2021
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'));

--outputs Bruce!!


SELECT name
FROM people
WHERE phone_number
IN (
    SELECT receiver FROM phone_calls WHERE caller IN (
        SELECT caller FROM phone_calls WHERE phone_number IN (
            SELECT phone_number FROM people WHERE name = 'Bruce')));
--outputs Bruce??

SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce');

SELECT name
FROM people
WHERE phone_number
IN (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));

SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = 2021 AND month = 7 AND day = 28 AND duration <= 60;
--outputs only 1 phone number (375) 555-8161

SELECT name
FROM people
WHERE phone_number
IN (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = 2021 AND month = 7 AND day = 28 AND duration <= 60);
--outputs Robin

SELECT name
FROM people
WHERE phone_number
IN (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Diana') AND year = 2021 AND month = 7 AND day = 28 AND duration <= 60);

SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE hour <= 8 AND month = 7 AND day = 29 AND year = 2021));

SELECT license_plate, hour, minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND activity = 'exit';