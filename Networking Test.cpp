// Networking Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Networking.h"
#include <ctime>
#include <sstream>


std::string makeMsg(float lat, float lon);


//sends the server 10 msgs over 5 seconds
int main()
{
    NetworkHandler net;

	std::string test = makeMsg(28, -80); //puts unit off the coast of florida
	
	for (size_t i = 0; i < 10; i++)
	{
		net.sendData(test);
		Sleep(500);
	}
    
   

}

// Makes a fake unit at the given long and lat 
std::string makeMsg(float lat, float lon) 
{
	std::stringstream ss;
	time_t current_time;
	struct tm* timeinfo = new tm();
	char buffer[26];
	time(&current_time);
	localtime_s(timeinfo, &current_time);
	strftime(buffer, 26, "%FT%TZ", timeinfo);

	std::string callsign = "Test UNIT";


	ss << "<event version=\"2.0\" uid=\"88772c0d-b218-469f-a995-37981b209928\" type=\"a-n-S\" time=\"" << buffer << "\" start=\"" << buffer << "\" stale=\"" << buffer;
	ss << "\" how=\"h-g-i-g-o\"><point lat=\"" << lat << "\" lon=\"" << lon;
	ss << "\" hae=\"0\" ce=\"9999999\" le=\"9999999\" /><detail><contact callsign=\"" << callsign <<"\" /></detail><remarks><remarks source=\"AIS\" /></remarks></event>";
	return ss.str();

}