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
	class VARCHAR(255),
	owner_id INT
) ENGINE=InnoDB;

CREATE TABLE drivescores (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	ts TIMESTAMP,
	score FLOAT NOT NULL,
	user_id INT UNSIGNED,
	CONSTRAINT `fk_drivescores_users`
      FOREIGN KEY (user_id) REFERENCES users (id)
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

INSERT INTO users (name, email, address) VALUES
	('Arne Midjo', 'arne.midjo@mail.no', 'ntnubakken 12C'),
	('Mrne Aidjo', 'mrne@gmail.com', 'utnudalen 18C');

INSERT INTO drivescores (score, user_id) VALUES 
	(134.82, 1),
	(111.82, 1);

INSERT INTO vehicles (class) VALUES ('Garbage collector');
INSERT INTO vehicles (class, owner_id) VALUES ('Personal',1);
INSERT INTO vehicles (class) VALUES ('Street sweeper');


/* eksempel på å finne alle scores knyttett 
 * til en bruker og lagre gjennomsnittet */

INSERT INTO rentrecords (start_date, average_score, user_id)
SELECT '2024-03-21', AVG(score), 1 
FROM drivescores
WHERE user_id = 1;


