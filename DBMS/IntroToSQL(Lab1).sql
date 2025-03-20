create table employee(
    emp_no number(5),
    emp_name varchar(20),
    emp_address varchar(100));

insert into employee values(10001,'Tushar Pathak','Bangalore');
insert into employee values(10002,'Aditya Kumar','Mumbai');
insert into employee values(10003,'Aditya Singh','Punjab');
insert into employee values(10004,'Aditya Khare','Madhya Pradesh');
insert into employee values(10005,'Aditya Bannerjee','West Bengal');

select * from employee;

select * from employee where EMP_ADDRESS = 'Manipal';

alter table employee add (Salary number(10,2));

UPDATE employee SET salary = 50000;

desc employee;

delete from employee where EMP_ADDRESS = 'Mangalore';

rename employee to employee1;

drop table employee1;

