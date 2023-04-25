#include <Pixy2.h>

Pixy2 pixy;

class Position {
  private:
  int px;
  int py;

  public:
    Position();
    Position(int x, int y) {
      this->px = x;
      this->py = y;
    }

    int getX() { return this->px; }
    int getY() { return this->py; }
    void setX(int x) { this->px = x; }
    void setY(int y) { this->py = y; }
    void set(int x, int y) { 
      this->px = x;
      this->py = y;
    }
};

class Point {
  private:
  Position pos;

  
  public:
  Point();
  Point(Position pos) {
    this->pos = pos;
  }

  Position getPos() { return this->pos; }
  void setPos(Position p) { this->pos = p; }
  int getX() { return this->pos.getX(); }
  int getY() { return this->pos.getY(); }
};

class Taille {
  private:
  int x;
  int y;

  
  public:
  Taille();
  Taille(int x, int y) {
    this->x = x;
    this->y = y;
  }

  int getX() { return this->x; }
  int getY() { return this->y; }
  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
};

class Distance {
  private:
  double valeurTotal;
  double valeurX;
  double valeurY;
  Point startPoint;
  Point endPoint;

  
  public:
  Distance();

  double getValueX() { return this->valeurX; }
  double getValueY() { return this->valeurY; }
  double getValue() { return this->valeurTotal; }
  void setValueX(double v) { this->valeurX = v; }
  void setValueY(double v) { this->valeurY = v; }
  void setValue(double v) { this->valeurTotal = v; }
  Point getStartPoint() { return this->startPoint;}
  Point getEndPoint() { return this->endPoint;}
  void setStartPoint(Point p) { this->startPoint = p; }
  void setEndPoint(Point p) { this->endPoint = p; }
};

class Fleche {
  private:
  Position pos;
  Point centerPoint;
  Taille markerSize; // La taile du marqueur

  
  public:
  Fleche();

  Position getPosition() { return this->pos; }
  Point getCenterPoint() { return this->centerPoint; }
  Taille getMarkerSize() { return this->markerSize; }
  void setPosition(Position p) { this->pos = p; }
  void setCenterPoint(Point p) { this->centerPoint = p; }
  void setMarkerSize(Taille t) { this->markerSize = t; }
};



double distance(int x, int y) {
  return sqrt(x*x + y*y);
}



void setup()
{
  Serial.begin(115200);
  
  pixy.init();
}

void loop()
{ 
  pixy.ccc.getBlocks();

  Taille tailleBackground;
  Point pointCentralCible;

  int sizeBackground[2]; // 0 -> x, 1 -> y
  int centerPoint[2]; // 0 -> x, 1 -> y

  Position pos_fleche1;
  Position pos_fleche2;

  Distance dis_fleche1;
  Distance dis_fleche2;
  
  if (pixy.ccc.numBlocks)// S'il y a des blocs trouvé par la caméra
  { 
    for (int i = 0; i < pixy.ccc.numBlocks; i++)
    {
      if (pixy.ccc.blocks[i].m_signature == 1) { // Mise à jour du point centrale en ayant capturer la cible sur fond vert foncé -> 1
        tailleBackground.setX(pixy.ccc.blocks[i].m_width); // Taille x du fond de la cible
        tailleBackground.setY(pixy.ccc.blocks[i].m_height); // Taille y du fond de la cible
        
        Position posPoint;
        posPoint.setX(pixy.ccc.blocks[i].m_x/2);
        posPoint.setY(pixy.ccc.blocks[i].m_y/2);
        
        pointCentralCible.setPos(posPoint);  // Coordonnée x & y de la cible
      } else if (pixy.ccc.blocks[i].m_signature == 2) { // Flèche 1 -> un point rouge
        pos_fleche1.set(pixy.ccc.blocks[i].m_x, pixy.ccc.blocks[i].m_y);
      } else if (pixy.ccc.blocks[i].m_signature == 3) { // Flèche 2 -> un point bleu
        pos_fleche2.set(pixy.ccc.blocks[i].m_x, pixy.ccc.blocks[i].m_y);
      }
    }


    dis_fleche1.setValueX( distance( pos_fleche1.getX(), pointCentralCible.getX() ) );
    dis_fleche1.setValueY( distance( pos_fleche1.getY(), pointCentralCible.getY() ) );
    
    dis_fleche2.setValueX( distance( pos_fleche2.getX(), pointCentralCible.getX() ) );
    dis_fleche2.setValueY( distance( pos_fleche2.getY(), pointCentralCible.getY() ) );


    dis_fleche1.setValue(distance(dis_fleche1.getValueX(), dis_fleche1.getValueY());
    dis_fleche2.setValue(distance(dis_fleche2.getValueX(), dis_fleche2.getValueY());

    Serial.print("Taille X (Bg) :");
    Serial.println(tailleBackground.getX());
    Serial.print("Taille Y (Bg) :");
    Serial.println(tailleBackground.getY());

    Serial.print("Position X (Point central) :");
    Serial.println(pointCentralCible.getX());
    Serial.print("Position Y (Point central) :");
    Serial.println(pointCentralCible.getY());
    
    Serial.print("Position X (F1) :");
    Serial.println(dis_fleche1.getValueX());
    Serial.print("Position Y (F1) :");
    Serial.println(dis_fleche1.getValueY());
    Serial.print("Position X (F1) :");
    Serial.println(dis_fleche2.getValueX());
    Serial.print("Position Y (F1) :");
    Serial.println(dis_fleche2.getValueY());
    
    Serial.print("Distance (F1) :");
    Serial.println(dis_fleche1.getValue());
    Serial.print("Distance (F2) :");
    Serial.println(dis_fleche2.getValue());
  }  
}
