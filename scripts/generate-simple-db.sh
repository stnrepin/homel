#!/bin/bash

SQL=$(cat <<-END
    CREATE TABLE IF NOT EXISTS Files(Id INT, TagPathes TEXT, Path TEXT);
    INSERT INTO Files (Id, TagPathes, Path) VALUES 
        (0, 'a;b;c/asd 12/d', 'simple/1'),
        (1, 'abcd/a', 'simp/le/2'),
        (2, '', 'simple 3'),
        (3, 'asd;asd/asd;123/123/12', 's/impl /4');
END
)

sqlite3 index.db "$SQL"

