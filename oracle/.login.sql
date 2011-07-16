--
-- Copyright (c) 1988, 2005, Oracle.  All Rights Reserved.
--
-- NAME
--   glogin.sql
--
-- DESCRIPTION
--   SQL*Plus global login "site profile" file
--
--   Add any SQL*Plus commands here that are to be executed when a
--   user starts SQL*Plus, or uses the SQL*Plus CONNECT command.
--
-- USAGE
--   This script is automatically run
--
set timing on
set linesize 120
set pagesize 50
-- set arraysize 5000
-- set newpage none
-- set long 5000
-- set trimspool on
set serveroutput on size 100000 format wrapped
set termout off 
alter session set nls_date_format='yyyy-mm-dd hh24:mi:ss';
col login_info_temp new_value login_info
select user||'@'||global_name login_info_temp from global_name;
set sqlprompt '&login_info> '
set termout on
-- set serveroutput on
