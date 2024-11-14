with ranked as (
    select submission_date, hacker_id,
       dense_rank() over (order by submission_date) as rk
    from Submissions
),
cntd as (
    select 
        distinct hacker_id,
        submission_date,
        rk,
        0 as level
    from ranked 
    where rk = 1
    
    union all 
    
    select 
        a.hacker_id,
        a.submission_date,
        a.rk,
        level + 1 as level
    from 
    ranked a
    inner join
    cntd b
    on a.rk = b.rk + 1 and a.hacker_id = b.hacker_id
),
sorted as (
    select submission_date, count(distinct hacker_id) as cnt 
    from cntd group by submission_date
),
prepared as (
  select submission_date, 
    hacker_id,
    count(hacker_id) over (partition by submission_date, hacker_id) as cnt 
  from Submissions
),
maxAtDay as (
  select t1.submission_date, min(t2.hacker_id) as hacker_id from 
    (select submission_date, max(cnt) as cnt from prepared 
      group by submission_date) as t1
  join prepared as t2
  on (t1.submission_date = t2.submission_date and t1.cnt = t2.cnt)
  group by t1.submission_date
)

select 
    maxAtDay.submission_date, 
    sorted.cnt as cnt,
    maxAtDay.hacker_id,
    Hackers.name
from maxAtDay
left join sorted
on (sorted.submission_date = maxAtDay.submission_date)
left join Hackers
on (maxAtDay.hacker_id = Hackers.hacker_id)
order by maxAtDay.submission_date

