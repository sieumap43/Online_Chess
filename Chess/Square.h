#ifndef SQUARE_H
#define SQUARE_H

class Square{
	protected:
		int red, green;
	public:
		int x,y;
		int piece_x_index, piece_y_index;	
		bool isWhite;		
		Square();
		Square(const Square& b);
		~Square();
		void setPos(int a, int b);
		void clear();
		void print();
		void glow_red();
		void glow_green();
		void stop_glowing_green();
		void update();
		void render();
};
	
class Path{
	public:
		Square* array[7];
		int size;
		int checker[2][2];
		int checker_num;
		Path();
		~Path();
		void add_checker(int x, int y);
		void append(Square* sq);
		void print();
		void clear();
};
#endif
