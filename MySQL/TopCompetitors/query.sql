select hacker_id, name from (select distinct Submissions.hacker_id as hacker_id, Hackers.name as name, count(Submissions.hacker_id) over(partition by Hackers.hacker_id) as cnt from Submissions 
left join Challenges on 
(Submissions.challenge_id = Challenges.challenge_id) 
left join Hackers on 
(Submissions.hacker_id = Hackers.hacker_id)
left join Difficulty on
(Challenges.difficulty_level = Difficulty.difficulty_level) 
where Submissions.score = Difficulty.score) as t where cnt > 1 order by cnt DESC, hacker_id ASC; 