
select id, age, cns_needed, pwr from
(select Wands.id as id, Wands.power as pwr, Wands_Property.age as age, Wands.coins_needed as cns_needed,
  min(Wands.coins_needed) over (partition by Wands.power, Wands_Property.age) as cns
  from Wands left join Wands_Property on (Wands.code = Wands_Property.code) 
  where Wands_Property.is_evil = 0) as tbl 
  where cns_needed = cns order by pwr DESC, age DESC;

	
