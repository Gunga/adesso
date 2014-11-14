<?php
	include 'functions.php';
	
	function crypt_ebc($input, $key, $mode){
		
		$size= count($input);
		
		$firstBlock= array_slice($input, 0, ($size/2)-1);
		
		$secondBlock= array_slice($input, $size/2, $size-1);
		
		if($mode==='E'){
			
			$output = cipher($firstBlock, KeyExpansion($key));
			$soutput = cipher($secondBlock, KeyExpansion($key));
		
			foreach($soutput as $value)
				$ouput[] = $value;
			
		}
		else if($mode==='D'){
		
			$ouput = inverseCipher($firstBlock, KeyExpansion($key));
			$soutput = inverseCipher($secondBlock, KeyExpansion($key));
			
			foreach($soutput as $value)
				$ouput[] = $value;
		}
		
		return $output;
		
	}
	
	
	function crypt_cbc($input, $key, $mode){
		
		$size= count($input);
		
		$firstBlock= array_slice($input, 0, ($size/2)-1);
		
		$secondBlock= array_slice($input, $size/2, $size-1);
		
		$init_Vector = mcrypt_create_iv($size/2);
		
		if($mode==='E')
			$output = cipher(TwoArrayXor($secondBlock,cipher(TwoArrayXor($firstBlock,$init_Vector), KeyExpansion($key))), KeyExpansion($key));
		else if ($mode==='D')
			$output = inverseCipher(TwoArrayXor($secondBlock,inverseCipher(TwoArrayXor($firstBlock,$init_Vector), KeyExpansion($key))), KeyExpansion($key));
		
		return $output;	
		
	}
?>