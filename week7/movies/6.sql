select avg(r.rating) from ratings r join movies m on m.id = r.movie_id
where m.year = 2012;
