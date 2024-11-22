select name from people p
join stars s on p.id = s.person_id
join movies m on m.id = s.movie_id
where m.title = 'Toy Story';
