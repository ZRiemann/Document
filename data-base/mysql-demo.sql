-- Simple query
SELECT VERSION(), CURRENT_DATE, NOW(), USER();
select "simple-calculator", sin(pi()/4), (4+1)*5;
-- SELECT "SHOW VARIABLES LIKE 'validate_password.%'";
SHOW VARIABLES LIKE 'validate_password.%';

-- 3.3 Creating and Using Database
-- Find out what databases currently exist on the server:
show databases;
-- access the data base
use mysql;
-- GRANT ALL ON menagerie.* TO 'your_mysql_name'@'your_client_host';

-- 3.3.1 Creating and Selecting a Database
create database test;
-- access data base test
use test;
-- show which database is current selected using
select database();

-- 3.3.2 Creating a Table
show tables;
create table pet (name VARCHAR(20), owner VARCHAR(20),
       species VARCHAR(20), sex CHAR(1), birth DATE, death DATE);
show tables;
describe pet;

-- 3.3.3 Loading data into a table
LOAD DATA LOCAL INFILE './pet.txt' INTO TABLE pet;
INSERT INTO pet VALUES ('Puffball','Diane','hamster','f','1999-03-30',NULL);

-- 3.3.4 Retrieving Infomation from a table
select * from pet;
SELECT * FROM pet WHERE name = 'Bowser';
SELECT * FROM pet WHERE birth >= '1998-1-1';
SELECT * FROM pet WHERE species = 'snake' OR species = 'bird';