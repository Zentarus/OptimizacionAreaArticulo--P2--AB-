
class Articulo {
public:
    int x;
    int y;
    int ancho;
    int alto;
    int area;

    Articulo(int _x, int _y, int _ancho, int _alto) :
        x(_x), y(_y), ancho(_ancho), alto(_alto) {
            area = _ancho * _alto;
        }

    Articulo() :
        Articulo(0, 0, 0, 0) {}
};

class Pagina {
public:
    int num_articulos;
    int ancho;
    int alto;
    int area;
    Articulo* articulos;

    Pagina(int _num_articulos, int _ancho, int _alto) :
        num_articulos(_num_articulos), ancho(_ancho), alto(_alto) {
            articulos = new Articulo[num_articulos];
            area = _ancho * _alto;
    }

    ~Pagina() {
        delete[] articulos;
    }
};