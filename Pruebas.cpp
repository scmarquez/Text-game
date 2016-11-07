//Prueba.cpp
#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace std;

enum DIRECCION
{
	NORTE,SUR,ESTE,OESTE,ARRIBA,ABAJO
};
class Item;
class Butom;
class Place;
class EItem;
class Event;
class Gate;
class Player;
///////////////////////////////////
		struct StateButom
		{
			Butom* B;
			bool state;
		};
		struct StateItem
		{
			Item* I;
			bool state;
		};
		struct StatePlace
		{
			Place* P;
			bool state;
		};
		struct StateEItem
		{
			EItem* EI;
			bool state;	
		};
///////////////////////////////////
class Condition{
	private:
		std::vector<StateButom> Botones;
		std::vector<StateItem> Items;
		std::vector<StatePlace> Places;
		std::vector<StateEItem> EItems;
		std::vector<Event*> Events;
	public:
		Condition(){}
		Condition(vector<StateButom> SB,vector<StateEItem> SEI,vector<StatePlace> SP,vector<StateItem> SI,vector<Event*> E){
			Botones = SB;
			Items = SI;
			EItems = SEI;
			Places = SP;
			Events = E;
		}
		void CheckCondition();
};
class Item{
	private:
		string name;
		string description;
		int ID;
		bool state;
		bool CouldGrab;
	public:
		Item(string name, string description, int ID, bool state, bool CouldGrab){
			this->name = name;
			this->description = description;
			this->ID = ID;
			this->state = state;
			this->CouldGrab = CouldGrab;
		}
		void DefaultInteract(){
			state = !state;
		}
		string GetName(){
			return name;
		}
		string GetDescription(){
			return description;
		}
		int GetID(){
			return ID;
		}
		bool GetCouldGrab(){
			return CouldGrab;
		}
		bool GetState(){
			return state;
		}
		void SetTo(bool s){
			state = s;
		}
};
class Place{
	private:
		string name;
		string description;
		string nameNecesario;
		bool state;
	public:
		Place(){}
		Place(string name, string description, string nameNecesario){
			state = false;
			this->name = name;
			this->description = description;
			this->nameNecesario = nameNecesario;
		}
		void DefaultInteract(string name){
			if(name == nameNecesario){
				state = true;
			}
		}
		string GetDescription(){
			return description;
		}
		string GetName(){
			return name;
		}
};
////////////////////////////////////////////////////////////////////////////////////////
class Gate{
	private:
		bool lock;
		string name;
		string description;
		DIRECCION dir;
	public:
		Gate(bool lock, string name, string description, DIRECCION dir){
			this->lock = lock;
			this->name = name;
			this->description = description;
			this->dir = dir;
		}
		Gate(){}
		void Interact(){
			lock = !lock;
		}
		string GetName(){
			return name;
		}
		string GetDescription(){
			return description;
		}
		bool GetLock(){
			return lock;
		}
		DIRECCION GetDirection(){
			return dir;
		}
		void Lock(){
			lock = true;
		}
		void Unlock(){
			lock = false;
		}
};
///////////////////////////////////////////////////////////////
class Butom{
	private:
		bool state;
		string name;
		string description;
	public:
		Butom(bool state, string name, string description){
			this->state = state;
			this->name = name;
			this->description = description;
		}
		Butom(){}
		void DefaultInteract(){
			state = !state;
		}
		bool GetState(){
			return state;
		}
		string GetName(){
			return name;
		}
		string GetDescription(){
			return description;
		}
};
//////////////////////////////////////////////////////////////////
class Battery{
	private:
		string name;
		string description;
		int ID;
		int Capacidad;
	public:
		Battery(string name, string description,int ID, int Capacidad){
			this->Capacidad = Capacidad;
			this->ID = ID;
			this->name = name;
			this->description = description;
		}
		Battery(){}
		bool IsEmpty(){
			if(Capacidad == 0){
				return true;
			}
			return false;
		}
		void Decrement(){
			Capacidad--;
		}
		string GetName(){
			return name;
		}
		string GetDescription(){
			return description;
		}
};
/////////////////////////////////////////////////////////////////
class EItem{
	private:
		string name;
		string description;
		int ID;
		bool state;
		bool CouldGrab;
		Battery* bateria;
	public:
		EItem(string name, string description, int ID, bool state, bool CouldGrab){
			this->name = name;
			this->description = description;
			this->ID = ID;
			this->state = state;
			this->CouldGrab = CouldGrab;
			bateria = 0;
		}
		EItem(){}
		void DefaultInteract(){
			if(bateria != 0){
				if(!bateria->IsEmpty()){
					state = !state;
				}
			}
			else{
				cout << "No parece que funcione...\n";
			}
			
		}
		string GetName(){
			return name;
		}
		string GetDescription(){
			return description;
		}
		int GetID(){
			return ID;
		}
		bool GetCouldGrab(){
			return CouldGrab;
		}
		bool GetState(){
			return state;
		}
		void ChangeBattery(Battery* bateria){
			this->bateria = bateria;
		}
		void Apagar(){
			if(bateria->IsEmpty()){
				state = false;
			}
		}
		void Desgastar(){
			if(state == true){
				bateria->Decrement();
			}
			Apagar();
		}
};
class Key{
	private:
		string name;
		std::vector<Gate*> Puertas;
		bool state;
	public:
		Key(string name, std::vector<Gate*> Puertas,bool state){
			this->name = name;
			this->Puertas = Puertas;
			this->state = state;
		}
		Key(){}
		void SetFalse(){
			state = false;
			//Cierra las puertas asignadas
			for(int i = 0;i < Puertas.size(); i++){
				//Cerrar la puerta
				Puertas[i]->Lock();
			}
		}
		void SetTrue(){
			state = true;
			//Abre las puertas asignadas
			for(int i = 0;i < Puertas.size(); i++){
				//Abrir la puerta
				Puertas[i]->Unlock();
			}
		}
		string GetName(){
			return name;
		}
		bool GetState(){
			return state;
		}
};
class Room{
	private:
		int id;
		string description;
		//Objetos de la habitación
		std::vector<Item*> Items;
		std::vector<EItem*> EItems;
		std::vector<Battery*> Batteries;
		std::vector<Key*> Keys;
		std::vector<Gate*> Puertas;
		std::vector<Place*> Places;
		std::vector<Butom*> butoms;
		std::vector<Room*> Salidas;//N,S,E,O,UP,DOWN
	public:
		Room(int id,string description,std::vector<Item*> Items,std::vector<EItem*> EItems,std::vector<Battery*> Batteries,
			std::vector<Key*> Keys,std::vector<Gate*> Puertas,std::vector<Place*> Places,std::vector<Butom*> butoms/*,
			std::vector<Room*> Salidas*/){

			this->id = id;
			this->description = description;

			this->Items = Items;
			this->EItems = EItems;
			this->Batteries = Batteries;
			this->Keys = Keys;
			this->Puertas = Puertas;//N,S,E,O,UP,DOWN
			this->Places = Places;
			this->butoms = butoms;
			//this->Salidas = Salidas;
		}
		Room(){}
		void Describe(){
			cout << description;
			cout << "Encuentras ";
			for(int i = 0; i < Items.size(); i++){
				cout << Items[i]->GetDescription() << endl;
			}
			for(int i = 0; i< EItems.size(); i++){
				cout << EItems[i]->GetDescription()<< endl;
			}
			for(int i = 0; i < Batteries.size(); i++){
				cout << Batteries[i]->GetDescription()<< endl;
			}
			for(int i = 0; i < Places.size(); i++){
				cout << Places[i]->GetDescription() << endl;
			}
			for(int i = 0; i < Keys.size(); i++){
				cout << Keys[i]->GetName();
			}
		}
		string GetDescription(){
			return description;
		}
		
