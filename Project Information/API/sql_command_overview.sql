
-- Get all users and their driving scores
SELECT u.id, u.name, u.email, u.address, u.tlf, e.total_impact_score FROM users u 
LEFT JOIN ecoscore e
ON u.id = e.user_id;

-- Overview
SHOW TABLES;

-- Show info
SELECT p.NOK_per_kWh OK, c.tr_id FROM powerprices p LEFT JOIN coupling c ON p.id = c.pcost_id;

-- Get score based on vehicle ID and user ID

SELECT v.class, e.total_impact_score FROM vehicles v 
LEFT JOIN users u ON v.owner_id = u.id
LEFT JOIN ecoscore e ON e.user_id = u.id
WHERE u.id = 1;




