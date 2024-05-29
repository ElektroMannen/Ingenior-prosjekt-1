
-- Get all users and their driving scores
SELECT u.id, u.name, u.email, u.address, u.tlf, e.total_impact_score FROM users u 
LEFT JOIN ecoscore e
ON u.id = e.user_id;

-- Overview
SHOW TABLES;