		Room* GetRoom(DIRECCION dir){
			switch (dir){
				case NORTE:
					return Salidas[0];
					break;
				case SUR:
					return Salidas[1];
					break;
				case ESTE:
					return Salidas[2];
					break;
				case OESTE:
					return Salidas[3];
					break;
				case ARRIBA:
					return Salidas[4];
					break;
				case ABAJO:
					return Salidas[5];
					break;
			}
		}
		Gate* GetGate(DIRECCION dir){
			switch (dir){
				case NORTE:
					return Puertas[0];
					break;
				case SUR:
					return Puertas[1];
					break;
				case ESTE:
					return Puertas[2];
					break;
				case OESTE:
					return Puertas[3];
					break;
				case ARRIBA:
					return Puertas[4];
					break;
				case ABAJO:
					return Puertas[5];
					break;
			}
		}
		bool CanGo(DIRECCION dir){
			//Busca la puerta con la direccion dir
			Gate* p;
			p = GetGate(dir);
			if(p == 0){
				
				//No hay una puerta
				if(GetRoom(dir) != 0){
					return true;
				}
				else{
					return false;
				}
			}
			else{
				//Hay una puerta en esa direccion
				
				if(p->GetLock()){
					return false;
				}
				else{
					return true;
				}
			}
			/*
			bool found = false;
			Gate* puerta;
			for(int i = 0; i < Puertas.size() && !found;i++){
				puerta = Puertas[i];
				if(puerta->GetDirection() == dir){
					found = true;
				}
			}
			if(found){
				return !puerta->GetLock();
			}
			if(GetRoom(dir) != 0){
				return true;
			}
			return false;
			*/
		}
		///////////////////////////////////////////
		bool ExistEItem(string name){
			//Busca el Item con ese nombre en el vector
			for(int i = 0; i < EItems.size(); i++){
				if(EItems[i]->GetName() == name){
					return true;
				}
			}
			return false;
		}
		bool ExistItem(string name){
			for(int i = 0; i < Items.size(); i++){
				if(Items[i]->GetName() == name){
					return true;
				}
			}
			return false;
		}
		bool ExistButom(string name){
			for(int i = 0; i < butoms.size(); i++){
				if(butoms[i]->GetName() == name){
					return true;
				}
			}
			return false;
		}
		bool ExistBattery(string name){
			for(int i = 0; i < Batteries.size(); i++){
				if(Batteries[i]->GetName() == name){
					return true;
				}
			}
			return false;
		}
		bool ExistKey(string name){
			for(int i = 0; i < Keys.size(); i++){
				if(Keys[i]->GetName() ==name){
					return true;
				}
			}
			return false;
		}
		void SetSalidas(std::vector<Room*> Salidas){
			this->Salidas = Salidas;
		}
		////////////////////////////////////////////
		void AddItem(Item* i){
			Items.push_back(i);
		}
		void AddItem(EItem* ei){
			EItems.push_back(ei);
		}
		////////////////////////////////////////////
		Item* GetItem(string name){
			if(ExistItem(name)){
				bool found = false;
				for(int i = 0; i < Items.size();i++){
					if(Items[i]->GetName() == name){
						return Items[i];
					}
				}
			}
			return 0;
		}
		EItem* GetEItem(string name){
			if(ExistEItem(name)){
				for(int i = 0; i < EItems.size(); i++){
					if(EItems[i]->GetName() == name){
						return EItems[i];
					}
				}
			}
			return 0;
		}
		Butom* GetButom(string name){
			if(ExistButom(name)){
				for(int i = 0; i < butoms.size(); i++){
					if(butoms[i]->GetName() == name){
						return butoms[i];
					}
				}
			}
			return 0;
		}
		Battery* GetBattery(string name){
			if(ExistBattery(name)){
				for(int i = 0; i < Batteries.size(); i++){
					if(Batteries[i]->GetName() == name){
						return Batteries[i];
					}
				}
			}
			return 0;
		}
		Key* GetKey(string name){
			if(ExistKey(name)){
				for(int i = 0; i < Keys.size(); i++){
					if(Keys[i]->GetName() ==name){
						return Keys[i];
					}
				}
			}
			return 0;
		}
		/////////////////////////////////////////////
		void DeleteItem(string name){
			if(ExistItem(name)){
				bool found = false;
				for(int i = 0; i < Items.size();i++){
					if(Items[i]->GetName() == name){
						Items.erase(Items.begin()+i);
					}
				}
			}
		}
		void DeleteEItem(string name){
			if(ExistEItem(name)){
				for(int i = 0; i < EItems.size(); i++){
					if(EItems[i]->GetName() == name){
						EItems.erase(EItems.begin()+i);
					}
				}
			}
		}
		void DeleteBattery(string name){
			if(ExistBattery(name)){
				for(int i = 0; i < Batteries.size(); i++){
					if(Batteries[i]->GetName() == name){
						Batteries.erase(Batteries.begin()+i);
					}
				}
			}
		}
		void DeleteKey(string name){
			if(ExistKey(name)){
				for(int i = 0; i < Keys.size(); i++){
					if(Keys[i]->GetName() ==name){
						Keys.erase(Keys.begin()+i);
					}
				}
			}
		}	
};
///////////////////////////////////////////////////////////////////////////////////////////
class Player{
	private:
		struct Mochila{
			std::vector<Item*> Items;
			std::vector<EItem*> EItems;
			std::vector<Battery*> Batteries;
			std::vector<Key*> Keys;
		};
		Room* CurrentRoom;
		Mochila M;
	public:
		Player(Room* InitialRoom){
			CurrentRoom = InitialRoom;
		}

