package DAO;

import model.Empresa;

public interface IEmpresa {
	public void inserir(Empresa empresa);
	public void listar(int id);
	public void deletar(int id);
	public void atualizar(Empresa empresa, int id);
}
