package DAO;

import model.Parcela;

public interface IParcela {
	public void inserir(Parcela par);
	public void listar(int id);
	public void deletar(int id);
	public void atualizar(Parcela par, int id);
	public void efetuarPagamento(String data,double juros, double valor_pagamento, int id);
}
