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













// 9. List all Students with names and their department names.
// 10. List all instructors in CSE department.
// 11. Find the names of courses in CSE department which have 3 credits.
// 12. For the student with ID 12345 (or any other value), show all course-id and title of all courses registered for by the student
// 13. List all the instructors whose salary is in between 40000 and 90000.

9.	select name, dept_name from Student;
10.	select * from instructor where dept_name='Comp. Sci.';
11.	select title from course where dept_name='Comp. Sci.' and credits=3;
12.	select c.Course_id, c.title from student s, course c where s.ID=12345;
13.	select * from instructor where salary between 40000 and 90000;

// 14. Display the IDs of all instructors who have never taught a course.
// 15. Find the student names, course names, and the year, for all students those who have attended classes in room-number 103.

14.	select i.id from instructor i, teaches t where i.id not in t.id;
15.	select s.name, c.title, t.year from student s, course c, section cl, takes t where cl.room_number=103 and cl.course_id=t.course_id and t.id=s.id and t.course_id=s.course_id;

// 16. For all students who have opted courses in 2010, find their names and course id’s with the attribute course title replaced by c-name.
// 17. Find the names of all instructors whose salary is greater than the salary of at least one instructor of CSE department and salary replaced by inst-salary.

16.	select s.name, c.title as c_name from student s, course c, section t where t.year=2010;
17.	select i.name, i.salary as inst_salary from instructor i, instructor j where j.dept_name='Comp. Sci.' and i.salary>j.salary;

// 18. Find the names of all instructors whose department name includes the substring ‘ic’.

18.	select name from instructor where dept_name like '%ic%';

// 19. List the student names along with the length of the student names.
// 20. List the department names and 3 characters from 3rd position of each department name
// 21. List the instructor names in upper case.
// 22. Replace NULL with value1(say 0) for a column in any of the table 
// 23. Display the salary and salary/3 rounded to nearest hundred from Instructor.

19.	select name, length(name) from student ;
20.	select dept_name, substr(dept_name,3,3) from department;
21.	select upper(name) from instructor;
22.	SELECT NVL(NULL, 0) AS start_min FROM time_slot;
23. 	select salary,round(salary/3) from instructor;

