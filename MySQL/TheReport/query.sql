/*
Enter your query here.
*/

select 
  Name, 
  Grade, 
  Marks
from 
  (select 
     IF(Grades.grade >= 8, Students.Name, NULL) as Name, 
     Students.Marks as Marks, 
     Grades.Grade as Grade from Students left join Grades on 
       (Students.Marks >= Grades.Min_Mark and 
        Students.Marks <= Grades.Max_Mark) order by Grades.Grade DESC, Name ASC) 
   as t1;