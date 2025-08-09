<?php
require_once "../Model/Item.php";
require_once "../DAO/ItemDAO.php";
require_once "ProdutoController.php";

class ItemController{
    private $itemDAO;

    function __construct(){
        $this->itemDAO = new ItemDAO();
    }

    function inserir($produtos,$qtds,$idVenda){
        $produtoControl = new ProdutoController();

        if(!empty($produtos)){
            foreach ($produtos as $produto) {
                $item = new Item();
                $ProdPosPre = explode("-",$produto);
                $Pos = $ProdPosPre[1];
                $Preco = doubleval($ProdPosPre[2]);
                $QtdEstoque = $ProdPosPre[3];
                $item->setIdProduto($ProdPosPre[0]);
                $item->setQtd(doubleval($qtds[$Pos]));
                $item ->setPrecoParcial($Preco * $item->getQtd());
                $item ->setVenda($idVenda);

                if($item->getQtd() > 0 && $item->getQtd() <= $QtdEstoque){
                    $this -> itemDAO -> inserir($item);
                    $NewQtdEstoque = $QtdEstoque - $item->getQtd();
                    $produtoControl->atualizaEstoque($item->getIdProduto(),$NewQtdEstoque);
                }else{
                    echo "Erro: Quantidade de Itens Invalida";
                    $this -> itemDAO ->excluirPorIdVenda($idVenda);
                    echo "<a href='../View/menuVenda.php'>Clique para reiniciar a Venda</a>";
                    exit();
                }

            }
        }else{
            echo "Erro: Quantidade de Produtos Invalida";
            echo "<a href='../View/menuVenda.php'>Clique para reiniciar a Venda</a>";
            exit();
        }
    }

    function listarPorIdVenda($idVenda){
        return $this -> itemDAO -> listarPorIdVenda($idVenda);
    }
}