<?php
  $Nb = 4;
  $Nr = 10;
  $Nk = 4;

  $Rcon = array( 
    array(0x00, 0x00, 0x00, 0x00),
    array(0x01, 0x00, 0x00, 0x00),
    array(0x02, 0x00, 0x00, 0x00),
    array(0x04, 0x00, 0x00, 0x00),
    array(0x08, 0x00, 0x00, 0x00),
    array(0x10, 0x00, 0x00, 0x00),
    array(0x20, 0x00, 0x00, 0x00),
    array(0x40, 0x00, 0x00, 0x00),
    array(0x80, 0x00, 0x00, 0x00),
    array(0x1b, 0x00, 0x00, 0x00),
    array(0x36, 0x00, 0x00, 0x00)
  );

  $sbox = array(0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
                0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
                0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
                0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
                0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
                0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
                0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
                0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
                0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
                0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
                0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
                0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
                0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
                0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
                0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
                0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16);

  function cipher( $in, $keysched){
    global $Nb;
    global $Nr;

      //$state = $in;
      //s[r][c]=in[r+4c]
    for($r=0;$r<4;$r++)
      for($c=0;$c<$Nb;$c++)
        $state[$r][$c]=$in[$r+4*$c];
      
    $state=AddRoundKey($state, $keysched, 0);
    
    for($round = 1; $round<$Nr-1; $round++){
      $state=SubBytes($state);
      $state=ShiftRows($state);
      $state=MixColumns($state);
      $state=AddRoundKey($state, $keysched, $round);
    }
    
    $state=SubBytes($state);
    $state=ShiftRows($state);
    $state=AddRoundKey($state, $keysched, $Nr);
    
    
    //$out = $state;
    //out[r+4c]=s[r,c]
    for($r=0;$r<4;$r++)
      for($c=0;$c<$Nb;$c++)
        $out[$r+4*$c]=$state[$r][$c];

    return $out;
  }

  function AddRoundKey($state, $keysched, $round){
    global $Nb;

    for ($r=0; $r<4; $r++)
      for ($c=0; $c<$Nb; $c++)
        $state[$r][$c] ^= $keysched[$round*4+$c][$r];

    return $state;
  }

  function SubBytes($state){
    global $sbox;
    global $Nb;

    for ($r=0; $r<4; $r++)
      for ($c=0; $c<$Nb; $c++) 
        $state[$r][$c] = $sbox[$state[$r][$c]];

    return $state;
  }

  function ShiftRows($state){
  //s'[r][c] =s[r][(c+shift(r,Nb))mod Nb] for0<r<4 and 0<=c<Nb
    global $Nb;

    $temp = array();

    for ($r=1; $r<4; $r++)
      for ($c=0; $c<4; $c++)
        $temp[$r][$c] = $state[$r][($c+$r)%$Nb]; 

      for ($r=1; $r<4; $r++)
        for ($c=0; $c<4; $c++)
          $state[$r][$c] = $temp[$c];           
        
    return $state;
  }

    function MixColumns($state){

      for ($c=0; $c<4; $c++) {
        $a = array(4);  
        $b = array(4);  
        for ($i=0; $i<4; $i++) {
          $a[$i] = $state[$i][$c];
          if($state[$i][$c] & 0x80)
            $b[$i] = $state[$i][$c] << 1 xor 0x011b;
          else
            $b[$i] = $state[$i][$c] << 1;
        }     

        $state[0][$c] = $b[0] xor $a[1] xor $b[1] xor $a[2] xor $a[3];
        $state[1][$c] = $a[0] xor $b[1] xor $a[2] xor $b[2] xor $a[3];
        $state[2][$c] = $a[0] xor $a[1] xor $b[2] xor $a[3] xor $b[3];
        $state[3][$c] = $a[0] xor $b[0] xor $a[1] xor $a[2] xor $b[3];
      }

      return $state;
    }

    function KeyExpansion($key){
      global $Nk;
      global $Nb;
      global $Nr;
      global $Rcon;

      $w=array();
      $i=0;

      while ($i < $Nk){
        $w[$i] = array($key[4*$i], $key[4*$i+1], $key[4*$i+2], $key[4*$i+3]);
        $i++;
      }

      $i = $Nk;

      while ($i < $Nb * ($Nr + 1)){

        $temp = $w[$i-1];

        if ($i % $Nk == 0)
          $temp = SubWord(RotWord($temp)) xor $Rcon[$i/$Nk];
        else if ($Nk > 6 and $i % $Nk == 4)
         $temp = SubWord($temp);

        $w[$i] = $w[$i-$Nk] xor $temp;
        $i++;
      }

     return $w;
   }

   function SubWord($temp){
    global $sbox;

    for ($i=0; $i<4; $i++)
      $temp[$i] = $sbox[$temp[$i]];

    return $temp;
  }

  function RotWord($temp){
    $first = $temp[0];

    for ($i=0; $i<3; $i++)
      $temp[$i] = $temp[$i+1];

    $temp[3] = $first;

    return $temp;
  }
?>