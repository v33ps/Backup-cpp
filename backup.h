#include "configure.h"

#include <sstream>

class Backup{
    private:
        time_t                      raw_time;
        struct tm*                  timeinfo;
        char                        buffer[80];
        std::string                 str_time;
        std::string                 path;
        std::string                 line;
        std::string                 freq;
        std::vector<std::string>    source_v;
        std::vector<std::string>    dest_v;
        int                         interval;
        std::string                 time_type;
        std::string                 garbage_collector;
        std::string                 date;
        std::string                 dirName;
        std::string                 dest_temp;
        std::string                 source_temp;

    public:
        Backup();
        void Create_backup(std::vector<std::string>, std::vector<std::string>);
        bool Read_file();
        bool analyze_freq(std::string);
        std::string path_join(std::string, std::string);
        std::string get_time();
        void Copy_assist(std::string, std::string);

};