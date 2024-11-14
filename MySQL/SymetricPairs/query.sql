select distinct x1, y1 from 
(select t1.X as x1, t1.Y as y1, t2.X as x2, t2.Y as y2, count(t1.X) over (partition by t1.X) as cnt
from Functions as t1 left join Functions as t2 
on (t1.Y = t2.X and t2.Y = t1.X) where t1.X <= t2.Y) as t 
where (x1 < y1 and cnt = 2) or (x1 = y1 and cnt = 4) order by x1 