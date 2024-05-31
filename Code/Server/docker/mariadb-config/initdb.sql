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

CREATE TABLE ecoscore (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	td TIMESTAMP,
	total_impact_score FLOAT,
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

CREATE TABLE toll (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	info VARCHAR(255),
	recorded_date TIMESTAMP,
	car_id INT UNSIGNED,
    CONSTRAINT `fk_toll_vehicles`
      FOREIGN KEY (car_id) REFERENCES vehicles (id)
      ON DELETE SET NULL
      ON UPDATE CASCADE
) ENGINE=InnoDB;

CREATE TABLE powerprices (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	NOK_per_kWh FLOAT
) ENGINE=InnoDB;

CREATE TABLE coupling (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	tr_id INT UNSIGNED,
	toll_id INT UNSIGNED,
	pcost_id INT UNSIGNED,
	CONSTRAINT FOREIGN KEY (tr_id) REFERENCES transactions(id)
	  ON DELETE SET NULL
      ON UPDATE CASCADE,
    CONSTRAINT FOREIGN KEY (toll_id) REFERENCES toll(id)
      ON DELETE SET NULL
      ON UPDATE CASCADE,
    CONSTRAINT FOREIGN KEY (pcost_id) REFERENCES powerprices(id)
) ENGINE=InnoDB;



INSERT INTO users (name, email, address) VALUES
	('Erlend Ferkingstad', 'erlend@mail.no', 'Fjellheimen 12C'),
	('Artur Jakobsen', 'artur@gmail.com', 'Sjøbakken 15'),
	('Solveig Karimi', 'solveig@gmail.com', 'Grønnhagen 42');

INSERT INTO drivescores (score, user_id) VALUES
	(134.82, 1),
	(111.82, 1);

INSERT INTO vehicles (class) VALUES ('Gasoline');
INSERT INTO vehicles (class, owner_id) VALUES ('Electric',1);
INSERT INTO vehicles (class) VALUES ('Street sweeper');


/* eksempel på å finne alle scores knyttett 
 * til en bruker og lagre gjennomsnittet */

INSERT INTO rentrecords (start_date, average_score, user_id)
SELECT '2024-03-21', AVG(score), 1 
FROM drivescores
WHERE user_id = 1;


INSERT INTO ecoscore (total_impact_score, user_id) VALUES (124451.1, 1);

INSERT INTO transactions (amount, user_id) VALUES (165, 1);

SELECT * FROM transactions t;

SELECT * FROM toll t;

INSERT INTO toll (info, car_id) VALUES ("it went good", 1);

INSERT INTO powerprices (NOK_per_kWh) VALUES (193.33);

INSERT INTO coupling (tr_id, toll_id, pcost_id) VALUES
	(1, NULL, 1),
	(1, 1, NULL),
	(1, NULL, NULL);


SELECT * FROM powerprices p;


START TRANSACTION;
INSERT INTO toll (info, car_id)
  VALUES ('ask for price', 1);
SET @toll_id = LAST_INSERT_ID();
INSERT INTO powerprices (NOK_per_kWh)
  VALUES (0.211);
INSERT INTO tcoupling (t_id, toll_id, pcost_id)
SELECT NULL, @toll_id, MAX(id) FROM powerprices;
COMMIT;