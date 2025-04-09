
create table salary_raise(Instructor_Id numeric(5), Raise_date date, Raise_amt numeric(8,2));

INSERT INTO salary_raise VALUES (33456, TO_DATE('2005-07-07', 'YYYY-MM-DD'), 10000);

set serveroutput on
	
declare 
cursor c is (select * from instructor) for update;
dname instructor.dept_name%TYPE;
begin
dname:='&dept_name';
for i in c loop
if i.dept_name=dname then
	update instructor set salary = salary*1.05 where current of c;
	insert into salary_raise values(i.id, current_date, i.salary);
end if;
end loop;
end;
/




  

set serveroutput on
declare 
cursor c is select * from student order by tot_cred;
begin
for i in c loop
	exit when c%rowcount>10;
	dbms_output.put_line(i.id||' '||i.name||' '||i.dept_name||' '||i.tot_cred);
end loop;
end;
/


  

set serveroutput on
declare
	cursor c is select c.course_id, c.title, c.dept_name, c.credits, t.name, s.building, s.room_number, s.time_slot_id, count(*) tot_student_no 
	from department d 
	join course c on c.dept_name=d.dept_name 	
	join section s on c.course_id=s.course_id 
	join instructor t on d.dept_name=t.dept_name 
	group by c.course_id, c.title, c.dept_name, c.credits, t.name, s.building, s.room_number, s.time_slot_id;
begin
for i in c loop
	dbms_output.put_line(i.course_id||' '||i.title||' '||i.dept_name||' '||i.credits||' '||i.name||' '||i.building||' '||i.room_number||' '||i.time_slot_id||' '||i.tot_student_no);
end loop;
end;
/



  
set serveroutput on
declare
	cursor c is select c.id, c.name, c.dept_name, c.tot_cred 
	from student c 
	join takes t on t.id=c.id 
	where t.course_id='CS101';
begin
for i in c loop
	dbms_output.put_line(i.id||' '||i.dept_name||' '||i.name||' '||i.tot_cred);
	if (i.tot_cred<30) then 
		delete from takes where course_id = 'CS101';
		dbms_output.put_line('Deleted succesfully');
end if;
end loop;
end;
/



  
update student1 set lettergrade='F';
select * from student1;

set serveroutput on
declare 
cursor c is select * from student1;
begin
for i in c loop
	if (i.gpa<4 and i.gpa>=0) then
		update student1 set lettergrade='F' where rollno=i.rollno;
	elsif (i.gpa<5 and i.gpa>=4) then
		update student1 set lettergrade='E' where rollno=i.rollno;
	elsif (i.gpa<6 and i.gpa>=5) then
		update student1 set lettergrade='D' where rollno=i.rollno;
	elsif (i.gpa<7 and i.gpa>=6) then
		update student1 set lettergrade='C' where rollno=i.rollno;
	elsif (i.gpa<8 and i.gpa>=7) then
		update student1 set lettergrade='B' where rollno=i.rollno;
	elsif (i.gpa<9 and i.gpa>=8) then
		update student1 set lettergrade='A' where rollno=i.rollno;
	elsif (i.gpa<=10 and i.gpa>=9) then
		update student1 set lettergrade='A+' where rollno=i.rollno;
	else
		dbms_output.put_line('ERROR');
end if;
end loop;
end;
/



  
set serveroutput on
declare 
	cursor c is select id, course_id 
	from takes 
	group by id,course_id;
begin
for i in c loop
	dbms_output.put_line(i.id||' '||i.course_id);
end loop;
end;
/



  
set serveroutput on
declare
	cursor c is select s.id from takes s, advisor a, teaches i 
	where s.course_id=i.course_id 
	and s.id=a.s_iD 
	and i.id=a.i_id;
begin
for i in c loop
	dbms_output.put_line(i.id);
end loop;
end;
/
