/*
    Borealis, a Nintendo Switch UI Library
    Copyright (C) 2019  natinusala
    Copyright (C) 2019  p-sam

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Logger.hpp>

#include <stdio.h>
#include <stdarg.h>

static LogLevel logLevel = LogLevel::INFO;

void setLogLevel(LogLevel newLogLevel)
{
    logLevel = newLogLevel;
}

void printLine(string prefix, string line)
{
    printf("[%s] %s\n", prefix.c_str(), line.c_str());

#ifdef __MINGW32__
    fflush(0);
#endif
}

void error(const char *format, ...)
{
    if (logLevel < LogLevel::ERROR)
        return;

    va_list ap;
    va_start(ap, format);
    char line[256];
    vsnprintf(line, sizeof(line), format, ap);
    va_end(ap);

    printLine("ERROR", string(line));
}

void info(const char *format, ...)
{
    if (logLevel < LogLevel::INFO)
        return;

    va_list ap;
    va_start(ap, format);
    char line[256];
    vsnprintf(line, sizeof(line), format, ap);
    va_end(ap);

    printLine("INFO", string(line));
}

void debug(const char *format, ...)
{
    if (logLevel < LogLevel::DEBUG)
        return;

    va_list ap;
    va_start(ap, format);
    char line[256];
    vsnprintf(line, sizeof(line), format, ap);
    va_end(ap);

    printLine("DEBUG", string(line));
}

void errorResult(string tag, Result rc)
{
#ifdef __SWITCH__
    error("[0x%x] %s failed - %04d-%04d", tag.c_str(), rc, R_MODULE(rc), R_DESCRIPTION(rc));
#else
    error("[0x%x] %s failed - xxxx-xxxx", tag.c_str(), rc);
#endif
}