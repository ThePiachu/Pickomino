#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <vector>

using namespace std;

class random
{
	//a class for better handling of random numbers
	//this class is a singleton, since if a lot of objects
	//would want their own copy of it, srand would be called too many times
	//and some wrong data can be generated

	//example from experiance: all newly generated stars in the stars class
	//had the same position, since the class colour was using a member of this class
	//and it was being created, along with srand, between stars being created

	static random* instance;
	unsigned int tmprand, anwseru;
	int anwser;
	unsigned int randombuffersize;
	vector<unsigned int> randomnumbers;
	random():
		tmprand(0), anwseru(0), anwser(0), randombuffersize(4096)
	{
		srand((unsigned int)time(NULL));
	}
	inline
	unsigned int getrandom(void)
	{
		if (randomnumbers.empty())
		{
			return rand();
		}
		else
		{
			anwseru=randomnumbers.back();
			randomnumbers.pop_back();
			return anwseru;
		}
	}
public:
	~random()
	{
	}
	inline
	void preparerandom(unsigned int Amount=1)
	{
		for (unsigned int i=0; i<Amount; i++)
			if (randomnumbers.size()<randombuffersize)
				randomnumbers.push_back(rand());
	}
	inline
	void setrandombuffersize(const unsigned int NewSize)
	{
		randombuffersize=NewSize;
	}
	inline
	static random* getinstance()//getting instance of the singleton
	{
		if (instance==NULL)
			instance=new random();
		return instance;
	}

	inline
	char randomlowercasechar()
	{
		return (char)97+randomunsignedint('z'-'a');
	}
	inline
	float randomfloatpositive(const float& Range=1.0, const float& Offset=0.0)
	{//random positive float of range Offet - Offset+Range
		return Range*getrandom()/RAND_MAX+Offset;
	}
	inline
	float randomfloatbetween(const float& Min=0.0, const float& Max=1.0)
	{//random positive float of range Offet - Offset+Range
		return (Max-Min)*getrandom()/RAND_MAX+Min;
	}
	inline
	float randomfloatcenteredatzero(const float& Range=1.0,
			const float& Offset=0.0)
	{//random float of range Offset-Range/2 - Offset+Range/2
		return Range*(1.0f*getrandom()/RAND_MAX+Offset-0.5f)+Offset;
	}
	inline
	float randomnormalcenteredatzero(const float& Range=1.0,
			const unsigned int& Samples=4)
	{//random float of normal distribution centered at 0 with distribution from -Range/2 to Range/2
		float anwser=0.0;
		for (unsigned int i=0; i<Samples; i++)
		{
			anwser+=1.0f*getrandom()/RAND_MAX;
		}
		anwser=anwser/Samples-0.5f;//scales anwsers to +-1 range and centers it around 0
		return Range*anwser;
	}
	inline
	float randomnormalpositive(const float& Range=1.0,
			const unsigned int& Samples=4)
	{//random float of normal distribution, center at Range/2
		float anwser=0.0;
		for (unsigned int i=0; i<Samples; i++)
		{
			anwser+=1.0f*getrandom()/RAND_MAX;
		}
		anwser=anwser/Samples;
		return Range*anwser;
	}
	inline
	float randomnormalpositivecenteredatzero(const float& Range=1.0,
			const unsigned int& Samples=4)
	{//random float of half of normal distribution with center at 0
		float anwser=0.0;
		for (unsigned int i=0; i<Samples; i++)
		{
			anwser+=1.0f*getrandom()/RAND_MAX;
		}
		anwser=anwser/Samples;
		return Range*fabs(anwser-1);
	}
	inline
	unsigned int randomunsignedint(const unsigned int& Modulo=10)
	{//random unsigned int
		if (tmprand<Modulo)
			tmprand=rand();
		anwseru=tmprand%Modulo;
		tmprand=(int) tmprand/Modulo;
		return anwseru;
	}
	inline
	int randomint(const unsigned int& Modulo=10)
	{//random int
		if (tmprand<2*Modulo)
			tmprand=rand();
		anwser=tmprand%(2*Modulo)-Modulo;
		tmprand=(int) tmprand/(2*Modulo);
		return anwser;
	}
	inline
	unsigned int randomnormalunsignedint(const unsigned int& Modulo=10)
	{//random unsigned int with normal distribution centered at Modulo/2
		return (unsigned int) (Modulo*randomnormalpositive());
	}
	inline
	unsigned int randomnormalunsignedintcenteredatzero(
			const unsigned int& Modulo=10)
	{//random unsigned int of half normal distribution with center at 0
		return (unsigned int) fabs((Modulo*(randomnormalpositive()-0.5)));
	}

	
};

#endif /* RANDOM_H_ */
