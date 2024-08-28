-- Create Tables

CREATE TABLE member(
memID VARCHAR(4) UNIQUE,
uname VARCHAR(18),
pass  VARCHAR(20),
PRIMARY KEY(memID),
CHECK(memID LIKE('m%'))
);

CREATE TABLE book(
bookID VARCHAR(4) UNIQUE,
title  VARCHAR(50),
available BOOLEAN,
PRIMARY KEY(bookID)
CHECK(bookID LIKE('b%'))
);

CREATE TABLE borrow(
memID VARCHAR(4), 
bookID VARCHAR(4),
FOREIGN KEY(memID) REFERENCES member(memID),
FOREIGN KEY(bookID) REFERENCES member(bookID),
PRIMARY KEY(memID, bookID),
CHECK(bookID LIKE('b%')),
CHECK(memID LIKE('m%'))
);

-- sample values
/*
INSERT INTO book VALUES
('b000', 'Lord Of The Mysteries', true),
('b005', 'Legendary Mechanic', true),
('b7', 'Overlord', true),
('b8', 'Astral Apostle', true),
('b007', 'Fire Mage', true);
*/
