select c.course_id from course c, section s where s.semester='Fall' and s.year=2009 and s.course_id=c.course_id union select c.course_id from course c, section s where s.semester='Spring' and s.year=2010 s.course_id=c.course_id

select c.title from course c, section s where s.semester='Fall' and s.year=2009 and s.course_id=c.course_id intersect select c.title from course c, section s where s.semester='Spring' and s.year=2010 and s.course_id=c.course_id; 

select c.title from course c, section s where s.semester='Fall' and s.year=2009 and s.course_id=c.course_id minus select c.title from course c, section s where s.semester='Spring' and s.year=2010 and s.course_id=c.course_id; 

select title from course minus select c.title from course c,takes t where t.course_id=c.course_id;

select distinct course_id from takes t where semester='Fall' and year=2009 and course_id in (select distinct course_id from takes t where semester='Spring' and year=2010);

select count(*) from takes where course_id in (select course_id from teaches where ID=10101);

select distinct course_id from takes t where semester='Fall' and year=2009 and course_id not in (select distinct course_id from takes t where semester='Spring' and year=2010);

select name from student where name in (select name from instructor);

select name from instructor where salary >= some (select salary from instructor where dept_name = 'Biology');

select name from instructor where salary > all (select salary  from instructor where dept_name='Biology');

select dept_name, avg(salary) from instructor group by dept_name having avg(salary) = all(select max(avg(salary)) from instructor group by dept_name);

select dept_name from department where budget < all (select avg(salary) from instructor);

select c.title from course c, takes t where c.course_id=t.course_id and t.semester='Fall' and t.year=2009 and exists (select c.title from course c, takes t where c.course_id=t.course_id and t.semester='Spring' and t.year=2010);

select id from student where not exists((select course_id from course where dept_name='Biology') minus (select c.course_id from course c, takes t where c.course_id=t.course_id));

select course_id from section where year = 2009 group by course_id having count(course_id) <= 1;



select dept_name, avg(salary) from instructor group by dept_name having avg(salary) > 42000;

create view all_courses as 
select s.course_id, s.semester, s.year, s.building, s.room_number
from section s
join course c on s.course_id = c.course_id
where c.dept_name = 'Physics' and s.semester = 'Fall' and s.year = 2009;


select * from all_courses;

create view department_total_salary as
   select d.dept_name, sum(i.salary) as total_salary
   from department d
   join instructor i on d.dept_name = i.dept_name
   group by d.dept_name;

   select * from department_total_salary;
