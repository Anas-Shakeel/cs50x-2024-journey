SELECT AVG(energy) from songs where (artist_id = (SELECT id FROM artists WHERE name = 'Drake'));
