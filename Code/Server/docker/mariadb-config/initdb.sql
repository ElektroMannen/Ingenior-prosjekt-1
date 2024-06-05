DROP DATABASE testdb;
CREATE DATABASE IF NOT EXISTS testdb;
USE testdb;

-- opprett tabeller

CREATE TABLE users (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name VARCHAR(255) NOT NULL,
	email VARCHAR(255) NOT NULL,
	address VARCHAR(255) NOT NULL,
	tlf VARCHAR(255)
) ENGINE=InnoDB;


CREATE TABLE vehicles (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	vehicle_type VARCHAR(255),
	user_id INT UNSIGNED,
	owner_id INT UNSIGNED,
	CONSTRAINT FOREIGN KEY (user_id) REFERENCES users(id)
	  ON DELETE SET NULL
      ON UPDATE CASCADE,
    CONSTRAINT FOREIGN KEY (owner_id) REFERENCES users(id)
) ENGINE=InnoDB;


CREATE TABLE drivescores (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	ts TIMESTAMP,
	score FLOAT NOT NULL,
	car_id INT UNSIGNED,
	CONSTRAINT `fk_drivescores_users`
      FOREIGN KEY (car_id) REFERENCES vehicles (id)
      ON DELETE SET NULL
      ON UPDATE CASCADE
) ENGINE=InnoDB;


CREATE TABLE rentrecords (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	start_date DATE NOT NULL,
	end_date DATE,
	average_score FLOAT,
	user_id INT UNSIGNED NOT NULL,
    CONSTRAINT `fk_rentrecords_users`
      FOREIGN KEY (user_id) REFERENCES users (id)
      ON DELETE CASCADE
      ON UPDATE RESTRICT
) ENGINE=InnoDB;


CREATE TABLE ecoscore (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	td TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	score FLOAT,
	user_id INT UNSIGNED,
    CONSTRAINT `fk_ecoscore_users`
      FOREIGN KEY (user_id) REFERENCES users (id)
      ON DELETE SET NULL
      ON UPDATE CASCADE
) ENGINE=InnoDB;


CREATE TABLE transactions (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	amount FLOAT,
	recorded_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	user_id INT UNSIGNED,
    CONSTRAINT `fk_transactions_users`
      FOREIGN KEY (user_id) REFERENCES users (id)
      ON DELETE SET NULL
      ON UPDATE CASCADE
) ENGINE=InnoDB;


CREATE TABLE tollstation (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	info VARCHAR(255),
	location VARCHAR(255),
	electric_price FLOAT,
	gasoline_price FLOAT,
	service_price FLOAT
) ENGINE=InnoDB;


CREATE TABLE powerprices (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	NOK_per_kWh FLOAT
) ENGINE=InnoDB;


CREATE TABLE chargestation (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	weather VARCHAR(255),
	location VARCHAR(255),
	electric_price FLOAT,
	service_price FLOAT
) ENGINE=InnoDB;


CREATE TABLE chargerecords (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	parking_spot INT UNSIGNED NOT NULL,
	from_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	to_time TIMESTAMP NULL,
	station_id INT UNSIGNED,
	start_charge FLOAT,
	end_charge FLOAT,
	CONSTRAINT FOREIGN KEY (station_id) REFERENCES chargestation(id)
) ENGINE=InnoDB;


CREATE TABLE relations (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	tr_id INT UNSIGNED,
	toll_id INT UNSIGNED,
	pcost_id INT UNSIGNED,
	cr_id INT UNSIGNED,
	CONSTRAINT FOREIGN KEY (tr_id) REFERENCES transactions(id)
	  ON DELETE SET NULL
      ON UPDATE CASCADE,
    CONSTRAINT FOREIGN KEY (toll_id) REFERENCES tollstation(id)
      ON DELETE SET NULL
      ON UPDATE CASCADE,
    CONSTRAINT FOREIGN KEY (pcost_id) REFERENCES powerprices(id),
    CONSTRAINT FOREIGN KEY (cr_id) REFERENCES chargerecords(id)
) ENGINE=InnoDB;


-- Setup test-database.

INSERT INTO users (name, email, address) VALUES
	('Staten', "stat@mail.no", "Gate 23"),
	('Erlend Ferkingstad', 'erlend@mail.no', 'Fjellheimen 12C'),
	('Artur Jakobsen', 'artur@gmail.com', 'Sjøbakken 15'),
	('Solveig Karimi', 'solveig@gmail.com', 'Grønnhagen 42');



INSERT INTO vehicles (vehicle_type, owner_id, user_id) VALUES
('Gasoline',1,1),
('Electric',1,1),
('Service',1,1),
('Electric',2,1),
('Service',2,2),
('Gasoline',3,3),
('Electric',1,4);


INSERT INTO drivescores (score, car_id) VALUES
	(85.4, 1),
	(75.9, 1),
	(57.9, 2),
	(89.9, 3),
	(64.31, 2),
	(91.3, 4);

/* eksempel på å finne alle scores knyttett 
 * til en bruker og lagre gjennomsnittet */

INSERT INTO rentrecords (start_date, average_score, user_id)
SELECT '2024-03-21', AVG(score), 1 
FROM drivescores
WHERE car_id = 1;

INSERT INTO ecoscore (score, user_id)
SELECT AVG(score), 1 FROM users u 
LEFT JOIN vehicles v ON v.user_id = u.id
LEFT JOIN drivescores d ON d.id = v.user_id
WHERE u.id = 1;

INSERT INTO ecoscore (score, user_id)
SELECT AVG(score), 2 FROM users u 
LEFT JOIN vehicles v ON v.user_id = u.id
LEFT JOIN drivescores d ON d.id = v.user_id
WHERE u.id = 2;

INSERT INTO ecoscore (score, user_id)
SELECT AVG(score), 3 FROM users u 
LEFT JOIN vehicles v ON v.user_id = u.id
LEFT JOIN drivescores d ON d.id = v.user_id
WHERE u.id = 3;


INSERT INTO ecoscore (score, user_id) VALUES (97.1, 1);

INSERT INTO transactions (amount, user_id) VALUES (165, 1);

INSERT INTO tollstation (info, location, electric_price, gasoline_price, service_price) VALUES 
("operation normal", "Nardo", 12.1, 21.41, 2.14),
("operation normal", "Angeltrøa", 10.1, 24.41, 4.14),
("operation normal", "Melhus", 9.1, 21.41, 2.14);

INSERT INTO powerprices (NOK_per_kWh) VALUES (0.0134);

INSERT INTO chargestation (location, electric_price, service_price, weather) VALUES
("Lade", 5.41, 3.15, "cloudy"),
("Byåsen", 5.21, 2.12, "sunny");

INSERT INTO chargerecords (parking_spot, from_time, to_time, station_id, start_charge, end_charge) VALUES
(1, '2024-06-03 12:34:56', '2024-06-03 14:34:56', 1, 240, 10),
(3, '2024-06-04 10:00:00', '2024-06-04 12:00:00', 2, 198, 62),
(2, '2024-06-05 09:00:00', '2024-06-05 11:00:00', 1, 1205, 499);

INSERT INTO relations (tr_id, toll_id, pcost_id, cr_id) VALUES
	(1, NULL, 1, 1),
	(NULL, 1, NULL, NULL),
	(1, 1, NULL, NULL),
	(1, NULL, NULL, 2);



