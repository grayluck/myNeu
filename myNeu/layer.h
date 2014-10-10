
#ifndef _LAYER_H_
#define _LAYER_H_

class Layer
{
public:
	Layer();
	enum Typ{
		BP = 0, CNN = 1
	} typ;
	virtual void forward() = 0;
	virtual void backward() = 0;
	Layer* last;
};

class BPLayer : public Layer
{
public:
	BPLayer(int n, Layer* last = 0);
	void forward();
	void backward();
};

#endif
