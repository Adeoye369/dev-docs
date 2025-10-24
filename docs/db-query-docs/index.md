
# Basic Querying

# CREATING, INSERT, UPDATE A TABLE

```sql
CREATE TABLE shop001_database.grad_student
(id INTEGER PRIMARY KEY NOT NULL,
  name VARCHAR(100) NOT NULL,
  age INT NOT NULL,
  balance DOUBLE,
  is_admin BOOLEAN,
  student_id INT
  );
```

```sql
-- Inserting into a table
INSERT INTO shop001_database.students (id, name, age, balance, is_admin, student_id) 
VALUES (1,'Adeoye', 34, 45.34, 0, 1)

INSERT INTO shop001_database.students(id, name, age, balance, is_admin, student_id)
VALUES (3, "Anifowose", 45, 4000, 1, 4563);

INSERT INTO shop001_database.students(id, name, age, balance, is_admin, student_id)
VALUES (2, "Majekodunmi", 30, 15000, 0, 5530);

-- Inserting multiple values at a time

INSERT INTO shop001_database.students (id, name, age, balance, is_admin, student_id)
VALUES (4, "Omobaba", 45, 4000, 0, 1232),
       (6, "Funmu",  33,   1000, 0, 9111),
       (7, "Ikechi",  43,  11000, 1, 9101);

-- Updating a table
UPDATE shop001_database.students SET student_id = 1231 WHERE id = 1;
UPDATE shop001_database.students SET name="Adegbite Adeoye" WHERE id =1;
```

## RENAME, CHANGE, MODIFY and ADD

```sql
-- ### RENAME TABLE ### ---
ALTER TABLE grad_student RENAME TO grad_students;

-- CHANGING COLUMN name ----
-- ALTER TABLE [table_name] CHANGE COLUMN [old_name] [new_name] [data_type];
ALTER TABLE shop001_database.students 
CHANGE COLUMN age stu_age MEDIUMINT;

-- #### ADDING A NEW COLUMN to Table ####
-- ALTER TABLE [table_name] ADD COLUMN [column_name] [data_type, constraints];
ALTER TABLE shop001_database.students 
ADD COLUMN email VARCHAR(150);

ALTER TABLE shop001_database.students 
ADD COLUMN email VARCHAR(200) NOT NULL DEFAULT 'www@mail.com';

-- MODIFYING EXISTING COLUMN DATA TYPE
ALTER TABLE shop001_database.students
MODIFY email TEXT;

-- DELETING A COLUMN
ALTER TABLE shop001_database.students 
DROP COLUMN email;


--- ### CONSTRAINT ### ---
-- ADDING UNQUE CONSTRAINT
ALTER TABLE shop001_database.students
ADD CONSTRAINT uc_email UNIQUE (email);

-- DELETING DROPPING CONSTRAINT
ALTER TABLE shop001_database.grad_student
DROP constraint `grad_student_ibfk_1`;

```

## MAKING AN EXISTING COLUMN A FOREIGN KEY

* **Identify the referenced column(s):** Determine which column(s) in the students table are being referenced by your foreign key `fk_student_id`. 
    This is typically the student_id column in the students table.
* **Add a primary key or unique index:** If the referenced column(s) are not already part of a primary key or a unique index,
    you need to create one.

If `student_id `should be the primary key in students:

```sql
        ALTER TABLE students
        ADD PRIMARY KEY (student_id);
```

If student_id is not the primary key but needs to be unique for the foreign key:

```sql
        CREATE UNIQUE INDEX idx_student_id ON students (student_id);
```

* **Adding the foreign key constraint:** After creating the necessary index, 
attempt to add the foreign key constraint again.

```sql
    ALTER TABLE your_child_table
    ADD CONSTRAINT fk_student_id
    FOREIGN KEY (student_id_in_child_table)
    REFERENCES students (student_id);
```

### Important considerations - Data types and collation

 Ensure that the data type and collation of the foreign key column in the child table exactly match those of the referenced column(s) in the parent table.

#### EXAMPLE

```sql
--  First make sure the referenced key has a UNIQUE INDEX,
-- If its a primary key, it will have that by default but if not, you will have to set it


-- EXAMPLE :

CREATE UNIQUE INDEX ui_student_id ON shop001_database.students(student_id);

ALTER TABLE shop001_database.grad_students
ADD CONSTRAINT fk_student_id 
FOREIGN KEY (student_id) REFERENCES shop001_database.students(student_id)
ON DELETE CASCADE
ON UPDATE CASCADE;
```

## SHOW TABLE INFO

```sql
SHOW CREATE TABLE shop001_database.students;
 -- RESULT:
 -- 'students', 'CREATE TABLE `students
 --` (\n  `id` int NOT NULL,\n  `name` varchar(100) NOT NULL,\n  
 -- `stu_age` mediumint DEFAULT NULL,\n  `balance` double DEFAULT NULL,\n  
 -- `is_admin` tinyint(1) DEFAULT NULL,\n  `student_id` int DEFAULT NULL,\n  
 -- `email` varchar(150) DEFAULT NULL,\n  PRIMARY KEY (`id`),\n 
 --  UNIQUE KEY `student_id` (`student_id`)\n) 
 -- ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci'

```

