#include <string>


template <typename Typ> class que //это класс очереди, то, что не описано комментариями в принципе тебе не нужно, но могу рассказать PS я еще не все тестировал, совсем не все :с
{
private:
	int siz_e, ind_first, ind_last;
	int q_position;
	struct trio
	{
		int prev, next;
		Typ obj;
		trio()
		{
			prev=-1;
			next=-1;
		}
		void operator =(trio B)
		{
			obj=B.obj;
			prev=B.prev;
			next=B.next;
		}
		~trio()
		{
		  delete prev;
		  delete next;
		  delete obj;
		}
	};
	template <class T> class array
	{
	private:
		const static int ARRAY_SIZE=100;
		T mas[ARRAY_SIZE];
		int next[ARRAY_SIZE];
		int first_free;
	public:
		array()
		{
			first_free=0;
			for (int i=0; i<ARRAY_SIZE; i++)
				next[i]=i+1;
		}
		void pop(int ind)
		{
			next[ind]=first_free;
			first_free=ind;
		}
		int push(T smt)
		{
			int i=first_free;
			first_free=next[i];
			mas[i]=smt;
			return i;
		}
		T get(int i)
		{
			return mas[i];
		}
		void prisv(int ind, T smt)
		{
			mas[ind]=smt;
		}
		friend void operator=(array<T> b)
		{
		  first_free=b.first_free;
		  for (int i=0; i<ARRAY_SIZE; i++)
		  {
		    mas[i]=b.mas[i];
		    next[i]=b.next[i];
		  }
		}
		~array()
		{
		  delete[] mas;
		  delete[] next;
		  delete first_free;
		}
	};
	array <trio> arr;
public:
	que() //конструктор
	{
		siz_e=0;
		ind_first=-1;
		ind_last=-1;
		q_position=-1;
	}
	int size()//размер
	{
		return siz_e;
	}
	void pop()//удалить первый элемент
	{
		if (siz_e!=0)
		{
			int i=ind_first;
			trio smt=arr.get(i);
			ind_first=smt.next;
			arr.pop(i);
			siz_e--;
		}
	}
	int push(Typ smt)//добавить в очередь
	{
		if (siz_e==0)
		{
			trio a;
			a.obj=smt;
			int i=arr.push(a);
			ind_first=i;
			ind_last=i;
		}
		else
		{
			int i=ind_last;
			trio a;
			a.prev=i;
			a.obj=smt;
			ind_last=arr.push(a);
			a=arr.get(i);
			a.next=ind_last;
			arr.prisv(i, a);
		}
		siz_e++;
		return ind_last;
	}
	void to_begin()
	{
	  q_position=ind_first;
	}
	Typ get_next()
	{
	  trio smt=arr.get(q_position);
	  q_position=smt.next;
	}
	void pop_el(int ind)
	{
	  if (siz_e==1||ind==ind_first())
	    pop();
	  else if(ind==ind_last;)
	  {
	    trio smt=arr.get(ind_first);
	    smt.next=-1;
	    arr.prisv(ind_first, smt);
	    arr.pop(ind);
	  }
	  else
	  {
	    trio smt1=arr.get(ind);
	    int x=smt1.prev;
	    int y=smt1.next;
	    arr.pop(ind);
	    smt1=arr.get(x);
	    trio smt2=arr.get(y);
	    smt1.next=y;
	    smt2.prev=x;
	    arr.prisv(x, smt1);
	    arr.prisv(y, smt2);
	  }
	  siz_e--;
	}
	Typ get_el(int ind)
	{
	  return arr.get(ind).obj;
	}
	void prisv_el(int ind, Typ el)
	{
	  trio smt=arr.get(ind);
	  smt.obj=el;
	  arr.prisv(ind, smt);
	}
	Typ get()//вернуть первый элемент
	{
		trio smt=arr.get(ind_first);
		return smt.obj;
	}
	friend void operator =(que<Typ> b, que&)
	{
	  siz_e=b.siz_e;
	  ind_first=b.ind_first;
	  ind_last=b.ind_last;
	  arr=b.arr;
	  q_position=b.q_position;
	}
	~que()
	{
	  delete si_ze;
	  delete ind_first;
	  delete ind_last;
	  delete arr;
	  delete q_position;
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
	//разные операторы для изменения координат
	void operator >>()
	{
	  x++;
	  y++;
	}
	void operator <<()
	{
	  x--;
	  y++;
	}
	void operator ++()
	{
	  x++;
	  y--;
	}
	void operator --()
	{
	  x--;
	  y--;
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
	bool type;
	position start;
	position finish;
	static const bool hod=false;
	static const bool rubit=true;
	bool operator =(Move b)
	{
	  start=b.start;
	  finish=b.finish;
	  type=b.type;
	}
	~Move()
	{
	  delete start;
	  delete finish;
	  delete type;
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
	Draught()//нужен второй конструктор для меня
	{
	  pos.x=-1;
	  pos.y=-1;
	  color=-1;
	}
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
  int **Pol
  que <Draught> White_och;
  que <Draught> Black_och;
public:
  // первая координата пусть будет х, вторая - у (x - по горизонтали)
  pole() //конструктор
  {
    PL=new char *[N];
    Pol=new int *[N];
    int x, y;
    for (x=0; x<N; x++)
    {
      PL[x]=new char[N];
      Pol[x]=new int[N];
    }
    for (x=0; x<N; x++)
      for (y=0; y<N; y++)
	Pol[x][y]=-1;
    //тут мы типа расставляем фигурки
    for (x=0; x<N; x++)
      for (y=0; y<3; y++)
      {
	if (y%2==0)
	{
	  if (x%2==0)
	  {
	    PL[x][y]=White;
	    Pol[x][y]=White_och.push(Draught(x, y, 1));
	  }
	  else
	    PL[x][y]=Empty;
	}
	else
	{
	  if (x%2==1)
	  {
	    PL[x][y]=White;
	    Pol[x][y]=White_och.push(Draught(x, y, 1));
	  }
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
	  {
	    PL[x][y]=Black;
	    Pol[x][y]=Black_och.push(Draught(x, y, 2));
	  }
	  else
	    PL[x][y]=Empty;
	}
	else
	{
	  if (x%2==1)
	  {
	    PL[x][y]=Black;
	    Pol[x][y]=Black_och.push(Draught(x, y, 2));
	  }
	  else
	    PL[x][y]=Empty;
	}
      }
     //вот до этого места
  }
  void mov(Move b)//делает ход или рубит, если надо
  {
    
  }
  que <Move> get_Kill_white()//возвращает очередь ходов для белых, где рубят черные фигуры
  {
    
  }
  que <Move> get_Kill_black()//возвращает очередь ходов для черных, где тоже рубят
  {
    
  }
  //тут ходы, которые не приводят к срубленным фигурам
  que <Move> get_Move_white()//возвращает очередь ходов для белых
  {
    
  }
  que <Move> get_Move_black()//возвращает очередь ходов для черных
  {
    
  }
  que <Draught> get_black_positions()//возвращает очередь, в которой позиции черных
  {
    return Black_och;
  }
  que <Draught> get_white_positions()//возвращает очередь, в которой позиции белых
  {
    return White_och;
  }
  ~pole()
  {
    delete White_och;
    delete Black_och;
    for (int i=0; i<N; i++)
    {
      delete[] PL[i];
      delete[] Pol[i];
    }
    delete[] PL;
    delete[] Pol;
  }
};



class Player//игрок, у него есть имя, ход/неход, цве, очки.
{
private:
	bool turn;
	std::string name;
	char color;
	int points;
public:
	Player()
	{
		turn = false;
		points = 0;
	}

	Player(bool turn, std::string name, char color)
	{

	}

	void setTurn(bool a)
	{
		this->turn = a;
	}

	bool getTurn()
	{
		return this->turn;
	}
	
	void setColor(char a)
	{
		this->color = a;
	}

	char getColor()
	{
		return this->color;
	}
	
	void setPoints(int a)
	{
		this->points = a;
	}

	int getPoints()
	{
		return this->points;
	}
	void addPoint()
	{
		this->points++;
	}
	void setName(std::string a)
	{
		this->name = a;
	}
	void getName()
	{
		return this->name;
	}

};