/* This file is part of the Pangolin Project.
 * http://github.com/stevenlovegrove/Pangolin
 *
 * Copyright (c) 2013 Steven Lovegrove
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PANGOLIN_FILE_UTILS_H
#define PANGOLIN_FILE_UTILS_H

#include <string>
#include <vector>

namespace pangolin
{

std::vector<std::string>& Split(const std::string& s, char delim, std::vector<std::string>& elements);

std::vector<std::string> Split(const std::string &s, char delim);

std::vector<std::string> Expand(const std::string &s, char open='[', char close=']', char delim=',');

std::string PathParent(const std::string& path);

bool FileExists(const std::string& filename);

std::string PathExpand(const std::string& sPath);

bool MatchesWildcard(const std::string& str, const std::string& wildcard);

bool FilesMatchingWildcard(const std::string& wildcard_file_path, std::vector<std::string>& file_vec);

}

#endif // PANGOLIN_FILE_UTILS_H
