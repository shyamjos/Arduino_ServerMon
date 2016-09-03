<?php
// Monitoring Linux server with arduino uno, LCD, ethernet module and PHP.
// Created 27 Aug 2016 by Shyam Jos <shyamjosepp@gmail.com> http://shyamjos.com

// get server up time
     $data = shell_exec('uptime'); 
     $uptime = explode(' up ', $data);
     $uptime = explode(',', $uptime[1]);
     $uptime = $uptime[0].', '.$uptime[1];

echo ($uptime);
echo ";"; // delimiter for value sepration 

// get server load average
echo implode(' ', sys_getloadavg());
echo ";";  // delimiter for value sepration 

// get server free memory 
 $free = shell_exec('free -m');
    $free = (string)trim($free);
    $free_arr = explode("\n", $free);
    $mem = explode(" ", $free_arr[1]);
    $mem = array_filter($mem);
    $mem = array_merge($mem);
echo ("$mem[3] MB");
echo ";";  // delimiter for value sepration 

// get server free disk space
$df = round(disk_free_space("/home") / 1024 / 1024 / 1024);
print("$df GB");
?>

