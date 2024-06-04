
-- Get all users and their driving scores
SELECT u.id, u.name, u.email, u.address, u.tlf, e.score FROM users u 
LEFT JOIN ecoscore e
ON u.id = e.user_id;

-- Overview
SHOW TABLES;

-- Show info
SELECT p.NOK_per_kWh OK, c.tr_id FROM powerprices p LEFT JOIN coupling c ON p.id = c.pcost_id;

-- Get score based on vehicle ID and user ID

SELECT v.class, e.total_impact_score, t.info, p.NOK_per_kWh  FROM vehicles v 
LEFT JOIN users u ON v.owner_id = u.id
LEFT JOIN ecoscore e ON e.user_id = u.id
LEFT JOIN toll t ON v.id = t.car_id
LEFT JOIN coupling c ON c.toll_id = t.id
LEFT JOIN powerprices p ON p.id = c.pcost_id 
WHERE u.id = 1;

SELECT v.class, e.total_impact_score, t.info, p.NOK_per_kWh  FROM vehicles v 
LEFT JOIN users u ON v.owner_id = u.id
LEFT JOIN ecoscore e ON e.user_id = u.id
LEFT JOIN toll t ON v.id = t.car_id
LEFT JOIN coupling c ON c.toll_id = t.id
LEFT JOIN powerprices p ON p.id = c.pcost_id;
-- WHERE u.id = 1;

SELECT t.id, p.id, p.NOK_per_kWh FROM relations r 
LEFT JOIN powerprices p ON r.pcost_id = p.id
LEFT JOIN tollstation t ON r.toll_id = t.id
WHERE t.id = 1
ORDER BY p.id DESC
LIMIT 1;

SELECT id, electric_price, gasoline_price, service_price FROM tollstation t
WHERE id = 1;


SELECT * FROM relations r ;

SELECT * FROM powerprices p;

SELECT * FROM transactions t;

SELECT * FROM tollstation t;

SELECT * FROM powerprices p;

SELECT * FROM chargestation cs ;

SELECT * FROM chargerecords cr;

SELECT v.id, v.vehicle_type, AVG(e.score) FROM vehicles v 
LEFT JOIN users u ON v.owner_id = u.id
LEFT JOIN ecoscore e ON e.user_id = u.id
WHERE u.id = 1 AND v.id = 1;

SELECT id, (start_charge - end_charge) AS total
FROM chargerecords
ORDER BY id DESC
LIMIT 1;

SELECT t.id, c.parking_spot, cs.location , t.amount, t.user_id  FROM transactions t 
LEFT JOIN relations r ON t.id = r.tr_id 
LEFT JOIN chargerecords c ON c.id = r.cr_id
RIGHT JOIN chargestation cs ON cs.id = c.station_id; 



SELECT * FROM vehicles v ;


UPDATE chargerecords 
SET parking_spot = 1
WHERE id = 4;


UPDATE chargerecords 
SET end_charge = 184
WHERE id = 9;


-- DO NOT USE
START TRANSACTION;
INSERT INTO toll (info, car_id)
  VALUES ('ask for price', 1);
SET @toll_id = LAST_INSERT_ID();
INSERT INTO powerprices (NOK_per_kWh)
  VALUES (0.211);
INSERT INTO coupling  (tr_id, toll_id, pcost_id)
SELECT NULL, @toll_id, MAX(id) FROM powerprices;
COMMIT;