SELECT DISTINCT(p.name)
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE m.title IN (
    SELECT DISTINCT(m2.title)
    FROM people p2
    JOIN stars s2 ON p2.id = s2.person_id
    JOIN movies m2 ON s2.movie_id = m2.id
    WHERE p2.name = "Kevin Bacon" AND p2.birth = 1958
) AND p.name != "Kevin Bacon";
