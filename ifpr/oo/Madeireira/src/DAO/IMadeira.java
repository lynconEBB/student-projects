package DAO;

import model.Madeira;

public interface IMadeira {
	public void inserir(Madeira madeira);
	public void listar(int id);
	public void deletar(int id);
	public void atualizar(Madeira madeira, int id);
	
}
