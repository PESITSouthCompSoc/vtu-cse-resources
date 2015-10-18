 <br><br><br><center><h2>
 <?php
#start session
session_start();
    #check if session exists
    if(isset($_SESSION['view_count']))
    {        
        #increment the count
        $_SESSION['view_count']++;
        echo "Current Page View Count: " .$_SESSION['view_count'];
    }
    else
    {
        #if no session exists
        echo "Fresh session started.<br><br><br>";
        $_SESSION['view_count']=1;
        echo "Current Page View Count: " .$_SESSION['view_count'];
    }
 ?>
 </h2>
 </center>

