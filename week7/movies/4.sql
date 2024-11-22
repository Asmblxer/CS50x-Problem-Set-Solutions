select count(*) from movies m join ratings r on m.id = r.movie_id
where r.rating = 10.0;