		void ChangeRoom(DIRECCION dir){
			if(CurrentRoom->CanGo(dir)){
				
				CurrentRoom = CurrentRoom->GetRoom(dir);
				CurrentRoom->Describe();
			}
			else{
				cout << "No puedes avanzar en esa direccion...\n";
			}
		}
		void GrabItem(string name){
			if(CurrentRoom->ExistItem(name)){
				Item* I = CurrentRoom->GetItem(name);
				if(I->GetCouldGrab() ){
					CurrentRoom->DeleteItem(name);
					M.Items.push_back(I);
					cout << "Lo tienes\n";
				}
			}
			else{
				cout << "No puedes coger eso...\n";
			}
		}
		
		void GrabEItem(string name){
			if(CurrentRoom->ExistEItem(name)){
				EItem* EI = CurrentRoom->GetEItem(name);
				if(EI->GetCouldGrab()){
					CurrentRoom->DeleteEItem(name);
					M.EItems.push_back(EI);
					cout << "Lo tienes\n";
				}
			}
			else{
				cout << "No puedes coger eso...\n";
			}
		}
		
		void GrabKey(string name){
			if(CurrentRoom->ExistKey(name)){
				Key* k = CurrentRoom->GetKey(name);
				k->SetTrue();
				CurrentRoom->DeleteKey(name);
				M.Keys.push_back(k);
				cout << "Lo tienes\n";
			}
			else{
				cout << "No puedes coger eso...\n";
			}
		}
		
