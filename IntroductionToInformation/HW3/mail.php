<?php
$to = "hjkja25@gmail.com"; //收件者
$subject = "四資迎新報名成功確認信"; //信件標題
$message = "恭喜你成功報名四資迎新-監獄風雲";//信件內容
$headers = "From: 511082@stu.tnssh.tn.edu.tw"; //寄件者

if(mail($to,$subject,$message,$headers)){
	echo "yes";
}else{
	echo "no";
}
?>