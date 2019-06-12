#ifndef move_H
#define move_H

class Move
{
	public:
		Move();
		~Move();
		int x_index;	//X (first) Index of Piece
		int y_index;	//Y (second) Index of Piece
		int finalX;		//X Destination of the move
		int finalY;		//Y Destination of the move
		int score;		//Value of the move made
};

#endif

