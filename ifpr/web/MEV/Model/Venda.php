<?php
/**
 * Created by PhpStorm.
 * User: User
 * Date: 22/09/2018
 * Time: 14:13
 */

class Venda{
    private $idVenda;
    private $dtVenda;
    private $cartaoBand;
    private $cartaoNum;
    private $total;
    private $idCliente;

    public function getIdVenda()
    {
        return $this->idVenda;
    }

    public function setIdVenda($idVenda): void
    {
        $this->idVenda = $idVenda;
    }

    public function getDtVenda()
    {
        return $this->dtVenda;
    }

    public function setDtVenda($dtVenda): void
    {
        $this->dtVenda = $dtVenda;
    }

    public function getCartaoBand()
    {
        return $this->cartaoBand;
    }

    public function setCartaoBand($cartaoBand): void
    {
        $this->cartaoBand = $cartaoBand;
    }

    public function getCartaoNum()
    {
        return $this->cartaoNum;
    }

    public function setCartaoNum($cartaoNum): void
    {
        $this->cartaoNum = $cartaoNum;
    }

    public function getTotal()
    {
        return $this->total;
    }

    public function setTotal($total): void
    {
        $this->total = $total;
    }

    public function getIdCliente()
    {
        return $this->idCliente;
    }

    public function setIdCliente($idCliente): void
    {
        $this->idCliente = $idCliente;
    }


}