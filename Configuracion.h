#ifndef CONFIGURACION_H
#define CONFIGURACION_H

class Configuracion {
	private:
		int colorRutas;
		int colorNodos;
	public:
		void run();
		int getColorRuta(){
			return colorRutas;
		}
		int getColorNodo(){
			return colorNodos;
		}
		void setColorRuta(int color){
			colorRutas=color;
		}
		void setColorNodo(int color){
			colorNodos=color;
		}
};

#endif
