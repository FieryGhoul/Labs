create table employee (
    empno number primary key,
    empname varchar(100) not null,
    gender char(1) check (gender in ('m', 'f')) not null,
    salary numeric(10, 2) not null,
    address varchar(255) not null,
    dno number
);

create table department (
    deptno number primary key,
    deptname varchar(100) unique,
    location varchar(100)
);

alter table employee add constraint dfk foreign key(dno) references department(deptno);

insert into department values(2226, 'cse', 'udupi');
insert into department values(2227, 'ece', 'banglore');
insert into department values(2228, 'cce', 'manglore');
insert into employee values(123, 'abc', 'm', 1234.56, 'udupi', 2226);
insert into employee values(456, 'def', 'f', 2345.67, 'banglore', 2227);
insert into employee values(789, 'ghi', 'm', 3456.78, 'manglore', 2227);
insert into employee values(012, 'jkl', 'f', 4567.89, 'manipal', 2228);
insert into employee values(345, 'mno', 'm', 5678.90, 'delhi', 2227);

insert into employee values(345, 'mno', 'm', 5678.90, 'delhi', 2237);  -- This will fail because 2237 doesn't exist in Department.
insert into department values(2228, 'cce', 'manglore');  -- This will fail because deptno 2228 already exists.
insert into employee values(456, 'def', 'f', 23445.67, 'banglore', 2227);  -- This will fail if the record already exists with the same primary key.

delete from employee where dno = 2227 and address in ('banglore', 'delhi');

alter table employee drop constraint dfk;
alter table employee add constraint dfk foreign key(dno) references department(deptno) on delete cascade;

alter table employee modify salary default 10000;

select name, dept_name from Student;
select * from instructor where dept_name='Comp. Sci.';
select title from course where dept_name='Comp. Sci.' and credits=3;
select c.Course_id, c.title from student s, course c where s.ID=12345;
select * from instructor where salary between 40000 and 90000;

select i.id from instructor i, teaches t where i.id not in t.id;
select s.name, c.title, t.year from student s, course c, section cl, takes t where cl.room_number=103 and cl.course_id=t.course_id and t.id=s.id and t.course_id=s.course_id;

select s.name, c.title as c_name from student s, course c, section t where t.year=2010;
select i.name, i.salary as inst_salary from instructor i, instructor j where j.dept_name='Comp. Sci.' and i.salary>j.salary;

select name from instructor where dept_name like '%ic%';

select name, length(name) from student ;
select dept_name, substr(dept_name,3,3) from department;
select upper(name) from instructor;
SELECT NVL(NULL, 0) AS start_min FROM time_slot;
select salary,round(salary/3) from instructor;