		void GrabBattery(string name){
			if(CurrentRoom->ExistBattery(name)){
				Battery* B = CurrentRoom->GetBattery(name);
				CurrentRoom->DeleteBattery(name);
				M.Batteries.push_back(B);
				cout << "Lo tienes\n";
			}
			else{
				cout << "No puedes coger eso...\n";
			}
		}
		
		int SearchItem(string name){
			for(int i = 0; i < M.Items.size();i++){
				if(M.Items[i]->GetName() == name){
					return i;
				}
			}
			return -1;
		}
		
		int SearchEItem(string name){
			for(int i = 0; i < M.EItems.size();i++){
				if(M.EItems[i]->GetName() == name){
					return i;
				}
			}
			return -1;
		}
		int SearchBattery(string name){
			for(int i = 0; i < M.Batteries.size(); i++){
				if(M.Batteries[i]->GetName() == name){
					return i;
				}
			}
			return -1;
		}
		
		void DropItem(string name){
			int Pos;
			Pos = SearchItem(name);
			if(Pos != -1){
				Item* I = M.Items[Pos];
				M.Items.erase(M.Items.begin() + Pos);
				//Al soltar el objeto, lo añade a la habitación actual.
				CurrentRoom->AddItem(I);
			}
		}
		
		void DropEItem(string name){
			int Pos;
			Pos = SearchEItem(name);
			if(Pos != -1){
				EItem* EI = M.EItems[Pos];
				M.EItems.erase(M.EItems.begin() + Pos);
				//Al soltar el objeto, lo añade a la habitación actual.
				CurrentRoom->AddItem(EI);
			}
		}
		
		void PressButom(string name){
			//Busca si el botón existe en la sala
			if(CurrentRoom->ExistButom(name)){
				Butom* B = CurrentRoom->GetButom(name);
				B->DefaultInteract();
			}
			else{
				cout << "No puedes hacer eso...";
			}
		}
		
		void EquiparItem(string name, bool estado){
			int pos = SearchItem(name);
			if(pos != -1){
				M.Items[pos]->SetTo(estado);
			}
			else{
				cout << "No puedes hacer eso...\n";
			}
		}
		

		void EncenderEItem(string name, bool estado){
			int pos = SearchEItem(name);
			if(pos != -1){
				if(M.EItems[pos]->GetState() != estado){
					M.EItems[pos]->DefaultInteract();
				}
			}
			else{
				cout << "No puedes hacer eso...\n";
			}
		}

		void OpenGate(DIRECCION dir){
			Gate* p;
			p = CurrentRoom->GetGate(dir);
			if(p != 0){
				//Si la puerta existe
				if(p->GetLock()){
					cout << "No puedes abrir esta puerta.\n";
				}
				else{
					cout << "La puerta esta abierta\n";
				}
			}
		}
		
