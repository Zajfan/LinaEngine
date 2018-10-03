/*
Author: Inan Evin
www.inanevin.com

BSD 2-Clause License
Lina Engine Copyright (c) 2018, Inan Evin All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.

-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO
-- THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
-- BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
-- GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
-- STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
-- OF SUCH DAMAGE.

4.0.30319.42000
9/30/2018 4:14:11 PM

*/

#pragma once

#ifndef Lina_Console_H
#define Lina_Console_H

#define CONSOLECOLOR_WHITE 15
#define CONSOLECOLOR_GREEN 10
#define CONSOLECOLOR_RED 12
#define CONSOLECOLOR_YELLOW 14
#define CONSOLECOLOR_CYAN 11
#define CONSOLECOLOR_PURPLE 13
#define CONSOLECOLOR_WHITEOVERRED 79
#define CONSOLECOLOR_WHITEOVERGREEN 47
#define CONSOLECOLOR_WHITEOVERGREY 143

#include "Lina_Rendering.h"


class Lina_Console
{

public:

	enum MsgType { Debug, Success, Warning, Error, Initialization, Update, Deinitialization };


	// Returns the current time in string format. Pass in %I, %M, %S, %p %F for formatting.
	std::string now(const char* format = "%c")
	{
		std::time_t t = std::time(0);
		char cstr[128];
		std::strftime(cstr, sizeof(cstr), format, std::localtime(&t));
		return cstr;
	}

	// Adds a colored message to the console.
	inline void AddConsoleMsg(std::string msg, MsgType type, std::string sender, bool flushAfter = false)
	{
		// Get the console.
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Choose a color acc to the type.
		int colorVal = CONSOLECOLOR_WHITE;	// White.

		if (type == MsgType::Error)
			colorVal = CONSOLECOLOR_RED;
		else if (type == MsgType::Warning)
			colorVal = CONSOLECOLOR_YELLOW;
		else if (type == MsgType::Success)
			colorVal = CONSOLECOLOR_GREEN;
		else if (type == MsgType::Initialization)
			colorVal = CONSOLECOLOR_WHITEOVERGREEN;
		else if (type == MsgType::Deinitialization)
			colorVal = CONSOLECOLOR_WHITEOVERRED;
		else if (type == MsgType::Update)
			colorVal = CONSOLECOLOR_WHITEOVERGREY;

		// Set color.
		SetConsoleTextAttribute(hConsole, colorVal);

		// Add an end of line string acc to flush choice.
		// std::string eofStr = flushAfter ? " \r ACTIVE LOOP " : "\r";

		std::string eofStr = "\n";

		// Static bool to record flushings.
		// static bool wasFlushed;

		// If a line without flushing has been logged after a flushed line, add a new line.
		// if (!flushAfter && wasFlushed)
		// std::cout << std::endl;

		// print.
		std::cout << "-> " << sender << " ->: " << msg << " T = " << now("%I:%M:%S %p") << std::string(eofStr);

		// End line or flush the current one according to choice.
		// if (flushAfter) std::cout << std::flush;
		// else std::cout << std::flush << std::endl;
		// wasFlushed = flushAfter;

		// Set the console color back to white.
		colorVal = CONSOLECOLOR_WHITE;
		SetConsoleTextAttribute(hConsole, colorVal);
	}

private:


};


#endif