//Test.cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Room{
	private:
		int ID;//ID de la habitación que además designará la posición de la habitación en el vector
		std::vector<Room> salidas;//norte,sur,este,oeste,arriba,abajo
		std::vector<Item> objetos;//Vector de objetos existente en la habitación
		string Descripcion;//Descripción de la habitación
	public:
		Room(int ID,vector<Room> salidas,vector<Item> objetos,string Descripcion){
			this.ID = ID;
			this.salidas = salidas;
			this.objetos = objetos;
			this.Descripcion = Descripcion;
		}
		////////////////////////////////////////////
		int GetID(){
			return ID;
		}
		Room GetSalida(int PuntoCardinal){
			/*
			0:Norte
			1:Sur
			2:Este
			3:Oeste
			4:Arriba
			5:Abajo
			*//*////////////////////////////////////////////////////////////////////////////////////////
			if(PuntoCardinal >=0 && PuntoCardinal <= 5){
				return salidas[PuntoCardinal];
			}
			else{
				cout << "Error\n";
				exit(0);
			}
		}
		vector<Item> GetObjetos(){
			return objetos;
		}
		string GetDescripcion(){
			return Descripcion;
		}
		////////////////////////////////////////////
		bool ItemInRoom(Item objetos){
			for(int i = 0; i < objetos.size(); i++){
				if(objeto == objetos[i]){
					return true;
				}
			}
			return false;
		}
		bool DeleteObjeto(Item objeto){
			//Buscar el objeto en el vector de objetos
			int IndiceObjeto = -1;
			for(int i = 0; i < objetos.size(); i++){
				if(objeto == objetos[i]){
					IndiceObjeto = i;
				}
			}
			if(IndiceObjeto != -1){
				objetos.erase(objetos.begin()+IndiceObjeto);
				return true;
			}
			else{
				cout << "Ese objeto no se encuentra aquí." << endl;
				return false;
			}
		}
		void InsertObjeto(Item objeto){
			objetos.push_back(objeto);
		}
};

*/////////////////////////////////////////////////////////////////////////////////////////////////
class c1;
class c2{
private:
	c1* unaInstancia;
public:
	c2(c1* a){}
	c2(){}
	void Metodo();
	void Pinta();
};
class c1{
private:
	int n;
	c2 OtraInstancia;
public:
	c1(int k, c2 o){
		n = k;
		OtraInstancia = o;
	}
	c1(){}
	void Metodo(){
		cout << n;
	}
	void M2(){
		OtraInstancia.Pinta();
	}
};
void c2::Metodo(){
	unaInstancia->Metodo();
}
void c2::Pinta(){
	cout << "Pintando...";
}
void Function(vector<char> v){
	cout << v.size();
}
//////////////////////////////////
int main(){
	/*
	c2 A;
	c1 B(7,A);
	B.M2();
	*/
vector<int> v;
v.push_back(666);
/*
vector<int>::iterator it;
it = v.begin();
*/
int* puntero = &v[0];
cout << "Por el momento el puntero vale " << *puntero << endl;
*puntero = 555;
cout << "y ahora el vector vale " << v[0];
cout << "Surprise madafakaaa " << *puntero;
}