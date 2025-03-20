
select Bdate, Address from employee1 where fname='John' and minit='B' and lname='Smith';

select p.pnumber, d1.dname, e1.lname, e1.address, e1.bdate from project p join dept_locations d on p.dnum=d.dnumber natural join department1 d1 join employee1 e1 on d1.mgr_ssn=e1.ssn where d.dlocation='Stafford';

select e1.fname emp_fname, e1.lname emp_lname, e2.fname sup_fname, e2.lname sup_lname from employee1 e1 join employee1 e2 on e1.ssn=e2.super_ssn;

select p.pnumber from project p join department1 d1 on d1.dnumber=p.dnum join employee1 e1 on e1.ssn=d1.mgr_ssn join works_on w on w.essn=e1.ssn where e1.lname='Smith';

select e1.salary*1.1 raise from project p join works_on w on w.pno=p.pnumber join employee1 e1 on w.essn=e1.ssn where p.pname='ProductX';

select * from project p join works_on w on w.pno=p.pnumber join employee1 e1 on e1.ssn=w.essn join department1 d1 on e1.ssn=d1.mgr_ssn order by d1.dname, e1.lname, e1.fname;

select e1.fname from employee1 e1 join dependent d on d.essn=e1.ssn where d.dependent_name=e1.fname and d.sex=e1.sex;

select e1.fname from employee1 e1 left outer join dependent d on d.essn=e1.ssn where d.essn is NULL;

select distinct e1.fname from dependent d join employee1 e1 on e1.ssn=d.essn join department1 d1 on e1.ssn=d1.mgr_ssn;

select sum(salary) sum, max(salary) max, min(salary) min, avg(salary) avg from employee1;

select p.pnumber, p.pname, count(w.essn) no from project p join works_on w on w.pno=p.pnumber group by(p.pnumber, p.pname);

select p.pnumber, p.pname, count(w.essn) no from project p join works_on w on w.pno=p.pnumber group by(p.pnumber, p.pname) having count(w.essn)>2;

select dno, count(*) no from employee1 where salary>40000 group by dno having  count(*)>1;
