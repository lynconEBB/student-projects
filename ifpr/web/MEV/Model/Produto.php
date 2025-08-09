<?php
/**
 * Created by PhpStorm.
 * User: User
 * Date: 22/09/2018
 * Time: 14:11
 */

class Produto{
    private $idProduto;
    private $descricao;
    private $preco;
    private $qrdestoque;

    public function getIdProduto()
    {
        return $this->idProduto;
    }

    public function setIdProduto($idProduto)
    {
        $this->idProduto = $idProduto;
    }

    public function getDescricao()
    {
        return $this->descricao;
    }

    public function setDescricao($descricao)
    {
        $this->descricao = $descricao;
    }

    public function getPreco()
    {
        return $this->preco;
    }

    public function setPreco($preco)
    {
        $this->preco = $preco;
    }

    public function getQrdestoque()
    {
        return $this->qrdestoque;
    }

    public function setQrdestoque($qrdestoque)
    {
        $this->qrdestoque = $qrdestoque;
    }


}