<?php
require_once "../Model/Pessoa.php";
require_once "../DAO/PessoaDAO.php";

class PessoaController{
    private $pessoaDAO;
    function __construct(){
        $this->pessoaDAO = new PessoaDAO();

        if(isset($_REQUEST["acao"])){
            $acao = $_REQUEST["acao"];
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
                $this->alterar();
                break;
        }
    }

    function listar(){
        return $this->pessoaDAO->listar();
    }

    function listarPorId($id){
        return $this -> pessoaDAO ->listarPorId($id);
    }

    function listarPorIdVenda($idVenda){
        return $this -> pessoaDAO -> listarPorIdVenda($idVenda);
    }

    function inserir(){
        $pessoa = new Pessoa();
        $pessoa->setNomeCompleto($_POST["NomeCompleto"]);
        $pessoa->setBairro($_POST["Bairro"]);
        $pessoa->setCidade($_POST["Cidade"]);
        $pessoa->setRua($_POST["Rua"]);
        $pessoa->setNumero($_POST["Numero"]);
        $pessoa->setCpf($_POST["CPF"]);
        $pessoa->setTelefone($_POST["Telefone"]);
        $pessoa->setLogin($_POST["Login"]);
        $pessoa->setSenha($_POST["Senha"]);
        $pessoa->setEmail($_POST["Email"]);
        $pessoa->setTipoPessoa($_POST["TipoPessoa"]);

        $this -> pessoaDAO -> inserir($pessoa);
    }

    function alterar(){
        $pessoa = new Pessoa();
        $pessoa->setNomeCompleto($_POST["NomeCompleto"]);
        $pessoa->setBairro($_POST["Bairro"]);
        $pessoa->setCidade($_POST["Cidade"]);
        $pessoa->setRua($_POST["Rua"]);
        $pessoa->setNumero($_POST["Numero"]);
        $pessoa->setCpf($_POST["CPF"]);
        $pessoa->setTelefone($_POST["Telefone"]);
        $pessoa->setLogin($_POST["Login"]);
        $pessoa->setEmail($_POST["Email"]);
        $pessoa->setTipoPessoa($_POST["TipoPessoa"]);
        $pessoa->setIdPessoa($_POST["idPessoa"]);

        $this -> pessoaDAO -> alterar($pessoa);
    }

    function excluir(){
        $this -> pessoaDAO -> excluir($_GET["id"]);
    }

    function consultar($login,$senha){
        return $this -> pessoaDAO ->consultar($login,$senha);
    }
}
new PessoaController();
