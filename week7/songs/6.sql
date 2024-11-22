SELECT songs.name
FROM songs
JOIN artists ON songs.artist_id = artists.id
where artists.name = 'Post Malone';
