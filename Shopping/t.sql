all sql codes

create database db;
select db;
create table users(
cid int primary key,
username varchar(6) unique,
usertype int not null,
password varchar(10)
);
-- % types: 0 admin 1 staff 2 customer
-- % create an admin user 
insert into users values(69,'admin',0,'meow');
