
select distinct Company.company_code, founder, lead_t.lead_mng, seni_t.seni_mng, mng_t.mng, empl_t.empl
from Company 
left join (select company_code, count(lead_manager_code) over (partition by company_code order by company_code) as lead_mng from (select distinct * from Lead_Manager) as a) as lead_t on Company.company_code = lead_t.company_code
left join (select company_code, count(senior_manager_code) over (partition by company_code order by company_code) as seni_mng from (select distinct * from Senior_Manager) as b) as seni_t on Company.company_code = seni_t.company_code 
left join (select company_code, count(manager_code) over (partition by company_code order by company_code) as mng from (select distinct * from Manager) as c) as mng_t on Company.company_code = mng_t.company_code
left join (select company_code, count(employee_code) over (partition by company_code order by company_code) as empl from (select distinct * from Employee) as d) as empl_t on Company.company_code = empl_t.company_code order by Company.company_code


/*select distinct company_code, count(lead_manager_code) over (partition by company_code order by company_code) as cnt1 from Lead_Manager;*/
/*select distinct company_code, count(senior_manager_code) over (partition by company_code order by company_code) as cnt1 from Senior_Manager;*/


/*select distinct company_code, count(manager_code) over (partition by company_code order by company_code) as mng from Manager;*/
/*select distinct company_code, count(employee_code) over (partition by company_code order by company_code) as empl from Employee;*/

