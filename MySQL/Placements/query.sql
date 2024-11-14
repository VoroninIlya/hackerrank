select Students.name from Students left join Packages 
on (Students.id = Packages.id) left join Friends 
on(Students.id = Friends.id) left join Packages as friend_Packages
on(Friends.Friend_id = friend_Packages.id) where Packages.Salary < friend_Packages.Salary order by friend_Packages.Salary