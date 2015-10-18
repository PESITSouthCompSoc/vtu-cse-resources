#!/usr/bin/perl
use CGI;
$q=new CGI;
$cmd=$q->param('name');


@greet=("Hello there","Greetings","Nice to meet you","Good day");
#choose a random message index
$index=int(rand(4));

print<<here;
Content-type:text/html\n\n
<html>
<center><br /><br />
<h2>$greet[$index], $cmd!</h2>
</center>
</html>
here
