select m.title, r.rating from ratings r join movies m on m.id = r.movie_id
where year = 2010
order by r.rating desc, m.title;
