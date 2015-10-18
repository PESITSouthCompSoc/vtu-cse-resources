<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" encoding="utf-8" style="margin:0; padding:0;">
<head>
	<title>Program 09</title>
</head>
<body style="margin:0; padding:0;">

<center style="position: absolute; height:100%; width:100%; margin:0; padding:0;">
<h2 style="margin:0; padding:0; position: absolute; top: 50%; left: 50%; transform: translate(-50%,-70%);">
	<?php
		/* 
		Function to set cookie:
			setcookie(name, value, expire, path, domain, secure, httponly);
			only the 'name' parameter is required, rest are optional.
		*/
		$cookie_name = "LAST_VISITED";
		$cookie_value = date("l, jS F Y") . " at " . date("h:i:s a");

		if(!isset($_COOKIE[$cookie_name])) {
			
			print "This is your first visit to this page!";
		} 
		else { 

			print "Your last visit was on:". "<br />"."<br />";
			echo $_COOKIE[$cookie_name] ;
		}
		setcookie($cookie_name,$cookie_value);
	?>
</h2>
</center>

</body>
</html>
