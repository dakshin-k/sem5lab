all sql codes

create database db;
select db;
create table users(
username varchar(25) unique,
usertype int not null,
password varchar(10),
cid int auto_increment primary key
);
-- % types: 0 admin 1 staff 2 customer
-- % create an admin user 
insert into users values('admin',0,'meow',null);

create table staff(id int primary key references users.cid,
name varchar(20),city varchar(20));

create table products(pid int auto_increment, primary key
);