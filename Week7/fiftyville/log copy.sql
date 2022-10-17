-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
--                             |
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
SELECT * FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND minute < 25 AND activity = "exit";
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+

-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking
-- by the ATM on Leggett Street and saw the thief there withdrawing some money.

SELECT * FROM atm_transactions WHERE atm_location LIKE "Leggett Street" AND year = 2021 AND day = 28 AND month = 7 AND transaction_type = "withdraw";

-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say
-- that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT * FROM phone_calls WHERE duration < 60 AND year = 2021 AND day = 28 AND month = 7;
SELECT * FROM flights WHERE year = 2021 AND day = 29 AND month = 7 ORDER BY hour,;

-- needs license plate, passport number, flight, phone number, atm

SELECT * FROM people WHERE phone_number IN ()
AND license_plate IN ()
AND passport_number IN ()
AND id IN ()
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );