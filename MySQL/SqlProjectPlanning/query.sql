DELIMITER //

CREATE PROCEDURE process_tasks()
BEGIN
    DECLARE done INT DEFAULT 0;
    DECLARE id INT;
    DECLARE curr_start DATE;
    DECLARE curr_end DATE;
    DECLARE pre_end DATE;
    DECLARE proj_start DATE;
    DECLARE proj_end DATE;

    -- Step 1: Declare the cursor for the query
    DECLARE tasks_cursor CURSOR FOR 
    SELECT Task_ID, DATE(Start_Date), DATE(End_Date) FROM Projects ORDER BY Start_Date;

    -- Step 2: Declare a handler to manage end of cursor
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    CREATE TEMPORARY TABLE IF NOT EXISTS tmp_table (
        projStart DATE,
        projEnd DATE,
        duration INT
    ) ENGINE=MEMORY;

    -- Step 3: Open the cursor
    OPEN tasks_cursor;

    -- Step 4: Fetch each row and process it in a loop
    FETCH tasks_cursor INTO id, curr_start, curr_end;
    SET proj_start = curr_start; 
    SET pre_end = curr_end;
    
    REPEAT
        FETCH tasks_cursor INTO id, curr_start, curr_end;

        IF curr_start != pre_end THEN
            SET proj_end = pre_end;
            /*SELECT proj_start, proj_end;*/

            INSERT INTO tmp_table (projStart, projEnd, duration)
            VALUES (proj_start, proj_end, (projEnd - projStart));

            SET proj_start = curr_start;
        END IF;
            
        SET pre_end = curr_end;

    UNTIL done END REPEAT;

    -- Step 5: Close the cursor
    CLOSE tasks_cursor;
    
    select projStart, projEnd from tmp_table order by duration, projStart;
END //

DELIMITER ;

/*SELECT Task_ID, DATE(Start_Date), DATE(End_Date) FROM Projects ORDER BY Start_Date*/

call process_tasks();