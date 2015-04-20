#include <iostream>
#include "Document.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <memory>



int getFilesFromDir(std::string& dir,std::vector<std::string>& files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir <<std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
    		if(dirp->d_name[0]!='.')
            	files.push_back(std::string(dirp->d_name));
        }

    closedir(dp);
    return 0;
}




int main(int argc,char**argv)
{
	//folder path
	std::string folder(argv[1]);

	//sample text file
	std::string samplefile(argv[2]);

	//list of file names
	std::vector<std::string> files;


	//get file names from directory
	int n = getFilesFromDir(folder,files);

	std::cout<<"Files found are......"<<std::endl;

	for(unsigned int i=0;i<files.size();i++){	
		std::cout<<i+1<<":- "<<files.at(i)<<std::endl;
	}


	std::map<double,std::string> docDistance;

	//sample text
	std::unique_ptr<Document> sampleText(new Document(samplefile));

	//initialize sample and compute frequency
	sampleText->init();

	for(unsigned int i=0;i<files.size();i++)
	{
		//add folder path to name of files
	    std::string filePath = folder + "/" +  files.at(i);

		std::unique_ptr<Document> compareText(new Document(filePath));
		
		//init and get frequency
		compareText->init();

		//get document distance
		double distance = compareText->getDistance(sampleText->frequency);

		docDistance.insert(std::make_pair(distance,files.at(i)));

	}

	int count =0;

	std::cout<<"The three most similar files are"<<std::endl;

	for(std::map<double,std::string>::iterator it = docDistance.begin();
		it!=docDistance.end();it++){
		if(count==3)
			break;
		++count;
		std::cout<<(it)->second<<" value "<<it->first<<std::endl;
		}

	return 0;


}







