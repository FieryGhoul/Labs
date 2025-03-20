select course_id, count(id)from takes group by course_id;

select dept_name, avg(count)
    from (
        select c.dept_name, count(t.id) as count
        from takes t
        join course c on t.course_id = c.course_id
        group by c.dept_name, t.course_id) department count
    group by dept_name having avg(count) > 10;
	
select dept_name, count(course_id) from course group by dept_name;

select dept_name, avg(i.salary) from department d join instructor i on d.dept_name = i.dept_name group by d.dept_name having avg(i.salary) > 42000;

select s.course_id, s.sec_id, count(distinct t.id) as enrollment from section s join takes t on s.course_id = t.course_id and s.sec_id = t.sec_id where s.semester = 'Spring' and s.year = 2009 group by s.course_id, s.sec_id;

select c.course_id, p.prereq_id from prereq p join course c on p.course_id = c.course_id order by c.course_id asc;

select * from instructor order by i.salary desc;

select dept_name, sum(salary) from instructor group by dept_name
having sum(salary) = (select max(sum(salary)) from instructor group by dept_name); 	

select dept_name, avg(salary) as avg_salary from instructor group by dept_name having avg(salary) > 42000;

select s.sec_id, count(t.id) as enrolment from section s join takes t on s.course_id = t.course_id and s.sec_id = t.sec_id and s.semester = 'Spring' and s.year = 2010 group by s.course_id, s.sec_id having count(t.id) = (select max(enrolment) from (select count(id) as enrolment from takes group by course_id, sec_id) enrolments);

select i.name
from instructor i
join teaches t on i.ID = t.ID
join student s on t.ID = s.ID
join course c on t.course_id = c.course_id
where c.dept_name = 'CSE'
group by i.name
having count(distinct s.ID) = (select count(distinct s2.ID)
                                from student s2
                                where s2.dept_name = 'CSE');


select dept_name, avg(salary)
from instructor
group by dept_name
having avg(salary) > 50000 and count(ID) > 5;

with max_budget as (select max(budget) as max_budget_value from department) select dept_name,budget from department,max_budget where department.budget=max_budget.max_budget_value;

with total_salaries as (select dept_name,sum(salary) as total_salary from instructor group by dept_name), avg_salary as (select avg(total_salary) as avg_total_salary from total_salaries) select t.dept_name,t.total_salary from total_salaries t,avg_salary a where t.total_salary>a.avg_total_salary;


UPDATE student
SET dept_name = 'IT'
WHERE dept_name = 'CSE';

UPDATE instructor
SET salary = CASE
                WHEN salary > 100000 THEN salary * 1.03
                ELSE salary * 1.05
          





