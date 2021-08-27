#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>

using namespace std;

namespace fs = filesystem;

namespace split {

    inline string substr(string s, int start, int end);

    vector<string> get_tokens(string s, string del);
}


namespace file {
    string read(const string path);
    bool fs_exists(const fs::path& p, fs::file_status s = fs::file_status{});
}


template <typename T>
void print_vector(vector<T> v);
#include "utils_t_impl.h"

#endif
