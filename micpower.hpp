#ifndef _MICPOWER_HPP
#define _MICPOWER_HPP

#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
//#include <chrono>
#include <cstdio>

#include <unistd.h>

#define MICPOWER_MAX_COUNTERS 16
#define PATH_TO_FILE "/sys/class/micras/power"
#define LOG_FILE "mic_energy.log"
#define MICRO_SECOND_MULTIPLIER  1000  // 1 millisecond = 1000 Microseconds
#define SAMPLING_RATE_MS 500

class micpower {
private:
  std::vector<unsigned long long> micCounts;
  std::thread micThread;
  
  bool stopRead;
  std::ifstream inputFile;
  std::ofstream outputFile;
  
  void recordDataFromThread();
  void readSysFile();
  void description();
  
public:
  micpower();
  ~micpower();
  
  void start();
  void stop();

};

typedef struct MICPOWER_native_event_entry
{
   char name[128];
   char units[128];
   char description[128];
} MICPOWER_native_event_entry_t;

//Description of the file /sys/class/micras/power taken from the PAPI documentation
static MICPOWER_native_event_entry_t _micpower_native_events[] = {
{ 	.name 				= "tot0",
		.units 			= "uW",
		.description 		= "Total power, win 0", 
},
{ 	.name 				= "tot1",
		.units 			= "uW",
		.description 		= "Total power, win 1", 
},
{ 	.name 				= "pcie",
		.units 			= "uW",
		.description 		= "PCI-E connector power", 
},
{ 	.name 				= "inst",
		.units 			= "uW",
		.description 		= "Instantaneous power", 
},
{ 	.name 				= "imax",
		.units 			= "uW",
		.description 		= "Max Instantaneous power", 
},
{ 	.name 				= "c2x3",
		.units 			= "uW",
		.description 		= "2x3 connector power", 
},
{ 	.name 				= "c2x4",
		.units 			= "uW",
		.description 		= "2x4 connector power", 
},
{ 	.name 				= "vccp:pwr",
		.units 			= "uW",
		.description 		= "Core rail; Power reading", 
},
{ 	.name 				= "vccp:cur",
		.units 			= "uA",
		.description 		= "Core rail; Current", 
},
{	.name 				= "vccp:volt",
		.units 			= "uV",
		.description 		= "Core rail; Voltage", 
},
{ 	.name 				= "vddg:pwr",
		.units 			= "uW",
		.description 		= "Uncore rail; Power reading", 
},
{ 	.name 				= "vddg:cur",
		.units 			= "uA",
		.description 		= "Uncore rail; Current", 
},
{ 	.name 				= "vddg:volt",
		.units 			= "uV",
		.description 		= "Uncore rail; Voltage", 
},
{ 	.name 				= "vddq:pwr",
		.units 			= "uW",
		.description 		= "Memory sybsystem rail; Power reading", 
},
{ 	.name 				= "vddq:cur",
		.units 			= "uA",
		.description 		= "Memory sybsystem rail; Current", 
},
{ 	.name 				= "vddq:volt",
		.units 			= "uV",
		.description 		= "Memory sybsystem rail; Voltage", 
}
};

#endif