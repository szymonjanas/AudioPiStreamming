#pragma once
#include "client-communication-with-headquarters.h"
#include "communication-state.hpp"

class Communication_Controller : protected Communication_with_headquarters
{

    Communication_state_converter converter;

public:
    Communication_Controller(const std::string &zmqAddress);
    bool check_connection();
    Replay send_request(Request request);

};
