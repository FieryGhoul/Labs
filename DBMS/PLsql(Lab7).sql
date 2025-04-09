create table student(rollno numeric(1), gpa numeric(2,1));
insert into student values(1,5.8);
insert into student values(2,6.5);
insert into student values(3,3.4);
insert into student values(4,7.8);
insert into student values(5,9.5);



declare 
	roll student.rollno%TYPE;
	gr student.gpa%TYPE;
	begin
		roll:='&roll';
		select gpa into gr from student where rollno=roll;
		dbms_output.put_line('Grade for roll : '||roll||' is '||gr); 
end;
/



  
declare 
rollvar student.rollno%TYPE;
gr student.gpa%TYPE;
begin
	rollvar:='&roll';
	select gpa into gr from student where rollno=rollvar;
	if (gr<4 and gr>=0) then
		dbms_output.put_line('Grade : F');
	elsif (gr<5 and gr>=4) then
		dbms_output.put_line('Grade : E');
	elsif (gr<6 and gr>=5) then
		dbms_output.put_line('Grade : D');
	elsif (gr<7 and gr>=6) then
			dbms_output.put_line('Grade : C');
	elsif (gr<8 and gr>=7) then
		dbms_output.put_line('Grade : B');
	elsif (gr<9 and gr>=8) then
		dbms_output.put_line('Grade : A');
	elsif (gr<=10 and gr>=9) then
		dbms_output.put_line('Grade : A+');
	else
	dbms_output.put_line('ERROR');
end if;
end;
/



create table book(id numeric(3), name varchar(10), late numeric(2));
insert into book values(101,'DBMS',28);
insert into book values(102,'MATHS',2);
insert into book values(103,'FLAT',16);
insert into book values(104,'DAA',12);
insert into book values(105,'ES',21);

declare
fine numeric(3);
idvar book.id%TYPE;
namevar book.name%TYPE;
dayvar book.late%TYPE;
	begin
		idvar:='&id';
		namevar:='&name';
		select late into dayvar from book where id=idvar and name=namevar;
			if (dayvar<=7) then 
				dbms_output.put_line('Fine : NIL');
			elsif(dayvar>=8 and dayvar<=15) then 
				dbms_output.put_line('Fine : '||dayvar*1);
			elsif(dayvar>=16 and dayvar<=30) then 
				dbms_output.put_line('Fine : '||dayvar*2);
			else 
				dbms_output.put_line('Fine : '||dayvar*5);
end if;
end;
/




declare
flag numeric(1); 
rollvar student.rollno%TYPE;
gr student.gpa%TYPE;
begin
	flag:=0;
	loop
	flag:=flag+1;
	select gpa into gr from student where rollno=flag;
	if (gr<4 and gr>=0) then
		dbms_output.put_line('Grade : F');
	elsif (gr<5 and gr>=4) then
		dbms_output.put_line('Grade : E');
	elsif (gr<6 and gr>=5) then
		dbms_output.put_line('Grade : D');
	elsif (gr<7 and gr>=6) then
		dbms_output.put_line('Grade : C');
	elsif (gr<8 and gr>=7) then
		dbms_output.put_line('Grade : B');
	elsif (gr<9 and gr>=8) then
		dbms_output.put_line('Grade : A');
	elsif (gr<=10 and gr>=9) then
		dbms_output.put_line('Grade : A+');
	elsif(flag>5) then exit;

	else
		dbms_output.put_line('ERROR');
end if;
end loop;
end;
/



  
declare 
flag numeric(1); 
gr student.gpa%TYPE;
begin
	flag:=0;
	while (flag<6)
	loop
	flag:=flag+1;
	select gpa into gr from student where rollno=flag;
	if (gr<4 and gr>=0) then
		update student set lettergrade='F' where rollno=flag;
	elsif (gr<5 and gr>=4) then
		update student set lettergrade='E' where rollno=flag;
	elsif (gr<6 and gr>=5) then
		update student set lettergrade='D' where rollno=flag;
	elsif (gr<7 and gr>=6) then
		update student set lettergrade='C' where rollno=flag;
	elsif (gr<8 and gr>=7) then
		update student set lettergrade='B' where rollno=flag;
	elsif (gr<9 and gr>=8) then
		update student set lettergrade='A' where rollno=flag;
	elsif (gr<=10 and gr>=9) then
		update student set lettergrade='A+' where rollno=flag;
	else
		dbms_output.put_line('ERROR');
end if;
end loop;
end;
/




  

--6. Write a PL/SQL block to find the student with max. GPA without using aggregate function.
DECLARE
    max_gpa student.gpa%TYPE := 0;
    max_rollno student.rollno%TYPE := NULL;
    current_gpa student.gpa%TYPE;
BEGIN
    FOR sr IN (SELECT rollno FROM student) LOOP
        BEGIN
            SELECT gpa INTO current_gpa FROM student WHERE rollno = sr.rollno;
            IF current_gpa > max_gpa THEN
                max_gpa := current_gpa;
                max_rollno := sr.rollno;
            END IF;
        EXCEPTION
            WHEN NO_DATA_FOUND THEN
                -- Handle the case where no data is found, if necessary
                NULL;
        END;
    END LOOP;

        DBMS_OUTPUT.PUT_LINE('Roll ' || max_rollno || ' has the maximum GPA of ' || max_gpa);
END;
/




  
declare
flag numeric(1); 
rollvar student.rollno%TYPE;
gr student.gpa%TYPE;
begin
	flag:=0;
	loop
	flag:=flag+1;
	select gpa into gr from student where rollno=flag;
	if (gr<4 and gr>=0) then
		GOTO fg;
	elsif (gr<5 and gr>=4) then
		dbms_output.put_line('Grade : E');
	elsif (gr<6 and gr>=5) then
		dbms_output.put_line('Grade : D');
	elsif (gr<7 and gr>=6) then
			dbms_output.put_line('Grade : C');
	elsif (gr<8 and gr>=7) then
		dbms_output.put_line('Grade : B');
	elsif (gr<9 and gr>=8) then
		dbms_output.put_line('Grade : A');
	elsif (gr<=10 and gr>=9) then
		dbms_output.put_line('Grade : A+');
	elsif(flag>5) then exit;
	else
		dbms_output.put_line('ERROR');

end if;
end loop;
<<fg>> dbms_output.put_line('Grade : F');
end;
/
