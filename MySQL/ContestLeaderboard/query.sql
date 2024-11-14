select Hackers.hacker_id, Hackers.name, tbl2.sm
from Hackers left join 
    (select id, sum(max_sc) as sm from
        (select hacker_id as id, max(score) as max_sc
         from Submissions where score > 0 
         group by challenge_id, hacker_id 
         order by hacker_id) as tbl 
     group by id) as tbl2
on (tbl2.id = Hackers.hacker_id)
where tbl2.sm is not NULL
order by tbl2.sm DESC, Hackers.hacker_id