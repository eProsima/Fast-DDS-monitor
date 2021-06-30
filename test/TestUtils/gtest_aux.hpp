// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file gtest_aux.hpp
 */

#ifndef _EPROSIMA_FASTDDS_STATISTICS_BACKEND_TEST_GTEST_AUX_HPP_
#define _EPROSIMA_FASTDDS_STATISTICS_BACKEND_TEST_GTEST_AUX_HPP_

#ifdef _WIN32

#include <stdio.h>

int __cdecl chdir(
        char const* _Path);
FILE* __cdecl fdopen(
        int _FileHandle,
        char const* _Format);
int __cdecl read(
        int _FileHandle,
        void* _DstBuf,
        unsigned int _MaxCharCount);
int __cdecl write(
        int _FileHandle,
        void const* _Buf,
        unsigned int _MaxCharCount);
int __cdecl close(
        int _FileHandle);

#endif // _WIN32

#endif // _EPROSIMA_FASTDDS_STATISTICS_BACKEND_TEST_GTEST_AUX_HPP_

