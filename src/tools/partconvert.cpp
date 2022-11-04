/*
PARTIO SOFTWARE
Copyright 2010 Disney Enterprises, Inc. All rights reserved

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.

* The names "Disney", "Walt Disney Pictures", "Walt Disney Animation
Studios" or the names of its contributors may NOT be used to
endorse or promote products derived from this software without
specific prior written permission from Walt Disney Pictures.

Disclaimer: THIS SOFTWARE IS PROVIDED BY WALT DISNEY PICTURES AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT AND TITLE ARE DISCLAIMED.
IN NO EVENT SHALL WALT DISNEY PICTURES, THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND BASED ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*/
#include <Partio.h>
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;
int main(int argc,char *argv[])
{
    // git@github.com:CanoeByGuitar/partio.git
    if(argc!=3){
        // 新建用法解析(.xyz)
        std::string inputDir = "/Users/wangchenhui/github/fluid-engine-dev/bin/hybrid_liquid_sim_output";
        std::string outputDir = "/Users/wangchenhui/downloads/data/";
        std::vector<std::string> fileNames;
        for(const auto &entry : fs::directory_iterator(inputDir)){
            fileNames.push_back(entry.path());
        }
        sort(fileNames.begin(), fileNames.end());
        int frame = 0;
        for(auto file : fileNames){
            char basename[256];
            snprintf(basename, sizeof(basename), "particles_%06d.bgeo", frame);
            std::string outputPath = outputDir + basename;
            Partio::convert_xyz(file, outputPath, 2.5);
            frame++;
            std::cout << frame << std::endl;
        }

    }else{
        // 原项目用法
        Partio::ParticlesData* p=Partio::read(argv[1]);
        if(p){
            Partio::print(p);
            Partio::write(argv[2],*p);
            p->release();
        }
    }
    return 0;

}
