#include "messageBus.hpp"

namespace {
    bool is_bus_on = false;
}

void bus_on()
{
    is_bus_on = true;
}

void bus_off()
{
    is_bus_on = false;
}

bool bus_status()
{
    return is_bus_on;
}

void bus_message_short (std::string message)
{
    if (bus_status())
        std::cout << " > > MESSAGE -- " << message << std::endl;
}

void bus_message_long (std::string message)
{
    if (bus_status())
        std::cout << "---------------------------------------" << std::endl <<
                     " > > > > > > MESSAGE BEGIN < < < < < < " << std::endl <<
                     message << std::endl <<
                     " > > > > > > MESSAGE END < < < < < <" << std::endl <<
                     "---------------------------------------" << std::endl;
}

void bus_message_error_report (std::string report_file,
                               std::string report_class,
                               std::string report_function,
                               std::string report_error)
{
    if (bus_status())
        std::cerr << "============================================" << std::endl <<
                     " > > > > > > ERROR MESSAGE BEGIN < < < < < <" << std::endl <<
                     "  FILE     -- " << report_file << std::endl <<
                     "  CLASS    -- " << report_class << std::endl <<
                     "  FUNCTION -- " << report_function << std::endl <<
                     "  ERROR    -- " << report_error << std::endl <<
                     " > > > > > > ERROR MESSAGE END < < < < < < <" << std::endl <<
                     "============================================" << std::endl;
}

void bus_message_log_address (std::string log_location, std::string log_message, std::string address)
{
    if (bus_status())
        std::cout << " > > LOG IP:PORT || from: " << log_location << std::endl <<
                     "                 || name: " << log_message << std::endl <<
                     "                 || protocol://IP:port:  " << address  << std::endl;
}
