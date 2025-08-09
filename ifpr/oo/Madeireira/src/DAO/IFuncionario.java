package DAO;

import model.Funcionario;

public interface IFuncionario {
	public void inserir(Funcionario func);
	public void listar(int id);
	public void deletar(int id);
	public void atualizar(Funcionario func, int id);
}
