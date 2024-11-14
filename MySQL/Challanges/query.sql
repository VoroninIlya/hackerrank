select hacker_id, name, total_number
from 
   (select 
       Hackers.hacker_id as hacker_id, 
       Hackers.name as name, 
       count(Hackers.hacker_id) as total_number 
    from Hackers left join Challenges 
    on (Hackers.hacker_id = Challenges.hacker_id)
    group by Hackers.hacker_id, Hackers.name) as tbl
where 
    total_number = (select max(total_number) 
                    from (select Hackers.hacker_id as hacker_id, 
                                 Hackers.name as name, 
                                 count(Hackers.hacker_id) as total_number 
                          from Hackers left join Challenges 
                          on (Hackers.hacker_id = Challenges.hacker_id)
                          group by Hackers.hacker_id, Hackers.name) as tbl) or
    total_number in (select total_number 
                    from (select total_number, 
                                 count(hacker_id) over (partition by total_number) as min_id 
                          from (select Hackers.hacker_id as hacker_id, 
                                       Hackers.name as name, 
                                       count(Hackers.hacker_id) as total_number 
                                from Hackers left join Challenges 
                                on (Hackers.hacker_id = Challenges.hacker_id)
                                group by Hackers.hacker_id, Hackers.name) as tbl) as tbl2
                    where min_id = 1)
order by total_number DESC, hacker_id;