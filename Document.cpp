#include "Document.h"
#include <algorithm>
#include <math.h>
#include <fstream>
#include <iostream>



Document::~Document()
{
	//std::cout<<"Object is destroyed"<<std::endl;
}



void Document::init()
{
	readWords();
	computeFrequency();

}


void Document::readWords()
{
	std::string x;
	std::ifstream inFile;

	inFile.open(name.c_str());

	//std::cout<<"Trying to open..........."<<std::endl;
	//std::cout<<"------"<<name<<"-------"<<std::endl;
	if (!inFile) {
	std::cout << "Unable to open file"<<std::endl;
	}

	while (inFile >> x) {

		//convert to lower case
		std::transform(x.begin(), x.end(), x.begin(), ::tolower);
		words.push_back(x);

	}

	inFile.close();

}

void Document::computeFrequency()
{
	for(unsigned int i=0;i<words.size();i++){
		if(frequency.find(words.at(i))!=frequency.end()){
			frequency[words.at(i)]+=1;
		}
		else{
			frequency.insert(std::make_pair(words.at(i),1));
		}

	}
}



double Document::getDistance(std::map<std::string,int>& freq_)
{
	int num_ = getInnerProduct(frequency,freq_);

	double denom_ = sqrt((double)(getInnerProduct(frequency,frequency)*getInnerProduct(freq_,freq_)));

	double val = acos(num_/denom_);

	return val;

}

int Document::getInnerProduct(std::map<std::string,int>& a,std::map<std::string,int>& b)
{
	int sum = 0;

	for(std::map<std::string,int>::iterator it=a.begin();it!=a.end();it++){
		std::map<std::string,int>::iterator fit = b.find(it->first);
		if(fit!=b.end())
			sum+=it->second*fit->second;
	}

	return sum;
}
