<?php

require_once('TCPDF/tcpdf_import.php');
/*---------------- Input in MySQL ------------------*/

header("Content-Type:text/html; charset=utf-8");

$name = $_POST['name'];
$gender = $_POST['gender'];
$tel = $_POST['tel'];
$stdnum = $_POST['stdnum'];
$birth = $_POST['birth'];
$people = $_POST['people'];
$gmail = $_POST['mail'];
$eat = $_POST['eat'];

$link=mysqli_connect("localhost","xuan","123") or die("連接失敗");

mysqli_select_db($link,"form");

mysqli_query($link,"SET NAMES utf8");

$sqlStr="insert into tb1 (name,gender,tel,stdnum,birth,people,mail,eat) ";

$sqlStr.="values('$name','$gender','$tel','$stdnum','$birth','$people','$gmail','$eat')";

echo $sqlStr."<br>";

mysqli_query($link,$sqlStr) or die("寫入失敗");

echo "資料寫入成功";

/*---------------- Sent Mail Start -----------------*/
$name = $_POST['name'];
$gender = $_POST['gender'];
$tel = $_POST['tel'];
$stdnum = $_POST['stdnum'];
$birth = $_POST['birth'];
$people = $_POST['people'];
$eat = $_POST['eat'];

$to = $_POST['mail']; //收件者
$subject = "四資迎新報名成功確認信"; //信件標題
$message = "恭喜你成功報名四資迎新-監獄風雲\r\n\r\n以下是你的報名資料:\r\n\r\n姓名 : $name\r\n性別 : $gender\r\n電話號碼 : $tel\r\n學號 : $stdnum\r\n出生年月日 : $birth\r\n身分證字號 : $people\r\n飲食習慣 : $eat\r\n";//信件內容
$headers = "From: 511082@stu.tnssh.tn.edu.tw"; //寄件者

if(mail($to,$subject,$message,$headers)){
	echo "yes";
}else{
	echo "no";
}
/*---------------- Sent Mail End -------------------*/

/*---------------- Print PDF Start -----------------*/
ob_end_clean();
$pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);
$pdf->SetFont('cid0jp','', 18); 
$pdf->AddPage();

$name = $_POST['name'];
$gender = $_POST['gender'];
$tel = $_POST['tel'];
$stdnum = $_POST['stdnum'];
$birth = $_POST['birth'];
$people = $_POST['people'];
$gmail = $_POST['mail'];
$eat = $_POST['eat'];
$other = $_POST['other'];
$html = <<<EOF

<link rel = "stylesheet" type = "text/css" href = "mo.css">
<style >
	em	{	font-weight: bold;
		color: blue;	}
</style>
<table border = "1" width=400 height=250>
	<tr>
		<td colspan="2">&nbsp;姓名</td>
		<td colspan="2">&nbsp;$name</td>
		<td colspan="2">&nbsp;性別</td>
		<td colspan="2">&nbsp;$gender</td>
	</tr>
	<tr>
		<td colspan="2"><em>&nbsp;手機號碼</em></td>
		<td colspan="6">&nbsp;$tel</td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;學號</td>
		<td colspan="2">&nbsp;$stdnum</td>
		<td colspan="2">&nbsp;出生年月日</td>
		<td colspan="2">&nbsp;$birth</td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;身分證字號</td>
		<td colspan="2">&nbsp;$people</td>
		<td colspan="2">&nbsp;飲食習慣</td>
		<td colspan="2">&nbsp;$eat</td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;電子信箱</td>
		<td colspan="6" style="color:red">&nbsp;$gmail</td>
	</tr>
	<tr>
		<td style = " text-align: center;" colspan="8">&nbsp;其他</td>
	</tr>
	<tr>
		<td style = " text-align: center;" colspan="8" rowspan"4" >$other</td>
	</tr>
</table>
EOF;
/*---------------- Print PDF End -------------------*/

$pdf->writeHTML($html);
$pdf->lastPage();
$pdf->Output('order.pdf', 'I');
?>