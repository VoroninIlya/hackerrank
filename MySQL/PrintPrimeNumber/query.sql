DELIMITER //

CREATE PROCEDURE print_prime()
BEGIN
    DECLARE ind INT DEFAULT 5;
    DECLARE i INT DEFAULT 5;
    DECLARE b BOOLEAN;
    DECLARE res TEXT DEFAULT '';
    SET res = CONCAT(res, '2&3');
    
    WHILE ind <= 1000 DO
        
        SET b = TRUE;
        
        IF (ind % 2 = 0 or ind % 3 = 0) THEN
            SET b = FALSE;
        ELSE
            SET i = 5;
            WHILE i * i <= ind DO
                IF (ind % i = 0 OR ind % (i + 2) = 0) THEN
                    SET b = FALSE;
                END IF;
                SET i = i + 6;
            END WHILE;
        END IF;

        IF b = true THEN
            SET res = CONCAT(res, '&', ind);
        END IF;
        
        SET ind = ind + 1;
    END WHILE;
    
    select res;
END //

DELIMITER ;

call print_prime();