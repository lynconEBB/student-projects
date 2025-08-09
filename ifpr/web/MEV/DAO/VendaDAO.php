<?php
require_once "../Model/Venda.php";
require_once "conexao.php";

class VendaDAO{
    private $con;

    function __construct(){
        $this->con = Conexao::conectar();
    }

    function inserir(Venda $venda){
        $sql = "insert into tbVenda (dtVenda,cartaoBand,cartaoNum,idCliente,Total) values ('".$venda->getDtVenda()."','".$venda->getCartaoBand().
            "','".$venda->getCartaoNum()."','".$venda->getIdCliente()."','".$venda->getTotal()."')";
        if (mysqli_query($this->con, $sql)) {
            $last_id = mysqli_insert_id($this->con);
            return $last_id;
        } else {
            echo "Error: " . $sql . "<br>" . mysqli_error($this->con);
        }
    }


    function listar(){
        $sql="select * from tbvenda";
        $resultado = mysqli_query($this->con, $sql);

        $lista_venda = array();

        while ($row = mysqli_fetch_array($resultado)) {
            $venda = new Venda();
            $venda -> setIdVenda($row["idVenda"]);
            $venda -> setIdCliente($row["idCliente"]);
            $venda -> setCartaoNum($row["cartaoNum"]);
            $venda -> setCartaoBand($row["cartaoBand"]);
            $venda -> setDtVenda($row["dtVenda"]);
            $venda -> setTotal($row["Total"]);

            $lista_venda[] = $venda;
        }

        return $lista_venda;
    }


    function listarPorId($id){
        $sql="select Total, dtVenda,cartaoBand,cartaoNum from tbvenda where idVenda='".$id."'";
        $resultado=mysqli_query($this->con, $sql);

        $row = mysqli_fetch_object($resultado);

        $venda = new Venda();
        $venda -> setCartaoNum($row->cartaoNum);
        $venda -> setCartaoBand($row->cartaoBand);
        $venda -> setDtVenda($row->dtVenda);
        $venda -> setTotal($row->Total);

        return $venda;
    }
}