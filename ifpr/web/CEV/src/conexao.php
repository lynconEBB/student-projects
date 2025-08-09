<?php
	class Conexao{
        static function conectar()
        {
            $host="localhost";
            $user="root";
            $password="bancodedados";
            $banco="dbvacinacao";

            $con = mysqli_connect($host,$user,$password,$banco);
            return $con;
        }
	}
