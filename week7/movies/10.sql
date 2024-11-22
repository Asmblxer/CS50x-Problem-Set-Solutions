select p.name from people p
join directors d on p.id = d.person_id
join ratings r on r.movie_id = d.movie_id
where r.rating >= 9.0
