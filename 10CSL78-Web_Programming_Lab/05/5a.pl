#!/usr/bin/perl
print "Content-type: text/html\n\n";
print <<here;
   <html>
   <center>
   <table border=1 style="font-size:13px;">
   <tr>
       <th>ENV_VARIABLES</th><th>Value</th>
   </tr>
here
 
foreach $i(sort keys %ENV)
{
    print "<tr><td>$i</td><td>$ENV{$i}</td></tr>\n";
}
print "</table></center></html>";
