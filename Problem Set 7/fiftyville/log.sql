-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get interview transcripts for witnesses who saw the theft
SELECT * FROM interviews WHERE id IN (161, 162, 163);
-- Look for ATM transactions on July 28, 2024 near crime time
SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28;

-- Look for phone calls made on that day (suspect called accomplice)
SELECT * FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;

-- Look for flights leaving Fiftyville on July 28 after 10am
SELECT * FROM flights WHERE origin_airport_id = (
    SELECT id FROM airports WHERE city = 'Fiftyville'
) AND year = 2024 AND month = 7 AND day = 28 ORDER BY hour, minute;

-- Get passenger names on the earliest flight
SELECT * FROM passengers WHERE flight_id = [ID_OF_FIRST_FLIGHT];
-- Replace [ID_OF_FIRST_FLIGHT] with actual flight ID from the above

-- Join with people table to get names
SELECT people.name, people.phone_number, people.passport_number
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = [FLIGHT_ID];

