select N,
case 
when N in (select N from BST where P is NULL) then 'Root' 
when N in (select distinct P from BST where P is not NULL) then 'Inner'
else 'Leaf'
end
from BST order by N


/**/