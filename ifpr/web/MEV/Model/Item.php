<?php
/**
 * Created by PhpStorm.
 * User: User
 * Date: 22/09/2018
 * Time: 14:09
 */

class Item{
    private $idItem;
    private $precoParcial;
    private $idProduto;
    private $venda;
    private $qtd;

    public function getIdItem()
    {
        return $this->idItem;
    }

    public function setIdItem($idItem): void
    {
        $this->idItem = $idItem;
    }

    public function getPrecoParcial()
    {
        return $this->precoParcial;
    }

    public function setPrecoParcial($precoParcial): void
    {
        $this->precoParcial = $precoParcial;
    }

    public function getIdProduto()
    {
        return $this->idProduto;
    }

    public function setIdProduto($idProduto): void
    {
        $this->idProduto = $idProduto;
    }

    public function getVenda()
    {
        return $this->venda;
    }

    public function setVenda($venda): void
    {
        $this->venda = $venda;
    }

    public function getQtd()
    {
        return $this->qtd;
    }

    public function setQtd($qtd): void
    {
        $this->qtd = $qtd;
    }


}