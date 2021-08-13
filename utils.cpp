#include "utils.h"

namespace split {

    inline string substr(string s, int start, int end) {
        return s.substr(start, end - start);
    } 

    vector<string> get_tokens(string s, string del) {
        int start = 0;
        int end = s.find(del);
        vector<string> result;
        
        while (end != -1) {
            result.push_back(substr(s, start, end));
            start = end + del.size();
            end = s.find(del, start);
        }

        result.push_back(substr(s, start, end));

        return result;
    }
}


namespace file {
    string read(const string path) {
        string filename(path);
        auto ss = ostringstream{};
        ifstream input_file(path);
        if (!input_file.is_open()) {
            cerr << "Could not open the file - '" << path << "'" << endl;
            exit(EXIT_FAILURE);
        }
        ss << input_file.rdbuf();
        return ss.str();
    }
}
