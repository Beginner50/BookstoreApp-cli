-- Create Tables

/*
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
*/

-- sample values
/*
INSERT INTO member VALUES
('m001', 'Francois', 'h3avenS3eker'),
('m002', 'Petroy', 'Dmitri444'),
('m003', 'Jiang', '123456');

INSERT INTO book VALUES
('b000', 'Lord Of The Mysteries', true),
('b001', 'Shadow Slave', true),
('b002', 'Reverend Insanity', false),
('b003', 'Florida Man', true),
('b005', 'Legendary Mechanic', true),
('b006', 'Overgeared', true),
('b7', 'Overlord', true),
('b8', 'Astral Apostle', true),
('b007', 'Fire Mage', true);

INSERT INTO borrow VALUES
('m001', 'b001' ),
('m002', 'b004' ),
('m002', 'b003' )
;
*/

SELECT * FROM member;
SELECT * FROM book;
SELECT * FROM borrow;