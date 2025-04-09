--q1
set serveroutput on
create or replace procedure print is
begin
dbms_output.put_line('"Good Day to You"');
end;
/

begin 
print;
end;
/

--if using oracle live use AUTHID CURRENT_USER
--create or replace procedure print AUTHID CURRENT_USER is






  





  
--q2
set serveroutput on
  
create or replace procedure list(name varchar) is
begin

    for i in (select name from instructor where dept_name = name) loop
        dbms_output.put_line(i.name);
    end loop;


    for i in (select title from course where dept_name = name) loop
        dbms_output.put_line(i.title);
    end loop;
end;
/


begin
    list('Comp. Sci.');
end;
/














  
--q3
create or replace procedure course_popular(dept_name varchar) is
    v_cid varchar(8);
    v_max number;
begin
    select s.course_id, count(*) into v_cid, v_max
    from takes t
    join section s on t.course_id = s.course_id 
                   and t.sec_id = s.sec_id 
                   and t.semester = s.semester 
                   and t.year = s.year
    join course c on s.course_id = c.course_id
    where c.dept_name = dept_name
    group by s.course_id
    order by count(*) desc
    fetch first row only;

    dbms_output.put_line( dept_name || ': ' || v_course_id || ' with ' || v_max || ' students.');

end;
/


begin
    course_popular('Comp. Sci.');
end;
/















  


  
--q4 
create or replace procedure list_students(p_dept_name varchar) is
begin
    for i in (select name from student where p_dept_name = dept_name) loop
        dbms_output.put_line(i.name);
    end loop;

    for i in (select title from course where p_dept_name = dept_name) loop
        dbms_output.put_line(i.title);
    end loop;
end;
/


begin
    list_students('Comp. Sci.');
end;
/



















--q5
set serveroutput on
create or replace function sqnum(num number)return number as
begin
    return num * num;
end;
/

declare 
    v_result number;
begin
    v_result := sqnum(5);
    dbms_output.put_line('Square of 5 is: ' || v_result);
end;
/























  

  


--q6
create or replace function d_h(p_dept_name varchar) return varchar as
    v_high varchar(5);
begin
    select id into v_high
    from instructor
    where dept_name = p_dept_name
    order by salary desc
    fetch first row only;

    return v_high;
end;
/

declare
    v_iid varchar(5);
begin
    for dr in (select dept_name from department) loop
        v_iid := d_h(dr.dept_name);
        dbms_output.put_line(dr.dept_name || ': ' || v_iid);
    end loop;
end;
/











  


  

--q7

create or replace package uni_package AS
    procedure list_inst(d_dept_name varchar);
    function max_salary(d_dept_name varchar) return number;
end uni_package;
/

create or replace package body uni_package as

    procedure list_inst(d_dept_name varchar) is
    begin
        for i in (select name from instructor where dept_name = d_dept_name) loop
            dbms_output.put_line(i.name);
        end loop;
    end list_inst;

    function max_salary(d_dept_name varchar) return number is 
        maxsal number;
    begin
        select max(salary) into maxsal
        from instructor
        where dept_name = d_dept_name;
        return maxsal;
    end max_salary;

end uni_package;
/

-- Now you can test the package
begin
    uni_package.list_inst('Comp. Sci.');
    dbms_output.put_line('Max salary in Computer Science: ' || uni_package.max_salary('Comp. Sci.'));
end;
/























  
--q8

create or replace procedure cal(p number, rate number, years number, 
                                                si out number, ci out number, 
                                                total in out number)as
begin
    si := (p * rate * years) / 100;
    ci := p * POWER((1 + rate / 100), years) - p;
    total := total + si + ci;
end;
/

declare
    v_si NUMBER;
    v_ci NUMBER;
    v_total NUMBER := 100000;
begin
    cal(100000, 5, 2, v_si, v_ci, v_total);
    dbms_output.put_line('Simple Interest: ' || v_si);
    dbms_output.put_line('Compound Interest: ' || v_ci);
    dbms_output.put_line('Total Sum: ' || v_total);
end;
/
