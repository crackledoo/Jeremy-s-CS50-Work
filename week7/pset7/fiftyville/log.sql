-- Keep a log of any SQL queries you execute as you solve the mystery.


--In case anyone was wondering, I'm listening to https://open.spotify.com/playlist/1lVvm0ra9Zfwkrwlk0BC0O


--Look at description of crime
SELECT description FROM crime_scene_reports WHERE street = "Chamberlin Street" AND month = 7 AND day = 28;
--Search interview transcripts from month 7 and day 28 where "courthouse" is in the transcript text.
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND year = 2020 AND transcript LIKE "%courthouse%";

--IDEAS: Ruth: Search courthouse_security_logs before and after 10 minutes of theft for license plates
--       Eugene: Thief was withdrawing money from ATM on Fifer street before 10:15am
--       Raymond: Thief made call for less than a minute within 10 minutes of 10:15am, mentioned "they were planning to take the earliest
--          flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight
--          ticket"

--Select license_plate from Ruth's timeframe, establish all "exit" names as SUSPECTS.
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 0 AND minute <=30 AND activity = "exit");

--SUSPECTS:
--      Patrick
--      Amber
--      Elizabeth
--      Roger
--      Danielle
--      Russell
--      Evelyn
--      Ernest

--Compare names to Eugene's suggestion: people who made withdrawals on Fifer street on 07-28-2020 before 10:15am
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number =
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"));
--Gasp! Is it Danielle???


--Search according to Raymond's suggestion, by phone call:
SELECT name FROM people WHERE phone_number = (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);
--Perhaps its Roger??

SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);
--It would make Jack an accomplice...


--Re-searching atm transactions more broadly, to see if Roger has any activity
SELECT atm_location, transaction_type FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND account_number = (SELECT account_number FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE name = "Roger"));
--Nothing?

--Further following Raymond's tip, let's see all the people who left Fiftyville on 07-29
SELECT name FROM people WHERE passport_number =
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE city = "Fiftyville")));
--GLORIA???????????????
--Ugh.

SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE city = "Fiftyville"));
--There so many passports that don't match with people...

SELECT flight_id FROM passengers WHERE passport_number =
(SELECT passport_number FROm people WHERE name = "Roger")
AND flight_id IN
(SELECT id FROM flights WHERE year = 2020 AND month = 7);
--36??

SELECT day, origin_airport_id FROM flights WHERE id = 36;
--Okay, so the flight took place on July 28, not 'the earliest flight out tomorrow'. Fine. Whatever.

--I'm just going to check for each suspect's flights:
SELECT name, month, day, hour, minute, city FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND month =  7 AND day > 27 AND (name = "Roger" OR name = "Danielle" OR name = "Jack");

--if joining by origin:
--name | month | day | hour | minute | city
--Danielle | 7 | 30 | 13 | 7 | Fiftyville
--Jack | 7 | 28 | 12 | 51 | Chicago
--Roger | 7 | 29 | 8 | 20 | Fiftyville
--Danielle | 7 | 29 | 8 | 20 | Fiftyville
--Danielle | 7 | 30 | 18 | 28 | Dallas

SELECT name, month, day, hour, minute, city FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON flights.destination_airport_id = airports.id
WHERE year = 2020 AND month =  7 AND day > 27 AND (name = "Roger" OR name = "Danielle" OR name = "Jack");

--if joining by destination:
--name | month | day | hour | minute | city
--Danielle | 7 | 30 | 13 | 7 | Delhi
--Jack | 7 | 28 | 12 | 51 | Fiftyville
--Roger | 7 | 29 | 8 | 20 | London
--Danielle | 7 | 29 | 8 | 20 | London
--Danielle | 7 | 30 | 18 | 28 | Fiftyville
--
--it doesn't look like it was Danielle, although her travel schedule IS pretty messed up.
--Like, who flies to Delhi, then London, then back to Fiftyville within a few hours????
--
--It looks like it was Jack and Roger, in cahoots. Roger must be in London now.
--Okay, check50 says that it WASN'T Jack and Roger. Whatever.
--
--I'm just going to redo this whole thing, then...
--Ruth: Search courthouse_security_logs before and after 10 minutes of theft for license plates
--Eugene: Thief was withdrawing money from ATM on Fifer street before 10:15am
--Raymond: Thief made call for less than a minute within 10 minutes of 10:15am, mentioned "they were planning to take the earliest
--      flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight
--      ticket"
--
--LICENSE PLATE SUSPECTS:
--      Patrick
--      Amber
--      Elizabeth
--      Roger
--      Danielle
--      Russell
--      Evelyn
--      Ernest

SELECT name, atm_location FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
--output:
--name | atm_location
--Ernest | Fifer Street
--Russell | Fifer Street
--Elizabeth | Fifer Street
--Danielle | Fifer Street

--remaining suspects:
--Ernest
--Russell
--Elizabeth
--Danielle

--Finding caller-suspects
SELECT name FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 61;

--Remaining suspects:
--Ernest
--Russell

--Finding receiver-suspects
SELECT name FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 61 AND caller =
(SELECT phone_number FROM people WHERE (name = "Ernest" OR name = "Russell"));
--Only suspect is Philip

SELECT name FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 61 AND receiver =
(SELECT phone_number FROM people WHERE name = "Philip");

--Is it Russell??????????????


--I'm just going to check for each suspect's flights AGAINNNNNN
SELECT name, month, day, hour, minute, city FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND month =  7 AND day > 27 AND (name = "Russell" OR name = "Philip");

--if joining by origin:
--name | month | day | hour | minute | city
--Philip | 7 | 30 | 13 | 55 | Fiftyville
--Russell | 7 | 29 | 16 | 0 | Fiftyville
--Russell | 7 | 30 | 16 | 27 | Dubai
--Philip | 7 | 30 | 9 | 46 | London
--Russell | 7 | 30 | 10 | 19 | Fiftyville


SELECT name, month, day, hour, minute, city FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON flights.destination_airport_id = airports.id
WHERE year = 2020 AND month =  7 AND day > 27 AND (name = "Russell" OR name = "Philip");

--name | month | day | hour | minute | city
--Philip | 7 | 30 | 13 | 55 | London
--Russell | 7 | 29 | 16 | 0 | Boston
--Russell | 7 | 30 | 16 | 27 | Fiftyville
--Philip | 7 | 30 | 9 | 46 | Fiftyville
--Russell | 7 | 30 | 10 | 19 | Dallas