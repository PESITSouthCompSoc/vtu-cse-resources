#!/usr/bin/perl

use CGI':standard';
print "Content-type:text/html\n\n";
#File count.txt must exist in same directory
open(FILE,'<count.txt');
#copy file contents to a variable
$count=<FILE>;
close(FILE);
$count++;
#overwrite the file with new count
open(FILE,'>count.txt');
print FILE "$count";
close(FILE);
print "This page has been viewed <strong><em>$count</em></strong> times!";

