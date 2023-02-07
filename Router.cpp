#include "Router.h"
#include "hash.h"
/*          Metodos Router      */

void Router::enviarPaquete(){

}

void Router::recibirPag(Pagina* p){

    
    //this->listaDePaginas->addFinal(p);
    for (int i = 0 ; i < p->getTamanioDePag();i++){
        Paquete* pkg = new Paquete (i,p,p->getOrigen(),p->getDestino(), p->getTamanioDePag());
        cout<<"\n Paquete"<<endl;
        cout<<i << p->getidentificadorDePag()<<" "<<p->getOrigen()[0]<<"=>"<<p->getDestino()[0]<<endl;
        //this->addPaquete(pkg);
        this->paquetes->addFinal(pkg);
    }

    // empaque -> imprimir();
    //this->empaquetador = empaque;

}


void Router::agregarPagina(Pagina* p){
    this->listaDePaginas->addFinal(p);
}


void Router::segmentarPag(){
    Nodo<Pagina*>* aux;
    aux = listaDePaginas->comienzo();
    int identificador;
    for (int i = 0 ; i < listaDePaginas->size();i++){
        int tamanioDePaquetes = (10 * aux->get_dato()->getTamanioDePag())/100;
        int cantidadDePaquetes = aux->get_dato()->getTamanioDePag()/tamanioDePaquetes;    
        for (int j = 0 ; j < cantidadDePaquetes;j++){
            
          //  Paquete* paq = new Paquete(j,aux->get_dato(), aux->get_dato()->getOrigen(),aux->get_dato()->getDestino(),tamanioDePaquetes );
               
          //  colaDeEnvio->addFinal(paq);    
            
        }
        aux = aux->get_next();
    }
}

void Router::agregarTerminal(Terminal* t){
   // cout<<"Reconocido desde el router"<<endl;
    t->conectarseAUnRouter(this);
    terminalesConectados->addFinal(t);
}

void Router::agregarVecino(int id) {
    Router* r = new Router(id);
    //cout<<"Tengo un vecino nuevo y es el router de id "<<id<<endl;
    listaDeVecinos->addFinal(r);
}

void Router::imprimirTerminales(){
    Nodo<Terminal*>* aux;
    aux= terminalesConectados->comienzo();
    cout<<"\nSOY EL ROUTER "<<id<<" y estos son los terminales que tengo conectados: "<<endl;

    for (int i =0; i< terminalesConectados->size() ; i++){
        cout<< aux->get_dato()->getIP()<<endl;
        aux = aux->get_next();
    }
}

void Router::imprimirVecinos(){
    Nodo<Router*>* aux;
    aux = listaDeVecinos->comienzo();
    cout<<"\nSoy el router "<<id<<" y estos son mis vecinos: "<<endl;
    for (int i =0;i <listaDeVecinos->size();i++){
        cout<<aux->get_dato()->getID()<<endl;
        aux = aux->get_next();
    }

}

void Router::imprimirPaginas(){
    Nodo<Pagina*>* aux;
    aux = listaDePaginas->comienzo();

    for(int i = 0; i < listaDePaginas->size(); i++)
    {
        cout<<"\nDatos de pagina: "<<endl;
        cout<<"identificador: "<<aux->get_dato()->getidentificadorDePag()<<endl;
        cout<<"tamanio: "<<aux->get_dato()->getTamanioDePag()<<endl;
        cout<<"origen: "<<aux->get_dato()->getOrigen()[1]<<endl;
        cout<<"destino: "<<aux->get_dato()->getDestino()[1]<<endl;
    }
    
}

void Router::imprimirPaquetes(){
   // empaquetador = new SistemaEmpaquetado();
    cout<<"\nSoy el router "<<this->getID()<<endl;
    cout<<"Paquetes que tengo :"<<endl;
    Nodo<Paquete*>* aux;
    aux = paquetes->comienzo();
    for (int i = 0 ; i < paquetes->size();i++){
        cout<<aux->get_dato()->getNumeroDePaquete()<<" paquete de " <<aux->get_dato()->getPaginaMadre()->getOrigen()[0]<<
        aux->get_dato()->getDestino()[0]<<aux->get_dato()->getEstado()<<endl;
        aux = aux ->get_next();
    }
   // this->empaquetador.imprimir();
}

void Router::imprimirLazosConectados(){
    Nodo<LazoDeConexion*>* aux;
    aux = this->ida->comienzo();
    cout<<"\nSoy el router "<<this->getID()<<" y estos son los lazos:"<<endl;
    cout<<"de ida: "<<endl;
    for (int i =0;i<ida->size();i++){
        cout<<aux->get_dato()->getTerminal1()<<" ----> "<<aux->get_dato()->getTerminal2()<<endl;
        aux = aux->get_next();
    }
    aux = this->vuelta->comienzo();
    cout<<"de veulta"<<endl;
    for (int i =0;i<vuelta->size();i++){
        cout<<aux->get_dato()->getTerminal1()<<" ----> "<<aux->get_dato()->getTerminal2()<<endl;
        aux=aux->get_next();
    }

}

