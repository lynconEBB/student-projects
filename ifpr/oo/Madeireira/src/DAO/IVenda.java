package DAO;



public interface IVenda {
	public void listar(int id);
	public double fazerVenda(int id,double qdt,double comp);
	public void atualizarTotal(double t,int id);
}
