#pragma once
class block
{
private :
	int x_pos;
	int y_pos;
	int rotation;
	int block_type;

public :
	block();
	~block();

	void move(int x_pos, int y_pos);
	void rotate();
	void dropDown();






	/********************get - set*********************/
	int getXpos() {
		return this->x_pos;
	}
	void setXpos(int x_pos) {
		this->x_pos = x_pos;
	}
	int getYpos() {
		return this->y_pos;
	}
	void setYpos(int y_pos) {
		this->y_pos = y_pos;
	}
	int getRotation() {
		return this->rotation;
	}
	void setRotation(int rotation) {
		this->rotation = rotation;
	}
	int getBlockType() {
		return this->block_type;
	}
	void setBlockType(int block_type) {
		this->block_type = block_type;
	}
	/**************************************************/

};

