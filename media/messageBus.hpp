#pragma once
#include <iostream>
#include <fstream>

void bus_on();
void bus_off();
bool bus_status();

void bus_message_short (std::string message);

void bus_message_long (std::string message);

void bus_message_error_report (std::string report_file,
                               std::string report_class,
                               std::string report_function,
                               std::string report_error);

void bus_message_log_address (std::string log_location, std::string log_message, std::string address);

template < class T >
void bus_message_log (std::string log_location, std::string log_message, T value)
{
    if (bus_status())
        std::cout << " > > LOG || from: " << log_location << " || name: " << log_message << " || value: " << value << " < <" << std::endl;
}

template < class T >
void bus_message_log_compare (std::string log_location, std::string log_message, T value_first, T value_second)
{
    if (bus_status())
        std::cout << " > > LOG COMPARE || from: " << log_location << std::endl <<
                     "                 || name: " << log_message << std::endl <<
                     "                 || value_first:  " << value_first  << std::endl <<
                     "                 || value_second: " << value_second << std::endl;
}

template < class T >
void bus_message_log_ip_port (std::string log_location, std::string log_message, std::string ip, T port)
{
    if (bus_status())
        std::cout << " > > LOG IP:PORT || from: " << log_location << std::endl <<
                     "                 || name: " << log_message << std::endl <<
                     "                 || IP:   " << ip  << std::endl <<
                     "                 || port: " << port << std::endl;
}

