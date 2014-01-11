#include <iostream>
#include <string>
#include <vector>

class Conf{
	private:
		int         num_sources;
		int         num_dests;
		std::string frequency;
		std::string source;
		std::string dest;
		std::vector<std::string> source_v;
		std::vector<std::string> dest_v;

    public:
        Conf();
		void Init_config();
		int Write_to_file(std::vector<std::string>, std::vector<std::string>, std::string);

};







