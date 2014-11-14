<?php
    include 'functions.php';
	
	if(!isset($_POST['submit']))
		print_form();
	else
		encrypt();
	
	
	function print_form(){
		print_header();
?>
		<form action="tester.php" method="POST">
			Input: <input type="text" name="input" value="32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34"><br>
			Cipher Key: <input type="text" name="key" value="2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c"><br>
			<input type="submit" name="submit" value="Submit">
		</form>
		
<?
		
	}
	
	function print_header(){
?>
	<!DOCTYPE HTML>
	<html lang="es">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="description" content="Tester para AES">
        <title>AES: Joan Torres's Tester</title>
    </head>
    <body>
<?
	}
	
	function print_footer(){
?>
		</body>
		</html>
<?
		
	}
	
	function encrypt(){
		
		$input = explode(" ", $_POST['input']);
		$key = explode(" ", $_POST['key']);
		
		$i=0;
		foreach($input as $in)
			$input[$i++] = "0x".$in;
		
		$i=0;
		foreach($key as $in)
			$key[$i++] = "0x".$in;
		
		print_r(cipher($input, KeyExpansion($key)));
		
		
	}
?>