int Router::comprobarDestino(int dir){
    
    for (int i = 0 ; i < ida ->size() ; i ++){
        //cout<<f;
        if ( ida->buscarPorIndice(i)->getTerminal2() == dir){
           return i;
        }
    }
    return 9999;

}

void Router::sacarPkg(Paquete * r){

        
    for(int i = 0 ; i < paquetes->size();i++){
        if(r == paquetes->buscarPorIndice(i)){
            paquetes->borrar();
        }
    }
    

}


void Router::enviarPaquetes(){

    bool aux;
    int x ;
    if (paquetes->esvacia()){
        cout<<"no hay paquetes para este router"<<endl;
    }else{
        
        for(int i = 0 ; i < paquetes->size() ; i ++){
            int x =comprobarDestino(paquetes->buscarPorIndice(i)->getDestino()[0]);
            
            if (x!=9999){
                int l = paquetes->buscarPorIndice(i)->getNumeroDePaquete();
                cout<<"Envio directo a porque es vecino "<< /* paquetes->buscarPorIndice(i)->getDestino()[0]<<x<*/endl;
                ida->buscarPorIndice(x)->cargarPkg(paquetes->buscarPorIndice(i));
                paquetes->buscarPorIndice(i)->setEstado();
                //sacarPkg(paquetes->buscarPorIndice(i));
               // cout<<"borre "<<l<<endl;
                

            }else if(int y = buscarEnTabla(paquetes->buscarPorIndice(i)->getDestino()[0])!=9999){
                int l = paquetes->buscarPorIndice(i)->getNumeroDePaquete();
                cout<<"no tengo camino directo pero tengo ruta"<<endl;
                ida->buscarPorIndice(y)->cargarPkg(paquetes->buscarPorIndice(i));
                paquetes->buscarPorIndice(i)->setEstado();
               // sacarPkg(paquetes->buscarPorIndice(i));
                //paquetes->borrar();
               
            }else{
                cout<<"no hay ruta para este paquete :( "<<endl;
            }
        }
    }

}



void Router::recibirPaquetes(){

    cout<<this->id<<endl;
    if (!vuelta->esvacia()){
       // cout<<this->id<<" puedo recibir"<<endl;
        for (int i =0 ; i < vuelta->size();i++){
            if(vuelta->buscarPorIndice(i)->vacia()==true){
                cout<<"Vacia"<<endl;
            }else{
                int cont = vuelta->buscarPorIndice(i)->getcolaconectora()->size()-1;
                while(cont>=0/*vuelta->buscarPorIndice(i)->vacia()!=true*/){
                    Paquete* pkg0 = vuelta->buscarPorIndice(i)->leerPkg();
                    
                    if (pkg0!=NULL){
                        this->vincularConKey(pkg0);
                        //this->hash->agregarH(pkg0);
                        cout<<"soy "<<this->id<<"y lei"<<pkg0->getNumeroDePaquete()<<" "<<pkg0->getPaginaMadre()->getidentificadorDePag()<<endl;
                    }         
                    cont--;
                }
            }
        }
    }
}

void Router::vincularConKey(Paquete* p){
    if(p->getDestino()[0]!=this->id){
        cout<<"el paquete no es parami"<<endl;
        p->setEstado1();
        paquetes->addFinal(p);
        
    }else{
        int i = p->getPaginaMadre()->getidentificadorDePag();
        D[i].addFinal(p);
        if(D[i].size()==10){
        cout<<"completaste la pagina";
        
    }

    }
    

}

bool Router::esVecino(int id){
    bool respuesta = false;
    Nodo<Router*>* aux;
    aux = listaDeVecinos->comienzo();
    for (int i =0 ; i < listaDeVecinos->size();i++){
        if(aux->get_dato()->getID()==id){
            respuesta= true;
            return respuesta;
        }
        aux = aux->get_next();

    }
    return respuesta;

}


void Router::setTabla(Lista<Direccion*>* nuevaTabla){
    this->tabla = nuevaTabla;

}

void Router::imprimirTabla(){
    Nodo<Direccion*>* aux;
    aux = tabla->comienzo();
    cout<<"Soy "<<this->id<<" y esta es mi tabla para los que no conozco: "<<endl;
    for (int i = 0 ; i < tabla->size();i++){
        cout<<"["<<aux->get_dato()->getDestino_D()<<"] enrutar a ->"<<aux->get_dato()->getCamino_D()<<endl;
        aux = aux->get_next();
    }
}

int Router::buscarEnTabla(int destinoDePkgABuscar){
    int r =9999;
    //cout<<tabla->size()<<endl;
    for (int i = 0 ; i< tabla->size() ; i++){
        if(tabla->buscarPorIndice(i)->getDestino_D() == destinoDePkgABuscar){   //tengo en la ruta
           // cout<<"paquete de "<<tabla->buscarPorIndice(i)->getDestino_D()<<" tiene que tomar la ruta de "<<tabla->buscarPorIndice(i)->getCamino_D()<<endl;
            r= tabla->buscarPorIndice(i)->getCamino_D();
        }
    }
    return r;


}