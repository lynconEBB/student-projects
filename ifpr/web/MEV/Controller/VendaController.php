<?php
    require_once '../DAO/VendaDAO.php';
    require_once '../Model/Venda.php';
    require_once 'ItemController.php';
    require_once 'ProdutoController.php';
    require_once 'PessoaController.php';

    class VendaController{
        private $vendaDAO;

        function __construct(){
            $this -> vendaDAO = new VendaDAO();

            if(isset($_REQUEST["escolha"])){
                $acao=$_REQUEST["escolha"];
                $this->verificaAcao($acao);
            }
        }

        function verificaAcao($acao){
            switch ($acao){
                case 1:
                    $this->inserir();
                    break;
            }
        }

        function inserir(){
            $venda = new Venda();
            $venda->setDtVenda($_POST["dtVenda"]);
            $venda->setCartaoBand($_POST["cartaoBand"]);
            $venda->setIdCliente($_POST["idPessoa"]);
            $venda ->setCartaoNum($_POST["cartaoNum"]);
            $total = $this ->gerarTotal($_POST["produtos"],$_POST["Quantidade"]);
            $venda -> setTotal($total);
            $idVenda = $this ->vendaDAO ->inserir($venda);
            echo $idVenda;
            $itemControl = new ItemController();
            $itemControl -> inserir($_POST["produtos"],$_POST["Quantidade"],$idVenda);


        }

        function gerarTotal($produtos,$qtds){
            $total = 0.0;

            foreach ($produtos as $produto){
                $ProdPosPre = explode("-",$produto);
                $precoProduto = floatval($ProdPosPre[2]);
                $Pos = $ProdPosPre[1];
                $qtd = (doubleval($qtds[$Pos]));
                $precoParcial = $precoProduto * $qtd;
                $total += $precoParcial;
            }
            return $total;
        }

        function listar(){
            return $this -> vendaDAO -> listar();
        }

        function gerarNotaFiscal($id){
            $itemControl = new ItemController();
            $itens = $itemControl->listarPorIdVenda($id);

            $produtoControl = new ProdutoController();
            $produtos= array();

            foreach ($itens as $item){
                $produto = $produtoControl -> listarPorIdItem($item->getIdItem());
                $produtos[] = $produto;
            }

            $pessoaControl = new PessoaController();
            $cliente = $pessoaControl ->listarPorIdVenda($id);

            $venda = $this ->vendaDAO->listarPorId($id);

            return array($itens,$produtos,$cliente,$venda,);

        }

    }
new VendaController();
?>