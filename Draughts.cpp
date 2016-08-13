template <class T>
class list() //двусвязный список, пусть тут полежит
{
  struct trio //что-то Волковым запахло
  {
    T obj;
    int prev;
    int next;
    bool operetor=(trio b)
    {
      obj=b.obj;
      prev=b.prev;
      next=b.next;
    }
    ~trio()
    {
      delete T;
      delete prev;
      delete next;
    }
  }
};



struct position//координаты, решил сделать структурой
{
	int x;
	int y;
	void operator =(position b)
	{
	  x=b.x;
	  y=b.y;
	}
	bool operator ==(position b)
	{
	  return x==b.x&&y==b.y;
	}
	bool operator !=(position b)
	{
	  return !((*this)==b);
	}
	~position() // деструктор, в С++ нет сборщика мусора, как привыкли некоторые Java программисты
	{
	  delete x;
	  delete y;
	};
};



class Move
{
public:
	position start;
	position finish;
	~Move()
	{
	  delete start;
	  delete finish;
	}
};


class Draught {
private:
	bool dame = false;//дамка не дамка
	int color;//цвет будет интом 1-белая 2-черная
	position pos;
public:	
	static const int Black=2;
	static const int White=1; // как чуть ниже хочу реализовать
	Draught(int X, int Y, int Color)//конструктор; можем априори говорить что любая шашка не дамка, тогда конструктор переделаю;
	{
		pos.x = X;
		pos.y = Y;
		color = Color;
	}
	void man_to_dame()//превращаем в дамку
	{
		this->dame = true;
	}
	
	int getColor()
	{
		return this->color;
	}
	bool getDame()
	{
		return this->dame
	}
	position getPos()
	{
		return this->pos;
	}
	void mov(Move q)
	{
		pos=q.finish;
	}
	~Draught()
	{
	  delete dame;
	  delete color;
	  delete pos;
	}
};

class pole
{
private:
  static const char Black=0; //немножко констант для поля, ну, понимаешь, зачем так делается? это не цвет клеток, а цвет шашек на них
  static const char White=1;
  static const char Empty=-1;
  static const int N=8;
  char **PL; //само поле типа
  // первая координата пусть будет х, вторая - у (x - по горизонтали)
public:
  pole() //конструктор
  {
    PL=new char *[N];
    int x, y;
    for (x=0; x<N; x++)
    {
      PL[x]=new char[N];
    }
    //тут мы типа расставляем фигурки
    for (x=0; x<N; x++)
      for (y=0; y<3; y++)
      {
	if (y%2==0)
	{
	  if (x%2==0)
	    PL[x][y]=White;
	  else
	    PL[x][y]=Empty;
	}
	else
	{
	  if (x%2==1)
	    PL[x][y]=White;
	  else
	    PL[x][y]=Empty;
	}
      }
     for (x=0; x<N; x++)
      for (y=N-3; y<N; y++)
      {
	if (y%2==0)
	{
	  if (x%2==0)
	    PL[x][y]=Black;
	  else
	    PL[x][y]=Empty;
	}
	else
	{
	  if (x%2==1)
	    PL[x][y]=Black;
	  else
	    PL[x][y]=Empty;
	}
      }
     //вот до этого места
  }
};
