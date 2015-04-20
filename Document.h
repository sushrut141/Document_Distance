#ifndef DOC_H_
#define DOC_H_

#include <string>
#include <vector>
#include <map>


class Document
{
public:
	Document(std::string a):name(a){}
	~Document();

	void init();

	double getDistance(std::map<std::string,int>& frequency);

	//frequency distribition
	std::map<std::string,int> frequency;

private:

	void readWords();

	void computeFrequency();

	int getInnerProduct(std::map<std::string,int>& a,std::map<std::string,int>& b);

	//name of file
	std::string name;

	//words in file
	std::vector<std::string> words;

};

#endif
