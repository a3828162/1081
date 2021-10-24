<?php

require_once('TCPDF/tcpdf_import.php');
$pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);
$pdf->SetFont('cid0jp','', 18); 
$pdf->AddPage();

/*---------------- Your Code Start -----------------*/
$style = array(
    'position' => '',
    'align' => 'C',
    'stretch' => false,
    'fitwidth' => true,
    'cellfitalign' => '',
    'border' => true,
    'hpadding' => 'auto',
    'vpadding' => 'auto',
    'fgcolor' => array(0,0,0),
    'bgcolor' => false, 
    'text' => true,
    'font' => 'helvetica',
    'fontsize' => 8,
    'stretchtext' => 4
);

$name = $_POST['name'];
$sex = $_POST['sex1'];
$birthday = $_POST['birthday'];
$tel = $_POST['tel'];
$email = $_POST['email'];
$url = $_POST['url'];
$e1 = $_POST['e1'];
$e1s = $_POST['e1s'];
$e1e = $_POST['e1e'];
$e2 = $_POST['e2'];
$e2s = $_POST['e2s'];
$e2e = $_POST['e2e'];
$e3 = $_POST['e3'];
$e3s = $_POST['e3s'];
$e3e = $_POST['e3e'];

$html = <<<EOF
		<table cellspacing="0" cellpadding="1" border="1">
			<tr>
				<td rowspan=4><img src="$url" width=100 height=100></td>
				<td>Name:</td>
				<td>$name</td>
			</tr>
			<tr>
				<td>Gender:</td>
				<td>$sex</td>
			</tr>			
			<tr>
				<td>Birthday:</td>
				<td>$birthday</td>
			</tr>
			<tr>
				<td>Cellphone:</td>
				<td>$tel</td>
			</tr>			
			<tr>
				<td>Email:</td>
				<td colspan=2>$email</td>
			</tr>   
			<tr>
				<td colspan=3>Education:
				<ul> 
					<li>$e1 University</li> 
						<ol>
							<li>$e1s ~ $e1e</li>
						</ol>
					
					<li>$e2 Senior High School </li>
						<ol>
							<li>$e2s ~ $e2e</li>
						</ol>
									
					<li>$e3 Junior High School </li>
						<ol>
							<li>$e3s ~ $e3e</li>
						</ol>
									
				</ul>
				</td>
			</tr>
		</table>
EOF
/*---------------- Your Code End -------------------*/

$pdf->writeHTML($html);
$pdf->lastPage();
$pdf->Output('order.pdf', 'I');
?>