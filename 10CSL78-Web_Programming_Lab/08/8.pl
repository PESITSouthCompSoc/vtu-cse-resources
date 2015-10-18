#!/usr/bin/perl

use CGI ':standard';

#import database module
use DBI;
$q=new CGI;

#get inputs through the html form
$name	= $q->param('f_name');
$age	= $q->param('f_age');

#The $dsn is the data source name. It is a string that tells the Perl DBI module, what kind of driver it should load and the location of the database to which the connection is going to be created. 
# Key: dbi:DriverName:database=database_name;host=hostname;
$dsn = "DBI:mysql:database=wp_lab;host=localhost;";

# other details to log in:
$username = "root";
$password = "<password_here>";

#this creates a database handle & stores it in $dbh
$dbh	= DBI->connect($dsn, $username, $password,{ RaiseError => 1 }) or die $DBI::errstr;


# Preparing the queries for execution later.
# prepare(): compiles the query and returns an object reference which is called statement handle ($insert_query & $select_query)
$insert_query = $dbh->prepare("insert into prog8 (`name`,`age`) values ('$name','$age');");
$select_query = $dbh->prepare("select * from prog8;");


#execute the query using statement handle
#$dbh->do() or die "Insert failed";
$insert_query->execute();
$select_query->execute();

print header();

print "<p>Row ($name,$age) was inserted successfully.</p><center><h2>Current Contents of Table</h2><br /><br /><table cellpadding='10px' cellspacing='0px' border=1px>\n<tr><th width=400px align=left>Name</th><th width=200px align=left>Age</th></tr>\n";
while(($name, $age)=$select_query->fetchrow()){
	print "<tr><td>$name</td><td>$age</td></tr>\n";
}

print "</table></center>\n";


