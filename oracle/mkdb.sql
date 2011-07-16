CREATE DATABASE xe
    controlfile reuse
    USER SYS IDENTIFIED BY oracle
    USER SYSTEM IDENTIFIED BY oracle
    LOGFILE GROUP 1 ('?/oradata/xe/redo01.log') SIZE 100M,
        GROUP 2 ('?/oradata/xe/redo02.log') SIZE 100M,
        GROUP 3 ('?/oradata/xe/redo03.log') SIZE 100M
    MAXLOGFILES 5
    MAXLOGMEMBERS 5
    MAXLOGHISTORY 1
    MAXDATAFILES 40
    CHARACTER SET US7ASCII
    NATIONAL CHARACTER SET AL16UTF16
    EXTENT MANAGEMENT LOCAL
    DATAFILE '?/oradata/xe/system01.dbf' SIZE 400M REUSE
    SYSAUX DATAFILE '?/oradata/xe/sysaux01.dbf' SIZE 400M REUSE
    DEFAULT TABLESPACE users
        DATAFILE '?/oradata/xe/users01.dbf'
            SIZE 400M REUSE AUTOEXTEND ON MAXSIZE UNLIMITED
    DEFAULT TEMPORARY TABLESPACE tempts1
        TEMPFILE '?/oradata/xe/temp01.dbf'
            SIZE 20M REUSE
    UNDO TABLESPACE UNDOTBS1
        DATAFILE '?/oradata/xe/undotbs01.dbf'
            SIZE 200M REUSE AUTOEXTEND ON MAXSIZE UNLIMITED;

CREATE TABLESPACE apps_tbs LOGGING 
     DATAFILE '?/oradata/xe/apps01.dbf' 
     SIZE 500M REUSE AUTOEXTEND ON NEXT  1280K MAXSIZE UNLIMITED 
     EXTENT MANAGEMENT LOCAL;
-- create a tablespace for indexes, separate from user tablespace (optional)
CREATE TABLESPACE indx_tbs LOGGING 
     DATAFILE '?/oradata/xe/indx01.dbf' 
     SIZE 100M REUSE AUTOEXTEND ON NEXT  1280K MAXSIZE UNLIMITED 
     EXTENT MANAGEMENT LOCAL;
exit;
