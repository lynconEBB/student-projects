<?php
require_once "conexao.php";
require_once "../Model/Produto.php";

class ProdutoDAO{
    private $con;
    function __construct(){
        $this->con = Conexao::conectar();
    }

    function inserir(Produto $produto){
        $sql="insert into tbproduto (descricao, preco, qtdestoque) values ('".$produto->getDescricao()."','".$produto->getPreco()."','".$produto->getQrdestoque()."')";
        mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        header("location:../View/relatorioGeralProduto.php");
    }

    function listarPorId($id){
        $sql="select * from tbproduto where idproduto =".$id;
        $resultado = mysqli_query($this->con, $sql);
        $row = mysqli_fetch_object($resultado);

        $produto = new Produto();
        $produto -> setDescricao($row->descricao);
        $produto -> setQrdestoque($row->qtdestoque);
        $produto -> setPreco($row->preco);

        return $produto;
    }

    function listar(){
        $sql="select * from tbproduto";
        $resultado = mysqli_query($this->con, $sql);

        $lista_produto = array();

        while ($row = mysqli_fetch_array($resultado)) {
            $produto = new Produto();
            $produto -> setDescricao($row['descricao']);
            $produto -> setQrdestoque($row['qtdestoque']);
            $produto -> setPreco($row['preco']);
            $produto -> setIdProduto($row['idProduto']);

            $lista_produto[] = $produto;
        }

        return $lista_produto;
    }

    function excluir($id){
        $sql="delete from tbproduto where idproduto=".$id;
        $msg="Erro ao excluir o registro<hr>";
        mysqli_query($this->con, $sql)or die ($msg.mysqli_error($this->con));
        header("Location:../View/relatorioGeralProduto.php");
    }

    function alterar(Produto $produto){
        $sql="update tbproduto set descricao='".$produto->getDescricao()."', preco='".$produto->getPreco()."', qtdestoque='".$produto->getQrdestoque()."' where idProduto='".$produto->getIdProduto()."'";
        mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        header("Location:../View/menuProduto.php");

    }

    function atualizaEstoque($idProduto,$qtd){
        $sql="update tbproduto set qtdestoque ='".$qtd."' where idProduto='".$idProduto."'";
        mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
    }

    function listarPorIdItem($idItem){
        $sql="select descricao,preco from tbproduto inner join tbitem  on tbproduto.idProduto = tbitem.idProduto where tbitem.idItem ='".$idItem."'";
        $resultado = mysqli_query($this->con, $sql);

        $row = mysqli_fetch_object($resultado);

        $produto = new Produto();
        $produto -> setDescricao($row->descricao);
        $produto -> setPreco($row->preco);

        return $produto;
    }
}