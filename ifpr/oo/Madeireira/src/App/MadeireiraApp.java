package App;

import java.util.Scanner;
import DAO.TbFuncionario;
import DAO.TbItem;
import DAO.TbEmpresa;
import DAO.TbEntregador;
import DAO.TbMadeira;
import DAO.TbParcela;
import DAO.TbTipo;
import DAO.TbVenda;
import model.Empresa;
import model.Entregador;
import model.Madeira;
import model.Parcela;
import model.Tipo;
import model.Venda;
import model.Item;
import model.Funcionario;

public class MadeireiraApp {
	
	public static void main(String[] args) {
	TbVenda vendinha = new TbVenda();
	TbMadeira madeirinha = new TbMadeira();
	TbItem itenzinho = new TbItem();
	TbEmpresa empresinha = new TbEmpresa();
	int cont = 0;
	while( cont != 9) {
		Scanner scan = new Scanner(System.in);
		System.out.println("Escolha uma opçao");
		System.out.println("1-Executar venda");
		System.out.println("2-Listar notas fiscais");
		System.out.println("3-Menu Tabela Madeira");
		System.out.println("4-Menu Tabela Tipo");
		System.out.println("5-Menu Tabela Empresa Cliente");
		System.out.println("6-Menu Tabela Funcionario");
		System.out.println("7-Menu Tabela Entregador");
		System.out.println("8-Menu Tabela Parcela");
		System.out.println("9-Sair");
		System.out.println("Opção:");
		cont = Integer.valueOf(scan.nextLine());
				if(cont==1) {
					System.out.println("Informe o id da empresa");
					int idemp = Integer.valueOf(scan.nextLine());
					
					System.out.println("Informe o id do funcionario responsavel");
					int idf = Integer.valueOf(scan.nextLine());

					System.out.println("Informe o id do entregador");
					int ident= Integer.valueOf(scan.nextLine());

					System.out.println("Informe a data da venda");
					String data =scan.nextLine();
					
					System.out.println("Informe o horario");
					String hora = scan.nextLine();
					
					double nd = 0;
					
					Venda v = new Venda(data, hora, nd, idf, idemp, ident);
					
					int id = vendinha.inserir(v);
					int bla=1;
					double tv=0;
					while(bla != 2) {
						
					madeirinha.listar(0);
					System.out.println("Insira o id da madeira que deseja comprar");
					int idma = Integer.valueOf(scan.nextLine());
					
					System.out.println("Insira quantidade de madeira");
					int qdt = Integer.valueOf(scan.nextLine());
					
					System.out.println("Insira o comprimento da madeira");
					double comp = Double.valueOf(scan.nextLine());
					
					double t = vendinha.fazerVenda(idma, qdt,comp);
					tv= tv+t;
					double preco = t/qdt/comp;
					Item it = new Item(preco,t, id, idma, comp,qdt);
					itenzinho.inserir(it);
					
					
					System.out.println("Deseja adicionar mais algo a venda? 1-Sim/2-Não");
					int prox = Integer.valueOf(scan.nextLine());
					if (prox==2){
						bla = 2;
						vendinha.atualizarTotal(tv, id);
					}
				}
					vendinha.listar(id);
					itenzinho.listar(id);
					
					
					
				}else if(cont==2){
					System.out.println("Insira o ID da venda que deseja ver a nota fiscal (0=todas notas fiscais):"); 
					int id = Integer.valueOf(scan.nextLine());
					vendinha.listar(id);
					itenzinho.listar(id);
					
					
					
				}else if(cont ==3) {
				TbMadeira tbmadeira = new TbMadeira();
				System.out.println("1-Listar Madeira(s)");
				System.out.println("2-Inserir Madeira");
				System.out.println("3-Deletar Madeira");
				System.out.println("4-Atualizar Madeira");
				System.out.println("Opção:");
				int contmad = Integer.valueOf(scan.nextLine());
				
				if(contmad==1) {
						System.out.println("Insira o ID da Madeira desejada(0 = todas madeiras)");
						int id = Integer.valueOf(scan.nextLine());
						tbmadeira.listar(id);
				}else if(contmad==2){
						System.out.println("Preço unitario da madeira: ");
						double precomad= Double.valueOf(scan.nextLine());
						System.out.println("Nome da Madeira: ");
						String nomemad = scan.nextLine();
						System.out.println("ID do Tipo: ");
						int idtipmad = Integer.valueOf(scan.nextLine());
						Madeira mad = new Madeira(precomad,idtipmad,nomemad);
						tbmadeira.inserir(mad);
				}else if(contmad==3){	
						System.out.println("Insira o ID da madeira que deseja deletar");
						int id3 = Integer.valueOf(scan.nextLine());
						tbmadeira.deletar(id3);
				}else if(contmad==4){
						System.out.println("Insira o ID da madeira que deseja atualizar");
						int id4 = Integer.valueOf(scan.nextLine());
						System.out.println("Preço unitario da madeira: ");
						double precomad2= Double.valueOf(scan.nextLine());
						System.out.println("Nome da Madeira: ");
						String nomemad2 = scan.nextLine();
						System.out.println("ID do Tipo: ");
						int idtipmad2 = Integer.valueOf(scan.nextLine());
						Madeira mad2= new Madeira(precomad2,idtipmad2,nomemad2);
						tbmadeira.atualizar(mad2, id4);
					}
				}
				
				else if(cont==4) {
				TbTipo tbtipo= new TbTipo();
				System.out.println("1-Listar Tipo(s)");
				System.out.println("2-Inserir Tipo");
				System.out.println("3-Deletar Tipo");
				System.out.println("4-Atualizar Tipo");
				System.out.println("Opção:");
				int conttipo = Integer.valueOf(scan.nextLine());
				
				if(conttipo ==1) {
						System.out.println("Insira o ID do Tipo de madeira desejado(0 = todos tipos)");
						int id = Integer.valueOf(scan.nextLine());
						tbtipo.listar(id);
				}else if(conttipo==2) {
						System.out.println("Espessura do tipo de madeira : ");
						double espessura= Double.valueOf(scan.nextLine());
						System.out.println("Nome do tipo de Madeira: ");
						String nometipo = scan.nextLine();
						Tipo tipo = new Tipo(espessura,nometipo);
						tbtipo.inserir(tipo);
				}else if(conttipo==3) {
						System.out.println("Insira o ID do tipo de madeira que deseja deletar");
						int id3 = Integer.valueOf(scan.nextLine());
						tbtipo.deletar(id3);
				}else if(conttipo==4) {
						System.out.println("Espessura do tipo de madeira : ");
						double espessura2= Double.valueOf(scan.nextLine());
						System.out.println("Nome do tipo de Madeira: ");
						String nometipo2 = scan.nextLine();
						System.out.println("ID do Tipo de madeira que deseja atualizar: ");
						int id4 = Integer.valueOf(scan.nextLine());
						Tipo tipo2 = new Tipo(espessura2,nometipo2);
						tbtipo.atualizar(tipo2, id4);
					}
				}
				
				else if(cont==5) {
					TbEmpresa tbemp= new TbEmpresa();
					System.out.println("1-Listar Empresa(s)");
					System.out.println("2-Inserir Empresa");
					System.out.println("3-Deletar Empresa");
					System.out.println("4-Atualizar Empresa");
					System.out.println("Opção:");
					int contemp = Integer.valueOf(scan.nextLine());
					
					if(contemp ==1) {
							System.out.println("Insira o ID da empresa desejada(0 = todas empresas)");
							int id = Integer.valueOf(scan.nextLine());
							tbemp.listar(id);
					}else if(contemp==2) {
							System.out.println("Nome da Empresa : ");
							String nomeemp=scan.nextLine();
							System.out.println("CNPJ da Empresa: ");
							String cnpjemp = scan.nextLine();
							System.out.println("Rua da Empresa");
							String ruaemp= scan.nextLine();
							System.out.println("Bairro da Empresa");
							String bairroemp= scan.nextLine();
							System.out.println("Cidade da Empresa");
							String cidadeemp= scan.nextLine();
							System.out.println("Numero de endereço da Empresa");
							int numemp= Integer.valueOf(scan.nextLine());
							System.out.println("Telefone da Empresa");
							String telemp= scan.nextLine();
							Empresa emp = new Empresa(nomeemp,ruaemp,telemp,cnpjemp,numemp,bairroemp,cidadeemp);
							tbemp.inserir(emp);
					}else if(contemp==3) {
							System.out.println("Insira o ID da Empresa que deseja deletar");
							int id3 = Integer.valueOf(scan.nextLine());
							tbemp.deletar(id3);
					}else if(contemp==4) {
							System.out.println("Nome da Empresa : ");
							String nomeemp2=scan.nextLine();
							System.out.println("CNPJ da Empresa: ");
							String cnpjemp2 = scan.nextLine();
							System.out.println("Rua da Empresa");
							String ruaemp2= scan.nextLine();
							System.out.println("Bairro da Empresa");
							String bairroemp2= scan.nextLine();
							System.out.println("Cidade da Empresa");
							String cidadeemp2= scan.nextLine();
							System.out.println("Numero de endereço da Empresa");
							int numemp2= Integer.valueOf(scan.nextLine());
							System.out.println("Telefone da Empresa");
							String telemp2= scan.nextLine();
							System.out.println("ID da Empresa que deseja atualizar: ");
							int id4 = Integer.valueOf(scan.nextLine());
							Empresa emp2 = new Empresa(nomeemp2,ruaemp2,telemp2,cnpjemp2,numemp2,bairroemp2,cidadeemp2);
							tbemp.atualizar(emp2, id4);
						}
				}
				
				else if(cont==6) {
					TbFuncionario tbfunc= new TbFuncionario();
					System.out.println("1-Listar Funcionario(s)");
					System.out.println("2-Inserir Funcionario");
					System.out.println("3-Deletar Funcionario");
					System.out.println("4-Atualizar Funcionario");
					System.out.println("Opção:");
					int contfunc = Integer.valueOf(scan.nextLine());
					
					if(contfunc ==1) {
							System.out.println("Insira o ID do Funcionario desejada(0 = todos funcionarios)");
							int id = Integer.valueOf(scan.nextLine());
							tbfunc.listar(id);
					}else if(contfunc==2) {
							System.out.println("Nome do Funcionario : ");
							String nomefunc=scan.nextLine();
							System.out.println("CPF do Funcionario: ");
							String cpffunc = scan.nextLine();
							System.out.println("RG do Funcionario: ");
							String rgfunc = scan.nextLine();
							System.out.println("Rua do endereço do Funcionario");
							String ruafunc= scan.nextLine();
							System.out.println("Bairro do endereço do Funcionario");
							String bairrofunc= scan.nextLine();
							System.out.println("Cidade do endereço do Funcionario");
							String cidadefunc= scan.nextLine();
							System.out.println("Numero de endereço do Funcionario");
							int numfunc= Integer.valueOf(scan.nextLine());
							System.out.println("Telefone do Funcionario");
							String telfunc= scan.nextLine();
							Funcionario func = new Funcionario(nomefunc,cpffunc,rgfunc,ruafunc,cidadefunc,numfunc,bairrofunc,telfunc );
							tbfunc.inserir(func);
					}else if(contfunc==3) {
							System.out.println("Insira o ID do Funcionario que deseja deletar");
							int id3 = Integer.valueOf(scan.nextLine());
							tbfunc.deletar(id3);
					}else if(contfunc==4) {
							System.out.println("Nome do Funcionario : ");
							String nomefunc2=scan.nextLine();
							System.out.println("CPF do Funcionario: ");
							String cpffunc2 = scan.nextLine();
							System.out.println("RG do Funcionario: ");
							String rgfunc2 = scan.nextLine();
							System.out.println("Rua do endereço do Funcionario");
							String ruafunc2= scan.nextLine();
							System.out.println("Bairro do endereço do Funcionario");
							String bairrofunc2= scan.nextLine();
							System.out.println("Cidade do endereço do Funcionario");
							String cidadefunc2= scan.nextLine();
							System.out.println("Numero de endereço do Funcionario");
							int numfunc2= Integer.valueOf(scan.nextLine());
							System.out.println("Telefone do Funcionario");
							String telfunc2= scan.nextLine();
							System.out.println("ID do Funcionario que deseja atualizar: ");
							int id4 = Integer.valueOf(scan.nextLine());
							Funcionario func2 = new Funcionario(nomefunc2,cpffunc2,rgfunc2,ruafunc2,cidadefunc2,numfunc2,bairrofunc2,telfunc2 );
							tbfunc.atualizar(func2, id4);
						}
				}
				
				else if(cont==7) {
					TbEntregador tbent= new TbEntregador();
					System.out.println("1-Listar Entregador(es)");
					System.out.println("2-Inserir Entregador");
					System.out.println("3-Deletar Entregador");
					System.out.println("4-Atualizar Entregador");
					System.out.println("Opção:");
					int content = Integer.valueOf(scan.nextLine());
					
					if(content ==1) {
							System.out.println("Insira o ID do entregador desejado(0 = todos Entregadores)");
							int id = Integer.valueOf(scan.nextLine());
							tbent.listar(id);
					}else if(content==2) {
							System.out.println("Numero da carteira de Motorista : ");
							String carteiraent=scan.nextLine();
							System.out.println("Veiculo que o entregador dirige: ");
							String veiculoent = scan.nextLine();
							System.out.println("ID do Funcionario que esta trabalhando como entregador: ");
							int idfuncent = Integer.valueOf(scan.nextLine());
							Entregador ent = new Entregador(carteiraent,veiculoent,idfuncent );
							tbent.inserir(ent);
					}else if(content==3) {
							System.out.println("Insira o ID do Entregador que deseja deletar");
							int id3 = Integer.valueOf(scan.nextLine());
							tbent.deletar(id3);
					}else if(content==4) {
							System.out.println("Numero da carteira de Motorista : ");
							String carteiraent2=scan.nextLine();
							System.out.println("Veiculo que o entregador dirige: ");
							String veiculoent2 = scan.nextLine();
							System.out.println("ID do Entregador que deseja atualizar: ");
							int id4 = Integer.valueOf(scan.nextLine());
							Entregador ent2 = new Entregador(carteiraent2,veiculoent2,id4 );
							tbent.atualizar(ent2, id4);
						}
				}
				
				else if(cont==8) {
					TbParcela tbpar= new TbParcela();
					System.out.println("1-Listar Parcela(s)");
					System.out.println("2-Inserir Parcela");
					System.out.println("3-Deletar Parcela");
					System.out.println("4-Atualizar Parcela");
					System.out.println("5-Efetuar Pagamento");
					System.out.println("Opção:");
					int contpar = Integer.valueOf(scan.nextLine());
					
					if(contpar ==1) {
							System.out.println("Insira o ID da parcela desejada(0 = todas Parcelas)");
							int id = Integer.valueOf(scan.nextLine());
							tbpar.listar(id);
					}else if(contpar==2) {
							System.out.println("ID da venda parcelada");
							int idvendpar = Integer.valueOf(scan.nextLine());
							System.out.println("Valor Parcela : ");
							double valorparcela=Double.valueOf(scan.nextLine());
							System.out.println("Data de vencimento da parcela: ");
							String datavenc = scan.nextLine();
							System.out.println("Data de Pagamento: ");
							String datapag = scan.nextLine();
							System.out.println("Juros em %");
							double juros = Double.valueOf(scan.nextLine());
							System.out.println("Valor do pagamento");
							double valorpag = Double.valueOf(scan.nextLine());
							
							Parcela par = new Parcela(valorparcela,datavenc,idvendpar,valorpag,juros,datapag); 
							tbpar.inserir(par);
					}else if(contpar==3) {
							System.out.println("Insira o ID da parcela que deseja deletar");
							int id3 = Integer.valueOf(scan.nextLine());
							tbpar.deletar(id3);
					}else if(contpar==4) {
							System.out.println("ID da venda parcelada");
							int idvendpar2 = Integer.valueOf(scan.nextLine());
							System.out.println("Valor Parcela : ");
							double valorparcela2=Double.valueOf(scan.nextLine());
							System.out.println("Data de vencimento da parcela: ");
							String datavenc2 = scan.nextLine();
							System.out.println("Data de Pagamento: ");
							String datapag2 = scan.nextLine();
							System.out.println("Juros em %");
							double juros2 = Double.valueOf(scan.nextLine());
							System.out.println("Valor do pagamento");
							double valorpag2 = Double.valueOf(scan.nextLine());
							System.out.println("ID do Entregador que deseja atualizar: ");
							int id4 = Integer.valueOf(scan.nextLine());
							Parcela par2 = new Parcela(valorparcela2,datavenc2,idvendpar2,valorpag2,juros2,datapag2); 
							tbpar.atualizar(par2, id4);
					}else if(contpar==5) {
							System.out.println("Data de Pagamento: ");
							String datapag3 = scan.nextLine();
							System.out.println("Juros em %");
							double juros3 = Double.valueOf(scan.nextLine());
							System.out.println("Valor do pagamento");
							double valorpag3 = Double.valueOf(scan.nextLine());
							System.out.println("ID da parcela que deseja pagar: ");
							int id5 = Integer.valueOf(scan.nextLine());
							tbpar.efetuarPagamento(datapag3, juros3, valorpag3, id5);
					}
				}
		}
	}
}
		


