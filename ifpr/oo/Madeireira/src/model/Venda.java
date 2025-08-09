package model;

public class Venda {
	private String data;
	private String horario;
	private double total;
	private int id_func;
	private int id_empresa;
	private int id_entregador;
	
	public Venda(String data, String horario, double total,int id_func, int id_empresa, int id_entregador) {
		this.data = data;
		this.horario=horario;
		this.total=total;
		this.id_func=id_func;
		this.id_empresa=id_empresa;
		this.id_entregador=id_entregador;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}

	public String getHorario() {
		return horario;
	}

	public void setHorario(String horario) {
		this.horario = horario;
	}

	public double getTotal() {
		return total;
	}

	public void setTotal(double total) {
		this.total = total;
	}

	public int getId_func() {
		return id_func;
	}

	public void setId_func(int id_func) {
		this.id_func = id_func;
	}

	public int getId_empresa() {
		return id_empresa;
	}

	public void setId_empresa(int id_empresa) {
		this.id_empresa = id_empresa;
	}

	public int getId_entregador() {
		return id_entregador;
	}

	public void setId_entregador(int id_entregador) {
		this.id_entregador = id_entregador;
	}
}	
