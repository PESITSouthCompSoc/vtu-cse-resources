#!/usr/bin/perl
use CGI':standard';
#refresh page every second
print "Refresh:1\n";
print "Content-type:text/html\n\n";
($s,$m,$h)=localtime(time);
print br "Hi! Current server time is $h:$m:$s";
print br "In words, the time is <strong><em>$h</em></strong> hours, <strong><em>$m</em></strong> minutes & <strong><em>$s</em></strong> seconds";
