<?php
// Include database configuration file
require_once 'dbConfig.php';

// Include URL Shortener library file
require_once 'Shortener.class.php';

// Initialize Shortener class and pass PDO object
$shortener = new Shortener($db);

// Long URL
//$longURL = 'https://www.codexworld.com/tutorials/php/';
$longURL = $_POST['lu'];

// Prefix of the short URL(with URL rewrite)
$shortURL_Prefix = 'http://localhost:8080/php_url_shortener/'; 
//$shortURL_Prefix = 'https://xyz.com/?c='; 

try{
    // Get short code of the URL
    $shortCode = $shortener->urlToShortCode($longURL);
    
    // Create short URL
    $shortURL = $shortURL_Prefix.$shortCode;
    
    // Display short URL
   // echo 'Short URL: '.$shortURL;
   echo 'Short URL: <a href="'.$shortURL.'" target="_blank">'.$shortURL.'</a>';
   //print 'Short URL: <a href="'.$shortURL.'" target="_blank">'.$shortURL.'</a>';
}catch(Exception $e){
    // Display error
    echo $e->getMessage();
}