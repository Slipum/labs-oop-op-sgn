#include "addFigure.h"

AddFigureCommand::AddFigureCommand(MenuCommand* owner, vector<Figure*>* f)
    : ICommand(f), owner(owner) {
    figureCommand[CIRCLE] = make_unique<AddCircleCommand>(f);
    figureCommand[RECTANGLE] = make_unique<AddRectangleCommand>(f);
    figureCommand[TRIANGLE] = make_unique<AddTriangleCommand>(f);
    figureCommand[POLYGON] = make_unique<AddPolygonCommand>(f);
}

AddCircleCommand::AddCircleCommand(vector<Figure*>* f)
    : ICommand(f) {}
AddPolygonCommand::AddPolygonCommand(vector<Figure*>* f)
    : ICommand(f) {}
AddRectangleCommand::AddRectangleCommand(vector<Figure*>* f)
    : ICommand(f) {}
AddTriangleCommand::AddTriangleCommand(vector<Figure*>* f)
    : ICommand(f) {}


string AddCircleCommand::intro() { return "Круг"; };
string AddPolygonCommand::intro() { return "Выпуклый многоугольник"; };
string AddRectangleCommand::intro() { return "Прямоугольник"; };
string AddTriangleCommand::intro() { return "Треугольник"; };



void AddFigureCommand::InputTypeFigure() {
    printFigureTypes();
    cout << "Введите тип фигуры: ";
    cin >> currentTypeFigure;
    if (!validEnd()) {
        currentTypeFigure = ERROR;
    }
    freeInput();
}

void AddFigureCommand::exec() {
    while (true) {
        InputTypeFigure();
        try {
            auto it = figureCommand.find(currentTypeFigure);
            if (it == figureCommand.end()) {
                throw runtime_error("Некорректный пункт. Попробуйте другой из предложенных:");
            }
            it->second->exec();
            cout << "Фигура добавлена." << endl;
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
}

void AddFigureCommand::printFigureTypes() {
    for (auto &it : figureCommand)
        cout << it.first << ". " << it.second->intro() << endl;
}

string AddFigureCommand::intro() { return "Добавить фигуру"; }



void AddCircleCommand::exec() {
    Circle* f = new Circle();
    setNameFigure(f);
    bool valid;

    coord c;
    do {
        valid = true;
        cout << "Введите координаты центра: ";
        cin >> c.x >> c.y;
        if (cin.fail() || !validEnd()) {
            cout << "Введите обе координаты центра." << endl;
            freeInput();
            valid = false;
            continue;
        }
    } while (!f->setCenter(c.x, c.y, cin.fail()) || !valid);
    freeInput();

    if (valid) {
        float r;
        do {
            valid = true;
            cout << "Введите радиус: ";
            cin >> r;
            if (!validEnd()) {
                r = 0;
                valid = false;
                continue;
            }
        } while (!f->setRadius(r));
    }
    if (valid) figures->push_back(f);
}



void AddPolygonCommand::exec() {
    Polygon* f = new Polygon();
    setNameFigure(f);

    int corns;
    cout << "Введите количество вершин: ";
    cin >> corns;
    while (cin.fail() || corns < 3 || !validEnd()) {
        cout << "Некоректное количество вершин." << endl;
        cout << "Введите количество вершин: ";
        freeInput();
        cin >> corns;
    }

    vector<coord> corners;
    for (int i = 1; i < corns+1; i++) {
        this->setPolygonCorner(&corners, (to_string(i) + "-ого"));
    }
    f->setCorners(corners);

    figures->push_back(f);
}

void AddPolygonCommand::setPolygonCorner(vector<coord>* corners, string corner) {
    coord c;

    cout << "Введите координаты " << corner << " угла: ";
    cin >> c.x >> c.y;
    while (cin.fail() || !validEnd()) {
        cout << "Введите обе координаты " << corner << " угла." << endl;
        freeInput();
        cout << "Введите координаты " << corner << " угла: ";
        cin >> c.x >> c.y;
    };
    corners->push_back(c);
}



void AddRectangleCommand::exec() {
    Rectangle* f = new Rectangle();
    setNameFigure(f);
    bool valid;

    coord l;
    do {
        valid = true;
        cout << "Введите координаты левого верхнего угла: ";
        cin >> l.x >> l.y;
        if (cin.fail() || !validEnd()) {
            cout << "Введите обе координаты левого верхнего угла." << endl;
            freeInput();
            valid = false;
        }
    } while (!valid || !f->setLeftCorner(l.x, l.y, cin.fail()));

    if (valid) {
        coord r;
        do {
            valid = true;
            cout << "Введите координаты правого нижнего угла: ";
            cin >> r.x >> r.y;
            if (cin.fail() || !validEnd()) {
                cout << "Введите обе координаты правого нижнего угла." << endl;
                freeInput();
                valid = false;
            }
        } while (!valid || !f->setRightCorner(r.x, r.y, cin.fail()));
    }
    if (valid) figures->push_back(f);
}



void AddTriangleCommand::exec() {
    Triangle* f = new Triangle();
    setNameFigure(f);

    this->setTriangleCorner(f, "первого");
    this->setTriangleCorner(f, "второго");
    this->setTriangleCorner(f, "третьего");

    figures->push_back(f);
}

void AddTriangleCommand::setTriangleCorner(Triangle* f, string corner) {
    coord c;
    bool success;
    bool valid;
    do {
        valid = true;
        cout << "Введите координаты " << corner << " угла: ";
        cin >> c.x >> c.y;
        if (cin.fail() || !validEnd()) {
            cout << "Введите обе координаты " << corner << " угла." << endl;
            freeInput();
            valid = false;
            continue;
        }

        if (corner == "первого") {
            success = f->setA(c.x, c.y, cin.fail());
        } else if (corner == "второго") {
            success = f->setB(c.x, c.y, cin.fail());
        } else {
            success = f->setC(c.x, c.y, cin.fail());
        }
    } while (!success || !valid);
}