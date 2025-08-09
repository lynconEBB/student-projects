package DAO;

import model.Tipo;

public interface ITipo {
	public void inserir(Tipo tipo);
	public void listar(int id);
	public void deletar(int id);
	public void atualizar(Tipo tipo, int id);
}
