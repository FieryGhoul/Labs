create table log_change_Takes (
    Time_Of_Change timestamp default current_timestamp,
    ID varchar(5),
    course_id varchar(8),
    sec_id varchar(8),
    semester varchar(6),
    year numeric(4,0),
    grade varchar(2)
);


create or replace trigger triggerdata
after insert or update or delete on takes
for each row
begin
    if (inserted) then
        insert into log_change_Takes values (:new.ID, :new.course_id, :new.sec_id, :new.semester, :new.year, :new.grade);
    elsif (deleted) then
        insert into log_change_Takes values (:old.ID, :old.course_id, :old.sec_id, :old.semester, :old.year, :old.grade);
    end if;
end;











create table Old_Data_Instructor (
    ID varchar(5),
    name varchar(20),
    dept_name varchar(20),
    salary numeric(8,2)
);

create or replace trigger triggerdata
before update on instructor
for each row
begin
    if :old.salary != :new.salary then
        insert into Old_Data_Instructor	values(:old.ID,:old.name,:old.dept_name,:old.salary);
    end if;
end;
/










create or replace trigger triggerdata
before insert or update on instructor
for each row
declare
    dept_budget numeric(12,2);
begin
    if not regexp_like(:new.name, '^[A-Za-z]+$') then
        raise_application_error(-20001, 'only alphabets.');
    end if;

    if :new.salary <= 0 then
        raise_application_error(-20002, 'must be positive.');
    end if;

    select budget into dept_budget from department where dept_name = :new.dept_name;
    if :new.salary > dept_budget then
        raise_application_error(-20003, 'salary>department budget');
    end if;
end;










create table auditclient (
    client_no varchar(10),
    name varchar(50),
    bal_due numeric(10,2),
    operation varchar(10),
    userid varchar(20),
    opdate timestamp default current_timestamp
);

create or replace trigger triggerdata
before delete or update on client_master
for each row
declare
    v_operation varchar(10);
begin
    if deleting then
        v_operation := 'DELETE';
    elsif updating then
        v_operation := 'UPDATE';
    end if;

    insert into auditclient values (:old.client_no, :old.name, :old.bal_due, v_operation, user, current_timestamp);
end;








create or replace view Advisor_Student as
select a.s_ID, a.i_ID, s.name as student_name, i.name as instructor_name
from advisor a
join student s on a.s_ID = s.ID
join instructor i on a.i_ID = i.ID;

create or replace trigger triggerdata
instead of delete on Advisor_Student
for each row
begin
    delete from advisor where s_ID = :old.s_ID;
end;
