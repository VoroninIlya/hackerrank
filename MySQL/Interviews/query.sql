select Contests.contest_id,
    Contests.hacker_id, Contests.name,
    cl.sumts, cl.sumtas, 
    cl.sumtv, cl.sumtuv
from Contests left join

(select Colleges.contest_id as contest_id,
    ifnull(sum(chll.sumts),0) as sumts, ifnull(sum(chll.sumtas),0) as sumtas,
    ifnull(sum(chll.sumtv),0) as sumtv, ifnull(sum(chll.sumtuv),0) as sumtuv
from Colleges left join 
(select Challenges.college_id as college_id,
    sum(ss.sumts) as sumts, sum(ss.sumtas) as sumtas,
    sum(vs.sumtv) as sumtv, sum(vs.sumtuv) as sumtuv
from Challenges 
left join 
(select t.challenge_id as challenge_id, 
    t.sumtv as sumtv, t.sumtuv as sumtuv
from 
    (select 
        challenge_id,
        sum(total_views) as sumtv,
        sum(total_unique_views) as sumtuv
     from View_Stats group by challenge_id) as t) as vs
on (Challenges.challenge_id = vs.challenge_id)
left join 
(select t.challenge_id as challenge_id, 
    t.sumts as sumts, t.sumtas as sumtas
from
    (select 
        challenge_id,
        sum(total_submissions) as sumts,
        sum(total_accepted_submissions) as sumtas
     from Submission_Stats group by challenge_id) as t) as ss
on (Challenges.challenge_id = ss.challenge_id)
group by Challenges.college_id) as chll
on(Colleges.college_id = chll.college_id)
group by Colleges.contest_id) as cl

on (Contests.contest_id = cl.contest_id)
where (cl.sumts != 0 or 
       cl.sumtas != 0 or
       cl.sumtv != 0 or
       cl.sumtuv != 0)
group by Contests.contest_id, Contests.hacker_id, Contests.name
order by Contests.contest_id
