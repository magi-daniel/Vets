
DROP DATABASE IF EXISTS veterinar;
CREATE DATABASE IF NOT EXISTS veterinar;
USE veterinar;

SELECT 'CREATING DATABASE STRUCTURE' as 'INFO';

DROP TABLE IF EXISTS owners,
                     pets;

CREATE TABLE owners (
    number_of_owner     INT             NOT NULL,
    first_name          VARCHAR(15)     NOT NULL,
    last_name           VARCHAR(15)     NOT NULL,
    PRIMARY KEY (number_of_owner)
);

CREATE TABLE pets (
    number_of_pet       INT             NOT NULL,
    pet_name            VARCHAR(15)     NOT NULL,
    type_pet            VARCHAR(15)      NOT NULL,
    number_of_owner     INT             NOT NULL,
    PRIMARY KEY (number_of_pet),
    FOREIGN KEY (number_of_owner) REFERENCES owners (number_of_owner) ON DELETE CASCADE
);

SELECT 'LOADING owners' as 'INFO';
source load_owners.dump ;
SELECT 'LOADING pets' as 'INFO';
source load_pets.dump ;