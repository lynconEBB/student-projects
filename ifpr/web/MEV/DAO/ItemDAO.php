<?php
require_once "../Model/Item.php";
require_once "conexao.php";

class ItemDAO{
    private $con;
    function __construct(){
        $this->con = Conexao::conectar();
    }

    function inserir(Item $item){
        $sql = "insert into tbItem (precoParcial,idProduto,idVenda,qtd) values ('".$item->getPrecoParcial()."','".$item->getIdProduto()."','".$item->getVenda()."','".$item->getQtd()."')";
        mysqli_query($this->con, $sql)or die (mysqli_error($this->con));
    }

    function excluirPorIdVenda($idVenda){
        $sql="delete from tbItem where idVenda=".$idVenda;
        $msg="Erro ao excluir o registro<hr>";
        mysqli_query($this->con, $sql)or die ($msg.mysqli_error($this->con));
    }

    function listarPorIdVenda($idVenda){
        $sql ="select precoParcial,idProduto,qtd,idItem from tbitem inner join tbvenda  on tbitem.idVenda = tbvenda.idVenda where tbvenda.idVenda = '".$idVenda."'";
        $resultado = mysqli_query($this->con, $sql)or die (mysqli_error($this->con));

        $lista_item = array();

        while ($row = mysqli_fetch_array($resultado)) {
            $item = new item();
            $item -> setPrecoParcial($row["precoParcial"]);
            $item -> setIdProduto($row["idProduto"]);
            $item -> setQtd($row["qtd"]);
            $item -> setIdItem($row["idItem"]);

            $lista_item[] = $item;
        }

        return $lista_item;
    }
}