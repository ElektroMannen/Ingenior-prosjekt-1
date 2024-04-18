DROP DATABASE testdb;
CREATE DATABASE IF NOT EXISTS testdb;
USE testdb;
CREATE TABLE vehicles (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	class VARCHAR(255),
	owner_id INT
) ENGINE=InnoDB;

CREATE TABLE drivingscore (
	id INT AUTO_INCREMENT PRIMARY KEY,
	ts TIMESTAMP,
	score FLOAT NOT NULL,
	vehicle_id INT UNSIGNED NOT NULL,
	CONSTRAINT `fk_drivingscore_vehicles`
      FOREIGN KEY (vehicle_id) REFERENCES vehicles (id)
      ON DELETE CASCADE
      ON UPDATE RESTRICT
) ENGINE=InnoDB;

CREATE TABLE person (
	id INT AUTO_INCREMENT PRIMARY KEY,
	name VARCHAR(255) NOT NULL,
	email VARCHAR(255) NOT NULL,
	address VARCHAR(255) NOT NULL,
	tlf VARCHAR(255)
) ENGINE=InnoDB;

INSERT INTO vehicles (class) VALUES ('Garbage collector');
INSERT INTO vehicles (class) VALUES ('Street sweeper');
INSERT INTO drivingscore (score, vehicle_id) VALUES 
	(134.82, LAST_INSERT_ID()),
	(111.82, 1);

#INSERT INTO users (name) VALUES ('Bjarne'), ('Midjo');
