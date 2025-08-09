<?php
class Conexao{
    static function conectar(){
        $host="localhost";
        $user="root";
        $password="";
        $banco="dbMimo";
        $con=mysqli_connect($host,$user,$password,$banco);
        return $con;
   }
}
?>
