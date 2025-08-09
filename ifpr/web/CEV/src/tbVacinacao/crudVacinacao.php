<?php
require_once $_SERVER['DOCUMENT_ROOT']."/conexao.php";
  class Crud{
     private $con;
     function __construct(){
         $this->con=Conexao::conectar();
         if(isset($_REQUEST["acao"])){
             $acao=$_REQUEST["acao"];
             $this->verificaAcao($acao);
         }
     }
     function verificaAcao($acao){
         switch ($acao){
             case 1:
                 $this->inserir();
                 break;
             case 2:
                 $this->excluir();
                 break;
             case 3:
                 $this->listaPorId();
                 break;
             case 4:
                 $this->alterar();
                 break;
         }
     }

    function inserir(){
        $sql=" insert into tbvacinacao(Data, idPaciente, idVacina) values ('".$_REQUEST["Data"]."','".$_REQUEST["idPac"]."','".$_REQUEST["idVac"]."')";
        mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        header("Location:menuVacinacao.php");
    }

    function retornarNome(){
        $sql ="select distinct Nome from tbVacinacao inner join tbPaciente on tbPaciente.id = tbVacinacao.idPaciente where tbVacinacao.idPaciente ='".$_REQUEST["idPac"]."'";
        $query=mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        return $query;
    }

    function listaPorIdPaciente(){
        $sql = "select tbVacina.id, tbVacina.Nome , tbVacinacao.Data from 
        tbVacinacao inner join tbVacina on tbVacina.id = tbVacinacao.idVacina 
        inner join tbPaciente on tbPaciente.id = tbVacinacao.idPaciente 
        where tbVacinacao.idPaciente ='".$_REQUEST["idPac"]."'";
        $query=mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        return $query;
    }
  }
new Crud();
