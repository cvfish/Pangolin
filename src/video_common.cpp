/* This file is part of the Pangolin Project.
 * http://github.com/stevenlovegrove/Pangolin
 *
 * Copyright (c) 2011 Steven Lovegrove
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

#include <pangolin/video_common.h>

#include <vector>
#include <boost/algorithm/string.hpp>

namespace pangolin
{

const VideoPixelFormat SupportedVideoPixelFormats[] =
{
    {"GRAY8", 1, {8}, 8, false},
    {"GRAY16LE", 1, {16}, 16, false},
    {"Y400A", 2, {8,8}, 16, false},
    {"RGB24", 3, {8,8,8}, 24, false},
    {"BGR24", 3, {8,8,8}, 24, false},
    {"YUYV422", 3, {4,2,2}, 16, false},
    {"RGBA",  4, {8,8,8,8}, 32, false},
    {"",0,{0,0,0,0},0,0}
};

VideoPixelFormat VideoFormatFromString(const std::string& format)
{
    for(int i=0; !SupportedVideoPixelFormats[i].format.empty(); ++i)
        if(!format.compare(SupportedVideoPixelFormats[i].format))
            return SupportedVideoPixelFormats[i];
    throw VideoException("Unknown Format",format);
}

std::ostream& operator<< (std::ostream &out, Uri &uri)
{
    out << "scheme: " << uri.scheme << std::endl;
    out << "url:    " << uri.url << std::endl;
    out << "params:" << std::endl;

    for( Uri::ParamMap::const_iterator ip = uri.params.begin();
         ip != uri.params.end(); ++ip)
    {
        std::cout << "\t" << ip->first << " = " << ip->second << std::endl;
    }
    
    return out;
}

Uri ParseUri(std::string str_uri)
{
    Uri uri;
    
    // Find Scheme delimiter
    size_t ns = str_uri.find_first_of(':');
    if( ns != std::string::npos )
    {
        uri.scheme = str_uri.substr(0,ns);
    }else{
//        throw VideoException("Bad video URI","no device scheme specified");
        uri.scheme = "file";
        uri.url = str_uri;
        return uri;
    }
    
    // Find url delimiter
    size_t nurl = str_uri.find("//",ns+1);
    if(nurl != std::string::npos)
    {
        // If there is space between the delimiters, extract protocol arguments
        if( nurl-ns > 1)
        {
            if( str_uri[ns+1] == '[' && str_uri[nurl-1] == ']' )
            {
                std::string queries = str_uri.substr(ns+2, nurl-1 - (ns+2) );
                std::vector<std::string> params;
                boost::split(params, queries, boost::is_any_of(","));
                for(size_t i=0; i< params.size(); ++i)
                {
                    std::vector<std::string> args;
                    boost::split(args, params[i], boost::is_any_of("=") );
                    std::string key = args[0];
                    std::string val = args.size() > 1 ? args[1] : "";
                    boost::trim(key);
                    boost::trim(val);
                    uri.params[key] = val;
                }
            }else{
                throw VideoException("Bad video URI");
            }
        }
        
        uri.url = str_uri.substr(nurl+2);
    }
    
    return uri;
}

}