## WHERE LIKE

```sql

-- LIKE used with '%'' helps filter by "starts with" (eg. BA%), "ends with" (eg. BA%) or "Contains" (e.g %BA%)
SELECT  * FROM sakila.actor WHERE first_name LIKE '%BA%' AND last_update >= "2006-01-01 00:00:00";
SELECT  * FROM sakila.actor WHERE last_update LIKE "2006-02%";

--similar LIKE used with underscore('_') filter by any character (e.g %E_) filter strings endswith E and any(1) character
-- NOTE: for 2 characters you can specify 2 underscore and for 3 characters 3 underscore and so on
SELECT  * FROM sakila.actor WHERE first_name LIKE "%E__";   

```

## GROUP BY

```sql
-- group by - is basically group all appearance of a row into a SET of UNIQUE or DISTINCT row values i.e without Duplicates
SELECT rental_duration, COUNT(rental_rate) FROM sakila.film group by rental_duration;

SELECT 
    rental_duration, COUNT(rental_rate), MIN(rental_rate), MAX(rental_rate), 
    AVG(rental_rate) FROM  sakila.film  group by rental_duration;

SELECT active, count(store_id) FROM sakila.customer GROUP BY active;
```

## ENUM VS SET IN sql

ENUM and SET are both string data types in SQL (primarily found in MySQL) that allow a column to store values from a predefined list. The key difference lies in the number of values they can hold:

### ENUM (Enumeration)

* Purpose: Stores a single value from a predefined list of permitted values.
* Analogy: Similar to a radio button where only one option can be selected.
* Internal Representation: Stored internally as integers, typically from 1 to 'n' (where 'n' is the number of members in the enumeration). An invalid entry might be represented by 0.
* Example: A column order_status could be defined as `ENUM('pending', 'processing', 'shipped', 'delivered')`. A row can only have one of these statuses.

### SET

* Purpose: Stores zero or more values from a predefined list of permitted values. It allows for multiple selections.
* Analogy: Similar to a checkbox where multiple options can be selected.
* Internal Representation: Stored internally as a bitmap, with each bit representing a member of the set. The values are powers of 2 (1, 2, 4, 8, etc.).
* Example: A column features could be defined as SET('wifi', 'parking', 'pool', 'gym'). A row could have 'wifi,parking' or 'pool' or 'wifi,gym,parking'. 

Key Differences Summarized:

| Feature | ENUM | SET |
|---------|-------|------|
|Values | Single value from the list | Zero or more values from the |
|Analogy | Radio button | Checkbox|
|Storage | Integers (1 to n) | Bitmap (powers of 2)|
|Use Case | Mutually exclusive options | Multiple, independent options|
|Max Members | Up to 65,535 members | Up to 64 members|

### When to Choose Which

Use ENUM when you need to restrict a column to a single, specific value from a fixed set of choices (e.g., `gender, day_of_week, product_category`).
Use SET when a column needs to store a combination of values from a predefined list (e.g., `user_permissions, product_tags, amenities_available`).


## Working with Foreign Keys

### Defining Foreign keys during table Creation

```sql
CREATE TABLE Customers (
    CustomerID INT PRIMARY KEY,
    CustomerName VARCHAR(50) NOT NULL
);

CREATE TABLE Orders (
    OrderID INT PRIMARY KEY,
    OrderNumber INT NOT NULL,
    CustomerID INT,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);
```

In this example, `CustomerID `in the Orders table is a foreign key
 that references `CustomerID (the primary key) `in the Customers table.

### Adding Foreign Key to an Existing table

```sql
ALTER TABLE Orders
ADD CONSTRAINT FK_CustomerOrder
FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID);
```

### Understanding ON DELETE and ON UPDATE Actions (Optional)

Foreign keys can also specify actions to take when the referenced primary key is updated or deleted:

* **`ON DELETE CASCADE`** : Deletes rows in the child table when the corresponding parent row is deleted.
* **`ON UPDATE CASCADE`** : Updates foreign key values in the child table when the corresponding primary key in the parent table is updated.
* **`ON DELETE SET NULL`** : Sets the foreign key column(s) to NULL in the child table when the corresponding parent row is deleted (if the foreign key column allows NULL values).
* **`ON DELETE RESTRICT (default)`** : Prevents deletion of a parent row if there are dependent rows in the child table.
* **`ON DELETE NO ACTION (default)`** : Similar to RESTRICT, preventing the action if dependent rows exist.

#### ON DELETE Example

```sql
CREATE TABLE Orders (
    OrderID INT PRIMARY KEY,
    OrderNumber INT NOT NULL,
    CustomerID INT,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID) ON DELETE CASCADE
);
```
