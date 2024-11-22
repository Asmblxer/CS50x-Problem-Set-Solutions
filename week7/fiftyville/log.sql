-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Log of SQL queries for solving the mystery

-- Find crime scene report matching the date and location
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';

-- Retrieve relevant interview transcripts mentioning the bakery
SELECT transcript
FROM interviews
WHERE day = 28 AND month = 7 AND transcript LIKE '%bakery%';

-- Check bakery security logs for cars leaving the parking lot within the timeframe
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND hour = 10 AND minute BETWEEN 15 AND 25;

-- Identify people associated with the suspicious license plates
SELECT p.name
FROM people p
JOIN bakery_security_logs b ON p.license_plate = b.license_plate
WHERE b.day = 28 AND b.month = 7 AND b.hour = 10 AND b.minute BETWEEN 15 AND 25;

-- Find ATM transactions at Leggett Street on the day of the crime
SELECT *
FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street';

-- Identify people who made withdrawals from the ATM
SELECT p.name
FROM people p
JOIN bank_accounts b ON p.id = b.person_id
JOIN atm_transactions a ON b.account_number = a.account_number
WHERE a.month = 7 AND a.day = 28 AND a.atm_location = 'Leggett Street' AND a.transaction_type = 'withdraw';

-- Find short phone calls (less than 60 seconds) on the day of the crime
SELECT caller
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <= 60;

-- Identify callers of the short phone calls
SELECT p.name
FROM people p
JOIN phone_calls c ON p.phone_number = c.caller
WHERE c.month = 7 AND c.day = 28 AND c.duration <= 60;

-- Find Fiftyville airport ID
SELECT id
FROM airports
WHERE city = 'Fiftyville';

-- Identify the earliest flight leaving Fiftyville the next day
SELECT *
FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
  AND month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- List passengers on the earliest flight
SELECT p.name
FROM people p
JOIN passengers ps ON p.passport_number = ps.passport_number
JOIN flights f ON ps.flight_id = f.id
WHERE f.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND f.month = 7 AND f.day = 29
AND f.hour = 8 AND f.minute = 20;

-- Find the destination of the earliest flight
SELECT a.city
FROM airports a
JOIN flights f ON a.id = f.destination_airport_id
WHERE f.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
  AND f.month = 7 AND f.day = 29
  AND f.hour = 8 AND f.minute = 20;

-- Get Bruce's phone number
SELECT phone_number
FROM people
WHERE name = 'Bruce';

-- Identify Bruce's accomplice (receiver of his phone call)
SELECT p.name
FROM people p
JOIN phone_calls c ON p.phone_number = c.receiver
WHERE c.month = 7 AND c.day = 28
  AND c.duration <= 60
  AND c.caller = (SELECT phone_number FROM people WHERE name = 'Bruce');