		void PutBatteryOnEI(string nameEI, string nameB){
			int posEI = SearchEItem(nameEI);
			int posB = SearchBattery(nameB);
			if(posEI != -1 && posB!= -1){
				M.EItems[posEI]->ChangeBattery(M.Batteries[posB]);
			}
			else{
				cout << "No puedes hacer eso.\n";
			}
		}
		Room* GetCurrentRoom(){
			return CurrentRoom;
		}
		bool GetStateEI(string name){
			int pos = SearchEItem(name);
			if(pos != -1){
				return M.EItems[pos]->GetState();
			}
			return false;
		}
		/*
		void PutOjbetInPlace(Place* P, Item* I){
			P->Activate(I->GetID());
		}
		*/
};
class Event{
	private:
		std::vector<Gate*> Gates;
		bool EndGame;
		string Text;
		Player* me;
	public:
		Event(){}
		Event(std::vector<Gate*> Gates,bool EndGame, string Text,Player* me){
			this->Gates = Gates;
			this->EndGame = EndGame;
			this->Text = Text;
			this->me = me; 
		}
		void Activate(){
			for(int i = 0; i < Gates.size(); i++){
				Gates[i]->Interact();
			}
			cout << Text;
			if (EndGame){
				exit(0);
			}
		}
};
void Condition::CheckCondition(){
	//Comprueba todos los botones
	bool ok = true;
	for(int i = 0; i < Botones.size() && ok;i++){
		if(Botones[i].state != Botones[i].B->GetState()){
			ok = false;
		}
	}
	//Comprueba el estado de todos los item
	for (int i = 0;i < Items.size() && ok; i++){
		if(Items[i].state != Items[i].I->GetState()){
			ok = false;
		}
	}
	//Comprueba el estado de todos los EI
	for(int i = 0; i < EItems.size() && ok; i++){
		if(EItems[i].state != EItems[i].EI->GetState()){
			ok = false;
		}
	}
}
int main(){
	/*
	//Prueba del juego con un objeto de cada cosa en 2 habitaciones
	//////////////////////////////////////////////////////////////////////////////
	Item I("Item1","Este es el item1",1,false,true);
	std::vector<Item*> ITEMS;
	Item* PunteroItem = &I;
	ITEMS.push_back(PunteroItem);
	/////////////////////////////////////////////////////////////
	Gate G(true,"Puerta1","Una puerta oxidada por poner",NORTE);
	std::vector<Gate*> GATES;
	Gate* PunteroGate = &G;
	GATES.push_back(PunteroGate);
	////////////////////////////////////////////////////////
	Butom B(false,"Boton verde","Boton oxidado tambien");
	std::vector<Butom*> BOTONES;
	Butom* punteroButom = &B;
	BOTONES.push_back(punteroButom);
	///////////////////////////////////////////////////////
	Battery bateria("Bateria 215","Bateria oxidada",215,75);
	std::vector<Battery*> BATTERIES;
	Battery* punteroBattery = &bateria;
	BATTERIES.push_back(punteroBattery);
	/////////////////////////////////////////////////////////////
	EItem linterna("linterna","linterna oxidada",1,false,true);
	std::vector<EItem*> EITEMS;
	EItem* punteroEItem = &linterna;
	EITEMS.push_back(punteroEItem);
	////////////////////////////////////////////////////////////
	Key k("llave maestra",GATES,false);
	std::vector<Key*> KEYS;
	Key* punteroKey= &k;
	KEYS.push_back(punteroKey);
	/////////////////////////////////////////////////////////////////
	Item I2("Item2","Este el item 2",2,false,true);

	std::vector<Room*> habitaciones;
	Room Hab1(1,"sala 1",ITEMS,EITEMS,BATTERIES,KEYS,GATES,BOTONES,habitaciones);
	Hab1.AddItem(&I2);
	PunteroItem = Hab1.GetItem("Item2");
	//cout << PunteroItem->GetName();
	cout << Hab1.ExistItem("Item2");
	Hab1.DeleteItem("Item2");
	cout << Hab1.ExistItem("Item2");
	*/
	//Items
	Item agua("botella con agua","una botella con agua,",1,false,true);
	Place ALI("ser reseco","un SER RESECO que no se mueve,","botella con agua");
	//PUERTAS
	Gate Gate12(true,"puerta","puerta",NORTE);
	Gate Gate36(true,"puerta","puerta",NORTE);
	Gate Gate79(true,"puerta","puerta",ESTE);
	Gate Gate910(true,"puerta","puerta",SUR);

	//Llaves
	std::vector<Gate*> GatesLlave1;
	Gate* pg = &Gate12;
	GatesLlave1.push_back(pg);
	pg = &Gate36;
	GatesLlave1.push_back(pg);
	Key Llave1("llave 1",GatesLlave1,false);

	std::vector<Gate*> GatesLlave2;
	pg = &Gate910;
	GatesLlave2.push_back(pg);
	Key Llave2("llave 2",GatesLlave2,false);
	//EItem
	EItem linterna("linterna","una linterna apagada, ",1,false,true);
	EItem radar("pantalla", "Una pantalla que se muestra apagada, ",2,false,true);
	//Baterias
	Battery pila("pila","una pila",1,5);
	//Salas
	//Room Hab1(1,"sala 1",ITEMS,EITEMS,BATTERIES,KEYS,GATES,BOTONES,habitaciones);

	//Sala1
	std::vector<Item*> ItemsS1;
	std::vector<EItem*> EItemsS1;
	std::vector<Battery*> BatteriesS1;
	std::vector<Key*> KeysS1;
	std::vector<Gate*> GatesS1;
	std::vector<Butom*> BotonesS1;
	std::vector<Place*> PlacesS1;

	pg = &Gate12;
	GatesS1.push_back(pg);
	GatesS1.push_back(0);
	GatesS1.push_back(0);
	GatesS1.push_back(0);
	Room S1(1,"Encuentras una sala vacía, bañada en una luz artificial que resalta aún más la claridad de las paredes. Hay una puerta en cada dirección",
		ItemsS1,EItemsS1,BatteriesS1,KeysS1,GatesS1,PlacesS1,BotonesS1);

	//Sala 2
	std::vector<Item*> ItemsS2;
	std::vector<EItem*> EItemsS2;
	std::vector<Battery*> BatteriesS2;
	std::vector<Key*> KeysS2;
	std::vector<Gate*> GatesS2;
	std::vector<Butom*> BotonesS2;
	std::vector<Place*> PlacesS2;

	EItem* pei = &radar;
	EItemsS2.push_back(pei);

	pg = &Gate12;
	GatesS2.push_back(0);
	GatesS2.push_back(pg);
	GatesS2.push_back(0);
	GatesS2.push_back(0); 


	Room S2(2,"En el suelo ves objetos de todo tipo rotos: herramientas, libros y desperdicios varios. No parece haber nada util.",
		ItemsS2,EItemsS2,BatteriesS2,KeysS2,GatesS2,PlacesS2,BotonesS2);

	//Sala3
	std::vector<Item*> ItemsS3;
	std::vector<EItem*> EItemsS3;
	std::vector<Battery*> BatteriesS3;
	std::vector<Key*> KeysS3;
	std::vector<Gate*> GatesS3;
	std::vector<Butom*> BotonesS3;
	std::vector<Place*> PlacesS3;

	Key* pk = &Llave1;
	KeysS3.push_back(pk);
	pg = &Gate36;
	GatesS3.push_back(pg);
	GatesS3.push_back(0);
	GatesS3.push_back(0);
	GatesS3.push_back(0);

	Room S3(3,"Únicamente hay un cartel pegado en la pared dirigido a la tripulacion del S.S.Maine dando pautas de comportamiento en caso de incendio.Ves una puerta al norte",
		ItemsS3,EItemsS3,BatteriesS3,KeysS3,GatesS3,PlacesS3,BotonesS3);

	//Sala 4
	std::vector<Item*> ItemsS4;
	std::vector<EItem*> EItemsS4;
	std::vector<Battery*> BatteriesS4;
	std::vector<Key*> KeysS4;
	std::vector<Gate*> GatesS4;
	std::vector<Butom*> BotonesS4;
	std::vector<Place*> PlacesS4;

	Battery* bp = &pila;
	BatteriesS4.push_back(bp);

	GatesS4.push_back(0);
	GatesS4.push_back(0);
	GatesS4.push_back(0);
	GatesS4.push_back(0);

	Room S4(4,"Hay un escritorio lleno de papeleo ininteligible y boligrafos rotos. La unica iluminacion de la estancia es la pequeña barra fluorescente que preside la sala desde lo alto de la mesa.",
		ItemsS4,EItemsS4,BatteriesS4,KeysS4,GatesS4,PlacesS4,BotonesS4);

	//Sala 5
	std::vector<Item*> ItemsS5;
	std::vector<EItem*> EItemsS5;
	std::vector<Battery*> BatteriesS5;
	std::vector<Key*> KeysS5;
	std::vector<Gate*> GatesS5;
	std::vector<Butom*> BotonesS5;
	std::vector<Place*> PlacesS5;

	pei = &linterna;
	EItemsS5.push_back(pei);

	GatesS5.push_back(0);
	GatesS5.push_back(0);
	GatesS5.push_back(0);
	GatesS5.push_back(0);


	Room S5(5,"Tirado en el suelo encuentras un pequeño maletin abierto y vacio. En el maletin pone -propiedad de ... Lo demas esta demasiado desgastado como para poder leerlo. Hay una puerta al oeste.",
		ItemsS5,EItemsS5,BatteriesS5,KeysS5,GatesS5,PlacesS5,BotonesS5);

	//Sala 6
	std::vector<Item*> ItemsS6;
	std::vector<EItem*> EItemsS6;
	std::vector<Battery*> BatteriesS6;
	std::vector<Key*> KeysS6;
	std::vector<Gate*> GatesS6;
	std::vector<Butom*> BotonesS6;
	std::vector<Place*> PlacesS6;

	Item* pi = &agua;
	ItemsS6.push_back(pi);

	pg = &Gate36;
	GatesS6.push_back(0);
	GatesS6.push_back(pg);
	GatesS6.push_back(0);
	GatesS6.push_back(0);

	Room S6(6,"Tan solo ves una estanteria de tres pisos casi vacia. En la estanteria ves",
		ItemsS6,EItemsS6,BatteriesS6,KeysS6,GatesS6,PlacesS6,BotonesS6);

	//Sala 7
	std::vector<Item*> ItemsS7;
	std::vector<EItem*> EItemsS7;
	std::vector<Battery*> BatteriesS7;
	std::vector<Key*> KeysS7;
	std::vector<Gate*> GatesS7;
	std::vector<Butom*> BotonesS7;
	std::vector<Place*> PlacesS7;

	Place* pp;
	pp = &ALI;
	PlacesS7.push_back(pp);
	pg = &Gate79;
	GatesS7.push_back(0);
	GatesS7.push_back(0);
	GatesS7.push_back(0);
	GatesS7.push_back(pg);

	Room S7(7,"La sala es bastante fria y limpia. La sala esta presidida por tubos de ensallo y probetas vaicias. Hay una puerta hacia el este.",
		ItemsS7,EItemsS7,BatteriesS7,KeysS7,GatesS7,PlacesS7,BotonesS7);

	//Sala8
	std::vector<Item*> ItemsS8;
	std::vector<EItem*> EItemsS8;
	std::vector<Battery*> BatteriesS8;
	std::vector<Key*> KeysS8;
	std::vector<Gate*> GatesS8;
	std::vector<Butom*> BotonesS8;
	std::vector<Place*> PlacesS8;

	pk = &Llave2;
	KeysS8.push_back(pk);

	GatesS8.push_back(0);
	GatesS8.push_back(0);
	GatesS8.push_back(0);
	GatesS8.push_back(0);

	Room S8(8,"El aire en la sala el aire es denso y las luces parpaedan constantemente. Escuchas ruidos.",
		ItemsS8,EItemsS8,BatteriesS8,KeysS8,GatesS8,PlacesS8,BotonesS8);

	//Sala 9
	std::vector<Item*> ItemsS9;
	std::vector<EItem*> EItemsS9;
	std::vector<Battery*> BatteriesS9;
	std::vector<Key*> KeysS9;
	std::vector<Gate*> GatesS9;
	std::vector<Butom*> BotonesS9;
	std::vector<Place*> PlacesS9;

	GatesS9.push_back(0);
	pg = &Gate910;
	GatesS9.push_back(pg);
	GatesS9.push_back(0);
	pg = &Gate79;
	GatesS9.push_back(pg);

	Room S9(9,"El aire en la sala el aire es denso.Hay restos de una sustancia viscosa de mal olor. Escuchas ruidos y hay una puerta al sur y otra al norte\n",
		ItemsS9,EItemsS9,BatteriesS9,KeysS9,GatesS9,PlacesS9,BotonesS9);
	//Sala 10
	std::vector<Item*> ItemsS10;
	std::vector<EItem*> EItemsS10;
	std::vector<Battery*> BatteriesS10;
	std::vector<Key*> KeysS10;
	std::vector<Gate*> GatesS10;
	std::vector<Butom*> BotonesS10;
	std::vector<Place*> PlacesS10;


	GatesS10.push_back(0);
	GatesS10.push_back(0);
	GatesS10.push_back(0);
	GatesS10.push_back(0);

	Room S10(10,"Parece que has llegado al final del juego sin morir. GG\n",
		ItemsS10,EItemsS10,BatteriesS10,KeysS10,GatesS10,PlacesS10,BotonesS10);
	//Sala11
	std::vector<Item*> ItemsS11;
	std::vector<EItem*> EItemsS11;
	std::vector<Battery*> BatteriesS11;
	std::vector<Key*> KeysS11;
	std::vector<Gate*> GatesS11;
	std::vector<Butom*> BotonesS11;
	std::vector<Place*> PlacesS11;

	GatesS11.push_back(0);
	GatesS11.push_back(0);
	GatesS11.push_back(0);
	GatesS11.push_back(0);

	Room S11(11,"Todo esta oscuro. No ves nada en absoluto. Por el eco de los ruidos parece que la sala se extiende hacia el este\n",
		ItemsS11,EItemsS11,BatteriesS11,KeysS11,GatesS11,PlacesS11,BotonesS11);

	//Init
	cout << "Bienbenido jugador.\nYo soy Ali y soy tu guia en esta aventura. Antes de comenzar me gustaria que echases un vistazo\na este pequeño tutorial.\nMi programador, que andara durmiendo supongo, me ha hecho aprender algo de vuestro idioma, pero no mucho. Dice que tiene una algoritnoseque de la leche para hacer que entienda vuestra lengua.\n Como esto es una version de prueba eso aun no esta listo.\nPero si entiendo estas cosas:\n Ve al (direccion)\n Coger (nombre de lo que quieres coger)\n Poner (algo) en (algo)\n Encender/apagar (algo)\n Abrir (direccion de la puerta)\n Si detectas algun fallo en el juego hazlo saber y mi programador lo corregira desde Granada, si no anda dormido claro...\nCuando estes listo escribe ok\n";
	string entrada;
	//Asingnar a cada sala sus salidas
	std::vector<Room*> salidas;
	Room* pr;
	//Sala 1
	pr = &S2;
	salidas.push_back(pr);
	pr = &S4;
	salidas.push_back(pr);
	pr = &S3;
	salidas.push_back(pr);
	pr = &S5;
	salidas.push_back(pr);
	S1.SetSalidas(salidas);
	salidas.clear();
	//Sala2
	pr = &S1;
	salidas.push_back(pr);
	salidas.push_back(0);
	salidas.push_back(0);
	salidas.push_back(0);
	S2.SetSalidas(salidas);
	salidas.clear();
	//Sala 3
	pr = &S6;
	salidas.push_back(pr);
	salidas.push_back(0);
	
	salidas.push_back(0);
	pr = &S1;
	salidas.push_back(pr);
	S3.SetSalidas(salidas);
	salidas.clear();
	//Sala 4
	pr = &S1;
	salidas.push_back(pr);
	salidas.push_back(0);
	salidas.push_back(0);
	salidas.push_back(0);
	S4.SetSalidas(salidas);
	salidas.clear();
	//Sala 5 
	salidas.push_back(0);
	salidas.push_back(0);
	pr = &S1;
	salidas.push_back(pr);
	pr = &S7;
	salidas.push_back(pr);
	S5.SetSalidas(salidas);
	salidas.clear();
	//Sala 6
	salidas.push_back(0);
	pr = &S3;
	salidas.push_back(pr);
	salidas.push_back(0);
	salidas.push_back(0);
	S6.SetSalidas(salidas);
	salidas.clear();
	//Sala 7
	salidas.push_back(0);
	salidas.push_back(0);
	pr = &S5;
	salidas.push_back(pr);
	pr = &S9;
	salidas.push_back(pr);
	S7.SetSalidas(salidas);
	salidas.clear();
	//Sala 8
	salidas.push_back(0);
	salidas.push_back(0);
	salidas.push_back(0);
	pr = &S11;
	salidas.push_back(pr);
	S8.SetSalidas(salidas);
	salidas.clear();
	//Sala 9
	pr = &S11;
	salidas.push_back(pr);
	pr = &S10;
	salidas.push_back(pr);
	salidas.push_back(0);
	salidas.push_back(0);
	S9.SetSalidas(salidas);
	salidas.clear();
	//sala 10
	pr = &S9;
	salidas.push_back(pr);
	salidas.push_back(0);
	salidas.push_back(0);
	salidas.push_back(0);
	S10.SetSalidas(salidas);
	salidas.clear();
	//Sala 11
	salidas.push_back(0);
	pr = &S9;
	salidas.push_back(pr);
	pr = &S8;
	salidas.push_back(pr);
	salidas.push_back(0);

	Player yo(&S1);
	
	

	while(entrada != "ok"){
		cin >> entrada;
	}	
	yo.GetCurrentRoom()->Describe();
	
	bool endGame = false;
	while(!endGame){
		if(yo.GetCurrentRoom() == &S8 && yo.GetCurrentRoom() == &S9){
			if(yo.GetStateEI("pantalla")){
				cout << "La pantalla emite una luz y un leve sonido\n";
			}
		}
		if(yo.GetCurrentRoom() == &S11 && yo.GetStateEI("linterna")){
			cout << "Una estia de aspecto intimidante esta frente a ti. Te mira y te devora. Estas muerto\n";
			endGame = true;
		}
		if(yo.GetCurrentRoom() == &S10){
			endGame = true;
		}
		if(!endGame){
			bool get = false;
			bool primera = true;
			cout << endl;
			getline(cin,entrada);
			//Busca la primera palabra de entrada
			if(entrada == "ve al norte"){
				yo.ChangeRoom(NORTE);
				get = true;
			}
			if(entrada== "ve al sur"){
				yo.ChangeRoom(SUR);
				get = true;
			}
			if(entrada == "ve al este"){
				yo.ChangeRoom(ESTE);
				get = true;
			}
			if(entrada == "ve al oeste"){
				yo.ChangeRoom(OESTE);
				get = true;
			}
			if(entrada == "coger llave 1" && yo.GetCurrentRoom() == &S3 && Llave1.GetState() == false){
				yo.GrabKey("llave 1");
				get = true;
			}
			if(entrada == "coger llave 2" && yo.GetCurrentRoom() == &S8 && Llave2.GetState() == false){
				yo.GrabKey("llave 2");
				get = true;
			}
			if(entrada == "coger pila" && yo.SearchBattery("pila") == -1 && yo.GetCurrentRoom() == &S4){
				yo.GrabBattery("pila");
				get = true;
			}
			if(entrada == "coger pantalla" && yo.GetCurrentRoom() == &S2){
				yo.GrabEItem("pantalla");
				get = true;
			}
			if(entrada == "coger linterna"){
				yo.GrabEItem("linterna");
				get = true;
			}
			if(entrada == "coger botella con agua"){
				yo.GrabItem("botella con agua");
				get = true;
			}
			if(entrada == "poner botella con agua en ser reseco" || entrada == "echar agua en ser reseco"){
				if(yo.GetCurrentRoom() == &S7 && yo.SearchItem("botella con agua") != -1){
					ALI.DefaultInteract("botella con agua");
					cout << "El ser parece que se mueve a medida que el agua toca su piel\n. Se levanta de un salto y pasa por debajo de la puerta que hay al este.\n Escuchas un crujido";
					get = true;
				}
			}
			if(entrada == "poner pila en linterna"){
				yo.PutBatteryOnEI("linterna","pila");
				get = true;
			}
			if(entrada == "poner pila en pantalla"){
				yo.PutBatteryOnEI("pantalla","pila");
				get = true;
			}
			if(entrada == "encender linterna"){
				yo.EncenderEItem("linterna",true);
				get = true;
			}
			if(entrada == "apagar linterna"){
				yo.EncenderEItem("linterna",false);
				get = true;
			}
			if(entrada == "encender pantalla"){
				yo.EncenderEItem("pantalla",true);
				get = true;
			}
			if(entrada == "apagar pantalla"){
				yo.EncenderEItem("pantalla",false);
				get = true;
			}
			if(entrada == "abrir puerta norte"){
				yo.OpenGate(NORTE);
				get = true;
			}
			if(entrada == "abrir puerta sur"){
				yo.OpenGate(SUR);
				get = true;
			}
			if(entrada == "abrir puerta este"){
				yo.OpenGate(ESTE);
				get = true;
			}
			if(entrada == "abrir puerta oeste"){
				yo.OpenGate(OESTE);
				get = true;
			}
			if(!get && !primera){
				cout << "No entiendo lo que dices, lo siento\n";
			}
			primera = false;
		}
	}
	
}