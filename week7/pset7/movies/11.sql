SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE name = "Chadwick Boseman" AND title != "Message from the King" ORDER BY rating DESC;