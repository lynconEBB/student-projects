<?php
  require_once $_SERVER['DOCUMENT_ROOT']."/conexao.php";
  class CrudPac{
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
    function retornarNome($id){
        $sql="select Nome from tbPaciente where id=".$id ;
        $query=mysqli_query($this->con, $sql);
        return $query;
    }
    function listaPorId(){
      $sql="select * from tbPaciente where id=".$_REQUEST["id"] ;
      $query=mysqli_query($this->con, $sql);
      return $query;
    }

    function inserir(){
     $sql=" insert into tbPaciente(Senha, Email, DataNascimento, Cidade, Bairro, Nome, CPF, RG, Numero, Observacoes, Rua) values ('".$_REQUEST["Senha"]."','".$_REQUEST["Email"]."','".$_REQUEST["DataNascimento"]."','".$_REQUEST["Cidade"]."','".$_REQUEST["Bairro"]."','".$_REQUEST["Nome"]."','".$_REQUEST["CPF"]."','".$_REQUEST["RG"]."','".$_REQUEST["Numero"]."','".$_REQUEST["Observacoes"]."','".$_REQUEST["Rua"]."')";
      mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
      header("Location:relatorioGeralPaciente.php");
    }
     
    function listar(){
      $sql="select * from tbPaciente";
      $query=mysqli_query($this->con, $sql);
      return $query; 
    }

    function excluir(){
      $sql="delete from tbPaciente where id=".$_REQUEST["id"];
      $msg="Erro ao excluir o registro<hr>";
      mysqli_query($this->con, $sql)or die ($msg.mysqli_error($this->con));
      header("Location:relatorioGeralPaciente.php");
    }

    function alterar(){
      $sql="update tbPaciente set Email='".$_POST["Email"]."',DataNascimento='".$_POST["DataNascimento"]."', Cidade='".$_POST["Cidade"]."', Bairro='".$_POST["Bairro"]."', Nome='".$_POST["Nome"]."', CPF='".$_POST["CPF"]."', RG='".$_POST["RG"]."', Numero='".$_POST["Numero"]."', Observacoes='".$_POST["Observacoes"]."', Rua='".$_POST["Rua"]."' where id ='".$_POST["id"]."'";
      mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
      header("Location:relatorioGeralPaciente.php");   
    }
  }
new CrudPac();
