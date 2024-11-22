SELECT m.title
FROM movies m
JOIN stars s ON s.movie_id = m.id
JOIN people p ON p.id = s.person_id
WHERE p.name = 'Bradley Cooper'
AND m.title IN (
    SELECT m.title
    FROM movies m
    JOIN stars s ON s.movie_id = m.id
    JOIN people p ON p.id = s.person_id
    WHERE p.name = 'Jennifer Lawrence'
);
