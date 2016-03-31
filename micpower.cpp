/*
 *  Intel MIC / KNC Power measurements 
 * 
 *  Copyright (C) 2016 by Fabio Baruffa <fbaru.dev@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>. 
 *
 */


#include "micpower.hpp"

micpower::micpower() { outputFile.open(LOG_FILE); }

void micpower::start()
{
  stopRead = false;
  std::thread micThread(&micpower::recordDataFromThread,this);

  micThread.detach();
}

void micpower::stop()
{  
  stopRead = true;
}

void micpower::recordDataFromThread()
{
  unsigned long long int n=0;
  unsigned long long int rate = SAMPLING_RATE_MS*MICRO_SECOND_MULTIPLIER;
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  
  outputFile << "=== Time Stamp of the reading: " << buf <<  std::endl;
  
  while(1)
  {
    micCounts.push_back(n*SAMPLING_RATE_MS); 
    readSysFile();
    usleep(rate);
    //std::this_thread::sleep_for(std::chrono::milliseconds(SAMPLING_RATE_MS));
    //it does not compile with option -mmic
    n++;
    if(stopRead)
    {
      break;
    }
  }
}

void micpower::readSysFile()
{
  inputFile.open(PATH_TO_FILE);
  
  std::string line;
  
  if (inputFile.is_open())
  {
    for(int i=0; i < MICPOWER_MAX_COUNTERS-9; i++)
    {
      getline (inputFile,line);
      unsigned long long ull = std::stoull (line,nullptr,0);
      micCounts.push_back(ull); 
    }
    for(int i = MICPOWER_MAX_COUNTERS - 9; i < 10; i++)
    {
      getline(inputFile, line);
      std::stringstream ss(line); 
      std::string aux;
      while( getline(ss, aux, ' ') )
      {
	unsigned long long ull = std::stoull (aux,nullptr,0);
	micCounts.push_back(ull); 
      }
    }
    inputFile.close();
  }
  std::ostream_iterator<unsigned long long> output_iterator(outputFile, ",");
  std::copy(micCounts.begin(), micCounts.end(), output_iterator);
  outputFile << std::endl;
  micCounts.clear();
  
//  for (auto i = micCounts.begin(); i != micCounts.end(); ++i)
//     std::cout << *i << std::endl;
}

void micpower::description()
{
  int i;
  outputFile << std::endl; 
  outputFile << "=== Descrition of the file: " << LOG_FILE << std::endl;
  outputFile << "1, time(ms) = Sampling time" << std::endl;
  for(i=0;i<MICPOWER_MAX_COUNTERS;++i)
  {
    outputFile << i+2 << ", ";
    outputFile << _micpower_native_events[i].name << "(" <<_micpower_native_events[i].units << "),"
	       << " = " <<_micpower_native_events[i].description << std::endl;
  }
  outputFile << std::endl;    
}

micpower::~micpower() 
{ 
  description();
  outputFile.close();
}
