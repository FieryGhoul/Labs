create table Department(DeptNo numeric(10), DeptName varchar(30), Location varchar(30));
create table Employee(EmpNo numeric(6), EmpName varchar(30), Gender char(1), Salary numeric(6,2), Address varchar(30), DNo numeric(10));


alter table Employee add constraint pk primary key(EmpNo);
alter table Employee modify EmpName varchar(30) not null;
alter table Employee modify Gender char(1) not null;
alter table Employee modify Salary numeric(6,2) not null;
alter table Employee modify Address varchar(30) not null;
alter table Employee modify Gender char(1) check(Gender in('M','F'));

alter table Department add constraint dpk primary key(DeptNo);
alter table Department add constraint dun unique(DeptName);

alter table Employee add constraint dfk foreign key(DNo) references Department(DeptNo);

insert into Department values(2226,'CSE','Udupi');
insert into Department values(2227,'ECE','Banglore');
insert into Department values(2228,'CCE','Manglore');

insert into Employee values(123,'ABC','M',1234.56,'Udupi',2226);
insert into Employee values(456,'DEF','F',2345.67,'Banglore',2227);
insert into Employee values(789,'GHI','M',3456.78,'Manglore',2227);
insert into Employee values(012,'JKL','F',4567.89,'Manipal',2228);
insert into Employee values(345,'MNO','M',5678.90,'Delhi',2227);

insert into Employee values(345,'MNO','M',5678.90,'Delhi',2237);
insert into Department values(2228,'CCE',Manglore);
insert into Employee values(456,'DEF','F',23445.67,'Banglore',2227);

delete from Employee where DNo=2227 and Address in ('Banglore','Delhi');

alter table Employee drop constraint dfk;
alter table Employee add constraint dfk foreign key(DNo) references Department(DeptNo) on delete cascade;

alter table Employee modify Salary numeric(6,2) default(10000);
insert into Employee values(100,'DIV','M','Udupi',2226);
